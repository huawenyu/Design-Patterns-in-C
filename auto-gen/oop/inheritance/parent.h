/**
 * parent.h  2014-05-03 15:06:28
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
#ifndef __PARENT_H__
#define __PARENT_H__

#include <mycommon.h>

struct parent_ops;

struct parent {
	struct parent_ops *ops;
	int pub_data1;
	int pri_data2;
};
struct parent_ops {
	void (*_destructor)(struct parent *); /** called by free(): put resources, forward to super. */
	void (*free)(struct parent *); /** free memory after call destructor(). */
	void (*pub_v_func1)(struct parent *);
	void (*pub_v_func2)(struct parent *);
	void (*pri_v_func3)(struct parent *);
	void (*pri_v_func4)(struct parent *);
	struct parent_ops *__super;
	int static_pub_data3;
	int static_pri_data4;
};
void parent_init(struct parent *);

void parent_pub_m_func1(struct parent *);

void parent_static_pub_m_func2(void);

/** called by free(): put resources, forward to super. */
static inline void parent__destructor(struct parent *parent)
{
	parent->ops->_destructor(parent);
}
/** free memory after call destructor(). */
static inline void parent_free(struct parent *parent)
{
	parent->ops->free(parent);
}

static inline void parent_pub_v_func1(struct parent *parent)
{
	parent->ops->pub_v_func1(parent);
}

static inline void parent_pub_v_func2(struct parent *parent)
{
	parent->ops->pub_v_func2(parent);
}

static inline void parent_pri_v_func3(struct parent *parent)
{
	parent->ops->pri_v_func3(parent);
}

static inline void parent_pri_v_func4(struct parent *parent)
{
	parent->ops->pri_v_func4(parent);
}

#endif /* __PARENT_H__ */