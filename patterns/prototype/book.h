
#ifndef __BOOK_H__
#define __BOOK_H__
#include "product.h"


struct book {
	struct product product;
	int pages_num;
};

void book_init(struct book *);

void book_set_pages_num(struct book *, int pages);
int book_get_pages_num(struct book *);


#endif /* __BOOK_H__ */
