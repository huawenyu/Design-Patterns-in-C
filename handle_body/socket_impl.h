/**
 * socket_impl.h  2014-05-11
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
#ifndef __SOCKET_IMPL_H__
#define __SOCKET_IMPL_H__

#include <mycommon.h>
#include <mytrace.h>

struct sockaddr_un;
/** PIMPL-Private part: Donnot let others include this file, except socket
    implement */
struct socket_impl {
	int sock_id;
	struct sockaddr_un *sockaddr;
	char buffer[1024];
};

/** constructor(). */
void socket_impl_init(struct socket_impl *socket_impl);

int socket_impl_network_byte_order(struct socket_impl *socket_impl);

#endif /* __SOCKET_IMPL_H__ */
