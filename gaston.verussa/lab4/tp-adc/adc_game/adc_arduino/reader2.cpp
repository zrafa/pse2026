#include <stdio.h>
#include <string.h>

char serialPortFilename[] = "/dev/ttyUSB0";

int main()
{
    int readBuffer[1];
    int numBytesRead;

    FILE *serPort = fopen(serialPortFilename, "r");

	if (serPort == NULL)
	{
		printf("ERROR");	
		return 0;
	}

	printf("%s", serialPortFilename);
	printf("%ld", sizeof(int));
	printf(":\n");
	while(1)
	{
		memset(readBuffer, 0, 1);
		fread(readBuffer, sizeof(int),1,serPort);
		if(sizeof(readBuffer) != 0)
		{
			printf("%d", readBuffer[0]);
			printf("\n");
		}
	}
	return 0;
}
