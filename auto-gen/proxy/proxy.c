/**
 * proxy.c  2014-05-19
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
 * Provides a surrogate or placeholder for another object to control access to
    it.This structural code demonstrates the Proxy pattern which provides a
    representative object (proxy) that controls access to another similar
    object.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "proxy.h"
#include "real_subject.h"

static void proxy_ops_request(struct subject *subject)
{
	struct proxy *a_proxy = container_of(subject, typeof(*a_proxy), subject);
	struct real_subject *sub = a_proxy->_subject;
	_MY_TRACE_STR("proxy::request()\n");
	if (!sub) {
		sub = malloc(sizeof(*sub));
		real_subject_init(sub);
	}
	if (sub) {
		subject_request(&sub->subject);
	}
}

static struct subject_ops subject_ops = {
	.request = proxy_ops_request,
};

/** constructor(). */
void proxy_init(struct proxy *proxy)
{
	_MY_TRACE_STR("proxy_init()\n");
	memset(proxy, sizeof(*proxy), 0);
	subject_init(&proxy->subject);
	CLASS_OPS_INIT(proxy->subject.ops, subject_ops);
}
