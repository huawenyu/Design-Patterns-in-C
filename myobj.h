#ifndef __MY_OBJ_H__
#define __MY_OBJ_H__

#include <assert.h> /* assert */
#include <stddef.h> /* offset */

/**class support macro:
 * CLASS_OPS_INIT(ptr, ops)
 * CLASS_OPS_INIT_WITH_SUPER(ptr, ops, member)
 * CLASS_OPS_INIT_WITH_STATIC(ptr, ops, member)
 * CLASS_OPS_INIT_SUPER_STATIC(ptr, ops, m_super, m_static)
 */

#define _STR_MYOBJ_PRE_TAG_ "myobj.h:"

/* copy func-ptr array when src-ops[*] (!0) */
#define __CLASS_COPY_OPS(dst,src,offset) \
{ \
	typedef void (*fptr) (void); \
	int sz = offset/sizeof(fptr); \
	_Static_assert(offset <= sizeof(dst), _STR_MYOBJ_PRE_TAG_ #src " copy ops size overflow"); \
	_Static_assert(sizeof(dst) == sizeof(src), _STR_MYOBJ_PRE_TAG_ #src " copy ops should be same type"); \
	fptr *psrc = (fptr*)(&(src)); \
	fptr *pdst = (fptr*)(&(dst)); \
	while ((--sz) >= 0) { \
		if (psrc[sz]) \
			pdst[sz] = psrc[sz]; \
		else \
			assert(pdst[sz]); \
	} \
}

#define __CLASS_OPS_INIT(ptr, ops, offset) \
	static unsigned int ops##_init_flag_ = 0; \
	void class_ops_init() \
	{ \
		typeof(*(ptr)) l_super_ops = *(ptr); \
		if (!ops##_init_flag_) { \
			ops##_init_flag_ = 1; \
			__CLASS_COPY_OPS(l_super_ops, ops, offset); \
			ops = l_super_ops; \
		} \
	} \
	assert(ptr); \
	if (!ops##_init_flag_) { \
		class_ops_init(); \
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
	assert(ptr); \
	__CLASS_OPS_INIT(ptr, ops, sizeof(ops)) \
	ptr = &ops;

/**Initial with super using object-ptr
 * @PRE ptr have inited pointer to super-class ops
 * @PRE the member be the last element of struct
 * @member typeof ops-ptr, pointer to parent-class's ops
 */
#define CLASS_OPS_INIT_WITH_SUPER(ptr, ops, member) \
	typeof(ptr) l_super = ptr; \
	assert(ptr); \
	_Static_assert(sizeof(ops) == sizeof((ops).member) + offsetof(typeof(ops), member), \
			_STR_MYOBJ_PRE_TAG_ #ops "." #member " as super member, should be the last element"); \
	assert(!(ops).member); \
	__CLASS_OPS_INIT(ptr, ops, offsetof(typeof(ops), member)) \
	(ops).member = l_super; \
	ptr = &ops;

/**Initial with static-member
 * @PRE ptr have inited pointer to super-class ops
 * @PRE the member be the last element of struct, keep align
 * @member as static-member, can be object or object-ptr
 */
#define CLASS_OPS_INIT_WITH_STATIC(ptr, ops, member) \
	assert(ptr); \
	_Static_assert(sizeof(ops) == sizeof((ops).member) + offsetof(typeof(ops), member), \
			_STR_MYOBJ_PRE_TAG_ #ops "." #member " as static member should be the last element and keep align"); \
	__CLASS_OPS_INIT(ptr, ops, offsetof(typeof(ops), member)) \
	ptr = &ops;

/**Initial with super and static-member
 * @PRE ptr have inited pointer to super-class ops
 * @PRE order should be func-ptr+m_super+m_static, keep align
 * @member as static-member, can be object or object-ptr
 */
#define CLASS_OPS_INIT_SUPER_STATIC(ptr, ops, m_super, m_static) \
	typeof(ptr) l_super = ptr; \
	assert(ptr); \
	_Static_assert(offsetof(typeof(ops), m_super) < offsetof(typeof(ops), m_static), \
			_STR_MYOBJ_PRE_TAG_ #ops "." #m_super " as super member should before static member " #m_static); \
	_Static_assert(sizeof(ops) == offsetof(typeof(ops), m_super) \
			+ sizeof((ops).m_super) + sizeof((ops).m_static), \
			_STR_MYOBJ_PRE_TAG_ #ops "." #m_super "+" #m_static " should be the last element and keep align"); \
	assert(!(ops).m_super); \
	__CLASS_OPS_INIT(ptr, ops, offsetof(typeof(ops), m_super)) \
	(ops).m_super = l_super; \
	ptr = &ops;

#endif /* __MY_OBJ_H__ */

