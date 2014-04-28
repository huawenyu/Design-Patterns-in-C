#ifndef __CHAIN_HANDLE1_H__
#define __CHAIN_HANDLE1_H__

#include "chain_handle.h"

struct chain_handle1 {
	struct chan_handle super;
};

void chain_handle1_init(struct chain_handle1 *);

#endif /* __CHAIN_HANDLE1_H__ */

