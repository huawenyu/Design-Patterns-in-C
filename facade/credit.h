/**
 * credit.h  2014-05-19
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
 * Provide a unified interface to a set of interfaces in a subsystem. Facade
    defines a higher-level interface that makes the subsystem easier to use.
The classes and/or objects participating in this pattern are:
    Facade   (MortgageApplication)
      - knows which subsystem classes are responsible for a request.
      - delegates client requests to appropriate subsystem objects.
    Subsystem classes   (Bank, Credit, Loan)
      - implement subsystem functionality.
      - handle work assigned by the Facade object.
      - have no knowledge of the facade and keep no reference to it.
 */
#ifndef __CREDIT_H__
#define __CREDIT_H__

#include <mycommon.h>
#include <mytrace.h>

struct credit {
};

/** constructor(). */
void credit_init(struct credit *credit);

int credit_has_good_credit(struct credit *credit, char *name);

#endif /* __CREDIT_H__ */