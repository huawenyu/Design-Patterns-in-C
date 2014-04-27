
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <myobj.h>
#include "disk.h"


static struct product * disk_ops_clone(struct product *product)
{
	printf("disk::clone()\n");
	return 0;
}
static void disk_ops_set_description(struct product *product, const char *desc)
{
	printf("disk::set_description()\n");
}
static void disk_ops_set_sku(struct product *product, const char *sku)
{
	printf("disk::set_sku()\n");
}
static char * disk_ops_get_description(struct product *product)
{
	printf("disk::get_description()\n");
	return 0;
}
static char * disk_ops_get_sku(struct product *product)
{
	printf("disk::get_sku()\n");
	return 0;
}

static struct product_ops product_ops = {
	.clone = disk_ops_clone,
	.set_description = disk_ops_set_description,
	.set_sku = disk_ops_set_sku,
	.get_description = disk_ops_get_description,
	.get_sku = disk_ops_get_sku,
};


void disk_init(struct disk *disk)
{
	memset(disk, sizeof(*disk), 0);
	product_init(&disk->product);
	CLASS_OPS_INIT(disk->product.ops, product_ops);
}


void disk_set_duration(struct disk *disk, int duration)
{
	printf("disk::set_duration()\n");
}
int disk_get_duration(struct disk *disk)
{
	printf("disk::get_duration()\n");
	return 0;
}