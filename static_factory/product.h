
#ifndef PRODUCT_H_
#define PRODUCT_H_

enum product_type {
	product_one,
	product_two,
};

struct product_ops;
struct product {
	struct product_ops *ops;
};

struct product_ops {
	void (*do_it)(struct product*);
};

// product's static function
struct product *create_product(enum product_type);

static inline product_do_it(struct product *product)
{
	product->ops->do_it(product);
}

#endif /* PRODUCT_H_ */
