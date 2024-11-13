#include "linkedlist.h"
#include "student.h"
#include "hash.h"

node_t *create_node(void *data)
{
    node_t *new_node = NULL;

    new_node = (node_t *)calloc(STRUCT_MULTIPLIER, sizeof(node_t));

    if (new_node == NULL)
    {
        safe_exit("Failed to allocate memory for new node");
    }

    new_node->data_ptr = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

void insert_node(node_t **root, node_t *new_node)
{
    node_t *temp = NULL;

    if (*root == NULL)
    {
        *root = new_node;
    }
    else
    {
        temp = *root;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = new_node;
        new_node->prev = temp;
    }

    return;
}

void insert_node_in_order(node_t **root, node_t *new_node)
{
    node_t *current = NULL;
    student_t *new_stud = NULL;
    student_t *current_stud = NULL;

    if (*root == NULL)
    {
        *root = new_node;

        return;
    }

    current = *root;
    new_stud = (student_t *)new_node->data_ptr;

    while (current != NULL)
    {
        current_stud = (student_t *)current->data_ptr;

        if (new_stud->student_id < current_stud->student_id)
        {
            new_node->next = current;
            new_node->prev = current->prev;

            if (current->prev != NULL)
            {
                current->prev->next = new_node;
            }
            else
            {
                *root = new_node;
            }
            current->prev = new_node;

            return;
        }

        if (current->next == NULL)
        {
            current->next = new_node;
            new_node->prev = current;

            return;
        }

        current = current->next;
    }

    return;
}

void delete_node(node_t **root, node_t *node_to_delete)
{
    if (*root == NULL || node_to_delete == NULL)
    {
        return;
    }

    if (*root == node_to_delete)
    {
        *root = node_to_delete->next;
    }

    if (node_to_delete->prev != NULL)
    {
        node_to_delete->prev->next = node_to_delete->next;
        node_to_delete->prev = NULL;
    }

    if (node_to_delete->next != NULL)
    {
        node_to_delete->next->prev = node_to_delete->prev;
        node_to_delete->next = NULL;
    }

    free(node_to_delete->data_ptr);
    node_to_delete->data_ptr = NULL;
    free(node_to_delete);
    node_to_delete = NULL;

    return;
}

node_t *search_node(node_t *root, void *key, uint16_t (*cmp)(void *, void *))
{
    node_t *current = NULL;

    current = root;

    while (current != NULL)
    {
        if (cmp(current->data_ptr, key) == 0)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void free_everything()
{
    node_t *current = NULL;
    node_t *next = NULL;
    department_t *department = NULL;
    student_t *student = NULL;
    grade_t *grade = NULL;

    current = department_root;

    while (current != NULL)
    {
        next = current->next;
        department = (department_t *)current->data_ptr;

        if (department != NULL)
        {
            free(department->name);
            department->name = NULL;
            free(department);
            department = NULL;
        }

        free(current);
        current = next;
    }

    department_root = NULL;
    current = student_root;

    while (current != NULL)
    {
        next = current->next;
        student = (student_t *)current->data_ptr;

        if (student != NULL)
        {
            free(student->student_name);
            student->student_name = NULL;
            free(student);
            student = NULL;
        }

        free(current);
        current = next;
    }

    student_root = NULL;
    current = grade_root;

    while (current != NULL)
    {
        next = current->next;
        grade = (grade_t *)current->data_ptr;
        free(grade);
        grade = NULL;
        free(current);
        current = next;
    }

    grade_root = NULL;
    free_dept_hash_table(dept_hash_table);
    free_grade_hash_table(grade_hash_table);
    free_student_hash_table(student_hash_table);
}