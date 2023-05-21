#ifndef CUSTOM_FUNCTION
#define CUSTOM_FUNCTION

#include "nasl_lex_ctxt.h" /* for lex_ctxt */
#include <stdarg.h>

typedef tree_cell *(*func_ptr)(lex_ctxt *lexic);

tree_cell *
custom_function_loader (lex_ctxt *lexic);

u_int8_t load_lib_from_location (func_ptr *out_ptr, void *handle, char *loc);

#endif