#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

dept_hash_table_t *dept_hash_table = NULL;
grade_hash_table_t *grade_hash_table = NULL;
student_hash_table_t *student_hash_table = NULL;

/*Simple Hash Function */
uint16_t dept_hash_function(uint16_t dept_id)
{
    return dept_id % DEPT_HASH_TABLE_SIZE;
}

uint16_t grade_hash_function(uint16_t student_id)
{
    return student_id % GRAD_HASH_TABLE_SIZE;
}

uint32_t student_hash_function(uint16_t student_id)
{
    return student_id % STUD_HASH_TABLE_SIZE;
}

/*hash table for Department*/
dept_hash_table_t *create_dept_hash_table()
{
    dept_hash_table = (dept_hash_table_t *)calloc(STRUCT_MULTIPLIER, sizeof(dept_hash_table_t));

    if (!dept_hash_table)
    {
        safe_exit("Memory Allocation Failed for Hash Table");
    }

    dept_hash_table->entries = (dept_hash_table_entry_t **)calloc(DEPT_HASH_TABLE_SIZE, sizeof(dept_hash_table_entry_t *));

    if (!dept_hash_table->entries)
    {
        free(dept_hash_table);
        dept_hash_table = NULL;
        safe_exit("Memory Allocation Failed for Hash Table Entries");
    }

    return dept_hash_table;
}

void delete_from_dept_hash_table(dept_hash_table_t *table, uint16_t dept_id)
{
    uint32_t index = 0;
    dept_hash_table_entry_t *previous = NULL;
    dept_hash_table_entry_t *current = NULL;

    index = dept_hash_function(dept_id);
    current = table->entries[index];

    while (current != NULL)
    {
        /*Check if this is the entry to delete*/
        if (current->dept_id == dept_id)
        {
            /*If it's the first entry in the bucket (head of the list)*/
            if (previous == NULL)
            {
                /*Move the head to the next node*/
                table->entries[index] = current->next;
            }
            else
            {
                /*Otherwise, link the previous entry to the next one*/
                previous->next = current->next;
            }

            free(current);
            current = NULL;

            return;
        }

        previous = current;
        current = current->next;
    }

    return;
}

/* Free the memory allocated for the hash table*/
void free_dept_hash_table(dept_hash_table_t *table)
{
    uint16_t i = 0;
    dept_hash_table_entry_t *entry = NULL;
    dept_hash_table_entry_t *temp = NULL;

    for (i = 0; i < DEPT_HASH_TABLE_SIZE; i++)
    {
        entry = table->entries[i];

        while (entry)
        {
            temp = entry;
            entry = entry->next;
            free(temp);
            temp = NULL;
        }
    }

    free(table->entries);
    table->entries = NULL;
    free(table);
    table = NULL;

    return;
}

/*Insert a department into the hash table*/
void insert_into_dept_hash_table(dept_hash_table_t *table, uint16_t dept_id, node_t *dept)
{
    uint32_t index = 0;
    dept_hash_table_entry_t *new_entry = NULL;
    dept_hash_table_entry_t *current = NULL;

    index = dept_hash_function(dept_id);
    new_entry = (dept_hash_table_entry_t *)calloc(STRUCT_MULTIPLIER, sizeof(dept_hash_table_entry_t));

    if (!new_entry)
    {
        safe_exit("Memory Allocation Failed for Hash Table Entry");
    }

    new_entry->dept_id = dept_id;
    new_entry->dept = dept;
    new_entry->next = NULL;

    /* Insert into the hash table (handle collision with chaining) */
    if (table->entries[index] == NULL)
    {
        table->entries[index] = new_entry;
    }
    else
    {
        current = table->entries[index];

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = new_entry;
    }

    return;
}

/*Find a department by dept_id in the hash table*/
node_t *find_in_dept_hash_table(dept_hash_table_t *table, uint16_t dept_id)
{
    uint32_t index = 0;
    dept_hash_table_entry_t *entry = NULL;

    index = dept_hash_function(dept_id);
    entry = table->entries[index];

    while (entry)
    {
        if (entry->dept_id == dept_id)
        {
            return entry->dept;
        }
        entry = entry->next;
    }

    return NULL;
}

/*Grade Hash Table*/
grade_hash_table_t *create_grade_hash_table()
{
    grade_hash_table = (grade_hash_table_t *)calloc(STRUCT_MULTIPLIER, sizeof(grade_hash_table_t));

    if (!grade_hash_table)
    {
        safe_exit("Memory Allocation Failed for Grade Hash Table");
    }

    grade_hash_table->entries = (grade_hash_table_entry_t **)calloc(GRAD_HASH_TABLE_SIZE, sizeof(grade_hash_table_entry_t *));

    if (!grade_hash_table->entries)
    {
        free(grade_hash_table);
        grade_hash_table = NULL;
        safe_exit("Memory Allocation Failed for Grade Hash Table Entries");
    }

    return grade_hash_table;
}

/* Insert a grade into the hash table */
void insert_into_grade_hash_table(grade_hash_table_t *table, uint16_t student_id, node_t *grade)
{
    uint32_t index = 0;
    grade_hash_table_entry_t *new_entry = NULL;
    grade_hash_table_entry_t *current = NULL;

    index = grade_hash_function(student_id);
    new_entry = (grade_hash_table_entry_t *)calloc(STRUCT_MULTIPLIER, sizeof(grade_hash_table_entry_t));

    if (!new_entry)
    {
        safe_exit("Memory Allocation Failed for Grade Hash Table Entry");
    }

    new_entry->student_id = student_id;
    new_entry->grade = grade;
    new_entry->next = NULL;

    /* Insert into the grade hash table (handle collision with chaining) */
    if (table->entries[index] == NULL)
    {
        table->entries[index] = new_entry;
    }
    else
    {
        current = table->entries[index];

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = new_entry;
    }

    return;
}

