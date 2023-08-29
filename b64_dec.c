/* Base64 decoder operating on streams.
*/

#include "b64_dec.h"
#include "b64.h"

void b64_dec(FILE *i_s, FILE *o_s, char op_fmt)
{
    uint32_t reg32;
    int stop_flag = 0;
    int stop_idx = 0;

    while(!stop_flag)
    {
        reg32 = 0;

        // recover binary stream in 4 blocks of 6 bits 
        for(int i = 0; i < 4; i++)
        {
            int c = fgetc(i_s);
            if(c == EOF || c == '=')
            {
                stop_flag = 1;
                stop_idx = i;
                reg32 <<= 18 - stop_idx * 6;
                break;
            }
            else
            {
                // arithmetic to convert ASCII to B64 
                if(c >= 65 && c <= 90) c -= 65;
                else if(c >= 97 && c <= 122) c -= 97 - 26;
                else if(c >= 48 && c <= 57) c -= 48 - 52;
                else if(c == '+') c = 62;
                else if(c == '/') c = 63;

                reg32 |= (uint8_t)c;
                if(i < 3) reg32 <<= 6;
            }
        }

        if(stop_flag & !stop_idx) break;

        uint32_t mask = 0x00FF0000;

        // decode according to output format
        switch(op_fmt)
        {
            case 'a':  // decode to ASCII
                for(int i = 0; i < 3; i++)
                {
                    if(i + 1 >= stop_idx & stop_flag) break;

                    // get next char
                    uint32_t c = reg32 & mask;
                    c >>= 16 - i * 8;
                    mask >>= 8;

                    fprintf(o_s, "%c", (char)c);
                }
                break;

            case 'b': // decode to binary
                for(int i = 0; i < 3; i++)
                {
                    if(i + 1 >= stop_idx & stop_flag) break;

                    // get next char
                    uint32_t c = reg32 & mask;
                    c >>= 16 - i * 8;
                    mask >>= 8;

                    fwrite(&c, sizeof(char), 1, o_s);
                }
               break;


            default:
                fprintf(o_s, "Unknown op_fmt.\n");
        }
    }
}

