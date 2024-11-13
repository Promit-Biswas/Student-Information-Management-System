#include <stdint.h>
#include "department.h"
#include "input-handler.h"
#include "hash.h"
#include "student.h"

node_t *department_root = NULL;
uint16_t last_dept_id = 0;

void add_department()
{
    char name_to_store[BUFFER_SIZE] = {0};
    department_t *dept = NULL;
    node_t *new_node = NULL;

    do
    {
        printf("Department Name : ");
    } while (get_name(name_to_store) != TRUE);

    dept = (department_t *)calloc(STRUCT_MULTIPLIER, sizeof(department_t));

    if (dept == NULL)
    {
        safe_exit("Memory Allocation Failed");
    }

    dept->name = (char *)calloc(BUFFER_SIZE, sizeof(char));

    if (dept->name == NULL)
    {
        safe_exit("Memory Allocation Failed");
    }

    strncpy(dept->name, name_to_store, BUFFER_SIZE);

    if (search_node(department_root, dept->name, dept_name_compare) != NULL)
    {
        puts("Duplicate Department Found!");
        free(dept->name);
        dept->name = NULL;
        free(dept);
        dept = NULL;
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    dept->dept_id = ++last_dept_id;
    new_node = create_node(dept);

    insert_node(&department_root, new_node);
    insert_into_dept_hash_table(dept_hash_table, dept->dept_id, new_node);
    printf("Department %s successfully with ID: %hu\n", dept->name, dept->dept_id);
    PRESS_KEY_TO_CONTINUE;

    return;
}

void delete_department()
{
    uint16_t dept_id = 0;
    node_t *node_to_delete = NULL;

    do
    {
        printf("Please Enter a Department ID: ");
    } while (get_value(&dept_id) != TRUE);

    node_to_delete = find_in_dept_hash_table(dept_hash_table, dept_id);

    if (node_to_delete == NULL)
    {
        puts("Department not found.");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    delete_node(&department_root, node_to_delete);
    delete_from_dept_hash_table(dept_hash_table, dept_id);
    set_default_dept_to_student(dept_id);
    puts("Department deleted successfully.");
    PRESS_KEY_TO_CONTINUE;

    return;
}

void update_department()
{
    uint16_t dept_id = 0, checker = 0;
    char buffer[BUFFER_SIZE] = {0};
    node_t *node_to_update = NULL;
    department_t *dept = NULL;

    do
    {
        printf("Please enter an Dept ID: ");
    } while (get_value(&dept_id) != TRUE);

    node_to_update = find_in_dept_hash_table(dept_hash_table, dept_id);

    if (node_to_update == NULL)
    {
        puts("Department not found.");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    do
    {
        printf("Do you really want to update %s\? (1 to continue 0 to exit) : ", ((department_t *)(node_to_update->data_ptr))->name);
    } while (get_value(&checker) != TRUE);

    if (!checker || checker > 1)
    {
        puts("Department haven't updated.");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    do
    {
        printf("Updated Department Name : ");
    } while (get_name(buffer) != TRUE);

    if (search_node(department_root, buffer, dept_name_compare) != NULL)
    {
        puts("Department name already exists.");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    dept = (department_t *)node_to_update->data_ptr;
    free(dept->name);
    dept->name = NULL;
    dept->name = (char *)calloc(BUFFER_SIZE, sizeof(char));

    if (dept->name == NULL)
    {
        safe_exit("Memory Allocation Failed.");
    }

    strncpy(dept->name, buffer, BUFFER_SIZE);
    printf("Department updated successfully.\n");
    PRESS_KEY_TO_CONTINUE;

    return;
}

uint16_t dept_name_compare(void *a, void *b)
{
    department_t *dept_chk = (department_t *)a;
    char *name_chk = (char *)b;

    return strncmp(name_chk, dept_chk->name, BUFFER_SIZE);
}
