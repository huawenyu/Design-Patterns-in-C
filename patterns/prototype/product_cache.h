
#ifndef __PRODUCT_CACHE_H__
#define __PRODUCT_CACHE_H__

#include "book.h"
#include "disk.h"

struct product_cache_ops;
struct product_cache {
	struct product_cache_ops *ops;
};
struct product_cache_ops {
	int product_list_sz;
	struct product * product_list[32];
};
void product_cache_init(struct product_cache *);

void product_cache_load_cache(void);
struct product * product_cache_get_product(const char *);


#endif /* __PRODUCT_CACHE_H__ */
