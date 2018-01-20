
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <myobj.h>
#include "book.h"


static struct product * book_ops_clone(struct product *product)
{
	printf("book::clone()\n");
	return 0;
}
static void book_ops_set_description(struct product *product, const char *desc)
{
	printf("book::set_description()\n");
}
static void book_ops_set_sku(struct product *product, const char *sku)
{
	printf("book::set_sku()\n");
}
static char * book_ops_get_description(struct product *product)
{
	printf("book::get_description()\n");
	return 0;
}
static char * book_ops_get_sku(struct product *product)
{
	printf("book::get_sku()\n");
	return 0;
}

static struct product_ops product_ops = {
	.clone = book_ops_clone,
	.set_description = book_ops_set_description,
	.set_sku = book_ops_set_sku,
	.get_description = book_ops_get_description,
	.get_sku = book_ops_get_sku,
};


void book_init(struct book *book)
{
	memset(book, sizeof(*book), 0);
	product_init(&book->product);
	CLASS_OPS_INIT(book->product.ops, product_ops);
}


void book_set_pages_num(struct book *book, int pages)
{
	printf("book::set_pages_num()\n");
}
int book_get_pages_num(struct book *book)
{
	printf("book::get_pages_num()\n");
	return 0;
}