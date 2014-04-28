
#ifndef PERSON_H_
#define PERSON_H_

struct person_ops;
struct person {
	struct person_ops *ops;
	char name[32];
	int age;
};

struct person_ops {
	void (*name)(struct person *);
	void (*age)(struct person *);
};

void person_init(struct person *, const char *name, int age);

static inline
void person_name(struct person *person)
{
	person->ops->name(person);
}

static inline
void person_age(struct person *person)
{
	person->ops->age(person);
}

#endif
