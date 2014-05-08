/**
 * interface.h  2014-05-08
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate for Design Patterns in C
 */
#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <mycommon.h>
#include <mytrace.h>

struct interface_ops;

struct interface {
	struct interface_ops *ops;
};
struct interface_ops {
	void (*write)(struct interface *, char *buf);
	void (*read)(struct interface *, char *buf);
	struct interface_ops *__super;
};

/** constructor(). */
void interface_init(struct interface *interface);

static inline void interface_write(struct interface *interface, char *buf)
{
	interface->ops->write(interface, buf);
}

static inline void interface_read(struct interface *interface, char *buf)
{
	interface->ops->read(interface, buf);
}

#endif /* __INTERFACE_H__ */