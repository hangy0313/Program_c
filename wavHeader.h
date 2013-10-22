struct wavHeader {
    unsigned char id[4];         //RIFF
    unsigned long fileSize;
    unsigned char format[4];  //WAVE
    unsigned char id2[4];   //"fmt "

    unsigned long chunkSize;
    short int formatTag;
    short int channel;
    unsigned long sampleRate;
    unsigned long byteRate;
    short int blockAlign;
    short int bitsPerSample;

    unsigned char data[4];
    unsigned long dataSize;
};
