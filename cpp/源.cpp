#include<stdlib.h>
#include<stdio.h> 
#include<string.h>
int main()
{
	char a[10], b[10], c[10], s[10];
	scanf_s("%s", a, 10);
	scanf_s("%s", b, 10);
	scanf_s("%s", c, 10);
	if (strcmp(a, b) <= 0)
	{
		if (strcmp(b, c) <= 0)
		{
			puts(a);
			puts(b);
			puts(c);
		}
		else if (strcmp(a, c) <= 0)
		{
			puts(a);
			puts(c);
			puts(b);
		}
		else
		{
			puts(c);
			puts(a);
			puts(b);
		}
	}
	else
	{
		if (strcmp(a, c) <= 0)
		{
			puts(b);
			puts(a);
			puts(c);
		}
		else if (strcmp(b, c) <= 0)
		{
			puts(b);
			puts(c);
			puts(a);
		}
		else
		{
			puts(c);
			puts(b);
			puts(a);
		}
	}
	
	system("pause");
	return 0;
}