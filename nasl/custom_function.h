#ifndef CUSTOM_FUNCTION
#define CUSTOM_FUNCTION

#include "nasl_lex_ctxt.h" /* for lex_ctxt */

typedef char *(*func_ptr)(char * func_name, int count, ...);

tree_cell *
custom_function_loader (lex_ctxt *lexic);

u_int8_t load_lib_from_location (func_ptr *out_ptr, void *handle, char *loc);

#endif