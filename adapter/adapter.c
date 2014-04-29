
/**
 * adapter.c  2014-04-29 05:44:08
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <myobj.h>
#include "adapter.h"
#include "adaptee.h"


static void adapter_ops_request(struct target *target)
{
	struct adapter *adp = container_of(target, typeof(*adp), target);
	printf("adapter::request()\n");
	adaptee_specific_request(adp->_adaptee);
}

static struct target_ops target_ops = {
	.request = adapter_ops_request,
};


void adapter_init(struct adapter *adapter, struct adaptee *adaptee)
{
	memset(adapter, sizeof(*adapter), 0);
	target_init(&adapter->target);
	CLASS_OPS_INIT(adapter->target.ops, target_ops);
	adapter->_adaptee = adaptee;
}

