/**
 * loan.c  2014-05-19
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>

#include "loan.h"

/** constructor(). */
void loan_init(struct loan *loan)
{
	_MY_TRACE_STR("loan_init()\n");
	memset(loan, sizeof(*loan), 0);
}

int loan_has_bad_loan(struct loan *loan, char *name)
{
	_MY_TRACE_STR("loan::has_bad_loan()\n");
	return 0;
}
