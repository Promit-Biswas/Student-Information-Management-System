#ifndef HASH_H
#define HASH_H

#include <stdint.h>
#include "department.h"
#include "student.h"
#include "grade.h"

/* Macro Definitions */
#define DEPT_HASH_TABLE_SIZE 50
#define STUD_HASH_TABLE_SIZE 100
#define GRAD_HASH_TABLE_SIZE 100

/* Struct Definitions */
/* Hash table entry struct for departments */
typedef struct dept_hash_table_entry
{
    uint16_t dept_id;
    node_t *dept;
    struct dept_hash_table_entry *next;
} dept_hash_table_entry_t;

/* Hash table struct for departments */
typedef struct dept_hash_table
{
    dept_hash_table_entry_t **entries;
} dept_hash_table_t;

/* Hash table entry struct for students */
typedef struct student_hash_table_entry
{
    uint16_t student_id;
    node_t *student_node;
    struct student_hash_table_entry *next;
} student_hash_table_entry_t;

/* Hash table struct for students */
typedef struct student_hash_table
{
    student_hash_table_entry_t **entries;
} student_hash_table_t;

/* Hash table entry struct for grades */
typedef struct grade_hash_table_entry
{
    uint16_t student_id;
    node_t *grade;
    struct grade_hash_table_entry *next;
} grade_hash_table_entry_t;

/* Hash table struct for grades */
typedef struct grade_hash_table
{
    grade_hash_table_entry_t **entries;
} grade_hash_table_t;

/* Global Variables */
extern dept_hash_table_t *dept_hash_table;
extern student_hash_table_t *student_hash_table;
extern grade_hash_table_t *grade_hash_table;

/* Function Declarations */
dept_hash_table_t *create_dept_hash_table();
void free_dept_hash_table(dept_hash_table_t *table);
void insert_into_dept_hash_table(dept_hash_table_t *table, uint16_t dept_id, node_t *dept);
node_t *find_in_dept_hash_table(dept_hash_table_t *table, uint16_t dept_id);
uint16_t dept_hash_function(uint16_t dept_id);
void delete_from_dept_hash_table(dept_hash_table_t *table, uint16_t dept_id);
/*Student*/
student_hash_table_t *create_student_hash_table();
void free_student_hash_table(student_hash_table_t *table);
void insert_into_student_hash_table(student_hash_table_t *table, uint16_t student_id, node_t *student_node);
node_t *find_in_student_hash_table(student_hash_table_t *table, uint16_t student_id);
void delete_from_student_hash_table(student_hash_table_t *table, uint16_t student_id);
uint32_t student_hash_function(uint16_t student_id);
/*Grade*/
grade_hash_table_t *create_grade_hash_table();
void free_grade_hash_table(grade_hash_table_t *table);
void insert_into_grade_hash_table(grade_hash_table_t *table, uint16_t student_id, node_t *grade);
node_t *find_in_grade_hash_table(grade_hash_table_t *table, uint16_t student_id);
uint16_t grade_hash_function(uint16_t student_id);
void delete_from_grade_hash_table(grade_hash_table_t *table, uint16_t student_id);

#endif
