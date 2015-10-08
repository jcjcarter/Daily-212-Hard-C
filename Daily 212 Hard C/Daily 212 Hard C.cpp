// Daily 212 Hard C.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <array>

typedef struct { int x, y; }XY;
typedef std::vector<std::string>Map;
typedef std::vector<std::pair<XY, XY>>Results;
typedef std::vector<XY>Path;
typedef std::array<Path, 4>Paths;

const XY dirs[4] = { { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };

void go(int x, int y, const int W, const int H,
	const Path &path, const Map &map, 
	Results &results) {
	XY start = { x,y };
	for (XY xy : path) {
		x += xy.x;
		y += xy.y;

		if (x < 0 || y < 0 || x >= W || y >= H || map[y][x] != ' ')
			return;
	}
	results.emplace_back(start, XY{ x,y });

}


int main()
{
	std::ifstream file("maze.txt");
	int W, H;
	file >> H;

	file.ignore(4,'\n');

	Map map(H);

	for (auto &row : map) {
		std::getline(file,row);
	}
	W = map[0].size();

	std::string path_str;
	std::getline(file, path_str);

	Paths paths;
	int i = 0;
	for (Path &p : paths) {
		int dir = i++;
		for (char c : path_str) {
			if (c == 'r') {
				dir = (dir + 1) % 4;
			}
			else if (c == 'l') {
				dir = (dir - 1 + 4) % 4;
			}
			else {
				for (int i = 0; i < c - '0'; ++i)
				{
					p.emplace_back(dirs[dir]);
				}
			}
		}
	}
	Results results;

	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			if (map[y][x] != ' ')
				continue;
			else
				for (Path &p : paths) {
					go(x, y, W, H, p, map, results);
				}
		}
	}


	for (auto result : results) {
		printf("From (%d %d) to (%d %d)\n", result.first.x, result.first.y,
			result.second.x, result.second.y);
	}
    return 0;
}

