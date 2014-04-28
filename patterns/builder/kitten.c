
/**
 * kitten.c  2014-04-28 16:14:06
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
#include <myobj.h>
#include "kitten.h"


static void kitten_ops_eat(struct animal *animal)
{
	printf("kitten::eat()\n");
}

static struct animal_ops animal_ops = {
	.eat = kitten_ops_eat,
};


void kitten_init(struct kitten *kitten)
{
	memset(kitten, sizeof(*kitten), 0);
	animal_init(&kitten->animal);
	CLASS_OPS_INIT(kitten->animal.ops, animal_ops);
}

