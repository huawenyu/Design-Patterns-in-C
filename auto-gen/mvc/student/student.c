/**
 * student.c  2014-05-10
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
 * Student object acting as a model.StudentView will be a view class which can
    print student details on console and StudentController is the controller
    class responsible to store data in Student object and update view
    StudentView accordingly.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>

#include "student.h"

/** constructor(). */
void student_init(struct student *student)
{
	memset(student, sizeof(*student), 0);
}

void student_set_name(struct student *student, const char *name, int name_sz)
{
	_MY_TRACE_STR("student::set_name()\n");
	snprintf(student->_name, sizeof(student->_name), name);
}

char * student_get_name(struct student *student)
{
	_MY_TRACE_STR("student::get_name()\n");
	return student->_name;
}

void student_set_roll_no(struct student *student, int roll_no)
{
	_MY_TRACE_STR("student::set_roll_no()\n");
	student->_roll_no = roll_no;
}

int student_get_roll_no(struct student *student)
{
	_MY_TRACE_STR("student::get_roll_no()\n");
	return student->_roll_no;
}
