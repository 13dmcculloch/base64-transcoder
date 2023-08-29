/* Base64 encoder.
*/

#include "b64_enc.h"
#include "b64.h"

void b64_enc(FILE *i_s, FILE *o_s)
{
    uint32_t reg32 = 0;
    int stop_flag = 0;
    
    while(!stop_flag)
    {
        reg32 = 0;
        int i;

        // populate reg32 with 3 bytes
        for(i = 0; i < 3; i++)
        {
            int c = fgetc(i_s); // manually load to avoid issues with little
            if(c == EOF)
            {
                stop_flag = 1;
                reg32 <<= 24 - i * 8;
                break;
            }
            else
            {
                reg32 |= (uint8_t) c;
                reg32 <<= 8;
            }
        }

        // if nothing to decode
        if(!i) return;

        uint32_t mask = 0xFC;  // mask = 0x...FC
        mask <<= 24;  // mask = 0xFC...

        for(int j = 0; j < 4; j++)
        {
            uint32_t idx = reg32 & mask; // 0xFF...
            idx >>= 26;  // 24th + 2nd root - 0x...FF 
            reg32 <<= 6;  // next 6 bits
            
            if(stop_flag && j > i)  // padding
                fprintf(o_s, "%c", b64_table[64]);
            else
                fprintf(o_s, "%c", b64_table[idx]);
        }
    }
}

