
#include <stdio.h>
#include <stdlib.h>

#include <test_suite.h>
#include <myobj.h>
#include "product_cache.h"
#include "book.h"
#include "disk.h"

static int test_prototype(char *output, size_t sz)
{
	struct product *p1;
	struct book *b2;
	struct disk *d2;

	product_cache_load_cache();

	p1 = product_cache_get_product("B1");
	b2 = container_of(p1, struct book, product);
	printf("SKU = %s, %s, %d",
		product_get_sku(p1),
		product_get_description(p1),
		book_get_pages_num(b2));

	p1 = product_cache_get_product("D1");
	d2 = container_of(p1, struct disk, product);
	printf("SKU = %s, %s, %d",
		product_get_sku(p1),
		product_get_description(p1),
		disk_get_duration(d2));

	return 0;
}

void prototype_test(void);
void prototype_test(void)
{
	my_test_suite_add(test_prototype, "Prototype");
}
