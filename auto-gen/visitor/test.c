/**
 *   2014-05-13
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
#include "dog.h"
#include "cat.h"
#include "sound.h"
#include "eat.h"

static int test_main(void)
{
	struct cat *a_cat;
	struct dog *a_dog;
	struct sound *a_sound;
	struct eat *a_eat;

	a_cat = malloc(sizeof(*a_cat));
	cat_init(a_cat);

	a_dog = malloc(sizeof(*a_dog));
	dog_init(a_dog);

	a_sound = malloc(sizeof(*a_sound));
	sound_init(a_sound);

	a_eat = malloc(sizeof(*a_eat));
	eat_init(a_eat);

	animal_do_it(&a_cat->animal, &a_sound->animal_do);
	animal_do_it(&a_dog->animal, &a_eat->animal_do);
	
	return 0;
}

static int test_main_entry(char *output, size_t sz)
{
	test_main();
	return 0;
}

void main_entry_test(void);
void main_entry_test(void)
{
	my_test_suite_add(test_main_entry, "Test visitor");
}
