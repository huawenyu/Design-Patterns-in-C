/**
 * jalapeno_topping.c  2014-05-08
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate for Design Patterns in C *
 * 
 * Consider a case of a pizza shop.
 In the pizza shop they will sale few pizza varieties and they will also provide toppings in the menu.
 Now imagine a situation wherein if the pizza shop has to provide prices for each combination of pizza and topping.
 Even if there are four basic pizzas and 8 different toppings,
 the application would go crazy maintaining all these concrete combination of pizzas and toppings.
 Here comes the decorator pattern.
 As per the decorator pattern,
 you will implement toppings as decorators and pizzas will be decorated by those toppings' decorators.
 Practically each customer would want toppings of his desire and final bill-amount will be composed of the base pizzas and additionally ordered toppings.
 Each topping decorator would know about the pizzas that it is decorating and it's price.
 GetPrice() method of Topping object would return cumulative price of both pizza and the topping.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "jalapeno_topping.h"

static int jalapeno_topping_ops_price(struct pizza *pizza)
{
	/* struct jalapeno_topping *a_jalapeno_topping = container_of(pizza, typeof(*a_jalapeno_topping), toppings_decorator.pizza);
	*/
	_MY_TRACE_STR("jalapeno_topping::price()\n");
	return 0;
}

static struct pizza_ops pizza_ops = {
	.price = jalapeno_topping_ops_price,
};

/** constructor(). */
void jalapeno_topping_init(struct jalapeno_topping *jalapeno_topping, struct pizza *inner, int topping_price)
{
	memset(jalapeno_topping, sizeof(*jalapeno_topping), 0);
	toppings_decorator_init(&jalapeno_topping->toppings_decorator, inner, topping_price);
	CLASS_OPS_INIT(jalapeno_topping->toppings_decorator.pizza.ops, pizza_ops);
}