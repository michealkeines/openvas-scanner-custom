#include "custom_function.h"
#include <stdio.h>
#include <dlfcn.h>
#include <stdint.h>

u_int8_t load_lib_from_location (func_ptr *out_ptr, void *handle, char *loc)
{   
    if (!handle) {
        fprintf(stdout, "%s: couldn't open", loc);
        return 1;
    }

    func_ptr temp = (func_ptr) dlsym(handle, "invoke_function");
    fprintf(stdout, "func returned: %p\n", temp);
    if (!temp) {
        fprintf(stdout, "invoke funtion pointer is null\n");
        return 2;
    }
    if (*out_ptr == NULL)
    {
        *out_ptr = temp;
        fprintf(stdout, "func updated: %p\n", out_ptr);
    }
    
    return 0;
}


tree_cell *
custom_function_loader (lex_ctxt *lexic)
{
    fprintf(stdout, "this is custom funciton loader\n");
    char *string;
    char *out;
    tree_cell *retc;

    char *loc = "/source/holm-custom/holm-custom.so";
    void *handle = dlopen(loc, RTLD_LAZY);

    string = get_str_var_by_num (lexic, 0);
    fprintf(stdout, "str: %s\n", string);
    func_ptr out_ptr = NULL;
    uint8_t res = load_lib_from_location(&out_ptr, handle, loc);
    fprintf(stdout, "res: %d\n", res);
    if (res == 0)
    {
        fprintf(stdout, "func: %p\n", out_ptr);
        out = out_ptr(string, 1, "localhost");
        fprintf(stdout, "oout: %s\n", out);
    } else if (res == 1 || res == 2)
    {
        out = "erro happened";
    }

    dlclose(handle);

    retc = alloc_typed_cell (CONST_STR);
    retc->size = strlen (out);
    retc->x.str_val = out;
    return retc;
}