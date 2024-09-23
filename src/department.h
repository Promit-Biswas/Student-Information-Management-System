#ifndef DEPARTMENT_H_INCLUDED
#define DEPARTMENT_H_INCLUDED

#include "linkedlist.h"

#define DATA_FILE_DEPT "databases/departments.dat"

typedef struct department
{
    uint16_t dept_id;
    char *name;
} department_t;

extern node_t *department_root;
extern uint16_t last_dept_id;

void add_department();
void delete_department();
void update_department();

/********************************************************************************
 * Name:       dept_id_compare
 *
 * Input:      void *a - Pointer to a `department_t` structure,
 *             void *b - Pointer to a `uint16_t` variable, representing the
 *                       department ID to be compared.
 *
 * Return:     success  `0` if the department ID matches the provided
 *             fail      1  otherwise, returns `1`.
 *
 * Description: This function compares the department ID of a department with a given
 *              department ID. It is used to check whether a specific department
 *              matches a given ID.
 ********************************************************************************/
uint16_t dept_id_compare(void *a, void *b);

/********************************************************************************
 * Name:       dept_name_compare
 *
 * Input:      void *a - Pointer to a `department_t` structure,
 *             void *b - Pointer to a `char` array, representing the department
 *                       name to be compared.
 *
 * Return:     success  `0` if the department matches matches the provided
 *             fail      1  otherwise, returns `1`.
 *
 * Description: This function compares the name of a department with a given name.
 *              It uses `strncmp` to compare the two strings up to `BUFFER_SIZE`
 *              characters. The function is useful for determining whether a
 *              department has a specific name.
 ********************************************************************************/
uint16_t dept_name_compare(void *a, void *b);

#endif // DEPARTMENT_H_INCLUDED
