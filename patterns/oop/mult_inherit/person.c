
#include <stdio.h>
#include "person.h"

static void person_name_(struct person *person)
{
	printf("Person::name() is %s\n", person->name);
}

static void person_age_(struct person *person)
{
	printf("Person::name() is %s\n", person->name);
}

static struct person_ops ops = {
	.name =  person_name_,
	.age = person_age_,
};

void person_init(struct person *person, const char *name, int age)
{
	person->ops = &ops;
	snprintf(person->name, sizeof(person->name), name);
	person->age = age;
}
