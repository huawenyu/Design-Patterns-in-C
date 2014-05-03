#include <assert.h> /* assert */
#include <stdlib.h> /* exit */
#include <string.h> /* memset */
#include <mytrace.h>

#define MY_TRACE_SIZE_MAX 64
#define MY_TRACE_SIZE     32
#define MY_TRACE_STEP     2

static void* g_backtrace[MY_TRACE_SIZE_MAX] = {0};
static int   g_backtrace_top = 0;
static void* g_backtrace_local_stack[MY_TRACE_SIZE];

/* call once in top function such as main_entry() */
void _my_trace_backtrace_init(void)
{
    int addr_sz;
    addr_sz = backtrace(g_backtrace_local_stack, 3);

    assert(addr_sz >= 3);
    if (addr_sz < 3) {
        exit(1);
    }

    memset(g_backtrace, 0, sizeof(g_backtrace));
    g_backtrace_top = 0;
    g_backtrace[g_backtrace_top++] = g_backtrace_local_stack[2];
}

/*
 @ return 0, fail
 */
int _my_trace_backtrace_indent(void)
{
    /* bt at least 4, so offset is 3 from [0,1,2,3] */
    int ii, jj, addr_sz, trace_sz=6, offset=3;
    void *up_func = 0;

increase_stack_sz:
    addr_sz = backtrace(g_backtrace_local_stack, trace_sz);

try_upper:
    if (offset < addr_sz) {
        up_func = g_backtrace_local_stack[offset];
    } else {
        trace_sz += MY_TRACE_STEP;
        if (trace_sz <= MY_TRACE_SIZE)
            goto increase_stack_sz;
        goto fail;
    }

    for (ii=g_backtrace_top-1; ii>=0; ii--) {
        if (up_func == g_backtrace[ii]) {
            g_backtrace_top = ii+1;
            for (jj=offset-1; jj >= 2 && g_backtrace_top < MY_TRACE_SIZE_MAX; jj--) {
                up_func = g_backtrace[g_backtrace_top - 1];
                if (g_backtrace_local_stack[jj] != up_func) { /* avoid recursive */
                    g_backtrace[g_backtrace_top++] = g_backtrace_local_stack[jj];
                }
            }

            goto out;
        }
    }
    offset ++;
    goto try_upper;

out:
    return g_backtrace_top - 1;

fail:
    return 0;
}
