#ifndef __CHAIN_HANDLE2_H__
#define __CHAIN_HANDLE2_H__

#include "chain_handle.h"

struct chain_handle2 {
	struct chan_handle super;
};

void chain_handle2_init(struct chain_handle2 *);

#endif /* __CHAIN_HANDLE2_H__ */

