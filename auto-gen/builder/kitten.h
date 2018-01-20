
/**
 * kitten.h  2014-04-28 16:14:06
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
#ifndef __KITTEN_H__
#define __KITTEN_H__
#include "animal.h"


struct kitten {
	struct animal animal;
};

void kitten_init(struct kitten *);



#endif /* __KITTEN_H__ */
