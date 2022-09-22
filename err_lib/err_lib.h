
namespace err_lib {

#define RED_CLR  "\033[91m"
#define BLUE_CLR "\033[94m"
#define END_CLR  "\033[0m"


#define ass(condition, err_text, ret)                                                   \
    do {                                                                                \
        if(!condition)                                                                  \
        {                                                                               \
            fprintf(stderr, "Error: " RED_CLR "%s " END_CLR " in %s:%d\n",              \
                    err_text, __FILE__, __LINE__);                                      \
            return ret;                                                                 \
        }                                                                               \
    } while (0);   

}