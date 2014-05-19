/**
 * loan.h  2014-05-19
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
#ifndef __LOAN_H__
#define __LOAN_H__

#include <mycommon.h>
#include <mytrace.h>

struct loan {
};

/** constructor(). */
void loan_init(struct loan *loan);

int loan_has_bad_loan(struct loan *loan, char *name);

#endif /* __LOAN_H__ */