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
typedef struct allNode *anAddr;
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

typedef struct allNode{
	infotype nama;
	int age;
	bool gender;
	infotype parent;
	anAddr fs;
	anAddr nb;
	anAddr pr;
	infotype pair;
	bool status;
	int ydeath;
}ANode;

typedef struct mate{
	infotype nama;
	int age;
	bool gender;
}Mate;

typedef struct{
	nbAddr root;
}Root;

typedef struct{
	anAddr root;
}ATRoot;

bool isEmpty(nbAddr *node);

bool isSingle(nbAddr Person);

void setMate(nbAddr Person, infotype mate, ATRoot X, int umur, bool sex);

bool isRoot(Root X, nbAddr node);

nbAddr searchNode(Root X,infotype nama);

void insertNode(infotype nama, bool gender, nbAddr parent);

bool deleteNode(Root * X, infotype nama);

void showGarisSuksesi(Root X);

void displayFamily(nbAddr X, int Level);

int countAnak(Root X ,nbAddr node);

void showDetailNode(Root X,nbAddr node);

int countPenerus(Root X, infotype nama);

void addTahun(int * tahun, int penambahan, Root X, ATRoot x);

//tree 2
bool isEmptyAT(anAddr *node);

bool isRootAT(ATRoot X, anAddr node);

void insertNodeAT(infotype nama, bool gender, anAddr parent);

anAddr searchNodeAT(ATRoot X,infotype nama);

void setDeleteAT(anAddr person, ATRoot* X, int tahun);

//setmate

//addtahun

//showdetailnode

//jumlah generasi kerajaan

void displayFamilyAT(anAddr X, int Level);

#endif