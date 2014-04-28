
/**
 * kid.h  2014-04-28 16:14:06
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate to show Design Pattern in C
 */
#ifndef __KID_H__
#define __KID_H__

#include "animal_builder.h"


struct kid {
	char name[32];
};

void kid_init(struct kid *);

void kid_make_animal(struct kid *, struct animal_builder *builder);


#endif /* __KID_H__ */
