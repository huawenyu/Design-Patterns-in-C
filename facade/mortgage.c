/**
 * mortgage.c  2014-05-19
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
#include "mortgage.h"

/** constructor(). */
void mortgage_init(struct mortgage *m)
{
	_MY_TRACE_STR("mortgage_init()\n");
	memset(m, sizeof(*m), 0);

	m->_bank = malloc(sizeof(*m->_bank));
	bank_init(m->_bank);

	m->_credit = malloc(sizeof(*m->_credit));
	credit_init(m->_credit);

	m->_loan = malloc(sizeof(*m->_loan));
	loan_init(m->_loan);
}

int mortgage_is_eligible(struct mortgage *m, char *cust, int amount)
{
	int eligible = 1;
	_MY_TRACE_STR("mortgage::is_eligible()\n");
	printf("%s applies for %d loan\n", cust, amount);

	// Check creditworthyness of applicant
	if (!bank_has_sufficient_savings(m->_bank, cust, amount)) {
		eligible = 0;
	}
	else if (loan_has_bad_loan(m->_loan, cust)) {
		eligible = 0;
	}
	else if (!credit_has_good_credit(m->_credit, cust)) {
		eligible = 0;
	}

	return eligible;
}
