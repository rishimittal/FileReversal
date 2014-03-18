#ifndef _FOO_H_
#define _FOO_H_

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include "OS_HEADER.h"


extern void reverse_buffer(char* , int);
extern void concatenate(char* ,char*);
extern int string_length(char*);
extern int reverseFile(int args ,char *argv[]);

#endif
