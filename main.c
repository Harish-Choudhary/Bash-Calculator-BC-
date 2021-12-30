#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"istack.h"
#include "functions.h"
#include <limits.h>

//Name: Harishkumar F Choudhary
//MIS: 111903035
//DIV 1 S3 Batch

int main()
{
    printf("Enter Expression:\n");
	number *r;
	char lines[1000];
	while(getexpression(lines, 1000)) {

		r = infix(lines);
		if(r)
            printNumber(*r);
        else
            printf("Error in expression\n");
	}
	return 0;
}
