#########################################
# send debug messages
#########################################
divert(0)#include "core/debug.h"
divert(-1)

define(`DEBUG', `ifelse(`$#', 1,dnl
`debug_printf("Control6: " $1 "\n");',
`debug_printf("Control6: " $1 "\n", shift($@));')')

