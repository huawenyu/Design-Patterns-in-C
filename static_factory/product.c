
#include "product.h"


struct product_ops product_ops = {0};

struct product *create_product(enum product_type t)
{
	switch (t) {
	case product_one:
		break;
	case product_two:
		break;
	}
}
