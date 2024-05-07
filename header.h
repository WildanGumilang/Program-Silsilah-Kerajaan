#ifndef siljaan_h
#define siljaan_h

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include "boolean.h"

typedef char* infotype;
typedef struct royalNode *nbAddr;
typedef struct mate *mateAddr;

typedef struct mate{
	infotype nama;
	int age;
	bool gender;
}nbMateNode;

typedef struct royalTree{
	infotype nama;
	int age;
	bool gender;
	nbAddr fs;
	nbAddr nb;
	nbAddr pr;
	mateAddr ps;
}nbTreeNode;

struct nbTree{
	nbAddr root;
};


#endif