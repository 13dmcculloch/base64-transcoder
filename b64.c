/* Base64 transcoder on streams.
 * 
 * Douglas McCulloch, August 2023
 */

#include <string.h>
#include <unistd.h>

#include "b64_enc.h"
#include "b64_dec.h"

// prototypes
void usage();

// flags
int f_encode, f_decode;
int f_chgin, f_chgout;

// options
char *op_fmt;
char *i_s_name, *o_s_name;

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        usage();
        return 1;
    }

    FILE *in_stream = stdin;
    FILE *out_stream = stdout;

    int c = 0;
    while((c = getopt(argc, argv, "ed:i:o:")) != -1)
    {
        switch(c)
        {
        case 'e':
            f_encode = 1;
            break;
        case 'd':
            f_decode = 1;
            op_fmt = optarg;
            break;
        case 'i':
            f_chgin = 1;
            i_s_name = optarg;
            break;
        case 'o':
            f_chgout = 1;
            o_s_name = optarg;
            break;
        default:
            usage();
            return 1;
        }
    }

    // handle flags and execute
    if(f_encode && f_decode)
    {
        usage();
        return 1;
    }

    if(f_chgin)
    {
        fclose(in_stream);
        in_stream = fopen(i_s_name, "rb");
    }

    if(f_chgout)
    {
        fclose(out_stream);
        out_stream = fopen(o_s_name, "wb");
    }

    if(f_encode) b64_enc(in_stream, out_stream);
    else if(f_decode)
    {
        if(!strcmp(op_fmt, "ASCII")) b64_dec(in_stream, out_stream, 'a');
        else if(!strcmp(op_fmt, "binary")) b64_dec(in_stream, out_stream, 'b');
        else printf("Output format not recognised.\nAvailable output formats:\n\t- ASCII\n\t- binary");
    }

    printf("\n");

    return 0;
}

void usage()
{
    printf("Usage: b64 [-e] [-d op_fmt] [-i if] [-o of]\n");
}
