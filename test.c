#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define PI 3.141592653589793
#define N 256

int main() {
    FILE *wav, *wavTxt;

//    struct wavHeader wavHeader;

    unsigned long n, k;
    short int s[N] = {0};
    double Sr[N] = {0.0}, Si[N] = {0.0}, Sa[N], Sp[N], theta;

    wav = fopen("1.wav", "rb");
    wavTxt = fopen("1.txt", "wt");

    fseek(wav, 44, SEEK_SET);
    fread(s, sizeof(short), N, wav);

    for(n = 0;n < N;n++) {
        for(k = 0;k < N;k++) {
            theta = 2 * PI * (double)(n*k) / (double)N;
            Sr[n] += (double)s[k] * cos(theta);
            Si[n] -= (double)s[k] * sin(theta);
        }
        Sa[n] = sqrt(Sr[n] * Sr[n] + Si[n] * Si[n]);
        Sp[n] = atan(Si[n] / Sr[n]) * 360 / PI;

//        fprintf(wavTxt, "%03ld %12.3e %12.3e %12.3e %12.3e\n", n, Sr[n], Si[n], Sa[n], Sp[n]);
        fprintf(wavTxt, "%12.3e\n", Sa[n]);
    }

    fclose(wav);
    fclose(wavTxt);
}
