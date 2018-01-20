
/**
 * animal_builder.h  2014-04-28 16:14:06
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate to show Design Pattern in C
 */
#ifndef __ANIMAL_BUILDER_H__
#define __ANIMAL_BUILDER_H__


struct animal_builder_ops;
struct animal_builder {
	struct animal_builder_ops *ops;
};
struct animal_builder_ops {
	void (*build_header)(struct animal_builder *);
	void (*build_body)(struct animal_builder *);
	void (*build_leg)(struct animal_builder *);
	void (*build_arm)(struct animal_builder *);
	void (*build_tail)(struct animal_builder *);
};
void animal_builder_init(struct animal_builder *);


static inline void animal_builder_build_header(struct animal_builder *animal_builder)
{
	animal_builder->ops->build_header(animal_builder);
}
static inline void animal_builder_build_body(struct animal_builder *animal_builder)
{
	animal_builder->ops->build_body(animal_builder);
}
static inline void animal_builder_build_leg(struct animal_builder *animal_builder)
{
	animal_builder->ops->build_leg(animal_builder);
}
static inline void animal_builder_build_arm(struct animal_builder *animal_builder)
{
	animal_builder->ops->build_arm(animal_builder);
}
static inline void animal_builder_build_tail(struct animal_builder *animal_builder)
{
	animal_builder->ops->build_tail(animal_builder);
}

#endif /* __ANIMAL_BUILDER_H__ */
