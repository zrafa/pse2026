void delay_ms(int ms)
{
	volatile int i;
	volatile int j;

	for (i = 0; i < ms; i++)
		for (j = 0; j < 452; j++)
			;
}