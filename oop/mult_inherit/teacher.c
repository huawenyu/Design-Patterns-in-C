
#include <stdio.h>
#include <myobj.h>
#include "teacher.h"

static void teacher_name(struct person *person)
{
	printf("The teacher's name is %s\n", person->name);
}

static void teacher_level(struct employee *employee)
{
	printf("The teacher is instuctor as level %d\n", employee->level);
}

static struct person_ops person_ops = {
	.name = teacher_name,
};

static struct employee_ops employee_ops = {
	.level = teacher_level,
};

void teacher_init(struct teacher *teacher, const char *name, int age, int wage, int level)
{
	person_init(&teacher->person, name, age);
	CLASS_OPS_INIT(teacher->person.ops, person_ops);
	employee_init(&teacher->employee, wage, level);
	CLASS_OPS_INIT(teacher->employee.ops, employee_ops);
}
