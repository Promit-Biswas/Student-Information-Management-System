#include "student.h"
#include "hash.h"

node_t *student_root = NULL;

void add_student()
{
    uint16_t id_to_store = INVALID_CHOICE;
    char name_to_store[BUFFER_SIZE] = {0};
    uint16_t gender_to_store = INVALID_CHOICE;
    uint16_t dept_to_store = 0;
    node_t *node_to_find = NULL;
    student_t *stud = NULL;
    node_t *new_node = NULL;

    do
    {
        printf("Give Student ID (i.e BDCOM001) : BDCOM");
    } while (get_value(&id_to_store) != TRUE);

    node_to_find = find_in_student_hash_table(student_hash_table, id_to_store);

    if (node_to_find != NULL)
    {
        puts("SIMILAR ID FOUND.");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    else if (id_to_store > 999)
    {
        puts("VALID UPTO BDCOM999");
        PRESS_KEY_TO_CONTINUE

        return;
    }

    do
    {
        printf("Give Student Name: ");
    } while (get_name(name_to_store) != TRUE);

    do
    {
        printf("Give Gender (0 for Male and 1 for Female): ");
    } while (!get_value(&gender_to_store) || (gender_to_store != 0 && gender_to_store != 1));

    do
    {
        printf("Give a Dept ID : ");
    } while (get_value(&dept_to_store) != TRUE);

    if (find_in_dept_hash_table(dept_hash_table, dept_to_store) == NULL)
    {
        puts("NO SUCH DEPT FOUND. Try again!");
        PRESS_KEY_TO_CONTINUE;

        return;
    };

    stud = (student_t *)calloc(STRUCT_MULTIPLIER, sizeof(student_t));

    if (stud == NULL)
    {
        safe_exit("Memory Allocation Failed");
    }

    stud->student_name = (char *)calloc(BUFFER_SIZE, sizeof(char));

    if (stud->student_name == NULL)
    {
        free(stud);
        stud = NULL;
        safe_exit("Memory Allocation Failed");
    }

    stud->student_id = id_to_store;
    strncpy(stud->student_name, name_to_store, BUFFER_SIZE);
    stud->student_gender = gender_to_store;
    stud->department_id = dept_to_store;

    new_node = create_node(stud);
    insert_into_student_hash_table(student_hash_table, stud->student_id, new_node);
    insert_node_in_order(&student_root, new_node);
    puts("Successfully Added a Student");
    PRESS_KEY_TO_CONTINUE;

    return;
}

void set_default_dept_to_student(uint16_t dept_id)
{
    node_t *current = NULL;
    student_t *stud = NULL;

    current = student_root;

    if (current == NULL)
    {
        return;
    }

    while (current != NULL)
    {
        stud = (student_t *)current->data_ptr;

        if (stud->department_id == dept_id)
        {
            stud->department_id = DEFAULT_DEPT_ID;
        }

        current = current->next;
    }

    return;
}

void delete_student()
{
    uint16_t stu_id = 0;
    node_t *node_to_delete_from_student = NULL;
    node_t *node_to_delete_from_grade = NULL;

    do
    {
        printf("Enter Student ID (i.e. BDCOM001): BDCOM");
    } while (get_value(&stu_id) != TRUE);

    node_to_delete_from_student = find_in_student_hash_table(student_hash_table, stu_id);
    node_to_delete_from_grade = find_in_grade_hash_table(grade_hash_table, stu_id);

    if (node_to_delete_from_student == NULL)
    {
        puts("STUDENT NOT FOUND. Try Again");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    delete_node(&student_root, node_to_delete_from_student);
    delete_node(&grade_root, node_to_delete_from_grade);
    delete_from_student_hash_table(student_hash_table, stu_id);
    delete_from_grade_hash_table(grade_hash_table, stu_id);
    puts("Student Info. deleted successfully.");
    PRESS_KEY_TO_CONTINUE;

    return;
}

void update_student()
{
    uint16_t stu_id = 0, checker = 0, gender_to_update = 0, dept_to_update = 0;
    char buffer[BUFFER_SIZE] = {0};
    student_t *data = NULL;

    do
    {
        printf("Please enter an Student ID (i.e BDCOM001): BDCOM");
    } while (get_value(&stu_id) != TRUE);

    node_t *node_to_update = NULL;
    node_to_update = find_in_student_hash_table(student_hash_table, stu_id);

    if (node_to_update == NULL)
    {
        puts("STUDENT NOT FOUND. Try Again");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    data = ((student_t *)(node_to_update->data_ptr));
    gender_to_update = data->student_gender;
    dept_to_update = data->department_id;
    strncpy(buffer, data->student_name, BUFFER_SIZE - 1);

    printf("Do you Really want to update the name : %s? (1 to continue 0 to skip) : ", data->student_name);
    get_value(&checker);

    if (checker)
    {
        checker = 0;
        printf("Give another Name: ");
        memset(buffer, 0, sizeof(buffer));

        get_name(buffer);
    }

    printf("Do you Really want to update Gender %s? (1 to continue 0 to skip) : ", data->student_gender ? "FEMALE" : "MALE");
    get_value(&checker);

    if (checker)
    {
        checker = 0;
        printf("Give Edited Gender (0 for male , 1 for female): ");
        get_value(&gender_to_update);
    }

    printf("Do you Really want to update Department ID : %hu? (1 to continue 0 to skip) : ", data->department_id);
    get_value(&checker);

    if (checker)
    {
        checker = 0;
        printf("Give Edited Department ID : ");
        get_value(&dept_to_update);

        if (find_in_dept_hash_table(dept_hash_table, dept_to_update) == NULL)
        {
            puts("NO SUCH DEPT FOUND. Try again!");
            PRESS_KEY_TO_CONTINUE;

            return;
        };
    }

    data->student_gender = (uint8_t)gender_to_update;
    data->department_id = dept_to_update;
    strncpy(data->student_name, buffer, BUFFER_SIZE);
    puts("Edited Successful");
    PRESS_KEY_TO_CONTINUE;

    return;
}

uint16_t stud_to_dept_compare(void *a, void *b)
{
    uint16_t *id_b = (uint16_t *)b;
    department_t *stud_chk = (department_t *)a;

    return (stud_chk->dept_id == *id_b) ? 0 : 1;
}
