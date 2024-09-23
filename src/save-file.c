#include <errno.h>
#include "save-file.h"
#include "department.h"
#include "student.h"
#include "grade.h"
#include "input-handler.h"

void ensure_directory_exists(const char *dir_name)
{
    struct stat st = {0};

    if (stat(dir_name, &st) == -1)
    {
        uint32_t result = 0;

        /*Read/write/execute for owner only*/
        result = mkdir(dir_name, 0700);

        if (result != 0)
        {
            fprintf(stderr, "Error creating directory %s: %s\n", dir_name, strerror(errno));

            return;
        }

        printf("Directory %s created successfully.\n", dir_name);
    }
}

void save_file_of_dept(const char *filename)
{
    FILE *file = NULL;
    node_t *current = NULL;
    department_t *dept = NULL;

    file = fopen(filename, "wb");

    if (file == NULL)
    {
        safe_exit("Failed to open Deptarments file to write.");

        return;
    }

    current = department_root;

    while (current != NULL)
    {
        dept = (department_t *)current->data_ptr;
        fwrite(&dept->dept_id, sizeof(dept->dept_id), 1, file);
        uint16_t name_length = strlen(dept->name) + 1;
        fwrite(&name_length, sizeof(name_length), 1, file);
        fwrite(dept->name, sizeof(char), name_length, file);
        current = current->next;
    }

    fclose(file);

    return;
}

void save_file_of_stud(const char *filename)
{
    FILE *file = NULL;
    node_t *current = NULL;
    student_t *stud = NULL;

    file = fopen(filename, "wb");

    if (file == NULL)
    {
        safe_exit("Failed to open Student file to write.");

        return;
    }

    current = student_root;

    while (current != NULL)
    {
        stud = (student_t *)current->data_ptr;
        fwrite(&stud->student_id, sizeof(stud->student_id), 1, file);
        uint16_t name_length = strlen(stud->student_name) + 1;
        fwrite(&name_length, sizeof(name_length), 1, file);
        fwrite(stud->student_name, sizeof(char), name_length, file);
        fwrite(&stud->student_gender, sizeof(stud->student_gender), 1, file);
        fwrite(&stud->department_id, sizeof(stud->department_id), 1, file);
        current = current->next;
    }

    fclose(file);

    return;
}

void save_file_of_grad(const char *filename)
{
    FILE *file = NULL;
    node_t *current = NULL;
    grade_t *grade = NULL;

    file = fopen(filename, "wb");

    if (file == NULL)
    {
        safe_exit("Failed to open Grades file.");

        return;
    }

    current = grade_root;

    while (current != NULL)
    {
        grade = (grade_t *)current->data_ptr;
        fwrite(&grade->student_id, sizeof(grade->student_id), 1, file);
        fwrite(&grade->english, sizeof(grade->english), 1, file);
        fwrite(&grade->math, sizeof(grade->math), 1, file);
        fwrite(&grade->history, sizeof(grade->history), 1, file);
        current = current->next;
    }

    fclose(file);

    return;
}

void save_all()
{
    ensure_directory_exists(DATA_DIR);
    save_file_of_dept(DATA_FILE_DEPT);
    save_file_of_stud(DATA_FILE_STUD);
    save_file_of_grad(DATA_FILE_GRAD);
    puts("All data saved successfully!.");
    PRESS_KEY_TO_CONTINUE;

    return;
}
