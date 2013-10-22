#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmpHeader.h"

#define originWidth 96
#define originHeight 96

#define PI 3.141592653589793

static unsigned char raw[originHeight][originWidth] = {0};

int main(int argc, char *argv[]) {
    struct bmpHeader bmpHeader;
    FILE *horiOne, *horiTwo, *horiThree, *vertOne, *vertTwo, *vertThree;
    FILE *horiOneDft, *horiTwoDft, *horiThreeDft, *vertOneDft, *vertTwoDft, *vertThreeDft;
    
    int height = 0, width = 0, heightNum, widthNum;

    double theta1, theta2, Pr[originHeight][originWidth] = {0.0}, Pi[originHeight][originWidth] = {0.0};
    double Pa[originHeight][originWidth], Pp[originHeight][originWidth];
    
    unsigned char colorPallete[256][4]={0};

    horiOne = fopen("horiOne.bmp", "rb");
    horiTwo = fopen("horiTwo.bmp", "rb");
    horiThree = fopen("horiThree.bmp", "rb");
    vertOne = fopen("vertOne.bmp", "rb");
    vertTwo = fopen("vertTwo.bmp", "rb");
    vertThree = fopen("vertThree.bmp", "rb");

    horiOneDft = fopen("horiOneDft.txt", "wt");
    horiTwoDft = fopen("horiTwoDft.txt", "wt");
    horiThreeDft = fopen("horiThreeDft.txt", "wt");
    vertOneDft = fopen("vertOneDft.txt", "wt");
    vertTwoDft = fopen("vertTwoDft.txt", "wt");
    vertThreeDft = fopen("vertThreeDft.txt", "wt");
    
    fread(&bmpHeader, sizeof(struct bmpHeader), 1, horiOne);
    fread(colorPallete, sizeof(unsigned char), 256*4, horiOne);
    fread(raw, sizeof(unsigned char), originHeight*originWidth, horiOne);

    for(height = 0;height < originHeight;height++) {
        for(width = 0;width < originWidth;width++) {
            for(heightNum = 0;heightNum < height;heightNum++) {
                for(widthNum = 0;widthNum < width;widthNum++) {
                    theta1 = 2 * PI * (double)(height * heightNum) / (double)originHeight;
                    theta2 = 2 * PI * (double)(width * widthNum) / (double)originWidth;
                    Pr[height][width] += raw[height][width] * (cos(theta1) * cos(theta2) - sin(theta1) * sin(theta2));
                    Pi[height][width] -= raw[height][width] * (cos(theta1) * sin(theta2) + cos(theta2) * sin(theta1));
                }
            }
            Pa[height][width] = sqrt(Pr[height][width] * Pr[height][width] + Pi[height][width] * Pi[height][width]);
            Pp[height][width] = atan( Pi[height][width] / Pr[height][width]) * 180 / PI;
            fprintf(horiOneDft, "%12.3e\n", Pa[height][width]);
        }
    }
    
    fread(&bmpHeader, sizeof(struct bmpHeader), 1, horiTwo);
    fread(colorPallete, sizeof(unsigned char), 256*4, horiTwo);
    fread(raw, sizeof(unsigned char), originHeight*originWidth, horiTwo);

    for(height = 0;height < originHeight;height++) {
        for(width = 0;width < originWidth;width++) {
            for(heightNum = 0;heightNum < height;heightNum++) {
                for(widthNum = 0;widthNum < width;widthNum++) {
                    theta1 = 2 * PI * (double)(height * heightNum) / (double)originHeight;
                    theta2 = 2 * PI * (double)(width * widthNum) / (double)originWidth;
                    Pr[height][width] += raw[height][width] * (cos(theta1) * cos(theta2) - sin(theta1) * sin(theta2));
                    Pi[height][width] -= raw[height][width] * (cos(theta1) * sin(theta2) + cos(theta2) * sin(theta1));
                }
            }
            Pa[height][width] = sqrt(Pr[height][width] * Pr[height][width] + Pi[height][width] * Pi[height][width]);
            Pp[height][width] = atan( Pi[height][width] / Pr[height][width]) * 180 / PI;
            fprintf(horiTwoDft, "%12.3e\n", Pa[height][width]);
        }
    }
    
    fread(&bmpHeader, sizeof(struct bmpHeader), 1, horiThree);
    fread(colorPallete, sizeof(unsigned char), 256*4, horiThree);
    fread(raw, sizeof(unsigned char), originHeight*originWidth, horiThree);

    for(height = 0;height < originHeight;height++) {
        for(width = 0;width < originWidth;width++) {
            for(heightNum = 0;heightNum < height;heightNum++) {
                for(widthNum = 0;widthNum < width;widthNum++) {
                    theta1 = 2 * PI * (double)(height * heightNum) / (double)originHeight;
                    theta2 = 2 * PI * (double)(width * widthNum) / (double)originWidth;
                    Pr[height][width] += raw[height][width] * (cos(theta1) * cos(theta2) - sin(theta1) * sin(theta2));
                    Pi[height][width] -= raw[height][width] * (cos(theta1) * sin(theta2) + cos(theta2) * sin(theta1));
                }
            }
            Pa[height][width] = sqrt(Pr[height][width] * Pr[height][width] + Pi[height][width] * Pi[height][width]);
            Pp[height][width] = atan( Pi[height][width] / Pr[height][width]) * 180 / PI;
            fprintf(horiThreeDft, "%12.3e\n", Pa[height][width]);
        }
    }
    
    fread(&bmpHeader, sizeof(struct bmpHeader), 1, vertOne);
    fread(colorPallete, sizeof(unsigned char), 256*4, vertOne);
    fread(raw, sizeof(unsigned char), originHeight*originWidth, vertOne);

    for(height = 0;height < originHeight;height++) {
        for(width = 0;width < originWidth;width++) {
            for(heightNum = 0;heightNum < height;heightNum++) {
                for(widthNum = 0;widthNum < width;widthNum++) {
                    theta1 = 2 * PI * (double)(height * heightNum) / (double)originHeight;
                    theta2 = 2 * PI * (double)(width * widthNum) / (double)originWidth;
                    Pr[height][width] += raw[height][width] * (cos(theta1) * cos(theta2) - sin(theta1) * sin(theta2));
                    Pi[height][width] -= raw[height][width] * (cos(theta1) * sin(theta2) + cos(theta2) * sin(theta1));
                }
            }
            Pa[height][width] = sqrt(Pr[height][width] * Pr[height][width] + Pi[height][width] * Pi[height][width]);
            Pp[height][width] = atan( Pi[height][width] / Pr[height][width]) * 180 / PI;
            fprintf(vertOneDft, "%12.3e\n", Pa[height][width]);
        }
    }
    
    fread(&bmpHeader, sizeof(struct bmpHeader), 1, vertTwo);
    fread(colorPallete, sizeof(unsigned char), 256*4, vertTwo);
    fread(raw, sizeof(unsigned char), originHeight*originWidth, vertTwo);

    for(height = 0;height < originHeight;height++) {
        for(width = 0;width < originWidth;width++) {
            for(heightNum = 0;heightNum < height;heightNum++) {
                for(widthNum = 0;widthNum < width;widthNum++) {
                    theta1 = 2 * PI * (double)(height * heightNum) / (double)originHeight;
                    theta2 = 2 * PI * (double)(width * widthNum) / (double)originWidth;
                    Pr[height][width] += raw[height][width] * (cos(theta1) * cos(theta2) - sin(theta1) * sin(theta2));
                    Pi[height][width] -= raw[height][width] * (cos(theta1) * sin(theta2) + cos(theta2) * sin(theta1));
                }
            }
            Pa[height][width] = sqrt(Pr[height][width] * Pr[height][width] + Pi[height][width] * Pi[height][width]);
            Pp[height][width] = atan( Pi[height][width] / Pr[height][width]) * 180 / PI;
            fprintf(vertTwoDft, "%12.3e\n", Pa[height][width]);
        }
    }
    
    fread(&bmpHeader, sizeof(struct bmpHeader), 1, vertThree);
    fread(colorPallete, sizeof(unsigned char), 256*4, vertThree);
    fread(raw, sizeof(unsigned char), originHeight*originWidth, vertThree);

    for(height = 0;height < originHeight;height++) {
        for(width = 0;width < originWidth;width++) {
            for(heightNum = 0;heightNum < height;heightNum++) {
                for(widthNum = 0;widthNum < width;widthNum++) {
                    theta1 = 2 * PI * (double)(height * heightNum) / (double)originHeight;
                    theta2 = 2 * PI * (double)(width * widthNum) / (double)originWidth;
                    Pr[height][width] += raw[height][width] * (cos(theta1) * cos(theta2) - sin(theta1) * sin(theta2));
                    Pi[height][width] -= raw[height][width] * (cos(theta1) * sin(theta2) + cos(theta2) * sin(theta1));
                }
            }
            Pa[height][width] = sqrt(Pr[height][width] * Pr[height][width] + Pi[height][width] * Pi[height][width]);
            Pp[height][width] = atan( Pi[height][width] / Pr[height][width]) * 180 / PI;
            fprintf(vertThreeDft, "%12.3e\n", Pa[height][width]);
        }
    }

    fclose(horiOne);
    fclose(horiTwo);
    fclose(horiThree);
    fclose(vertOne);
    fclose(vertTwo);
    fclose(vertThree);

    fclose(horiOneDft);
    fclose(horiTwoDft);
    fclose(horiThreeDft);
    fclose(vertOneDft);
    fclose(vertTwoDft);
    fclose(vertThreeDft);

    return 0;
}
