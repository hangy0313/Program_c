#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bmpHeader.h"

#define originWidth 1844
#define originHeight 3032

static unsigned char raw[originHeight][originWidth] = {0};

int main(int argc, char *argv[]) {
    struct bmpHeader bmpHeader;
    FILE *bmp, *horiOne, *horiTwo, *horiThree, *vertOne, *vertTwo, *vertThree;
    
    int height = 0, width = 0;
    
    unsigned long newHeight = 96, newWidth = 96;

    unsigned char colorPallete[256][4]={0}, red = 249, temp;

    bmp = fopen("arabic_best_color.bmp", "rb");
    horiOne = fopen("horiOne.bmp", "wb");
    horiTwo = fopen("horiTwo.bmp", "wb");
    horiThree = fopen("horiThree.bmp", "wb");
    vertOne = fopen("vertOne.bmp", "wb");
    vertTwo = fopen("vertTwo.bmp", "wb");
    vertThree = fopen("vertThree.bmp", "wb");
    
    fread(&bmpHeader, sizeof(struct bmpHeader), 1, bmp);
    fread(colorPallete, sizeof(unsigned char), 256*4, bmp);
    fread(raw, sizeof(unsigned char), originHeight*originWidth, bmp);

    bmpHeader.fileSize = (newWidth * newHeight) + 54 + 256*4;
    bmpHeader.width = newWidth;
    bmpHeader.height = newHeight;
    bmpHeader.imageSize = newWidth * newHeight;

    fwrite(&bmpHeader, sizeof(struct bmpHeader), 1, horiOne);
    fwrite(colorPallete, sizeof(unsigned char), 256*4, horiOne);
    fwrite(&bmpHeader, sizeof(struct bmpHeader), 1, horiTwo);
    fwrite(colorPallete, sizeof(unsigned char), 256*4, horiTwo);
    fwrite(&bmpHeader, sizeof(struct bmpHeader), 1, horiThree);
    fwrite(colorPallete, sizeof(unsigned char), 256*4, horiThree);
    fwrite(&bmpHeader, sizeof(struct bmpHeader), 1, vertOne);
    fwrite(colorPallete, sizeof(unsigned char), 256*4, vertOne);
    fwrite(&bmpHeader, sizeof(struct bmpHeader), 1, vertTwo);
    fwrite(colorPallete, sizeof(unsigned char), 256*4, vertTwo);
    fwrite(&bmpHeader, sizeof(struct bmpHeader), 1, vertThree);
    fwrite(colorPallete, sizeof(unsigned char), 256*4, vertThree);
    
    for(height = 0;height < newHeight;height++) {
        for(width = 0;width < newWidth;width++) {
            temp = raw[height][width];
            if(height > 43 && height < 52) {
                temp = red;
            }
            fwrite(&temp, sizeof(unsigned char), 1, horiOne);
        }
    }

    for(height = 0;height < newHeight;height++) {
        for(width = 0;width < newWidth;width++) {
            temp = raw[height][width];
            if(height > 26 && height < 35) {
                temp = red;
            }
            if(height > 61 && height < 70) {
                temp = red;
            }
            fwrite(&temp, sizeof(unsigned char), 1, horiTwo);
        }
    }
    
    for(height = 0;height < newHeight;height++) {
        for(width = 0;width < newWidth;width++) {
            temp = raw[height][width];
            if(height > 17 && height < 26) {
                temp = red;
            }
            if(height > 43 && height < 52) {
                temp = red;
            }
            if(height > 69 && height < 78) {
                temp = red;
            }
            fwrite(&temp, sizeof(unsigned char), 1, horiThree);
        }
    }

    for(height = 0;height < newHeight;height++) {
        for(width = 0;width < newWidth;width++) {
            temp = raw[height][width];
            if(width > 43 && width < 52) {
                temp = red;
            }
            fwrite(&temp, sizeof(unsigned char), 1, vertOne);
        }
    }

    for(height = 0;height < newHeight;height++) {
        for(width = 0;width < newWidth;width++) {
            temp = raw[height][width];
            if(width > 26 && width < 35) {
                temp = red;
            }
            if(width > 61 && width < 70) {
                temp = red;
            }
            fwrite(&temp, sizeof(unsigned char), 1, vertTwo);
        }
    }

    for(height = 0;height < newHeight;height++) {
        for(width = 0;width < newWidth;width++) {
            temp = raw[height][width];
            if(width > 17 && width < 26) {
                temp = red;
            }
            if(width > 43 && width < 52) {
                temp = red;
            }
            if(width > 69 && width < 78) {
                temp = red;
            }
            fwrite(&temp, sizeof(unsigned char), 1, vertThree);
        }
    }
    fclose(bmp);
    fclose(horiOne);
    fclose(horiTwo);
    fclose(horiThree);
    fclose(vertOne);
    fclose(vertTwo);
    fclose(vertThree);

    return 0;
}
