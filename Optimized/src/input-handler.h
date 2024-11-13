#ifndef INPUT_HANDLER_H_INCLUDED
#define INPUT_HANDLER_H_INCLUDED

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE 21
#define INVALID_CHOICE 0xFFFF
#define CHAR_TO_STORE 4
#define STRUCT_MULTIPLIER 1
#define WRONG_SELECTION puts("Wrong Input: Please try again.")

#if defined(_WIN32) || defined(_WIN64)
#define CLEAR_SCREEN system("cls")
#elif defined(__linux__) && (defined(__i386__) || defined(__x86_64__))
#define CLEAR_SCREEN system("clear")
#else
#define CLEAR_SCREEN
#endif

#define PRESS_KEY_TO_CONTINUE                     \
    {                                             \
        printf("Press ENTER key to continue..."); \
        while (getchar() != '\n')                 \
            ;                                     \
    }

enum menu_select
{
    DEPT = 1,
    STUD,
    GRAD,
    SAVE,
    EXIT
};

enum selection
{
    ADD = 1,
    DELETE,
    UPDATE,
    DISPLAY,
    EXIT_TO_MAIN
};

typedef enum
{
    FALSE = 0,
    TRUE
} bool_t;

bool_t get_value(uint16_t *value);
bool_t get_name(char *choice);

/****************************************************************************
 * Name:       fixing_characters
 *
 * Input:      char *buffer - Pointer to a character array where the input string
 *                            will be stored.
 *
 * Return:     success `TRUE` if the input is successfully processed
 *             fail 'FALSE'   otherwise,
 *
 * Description: This function reads a line of input into the provided buffer,
 *              checks if the input exceeds the buffer size, and removes the
 *              trailing newline character if present. It also trims leading
 *              spaces from the input. If the input is too long or if any errors
 *              occur during input.
 ****************************************************************************/
bool_t fixing_characters(char *buffer);
char *int_to_str(uint8_t num);
void safe_exit(const char *message);

#endif // INPUT-HANDLER_H_INCLUDED
