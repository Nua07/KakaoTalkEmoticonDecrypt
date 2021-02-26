#ifndef KT_EMOT_DECRYPT_H
#define KT_EMOT_DECRYPT_H

void generateLFSR(unsigned int* seq);
int cryptByte(int byte, unsigned int *seq);
void decryptImage(char *buf);

#endif
