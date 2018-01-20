#ifndef __MY_TRACE_H__
#define __MY_TRACE_H__

#include <execinfo.h>	/* backtrace */

void _my_trace_backtrace_init(void);
int  _my_trace_backtrace_indent(void);

#define MY_TRACE_FLAG          "" /* trace log prefix */
#define MY_DEBUG_CHECK_LEVEL() 1  /* log level check */
#define __MY_DUMP printf          /* log implement */

#define _MY_TRACE_INIT_ \
	_my_trace_backtrace_init();

#define _MY_TRACE_STR(str) \
	if (MY_DEBUG_CHECK_LEVEL()) {                                      \
		int _my_trace_indent;                                          \
		_my_trace_indent = _my_trace_backtrace_indent();               \
		__MY_DUMP(MY_TRACE_FLAG"%*s%s", 3*_my_trace_indent, " ", str); \
	}

#define _MY_TRACE_PTR(param) \
	if (MY_DEBUG_CHECK_LEVEL()) {                                      \
		int _my_trace_indent;                                          \
		_my_trace_indent = _my_trace_backtrace_indent();               \
		__MY_DUMP(MY_TRACE_FLAG"%*s%s(%p)\n", 3*_my_trace_indent, " ", \
			__FUNCTION__, param);                                      \
	}

#define _MY_TRACE_2(param_p, param_int) \
	if (MY_DEBUG_CHECK_LEVEL()) {                                      \
		int _my_trace_indent;                                          \
		_my_trace_indent = _my_trace_backtrace_indent();               \
		__MY_DUMP(MY_TRACE_FLAG"%*s%s(%p)\n", 3*_my_trace_indent, " ", \
				__FUNCTION__, param_p, param_int);                     \
	}

#define _MY_TRACE_ \
	if (MY_DEBUG_CHECK_LEVEL()) {                                      \
		int _my_trace_indent;                                          \
		_my_trace_indent = _my_trace_backtrace_indent();               \
		__MY_DUMP(MY_TRACE_FLAG"%*s%s()\n", 3*_my_trace_indent, " ",   \
			__FUNCTION__);                                             \
	}

#endif /* __MY_TRACE_H__ */
