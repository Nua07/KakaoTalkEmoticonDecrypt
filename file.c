void generateLFSR(const char* key, int key_len, unsigned int* a3, unsigned int* a4, unsigned int* a5)
{
	char keySet[65] = "";

	*a3 = 301989938;
	*a4 = 623357073;
	*a5 = -2004086252;

	for (int i = 0; i < key_len; ++i) // key * 2
	{
		keySet[i] = key[i];
		keySet[key_len + i] = key[i];
	}


	for(int i = 0; i < 4; ++i)
	{
		*a3 = keySet[i] | (*a3 << 8);
		*a4 = keySet[4+i] | (*a4 << 8);
		*a5 = keySet[8+i] | (*a5 << 8);
	}
}

int cryptByte(int byte, unsigned int *a, unsigned int *b, unsigned int *c)
{
	char flag1;
	int result;
	char flag2;
	int v10;
	int v11;
	int v12;

	flag1 = 1;
	flag2 = 0;

	result = 0;

	for (int i = 0; i < 8; i++)
	{
		v10 = *a >> 1;
		if (*a << 31)
		{
			*a = v10 ^ 0xC0000031;
			v12 = *b >> 1;
			if (*b << 31)
			{
				*b = (v12 | 0xC0000000) ^ 0x20000010;
				flag1 = 1;
			}
			else
			{
				*b = v12 & 0x3FFFFFFF;
				flag1 = 0;
			}
		}
		else
		{
			*a = v10;
			v11 = *c >> 1;
			if (*c << 31)
			{
				*c = (v11 | 0xF0000000) ^ 0x8000001;
				flag2 = 1;
			}
			else
			{
				flag2 = 0;
				*c = v11 & 0xFFFFFFF;
			}
		}
		result = flag1 ^ flag2 | 2 * result;
	}

	result = result ^ byte;

	return result;
}

void decryptImage(char *buf)
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	generateLFSR("a271730728cbe141e47fd9d677e9006d", 32, &a, &b, &c);

	for (int i = 0; i < 128; i++)
	{
		int r = cryptByte(*(buf + i), &a, &b, &c);
		*(buf + i) = r;
	}
}
