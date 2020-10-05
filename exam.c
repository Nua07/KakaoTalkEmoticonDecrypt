int main()
{
	FILE *fp;
	if (fopen_s(&fp, "image_enc", "rb") != 0)
	{
		printf("File Open Error\n");
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	int fileLength = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *buf = (char *)malloc(fileLength);

	fread_s(buf, fileLength, 1, fileLength, fp);
	decryptImage(buf);
	FILE *ffp = fopen("image_dec.webp", "wb");
	fwrite(buf, 1, fileLength, ffp);
	fflush(ffp);

	fclose(fp);
	fclose(ffp);

	free(buf);
}
