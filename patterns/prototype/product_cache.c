
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "product_cache.h"


static struct product_cache_ops product_cache_ops = {0
};

void product_cache_init(struct product_cache *product_cache)
{
	memset(product_cache, sizeof(*product_cache), 0);
	product_cache->ops = &product_cache_ops;
}


void product_cache_load_cache()
{
	struct book *b1;
	struct disk *d1;

	printf("product_cache::load_cache()\n");
	
	b1 = malloc(sizeof(*b1));
	book_init(b1);
	product_set_description(&b1->product, "Oliver Twist");
	product_set_sku(&b1->product, "B1");
	book_set_pages_num(b1, 100);

	product_cache_ops.product_list[product_cache_ops.product_list_sz++] = &b1->product;

	d1 = malloc(sizeof(*d1));
	disk_init(d1);
	product_set_description(&d1->product, "Superman");
	product_set_sku(&d1->product, "D1");
	disk_set_duration(d1, 180);

	product_cache_ops.product_list[product_cache_ops.product_list_sz++] = &d1->product;
}
struct product * product_cache_get_product(const char *sku)
{
	int ii;
	printf("product_cache::get_product()\n");
	for (ii=0; ii < product_cache_ops.product_list_sz; ii++) {
		if (0 == strcmp(sku, product_get_sku(product_cache_ops.product_list[ii])))
			return product_clone(product_cache_ops.product_list[ii]);
	}
	return 0;
}
