
/**
 * adapter.h  2014-04-29 05:44:08
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
#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include "adaptee.h"
#include "target.h"


struct adapter {
	struct target target;
	struct adaptee * _adaptee;
};

void adapter_init(struct adapter *, struct adaptee *);



#endif /* __ADAPTER_H__ */
