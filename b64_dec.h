/* Base64 decoder.
 *
 * Decoder function takes input, output stream, and a char representing the
 * output format, which is either char-formatted using fprintf(fp,"%c"...) or
 * binary formatted using fwrite(3 char blocks).
 *
 * Douglas McCulloch, August 2023
*/

#ifndef b64_d
#define b64_d

#include "b64.h"

void b64_dec(FILE *i_s, FILE *o_s, char op_fmt);

#endif
