#include "stdio.h"
#include "stdlib.h"

#include "wavHeader.h"

#define FS    11025
#define NSEC    900
#define NF      256
#define LEVEL1 2000

static short s[FS*NSEC] = {0};
static double e[FS*NSEC] = {0.0};

int main() {
    FILE *wav, *wavTxt, *formatWavTxt, *energyTxt, *formatEnergyTxt;

    struct wavHeader wavHeader;
    
    int num;
    unsigned long s_max;
    double ratio, energyRatio, e_max;

    wav = fopen("4w_00001.wav", "rb");
    wavTxt = fopen("wav.txt", "wt");
    formatWavTxt = fopen("formatWav.txt", "wt");
    energyTxt = fopen("energy.txt", "wt");
    formatEnergyTxt = fopen("formatEnergy.txt", "wt");

    fread(&wavHeader, sizeof(struct wavHeader), 1, wav);
    fread(s, sizeof(short), wavHeader.dataSize/2, wav);
    
    s_max = labs( (long)s[0]);
    for(num = 1;num < wavHeader.dataSize/2;num++) {
        if(labs((long)s[num]) > s_max) {
            s_max = labs( (long)s[num]);
        }
    }
    ratio = 32768.0 / (double)s_max;

    for(num = 0;num < wavHeader.dataSize/2;num++) {
        fprintf(wavTxt, "%d\n", s[num]);
        fprintf(formatWavTxt, "%f\n", ratio * (double)s[num]);
    }

    for(num = 0;num < NF;num++) {
        e[0] += fabs((double)s[num]);
    }
    for(num = 1;num < wavHeader.dataSize/2 - NF + 1;num++) {
        e[num] = e[num - 1] + fabs((double)s[num + NF -1]) - fabs((double)s[num - 1]);
    }
    for(num = wavHeader.dataSize/2 -NF + 1;num < wavHeader.dataSize/2;num++) {
        e[num] = e[wavHeader.dataSize/2 -NF];
    }
    for(num = 0;num < wavHeader.dataSize/2;num++) {
        fprintf(wavTxt, "%f\n", e[num]);
    }

    e_max = e[0];
    for(num = 1;num < wavHeader.dataSize/2;num++) {
        if(e[num] > e_max) {
            e_max = e[num];
        }
    }
    energyRatio = 32768.0/e_max;

    for(num = 0;num < wavHeader.dataSize/2;num++) {
        fprintf(energyTxt, "%f\n", e[num]);
        fprintf(formatEnergyTxt, "%f\n", energyRatio * e[num]);
    }

    printf("id: %c %c %c %c\n", wavHeader.id[0], wavHeader.id[1], wavHeader.id[2], wavHeader.id[3]);
    printf("file_size: %ld\n", wavHeader.fileSize);
    printf("format: %c %c %c %c\n", wavHeader.format[0], wavHeader.format[1], wavHeader.format[2], wavHeader.format[3]);
    printf("id2: %c %c %c %c\n", wavHeader.id2[0], wavHeader.id2[1], wavHeader.id2[2], wavHeader.id2[3]);

    printf("chunkSize: %ld\n", wavHeader.chunkSize);
    printf("formatTag: %d\n", wavHeader.formatTag);
    printf("channel: %d\n", wavHeader.channel);
    printf("sampleRate: %ld\n", wavHeader.sampleRate);
    printf("byteRate: %ld\n", wavHeader.byteRate);
    printf("blockAlign: %d\n", wavHeader.blockAlign);
    printf("bitsPerSample: %d\n", wavHeader.bitsPerSample);

    printf("data: %c %c %c %c\n", wavHeader.data[0], wavHeader.data[1], wavHeader.data[2], wavHeader.data[3]);
    printf("dataSize: %ld\n", wavHeader.dataSize);

    printf("ratio: %d", ratio);
    printf("dataSize/2: %ld FS*NSEC %d\n", wavHeader.dataSize/2, FS*NSEC);

    fclose(wav);
    fclose(wavTxt);
    fclose(formatWavTxt);
    fclose(energyTxt);
    fclose(formatEnergyTxt);
}
