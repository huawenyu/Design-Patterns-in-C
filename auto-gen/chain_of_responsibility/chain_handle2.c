#include "chain_handle2.h"

static void chain_handler2_ops_handle(struct chain_handle *base, int data)
{
	if (data % 3 == 2) {
		printf("H2 processed %d  \n", data);
	}
	else {
		// 3. Don't handle requests 3 times out of 4
		printf("H2 passsed %d  \n", data);

		// 3. Delegate to the base class
		//chain_base_ops_get(base, i);
		chain_base_handle_super(base, data);
	}
}

static void chain_handler2_ops_close(struct chain_handle *base)
{
}

static struct chain_base_ops chain_handler2_ops = {
	.handle = chain_handler2_ops_handle,
	.close = chain_handler2_ops_close,
};

void chain_handle2_init(struct chain_handle2 *chain)
{
	chain_base_init(&chain->super);
	CLASS_OPS_INIT_SUPER(chain->super.ops, chain_handler2_ops);
}
