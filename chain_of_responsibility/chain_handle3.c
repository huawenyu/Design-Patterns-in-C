#include "chain_handle3.h"

static void chain_handler3_ops_handle(struct chan_handle *base, int data)
{
	if (data % 3 == 0) {
		printf("H3 processed %d  \n", data);
	}
	else {
		// 3. Don't handle requests 3 times out of 4
		printf("H3 passsed %d  \n", data);

		// 3. Delegate to the base class
		//chain_base_ops_get(base, i);
		chain_base_handle_super(base, data);
	}
}

static void chain_handler3_ops_close(struct chan_handle *base)
{
}

static struct chain_base_ops chain_handler3_ops = {
	.handle = chain_handler3_ops_handle,
	.close = chain_handler3_ops_close,
};

void chain_handle3_init(struct chain_handle3 *chain)
{
	chain_base_init(&chain->super);
	CLASS_OPS_INIT_WITH_SUPER(chain->super.ops, chain_handler3_ops, super);
}