/* Find a grade by student_id in the grade hash table */
node_t *find_in_grade_hash_table(grade_hash_table_t *table, uint16_t student_id)
{
    uint16_t index = 0;
    grade_hash_table_entry_t *entry = NULL;

    index = grade_hash_function(student_id);
    entry = table->entries[index];

    while (entry)
    {
        if (entry->student_id == student_id)
        {
            return entry->grade;
        }

        entry = entry->next;
    }

    return NULL;
}

/* Delete a grade from the hash table */
void delete_from_grade_hash_table(grade_hash_table_t *table, uint16_t student_id)
{
    uint32_t index = 0;
    grade_hash_table_entry_t *previous = NULL;
    grade_hash_table_entry_t *current = NULL;

    index = grade_hash_function(student_id);
    current = table->entries[index];

    while (current != NULL)
    {
        /*Check if this is the entry to delete*/
        if (current->student_id == student_id)
        {
            /*If it's the first entry in the bucket (head of the list)*/
            if (previous == NULL)
            {
                /*Move the head to the next node*/
                table->entries[index] = current->next;
            }
            else
            {
                /*Otherwise, link the previous entry to the next one*/
                previous->next = current->next;
            }

            free(current);
            current = NULL;

            return;
        }

        previous = current;
        current = current->next;
    }

    return;
}

/* Free the memory allocated for the grade hash table */
void free_grade_hash_table(grade_hash_table_t *table)
{
    uint16_t i = 0;
    grade_hash_table_entry_t *entry = NULL;
    grade_hash_table_entry_t *temp = NULL;

    for (i = 0; i < GRAD_HASH_TABLE_SIZE; i++)
    {
        entry = table->entries[i];

        while (entry)
        {
            temp = entry;
            entry = entry->next;
            free(temp);
            temp = NULL;
        }
    }

    free(table->entries);
    table->entries = NULL;
    free(table);
    table = NULL;

    return;
}

/* hash table for students */
student_hash_table_t *create_student_hash_table()
{
    student_hash_table = (student_hash_table_t *)calloc(STRUCT_MULTIPLIER, sizeof(student_hash_table_t));

    if (!student_hash_table)
    {
        safe_exit("Failed to allocate memory for student hash table");
    }

    student_hash_table->entries = (student_hash_table_entry_t **)calloc(STUD_HASH_TABLE_SIZE, sizeof(student_hash_table_entry_t *));

    if (!student_hash_table->entries)
    {
        free(student_hash_table);
        student_hash_table = NULL;
        safe_exit("Failed to allocate memory for student hash table entries");
    }

    return student_hash_table;
}

/* Insert a student into the hash table */
void insert_into_student_hash_table(student_hash_table_t *table, uint16_t student_id, node_t *student_node)
{
    uint32_t index = 0;
    student_hash_table_entry_t *new_entry = NULL;
    student_hash_table_entry_t *current = NULL;

    index = student_hash_function(student_id);
    new_entry = (student_hash_table_entry_t *)calloc(STRUCT_MULTIPLIER, sizeof(student_hash_table_entry_t));

    if (!new_entry)
    {
        safe_exit("Memory allocation failed for student hash table entry");
    }

    new_entry->student_id = student_id;
    new_entry->student_node = student_node;

    /* Insert into the student hash table (handle collision with chaining) */
    if (table->entries[index] == NULL)
    {
        table->entries[index] = new_entry;
    }
    else
    {
        current = table->entries[index];

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = new_entry;
    }

    return;
}

/* Find a student by student_id in the hash table */
node_t *find_in_student_hash_table(student_hash_table_t *table, uint16_t student_id)
{
    uint32_t index = 0;
    student_hash_table_entry_t *entry = NULL;

    index = student_hash_function(student_id);
    entry = table->entries[index];

    while (entry)
    {
        if (entry->student_id == student_id)
        {
            return entry->student_node;
        }

        entry = entry->next;
    }

    return NULL;
}

/* Delete a student from the hash table */
void delete_from_student_hash_table(student_hash_table_t *table, uint16_t student_id)
{
    uint32_t index = 0;
    student_hash_table_entry_t *current = NULL;
    student_hash_table_entry_t *previous = NULL;

    index = student_hash_function(student_id);
    current = table->entries[index];

    while (current != NULL)
    {
        if (current->student_id == student_id)
        {
            if (previous == NULL)
            {
                table->entries[index] = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            free(current);
            current = NULL;

            return;
        }

        previous = current;
        current = current->next;
    }

    return;
}

/* Free the memory allocated for the student hash table */
void free_student_hash_table(student_hash_table_t *table)
{
    uint32_t i = 0;
    student_hash_table_entry_t *entry = NULL;
    student_hash_table_entry_t *temp = NULL;

    for (i = 0; i < STUD_HASH_TABLE_SIZE; i++)
    {
        entry = table->entries[i];

        while (entry)
        {
            temp = entry;
            entry = entry->next;
            free(temp);
            temp = NULL;
        }
    }

    free(table->entries);
    table->entries = NULL;
    free(table);
    table = NULL;

    return;
}