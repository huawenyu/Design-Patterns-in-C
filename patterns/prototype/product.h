
#ifndef __PRODUCT_H__
#define __PRODUCT_H__


struct product_ops;
struct product {
	struct product_ops *ops;
	char description[32];
	char sku[32];
};
struct product_ops {
	struct product * (*clone)(struct product *);
	void (*set_description)(struct product *, const char *desc);
	void (*set_sku)(struct product *, const char *sku);
	char * (*get_description)(struct product *);
	char * (*get_sku)(struct product *);
};
void product_init(struct product *);


static inline struct product * product_clone(struct product *product)
{
	return product->ops->clone(product);
}
static inline void product_set_description(struct product *product, const char *desc)
{
	product->ops->set_description(product, desc);
}
static inline void product_set_sku(struct product *product, const char *sku)
{
	product->ops->set_sku(product, sku);
}
static inline char * product_get_description(struct product *product)
{
	return product->ops->get_description(product);
}
static inline char * product_get_sku(struct product *product)
{
	return product->ops->get_sku(product);
}

#endif /* __PRODUCT_H__ */
