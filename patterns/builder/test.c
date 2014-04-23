
#include <stdio.h>
#include <stdlib.h>

#include <test_suite.h>
#include "kid.h"
#include "animal_builder_monkey.h"
#include "animal_builder_kitten.h"

static int test_builder(char *output, size_t sz)
{
	struct kid *akid;
	struct animal_builder_monkey *builder_monkey;
	struct animal_builder_kitten *builder_kitten;

	akid = malloc(sizeof(*akid));
	if (!akid) {
		snprintf(output, sz, "malloc akid fail");
		return 1;
	}
	kid_init(akid);

	builder_monkey = malloc(sizeof(*builder_monkey));
	if (!builder_monkey) {
		snprintf(output, sz, "malloc builder_monkey fail");
		return 1;
	}
	animal_builder_monkey_init(builder_monkey);

	builder_kitten = malloc(sizeof(*builder_kitten));
	if (!builder_kitten) {
		snprintf(output, sz, "malloc builder_kitten fail");
		return 1;
	}
	animal_builder_kitten_init(builder_kitten);

	kid_make_animal(akid, &builder_monkey->animal_builder);
	kid_make_animal(akid, &builder_kitten->animal_builder);

	return 0;
}

void builder_test(void);
void builder_test(void)
{
	my_test_suite_add(test_builder, "Builder");
}
