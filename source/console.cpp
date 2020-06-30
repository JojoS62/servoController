/**
 * @file console.cpp
 *
 * @brief console implementation using CMDB library.
 *
 * After boot, it prompts "CMD>" in console. Type "help" command to get help.
 */

#include "console.h"

#define CID_POS		        1
#define CID_VERSION		    2
#define CID_FREE		    3
#define CID_CFG_SET		    4
#define CID_CFG_RESET	    5
#define CID_CFG_SAVE	    6
#define CID_CFG_PRINT	    7
#define CID_POS_PRINT       8
#define CID_POS_TURN        9
#define CID_POS_TILT        10
#define CID_SPEED           11

static const cmd user_cmd[] = {
    {"pos",         SUBSYSTEM,  CID_POS             , ""            , "* pos Subsystem"},
    {"ver",         GLOBALCMD,  CID_VERSION         , ""	        , "show version info", ""},
    {"free",        GLOBALCMD,  CID_FREE            , ""	        , "show amount of free memory", ""},
    {"cfgset",      CID_POS,    CID_CFG_SET         , "%s %s"       , "config set", "config_key value"},
    {"cfgreset",    CID_POS,    CID_CFG_RESET       , ""            , "config reset", ""},
    {"cfgsave",     CID_POS,    CID_CFG_SAVE        , ""            , "config save to flash"},
    {"cfgprint",    CID_POS,    CID_CFG_PRINT       , ""            , "print all config"},
    {"print",       CID_POS,    CID_POS_PRINT       , ""            , "print setup"},
    {"turn",        CID_POS,    CID_POS_TURN        , "%f"          , "set pos turn value"},
    {"tilt",        CID_POS,    CID_POS_TILT        , "%f"          , "set pos tilt value"},
    {"speed",       GLOBALCMD,  CID_SPEED           , "%f"          , "set motor speed"}
};

Console::Console(BufferedSerial *serial) :
    cmdb(serial, cmds, callback(this, &Console::dispatcher))
{
    init();
}

/** Sample User Command Dispatcher.
 *
 * @parm cmdb the command interpreter object.
 * @parm cid the command id.
 */
void Console::dispatcher(Cmdb& cmdb, int cid)
{
    //cmdb.printf("my_dispatcher: cid=%d\r\n", cid);

    switch (cid) {
        case CID_VERSION :
            //print_version();
            break;
        case CID_FREE :
            //cmdb.printf("my_dispatcher: parm 0=%d\r\n",cmdb.INTPARM(0));
            //print_memstat();
            break;
        case CID_CFG_SET :
            _config.lock_config();
            if (!_config.value_replace(cmdb.STRINGPARM(0), cmdb.STRINGPARM(1))) {
                cmdb.printf("invalid key='%s'\r\n", cmdb.STRINGPARM(0));
            }
            _config.unlock_config();
            break;
        case CID_CFG_RESET :
            _config.lock_config();
             _config.reset_default();
            _config.unlock_config();
            break;
        case CID_CFG_SAVE :
            _config.lock_config();
            if (!_config.save_config()) {
                cmdb.printf("save fail\r\n");
            }
            _config.unlock_config();
            break;
        case CID_CFG_PRINT :
            _config.lock_config();
            _config.print_all();
            _config.unlock_config();
            break;
        case CID_POS_PRINT :
            //send_main_message(MSG_PID_PRINT, 0, 0.0f);
            break;
        case CID_POS_TURN:
            cmdb.printf("my_dispatcher: parm 0=%f\r\n", cmdb.FLOATPARM(0));
            //send_main_message(MSG_PID_KP, 0, cmdb.FLOATPARM(0));
            break;
        case CID_POS_TILT:
            cmdb.printf("my_dispatcher: parm 0=%f\r\n", cmdb.FLOATPARM(0));
            //send_main_message(MSG_PID_KI, 0, cmdb.FLOATPARM(0));
            break;
        case CID_SPEED :
            //end_main_message(MSG_SPEED, 0, cmdb.FLOATPARM(0));
            break;
        default:
            printf("unknown CID=%u\r\n", cid);
            break;
    }
}


void Console::init()
{
    //Create a Command Table Vector.
    cmds = vector<cmd>(&user_cmd[0], &user_cmd[sizeof(user_cmd)/sizeof(user_cmd[0])]);

    //Add some of our own first...
    //Add some predefined...
    cmds.push_back(COMMANDS); //Handled by Cmdb internally.
    cmds.push_back(BOOT); //Handled by Cmdb internally.

    cmds.push_back(ECHO); //Handled by Cmdb internally.
    cmds.push_back(BOLD); //Handled by Cmdb internally.
    cmds.push_back(CLS);  //Handled by Cmdb internally.

    //cmds.push_back(MACRO);  //Handled by Cmdb internally.
    //cmds.push_back(RUN);    //Handled by Cmdb internally.
    //cmds.push_back(MACROS); //Handled by Cmdb internally.

    //Add some predefined and mandatory...
    cmds.push_back(IDLE); //Handled by Cmdb internally.
    cmds.push_back(HELP); //Handled by Cmdb internally.

    //Create and initialize the Command Interpreter.
    //Cmdb cmdb(serial, cmds, &my_dispatcher);
    cmdb.replace(cmds);

    //cmdb.printf("%d=%d\r\n",cmds[0].subs,cmds[0].cid);
    //cmdb.printf("%d=%d\r\n",cmds[1].subs,cmds[1].cid);
}

void Console::process()
{
    while (1) {
        //Check for input...
        if (cmdb.hasnext()==true) {

            //Supply input to Command Interpreter
            if (cmdb.scan(cmdb.next())) {
            }
        }

        //For Macro Support we basically do the same but take characters from the macro buffer.
        //Example Macro: Test|Int_42|Idle
        while (cmdb.macro_hasnext()) {
            //Get and process next character.
            cmdb.scan(cmdb.macro_next());

            //After the last character we need to add a cr to force execution.
            if (!cmdb.macro_peek()) {
                cmdb.scan(cr);
            }
        }
    }
}


