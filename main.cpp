#include <getopt.h> 
#include <stdio.h>
#include <map>
#include "ls_core.h"

int main (const int argc, char* argv[]) {

    #ifdef _DEBUG
    printf ("Warning! Running in dubug mode!\n");
    #endif

    int a_flag = 0, l_flag = 0, r_flag = 0;
    int path_idx = -1;
    
    optind = 0;

    static struct option long_options[] =
    {
        {"list",        no_argument, &l_flag, 1},
        {"reqursive",   no_argument, &r_flag, 1},
        {"all",         no_argument, &a_flag, 1},
    };

    using pair_t = std::pair<int*, int>;
    std::map<char, pair_t> short_options{
        {'l', {&l_flag, 1}},
        {'R', {&r_flag, 1}},
        {'a', {&a_flag, 1}}
    };

    parse_ls_args (argc, argv, short_options, long_options, &path_idx);
    
    #ifdef _DEBUG
    printf ("l = %d a = %d r = %d\n", l_flag, a_flag, r_flag);
    #endif

    if (optind != 0 && optind < argc) {
        #ifdef _DEBUG
        printf ("DIR %s optind %d\n", argv[optind], optind);
        #endif
        my_ls (argv[optind], a_flag, l_flag, r_flag);
        
    }
    
    else
        my_ls (".", a_flag, l_flag, r_flag);
    return 0;
}