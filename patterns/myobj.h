#ifndef __MY_OBJ_H__
#define __MY_OBJ_H__

#include <assert.h> /* assert */
#include <stddef.h> /* offset */

/**class support macro:
 * CLASS_OPS_INIT(ptr, ops)
 * CLASS_OPS_INIT_WITH_SUPER(ptr, ops, member)
 * CLASS_OPS_INIT_WITH_STATIC(ptr, ops, member)
 * CLASS_OPS_INIT_SUPER_STATIC(ptr, ops, m_super, m_static)
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

/* get error message file info */
#define __CLASS_CONCAT(s1, s2) s1##s2
#define __CLASS_CONCAT_2(s1, s2) __CLASS_CONCAT(s1, s2)
#define __CLASS_CONCAT_3(s1, s2, s3) __CLASS_CONCAT_2(s1, __CLASS_CONCAT_2(s2,s3))
#define __CLASS_INTHELPER(x) 0 ## x
#define __CLASS_TOINT(x) __CLASS_INTHELPER(x)
#define __CLASS_STRINGIFY(x) #x
#define __CLASS_TOSTRING(x) __CLASS_STRINGIFY(x)
#define __CLASS_WHERE __FILE__ ":" __CLASS_TOSTRING(__LINE__)

/* copy func-ptr array when src-ops[*] (!0) */
#define __CLASS_COPY_OPS(dst,src,offset) \
{ \
	typedef void (*fptr) (void); \
	typeof(dst) *type_dst; \
	typeof(src) *type_src = 0; \
	int sz = offset/sizeof(fptr); \
	_Static_assert(offset <= sizeof(dst), _STR_MYOBJ_PRE_TAG_ __CLASS_WHERE ":" #src " copy ops size overflow"); \
	_Static_assert(sizeof(dst) == sizeof(src), _STR_MYOBJ_PRE_TAG_  __CLASS_WHERE ":" #src " copy ops should be same type"); \
	type_dst = type_src; \
	type_src = type_dst; \
	fptr *psrc = (fptr*)(&(src)); \
	fptr *pdst = (fptr*)(&(dst)); \
	while ((--sz) >= 0) { \
		if (psrc[sz]) \
			pdst[sz] = psrc[sz]; \
		else \
			assert(pdst[sz]); \
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
	assert(ptr);

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
 * @see CLASS_OPS_INIT_WITH_STATIC support static member
 * @see CLASS_OPS_INIT_SUPER_STATIC support super and static member
 */
#define CLASS_OPS_INIT(ptr, ops) \
	__CLASS_OPS_INIT(ptr, ops, sizeof(ops)) \
	ptr = &ops;

/**Initial with super using object-ptr
 * @PRE ptr have inited pointer to super-class ops
 * @PRE the member be the last element of struct
 * @member typeof ops-ptr, pointer to parent-class's ops
 */
#define CLASS_OPS_INIT_WITH_SUPER(ptr, ops, member) \
	typeof(ptr) l_super = ptr; \
	_Static_assert(sizeof(ops) == sizeof((ops).member) + offsetof(typeof(ops), member), \
			_STR_MYOBJ_PRE_TAG_  __CLASS_WHERE ":" #ops "." #member " as super member, should be the last element"); \
	__CLASS_OPS_INIT_WITH_MEMBER(ptr, ops, offsetof(typeof(ops), member), member, l_super) \
	assert(l_super != &ops); \
	ptr = &ops;

/**Initial with static-member
 * @PRE ptr have inited pointer to super-class ops
 * @PRE the member be the last element of struct, keep align
 * @member as static-member, can be object or object-ptr
 */
#define CLASS_OPS_INIT_WITH_STATIC(ptr, ops, member) \
	_Static_assert(sizeof(ops) == sizeof((ops).member) + offsetof(typeof(ops), member), \
			_STR_MYOBJ_PRE_TAG_  __CLASS_WHERE ":" #ops "." #member " as static member should be the last element and keep align"); \
	__CLASS_OPS_INIT(ptr, ops, offsetof(typeof(ops), member)) \
	ptr = &ops;

/**Initial with super and static-member
 * @PRE ptr have inited pointer to super-class ops
 * @PRE order should be func-ptr+m_super+m_static, keep align
 * @member as static-member, can be object or object-ptr
 */
#define CLASS_OPS_INIT_SUPER_STATIC(ptr, ops, m_super, m_static) \
	typeof(ptr) l_super = ptr; \
	_Static_assert(offsetof(typeof(ops), m_super) < offsetof(typeof(ops), m_static), \
			_STR_MYOBJ_PRE_TAG_  __CLASS_WHERE ":" #ops "." #m_super " as super member should before static member " #m_static); \
	_Static_assert(sizeof(ops) == offsetof(typeof(ops), m_super) \
			+ sizeof((ops).m_super) + sizeof((ops).m_static), \
			_STR_MYOBJ_PRE_TAG_  __CLASS_WHERE ":" #ops "." #m_super "+" #m_static " should be the last element and keep align"); \
	__CLASS_OPS_INIT_WITH_MEMBER(ptr, ops, offsetof(typeof(ops), m_super), m_super, l_super) \
	assert(l_super != &ops); \
	ptr = &ops;

/**Call super method
 * Assume ops have standard member name: ops, super
 */
#define CLASS_SUPER(ptr, function, ...) \
	CLASS_SUPER_OPS(ptr, function, ops, super, ##__VA_ARGS__)

/**Call super method
 * @ptr the basic class ptr
 * @function the method function name
 * @ops class.ops member name
 * @super pos.super member name
 */
#define CLASS_SUPER_OPS(ptr, function, ops, super, ...) do{\
	typeof((ptr)->ops) l_ops = (ptr)->ops; \
	assert((ptr)->ops->super); \
	if ((ptr)->ops->super) { \
		(ptr)->ops = (ptr)->ops->super; \
		(ptr)->ops->function(ptr, ##__VA_ARGS__); \
	} \
	(ptr)->ops = l_ops; \
}while(0)

#endif /* __MY_OBJ_H__ */
