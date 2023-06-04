#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdarg.h>

#define MINE 10

void usage(void)
{
	fprintf(stderr, "usage: mgc mines size\n");
	exit(1);
}

uint8_t getElementFrom2DArray8(uint8_t *field, int x, int y)
{
	return *(field + (y*sizeof(field)) + x);
}

void generateField(uint8_t *field, int mines_amount, int size)
{
	uint8_t mines_left = mines_amount;
	uint8_t x;
	uint8_t y;

	while (mines_left != 0)
	{ 
		x = rand() % size;
		y = rand() % size;
		if (getElementFrom2DArray8(field, y, x) == MINE)
			continue;
		getElementFrom2DArray8(field, y, x) += MINE;
		for (int8_t i = -1; i < 2; ++i)
			for (int8_t j = -1; j < 2; ++j)
			{
				int8_t yr = y+j;
				int8_t xr = x+i;
				if (yr < 0 || xr < 0 || yr >= size || xr >= size)
					continue;
				++getElementFrom2DArray8(field, yr, xr);
			}
		--mines_left;
	}
}

int main(int argc, char **argv)
{
	uint8_t size, mines;
	if (argc != 3 || !sscanf(argv[2], "%hhu", &size) || !sscanf(argv[1], "%hhu", &mines) || size == 0)
		usage();
	srand(time(NULL));

	uint8_t (*field)[size] = malloc(sizeof(uint8_t[size][size]));
	// for(uint8_t i = 0; i < size; i++)
  //   field[i] = malloc(size * sizeof(*field[i]));
	for (uint8_t i = 0; i < size; ++i)
		for (uint8_t j = 0; j < size; ++j)
			field[j][i] = 0;

	generateField(field, mines, size);
	printf("%d mines:\n", mines);
	for (uint8_t i = 0; i < size; ++i)
	{
		for (uint8_t j = 0; j < size; ++j)
		{
			if (getElementFrom2DArray8(field, j, i) >= MINE)
			{
				printf("||`BM`||");
				continue;
			}
			printf("||` %d`||", getElementFrom2DArray8(field, j, i));
		}
		printf("\n");
	}

	free(field);
	exit(0);
}