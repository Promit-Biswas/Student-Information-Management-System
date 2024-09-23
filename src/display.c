#include "display.h"
#include "department.h"
#include "student.h"
#include "grade.h"
#include "input-handler.h"

void display_department()
{
    /* linker_array[last_dept_id + 1][0] for Male & linker_array[last_dept_id + 1][1] for Female */
    uint16_t linker_array[last_dept_id + 1][2];
    uint16_t counter = 0;
    node_t *current = NULL;

    for (counter = 0; counter <= last_dept_id; counter++)
    {
        linker_array[counter][0] = 0;
        linker_array[counter][1] = 0;
    }

    current = student_root;

    while (current != NULL)
    {
        student_t *stud = NULL;

        stud = (student_t *)current->data_ptr;
        linker_array[stud->department_id][stud->student_gender]++;
        current = current->next;
    }

    current = department_root;
    if (current == NULL)
    {
        puts("No Departments to display.");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    CLEAR_SCREEN;
    puts("+----------------+--------------------+----------+----------+");
    puts("|                   Display All Departments                 |");
    puts("+----------------+--------------------+----------+----------+");
    puts("|Department Id   |Department Name     |Male      |Female    |");
    puts("+----------------+--------------------+----------+----------+");

    while (current != NULL)
    {
        department_t *dept = NULL;

        dept = (department_t *)current->data_ptr;
        uint16_t dept_id = dept->dept_id;

        printf("|%-16hu|%-20s|%-10hu|%-10hu|\n",
               dept_id,
               dept->name,
               linker_array[dept_id][0],
               linker_array[dept_id][1]);
        puts("+----------------+--------------------+----------+----------+");

        current = current->next;
    }

    PRESS_KEY_TO_CONTINUE;

    return;
}

void display_student()
{
    node_t *current = NULL;
    node_t *grade_node = NULL;
    node_t *dept_node = NULL;
    node_t *temp = NULL;
    student_t *stud = NULL;
    department_t *dept = NULL;
    grade_t *grade = NULL;
    char *english = NULL;
    char *math = NULL;
    char *history = NULL;

    current = student_root;
    grade_node = grade_root;
    dept_node = department_root;

    if (current == NULL)
    {
        grade_node = NULL;
        dept_node = NULL;

        puts("No students to display.");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    CLEAR_SCREEN;
    puts("+------------+----------------------+--------+----------------------+--------+--------+--------+");
    puts("|                                     Display All Students                                     |");
    puts("+------------+----------------------+--------+----------------------+--------+--------+--------+");
    puts("| Student ID | Student Name         | Gender | Department Name      | English| Math   | History|");
    puts("+------------+----------------------+--------+----------------------+--------+--------+--------+");

    while (current != NULL)
    {
        temp = grade_node;
        stud = (student_t *)current->data_ptr;
        dept_node = search_node(department_root, &stud->department_id, stud_to_dept_compare);
        dept = dept_node ? (department_t *)dept_node->data_ptr : NULL;
        grade_node = search_node(grade_node, &stud->student_id, grade_student_compare);
        grade = grade_node ? (grade_t *)grade_node->data_ptr : NULL;
        
        if(grade != NULL)
        {
        	english = int_to_str(grade->english);
        	math = int_to_str(grade->math);
        	history = int_to_str(grade->history);
		}
        
        printf("| BDCOM%03hu   | %-20s | %-6s | %-20s | %-6s | %-6s | %-6s |\n",
               stud->student_id,
               stud->student_name,
               stud->student_gender == 0 ? "Male" : "Female",
               dept ? dept->name : "N/A",
               grade ? english : "N/A",
               grade ? math : "N/A",
               grade ? history : "N/A");
        puts("+------------+----------------------+--------+----------------------+--------+--------+--------+");

        if (grade_node == NULL)
        {
            grade_node = temp;
        }
        else
        {
        	free(english);
	        free(math);
	        free(history);
	        english = NULL;
	        math = NULL;
	        history = NULL;
		}

        current = current->next;
    }

    PRESS_KEY_TO_CONTINUE;

    return;
}

void display_grade()
{
    node_t *current = NULL;
    node_t *temp = NULL;
    node_t *stud_node = NULL;
    grade_t *grade = NULL;
    student_t *stud = NULL;

    current = grade_root;
    stud_node = student_root;

    if (current == NULL)
    {
        stud_node = NULL;

        puts("No grades to display.");
        PRESS_KEY_TO_CONTINUE;

        return;
    }

    CLEAR_SCREEN;
    puts("+----------------------+--------+--------+--------+");
    puts("|               Display All Grades                |");
    puts("+----------------------+--------+--------+--------+");
    puts("| Student Name         | English| Math   | History|");
    puts("+----------------------+--------+--------+--------+");

    while (current != NULL)
    {
        temp = stud_node;
        grade = (grade_t *)current->data_ptr;
        stud_node = search_node(stud_node, &grade->student_id, stud_id_compare);
        stud = stud_node ? (student_t *)stud_node->data_ptr : NULL;

        printf("| %-20s | %-6hu | %-6hu | %-6hu |\n",
               stud->student_name,
               grade->english,
               grade->math,
               grade->history);
        puts("+----------------------+--------+--------+--------+");

        if (stud_node == NULL)
        {
            stud_node = temp;
        }

        current = current->next;
    }

    PRESS_KEY_TO_CONTINUE;

    return;
}
