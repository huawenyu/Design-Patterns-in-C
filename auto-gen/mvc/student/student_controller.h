/**
 * student_controller.h  2014-05-10
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
#ifndef __STUDENT_CONTROLLER_H__
#define __STUDENT_CONTROLLER_H__

#include <mycommon.h>
#include <mytrace.h>

#include "student.h"
#include "student_view.h"

struct student_controller {
	struct student * _model;
	struct student_view * _view;
};

/** constructor(). */
void student_controller_init(struct student_controller *student_controller, struct student *model, struct student_view *view);

void student_controller_set_student_name(struct student_controller *student_controller, const char * student_name);

char * student_controller_get_student_name(struct student_controller *student_controller);

void student_controller_set_student_roll_no(struct student_controller *student_controller, int student_roll_no);

int student_controller_get_student_roll_no(struct student_controller *student_controller);

void student_controller_update_view(struct student_controller *student_controller);

#endif /* __STUDENT_CONTROLLER_H__ */
