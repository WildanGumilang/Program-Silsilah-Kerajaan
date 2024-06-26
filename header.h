/*
Dibuat Oleh : 

KELOMPOK 688791
D3 - 1C

Alqan Nazra (231511068)
Muhammad Wildan Gumilang (231511087)
Ryuki Haga Budiarto (231511091)

Tanggal Update : 01 Mei 2024
*/

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
bool deleteNode(Root * X, infotype nama, int tahun);
void showGarisSuksesi(Root X);
void displayFamily(nbAddr X, int Level);
void showDetailNode(Root X, ATRoot x, infotype node);
int countAnak(Root X ,nbAddr node);
int countPenerus(Root X, infotype nama);

bool isEmptyAT(anAddr *node);
bool isRootAT(ATRoot X, anAddr node);
void insertNodeAT(infotype nama, bool gender, anAddr parent);
anAddr searchNodeAT(ATRoot X,infotype nama);
bool setDeleteAT(anAddr person, int tahun);
void saveNodeToFile(const char* filename, nbAddr node, int tahun);
void displayFamilyAT(anAddr X, int Level);
int countGenerasi(ATRoot x);
int countNode(nbAddr root);
void showDetailNodeMati(Root x, ATRoot X, infotype nama, anAddr person);
void saveNodeToFile(const char* filename, nbAddr node, int tahun);
void writeFamilyToFile(FILE *file, nbAddr X, int Level);
void saveTreeToFile(Root tree, const char *filename, int tahun, infotype nama, bool tambah);
void printFileContent(const char *filename);
void insertKing(Root *king, ATRoot *King, int tahun);
void insertBangsawan(Root *king, ATRoot *King, int tahun);
void insertMate(Root x, ATRoot X, int tahun);
void deleteBangsawan(Root* x, ATRoot X, infotype Delete, int tahun);
void addTahun(int * tahun, int penambahan, Root X, ATRoot x);
void aboutKerajaan(Root x, ATRoot X, int tahun, bool runtuh);
void introCreator();
void displayMenu(int selectedOption);
#endif