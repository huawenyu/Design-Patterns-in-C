/**
 * socket.h  2014-05-11
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
#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <mycommon.h>
#include <mytrace.h>

struct socket {
	struct socket_impl * _pimpl; /** forward declaration */
};

/** constructor(). */
void socket_init(struct socket *socket);

int socket_open(struct socket *socket, int type, int protocol);

int socket_receive(struct socket *socket, char *buf, size_t buf_sz);

#endif /* __SOCKET_H__ */