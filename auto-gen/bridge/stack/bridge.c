/**
 * bridge.c  2014-05-02 01:32:58
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

#include "bridge.h"

void bridge_init(struct bridge *bridge)
{
	memset(bridge, sizeof(*bridge), 0);
}

void bridge_main_entry(void)
{
	struct stack *s1;
	s1 = malloc(sizeof(*s1));
	stack_init(s1, "array");
	stack_push(s1, 1);
	stack_push(s1, 2);
	stack_push(s1, 3);
	printf("stack pop [1,2,3]: %d %d %d\n",
		stack_pop(s1), stack_pop(s1), stack_pop(s1));
	stack_free(s1);

	/*
	Stack[] stacks = { new Stack("java"), new Stack("mine"),
		new StackHanoi("java"), new StackHanoi("mine") };
	for (int i=0, num; i < 20; i++) {
		num = (int) (Math.random() * 1000) % 40;
		for (int j=0; j < stacks.length; j++) stacks[j].push( num );
	}
	for (int i=0, num; i < stacks.length; i++) {
		while ( ! stacks[i].isEmpty()) {
			System.out.print( stacks[i].pop() + "  " );
		}
		System.out.println();
	}
	System.out.println( "total rejected is " + ((StackHanoi)stacks[3]).reportRejected() );
	*/
}
