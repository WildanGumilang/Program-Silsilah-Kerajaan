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

typedef struct royalNode{
	infotype nama;
	int age;
	bool gender;
	infotype parent;
	nbAddr fs;
	nbAddr nb;
	nbAddr pr;
	mateAddr ps;
}TNode;

typedef struct mate{
	infotype nama;
	int age;
	bool gender;
}Mate;

typedef struct{
	nbAddr root;
}Root;

nbAddr searchNode(Root X,infotype nama);

void insertNode(infotype nama, bool gender, nbAddr parent);

bool isSingle(nbAddr Person);

void setMate(nbAddr Person, infotype mate, int umur, bool sex);

#endif