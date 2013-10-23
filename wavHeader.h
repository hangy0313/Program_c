struct wavHeader {
    unsigned char id[4];         //RIFF
    unsigned long fileSize;
    unsigned char format[4];  //WAVE
    unsigned char id2[4];   //"fmt "

    unsigned long chunkSize;
    short  formatTag;
    short  channel;
    unsigned long sampleRate;
    unsigned long byteRate;
    short  blockAlign;
    short  bitsPerSample;

    unsigned char data[4];
    unsigned long dataSize;
}__attribute__((__packed__));
