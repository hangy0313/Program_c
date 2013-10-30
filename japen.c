#include "stdlib.h"
#include "stdio.h"

int main()
{
    FILE *japen;

    unsigned char header;
    unsigned short code, newLine = 0x000a;

    japen = fopen("common.txt", "wb");

    header = 0xff;
    fputc(header, japen);
    header = 0xfe;
    fputc(header, japen);

    for(code = 0x3040;code <= 0x309F;code++){
        fwrite(&code, sizeof(unsigned short), 1, japen);
    }
    fwrite(&newLine, sizeof(unsigned short), 1, japen);
    
    for(code = 0x30A0;code <= 0x30FF;code++){
        fwrite(&code, sizeof(unsigned short), 1, japen);
    }
    fwrite(&newLine, sizeof(unsigned short), 1, japen);
    
    for(code = 0x31F0;code <= 0x31FF;code++){
        fwrite(&code, sizeof(unsigned short), 1, japen);
    }

    fclose(japen);
}
