
#ifndef __DISK_H__
#define __DISK_H__
#include "product.h"


struct disk {
	struct product product;
	int duration;
};

void disk_init(struct disk *);

void disk_set_duration(struct disk *, int duration);
int disk_get_duration(struct disk *);


#endif /* __DISK_H__ */
