/**
 * real_subject.h  2014-05-19
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
#ifndef __REAL_SUBJECT_H__
#define __REAL_SUBJECT_H__

#include <mycommon.h>
#include <mytrace.h>

#include "subject.h"

struct real_subject {
	struct subject subject;
};

/** constructor(). */
void real_subject_init(struct real_subject *real_subject);

#endif /* __REAL_SUBJECT_H__ */