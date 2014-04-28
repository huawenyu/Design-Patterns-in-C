#ifndef __CHAIN_HANDLE_H__
#define __CHAIN_HANDLE_H__

#include <stdio.h>
#include <stdlib.h>

#include <myobj.h>
#include <ulist.h>

struct chain_base_ops;
struct chan_handle
{
	struct chain_base_ops *ops;
	struct chan_handle *next; // 1. "next" pointer in the base class
};

struct chain_base_ops {
	void (*_add)(struct chan_handle *, struct chan_handle *next); /* not override */
	void (*handle)(struct chan_handle *, int);
	void (*close)(struct chan_handle *); /* virtual desturct routine, the base class no-implement */
	struct chain_base_ops *super; /* should as last of ops, pointer to parent's ops */
};

void chain_base_init(struct chan_handle *base); /* construct routine */
struct chain_base_ops *chain_base_ops_get(struct chan_handle *base); /* base::ops */

static inline
void chain_base_add(struct chan_handle *base, struct chan_handle *next)
{
	base->ops->_add(base, next);
}

static inline
void chain_base_handle(struct chan_handle *base, int data)
{
	base->ops->handle(base, data);
}

static inline
void chain_base_close(struct chan_handle *base)
{
	base->ops->close(base);
}

static inline
void chain_base_close_super(struct chan_handle *base)
{
	base->ops->super->close(base);
}

static inline
void chain_base_add_super(struct chan_handle *base, struct chan_handle *next)
{
	base->ops->super->_add(base, next);
}

static inline
void chain_base_handle_super(struct chan_handle *base, int data)
{
	base->ops->super->handle(base, data);
}

#endif /* __CHAIN_HANDLE_H__ */
