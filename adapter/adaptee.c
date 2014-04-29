
/**
 * adaptee.c  2014-04-29 05:44:08
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

#include "adaptee.h"



void adaptee_init(struct adaptee *adaptee)
{
	memset(adaptee, sizeof(*adaptee), 0);
}


void adaptee_specific_request(struct adaptee *adaptee)
{
	printf("adaptee::specific_request()\n");
}