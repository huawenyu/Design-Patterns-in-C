/**
 *   2014-05-10
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate for Design Patterns in C
 */
#include <stdio.h>
#include <stdlib.h>

#include <mycommon.h>
#include <myobj.h>
#include <mytrace.h>
#include <test_suite.h>
#include "student.h"
#include "student_view.h"
#include "student_controller.h"

static struct student *test_retrive_student_from_database(void)
{
	_MY_TRACE_STR("test::retrive_student_from_database()\n");
	/** PSEUDOCODE
    Student student = new Student();
    student.setName("Robert");
    student.setRollNo("10");
    return student;
	*/
	struct student *stu;
	stu = malloc(sizeof(*stu));
	student_init(stu);
	student_set_name(stu, "Robert", 0);
	student_set_roll_no(stu, 10);
	return stu;
}

static int test_main(void)
{
	_MY_TRACE_STR("test::main()\n");
	/** PSEUDOCODE
    //fetch student record based on his roll no from the database
    Student model  = retriveStudentFromDatabase();
    
    //Create a view : to write student details on console
    StudentView view = new StudentView();
    
    StudentController controller = new StudentController(model, view);
    
    controller.updateView();
    
    //update model data
    controller.setStudentName("John");
    
    controller.updateView();
	*/
	struct student *model;
	struct student_view *view;
	struct student_controller *controller;

	model = test_retrive_student_from_database();

	view = malloc(sizeof(*view));
	student_view_init(view);

	controller = malloc(sizeof(*controller));
	student_controller_init(controller, model, view);

	student_controller_update_view(controller);

	student_controller_set_student_name(controller, "John");
	student_controller_set_student_roll_no(controller, 19);
	student_controller_update_view(controller);

	return 0;
}

static int test_main_entry(char *output, size_t sz)
{
	test_main();
	return 0;
}

void main_entry_test(void);
void main_entry_test(void)
{
	my_test_suite_add(test_main_entry, "Test mvc_student");
}
