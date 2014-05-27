#ifndef __STACK_H__
#define __STACK_H__

/*
 * Simple stack implementation.

 * STACK_IMPL(sample, type, 128);
 *
 * bool sample_is_empty()
 * bool sample_is_full()
 * void sample_push(type)
 * type sample_pop()
 */

#define STACK_IMPL(stack, type, sz) \
static int stack ## _top = 0; \
static type stack[sz]; \
 \
static inline int stack ## _is_empty(void) \
{ \
	return (stack ## _top <= 0); \
} \
static inline int stack ## _is_full(void) \
{ \
	return (stack ## _top >= sz); \
} \
static inline void stack ## _push(type obj) \
{ \
	if (!stack ## _is_full()) \
		stack[stack ## _top++] = obj; \
} \
static inline type stack ## _pop(void) \
{ \
	if (!stack ## _is_empty()) \
		return stack[--stack ## _top]; \
	return (type){0}; \
}

#endif
