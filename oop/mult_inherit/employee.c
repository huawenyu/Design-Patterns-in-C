
#include <stdio.h>
#include "employee.h"

static void employee_wage_(struct employee *employee)
{
	printf("employee::wage() = %d\n", employee->wage);
}

static void employee_level_(struct employee *employee)
{
	printf("employee::level() = %d\n", employee->level);
}

static struct employee_ops ops = {
	.wage = employee_wage_,
	.level = employee_level_,
};

void employee_init(struct employee *employee, int wage, int level)
{
	employee->ops = &ops;
	employee->wage = wage;
	employee->level = level;
}
