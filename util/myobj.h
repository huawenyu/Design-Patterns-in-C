#ifndef __MY_OBJ_H__
#define __MY_OBJ_H__

#include <assert.h> /* assert */
#include <stddef.h> /* offset */

/**class support macro:
 * CLASS_OPS_INIT(ptr, ops)
 * CLASS_OPS_INIT_WITH_SUPER(ptr, ops, member)
 *
 * container_of(ptr, type, member)
 *
 * CLASS_SUPER(obj, ops_member, ...)
 * CLASS_SUPER_OPS(obj, ops_member, ops, super, ...)
 */

#define _STR_MYOBJ_PRE_TAG_ "myobj.h:"

/**
 * container_of - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define container_of(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define CLASS_TYPE_CHECK(a, b) do { \
	typeof(a) *_a; \
	typeof(b) *_b; \
	(void) (_a == _b); \
	} while (0)

/*
#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))
*/

/* get error message file info */
#define __CLASS_CONCAT(s1, s2) s1##s2
#define __CLASS_CONCAT_2(s1, s2) __CLASS_CONCAT(s1, s2)
#define __CLASS_CONCAT_3(s1, s2, s3) __CLASS_CONCAT_2(s1, __CLASS_CONCAT_2(s2,s3))
#define __CLASS_INTHELPER(x) 0 ## x
#define __CLASS_TOINT(x) __CLASS_INTHELPER(x)
#define __CLASS_STRINGIFY(x) #x
#define __CLASS_TOSTRING(x) __CLASS_STRINGIFY(x)
#define __CLASS_WHERE __FILE__ ":" __CLASS_TOSTRING(__LINE__)

#define __CLASS_VIRTUAL_VALID_STR(the_number) "the ["the_number"]th virtual function should be defined or overrided," \
		" <OR> should be init() with CLASS_OPS_INIT_WITH_SUPER()."
