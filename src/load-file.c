#include "load-file.h"
#include "department.h"
#include "student.h"
#include "grade.h"
#include "input-handler.h"

void load_from_dept(const char *filename)
{
    FILE *file = NULL;
    department_t *dept = NULL;

    file = fopen(filename, "rb");

    if (file == NULL)
    {
        puts("Error opening file. No existing Department data loaded.");

        return;
    }

    while (!feof(file))
    {
        dept = (department_t *)calloc(STRUCT_MULTIPLIER, sizeof(department_t));

        if (dept == NULL)
        {
            fclose(file);
            safe_exit("Memory Allocation Failed");
        }

        dept->name = NULL;
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
            free(dept);
            dept->name = NULL;
            dept = NULL;
            
            break;
        }

        if (dept->dept_id > last_dept_id)
        {
            last_dept_id = dept->dept_id;
        }

        uint16_t name_length = 0;

        if (fread(&name_length, sizeof(name_length), 1, file) != 1 ||
            fread(dept->name, sizeof(char), name_length, file) != name_length)
        {
            free(dept->name);
            free(dept);
            dept->name = NULL;
            dept = NULL;

            break;
        }

        dept->name[name_length - 1] = '\0';

        node_t *new_node = create_node(dept);
        insert_node(&department_root, new_node);
    }

    fclose(file);

    return;
}

void load_from_stud(const char *filename)
{
    FILE *file = NULL;
    student_t *stud = NULL;

    file = fopen(filename, "rb");

    if (file == NULL)
    {
        puts("Error opening file. No existing Student data loaded.");

        return;
    }

    while (!feof(file))
    {
        stud = (student_t *)calloc(STRUCT_MULTIPLIER, sizeof(student_t));

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

        uint16_t name_length = 0;
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
            free(stud);
            stud->student_name = NULL;
            stud = NULL;

            break;
        }

        stud->student_name[name_length - 1] = '\0';

        if (fread(&stud->student_gender, sizeof(stud->student_gender), 1, file) != 1 ||
            fread(&stud->department_id, sizeof(stud->department_id), 1, file) != 1)
        {
            free(stud->student_name);
            free(stud);
            stud->student_name = NULL;
            stud = NULL;

            break;
        }

        node_t *new_node = create_node(stud);
        insert_node_in_order(&student_root, new_node);
    }

    fclose(file);

    return;
}

void load_from_grad(const char *filename)
{
    FILE *file = NULL;
    grade_t *grade = NULL;

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

        node_t *new_node = create_node(grade);
        insert_node_in_order(&grade_root, new_node);
    }

    fclose(file);

    return;
}

void load_data()
{
    load_from_dept(DATA_FILE_DEPT);
    load_from_stud(DATA_FILE_STUD);
    load_from_grad(DATA_FILE_GRAD);

    return;
}
