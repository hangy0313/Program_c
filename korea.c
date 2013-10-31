#include "stdlib.h"
#include "stdio.h"

int main()
{
    FILE *test, *korea;

    unsigned char header, initial, medial, final;
    unsigned short code, newLine = 0x000a, count = 1;

//    test = fopen("test.txt", "wb");
    korea = fopen("korea.txt", "wb");

    header = 0xff;
    fputc(header, korea);
//    fputc(header, test);
    header = 0xfe;
    fputc(header, korea);
//    fputc(header, test);

//    for(code = 0xAc00;code <= 0xDA7F;code++){
//        fwrite(&code, sizeof(unsigned short), 1, test);
//        fwrite(&newLine, sizeof(unsigned short), 1, test);
//    }
//    
//    for(code = 0x1100;code <= 0x11FF;code++){
//        fwrite(&code, sizeof(unsigned short), 1, test);
//        fwrite(&newLine, sizeof(unsigned short), 1, test);
//    }
//    
//    for(code = 0x3130;code <= 0x318F;code++){
//        fwrite(&code, sizeof(unsigned short), 1, test);
//        fwrite(&newLine, sizeof(unsigned short), 1, test);
//    }

    for(initial = 0;initial <= 18;initial++){
        for(medial = 0;medial <= 20;medial++){
            for(final = 0;final <= 27;final++){
                code = initial*588 + medial*28 + final + 44032;
                fwrite(&code, sizeof(unsigned short), 1, korea);
                if(count%28 == 0){
                    fwrite(&newLine, sizeof(unsigned short), 1, korea);
                }

                count++;
            }
        }
    }
    printf("%d\n", count);
    fclose(korea);
}
