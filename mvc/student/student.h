/**
 * student.h  2014-05-10
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
#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <mycommon.h>
#include <mytrace.h>

struct student {
	char _name[32];
	int _roll_no;
};

/** constructor(). */
void student_init(struct student *student);

void student_set_name(struct student *student, const char *name, int name_sz);

char * student_get_name(struct student *student);

void student_set_roll_no(struct student *student, int roll_no);

int student_get_roll_no(struct student *student);

#endif /* __STUDENT_H__ */