#define __CLASS_VIRTUAL_CASE(number) case number: assert(super_class_ops[sz] && __CLASS_VIRTUAL_VALID_STR(__CLASS_STRINGIFY(number))); break;
/* copy func-ptr array when src-ops[*] (!0) */
#define __CLASS_COPY_OPS(dst,src,offset) \
{ \
	typedef void (*fptr) (void); \
	int sz = offset/sizeof(fptr); \
	_Static_assert(offset <= sizeof(dst), _STR_MYOBJ_PRE_TAG_ __CLASS_WHERE ":" #src " copy ops size overflow"); \
	CLASS_TYPE_CHECK(dst,src); \
	fptr *derive_class_ops = (fptr*)(&(src)); \
	fptr *super_class_ops = (fptr*)(&(dst)); \
	while ((--sz) >= 0) { \
		if (derive_class_ops[sz]) \
			super_class_ops[sz] = derive_class_ops[sz]; \
		else {\
			switch (sz) { \
			__CLASS_VIRTUAL_CASE(0)\
			__CLASS_VIRTUAL_CASE(1)\
			__CLASS_VIRTUAL_CASE(2)\
			__CLASS_VIRTUAL_CASE(3)\
			__CLASS_VIRTUAL_CASE(4)\
			__CLASS_VIRTUAL_CASE(5)\
			__CLASS_VIRTUAL_CASE(6)\
			__CLASS_VIRTUAL_CASE(7)\
			__CLASS_VIRTUAL_CASE(8)\
			__CLASS_VIRTUAL_CASE(9)\
			__CLASS_VIRTUAL_CASE(10)\
			__CLASS_VIRTUAL_CASE(11)\
			__CLASS_VIRTUAL_CASE(12)\
			__CLASS_VIRTUAL_CASE(13)\
			__CLASS_VIRTUAL_CASE(14)\
			__CLASS_VIRTUAL_CASE(15)\
			default: \
				assert(super_class_ops[sz] && __CLASS_VIRTUAL_VALID_STR(__CLASS_STRINGIFY(more))); break; \
			} \
		} \
	} \
}

#define __CLASS_OPS_INIT_COMN(ptr, ops, offset) \
	static unsigned int __CLASS_CONCAT_3(ops,_init_flag_,__LINE__) = 0; \
	void __CLASS_CONCAT_2(class_ops_init_,__LINE__)(void) \
	{ \
		typeof(*(ptr)) l_super_ops = *(ptr); \
		if (!__CLASS_CONCAT_3(ops,_init_flag_,__LINE__)) { \
			__CLASS_CONCAT_3(ops,_init_flag_,__LINE__) = 1; \
			__CLASS_COPY_OPS(l_super_ops, ops, offset); \
			ops = l_super_ops; \
		} \
	} \
	assert(ptr && "init() should be after super's init()");

#define __CLASS_OPS_INIT(ptr, ops, offset) \
	__CLASS_OPS_INIT_COMN(ptr, ops, offset) \
	if (!__CLASS_CONCAT_3(ops, _init_flag_, __LINE__)) { \
		__CLASS_CONCAT_2(class_ops_init_,__LINE__)(); \
	}

#define __CLASS_OPS_INIT_WITH_MEMBER(ptr, ops, offset, member, rval) \
	__CLASS_OPS_INIT_COMN(ptr, ops, offset) \
	if (!__CLASS_CONCAT_3(ops,_init_flag_,__LINE__)) { \
		__CLASS_CONCAT_2(class_ops_init_,__LINE__)(); \
		(ops).member = rval; \
	}

/**Initial the derive class's ops
 *  - class layer: one class call class_ops_init() once
 *  - ops is holder of func-ptr array
 *  - polymorphism
 * @PRE ptr have inited pointer to super-class ops
 * @see CLASS_OPS_INIT_WITH_SUPER support super ptr-to parent's ops
 */
#define CLASS_OPS_INIT(ptr, ops) \
	__CLASS_OPS_INIT(ptr, ops, sizeof(ops)) \
	ptr = &ops;

/**Initial with super using object-ptr
 * @PRE ptr have inited pointer to super-class ops
 * @PRE the member be the last element of struct
 * @member typeof ops-ptr, pointer to parent-class's ops
 */
#define CLASS_OPS_INIT_SUPER(ptr, ops) \
	CLASS_OPS_INIT_WITH_SUPER(ptr, ops, __super, sizeof(ops))
#define CLASS_OPS_INIT_SUPER_WITH_FIRST_STATIC(ptr, ops, static_member) \
	CLASS_OPS_INIT_WITH_SUPER(ptr, ops, __super, offsetof(typeof(ops), static_member))

#define CLASS_OPS_INIT_WITH_SUPER(ptr, ops, member, sz) \
	typeof(ptr) __CLASS_CONCAT_2(l_super,__LINE__) = ptr; \
	_Static_assert((sz) == sizeof((ops).member) + offsetof(typeof(ops), member), \
			_STR_MYOBJ_PRE_TAG_  __CLASS_WHERE ":" #ops "." #member " should be the last element with order (ops,super[,static])," \
			" <OR> should be init with CLASS_OPS_INIT_SUPER_WITH_FIRST_STATIC()"); \
	__CLASS_OPS_INIT_WITH_MEMBER(ptr, ops, offsetof(typeof(ops), member), member, __CLASS_CONCAT_2(l_super,__LINE__)) \
	assert(__CLASS_CONCAT_2(l_super,__LINE__) != &ops && "dead-loop: super pointer-to itself"); \
	ptr = &ops;

/**Call super method
 * Assume ops have standard member name: ops, super
 */
#define CLASS_SUPER(ptr, function, ...) \
	CLASS_SUPER_OPS(ptr, function, ops, __super, ##__VA_ARGS__)

#define CLASS_SUPER_RTN(ptr, function, rtn_type, ...) \
	CLASS_SUPER_OPS_RTN(ptr, function, rtn_type, ops, __super, ##__VA_ARGS__) \

/**Call super method
 * @ptr the basic class ptr
 * @function the method function name
 * @ops class.ops member name
 * @super pos.super member name
 */
#define CLASS_SUPER_OPS(ptr, function, ops, super, ...) do{ \
	typeof((ptr)->ops) __CLASS_CONCAT_2(l_ops,__LINE__) = (ptr)->ops; \
	assert((ptr)->ops->super && "invalid super pointer: check whether init with CLASS_OPS_INIT_SUPER()"); \
	if ((ptr)->ops->super) { \
		(ptr)->ops = (ptr)->ops->super; \
		(ptr)->ops->function(ptr, ##__VA_ARGS__); \
	} \
	(ptr)->ops = __CLASS_CONCAT_2(l_ops,__LINE__); \
}while(0)

#define CLASS_SUPER_OPS_RTN(ptr, function, rtn_type, ops, super, ...) ({ \
	rtn_type __CLASS_CONCAT_2(l_super_rtn,__LINE__); \
	typeof((ptr)->ops) l_ops = (ptr)->ops; \
	assert((ptr)->ops->super && "invalid super pointer: check whether init with CLASS_OPS_INIT_SUPER()"); \
	if ((ptr)->ops->super) { \
		(ptr)->ops = (ptr)->ops->super; \
		__CLASS_CONCAT_2(l_super_rtn,__LINE__) = (ptr)->ops->function(ptr, ##__VA_ARGS__); \
	} \
	(ptr)->ops = l_ops; \
	__CLASS_CONCAT_2(l_super_rtn,__LINE__); \
})

/*____________________________________________________________________________
                                                            MACROS OVERLOAD */
#define __CLASS_SELECT( NAME, NUM ) __CLASS_CONCAT( NAME ## _, NUM )

#define __CLASS_GET_COUNT( _1, _2, _3, _4, _5, _6 /* ad nauseam */, COUNT, ... ) COUNT
#define __CLASS_VA_SIZE( ... ) __CLASS_GET_COUNT( __VA_ARGS__, 6, 5, 4, 3, 2, 1 )

#define __CLASS_VA_SELECT( NAME, ... ) __CLASS_SELECT( NAME, __CLASS_VA_SIZE(__VA_ARGS__) )(__VA_ARGS__)

/*____________________________________________________________________________
                                                             OVERLOAD SAMPLE*/
#define MY_OVERLOADED( ... ) __CLASS_VA_SELECT( MY_IMPL, __VA_ARGS__ )
#define MY_IMPL_1( X ) foo< X >
#define MY_IMPL_2( X, Y ) bar< X >( Y )
#define MY_IMPL_3( X, Y, Z ) bang_ ## X< Y >.Z()

#endif /* __MY_OBJ_H__ */
