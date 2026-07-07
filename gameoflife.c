#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 4)
		return (1);
	int w = atoi(av[1]);
	int h = atoi(av[2]);
	int iter = atoi(av[3]);
	if (w <= 0 || h <= 0 || iter < 0)
		return (1);
	int board[h][w];
	int next[h][w];
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			board[y][x] = 0;
			next[y][x] = 0;
		}
	}
	int x = 0;
	int y = 0;
	int pen = 0;
	char c;
	while (read(0, &c, 1) > 0)
	{
		if (c == 'w' && y > 0)
			y--;
		else if (c == 's' && y < h - 1)
			y++;
		else if (c == 'a' && x > 0)
			x--;
		else if (c == 'd' && x < w - 1)
			x++;
		else if (c == 'x')
			pen = !pen;
		if (pen)
			board[y][x] = 1;
	}

	while (iter--)
	{
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				int n = 0;
				for (int dy = -1; dy <= 1; dy++)
				{
					for (int dx = -1; dx <= 1; dx++)
					{
						if (dy == 0 && dx == 0)
							continue;
						int ny = y + dy;
						int nx = x + dx;
						if (ny >= 0 && ny < h
							&& nx >= 0 && nx < w)
						{
							n += board[ny][nx];
						}
					}
				}
				next[y][x] = (board[y][x] && n == 2) || (n == 3);
			}
		}
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
				board[y][x] = next[y][x];
		}
	}
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (board[y][x])
				putchar('O');
			else
				putchar(' ');
		}
		putchar('\n');
	}
	return (0);
}