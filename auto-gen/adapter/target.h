
/**
 * target.h  2014-04-29 05:44:08
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
#ifndef __TARGET_H__
#define __TARGET_H__


struct target_ops;
struct target {
	struct target_ops *ops;
};
struct target_ops {
	void (*request)(struct target *);
};
void target_init(struct target *);


static inline void target_request(struct target *target)
{
	target->ops->request(target);
}

#endif /* __TARGET_H__ */
