﻿//#define DEBUG 1

#ifdef DEBUG
#define ITERATIONS 1
#include <bitset>
#else
#define ITERATIONS 100000//0
#endif

#define my 3
#define mx 3
#define mxmy (my*mx)
#define mxmymxmy (my*my*mx*mx)
#define mflags ((1 << (mxmy)) - 1)
#define consblocksize ((mxmy - 1) * 2 + (mx - 1)*(my - 1))

#define flagnull 32

//define bitcount(flgs) ( ((flgs & 1) + (((flgs >> 1) * 0x200040008001 & 0x111111111111111) * 0x111111111111111 >> 56) & 0xF) ) // подсчет количества вариантов в ячейке
#define bitcount(flgs) (bitcountarray[flgs])

#if mx == 3
#if my == 3

//The AI Escargot Sudoku
//by Arto Inkala. 2006.
//static int m[mxmy][mxmy] = {
//	{ 1, 0, 0, 0, 0, 7, 0, 9, 0 },
//	{ 0, 3, 0, 0, 2, 0, 0, 0, 8 },
//	{ 0, 0, 9, 6, 0, 0, 5, 0, 0 },
//	{ 0, 0, 5, 3, 0, 0, 9, 0, 0 },
//	{ 0, 1, 0, 0, 8, 0, 0, 0, 2 },
//	{ 6, 0, 0, 0, 0, 4, 0, 0, 0 },
//	{ 3, 0, 0, 0, 0, 0, 0, 1, 0 },
//	{ 0, 4, 0, 0, 0, 0, 0, 0, 7 },
//	{ 0, 0, 7, 0, 0, 0, 3, 0, 0 },
//};

//The World's Hardest Sudoku
//by Arto Inkala. 2010.
//static int m[mxmy][mxmy] = {
//	{ 0, 0, 5, 3, 0, 0, 0, 0, 0 },
//	{ 8, 0, 0, 0, 0, 0, 0, 2, 0 },
//	{ 0, 7, 0, 0, 1, 0, 5, 0, 0 },
//	{ 4, 0, 0, 0, 0, 5, 3, 0, 0 },
//	{ 0, 1, 0, 0, 7, 0, 0, 0, 6 },
//	{ 0, 0, 3, 2, 0, 0, 0, 8, 0 },
//	{ 0, 6, 0, 5, 0, 0, 0, 0, 9 },
//	{ 0, 0, 4, 0, 0, 0, 0, 3, 0 },
//	{ 0, 0, 0, 0, 0, 9, 7, 0, 0 }
//};

//autosolve test
//static int m[mxmy][mxmy] = {
//	{ 0, 0, 0, 2, 0, 4, 8, 1, 0 },
//	{ 0, 4, 0, 0, 0, 8, 2, 6, 3 },
//	{ 3, 0, 0, 1, 6, 0, 0, 0, 4 },
//	{ 1, 0, 0, 0, 4, 0, 5, 8, 0 },
//	{ 6, 3, 5, 8, 2, 0, 0, 0, 7 },
//	{ 2, 0, 0, 5, 9, 0, 1, 0, 0 },
//	{ 9, 1, 0, 7, 0, 0, 0, 4, 0 },
//	{ 0, 0, 0, 6, 8, 0, 7, 0, 1 },
//	{ 8, 0, 0, 4, 0, 3, 0, 5, 0 }
//};

//easy
static int m[mxmy][mxmy] = {
	{ 2, 4, 1, 3, 0, 0, 0, 0, 5 },
	{ 8, 0, 0, 6, 0, 0, 0, 2, 0 },
	{ 5, 0, 0, 0, 0, 0, 0, 0, 3 },
	{ 4, 5, 0, 0, 0, 6, 0, 0, 9 },
	{ 1, 3, 0, 0, 0, 0, 0, 4, 0 },
	{ 7, 0, 0, 2, 0, 0, 0, 0, 0 },
	{ 6, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 3, 8, 0, 0, 0, 1, 0, 0, 4 },
	{ 9, 2, 0, 0, 0, 5, 7, 1, 0 }
};

