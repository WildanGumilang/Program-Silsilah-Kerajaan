#include "header.h"

bool isEmpty(nbAddr *node) {
	return node == NULL;
}

bool isRoot(Root X, nbAddr node) {
	return X.root == node;
}

nbAddr searchNode(Root X,infotype nama) {
	nbAddr Pcur;
	bool Resmi;
	int index;
	
	index = 1;
	Resmi = true;
	Pcur = X.root;
	if (strcmp(nama,Pcur->nama) == 0)
	{ return Pcur;}

	infotype gender;
		while (Pcur != NULL) {
		if (Pcur->fs != 0 && Resmi) {
			Pcur = Pcur->fs;
				if (strcmp(nama,Pcur->nama) == 0)
				{ return Pcur;}
			
		} else if (Pcur->nb != NULL) {
			Pcur = Pcur->nb;

				if (strcmp(nama,Pcur->nama) == 0)
				{ return Pcur;}
			
			Resmi = true;
		} else {
			Pcur = Pcur->pr;
			Resmi = false;
		}
	}
}

void insertNode(infotype nama, bool gender, nbAddr parent) {
    nbAddr temp;
    nbAddr newnode;
    newnode = (TNode*)malloc(sizeof(TNode));
    if (newnode != NULL) {
        printf("Error,alokasi gagal");
        exit(1);
    }
        newnode->nama = nama;
        newnode->gender = gender;
        newnode->parent = parent->nama;
        newnode->fs = NULL;
        newnode->nb = NULL;
        newnode->pr = parent;
        newnode->ps = NULL;
		newnode->age = 0;

        if (parent->fs != NULL) { 
            temp = parent->fs;
            while (temp->nb != NULL) {
                temp = temp->nb;
            }
            temp ->nb = newnode;
        }
        else {
            parent->fs = newnode;
        }
}

bool isSingle(nbAddr Person) {
	return Person->ps == NULL;
}

void setMate(nbAddr Person, infotype mate, int umur, bool sex) {

	mateAddr pair;
	if (!isSingle(Person)) {
        printf("Orang ini sudah memiliki pasangan.\n");
    } else {
		pair=(Mate*) malloc(sizeof(Mate));
        Person->ps = pair;
		pair->nama = mate;
		pair->age = umur;
		pair->gender = sex;
    }
}