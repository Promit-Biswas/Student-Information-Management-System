#include "input-handler.h"

bool_t fixing_characters(char *buffer)
{
    char *newline_find = NULL;

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
    {
        puts("Input cancelled. Try Again.");
        PRESS_KEY_TO_CONTINUE;

        return FALSE;
    }

    if (buffer[strlen(buffer) - 1] != '\n')
    {
        char clear = 0;

        puts("Input exceeded 20 characters! Try Again.");
        PRESS_KEY_TO_CONTINUE;

        while ((clear = getchar()) != '\n' && clear != EOF);

        return FALSE;
    }

    newline_find = strchr(buffer, '\n');

    if (newline_find)
    {
        *newline_find = '\0';
    }

    return TRUE;
}

bool_t get_name(char *buffer)
{
    if(!fixing_characters(buffer))
    {
        return FALSE;
    }

    buffer[BUFFER_SIZE - 1] = '\0';

    return TRUE;
}

bool_t get_value(uint16_t *choice)
{
    char buffer[BUFFER_SIZE] = {0};
    uint16_t index = 0;
    uint32_t value = 0;
    uint16_t start_of_char = 0;

    if(!fixing_characters(buffer))
    {
        return FALSE;
    }

    while (buffer[start_of_char] == ' ')
    {
        start_of_char++;
    }

    for (index = start_of_char; buffer[index] != '\0'; index++)
    {
        if (!isdigit(buffer[index]))
        {
            puts("Non-digit characters present. Try Again.");
            PRESS_KEY_TO_CONTINUE;

            return FALSE;
        }

        if (buffer[index + 1] == ' ' && buffer[index + 1] != '\0')
        {
            buffer[index + 1] = '\0';
            break;
        }
    }

    value = atoi(buffer + start_of_char);

    if (value < 0 || value > UINT16_MAX)
    {
        puts("Number out of range. Try Again.");
        PRESS_KEY_TO_CONTINUE;

        return FALSE;
    }

    *choice = (uint16_t)value;

    return TRUE;
}

char* int_to_str(uint8_t num)
{
    /*to store unsigned char*/
    char *str = NULL;

    str = (char*)calloc(CHAR_TO_STORE, sizeof(char));

    if (str == NULL)
    {
        safe_exit("Memory Allocation Failed.");
    }

    snprintf(str, CHAR_TO_STORE, "%hu", num);

    return str;
}

void safe_exit(const char *message)
{
    fprintf(stderr, "%s\n", message);
    PRESS_KEY_TO_CONTINUE;
    exit(EXIT_FAILURE);

    return;
}

