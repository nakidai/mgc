#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define MINE 10

void usage(void)
{
	fprintf(stderr, "usage: mgc mines size\n");
	exit(1);
}

void generateField(uint8_t **field, int mines_amount, int size)
{
	uint8_t mines_left = mines_amount;
	uint8_t x;
	uint8_t y;

	while (mines_left != 0)
	{
		x = random() % size;
		y = random() % size;
		if (field[y][x] == MINE)
			continue;
		field[y][x] = MINE;
		for (int8_t i = -1; i < 2; ++i)
			for (int8_t j = -1; j < 2; ++j)
			{
				int8_t yr = y+j;
				int8_t xr = x+i;
				if (yr < 0 || xr < 0 || yr >= size || xr >= size || field[yr][xr] == MINE)
					continue;
				++field[yr][xr];
			}
		--mines_left;
	}
}

int main(int argc, char **argv)
{
	uint8_t size, mines;
	if (argc != 3 || !sscanf(argv[2], "%hhu", &size) || !sscanf(argv[1], "%hhu", &mines) || size == 0)
		usage();
	srandom(time(NULL));

	uint8_t **field = malloc(size * sizeof(*field));
	for(uint8_t i = 0; i < size; i++)
    field[i] = malloc(size * sizeof(*field[i]));
	for (uint8_t i = 0; i < size; ++i)
		for (uint8_t j = 0; j < size; ++j)
			field[j][i] = 0;

	generateField(field, mines, size);
	printf("%d mines:\n", mines);
	for (uint8_t i = 0; i < size; ++i)
	{
		for (uint8_t j = 0; j < size; ++j)
		{
			if (field[j][i] == MINE)
			{
				printf("||`BM`||");
				continue;
			}
			printf("||` %d`||", field[j][i]);
		}
		printf("\n");
	}

	free(field);
	exit(0);
}