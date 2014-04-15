
#ifndef GRANDSON_H_
#define GRANDSON_H_

#include "child.h"

struct grandson {
	struct child child;
};

void grandson_init(struct grandson *);

#endif /* GRANDSON_H_ */
