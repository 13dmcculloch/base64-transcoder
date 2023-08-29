/* Base64 encoder.
 *
 * Accept an input stream, be it text or binary mode, and encode it to B64
 * using the typical A-Za-z0-9+/ charset. Outputs a stream of formatted chars.
 *
 * Douglas McCulloch, August 2023
*/

#ifndef b64_e
#define b64_e

#include "b64.h"

void b64_enc(FILE *i_s, FILE *o_s);

#endif
