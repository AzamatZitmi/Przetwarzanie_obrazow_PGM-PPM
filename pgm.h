#pragma once
#include <stdio.h>

typedef struct pgm{
	char operation_name[30];
	char name_of_file[20];
	char type[2];
	int w;
	int h;
	int max;
	int** pixs;
	}pgm;