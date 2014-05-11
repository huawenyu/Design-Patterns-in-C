/**
 * socket_impl.c  2014-05-11
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

#include "socket_impl.h"

/** constructor(). */
void socket_impl_init(struct socket_impl *socket_impl)
{
	memset(socket_impl, sizeof(*socket_impl), 0);
}

int socket_impl_network_byte_order(struct socket_impl *socket_impl)
{
	_MY_TRACE_STR("socket_impl::network_byte_order()\n");
	return 0;
}