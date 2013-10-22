#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bmpHeader.h"

#define newWidth 1844
#define newHeight 3032
#define FALSE 0
#define TRUE 1

static unsigned char raw[newHeight][newWidth] = {0};

int main(int argc, char *argv[]) {
    struct bmpHeader bmpHeader;
    FILE *bmp, *seg, *horiPlot, *vertPlot;
    
    bool heightStart = TRUE, widthStart = TRUE;
    
    unsigned long i, j, width, height;
    unsigned long hori[newHeight] = {0}, vert[newWidth] = {0};
    unsigned long heightLocate[28] = {0}, widthLocate[8] = {0};
    
    int num, heightNum = 0, widthNum = 0;
    
    unsigned char colorPallete[256][4]={0};

    bmp = fopen("arabic_best_color.bmp", "rb");
    seg = fopen("seg.bmp", "wb");
    horiPlot = fopen("hori.txt", "wt");
    vertPlot = fopen("vert.txt", "wt");
    
    fread(&bmpHeader, sizeof(struct bmpHeader), 1, bmp);
    fread(colorPallete, sizeof(unsigned char), 256*4, bmp);
    fread(raw, sizeof(unsigned char), newHeight*newWidth, bmp);

    fwrite(&bmpHeader, sizeof(struct bmpHeader), 1, seg);
    fwrite(colorPallete, sizeof(unsigned char), 256*4, seg);

//    for(i = 0;i < 256;i++) {
//        printf("-------%03ld-------\n", i);
//        for (j = 0;j < 4;j++) {
//            printf("%03d, ",colorPallete[i][j]);
//        }
//        printf("\n");
//    }

    for(height = 0;height < newHeight;height++) {
        for(width = 0;width < newWidth;width++) {
            if(raw[height][width] == 0) {
                hori[height]++;
            }
        }
        fprintf(horiPlot, "%ld\n", hori[height]);
    }
    
    for(width = 0;width < newWidth;width++) {
        for(height = 0;height < newHeight;height++) {
            if(raw[height][width] == 0) {
                vert[width]++;
            }
        }
        fprintf(vertPlot, "%ld\n", vert[width]);
    }
    
    num = 0;
    for(height = 0;height < newHeight;height++) {
        if(heightStart) {
            if(hori[height] == 0 && hori[height + 1] != 0) {
                heightLocate[num] = height;
                num++;
                heightStart = FALSE;
                continue;
            }
        } else {
            if(hori[height] != 0 && hori[height + 1] == 0) {
                heightLocate[num] = height;
                num++;
                heightStart = TRUE;
                continue;
            }
        }
    }
    
    num = 0;
    for(width = 0;width < newWidth;width++) {
        if(widthStart) {
            if(vert[width] <= 1 && vert[width + 1] > 1) {
                widthLocate[num] = width;
                num++;
                widthStart = FALSE;
                continue;
            }
        } else {
            if(vert[width] > 1 && vert[width + 1] <= 1) {
                widthLocate[num] = width;
                num++;
                widthStart = TRUE;
                continue;
            }
        }
    }

//    for(num = 0;num < newHeight;num++)
//        printf("%d:%ld\n", num, hori[num]);

    for(height = 0;height < newHeight;height++) {
        for(width = 0;width < newWidth;width++) {
            for(heightNum = 0;heightNum < (sizeof(heightLocate)/8);heightNum++) {
                for(widthNum = 0;widthNum < (sizeof(widthLocate)/8);widthNum++) {
                    if(height == heightLocate[heightNum] || width == widthLocate[widthNum]) {
                        raw[height][width] = 249;
                    }
                }
            }
        }
    }
 
    fwrite(raw, sizeof(unsigned char), newHeight*newWidth, seg);

    fclose(bmp);
    fclose(seg);
    fclose(horiPlot);
    fclose(vertPlot);

    return 0;
}
