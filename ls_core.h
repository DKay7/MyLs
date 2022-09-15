#ifndef LSCORE
#define LSCORE
#include <stdio.h>
#include <map>

#define RED_CLR "\033[91m"
#define END_CLR "\033[0m"

#define ass(condition, err_text, ret)                                                   \
    do {                                                                                \
        if(!condition)                                                                  \
        {                                                                               \
            fprintf(stderr, "Error: " RED_CLR "%s " END_CLR " in %s:%d\n",              \
                    err_text, __FILE__, __LINE__);                                      \
            return ret;                                                                 \
        }                                                                               \
    } while (0);                      

enum ErrCodes {
    OK                      =  0,
    NULL_PTR_PASSED         = -1,
    CANT_OPEN_DIR           = -2,
    STAT_FUNC_FAILED        = -3,
    GETPWUID_FUNC_FAILED    = -4,
    GETGRGID_FUNC_FAILED    = -5,
    LOCALTIME_FUNC_FAILED   = -6,
    GETOPT_ERROR            = -7,
};


int parse_ls_args (int argc, char* argv[], std::map<char, std::pair<int*, int>>short_options, struct option* options, int* path_idx);

int my_ls (const char* dir_name, bool a_flag, bool l_flag, bool r_flag);
int process_long_flag (const char* dir, const struct dirent *dir_entry);

#endif