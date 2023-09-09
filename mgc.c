#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#define MINE 10

struct field_t
{
	uint8_t size;
	uint8_t *field;
};

void usage(void)
{
	fprintf(
		stderr, "%s",
		"usage: mgc mines size\n"
		"mines: (0, size^2]\n"
		"size:  (0, 10)\n");
	exit(1);
}

uint8_t *getelem(struct field_t field, uint8_t y, uint8_t x)
{
	return field.field + y*field.size + x;
}

void generateField(struct field_t field, int mines_amount)
{
	uint8_t mines_left = mines_amount;
	uint8_t x, y;
	uint8_t size = field.size;

	while (mines_left != 0)
	{
		x = rand() % size;
		y = rand() % size;
		if (*getelem(field, y, x) >= MINE)
			continue;
		*getelem(field, y, x) += MINE;
		for (int8_t i = -1; i < 2; ++i)
			for (int8_t j = -1; j < 2; ++j)
			{
				int8_t yr = y+j;
				int8_t xr = x+i;
				if (yr < 0 || xr < 0 || yr >= size || xr >= size)
					continue;
				++*getelem(field, yr, xr);
			}
		--mines_left;
	}
}

int main(int argc, char **argv)
{
	uint8_t size, mines;
	if (argc != 3 ||
		!sscanf(argv[2], "%hhu", &size) || !sscanf(argv[1], "%hhu", &mines)
		|| size == 0 || size > 9|| mines > size*size)
		usage();
	srand(time(NULL));

	struct field_t field = {
		size,
		malloc(size*size)
	};
	memset(field.field, 0, size*size);

	generateField(field, mines);

	printf("%d mines:\n", mines);
	for (uint8_t i = 0; i < size; ++i)
	{
		for (uint8_t j = 0; j < size; ++j)
		{
			if (*getelem(field, j, i) >= MINE)
			{
				printf("||`BM`||");
				continue;
			}
			printf("||` %d`||", *getelem(field, j, i));
		}
		printf("\n");
	}

	free(field.field);
	exit(0);
}