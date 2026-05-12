#include <stdio.h>
#include <string.h>

char serialPortFilename[] = "/dev/ttyUSB0";

int main()
{
    char readBuffer[5];
    int numBytesRead;
    char auxRead[1];

    FILE *serPort = fopen(serialPortFilename, "r");

	auxRead[0] = ' ';
	if (serPort == NULL)
	{
		printf("ERROR");	
		return 0;
	}

	printf("%s", serialPortFilename);
	printf(":\n");
	while(auxRead[0] != '\n')
	{
		memset(auxRead, 0, 1);
		fread(auxRead, sizeof(char), 1, serPort);
	}
	while(1)
	{
		memset(readBuffer, 0, 1);
		fread(readBuffer, sizeof(char),5,serPort);
		if(readBuffer[4] == '\n')
		{
			printf("%c", readBuffer[0]);
			printf("%c", readBuffer[1]);
			printf("%c", readBuffer[2]);
			printf("%c", readBuffer[3]);
			printf("\n");
		}
	}
	return 0;
}
