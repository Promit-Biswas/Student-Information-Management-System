#include "load-file.h"
#include "department.h"
#include "student.h"
#include "grade.h"
#include "input-handler.h"
#include "hash.h"

void load_from_dept(const char *filename)
{
    FILE *file = NULL;
    department_t *dept = NULL;
    node_t *new_node = NULL;
    uint16_t name_length = 0;

    file = fopen(filename, "rb");

    if (file == NULL)
    {
        puts("Error opening file. No existing Department data loaded.");

        return;
    }

    while (!feof(file))
    {
        dept = (department_t *)calloc(STRUCT_MULTIPLIER, sizeof(department_t));
        name_length = 0;

        if (dept == NULL)
        {
            fclose(file);
            safe_exit("Memory Allocation Failed");
        }

        dept->name = (char *)calloc(BUFFER_SIZE, sizeof(char));

        if (dept->name == NULL)
        {
            fclose(file);
            free(dept);
            dept = NULL;
            safe_exit("Memory Allocation Failed");
        }

        if (fread(&dept->dept_id, sizeof(dept->dept_id), 1, file) != 1)
        {
            free(dept->name);
            dept->name = NULL;
            free(dept);
            dept = NULL;

            break;
        }

        if (dept->dept_id > last_dept_id)
        {
            last_dept_id = dept->dept_id;
        }

        if (fread(&name_length, sizeof(name_length), 1, file) != 1 ||
            fread(dept->name, sizeof(char), name_length, file) != name_length)
        {
            free(dept->name);
            dept->name = NULL;
            free(dept);
            dept = NULL;

            break;
        }

        dept->name[name_length - 1] = '\0';

        new_node = create_node(dept);
        insert_into_dept_hash_table(dept_hash_table, dept->dept_id, new_node);
        insert_node(&department_root, new_node);
    }

    fclose(file);

    return;
}

void load_from_stud(const char *filename)
{
    FILE *file = NULL;
    student_t *stud = NULL;
    node_t *new_node = NULL;
    uint16_t name_length = 0;

    file = fopen(filename, "rb");

    if (file == NULL)
    {
        puts("Error opening file. No existing Student data loaded.");

        return;
    }

    while (!feof(file))
    {
        stud = (student_t *)calloc(STRUCT_MULTIPLIER, sizeof(student_t));
        name_length = 0;

        if (stud == NULL)
        {
            fclose(file);
            safe_exit("Memory Allocation Failed");
        }

        if (fread(&stud->student_id, sizeof(stud->student_id), 1, file) != 1)
        {
            free(stud);
            stud = NULL;

            break;
        }

        if (fread(&name_length, sizeof(name_length), 1, file) != 1)
        {
            free(stud);
            stud = NULL;

            break;
        }

        stud->student_name = NULL;
        stud->student_name = (char *)calloc(name_length, sizeof(char));

        if (stud->student_name == NULL)
        {
            free(stud);
            fclose(file);
            stud = NULL;
            safe_exit("Memory Allocation Failed");
        }

        if (fread(stud->student_name, sizeof(char), name_length, file) != name_length)
        {
            free(stud->student_name);
            stud->student_name = NULL;
            free(stud);
            stud = NULL;

            break;
        }

        stud->student_name[name_length - 1] = '\0';

        if (fread(&stud->student_gender, sizeof(stud->student_gender), 1, file) != 1 ||
            fread(&stud->department_id, sizeof(stud->department_id), 1, file) != 1)
        {
            free(stud->student_name);
            stud->student_name = NULL;
            free(stud);
            stud = NULL;

            break;
        }

        new_node = create_node(stud);
        insert_node_in_order(&student_root, new_node);
        insert_into_student_hash_table(student_hash_table, stud->student_id, new_node);
    }

    fclose(file);

    return;
}

void load_from_grad(const char *filename)
{
    FILE *file = NULL;
    grade_t *grade = NULL;
    node_t *new_node = NULL;

    file = fopen(filename, "rb");

    if (file == NULL)
    {
        puts("Error opening file. No existing Grade data loaded.");

        return;
    }

    while (!feof(file))
    {
        grade = (grade_t *)calloc(STRUCT_MULTIPLIER, sizeof(grade_t));

        if (grade == NULL)
        {
            fclose(file);
            safe_exit("Memory Allocation Failed");
        }

        if (fread(&grade->student_id, sizeof(grade->student_id), 1, file) != 1)
        {
            free(grade);
            grade = NULL;

            break;
        }

        if (fread(&grade->english, sizeof(grade->english), 1, file) != 1 ||
            fread(&grade->math, sizeof(grade->math), 1, file) != 1 ||
            fread(&grade->history, sizeof(grade->history), 1, file) != 1)
        {
            free(grade);
            grade = NULL;

            break;
        }

        new_node = create_node(grade);
        insert_into_grade_hash_table(grade_hash_table, grade->student_id, new_node);
        insert_node_in_order(&grade_root, new_node);
    }

    fclose(file);

    return;
}

void load_data()
{
    dept_hash_table = create_dept_hash_table(dept_hash_table);
    grade_hash_table = create_grade_hash_table(grade_hash_table);
    student_hash_table = create_student_hash_table(student_hash_table);
    load_from_dept(DATA_FILE_DEPT);
    load_from_stud(DATA_FILE_STUD);
    load_from_grad(DATA_FILE_GRAD);

    return;
}
