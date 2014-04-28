
#include <stdio.h>
#include <myobj.h>
#include "grandgirl.h"

static void grandgirl_v_override_who(struct parent *parent)
{
	printf("[virtual-override] I'm %s.\n", parent->name);
}

static struct parent_ops parent_ops = {
	.v_override_who = grandgirl_v_override_who,
};

static struct child_ops child_ops = {0};

void grandgirl_init(struct grandgirl *grandgirl)
{
	child_init(&grandgirl->child);
	CLASS_OPS_INIT(grandgirl->child.parent.ops, parent_ops);
	CLASS_OPS_INIT(grandgirl->child.ops, child_ops);

#if 0
	// CLASS_OPS_INIT(grandgirl->child.parent.ops, parent_ops);
	static unsigned int parent_ops_init_flag_20 = 0;
	void class_ops_init_20(void)
	{
		typeof(*(grandgirl->child.parent.ops)) l_super_ops = *(grandgirl->child.parent.ops);
		if (!parent_ops_init_flag_20) {
			parent_ops_init_flag_20 = 1;
			{
				typedef void (*fptr)(void);
				typeof(l_super_ops) *type_dst;
				typeof(parent_ops) *type_src = 0;
				type_dst = type_src;
				type_src = type_dst;
				int sz = sizeof(parent_ops) / sizeof(fptr);
				_Static_assert(sizeof(parent_ops) <= sizeof(l_super_ops),
						"myobj.h:" "grandgirl.c" ":" "20" ":" "parent_ops" " copy ops size overflow");
				_Static_assert(sizeof(l_super_ops) == sizeof(parent_ops),
						"myobj.h:" "grandgirl.c" ":" "20" ":" "parent_ops" " copy ops should be same type");
				fptr *psrc = (fptr*) (&(parent_ops));
				fptr *pdst = (fptr*) (&(l_super_ops));
				while ((--sz) >= 0) {
					if (psrc[sz])
						pdst[sz] = psrc[sz];
					else
						((pdst[sz]) ? (void) (0) : __assert_fail("pdst[sz]", "grandgirl.c", 20, __PRETTY_FUNCTION__));
				}
			};
			parent_ops = l_super_ops;
		}
	}
	((grandgirl->child.parent.ops) ? (void) (0) : __assert_fail("grandgirl->child.parent.ops", "grandgirl.c", 20, __PRETTY_FUNCTION__));
	if (!parent_ops_init_flag_20) {
		class_ops_init_20();
	}
	grandgirl->child.parent.ops = &parent_ops;


	//CLASS_OPS_INIT(grandgirl->child.ops, child_ops);
	static unsigned int child_ops_init_flag_21 = 0;
	void class_ops_init_21(void)
	{
		typeof(*(grandgirl->child.ops)) l_super_ops = *(grandgirl->child.ops);
		if (!child_ops_init_flag_21) {
			child_ops_init_flag_21 = 1;
			{
				typedef void (*fptr) (void);
				typeof(l_super_ops) *type_dst;
				typeof(child_ops) *type_src = 0;
				type_dst = type_src;
				type_src = type_dst;
				int sz = sizeof(child_ops)/sizeof(fptr);
				_Static_assert(sizeof(child_ops) <= sizeof(l_super_ops), "myobj.h:" "grandgirl.c" ":" "21" ":" "child_ops" " copy ops size overflow");
				_Static_assert(sizeof(l_super_ops) == sizeof(child_ops), "myobj.h:" "grandgirl.c" ":" "21" ":" "child_ops" " copy ops should be same type");
				fptr *psrc = (fptr*)(&(child_ops));
				fptr *pdst = (fptr*)(&(l_super_ops));
				while ((--sz) >= 0) {
					if (psrc[sz])
						pdst[sz] = psrc[sz];
					else
						((pdst[sz]) ? (void) (0) : __assert_fail ("pdst[sz]", "grandgirl.c", 21, __PRETTY_FUNCTION__));
				}
			};
			child_ops = l_super_ops;
		}
	}
	((grandgirl->child.ops) ? (void) (0) : __assert_fail ("grandgirl->child.ops", "grandgirl.c", 21, __PRETTY_FUNCTION__));
	if (!child_ops_init_flag_21) {
		class_ops_init_21();
	}
	grandgirl->child.ops = &child_ops;

#endif

	snprintf(grandgirl->child.parent.name, sizeof(grandgirl->child.parent.name),
		"GrandGirl-Emma");
}

