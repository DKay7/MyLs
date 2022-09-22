#ifndef LSCORE
#define LSCORE
#include <stdio.h>
#include <map>                   
#include "err_lib.h"

enum ErrCodes {
    OK                      =  0,
    NULL_PTR_PASSED         = -1,
    CANT_OPEN_DIR           = -2,
    STAT_FUNC_FAILED        = -3,
    GETPWUID_FUNC_FAILED    = -4,
    GETGRGID_FUNC_FAILED    = -5,
    LOCALTIME_FUNC_FAILED   = -6,
};


int my_ls (const char* dir_name, bool a_flag, bool l_flag, bool r_flag);
int process_long_flag (const char* dir, const struct dirent *dir_entry);

#endif