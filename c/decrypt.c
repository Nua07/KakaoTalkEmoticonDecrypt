void generateLFSR(unsigned int* seq)
{
        char key[]="a271730728cbe141e47fd9d677e9006da271730728cbe141e47fd9d677e9006d";

        seq[0] = 0x12000032;
        seq[1] = 0x2527ac91;
        seq[2] = 0x888c1214;

        for(int i = 0; i < 4; ++i)
        {
                seq[0] = key[i] | (seq[0] << 8);
                seq[1] = key[4+i] | (seq[1] << 8);
                seq[2] = key[8+i] | (seq[2] << 8);
        }
}

int cryptByte(int byte, unsigned int *seq)
{
        char flag1=1;
        char flag2=0;
        int v10=0;
        int v11=0;
        int v12=0;
        int result=0;

        for (int i = 0; i < 8; i++)
        {
                v10 = seq[0] >> 1;
                if (seq[0] << 31)
                {
                        seq[0] = v10 ^ 0xC0000031;
                        v12 = seq[1] >> 1;
                        if (seq[1] << 31)
                        {
                                seq[1] = (v12 | 0xC0000000) ^ 0x20000010;
                                flag1 = 1;
                        }
                        else
                        {
                                seq[1] = v12 & 0x3FFFFFFF;
                                flag1 = 0;
                        }
                }
                else
                {
                        seq[0] = v10;
                        v11 = seq[2] >> 1;
                        if (seq[2] << 31)
                        {
                                seq[2] = (v11 | 0xF0000000) ^ 0x8000001;
                                flag2 = 1;
                        }
                        else
                        {
                                flag2 = 0;
                                seq[2] = v11 & 0xFFFFFFF;
                        }
                }
                result = flag1 ^ flag2 | 2 * result;
        }

        result = result ^ byte;

        return result;
}

void decryptImage(char *buf)
{
        unsigned int seq[3];
        generateLFSR(seq);

        for (int i = 0; i < 128; i++)
        {
                int r = cryptByte(buf[i], seq);
                buf[i] = r;
        }
}