//M. Feenstra, Den Haag. 2005
//static int m[mxmy][mxmy] = {
//	{ 0, 0, 0, 2, 0, 0, 0, 6, 3 },
//	{ 3, 0, 0, 0, 0, 5, 4, 0, 1 },
//	{ 0, 0, 1, 0, 0, 3, 9, 8, 0 },
//	{ 0, 0, 0, 0, 0, 0, 0, 9, 0 },
//	{ 0, 0, 0, 5, 3, 8, 0, 0, 0 },
//	{ 0, 3, 0, 0, 0, 0, 0, 0, 0 },
//	{ 0, 2, 6, 3, 0, 0, 5, 0, 0 },
//	{ 5, 0, 3, 7, 0, 0, 0, 0, 8 },
//	{ 4, 7, 0, 0, 0, 1, 0, 0, 0 }
//};

//пример от интела 3319 решений.
//static int m[mxmy][mxmy] = {
//	{ 1, 0, 0, 9, 0, 0, 0, 8, 0 },
//	{ 0, 8, 0, 2, 0, 0, 0, 0, 0 },
//	{ 0, 0, 5, 0, 0, 0, 7, 0, 0 },
//	{ 0, 5, 2, 1, 0, 0, 4, 0, 0 },
//	{ 0, 0, 0, 0, 0, 5, 0, 0, 7 },
//	{ 4, 0, 0, 7, 0, 0, 0, 3, 0 },
//	{ 0, 3, 0, 0, 0, 2, 0, 0, 5 },
//	{ 0, 0, 0, 0, 0, 0, 1, 0, 0 },
//	{ 5, 0, 0, 0, 1, 0, 0, 0, 0 }
//};

//пример от интела 28154 решений.
//static int m[mxmy][mxmy] = {
//	{ 1, 0, 0, 9, 0, 0, 0, 8, 0 },
//	{ 0, 8, 0, 2, 0, 0, 0, 0, 0 },
//	{ 0, 0, 5, 0, 0, 0, 7, 0, 0 },
//	{ 0, 5, 2, 1, 0, 0, 4, 0, 0 },
//	{ 0, 0, 0, 0, 0, 5, 0, 0, 7 },
//	{ 4, 0, 0, 7, 0, 0, 0, 3, 0 },
//	{ 0, 3, 0, 0, 0, 2, 0, 0, 5 },
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//	{ 5, 0, 0, 0, 1, 0, 0, 0, 0 }
//};

//с ошибкой. соответственно решений не имеет.
//static int m[mxmy][mxmy] = {
//	{ 1, 0, 0, 9, 0, 0, 9, 8, 0 },
//	{ 0, 8, 0, 2, 0, 0, 0, 0, 0 },
//	{ 0, 0, 5, 0, 0, 0, 7, 0, 0 },
//	{ 0, 5, 2, 1, 0, 0, 4, 0, 0 },
//	{ 0, 0, 0, 0, 0, 5, 0, 0, 7 },
//	{ 4, 0, 0, 7, 0, 0, 0, 3, 0 },
//	{ 0, 3, 0, 0, 0, 2, 0, 0, 5 },
//	{ 0, 0, 0, 0, 0, 0, 1, 0, 0 },
//	{ 5, 0, 0, 0, 1, 0, 0, 0, 0 }
//};

#endif
#if my == 2
static int m[mxmy][mxmy] = {
	{ 3, 0, 5, 6, 0, 1 },
	{ 2, 0, 0, 4, 0, 0 },
	{ 0, 0, 3, 0, 0, 6 },
	{ 5, 0, 4, 2, 0, 3 },
	{ 6, 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0, 2 }
};
#endif
#else
int m[mxmy][mxmy];
#endif

static const int bitcountarray[512] =
{
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
	5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9
};

static const int mask2digit[512] =
{
	0, 1, 2, 0, 3, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
	5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const int offset2row[81] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7, 7, 7, 7, 7,
	8, 8, 8, 8, 8, 8, 8, 8, 8,
};

static const int offset2column[81] =
{
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
};

