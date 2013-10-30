#include "stdlib.h"
#include "stdio.h"

int main()
{
    FILE *japan;

    unsigned char header;
    unsigned short code, newLine = 0x000a;

    japan = fopen("common.txt", "wb");

    header = 0xff;
    fputc(header, japan);
    header = 0xfe;
    fputc(header, japan);

    for(code = 0x3040;code <= 0x309F;code++){
        fwrite(&code, sizeof(unsigned short), 1, japan);
    }
    fwrite(&newLine, sizeof(unsigned short), 1, japan);
    
    for(code = 0x30A0;code <= 0x30FF;code++){
        fwrite(&code, sizeof(unsigned short), 1, japan);
    }
    fwrite(&newLine, sizeof(unsigned short), 1, japan);
    
    for(code = 0x31F0;code <= 0x31FF;code++){
        fwrite(&code, sizeof(unsigned short), 1, japan);
    }

    fclose(japan);
}
