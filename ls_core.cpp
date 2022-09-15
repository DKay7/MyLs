#include <assert.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <getopt.h> 
#include <ranges>
#include <vector>
#include <map>
#include "ls_core.h"


int my_ls (const char* dir_name, bool a_flag, bool l_flag, bool r_flag) {
    ass (dir_name, "null ptr passed", NULL_PTR_PASSED);

    const struct dirent *entry = nullptr;
    DIR *directory = opendir(dir_name);
    ass (directory, "Can't open directory", CANT_OPEN_DIR);

    while ((entry = readdir(directory)) != NULL) {
        
        // skip hidden files
        if (!a_flag && entry->d_name[0] == '.')
            continue;
        
 
        if (r_flag && entry->d_type == DT_DIR 
                   && strcmp(entry->d_name, "..") != 0 
                   && strcmp(entry->d_name, ".") != 0) {

            char file_path[PATH_MAX];
            sprintf (file_path, "%s/%s", dir_name, entry->d_name);
            printf ("\n%s:\n", entry->d_name);

            return my_ls (file_path, a_flag, l_flag, r_flag);
        }
        else if (l_flag)
            process_long_flag (dir_name, entry);
        else
            printf ("%s\t", entry->d_name);
    }

    printf("\n");

    return OK;
}

int process_long_flag (const char* dir, const struct dirent *dir_entry) {
    ass (dir, "null ptr passed", NULL_PTR_PASSED);
    ass (dir_entry, "null ptr passed", NULL_PTR_PASSED);

    struct stat stat_bufer;
    char file_path[PATH_MAX];
    sprintf (file_path, "%s/%s", dir, dir_entry->d_name);
    
    int stat_result = stat (file_path, &stat_bufer);
    ass ((stat_result != -1), "Can't get file stat", STAT_FUNC_FAILED);

    // print permissions 
    printf((S_ISDIR(stat_bufer.st_mode))  ? "d" : "-"); 
    printf((stat_bufer.st_mode & S_IRUSR) ? "r" : "-");
    printf((stat_bufer.st_mode & S_IWUSR) ? "w" : "-");
    printf((stat_bufer.st_mode & S_IXUSR) ? "x" : "-");
    printf((stat_bufer.st_mode & S_IRGRP) ? "r" : "-");
    printf((stat_bufer.st_mode & S_IWGRP) ? "w" : "-");
    printf((stat_bufer.st_mode & S_IXGRP) ? "x" : "-");
    printf((stat_bufer.st_mode & S_IROTH) ? "r" : "-");
    printf((stat_bufer.st_mode & S_IWOTH) ? "w" : "-");
    printf((stat_bufer.st_mode & S_IXOTH) ? "x " : "- ");

    printf("%li ", stat_bufer.st_nlink);

    struct passwd *pw = nullptr; 
    struct group *gid = nullptr;

    // print user info
    pw = getpwuid(stat_bufer.st_uid);
    ass (pw, "getpwuid function failed", GETPWUID_FUNC_FAILED);
    printf("%s ", pw->pw_name); 

    // print group info
    gid = getgrgid(stat_bufer.st_gid);
    ass (gid, "getgrgid function failed", GETGRGID_FUNC_FAILED);
    printf("%s ", gid->gr_name); 

    // print file size info
    printf("%5ld ", stat_bufer.st_size);

    // print timestamp
    struct tm *local_time_data = nullptr;
    char formated_time_buf[256];
    time_t time = stat_bufer.st_mtime;
    local_time_data = localtime(&time);  
    ass (local_time_data, "localtime function failed", GETGRGID_FUNC_FAILED);

    strftime(formated_time_buf, sizeof(formated_time_buf), "%b %d %R", local_time_data); 
    printf("%s ", formated_time_buf);

    //print file name 
    printf("%s\n", dir_entry->d_name); 

    return OK;
}

int parse_ls_args (int argc, char* argv[], 
                    std::map<char, std::pair<int*, int>> short_options, 
                    struct option* options, int* path_idx) {
    ass (options, "null ptr passed", NULL_PTR_PASSED);
    ass (argv, "null ptr passed", NULL_PTR_PASSED);
    
    auto map_keys_view = std::views::keys(short_options);
    std::vector<char> keys{map_keys_view.begin(), map_keys_view.end() };
    char* short_options_keys_arr = &keys[0];

    int opt = -1;
    while ((opt = getopt_long(argc, argv, short_options_keys_arr, options, path_idx)) != -1) {
        
        if (opt == ':')
            ass (false, "flag has no rquired argument", GETOPT_ERROR);

        if (opt == '?')
            ass (false, "unknown flag found", GETOPT_ERROR);

        auto key_pair = short_options.find(opt); 

        if (key_pair != short_options.end())
            *short_options[opt].first = short_options[opt].second;  

        else
            ass (false, "unknown flag found", GETOPT_ERROR);
       
    }
    
    return OK;
}