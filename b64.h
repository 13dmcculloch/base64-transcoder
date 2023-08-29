/* A B64 transcoder working with streams.
 * The goal is to accept an indefinite amount
 * of data, take it up in blocks of 24 bits, then
 * output it in blocks of 6 bits.
 * 
 * Todo:
 *      - ???
 * 
 * Douglas McCulloch, August 2023
*/

#ifndef b64
#define b64

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// alphabet 
extern const char b64_table[];

#endif
