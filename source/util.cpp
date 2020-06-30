/**
 * @file util.cpp
 *
 * @brief system wide utility function
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#if defined(__CC_ARM) && !defined(__MICROLIB)
// Keil MDK with microlib supports __heapstats();
#define SUPPORT_HEAPSTATS
#endif

#if defined(SUPPORT_HEAPSTATS)

static void heap_printf(void *dummy, const char *fmt, ...)
{
    va_list	arg_ptr;

    if (strchr(fmt, '\n') != NULL) {
        putchar('\r');
    }
    va_start(arg_ptr, fmt);
    vprintf(fmt, arg_ptr);
    va_end(arg_ptr);
}

void print_memstat(void)
{
    __heapstats((__heapprt)heap_printf, NULL);
    printf("\r\n");
}

#else

/**
 * Compute max consecutive memory chunk, by trying to allocate it.
 */
static uint32_t comput_free_heap(uint32_t resolution, uint32_t maximum)
{
    uint32_t low = 0;
    uint32_t high = maximum + 1;

    while (high - low > resolution) {
        int mid = (low + high) / 2;
        void* p = malloc(mid);
        if (p == NULL) {
            high = mid;
        } else {
            free(p);
            low = mid;
        }
    }

    return low;
}

void print_memstat(void)
{
    printf("heap free %u\r\n", comput_free_heap(512, 192*1024));
}

#endif


