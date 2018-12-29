#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>

int main()
{
	char toto[42];
	printf("%lu, %lu, %lu, %lu\n", sizeof(size_t), sizeof(long), sizeof(long long), sizeof(toto));
}
