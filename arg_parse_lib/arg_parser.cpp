#include <getopt.h> 
#include <ranges>
#include <vector>
#include <map>
#include "arg_parser.h"
#include "err_lib.h"

namespace arg_parser {

int parse_args (int argc, char* argv[], 
                    std::map<char, std::pair<int*, int>> short_options, 
                    struct option* options, int* fist_non_flag_idx) {
    ass (options, "null ptr passed", ParserErrCodes::NULL_PTR_PASSED);
    ass (argv, "null ptr passed", ParserErrCodes::NULL_PTR_PASSED);
    
    auto map_keys_view = std::views::keys(short_options);
    std::vector<char> keys{map_keys_view.begin(), map_keys_view.end() };
    char* short_options_keys_arr = &keys[0];

    int opt = -1;
    while ((opt = getopt_long(argc, argv, short_options_keys_arr, options, fist_non_flag_idx)) != -1) {
        
        if (opt == ':')
            ass (false, "flag has no rquired argument", ParserErrCodes::GETOPT_ERROR);

        if (opt == '?')
            ass (false, "unknown flag found", ParserErrCodes::GETOPT_ERROR);

        auto key_pair = short_options.find(opt); 

        if (key_pair != short_options.end())
            *short_options[opt].first = short_options[opt].second;  

        else if (opt == '?')  
            ass (false, "unknown flag found", ParserErrCodes::GETOPT_ERROR);
       
    }
    
    return OK;
}

}