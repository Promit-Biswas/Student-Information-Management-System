#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include "linkedlist.h"
#include "input-handler.h"
#include "department.h"
#include "grade.h"

#define DATA_FILE_STUD "databases/students.dat"

typedef struct student
{
    uint16_t student_id;
    char *student_name;
    uint8_t student_gender;
    uint16_t department_id;
} student_t;

extern node_t *student_root;

void add_student();
void delete_student();
void update_student();

/*******************************************************************************
 * Name:       stud_id_compare
 *
 * Input:      void *a - Pointer to a `student_t` structure, representing
 *                       the student's data.
 *             void *b - Pointer to a `uint16_t` variable, representing the
 *                       student ID to be compared.
 *
 * Return:     success 0 Returns `0` if the student ID matches the provided
 *             fail 1    otherwise, returns `1`.
 *
 * Description: This function compares the student ID of a student with a given
 *              student ID. It is used to check whether a specific student is
 *              present based on the student ID.
 ********************************************************************************/
uint16_t stud_id_compare(void *a, void *b);

/********************************************************************************
 * Name:       stud_to_dept_compare
 *
 * Input:      void *a - Pointer to a `department_t` structure, representing
 *                       the student's department data.
 *             void *b - Pointer to a `uint16_t` variable, representing the
 *                       department ID to be compared.
 *
 * Return:     success 0 Returns `0` Returns `0` if the department ID of the student matches
 *             fail 1    otherwise, returns `1`.
 *
 * Description: This function compares the department ID of a student with a given
 *              department ID. It is used to check whether a student belongs to
 *              a specific department.
 **********************************************************************************/
uint16_t stud_to_dept_compare(void *a, void *b);

#endif // STUDENT_H_INCLUDED
