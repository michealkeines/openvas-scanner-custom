#include "custom_function.h"
#include <stdio.h>
#include <stdarg.h>
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
    fprintf(stdout, "inside custom funciton loader\n");

    char *out;
    out = "not valid";
    tree_cell *retc;

    char *loc = "/source/holm-custom/holm-custom.so";
    void *handle = dlopen(loc, RTLD_LAZY);

    func_ptr out_ptr = NULL;
    uint8_t res = load_lib_from_location(&out_ptr, handle, loc);
    fprintf(stdout, "res: %d\n", res);

    if (res == 0)
    {
        fprintf(stdout, "variable are passed at: %p\n", lexic);
        fprintf(stdout, "current function pointer: %p\n", out_ptr);
        retc = out_ptr(lexic);
    } else if (res == 1 || res == 2)
    {
        out = "erro happened";
    }

    dlclose(handle);

    // If error, we will return the out with not valid or error
    if(!retc) {
        retc = alloc_typed_cell (CONST_STR);
        retc->size = strlen (out);
        retc->x.str_val = out;
    }

    fprintf(stdout, "exiting custom loader retc: %p\n",retc);

    return retc;
}