
#include <stdio.h>
#include <stdlib.h>

#include <test_suite.h>
#include "teacher.h"

static int test_mult_inherit(char *output, size_t sz)
{
	int ii;
	struct teacher teachers[4];

	teacher_init(&teachers[0], "Tom", 28, 4000, 3);
	teacher_init(&teachers[1], "Jerry", 35, 5000, 4);
	teacher_init(&teachers[2], "John", 40, 6000, 5);
	teacher_init(&teachers[3], "Andy", 45, 7000, 6);
	
	for (ii=0; ii < 4; ii++) {
		person_name(&teachers[ii].person);
		person_age(&teachers[ii].person);

		employee_level(&teachers[ii].employee);
		employee_wage(&teachers[ii].employee);
	}

	return 0;
}

void mult_inherit_test(void);
void mult_inherit_test(void)
{
	my_test_suite_add(test_mult_inherit, "Mult_Inherit");
}
