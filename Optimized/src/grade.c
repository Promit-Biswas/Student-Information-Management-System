#include "grade.h"
#include "input-handler.h"
#include "student.h"
#include "hash.h"

node_t *grade_root = NULL;

void add_grade()
{
    uint16_t id_to_store = INVALID_CHOICE;
    uint16_t english_to_store = 0, math_to_store = 0, history_to_store = 0;
    node_t *node_to_find = NULL;
    grade_t *grade = NULL;
    node_t *new_node = NULL;

    do
    {
        printf("Enter Student ID (i.e. BDCOM001): BDCOM");
    } while (get_value(&id_to_store) != TRUE);

    node_to_find = find_in_grade_hash_table(grade_hash_table, id_to_store);

    if (node_to_find != NULL)
    {
        puts("Grade for this student ID already exists.");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    node_to_find = find_in_student_hash_table(student_hash_table, id_to_store);

    if (node_to_find == NULL)
    {
        puts("No student found with this ID.");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    do
    {
        printf("Enter English grade: ");

        if (get_value(&english_to_store) == TRUE)
        {
            if (english_to_store > MAXIMUM_GARDE)
            {
                puts("Score can't be more than 100");
            }
        }
    } while (english_to_store > MAXIMUM_GARDE);

    do
    {
        printf("Enter Math grade: ");

        if (get_value(&math_to_store) == TRUE)
        {
            if (math_to_store > MAXIMUM_GARDE)
            {
                puts("Score can't be more than 100");
            }
        }
    } while (math_to_store > MAXIMUM_GARDE);

    do
    {
        printf("Enter History grade: ");

        if (get_value(&history_to_store) == TRUE)
        {
            if (history_to_store > MAXIMUM_GARDE)
            {
                puts("Score can't be more than 100");
            }
        }
    } while (history_to_store > MAXIMUM_GARDE);

    grade = (grade_t *)calloc(STRUCT_MULTIPLIER, sizeof(grade_t));

    if (grade == NULL)
    {
        safe_exit("Memory Allocation Failed");
    }

    grade->student_id = id_to_store;
    grade->english = (uint8_t)english_to_store;
    grade->math = (uint8_t)math_to_store;
    grade->history = (uint8_t)history_to_store;

    new_node = create_node(grade);
    insert_node_in_order(&grade_root, new_node);
    insert_into_grade_hash_table(grade_hash_table, grade->student_id, new_node);

    puts("Successfully added grade.");
    PRESS_KEY_TO_CONTINUE;

    return;
}

void delete_grade()
{
    uint16_t id_to_delete = 0;
    node_t *node_to_delete = NULL;

    do
    {
        printf("Enter Student ID (i.e. BDCOM001): BDCOM");
    } while (get_value(&id_to_delete) != TRUE);

    node_to_delete = find_in_grade_hash_table(grade_hash_table, id_to_delete);

    if (node_to_delete == NULL)
    {
        puts("Grade not found for this student ID.");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    delete_from_grade_hash_table(grade_hash_table, id_to_delete);
    delete_node(&grade_root, node_to_delete);

    puts("Grade deleted successfully.");
    PRESS_KEY_TO_CONTINUE;

    return;
}

void update_grade()
{
    uint16_t id_to_update = 0;
    uint8_t english_to_update = 0, math_to_update = 0, history_to_update = 0;
    uint16_t checker = 0;
    node_t *node_to_update = NULL;
    grade_t *grade = NULL;

    do
    {
        printf("Enter Student ID (i.e. BDCOM001): BDCOM");
    } while (get_value(&id_to_update) != TRUE);

    node_to_update = find_in_grade_hash_table(grade_hash_table, id_to_update);

    if (node_to_update == NULL)
    {
        puts("Grade not found for this student ID.");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    grade = (grade_t *)node_to_update->data_ptr;
    english_to_update = grade->english;
    math_to_update = grade->math;
    history_to_update = grade->history;

    printf("Update English grade (current: %u), (1 to continue, 0 to skip): ", english_to_update);
    get_value(&checker);

    if (checker)
    {
        checker = 0;

        do
        {
            printf("Give Updated English Grade : ");

            if (get_value((uint16_t *)&english_to_update) == TRUE)
            {
                if (english_to_update > MAXIMUM_GARDE)
                {
                    puts("Score can't be more than 100");
                }
            }
        } while (english_to_update > MAXIMUM_GARDE);
    }

    grade->english = english_to_update;

    printf("Update Math grade (current: %u), (1 to continue, 0 to skip): ", grade->math);
    get_value(&checker);

    if (checker)
    {
        checker = 0;

        do
        {
            printf("Give Updated Math Grade : ");

            if (get_value((uint16_t *)&math_to_update) == TRUE)
            {
                if (math_to_update > MAXIMUM_GARDE)
                {
                    puts("Score can't be more than 100");
                }
            }
        } while (math_to_update > MAXIMUM_GARDE);
    }

    grade->math = math_to_update;

    printf("Update History grade (current: %u), (1 to continue, 0 to skip): ", grade->history);
    get_value(&checker);

    if (checker)
    {
        checker = 0;

        do
        {
            printf("Give Updated History Grade : ");

            if (get_value((uint16_t *)&history_to_update) == TRUE)
            {
                if (history_to_update > MAXIMUM_GARDE)
                {
                    puts("Score can't be more than 100");
                }
            }
        } while (history_to_update > MAXIMUM_GARDE);
    }

    grade->history = history_to_update;

    printf("%u,%u,%u", grade->english, grade->math, grade->history);

    puts("Grade updated successfully.");
    PRESS_KEY_TO_CONTINUE;

    return;
}

uint16_t grade_student_compare(void *a, void *b)
{
    grade_t *grade_chk = (grade_t *)a;
    uint16_t *id_b = (uint16_t *)b;

    return (grade_chk->student_id == *id_b) ? 0 : 1;
}