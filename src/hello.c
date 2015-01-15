/*
 * hello.c
 *
 * @author Simon Ortego Parra
 * @date 01/2015
 *
 * Copyright (c) 2015, Simón Ortego Parra - All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

//#include <fcntl.h> 
//#include <stdlib.h> 
#include <stdio.h> 
//#include <string.h> 

#include "hello.h"

int main(void)
{ 
	int a, b, c;

	a = 1;
	b = 2;
	c = sum(a,b);
	printf("Hello!\n");
	printf("%d + %d = %d\n", a, b, c);

    return 0; 
}
