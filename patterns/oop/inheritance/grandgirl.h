
#ifndef GRANDGIRL_H_
#define GRANDGIRL_H_

#include "child.h"

struct grandgirl {
	struct child child;
};

void grandgirl_init(struct grandgirl *);

#endif
