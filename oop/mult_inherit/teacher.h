
#ifndef TEACHER_H_
#define TEACHER_H_

#include "person.h"
#include "employee.h"

struct teacher {
	struct person person;
	struct employee employee;
};

void teacher_init(struct teacher *, const char *name, int age, int wage, int level);

#endif
