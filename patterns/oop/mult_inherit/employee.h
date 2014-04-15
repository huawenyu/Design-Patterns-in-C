
#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

struct employee_ops;
struct employee {
	struct employee_ops *ops;
	int wage;
	int level;
};

struct employee_ops {
	void (*wage)(struct employee *);
	void (*level)(struct employee *);
};

void employee_init(struct employee *, int wage, int level);

static inline
void employee_wage(struct employee *employee)
{
	employee->ops->wage(employee);
}

static inline
void employee_level(struct employee *employee)
{
	employee->ops->level(employee);
}

#endif
