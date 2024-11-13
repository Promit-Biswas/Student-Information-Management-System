#include "menu.h"
#include "input-handler.h"
#include "linkedlist.h"
#include "load-file.h"
#include "save-file.h"
#include "department.h"
#include "student.h"
#include "grade.h"
#include "display.h"

void print_main_menu()
{
    CLEAR_SCREEN;
    puts("+-------------------------------+");
    puts("|           Main Menu           |");
    puts("+-------------------------------+");
    puts("| 1. Department Management      |");
    puts("| 2. Student Management         |");
    puts("| 3. Grade Management           |");
    puts("| 4. Save Data                  |");
    puts("| 5. Exit                       |");
    puts("+-------------------------------+");

    return;
}

void print_department_menu()
{
    CLEAR_SCREEN;
    puts("+-------------------------------+");
    puts("|     Department Management     |");
    puts("+-------------------------------+");
    puts("| 1. Add a New Department       |");
    puts("| 2. Delete Department          |");
    puts("| 3. Update Department          |");
    puts("| 4. Display All Departments    |");
    puts("| 5. Back to Main Menu          |");
    puts("+-------------------------------+");

    return;
}

void print_student_menu()
{
    CLEAR_SCREEN;
    puts("+-------------------------------+");
    puts("|      Student Management       |");
    puts("+-------------------------------+");
    puts("| 1. Add a New Student          |");
    puts("| 2. Delete Student             |");
    puts("| 3. Update Student             |");
    puts("| 4. Display All Students       |");
    puts("| 5. Back to Main Menu          |");
    puts("+-------------------------------+");

    return;
}

void print_grade_menu()
{
    CLEAR_SCREEN;
    puts("+-------------------------------+");
    puts("|       Grade Management        |");
    puts("+-------------------------------+");
    puts("| 1. Add a New Grade            |");
    puts("| 2. Delete Grade               |");
    puts("| 3. Update Grade               |");
    puts("| 4. Display All Grades         |");
    puts("| 5. Back to Main Menu          |");
    puts("+-------------------------------+");

    return;
}

void handle_department_menu()
{
    uint16_t selection = INVALID_CHOICE;

    do
    {
        print_department_menu();

        do
        {
            printf("Input a Number : ");
        } while (get_value(&selection) != TRUE);

        switch (selection)
        {
            case ADD:
                add_department();
                break;
            case DELETE:
                delete_department();
                break;
            case UPDATE:
                update_department();
                break;
            case DISPLAY:
                display_department();
                break;
            case EXIT_TO_MAIN:
                return;
            default:
                WRONG_SELECTION;
                PRESS_KEY_TO_CONTINUE;
                break;
        }
    } while (selection != EXIT_TO_MAIN);

    return;
}

void handle_student_menu()
{
    uint16_t selection = INVALID_CHOICE;

    do
    {
        print_student_menu();

        do
        {
            printf("Input a Number : ");
        } while (get_value(&selection) != TRUE);

        switch (selection)
        {
            case ADD:
                add_student();
                break;
            case DELETE:
                delete_student();
                break;
            case UPDATE:
                update_student();
                break;
            case DISPLAY:
                display_student();
                break;
            case EXIT_TO_MAIN:
                return;
            default:
                WRONG_SELECTION;
                PRESS_KEY_TO_CONTINUE;
                break;
        }
    } while (selection != EXIT_TO_MAIN);

    return;
}

void handle_grade_menu()
{
    uint16_t selection = INVALID_CHOICE;

    do
    {
        print_grade_menu();

        do
        {
            printf("Input a Number : ");
        } while (get_value(&selection) != TRUE);

        switch (selection)
        {
            case ADD:
                add_grade();
                break;
            case DELETE:
                delete_grade();
                break;
            case UPDATE:
                update_grade();
                break;
            case DISPLAY:
                display_grade();
                break;
            case EXIT_TO_MAIN:
                return;
            default:
                WRONG_SELECTION;
                PRESS_KEY_TO_CONTINUE;
                break;
        }
    } while (selection != EXIT_TO_MAIN);

    return;
}

void main_menu()
{
    uint16_t selection = INVALID_CHOICE;

    do
    {
        print_main_menu();

        do
        {
            printf("Input a Number : ");
        } while (get_value(&selection) != TRUE);

        switch (selection)
        {
            case DEPT:
                handle_department_menu();
                break;
            case STUD:
                handle_student_menu();
                break;
            case GRAD:
                handle_grade_menu();
                break;
            case SAVE:
                save_all();
                break;
            case EXIT:
                free_everything();
                puts("EXIT Successful");
                exit(EXIT_SUCCESS);
            default:
                WRONG_SELECTION;
                PRESS_KEY_TO_CONTINUE;
                break;
        }
    } while (selection != EXIT);

    return;
}