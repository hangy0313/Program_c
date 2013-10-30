#include "stdlib.h"
#include "stdio.h"

int main()
{
    FILE *common, *subCommon, *et;

    unsigned char hb, lb;

    common = fopen("common.txt", "wb");
    subCommon = fopen("subCommon.txt", "wb");
    et = fopen("et.txt", "wt");

    for(hb = 0xA4;hb <= 0xC5;hb++){
        for(lb = 0x40;lb <= 0xFE;lb++){
            if(lb > 0x7E && lb < 0xA1){
                continue;
            }
            fputc(hb, common);
            fputc(lb, common);
            fprintf(common, "\n");
        }
    }
    hb = 0xC6;
    for(lb = 0x40;lb <= 0x7E;lb++){
        fputc(hb, common);
        fputc(lb, common);
        fprintf(common, "\n");
    }

    for(hb = 0xC9;hb <= 0xF9;hb++){
        for(lb = 0x40;lb <= 0xFE;lb++){
            if(lb > 0x7E && lb < 0xA1){
                continue;
            }

            if(hb == 0xF9 && lb > 0xD5){
                fputc(hb, et);
                fputc(lb, et);
                fprintf(et, "\n");
                
                continue;
            }

            fputc(hb, subCommon);
            fputc(lb, subCommon);
            fprintf(subCommon, "\n");
        }
    }
    
    fclose(common);
    fclose(subCommon);
    fclose(et);
}
