/**
 * student_controller.c  2014-05-10
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

#include "student_controller.h"

/** constructor(). */
void student_controller_init(struct student_controller *student_controller, struct student *model, struct student_view *view)
{
	memset(student_controller, sizeof(*student_controller), 0);
	student_controller->_model = model;
	student_controller->_view = view;
}

void student_controller_set_student_name(struct student_controller *controller, const char * student_name)
{
	_MY_TRACE_STR("student_controller::set_student_name()\n");
	student_set_name(controller->_model, student_name, 0);
}

char * student_controller_get_student_name(struct student_controller *controller)
{
	_MY_TRACE_STR("student_controller::get_student_name()\n");
	return student_get_name(controller->_model);
}

void student_controller_set_student_roll_no(struct student_controller *controller, int student_roll_no)
{
	_MY_TRACE_STR("student_controller::set_student_roll_no()\n");
	student_set_roll_no(controller->_model, student_roll_no);
}

int student_controller_get_student_roll_no(struct student_controller *controller)
{
	_MY_TRACE_STR("student_controller::get_student_roll_no()\n");
	return student_get_roll_no(controller->_model);
}

void student_controller_update_view(struct student_controller *controller)
{
	_MY_TRACE_STR("student_controller::update_view()\n");
	student_view_show_me(controller->_view, controller->_model);
}
