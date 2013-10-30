#include "stdlib.h"
#include "stdio.h"

int main()
{
    FILE *korea;

    unsigned char header;
    unsigned short code, newLine = 0x000a;

    korea = fopen("korea.txt", "wb");

    header = 0xff;
    fputc(header, korea);
    header = 0xfe;
    fputc(header, korea);

    for(code = 0xAc00;code <= 0xDA7F;code++){
        fwrite(&code, sizeof(unsigned short), 1, korea);
    }
    fwrite(&newLine, sizeof(unsigned short), 1, korea);
    
    for(code = 0x1100;code <= 0x11FF;code++){
        fwrite(&code, sizeof(unsigned short), 1, korea);
    }
    fwrite(&newLine, sizeof(unsigned short), 1, korea);
    
    for(code = 0x3130;code <= 0x318F;code++){
        fwrite(&code, sizeof(unsigned short), 1, korea);
    }

    fclose(korea);
}
