/**
 * socket.c  2014-05-11
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate for Design Patterns in C *
 * 
 * The Handle/Body idiom was originally introduced by Jim Coplien as a
    technique for hiding implementation details in the header file. This idiom
    is also called Pimpl, which stands for "implementation pointer" following
    the Hungarian naming convention. The version I present here is suitable for
    most header files that declare classes. The solution is reducing the number
    of #include directives and removing implementation details from header
    files (which are compiled multiple times) to a .cpp file (which gets
    compiled only once). Such "header downsizing" has another advantage: it
    enhances encapsulation.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>

#include "socket.h"

/** constructor(). */
void socket_init(struct socket *socket)
{
	memset(socket, sizeof(*socket), 0);
}

int socket_open(struct socket *socket, int type, int protocol)
{
	_MY_TRACE_STR("socket::open()\n");
	return 0;
}

int socket_receive(struct socket *socket, char *buf, size_t buf_sz)
{
	_MY_TRACE_STR("socket::receive()\n");
	/** PSEUDOCODE
    bool little_end=pimpl->network_byte_order();
    pimpl->buffer.clear();
    pimpl->buffer.assign(p, p+length);
	*/
	return 0;
}