static const int offset2block[81] =
{
	18, 18, 18, 19, 19, 19, 20, 20, 20,
	18, 18, 18, 19, 19, 19, 20, 20, 20,
	18, 18, 18, 19, 19, 19, 20, 20, 20,
	21, 21, 21, 22, 22, 22, 23, 23, 23,
	21, 21, 21, 22, 22, 22, 23, 23, 23,
	21, 21, 21, 22, 22, 22, 23, 23, 23,
	24, 24, 24, 25, 25, 25, 26, 26, 26,
	24, 24, 24, 25, 25, 25, 26, 26, 26,
	24, 24, 24, 25, 25, 25, 26, 26, 26,
};

static const int cons[81][20] =
{
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 18, 19, 20, 27, 36, 45, 54, 63, 72 },
	{ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 18, 19, 20, 28, 37, 46, 55, 64, 73 },
	{ 0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 18, 19, 20, 29, 38, 47, 56, 65, 74 },
	{ 0, 1, 2, 4, 5, 6, 7, 8, 12, 13, 14, 21, 22, 23, 30, 39, 48, 57, 66, 75 },
	{ 0, 1, 2, 3, 5, 6, 7, 8, 12, 13, 14, 21, 22, 23, 31, 40, 49, 58, 67, 76 },
	{ 0, 1, 2, 3, 4, 6, 7, 8, 12, 13, 14, 21, 22, 23, 32, 41, 50, 59, 68, 77 },
	{ 0, 1, 2, 3, 4, 5, 7, 8, 15, 16, 17, 24, 25, 26, 33, 42, 51, 60, 69, 78 },
	{ 0, 1, 2, 3, 4, 5, 6, 8, 15, 16, 17, 24, 25, 26, 34, 43, 52, 61, 70, 79 },
	{ 0, 1, 2, 3, 4, 5, 6, 7, 15, 16, 17, 24, 25, 26, 35, 44, 53, 62, 71, 80 },
	{ 0, 1, 2, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 27, 36, 45, 54, 63, 72 },
	{ 0, 1, 2, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 28, 37, 46, 55, 64, 73 },
	{ 0, 1, 2, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 29, 38, 47, 56, 65, 74 },
	{ 3, 4, 5, 9, 10, 11, 13, 14, 15, 16, 17, 21, 22, 23, 30, 39, 48, 57, 66, 75 },
	{ 3, 4, 5, 9, 10, 11, 12, 14, 15, 16, 17, 21, 22, 23, 31, 40, 49, 58, 67, 76 },
	{ 3, 4, 5, 9, 10, 11, 12, 13, 15, 16, 17, 21, 22, 23, 32, 41, 50, 59, 68, 77 },
	{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 24, 25, 26, 33, 42, 51, 60, 69, 78 },
	{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 24, 25, 26, 34, 43, 52, 61, 70, 79 },
	{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 24, 25, 26, 35, 44, 53, 62, 71, 80 },
	{ 0, 1, 2, 9, 10, 11, 19, 20, 21, 22, 23, 24, 25, 26, 27, 36, 45, 54, 63, 72 },
	{ 0, 1, 2, 9, 10, 11, 18, 20, 21, 22, 23, 24, 25, 26, 28, 37, 46, 55, 64, 73 },
	{ 0, 1, 2, 9, 10, 11, 18, 19, 21, 22, 23, 24, 25, 26, 29, 38, 47, 56, 65, 74 },
	{ 3, 4, 5, 12, 13, 14, 18, 19, 20, 22, 23, 24, 25, 26, 30, 39, 48, 57, 66, 75 },
	{ 3, 4, 5, 12, 13, 14, 18, 19, 20, 21, 23, 24, 25, 26, 31, 40, 49, 58, 67, 76 },
	{ 3, 4, 5, 12, 13, 14, 18, 19, 20, 21, 22, 24, 25, 26, 32, 41, 50, 59, 68, 77 },
	{ 6, 7, 8, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 33, 42, 51, 60, 69, 78 },
	{ 6, 7, 8, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 26, 34, 43, 52, 61, 70, 79 },
	{ 6, 7, 8, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 35, 44, 53, 62, 71, 80 },
	{ 0, 9, 18, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 45, 46, 47, 54, 63, 72 },
	{ 1, 10, 19, 27, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 45, 46, 47, 55, 64, 73 },
	{ 2, 11, 20, 27, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 45, 46, 47, 56, 65, 74 },
	{ 3, 12, 21, 27, 28, 29, 31, 32, 33, 34, 35, 39, 40, 41, 48, 49, 50, 57, 66, 75 },
	{ 4, 13, 22, 27, 28, 29, 30, 32, 33, 34, 35, 39, 40, 41, 48, 49, 50, 58, 67, 76 },
	{ 5, 14, 23, 27, 28, 29, 30, 31, 33, 34, 35, 39, 40, 41, 48, 49, 50, 59, 68, 77 },
	{ 6, 15, 24, 27, 28, 29, 30, 31, 32, 34, 35, 42, 43, 44, 51, 52, 53, 60, 69, 78 },
	{ 7, 16, 25, 27, 28, 29, 30, 31, 32, 33, 35, 42, 43, 44, 51, 52, 53, 61, 70, 79 },
	{ 8, 17, 26, 27, 28, 29, 30, 31, 32, 33, 34, 42, 43, 44, 51, 52, 53, 62, 71, 80 },
	{ 0, 9, 18, 27, 28, 29, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 54, 63, 72 },
	{ 1, 10, 19, 27, 28, 29, 36, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 55, 64, 73 },
	{ 2, 11, 20, 27, 28, 29, 36, 37, 39, 40, 41, 42, 43, 44, 45, 46, 47, 56, 65, 74 },
	{ 3, 12, 21, 30, 31, 32, 36, 37, 38, 40, 41, 42, 43, 44, 48, 49, 50, 57, 66, 75 },
	{ 4, 13, 22, 30, 31, 32, 36, 37, 38, 39, 41, 42, 43, 44, 48, 49, 50, 58, 67, 76 },
	{ 5, 14, 23, 30, 31, 32, 36, 37, 38, 39, 40, 42, 43, 44, 48, 49, 50, 59, 68, 77 },
	{ 6, 15, 24, 33, 34, 35, 36, 37, 38, 39, 40, 41, 43, 44, 51, 52, 53, 60, 69, 78 },
	{ 7, 16, 25, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 51, 52, 53, 61, 70, 79 },
	{ 8, 17, 26, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 51, 52, 53, 62, 71, 80 },
	{ 0, 9, 18, 27, 28, 29, 36, 37, 38, 46, 47, 48, 49, 50, 51, 52, 53, 54, 63, 72 },
	{ 1, 10, 19, 27, 28, 29, 36, 37, 38, 45, 47, 48, 49, 50, 51, 52, 53, 55, 64, 73 },
	{ 2, 11, 20, 27, 28, 29, 36, 37, 38, 45, 46, 48, 49, 50, 51, 52, 53, 56, 65, 74 },
	{ 3, 12, 21, 30, 31, 32, 39, 40, 41, 45, 46, 47, 49, 50, 51, 52, 53, 57, 66, 75 },
	{ 4, 13, 22, 30, 31, 32, 39, 40, 41, 45, 46, 47, 48, 50, 51, 52, 53, 58, 67, 76 },
	{ 5, 14, 23, 30, 31, 32, 39, 40, 41, 45, 46, 47, 48, 49, 51, 52, 53, 59, 68, 77 },
	{ 6, 15, 24, 33, 34, 35, 42, 43, 44, 45, 46, 47, 48, 49, 50, 52, 53, 60, 69, 78 },
	{ 7, 16, 25, 33, 34, 35, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 53, 61, 70, 79 },
	{ 8, 17, 26, 33, 34, 35, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 62, 71, 80 },
	{ 0, 9, 18, 27, 36, 45, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 72, 73, 74 },
	{ 1, 10, 19, 28, 37, 46, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 72, 73, 74 },
	{ 2, 11, 20, 29, 38, 47, 54, 55, 57, 58, 59, 60, 61, 62, 63, 64, 65, 72, 73, 74 },
	{ 3, 12, 21, 30, 39, 48, 54, 55, 56, 58, 59, 60, 61, 62, 66, 67, 68, 75, 76, 77 },
	{ 4, 13, 22, 31, 40, 49, 54, 55, 56, 57, 59, 60, 61, 62, 66, 67, 68, 75, 76, 77 },
	{ 5, 14, 23, 32, 41, 50, 54, 55, 56, 57, 58, 60, 61, 62, 66, 67, 68, 75, 76, 77 },
	{ 6, 15, 24, 33, 42, 51, 54, 55, 56, 57, 58, 59, 61, 62, 69, 70, 71, 78, 79, 80 },
	{ 7, 16, 25, 34, 43, 52, 54, 55, 56, 57, 58, 59, 60, 62, 69, 70, 71, 78, 79, 80 },
	{ 8, 17, 26, 35, 44, 53, 54, 55, 56, 57, 58, 59, 60, 61, 69, 70, 71, 78, 79, 80 },
	{ 0, 9, 18, 27, 36, 45, 54, 55, 56, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74 },
	{ 1, 10, 19, 28, 37, 46, 54, 55, 56, 63, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74 },
	{ 2, 11, 20, 29, 38, 47, 54, 55, 56, 63, 64, 66, 67, 68, 69, 70, 71, 72, 73, 74 },
	{ 3, 12, 21, 30, 39, 48, 57, 58, 59, 63, 64, 65, 67, 68, 69, 70, 71, 75, 76, 77 },
	{ 4, 13, 22, 31, 40, 49, 57, 58, 59, 63, 64, 65, 66, 68, 69, 70, 71, 75, 76, 77 },
	{ 5, 14, 23, 32, 41, 50, 57, 58, 59, 63, 64, 65, 66, 67, 69, 70, 71, 75, 76, 77 },
	{ 6, 15, 24, 33, 42, 51, 60, 61, 62, 63, 64, 65, 66, 67, 68, 70, 71, 78, 79, 80 },
	{ 7, 16, 25, 34, 43, 52, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 71, 78, 79, 80 },
	{ 8, 17, 26, 35, 44, 53, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 78, 79, 80 },
	{ 0, 9, 18, 27, 36, 45, 54, 55, 56, 63, 64, 65, 73, 74, 75, 76, 77, 78, 79, 80 },
	{ 1, 10, 19, 28, 37, 46, 54, 55, 56, 63, 64, 65, 72, 74, 75, 76, 77, 78, 79, 80 },
	{ 2, 11, 20, 29, 38, 47, 54, 55, 56, 63, 64, 65, 72, 73, 75, 76, 77, 78, 79, 80 },
	{ 3, 12, 21, 30, 39, 48, 57, 58, 59, 66, 67, 68, 72, 73, 74, 76, 77, 78, 79, 80 },
	{ 4, 13, 22, 31, 40, 49, 57, 58, 59, 66, 67, 68, 72, 73, 74, 75, 77, 78, 79, 80 },
	{ 5, 14, 23, 32, 41, 50, 57, 58, 59, 66, 67, 68, 72, 73, 74, 75, 76, 78, 79, 80 },
	{ 6, 15, 24, 33, 42, 51, 60, 61, 62, 69, 70, 71, 72, 73, 74, 75, 76, 77, 79, 80 },
	{ 7, 16, 25, 34, 43, 52, 60, 61, 62, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 80 },
	{ 8, 17, 26, 35, 44, 53, 60, 61, 62, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79 }
};

static const int block2offset[27][9] =
{
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8 },
	{ 9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	{ 0, 9, 18, 27, 36, 45, 54, 63, 72 },
	{ 1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{ 2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{ 3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{ 4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{ 5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{ 6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{ 7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{ 8, 17, 26, 35, 44, 53, 62, 71, 80 },
	{ 0, 1, 2, 9, 10, 11, 18, 19, 20 },
	{ 3, 4, 5, 12, 13, 14, 21, 22, 23 },
	{ 6, 7, 8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 }
};