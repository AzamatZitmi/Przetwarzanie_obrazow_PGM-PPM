#pragma once
#include <stdio.h>
#include "pixel.h"

typedef struct ppm{
	char operation_name[30];
	char name_of_file[20];
	char type[2];
	int w;
	int h;
	int max;
	pixel** pixs;
	}ppm;