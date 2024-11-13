#ifndef SAVE_FILE_H_INCLUDED
#define SAVE_FILE_H_INCLUDED

#ifdef _WIN32
#include <direct.h> /*For _mkdir on Windows*/
#define mkdir(path, mode) _mkdir(path)
#else
#include <sys/stat.h> /*For mkdir on Unix-like systems*/
#endif
#define DATA_DIR "databases"

void ensure_directory_exists(const char *dir_name);
void save_file_of_dept(const char *filename);
void save_file_of_stud(const char *filename);
void save_file_of_grad(const char *filename);

#endif // SAVE_FILE_H_INCLUDED
