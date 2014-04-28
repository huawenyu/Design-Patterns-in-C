
/**
 * kid.c  2014-04-28 16:14:06
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "kid.h"



void kid_init(struct kid *kid)
{
	memset(kid, sizeof(*kid), 0);
}


void kid_make_animal(struct kid *kid, struct animal_builder *builder)
{
	printf("kid::make_animal()\n");
	animal_builder_build_header(builder);
	animal_builder_build_body(builder);
	animal_builder_build_leg(builder);
	animal_builder_build_arm(builder);
	animal_builder_build_tail(builder);
}
