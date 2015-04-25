/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/

#include "parser.h"
#include "lexer.h"
#include "mapping.h"

int ParseTable[NUM_NONTERM + 1][NUM_TERM + 1] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 4, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 11, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 17, 17, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 20, 0, 0, 0, 0, 20, 20, 20, 20, 20, 0, 0, 0, 20, 20, 0, 0, 0, 0, 20, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 20, 0, 0},
		{0, 0, 0, 22, 0, 0, 21, 22, 0, 0, 0, 0, 22, 0, 0, 22, 0, 0, 21, 21, 0, 0, 0, 0, 21, 21, 21, 21, 21, 22, 22, 22, 21, 21, 0, 0, 0, 0, 21, 21, 0, 0, 0, 22, 22, 0, 0, 0, 0, 0, 0, 22, 22, 22, 21, 0, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 21, 0, 0},
		{0, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 23, 0, 0, 0, 0, 23, 23, 23, 23, 24, 0, 0, 0, 28, 28, 0, 0, 0, 0, 26, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27, 0, 0, 0, 0, 0, 0, 0, 29, 0, 0, 0, 0, 30, 0, 0},
		{0, 0, 0, 0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 31, 0, 0, 0, 0, 31, 31, 31, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 32, 0, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 32, 0, 0, 0, 0, 32, 32, 32, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34, 34, 0, 0, 0, 0, 34, 34, 34, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 37, 0, 0, 0, 0, 35, 35, 35, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 40, 41, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52, 53, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 57, 58, 59, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 63, 0, 0, 0, 63, 0, 0, 63, 63, 61, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 65, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 71, 0, 0, 68, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 73, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 74, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75, 75, 0, 0, 0, 0, 75, 75, 75, 75, 75, 0, 0, 0, 75, 75, 0, 0, 0, 0, 75, 75, 76, 75, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75, 0, 0, 0, 0, 0, 0, 0, 75, 0, 0, 0, 0, 75, 0, 0},
		{0, 0, 0, 0, 0, 0, 77, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 77, 77, 0, 0, 0, 0, 77, 77, 77, 77, 77, 0, 0, 0, 77, 77, 0, 0, 0, 0, 77, 77, 0, 78, 79, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 77, 0, 0, 0, 0, 0, 0, 0, 77, 0, 0, 0, 0, 77, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 83, 0, 0, 0, 0, 82, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 84, 85, 0, 0, 0, 0, 0, 0, 83, 83, 83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 86, 87, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 88, 89, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90, 91, 92, 93, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 94, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 95, 96, 97, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 98, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0, 0, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0, 0, 0, 0, 99, 99, 99, 0, 0, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 101, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 102, 0, 0, 0, 0, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 102, 0, 0, 0, 0, 0, 0, 102, 102, 102, 0, 0, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 104, 0, 0, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 104, 104, 103, 103, 103, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 105, 0, 0, 0, 0, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 105, 0, 0, 0, 0, 0, 0, 105, 105, 105, 0, 0, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 107, 0, 0, 0, 107, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 107, 107, 107, 107, 107, 106, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 109, 0, 0, 0, 0, 108, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 0, 0, 0, 0, 0, 0, 110, 110, 110, 0, 0, 111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 113, 112, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 114, 115, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 117, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 118, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 119, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 121, 0, 0, 0, 0, 0, 0, 0, 122, 123, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 124, 0, 0, 0, 0, 0, 0, 124, 124, 124, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 125, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 126, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 127, 0, 0, 0, 0, 0, 0, 127, 127, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 129, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 129, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 132, 0, 0, 0, 0, 0, 0, 130, 131, 133, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 134, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 135, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 137, 0, 0, 0, 0, 139, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 138, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 140, 0},
		{0, 0, 0, 0, 0, 0, 0, 141, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 142, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

Tree parser(TokenList tokens, int numTokens,bool* parseSuccess) {
        Rule rule;
	int tkIndex = 0, ruleNo;
	Symbol temp;
	*parseSuccess = true;
	SymbolStack stack = NULL;
	
        Rules rules = (Rule *)getGrammarRules();
        Node** followSet = (Node **)getFollowSet();

	Tree ParseTree = createTree(program);
	TreeNode* currNode = ParseTree;
	push(&stack, program);

	while ( !isEmpty(stack) && (tkIndex < numTokens)) {
		if ( top(stack) == (*(tokens+tkIndex))->token ) {
			pop(&stack);
			currNode->value = (tokens+tkIndex);
			if (!isEmpty(stack))
				currNode = searchTree(currNode, top(stack), program);
			else
				break;
			tkIndex++;
		}
		else if( top(stack) < program){
			printf("\nParsing Error in Line no %d: Expected '%s' instead of '%s'.\n", (*(tokens+tkIndex))->lineno, tokenToStr(top(stack)) ,tokenToStr((*(tokens+tkIndex))->token));
			pop(&stack);
			*parseSuccess = false;
		}
		else {
			ruleNo = ParseTable[INDEX(top(stack))][((*(tokens+tkIndex))->token)];
			if (ruleNo == 0) {
				printf("\nParsing Error in Line no %d: Unexpected '%s'.\n", (*(tokens+tkIndex))->lineno, tokenToStr((*(tokens+tkIndex))->token));
				while( !searchList(followSet[INDEX(top(stack))], ((*(tokens+tkIndex))->token) ) ){
					tkIndex++;
				}
				pop(&stack);
				*parseSuccess = false;
				continue;
			}
			rule = rules[ruleNo];
			pop(&stack);
                        fillStackFromList(&stack, &rule.rhs);
                        insertTreeList(&currNode, rule.rhs);
                        currNode = currNode->child;
                        currNode = searchTree(currNode, top(stack), program);
		}
		// printStack(stack);
		//printList(rule.rhs);
	}
	return ParseTree;
}

void fillStackFromList(Node** stack, Node** list){
        reverseList(list);
        Node *p = *list;
        while(p != NULL){
                if(p->value == 0){
                        p = p->next;
                        continue;
                }
                push(stack, p->value);
                p = p->next;
        }
        reverseList(list);
}

Rule* getGrammarRules() {
	Rule* Rules = malloc(sizeof(Rule) * (NUM_RULES + 1));

	//1
	Rules[1].lhs = program;
	insert(&(Rules[1].rhs), _records);
	insert(&(Rules[1].rhs), _procedures);
	insert(&(Rules[1].rhs), execute);

	//2
	Rules[2].lhs = execute;
	insert(&(Rules[2].rhs), EXECUTE);
	insert(&(Rules[2].rhs), COLON);
	insert(&(Rules[2].rhs), stmts);
	insert(&(Rules[2].rhs), END);

	//3
	Rules[3].lhs = _records;
	insert(&(Rules[3].rhs), records);

	//4
	Rules[4].lhs = _records;
	insert(&(Rules[4].rhs), EPSILON);

	//5
	Rules[5].lhs = records;
	insert(&(Rules[5].rhs), RECORDS);
	insert(&(Rules[5].rhs), COLON);
	insert(&(Rules[5].rhs), recs);
	insert(&(Rules[5].rhs), ENDRECORDS);

	//6
	Rules[6].lhs = recs;
	insert(&(Rules[6].rhs), rec);
	insert(&(Rules[6].rhs), _recs);

	//7
	Rules[7].lhs = _recs;
	insert(&(Rules[7].rhs), recs);

	//8
	Rules[8].lhs = recs;
	insert(&(Rules[8].rhs), EPSILON);

	//9
	Rules[9].lhs = rec;
	insert(&(Rules[9].rhs), REC);
	insert(&(Rules[9].rhs), ID);
	insert(&(Rules[9].rhs), COLON);
	insert(&(Rules[9].rhs), decl_stmts);
	insert(&(Rules[9].rhs), ENDREC);

	//10
	Rules[10].lhs = _procedures;
	insert(&(Rules[10].rhs), procedures);

	//11
	Rules[11].lhs = _procedures;
	insert(&(Rules[11].rhs), EPSILON);

	//12
	Rules[12].lhs = procedures;
	insert(&(Rules[12].rhs), PROCS);
	insert(&(Rules[12].rhs), COLON);
	insert(&(Rules[12].rhs), procs);
	insert(&(Rules[12].rhs), ENDPROCS);

	//13
	Rules[13].lhs = procs;
	insert(&(Rules[13].rhs), proc);
	insert(&(Rules[13].rhs), _procs);

	//14
	Rules[14].lhs = _procs;
	insert(&(Rules[14].rhs), procs);

	//15
	Rules[15].lhs = _procs;
	insert(&(Rules[15].rhs), EPSILON);

	//16
	Rules[16].lhs = proc;
	insert(&(Rules[16].rhs), PROC);
	insert(&(Rules[16].rhs), ID);
	insert(&(Rules[16].rhs), LPAREN);
	insert(&(Rules[16].rhs), param_list);
	insert(&(Rules[16].rhs), RPAREN);
	insert(&(Rules[16].rhs), ARROW);
	insert(&(Rules[16].rhs), LPAREN);
	insert(&(Rules[16].rhs), param_list);
	insert(&(Rules[16].rhs), RPAREN);
	insert(&(Rules[16].rhs), COLON);
	insert(&(Rules[16].rhs), stmts);
	insert(&(Rules[16].rhs), ENDPROC);

	//17
	Rules[17].lhs = param_list;
	insert(&(Rules[17].rhs), basic_type);
	insert(&(Rules[17].rhs), ID);
	insert(&(Rules[17].rhs), _param_list);

	//18
	Rules[18].lhs = _param_list;
	insert(&(Rules[18].rhs), COMMA);
	insert(&(Rules[18].rhs), param_list);

	//19
	Rules[19].lhs = _param_list;
	insert(&(Rules[19].rhs), EPSILON);

	//20
	Rules[20].lhs = stmts;
	insert(&(Rules[20].rhs), stmt);
	insert(&(Rules[20].rhs), _stmts);

	//21
	Rules[21].lhs = _stmts;
	insert(&(Rules[21].rhs), stmts);

	//22
	Rules[22].lhs = _stmts;
	insert(&(Rules[22].rhs), EPSILON);

	//23
	Rules[23].lhs = stmt;
	insert(&(Rules[23].rhs), decl_stmt);

	//24
	Rules[24].lhs = stmt;
	insert(&(Rules[24].rhs), cond_stmt);

	//25
	Rules[25].lhs = stmt;
	insert(&(Rules[25].rhs), loop_stmt);

	//26
	Rules[26].lhs = stmt;
	insert(&(Rules[26].rhs), proc_call_stmt);

	//27
	Rules[27].lhs = stmt;
	insert(&(Rules[27].rhs), assign_stmt);

	//28
	Rules[28].lhs = stmt;
	insert(&(Rules[28].rhs), io_stmt);

	//29
	Rules[29].lhs = stmt;
	insert(&(Rules[29].rhs), mat_assign_stmt);

	//30
	Rules[30].lhs = stmt;
	insert(&(Rules[30].rhs), str_assign_stmt);

	//31
	Rules[31].lhs = decl_stmts;
	insert(&(Rules[31].rhs), decl_stmt);
	insert(&(Rules[31].rhs), _decl_stmts);

	//32
	Rules[32].lhs = _decl_stmts;
	insert(&(Rules[32].rhs), decl_stmts);

	//33
	Rules[33].lhs = _decl_stmts;
	insert(&(Rules[33].rhs), EPSILON);

	//34
	Rules[34].lhs = decl_stmt;
	insert(&(Rules[34].rhs), type);
	insert(&(Rules[34].rhs), id_list);
	insert(&(Rules[34].rhs), SEMICOLON);

	//35
	Rules[35].lhs = type;
	insert(&(Rules[35].rhs), basic_type);

	//36
	Rules[36].lhs = type;
	insert(&(Rules[36].rhs), STRING);

	//37
	Rules[37].lhs = type;
	insert(&(Rules[37].rhs), MAT);
	insert(&(Rules[37].rhs), LT);
	insert(&(Rules[37].rhs), basic_type);
	insert(&(Rules[37].rhs), GT);
	insert(&(Rules[37].rhs), LSQ);
	insert(&(Rules[37].rhs), dims);
	insert(&(Rules[37].rhs), RSQ);

	//38
	Rules[38].lhs = type;
	insert(&(Rules[38].rhs), REC);
	insert(&(Rules[38].rhs), ID);

	//39
	Rules[39].lhs = basic_type;
	insert(&(Rules[39].rhs), INT);

	//40
	Rules[40].lhs = basic_type;
	insert(&(Rules[40].rhs), REAL);

	//41
	Rules[41].lhs = basic_type;
	insert(&(Rules[41].rhs), BOOL);

	//42
	Rules[42].lhs = basic_type;
	insert(&(Rules[42].rhs), CHAR);

	//43
	Rules[43].lhs = id_list;
	insert(&(Rules[43].rhs), ID);
	insert(&(Rules[43].rhs), _id_list);

	//44
	Rules[44].lhs = _id_list;
	insert(&(Rules[44].rhs), COMMA);
	insert(&(Rules[44].rhs), id_list);

	//45
	Rules[45].lhs = _id_list;
	insert(&(Rules[45].rhs), EPSILON);

	//46
	Rules[46].lhs = dims;
	insert(&(Rules[46].rhs), ind);
	insert(&(Rules[46].rhs), _dim_list);

	//47
	Rules[47].lhs = _dim_list;
	insert(&(Rules[47].rhs), COMMA);
	insert(&(Rules[47].rhs), ind);

	//48
	Rules[48].lhs = _dim_list;
	insert(&(Rules[48].rhs), EPSILON);

	//49
	Rules[49].lhs = cond_stmt;
	insert(&(Rules[49].rhs), IF);
	insert(&(Rules[49].rhs), LPAREN);
	insert(&(Rules[49].rhs), conds);
	insert(&(Rules[49].rhs), RPAREN);
	insert(&(Rules[49].rhs), COLON);
	insert(&(Rules[49].rhs), stmts);
	insert(&(Rules[49].rhs), else_if);
	insert(&(Rules[49].rhs), _cond_stmt);

	//50
	Rules[50].lhs = else_if;
	insert(&(Rules[50].rhs), ELIF);
	insert(&(Rules[50].rhs), LPAREN);
	insert(&(Rules[50].rhs), conds);
	insert(&(Rules[50].rhs), RPAREN);
	insert(&(Rules[50].rhs), COLON);
	insert(&(Rules[50].rhs), stmts);
	insert(&(Rules[50].rhs), else_if);

	//51
	Rules[51].lhs = else_if;
	insert(&(Rules[51].rhs), EPSILON);

	//52
	Rules[52].lhs = _cond_stmt;
	insert(&(Rules[52].rhs), ELSE);
	insert(&(Rules[52].rhs), COLON);
	insert(&(Rules[52].rhs), stmts);
	insert(&(Rules[52].rhs), ENDIF);

	//53
	Rules[53].lhs = _cond_stmt;
	insert(&(Rules[53].rhs), ENDIF);

	//54
	Rules[54].lhs = io_stmt;
	insert(&(Rules[54].rhs), GET);
	insert(&(Rules[54].rhs), LPAREN);
	insert(&(Rules[54].rhs), var);
	insert(&(Rules[54].rhs), RPAREN);
	insert(&(Rules[54].rhs), SEMICOLON);

	//55
	Rules[55].lhs = io_stmt;
	insert(&(Rules[55].rhs), PUT);
	insert(&(Rules[55].rhs), LPAREN);
	insert(&(Rules[55].rhs), put_param);
	insert(&(Rules[55].rhs), RPAREN);
	insert(&(Rules[55].rhs), SEMICOLON);

	//56
	Rules[56].lhs = put_param;
	insert(&(Rules[56].rhs), var);

	//57
	Rules[57].lhs = put_param;
	insert(&(Rules[57].rhs), ENDL);

	//58
	Rules[58].lhs = put_param;
	insert(&(Rules[58].rhs), TAB);

	//59
	Rules[59].lhs = put_param;
	insert(&(Rules[59].rhs), STR_LIT);

	//60
	Rules[60].lhs = var;
	insert(&(Rules[60].rhs), ID);
	insert(&(Rules[60].rhs), _var);

	//61
	Rules[61].lhs = _var;
	insert(&(Rules[61].rhs), LSQ);
	insert(&(Rules[61].rhs), dims);
	insert(&(Rules[61].rhs), RSQ);

	//62
	Rules[62].lhs = _var;
	insert(&(Rules[62].rhs), DOT);
	insert(&(Rules[62].rhs), ID);

	//63
	Rules[63].lhs = _var;
	insert(&(Rules[63].rhs), EPSILON);

	//64
	Rules[64].lhs = proc_call_stmt;
	insert(&(Rules[64].rhs), CALL);
	insert(&(Rules[64].rhs), ID);
	insert(&(Rules[64].rhs), LPAREN);
	insert(&(Rules[64].rhs), proc_arg_list);
	insert(&(Rules[64].rhs), RPAREN);
	insert(&(Rules[64].rhs), ARROW);
	insert(&(Rules[64].rhs), LPAREN);
	insert(&(Rules[64].rhs), proc_arg_list);
	insert(&(Rules[64].rhs), RPAREN);
	insert(&(Rules[64].rhs), SEMICOLON);

	//65
	Rules[65].lhs = proc_arg_list;
	insert(&(Rules[65].rhs), arg_list);

	//66
	Rules[66].lhs = proc_arg_list;
	insert(&(Rules[66].rhs), EPSILON);

	//67
	Rules[67].lhs = arg_list;
	insert(&(Rules[67].rhs), ID);
	insert(&(Rules[67].rhs), arg_list1);

	//68
	Rules[68].lhs = arg_list1;
	insert(&(Rules[68].rhs), COMMA);
	insert(&(Rules[68].rhs), arg_list);

	//69
	Rules[69].lhs = arg_list1;
	insert(&(Rules[69].rhs), LSQ);
	insert(&(Rules[69].rhs), dims);
	insert(&(Rules[69].rhs), RSQ);
	insert(&(Rules[69].rhs), arg_list2);

	//70
	Rules[70].lhs = arg_list1;
	insert(&(Rules[70].rhs), DOT);
	insert(&(Rules[70].rhs), ID);
	insert(&(Rules[70].rhs), arg_list2);

	//71
	Rules[71].lhs = arg_list1;
	insert(&(Rules[71].rhs), EPSILON);

	//72
	Rules[72].lhs = arg_list2;
	insert(&(Rules[72].rhs), COMMA);
	insert(&(Rules[72].rhs), arg_list);

	//73
	Rules[73].lhs = arg_list2;
	insert(&(Rules[73].rhs), EPSILON);

	//74
	Rules[74].lhs = loop_stmt;
	insert(&(Rules[74].rhs), LOOP);
	insert(&(Rules[74].rhs), LPAREN);
	insert(&(Rules[74].rhs), assign_list);
	insert(&(Rules[74].rhs), RPAREN);
	insert(&(Rules[74].rhs), LPAREN);
	insert(&(Rules[74].rhs), conds);
	insert(&(Rules[74].rhs), RPAREN);
	insert(&(Rules[74].rhs), LPAREN);
	insert(&(Rules[74].rhs), assign_list);
	insert(&(Rules[74].rhs), RPAREN);
	insert(&(Rules[74].rhs), COLON);
	insert(&(Rules[74].rhs), iloop_stmts);
	insert(&(Rules[74].rhs), ENDLOOP);

	//75
	Rules[75].lhs = iloop_stmts;
	insert(&(Rules[75].rhs), iloop_stmt);
	insert(&(Rules[75].rhs), iloop_stmts);

	//76
	Rules[76].lhs = iloop_stmts;
	insert(&(Rules[76].rhs), EPSILON);

	//77
	Rules[77].lhs = iloop_stmt;
	insert(&(Rules[77].rhs), stmt);

	//78
	Rules[78].lhs = iloop_stmt;
	insert(&(Rules[78].rhs), BREAK);
	insert(&(Rules[78].rhs), LPAREN);
	insert(&(Rules[78].rhs), conds);
	insert(&(Rules[78].rhs), RPAREN);
	insert(&(Rules[78].rhs), SEMICOLON);

	//79
	Rules[79].lhs = iloop_stmt;
	insert(&(Rules[79].rhs), CONTINUE);
	insert(&(Rules[79].rhs), LPAREN);
	insert(&(Rules[79].rhs), conds);
	insert(&(Rules[79].rhs), RPAREN);
	insert(&(Rules[79].rhs), SEMICOLON);

	//80
	Rules[80].lhs = assign_list;
	insert(&(Rules[80].rhs), assign_stmt);
	insert(&(Rules[80].rhs), assign_list);

	//81
	Rules[81].lhs = assign_list;
	insert(&(Rules[81].rhs), EPSILON);

	//82
	Rules[82].lhs = conds;
	insert(&(Rules[82].rhs), LPAREN);
	insert(&(Rules[82].rhs), conds);
	insert(&(Rules[82].rhs), RPAREN);
	insert(&(Rules[82].rhs), logical_op);
	insert(&(Rules[82].rhs), LPAREN);
	insert(&(Rules[82].rhs), conds);
	insert(&(Rules[82].rhs), RPAREN);

	//83
	Rules[83].lhs = conds;
	insert(&(Rules[83].rhs), elem);
	insert(&(Rules[83].rhs), rel_op);
	insert(&(Rules[83].rhs), elem);

	//84
	Rules[84].lhs = conds;
	insert(&(Rules[84].rhs), NOT);
	insert(&(Rules[84].rhs), LPAREN);
	insert(&(Rules[84].rhs), conds);
	insert(&(Rules[84].rhs), RPAREN);

	//85
	Rules[85].lhs = conds;
	insert(&(Rules[85].rhs), BOOL_LIT);

	//86
	Rules[86].lhs = logical_op;
	insert(&(Rules[86].rhs), AND);

	//87
	Rules[87].lhs = logical_op;
	insert(&(Rules[87].rhs), OR);

	//88
	Rules[88].lhs = rel_op;
	insert(&(Rules[88].rhs), LT);

	//89
	Rules[89].lhs = rel_op;
	insert(&(Rules[89].rhs), GT);

	//90
	Rules[90].lhs = rel_op;
	insert(&(Rules[90].rhs), LE);

	//91
	Rules[91].lhs = rel_op;
	insert(&(Rules[91].rhs), GE);

	//92
	Rules[92].lhs = rel_op;
	insert(&(Rules[92].rhs), EQ);

	//93
	Rules[93].lhs = rel_op;
	insert(&(Rules[93].rhs), NEQ);

	//94
	Rules[94].lhs = elem;
	insert(&(Rules[94].rhs), var);

	//95
	Rules[95].lhs = elem;
	insert(&(Rules[95].rhs), INT_LIT);

	//96
	Rules[96].lhs = elem;
	insert(&(Rules[96].rhs), REAL_LIT);

	//97
	Rules[97].lhs = elem;
	insert(&(Rules[97].rhs), CHAR_LIT);

	//98
	Rules[98].lhs = assign_stmt;
	insert(&(Rules[98].rhs), ASSIGN);
	insert(&(Rules[98].rhs), var);
	insert(&(Rules[98].rhs), ASSIGN_OP);
	insert(&(Rules[98].rhs), expr);
	insert(&(Rules[98].rhs), SEMICOLON);

	//99
	Rules[99].lhs = expr;
	insert(&(Rules[99].rhs), term);
	insert(&(Rules[99].rhs), _expr);

	//100
	Rules[100].lhs = _expr;
	insert(&(Rules[100].rhs), op_PlusMinus);
	insert(&(Rules[100].rhs), term);
	insert(&(Rules[100].rhs), _expr);

	//101
	Rules[101].lhs = _expr;
	insert(&(Rules[101].rhs), EPSILON);

	//102
	Rules[102].lhs = term;
	insert(&(Rules[102].rhs), expo_term);
	insert(&(Rules[102].rhs), _term);

	//103
	Rules[103].lhs = _term;
	insert(&(Rules[103].rhs), op_mulDivMod);
	insert(&(Rules[103].rhs), expo_term);
	insert(&(Rules[103].rhs), _term);

	//104
	Rules[104].lhs = _term;
	insert(&(Rules[104].rhs), EPSILON);

	//105
	Rules[105].lhs = expo_term;
	insert(&(Rules[105].rhs), factor);
	insert(&(Rules[105].rhs), _expo_term);

	//106
	Rules[106].lhs = _expo_term;
	insert(&(Rules[106].rhs), op_pow);
	insert(&(Rules[106].rhs), factor);
	insert(&(Rules[106].rhs), _expo_term);

	//107
	Rules[107].lhs = _expo_term;
	insert(&(Rules[107].rhs), EPSILON);

	//108
	Rules[108].lhs = factor;
	insert(&(Rules[108].rhs), LPAREN);
	insert(&(Rules[108].rhs), expr);
	insert(&(Rules[108].rhs), RPAREN);

	//109
	Rules[109].lhs = factor;
	insert(&(Rules[109].rhs), var);

	//110
	Rules[110].lhs = factor;
	insert(&(Rules[110].rhs), const_);

	//111
	Rules[111].lhs = factor;
	insert(&(Rules[111].rhs), MINUS);
	insert(&(Rules[111].rhs), LPAREN);
	insert(&(Rules[111].rhs), expr);
	insert(&(Rules[111].rhs), RPAREN);

	//112
	Rules[112].lhs = op_PlusMinus;
	insert(&(Rules[112].rhs), PLUS);

	//113
	Rules[113].lhs = op_PlusMinus;
	insert(&(Rules[113].rhs), MINUS);

	//114
	Rules[114].lhs = op_mulDivMod;
	insert(&(Rules[114].rhs), MUL);

	//115
	Rules[115].lhs = op_mulDivMod;
	insert(&(Rules[115].rhs), DIV);

	//116
	Rules[116].lhs = op_mulDivMod;
	insert(&(Rules[116].rhs), MOD);

	//117
	Rules[117].lhs = op_pow;
	insert(&(Rules[117].rhs), POW);

	//118
	Rules[118].lhs = mat_assign_stmt;
	insert(&(Rules[118].rhs), MATASSIGN);
	insert(&(Rules[118].rhs), ID);
	insert(&(Rules[118].rhs), ASSIGN_OP);
	insert(&(Rules[118].rhs), mat_stmt);

	//119
	Rules[119].lhs = mat_stmt;
	insert(&(Rules[119].rhs), LCURL);
	insert(&(Rules[119].rhs), row_list);
	insert(&(Rules[119].rhs), RCURL);
	insert(&(Rules[119].rhs), SEMICOLON);

	//120
	Rules[120].lhs = mat_stmt;
	insert(&(Rules[120].rhs), ID);
	insert(&(Rules[120].rhs), _mat_stmt);

	//121
	Rules[121].lhs = _mat_stmt;
	insert(&(Rules[121].rhs), PLUS);
	insert(&(Rules[121].rhs), ID);
	insert(&(Rules[121].rhs), SEMICOLON);

	//122
	Rules[122].lhs = _mat_stmt;
	insert(&(Rules[122].rhs), MAT_ROWS);
	insert(&(Rules[122].rhs), SEMICOLON);

	//123
	Rules[123].lhs = _mat_stmt;
	insert(&(Rules[123].rhs), MAT_COLS);
	insert(&(Rules[123].rhs), SEMICOLON);

	//124
	Rules[124].lhs = row_list;
	insert(&(Rules[124].rhs), row);
	insert(&(Rules[124].rhs), _row_list);

	//125
	Rules[125].lhs = _row_list;
	insert(&(Rules[125].rhs), SEMICOLON);
	insert(&(Rules[125].rhs), row);
	insert(&(Rules[125].rhs), _row_list);

	//126
	Rules[126].lhs = _row_list;
	insert(&(Rules[126].rhs), EPSILON);

	//127
	Rules[127].lhs = row;
	insert(&(Rules[127].rhs), const_);
	insert(&(Rules[127].rhs), _row);

	//128
	Rules[128].lhs = _row;
	insert(&(Rules[128].rhs), COMMA);
	insert(&(Rules[128].rhs), const_);
	insert(&(Rules[128].rhs), _row);

	//129
	Rules[129].lhs = _row;
	insert(&(Rules[129].rhs), EPSILON);

	//130
	Rules[130].lhs = const_;
	insert(&(Rules[130].rhs), INT_LIT);

	//131
	Rules[131].lhs = const_;
	insert(&(Rules[131].rhs), REAL_LIT);

	//132
	Rules[132].lhs = const_;
	insert(&(Rules[132].rhs), BOOL_LIT);

	//133
	Rules[133].lhs = const_;
	insert(&(Rules[133].rhs), CHAR_LIT);

	//134
	Rules[134].lhs = str_assign_stmt;
	insert(&(Rules[134].rhs), STRASSIGN);
	insert(&(Rules[134].rhs), ID);
	insert(&(Rules[134].rhs), ASSIGN_OP);
	insert(&(Rules[134].rhs), str_stmt);

	//135
	Rules[135].lhs = str_stmt;
	insert(&(Rules[135].rhs), STR_LIT);
	insert(&(Rules[135].rhs), SEMICOLON);

	//136
	Rules[136].lhs = str_stmt;
	insert(&(Rules[136].rhs), ID);
	insert(&(Rules[136].rhs), _str_stmt);

	//137
	Rules[137].lhs = _str_stmt;
	insert(&(Rules[137].rhs), SEMICOLON);

	//138
	Rules[138].lhs = _str_stmt;
	insert(&(Rules[138].rhs), PLUS);
	insert(&(Rules[138].rhs), ID);
	insert(&(Rules[138].rhs), SEMICOLON);

	//139
	Rules[139].lhs = _str_stmt;
	insert(&(Rules[139].rhs), LSQ);
	insert(&(Rules[139].rhs), ind);
	insert(&(Rules[139].rhs), RSQ);
	insert(&(Rules[139].rhs), SEMICOLON);

	//140
	Rules[140].lhs = _str_stmt;
	insert(&(Rules[140].rhs), STR_LENGTH);
	insert(&(Rules[140].rhs), SEMICOLON);

	//141
	Rules[141].lhs = ind;
	insert(&(Rules[141].rhs), ID);

	//142
	Rules[142].lhs = ind;
	insert(&(Rules[142].rhs), INT_LIT);

	return Rules;

}

Node** getFollowSet() {
	Node **followSet = (Node**)calloc(NUM_NONTERM + 1, sizeof(Node*));
	int i;
	for (i = 0; i <= NUM_NONTERM; i++) followSet[i] = NULL;
	insert(&followSet[INDEX(program)], DOLLAR);

	insert(&followSet[INDEX(execute)], DOLLAR);

	insert(&followSet[INDEX(_records)], EXECUTE);
	insert(&followSet[INDEX(_records)], PROCS);

	insert(&followSet[INDEX(records)], EXECUTE);
	insert(&followSet[INDEX(records)], PROCS);

	insert(&followSet[INDEX(recs)], ENDRECORDS);

	insert(&followSet[INDEX(_recs)], ENDRECORDS);

	insert(&followSet[INDEX(rec)], REC);
	insert(&followSet[INDEX(rec)], ENDRECORDS);

	insert(&followSet[INDEX(_procedures)], EXECUTE);

	insert(&followSet[INDEX(procedures)], EXECUTE);

	insert(&followSet[INDEX(procs)], ENDPROCS);

	insert(&followSet[INDEX(_procs)], ENDPROCS);

	insert(&followSet[INDEX(proc)], PROC);
	insert(&followSet[INDEX(proc)], ENDPROCS);

	insert(&followSet[INDEX(param_list)], RPAREN);

	insert(&followSet[INDEX(_param_list)], RPAREN);

	insert(&followSet[INDEX(stmts)], ENDIF);
	insert(&followSet[INDEX(proc)], ELIF);
	insert(&followSet[INDEX(proc)], LPAREN);
	insert(&followSet[INDEX(proc)], NOT);
	insert(&followSet[INDEX(proc)], BOOL_LIT);
	insert(&followSet[INDEX(proc)], INT_LIT);
	insert(&followSet[INDEX(proc)], REAL_LIT);
	insert(&followSet[INDEX(proc)], CHAR_LIT);
	insert(&followSet[INDEX(proc)], ID);
	insert(&followSet[INDEX(proc)], ENDPROC);
	insert(&followSet[INDEX(proc)], END);
	insert(&followSet[INDEX(proc)], ELSE);

	insert(&followSet[INDEX(_stmts)], ENDIF);
	insert(&followSet[INDEX(_stmts)], ELIF);
	insert(&followSet[INDEX(_stmts)], LPAREN);
	insert(&followSet[INDEX(_stmts)], NOT);
	insert(&followSet[INDEX(_stmts)], BOOL_LIT);
	insert(&followSet[INDEX(_stmts)], INT_LIT);
	insert(&followSet[INDEX(_stmts)], REAL_LIT);
	insert(&followSet[INDEX(_stmts)], CHAR_LIT);
	insert(&followSet[INDEX(_stmts)], ID);
	insert(&followSet[INDEX(_stmts)], ENDPROC);
	insert(&followSet[INDEX(_stmts)], END);
	insert(&followSet[INDEX(_stmts)], ELSE);

	insert(&followSet[INDEX(stmt)], STRING);
	insert(&followSet[INDEX(stmt)], MAT);
	insert(&followSet[INDEX(stmt)], REC);
	insert(&followSet[INDEX(stmt)], INT);
	insert(&followSet[INDEX(stmt)], REAL);
	insert(&followSet[INDEX(stmt)], BOOL);
	insert(&followSet[INDEX(stmt)], CHAR);
	insert(&followSet[INDEX(stmt)], LOOP);
	insert(&followSet[INDEX(stmt)], ASSIGN);
	insert(&followSet[INDEX(stmt)], MATASSIGN);
	insert(&followSet[INDEX(stmt)], IF);
	insert(&followSet[INDEX(stmt)], GET);
	insert(&followSet[INDEX(stmt)], PUT);
	insert(&followSet[INDEX(stmt)], CALL);
	insert(&followSet[INDEX(stmt)], STRASSIGN);
	insert(&followSet[INDEX(stmt)], BREAK);
	insert(&followSet[INDEX(stmt)], CONTINUE);
	insert(&followSet[INDEX(stmt)], ENDIF);
	insert(&followSet[INDEX(stmt)], ELIF);
	insert(&followSet[INDEX(stmt)], LPAREN);
	insert(&followSet[INDEX(stmt)], NOT);
	insert(&followSet[INDEX(stmt)], BOOL_LIT);
	insert(&followSet[INDEX(stmt)], INT_LIT);
	insert(&followSet[INDEX(stmt)], REAL_LIT);
	insert(&followSet[INDEX(stmt)], CHAR_LIT);
	insert(&followSet[INDEX(stmt)], ID);
	insert(&followSet[INDEX(stmt)], ENDPROC);
	insert(&followSet[INDEX(stmt)], END);
	insert(&followSet[INDEX(stmt)], ELSE);
	insert(&followSet[INDEX(stmt)], ENDLOOP);

	insert(&followSet[INDEX(decl_stmts)], ENDREC);

	insert(&followSet[INDEX(_decl_stmts)], ENDREC);

	insert(&followSet[INDEX(decl_stmt)], STRING);
	insert(&followSet[INDEX(decl_stmt)], MAT);
	insert(&followSet[INDEX(decl_stmt)], REC);
	insert(&followSet[INDEX(decl_stmt)], INT);
	insert(&followSet[INDEX(decl_stmt)], REAL);
	insert(&followSet[INDEX(decl_stmt)], BOOL);
	insert(&followSet[INDEX(decl_stmt)], CHAR);
	insert(&followSet[INDEX(decl_stmt)], ENDREC);
	insert(&followSet[INDEX(decl_stmt)], LOOP);
	insert(&followSet[INDEX(decl_stmt)], ASSIGN);
	insert(&followSet[INDEX(decl_stmt)], MATASSIGN);
	insert(&followSet[INDEX(decl_stmt)], IF);
	insert(&followSet[INDEX(decl_stmt)], GET);
	insert(&followSet[INDEX(decl_stmt)], PUT);
	insert(&followSet[INDEX(decl_stmt)], CALL);
	insert(&followSet[INDEX(decl_stmt)], STRASSIGN);
	insert(&followSet[INDEX(decl_stmt)], BREAK);
	insert(&followSet[INDEX(decl_stmt)], CONTINUE);
	insert(&followSet[INDEX(decl_stmt)], ENDIF);
	insert(&followSet[INDEX(decl_stmt)], ELIF);
	insert(&followSet[INDEX(decl_stmt)], LPAREN);
	insert(&followSet[INDEX(decl_stmt)], NOT);
	insert(&followSet[INDEX(decl_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(decl_stmt)], INT_LIT);
	insert(&followSet[INDEX(decl_stmt)], REAL_LIT);
	insert(&followSet[INDEX(decl_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(decl_stmt)], ID);
	insert(&followSet[INDEX(decl_stmt)], ENDPROC);
	insert(&followSet[INDEX(decl_stmt)], END);
	insert(&followSet[INDEX(decl_stmt)], ELSE);
	insert(&followSet[INDEX(decl_stmt)], ENDLOOP);

	insert(&followSet[INDEX(type)], ID);

	insert(&followSet[INDEX(basic_type)], GT);
	insert(&followSet[INDEX(basic_type)], ID);

	insert(&followSet[INDEX(id_list)], SEMICOLON);

	insert(&followSet[INDEX(_id_list)], SEMICOLON);

	insert(&followSet[INDEX(dims)], RSQ);

	insert(&followSet[INDEX(_dim_list)], RSQ);

	insert(&followSet[INDEX(cond_stmt)], STRING);
	insert(&followSet[INDEX(cond_stmt)], MAT);
	insert(&followSet[INDEX(cond_stmt)], REC);
	insert(&followSet[INDEX(cond_stmt)], INT);
	insert(&followSet[INDEX(cond_stmt)], REAL);
	insert(&followSet[INDEX(cond_stmt)], BOOL);
	insert(&followSet[INDEX(cond_stmt)], CHAR);
	insert(&followSet[INDEX(cond_stmt)], LOOP);
	insert(&followSet[INDEX(cond_stmt)], ASSIGN);
	insert(&followSet[INDEX(cond_stmt)], MATASSIGN);
	insert(&followSet[INDEX(cond_stmt)], IF);
	insert(&followSet[INDEX(cond_stmt)], GET);
	insert(&followSet[INDEX(cond_stmt)], PUT);
	insert(&followSet[INDEX(cond_stmt)], CALL);
	insert(&followSet[INDEX(cond_stmt)], STRASSIGN);
	insert(&followSet[INDEX(cond_stmt)], BREAK);
	insert(&followSet[INDEX(cond_stmt)], CONTINUE);
	insert(&followSet[INDEX(cond_stmt)], ENDIF);
	insert(&followSet[INDEX(cond_stmt)], ELIF);
	insert(&followSet[INDEX(cond_stmt)], LPAREN);
	insert(&followSet[INDEX(cond_stmt)], NOT);
	insert(&followSet[INDEX(cond_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(cond_stmt)], INT_LIT);
	insert(&followSet[INDEX(cond_stmt)], REAL_LIT);
	insert(&followSet[INDEX(cond_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(cond_stmt)], ID);
	insert(&followSet[INDEX(cond_stmt)], ENDPROC);
	insert(&followSet[INDEX(cond_stmt)], END);
	insert(&followSet[INDEX(cond_stmt)], ELSE);
	insert(&followSet[INDEX(cond_stmt)], ENDLOOP);

	insert(&followSet[INDEX(else_if)], ELSE);
	insert(&followSet[INDEX(else_if)], ENDIF);

	insert(&followSet[INDEX(_cond_stmt)], STRING);
	insert(&followSet[INDEX(_cond_stmt)], MAT);
	insert(&followSet[INDEX(_cond_stmt)], REC);
	insert(&followSet[INDEX(_cond_stmt)], INT);
	insert(&followSet[INDEX(_cond_stmt)], REAL);
	insert(&followSet[INDEX(_cond_stmt)], BOOL);
	insert(&followSet[INDEX(_cond_stmt)], CHAR);
	insert(&followSet[INDEX(_cond_stmt)], LOOP);
	insert(&followSet[INDEX(_cond_stmt)], ASSIGN);
	insert(&followSet[INDEX(_cond_stmt)], MATASSIGN);
	insert(&followSet[INDEX(_cond_stmt)], IF);
	insert(&followSet[INDEX(_cond_stmt)], GET);
	insert(&followSet[INDEX(_cond_stmt)], PUT);
	insert(&followSet[INDEX(_cond_stmt)], CALL);
	insert(&followSet[INDEX(_cond_stmt)], STRASSIGN);
	insert(&followSet[INDEX(_cond_stmt)], BREAK);
	insert(&followSet[INDEX(_cond_stmt)], CONTINUE);
	insert(&followSet[INDEX(_cond_stmt)], ENDIF);
	insert(&followSet[INDEX(_cond_stmt)], ELIF);
	insert(&followSet[INDEX(_cond_stmt)], LPAREN);
	insert(&followSet[INDEX(_cond_stmt)], NOT);
	insert(&followSet[INDEX(_cond_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(_cond_stmt)], INT_LIT);
	insert(&followSet[INDEX(_cond_stmt)], REAL_LIT);
	insert(&followSet[INDEX(_cond_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(_cond_stmt)], ID);
	insert(&followSet[INDEX(_cond_stmt)], ENDPROC);
	insert(&followSet[INDEX(_cond_stmt)], END);
	insert(&followSet[INDEX(_cond_stmt)], ELSE);
	insert(&followSet[INDEX(_cond_stmt)], ENDLOOP);

	insert(&followSet[INDEX(io_stmt)], STRING);
	insert(&followSet[INDEX(io_stmt)], MAT);
	insert(&followSet[INDEX(io_stmt)], REC);
	insert(&followSet[INDEX(io_stmt)], INT);
	insert(&followSet[INDEX(io_stmt)], REAL);
	insert(&followSet[INDEX(io_stmt)], BOOL);
	insert(&followSet[INDEX(io_stmt)], CHAR);
	insert(&followSet[INDEX(io_stmt)], LOOP);
	insert(&followSet[INDEX(io_stmt)], ASSIGN);
	insert(&followSet[INDEX(io_stmt)], MATASSIGN);
	insert(&followSet[INDEX(io_stmt)], IF);
	insert(&followSet[INDEX(io_stmt)], GET);
	insert(&followSet[INDEX(io_stmt)], PUT);
	insert(&followSet[INDEX(io_stmt)], CALL);
	insert(&followSet[INDEX(io_stmt)], STRASSIGN);
	insert(&followSet[INDEX(io_stmt)], BREAK);
	insert(&followSet[INDEX(io_stmt)], CONTINUE);
	insert(&followSet[INDEX(io_stmt)], ENDIF);
	insert(&followSet[INDEX(io_stmt)], ELIF);
	insert(&followSet[INDEX(io_stmt)], LPAREN);
	insert(&followSet[INDEX(io_stmt)], NOT);
	insert(&followSet[INDEX(io_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(io_stmt)], INT_LIT);
	insert(&followSet[INDEX(io_stmt)], REAL_LIT);
	insert(&followSet[INDEX(io_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(io_stmt)], ID);
	insert(&followSet[INDEX(io_stmt)], ENDPROC);
	insert(&followSet[INDEX(io_stmt)], END);
	insert(&followSet[INDEX(io_stmt)], ELSE);
	insert(&followSet[INDEX(io_stmt)], ENDLOOP);

	insert(&followSet[INDEX(put_param)], RPAREN);

	insert(&followSet[INDEX(var)], ASSIGN_OP);
	insert(&followSet[INDEX(var)], RPAREN);
	insert(&followSet[INDEX(var)], POW);
	insert(&followSet[INDEX(var)], LT);
	insert(&followSet[INDEX(var)], GT);
	insert(&followSet[INDEX(var)], LE);
	insert(&followSet[INDEX(var)], GE);
	insert(&followSet[INDEX(var)], EQ);
	insert(&followSet[INDEX(var)], NEQ);
	insert(&followSet[INDEX(var)], MUL);
	insert(&followSet[INDEX(var)], DIV);
	insert(&followSet[INDEX(var)], MOD);
	insert(&followSet[INDEX(var)], PLUS);
	insert(&followSet[INDEX(var)], MINUS);
	insert(&followSet[INDEX(var)], SEMICOLON);

	insert(&followSet[INDEX(_var)], ASSIGN_OP);
	insert(&followSet[INDEX(_var)], RPAREN);
	insert(&followSet[INDEX(_var)], POW);
	insert(&followSet[INDEX(_var)], LT);
	insert(&followSet[INDEX(_var)], GT);
	insert(&followSet[INDEX(_var)], LE);
	insert(&followSet[INDEX(_var)], GE);
	insert(&followSet[INDEX(_var)], EQ);
	insert(&followSet[INDEX(_var)], NEQ);
	insert(&followSet[INDEX(_var)], MUL);
	insert(&followSet[INDEX(_var)], DIV);
	insert(&followSet[INDEX(_var)], MOD);
	insert(&followSet[INDEX(_var)], PLUS);
	insert(&followSet[INDEX(_var)], MINUS);
	insert(&followSet[INDEX(_var)], SEMICOLON);

	insert(&followSet[INDEX(proc_call_stmt)], STRING);
	insert(&followSet[INDEX(proc_call_stmt)], MAT);
	insert(&followSet[INDEX(proc_call_stmt)], REC);
	insert(&followSet[INDEX(proc_call_stmt)], INT);
	insert(&followSet[INDEX(proc_call_stmt)], REAL);
	insert(&followSet[INDEX(proc_call_stmt)], BOOL);
	insert(&followSet[INDEX(proc_call_stmt)], CHAR);
	insert(&followSet[INDEX(proc_call_stmt)], LOOP);
	insert(&followSet[INDEX(proc_call_stmt)], ASSIGN);
	insert(&followSet[INDEX(proc_call_stmt)], MATASSIGN);
	insert(&followSet[INDEX(proc_call_stmt)], IF);
	insert(&followSet[INDEX(proc_call_stmt)], GET);
	insert(&followSet[INDEX(proc_call_stmt)], PUT);
	insert(&followSet[INDEX(proc_call_stmt)], CALL);
	insert(&followSet[INDEX(proc_call_stmt)], STRASSIGN);
	insert(&followSet[INDEX(proc_call_stmt)], BREAK);
	insert(&followSet[INDEX(proc_call_stmt)], CONTINUE);
	insert(&followSet[INDEX(proc_call_stmt)], ENDIF);
	insert(&followSet[INDEX(proc_call_stmt)], ELIF);
	insert(&followSet[INDEX(proc_call_stmt)], LPAREN);
	insert(&followSet[INDEX(proc_call_stmt)], NOT);
	insert(&followSet[INDEX(proc_call_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(proc_call_stmt)], INT_LIT);
	insert(&followSet[INDEX(proc_call_stmt)], REAL_LIT);
	insert(&followSet[INDEX(proc_call_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(proc_call_stmt)], ID);
	insert(&followSet[INDEX(proc_call_stmt)], ENDPROC);
	insert(&followSet[INDEX(proc_call_stmt)], END);
	insert(&followSet[INDEX(proc_call_stmt)], ELSE);
	insert(&followSet[INDEX(proc_call_stmt)], ENDLOOP);

	insert(&followSet[INDEX(proc_arg_list)], RPAREN);

	insert(&followSet[INDEX(arg_list)], RPAREN);

	insert(&followSet[INDEX(arg_list1)], RPAREN);

	insert(&followSet[INDEX(arg_list2)], RPAREN);

	insert(&followSet[INDEX(loop_stmt)], STRING);
	insert(&followSet[INDEX(loop_stmt)], MAT);
	insert(&followSet[INDEX(loop_stmt)], REC);
	insert(&followSet[INDEX(loop_stmt)], INT);
	insert(&followSet[INDEX(loop_stmt)], REAL);
	insert(&followSet[INDEX(loop_stmt)], BOOL);
	insert(&followSet[INDEX(loop_stmt)], CHAR);
	insert(&followSet[INDEX(loop_stmt)], LOOP);
	insert(&followSet[INDEX(loop_stmt)], ASSIGN);
	insert(&followSet[INDEX(loop_stmt)], MATASSIGN);
	insert(&followSet[INDEX(loop_stmt)], IF);
	insert(&followSet[INDEX(loop_stmt)], GET);
	insert(&followSet[INDEX(loop_stmt)], PUT);
	insert(&followSet[INDEX(loop_stmt)], CALL);
	insert(&followSet[INDEX(loop_stmt)], STRASSIGN);
	insert(&followSet[INDEX(loop_stmt)], BREAK);
	insert(&followSet[INDEX(loop_stmt)], CONTINUE);
	insert(&followSet[INDEX(loop_stmt)], ENDIF);
	insert(&followSet[INDEX(loop_stmt)], ELIF);
	insert(&followSet[INDEX(loop_stmt)], LPAREN);
	insert(&followSet[INDEX(loop_stmt)], NOT);
	insert(&followSet[INDEX(loop_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(loop_stmt)], INT_LIT);
	insert(&followSet[INDEX(loop_stmt)], REAL_LIT);
	insert(&followSet[INDEX(loop_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(loop_stmt)], ID);
	insert(&followSet[INDEX(loop_stmt)], ENDPROC);
	insert(&followSet[INDEX(loop_stmt)], END);
	insert(&followSet[INDEX(loop_stmt)], ELSE);
	insert(&followSet[INDEX(loop_stmt)], ENDLOOP);

	insert(&followSet[INDEX(iloop_stmts)], ENDLOOP);

	insert(&followSet[INDEX(iloop_stmt)], BREAK);
	insert(&followSet[INDEX(iloop_stmt)], CONTINUE);
	insert(&followSet[INDEX(iloop_stmt)], STRING);
	insert(&followSet[INDEX(iloop_stmt)], MAT);
	insert(&followSet[INDEX(iloop_stmt)], REC);
	insert(&followSet[INDEX(iloop_stmt)], INT);
	insert(&followSet[INDEX(iloop_stmt)], REAL);
	insert(&followSet[INDEX(iloop_stmt)], BOOL);
	insert(&followSet[INDEX(iloop_stmt)], CHAR);
	insert(&followSet[INDEX(iloop_stmt)], LOOP);
	insert(&followSet[INDEX(iloop_stmt)], ASSIGN);
	insert(&followSet[INDEX(iloop_stmt)], MATASSIGN);
	insert(&followSet[INDEX(iloop_stmt)], IF);
	insert(&followSet[INDEX(iloop_stmt)], GET);
	insert(&followSet[INDEX(iloop_stmt)], PUT);
	insert(&followSet[INDEX(iloop_stmt)], CALL);
	insert(&followSet[INDEX(iloop_stmt)], STRASSIGN);
	insert(&followSet[INDEX(iloop_stmt)], ENDLOOP);

	insert(&followSet[INDEX(assign_list)], RPAREN);

	insert(&followSet[INDEX(conds)], RPAREN);

	insert(&followSet[INDEX(logical_op)], LPAREN);

	insert(&followSet[INDEX(rel_op)], INT_LIT);
	insert(&followSet[INDEX(rel_op)], REAL_LIT);
	insert(&followSet[INDEX(rel_op)], CHAR_LIT);
	insert(&followSet[INDEX(rel_op)], ID);

	insert(&followSet[INDEX(elem)], LT);
	insert(&followSet[INDEX(elem)], GT);
	insert(&followSet[INDEX(elem)], LE);
	insert(&followSet[INDEX(elem)], GE);
	insert(&followSet[INDEX(elem)], EQ);
	insert(&followSet[INDEX(elem)], NEQ);
	insert(&followSet[INDEX(elem)], RPAREN);

	insert(&followSet[INDEX(assign_stmt)], ASSIGN);
	insert(&followSet[INDEX(assign_stmt)], RPAREN);
	insert(&followSet[INDEX(assign_stmt)], STRING);
	insert(&followSet[INDEX(assign_stmt)], MAT);
	insert(&followSet[INDEX(assign_stmt)], REC);
	insert(&followSet[INDEX(assign_stmt)], INT);
	insert(&followSet[INDEX(assign_stmt)], REAL);
	insert(&followSet[INDEX(assign_stmt)], BOOL);
	insert(&followSet[INDEX(assign_stmt)], CHAR);
	insert(&followSet[INDEX(assign_stmt)], LOOP);
	insert(&followSet[INDEX(assign_stmt)], MATASSIGN);
	insert(&followSet[INDEX(assign_stmt)], IF);
	insert(&followSet[INDEX(assign_stmt)], GET);
	insert(&followSet[INDEX(assign_stmt)], PUT);
	insert(&followSet[INDEX(assign_stmt)], CALL);
	insert(&followSet[INDEX(assign_stmt)], STRASSIGN);
	insert(&followSet[INDEX(assign_stmt)], BREAK);
	insert(&followSet[INDEX(assign_stmt)], CONTINUE);
	insert(&followSet[INDEX(assign_stmt)], ENDIF);
	insert(&followSet[INDEX(assign_stmt)], ELIF);
	insert(&followSet[INDEX(assign_stmt)], LPAREN);
	insert(&followSet[INDEX(assign_stmt)], NOT);
	insert(&followSet[INDEX(assign_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(assign_stmt)], INT_LIT);
	insert(&followSet[INDEX(assign_stmt)], REAL_LIT);
	insert(&followSet[INDEX(assign_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(assign_stmt)], ID);
	insert(&followSet[INDEX(assign_stmt)], ENDPROC);
	insert(&followSet[INDEX(assign_stmt)], END);
	insert(&followSet[INDEX(assign_stmt)], ELSE);
	insert(&followSet[INDEX(assign_stmt)], ENDLOOP);

	insert(&followSet[INDEX(expr)], RPAREN);
	insert(&followSet[INDEX(expr)], SEMICOLON);

	insert(&followSet[INDEX(_expr)], RPAREN);
	insert(&followSet[INDEX(_expr)], SEMICOLON);

	insert(&followSet[INDEX(term)], PLUS);
	insert(&followSet[INDEX(term)], MINUS);
	insert(&followSet[INDEX(term)], RPAREN);
	insert(&followSet[INDEX(term)], SEMICOLON);

	insert(&followSet[INDEX(_term)], PLUS);
	insert(&followSet[INDEX(_term)], MINUS);
	insert(&followSet[INDEX(_term)], RPAREN);
	insert(&followSet[INDEX(_term)], SEMICOLON);

	insert(&followSet[INDEX(expo_term)], MUL);
	insert(&followSet[INDEX(expo_term)], DIV);
	insert(&followSet[INDEX(expo_term)], MOD);
	insert(&followSet[INDEX(expo_term)], PLUS);
	insert(&followSet[INDEX(expo_term)], MINUS);
	insert(&followSet[INDEX(expo_term)], RPAREN);
	insert(&followSet[INDEX(expo_term)], SEMICOLON);

	insert(&followSet[INDEX(_expo_term)], MUL);
	insert(&followSet[INDEX(_expo_term)], DIV);
	insert(&followSet[INDEX(_expo_term)], MOD);
	insert(&followSet[INDEX(_expo_term)], PLUS);
	insert(&followSet[INDEX(_expo_term)], MINUS);
	insert(&followSet[INDEX(_expo_term)], RPAREN);
	insert(&followSet[INDEX(_expo_term)], SEMICOLON);

	insert(&followSet[INDEX(factor)], POW);
	insert(&followSet[INDEX(factor)], MUL);
	insert(&followSet[INDEX(factor)], DIV);
	insert(&followSet[INDEX(factor)], MOD);
	insert(&followSet[INDEX(factor)], PLUS);
	insert(&followSet[INDEX(factor)], MINUS);
	insert(&followSet[INDEX(factor)], RPAREN);
	insert(&followSet[INDEX(factor)], SEMICOLON);

	insert(&followSet[INDEX(op_PlusMinus)], LPAREN);
	insert(&followSet[INDEX(op_PlusMinus)], MINUS);
	insert(&followSet[INDEX(op_PlusMinus)], ID);
	insert(&followSet[INDEX(op_PlusMinus)], INT_LIT);
	insert(&followSet[INDEX(op_PlusMinus)], REAL_LIT);
	insert(&followSet[INDEX(op_PlusMinus)], BOOL_LIT);
	insert(&followSet[INDEX(op_PlusMinus)], CHAR_LIT);

	insert(&followSet[INDEX(op_mulDivMod)], LPAREN);
	insert(&followSet[INDEX(op_mulDivMod)], MINUS);
	insert(&followSet[INDEX(op_mulDivMod)], ID);
	insert(&followSet[INDEX(op_mulDivMod)], INT_LIT);
	insert(&followSet[INDEX(op_mulDivMod)], REAL_LIT);
	insert(&followSet[INDEX(op_mulDivMod)], BOOL_LIT);
	insert(&followSet[INDEX(op_mulDivMod)], CHAR_LIT);

	insert(&followSet[INDEX(op_pow)], LPAREN);
	insert(&followSet[INDEX(op_pow)], MINUS);
	insert(&followSet[INDEX(op_pow)], ID);
	insert(&followSet[INDEX(op_pow)], INT_LIT);
	insert(&followSet[INDEX(op_pow)], REAL_LIT);
	insert(&followSet[INDEX(op_pow)], BOOL_LIT);
	insert(&followSet[INDEX(op_pow)], CHAR_LIT);

	insert(&followSet[INDEX(mat_assign_stmt)], STRING);
	insert(&followSet[INDEX(mat_assign_stmt)], MAT);
	insert(&followSet[INDEX(mat_assign_stmt)], REC);
	insert(&followSet[INDEX(mat_assign_stmt)], INT);
	insert(&followSet[INDEX(mat_assign_stmt)], REAL);
	insert(&followSet[INDEX(mat_assign_stmt)], BOOL);
	insert(&followSet[INDEX(mat_assign_stmt)], CHAR);
	insert(&followSet[INDEX(mat_assign_stmt)], LOOP);
	insert(&followSet[INDEX(mat_assign_stmt)], ASSIGN);
	insert(&followSet[INDEX(mat_assign_stmt)], MATASSIGN);
	insert(&followSet[INDEX(mat_assign_stmt)], IF);
	insert(&followSet[INDEX(mat_assign_stmt)], GET);
	insert(&followSet[INDEX(mat_assign_stmt)], PUT);
	insert(&followSet[INDEX(mat_assign_stmt)], CALL);
	insert(&followSet[INDEX(mat_assign_stmt)], STRASSIGN);
	insert(&followSet[INDEX(mat_assign_stmt)], BREAK);
	insert(&followSet[INDEX(mat_assign_stmt)], CONTINUE);
	insert(&followSet[INDEX(mat_assign_stmt)], ENDIF);
	insert(&followSet[INDEX(mat_assign_stmt)], ELIF);
	insert(&followSet[INDEX(mat_assign_stmt)], LPAREN);
	insert(&followSet[INDEX(mat_assign_stmt)], NOT);
	insert(&followSet[INDEX(mat_assign_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(mat_assign_stmt)], INT_LIT);
	insert(&followSet[INDEX(mat_assign_stmt)], REAL_LIT);
	insert(&followSet[INDEX(mat_assign_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(mat_assign_stmt)], ID);
	insert(&followSet[INDEX(mat_assign_stmt)], ENDPROC);
	insert(&followSet[INDEX(mat_assign_stmt)], END);
	insert(&followSet[INDEX(mat_assign_stmt)], ELSE);
	insert(&followSet[INDEX(mat_assign_stmt)], ENDLOOP);

	insert(&followSet[INDEX(mat_stmt)], STRING);
	insert(&followSet[INDEX(mat_stmt)], MAT);
	insert(&followSet[INDEX(mat_stmt)], REC);
	insert(&followSet[INDEX(mat_stmt)], INT);
	insert(&followSet[INDEX(mat_stmt)], REAL);
	insert(&followSet[INDEX(mat_stmt)], BOOL);
	insert(&followSet[INDEX(mat_stmt)], CHAR);
	insert(&followSet[INDEX(mat_stmt)], LOOP);
	insert(&followSet[INDEX(mat_stmt)], ASSIGN);
	insert(&followSet[INDEX(mat_stmt)], MATASSIGN);
	insert(&followSet[INDEX(mat_stmt)], IF);
	insert(&followSet[INDEX(mat_stmt)], GET);
	insert(&followSet[INDEX(mat_stmt)], PUT);
	insert(&followSet[INDEX(mat_stmt)], CALL);
	insert(&followSet[INDEX(mat_stmt)], STRASSIGN);
	insert(&followSet[INDEX(mat_stmt)], BREAK);
	insert(&followSet[INDEX(mat_stmt)], CONTINUE);
	insert(&followSet[INDEX(mat_stmt)], ENDIF);
	insert(&followSet[INDEX(mat_stmt)], ELIF);
	insert(&followSet[INDEX(mat_stmt)], LPAREN);
	insert(&followSet[INDEX(mat_stmt)], NOT);
	insert(&followSet[INDEX(mat_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(mat_stmt)], INT_LIT);
	insert(&followSet[INDEX(mat_stmt)], REAL_LIT);
	insert(&followSet[INDEX(mat_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(mat_stmt)], ID);
	insert(&followSet[INDEX(mat_stmt)], ENDPROC);
	insert(&followSet[INDEX(mat_stmt)], END);
	insert(&followSet[INDEX(mat_stmt)], ELSE);
	insert(&followSet[INDEX(mat_stmt)], ENDLOOP);

	insert(&followSet[INDEX(_mat_stmt)], STRING);
	insert(&followSet[INDEX(_mat_stmt)], MAT);
	insert(&followSet[INDEX(_mat_stmt)], REC);
	insert(&followSet[INDEX(_mat_stmt)], INT);
	insert(&followSet[INDEX(_mat_stmt)], REAL);
	insert(&followSet[INDEX(_mat_stmt)], BOOL);
	insert(&followSet[INDEX(_mat_stmt)], CHAR);
	insert(&followSet[INDEX(_mat_stmt)], LOOP);
	insert(&followSet[INDEX(_mat_stmt)], ASSIGN);
	insert(&followSet[INDEX(_mat_stmt)], MATASSIGN);
	insert(&followSet[INDEX(_mat_stmt)], IF);
	insert(&followSet[INDEX(_mat_stmt)], GET);
	insert(&followSet[INDEX(_mat_stmt)], PUT);
	insert(&followSet[INDEX(_mat_stmt)], CALL);
	insert(&followSet[INDEX(_mat_stmt)], STRASSIGN);
	insert(&followSet[INDEX(_mat_stmt)], BREAK);
	insert(&followSet[INDEX(_mat_stmt)], CONTINUE);
	insert(&followSet[INDEX(_mat_stmt)], ENDIF);
	insert(&followSet[INDEX(_mat_stmt)], ELIF);
	insert(&followSet[INDEX(_mat_stmt)], LPAREN);
	insert(&followSet[INDEX(_mat_stmt)], NOT);
	insert(&followSet[INDEX(_mat_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(_mat_stmt)], INT_LIT);
	insert(&followSet[INDEX(_mat_stmt)], REAL_LIT);
	insert(&followSet[INDEX(_mat_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(_mat_stmt)], ID);
	insert(&followSet[INDEX(_mat_stmt)], ENDPROC);
	insert(&followSet[INDEX(_mat_stmt)], END);
	insert(&followSet[INDEX(_mat_stmt)], ELSE);
	insert(&followSet[INDEX(_mat_stmt)], ENDLOOP);

	insert(&followSet[INDEX(row_list)], RCURL);

	insert(&followSet[INDEX(_row_list)], RCURL);

	insert(&followSet[INDEX(row)], SEMICOLON);
	insert(&followSet[INDEX(row)], RCURL);

	insert(&followSet[INDEX(_row)], SEMICOLON);
	insert(&followSet[INDEX(_row)], RCURL);

	insert(&followSet[INDEX(const_)], COMMA);
	insert(&followSet[INDEX(const_)], SEMICOLON);
	insert(&followSet[INDEX(const_)], RCURL);
	insert(&followSet[INDEX(const_)], POW);
	insert(&followSet[INDEX(const_)], MUL);
	insert(&followSet[INDEX(const_)], DIV);
	insert(&followSet[INDEX(const_)], MOD);
	insert(&followSet[INDEX(const_)], PLUS);
	insert(&followSet[INDEX(const_)], MINUS);
	insert(&followSet[INDEX(const_)], RPAREN);

	insert(&followSet[INDEX(str_assign_stmt)], STRING);
	insert(&followSet[INDEX(str_assign_stmt)], MAT);
	insert(&followSet[INDEX(str_assign_stmt)], REC);
	insert(&followSet[INDEX(str_assign_stmt)], INT);
	insert(&followSet[INDEX(str_assign_stmt)], REAL);
	insert(&followSet[INDEX(str_assign_stmt)], BOOL);
	insert(&followSet[INDEX(str_assign_stmt)], CHAR);
	insert(&followSet[INDEX(str_assign_stmt)], LOOP);
	insert(&followSet[INDEX(str_assign_stmt)], ASSIGN);
	insert(&followSet[INDEX(str_assign_stmt)], MATASSIGN);
	insert(&followSet[INDEX(str_assign_stmt)], IF);
	insert(&followSet[INDEX(str_assign_stmt)], GET);
	insert(&followSet[INDEX(str_assign_stmt)], PUT);
	insert(&followSet[INDEX(str_assign_stmt)], CALL);
	insert(&followSet[INDEX(str_assign_stmt)], STRASSIGN);
	insert(&followSet[INDEX(str_assign_stmt)], BREAK);
	insert(&followSet[INDEX(str_assign_stmt)], CONTINUE);
	insert(&followSet[INDEX(str_assign_stmt)], ENDIF);
	insert(&followSet[INDEX(str_assign_stmt)], ELIF);
	insert(&followSet[INDEX(str_assign_stmt)], LPAREN);
	insert(&followSet[INDEX(str_assign_stmt)], NOT);
	insert(&followSet[INDEX(str_assign_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(str_assign_stmt)], INT_LIT);
	insert(&followSet[INDEX(str_assign_stmt)], REAL_LIT);
	insert(&followSet[INDEX(str_assign_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(str_assign_stmt)], ID);
	insert(&followSet[INDEX(str_assign_stmt)], ENDPROC);
	insert(&followSet[INDEX(str_assign_stmt)], END);
	insert(&followSet[INDEX(str_assign_stmt)], ELSE);
	insert(&followSet[INDEX(str_assign_stmt)], ENDLOOP);

	insert(&followSet[INDEX(str_stmt)], STRING);
	insert(&followSet[INDEX(str_stmt)], MAT);
	insert(&followSet[INDEX(str_stmt)], REC);
	insert(&followSet[INDEX(str_stmt)], INT);
	insert(&followSet[INDEX(str_stmt)], REAL);
	insert(&followSet[INDEX(str_stmt)], BOOL);
	insert(&followSet[INDEX(str_stmt)], CHAR);
	insert(&followSet[INDEX(str_stmt)], LOOP);
	insert(&followSet[INDEX(str_stmt)], ASSIGN);
	insert(&followSet[INDEX(str_stmt)], MATASSIGN);
	insert(&followSet[INDEX(str_stmt)], IF);
	insert(&followSet[INDEX(str_stmt)], GET);
	insert(&followSet[INDEX(str_stmt)], PUT);
	insert(&followSet[INDEX(str_stmt)], CALL);
	insert(&followSet[INDEX(str_stmt)], STRASSIGN);
	insert(&followSet[INDEX(str_stmt)], BREAK);
	insert(&followSet[INDEX(str_stmt)], CONTINUE);
	insert(&followSet[INDEX(str_stmt)], ENDIF);
	insert(&followSet[INDEX(str_stmt)], ELIF);
	insert(&followSet[INDEX(str_stmt)], LPAREN);
	insert(&followSet[INDEX(str_stmt)], NOT);
	insert(&followSet[INDEX(str_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(str_stmt)], INT_LIT);
	insert(&followSet[INDEX(str_stmt)], REAL_LIT);
	insert(&followSet[INDEX(str_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(str_stmt)], ID);
	insert(&followSet[INDEX(str_stmt)], ENDPROC);
	insert(&followSet[INDEX(str_stmt)], END);
	insert(&followSet[INDEX(str_stmt)], ELSE);
	insert(&followSet[INDEX(str_stmt)], ENDLOOP);

	insert(&followSet[INDEX(_str_stmt)], STRING);
	insert(&followSet[INDEX(_str_stmt)], MAT);
	insert(&followSet[INDEX(_str_stmt)], REC);
	insert(&followSet[INDEX(_str_stmt)], INT);
	insert(&followSet[INDEX(_str_stmt)], REAL);
	insert(&followSet[INDEX(_str_stmt)], BOOL);
	insert(&followSet[INDEX(_str_stmt)], CHAR);
	insert(&followSet[INDEX(_str_stmt)], LOOP);
	insert(&followSet[INDEX(_str_stmt)], ASSIGN);
	insert(&followSet[INDEX(_str_stmt)], MATASSIGN);
	insert(&followSet[INDEX(_str_stmt)], IF);
	insert(&followSet[INDEX(_str_stmt)], GET);
	insert(&followSet[INDEX(_str_stmt)], PUT);
	insert(&followSet[INDEX(_str_stmt)], CALL);
	insert(&followSet[INDEX(_str_stmt)], STRASSIGN);
	insert(&followSet[INDEX(_str_stmt)], BREAK);
	insert(&followSet[INDEX(_str_stmt)], CONTINUE);
	insert(&followSet[INDEX(_str_stmt)], ENDIF);
	insert(&followSet[INDEX(_str_stmt)], ELIF);
	insert(&followSet[INDEX(_str_stmt)], LPAREN);
	insert(&followSet[INDEX(_str_stmt)], NOT);
	insert(&followSet[INDEX(_str_stmt)], BOOL_LIT);
	insert(&followSet[INDEX(_str_stmt)], INT_LIT);
	insert(&followSet[INDEX(_str_stmt)], REAL_LIT);
	insert(&followSet[INDEX(_str_stmt)], CHAR_LIT);
	insert(&followSet[INDEX(_str_stmt)], ID);
	insert(&followSet[INDEX(_str_stmt)], ENDPROC);
	insert(&followSet[INDEX(_str_stmt)], END);
	insert(&followSet[INDEX(_str_stmt)], ELSE);
	insert(&followSet[INDEX(_str_stmt)], ENDLOOP);

	insert(&followSet[INDEX(ind)], RSQ);
	insert(&followSet[INDEX(ind)], COMMA);
	// printList(followSet[INDEX(_str_stmt)]);
	return followSet;
}
