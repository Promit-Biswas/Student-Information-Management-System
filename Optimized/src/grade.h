#ifndef GRADE_H_INCLUDED
#define GRADE_H_INCLUDED

#include "linkedlist.h"

#define DATA_FILE_GRAD "databases/grades.dat"
#define MAXIMUM_GARDE 100

typedef struct grade
{
    uint16_t student_id;
    uint8_t english;
    uint8_t math;
    uint8_t history;
} grade_t;

extern node_t *grade_root;

void add_grade();
void delete_grade();
void update_grade();

/********************************************************************************
 * Name:       grade_student_compare
 *
 * Input:      void *a - Pointer to a `grade_t` structure, representing the
 *                       grade data associated with a student.
 *             void *b - Pointer to a `uint16_t` variable, representing the
 *                       student ID to be compared.
 *
 * Return:     success 0 Returns `0` if the student ID in the grade structure
 *             fail    1 otherwise, returns `1`.
 *
 * Description: This function compares the student ID within a `grade_t` structure
 *              with a given student ID.
 ********************************************************************************/
uint16_t grade_student_compare(void *a, void *b);

#endif // GRADE_H_INCLUDED
