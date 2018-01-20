/**
 * test.c  2014-05-04
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
#include <stdio.h>
#include <stdlib.h>

#include <mycommon.h>
#include <myobj.h>
#include <mytrace.h>
#include <test_suite.h>
#include "primitive.h"
#include "row.h"
#include "column.h"

static int test_main_entry(char *output, size_t sz)
{
	/*
	Row first(1);                 // Row1
	Column second(2);             //   |
	Column third(3);              //   +-- Col2
	Row fourth(4);                //   |     |
	Row fifth(5);                 //   |     +-- 7
	first.add(&second);           //   +-- Col3
	first.add(&third);            //   |     |
	third.add(&fourth);           //   |     +-- Row4
	third.add(&fifth);            //   |     |     |
	first.add(&Primitive(6));     //   |     |     +-- 9
	second.add(&Primitive(7));    //   |     +-- Row5
	third.add(&Primitive(8));     //   |     |     |
	fourth.add(&Primitive(9));    //   |     |     +-- 10
	fifth.add(&Primitive(10));    //   |     +-- 8
	first.traverse();             //
	*/

	struct row *r1, *r4, *r5;
	struct column *c2, *c3;
	struct primitive *p6, *p7, *p8, *p9, *p10;
	
	r1 = malloc(sizeof(*r1)); row_init(r1, 1);
	c2 = malloc(sizeof(*c2)); column_init(c2, 2);
	c3 = malloc(sizeof(*c3)); column_init(c3, 3);
	r4 = malloc(sizeof(*r4)); row_init(r4, 4);
	r5 = malloc(sizeof(*r5)); row_init(r5, 5);

	composite_add(&r1->composite, &c2->composite.component);
	composite_add(&r1->composite, &c3->composite.component);

	composite_add(&c3->composite, &r4->composite.component);
	composite_add(&c3->composite, &r5->composite.component);

	p6 = malloc(sizeof(*p6)); primitive_init(p6, 6);
	p7 = malloc(sizeof(*p7)); primitive_init(p7, 7);
	p8 = malloc(sizeof(*p8)); primitive_init(p8, 8);
	p9 = malloc(sizeof(*p9)); primitive_init(p9, 9);
	p10 = malloc(sizeof(*p10)); primitive_init(p10, 10);

	composite_add(&r1->composite, &p6->component);
	composite_add(&c2->composite, &p7->component);
	composite_add(&c3->composite, &p8->component);
	composite_add(&r4->composite, &p9->component);
	composite_add(&r5->composite, &p10->component);

	component_traverse(&r1->composite.component);

	return 0;
}

void main_entry_test(void);
void main_entry_test(void)
{
	my_test_suite_add(test_main_entry, "Test composite");
}
