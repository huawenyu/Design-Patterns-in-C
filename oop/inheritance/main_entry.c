/**
 * main_entry.c  2014-05-02 23:11:33
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

#include "main_entry.h"

void main_entry_init(struct main_entry *main_entry)
{
	memset(main_entry, sizeof(*main_entry), 0);
}

void main_entry_main_entry(void)
{
	printf("main_entry::main_entry()\n");
}

char * main_entry_get_name(void)
{
	return "OOP::Inheritance";
}
