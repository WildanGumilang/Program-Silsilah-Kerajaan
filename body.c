#include "header.h"

nbAddr searchNode(Root X,infotype nama)
/* Mencari suatu Node berdasarkan subvar nama lalu akan mengembalikan node tersebut jika ketemu */
{
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

void nbInsert(infotype n,bool Kl,int usia,nbAddr ortu)
{
    nbAddr temp;
    nbAddr newnode;
    newnode = (nbAddr)malloc(sizeof(TNode));
    if (newnode != NULL)
    {
        printf("Error,alokasi gagal");
        exit(1);
    }
        newnode->nama = n;
        newnode->age = usia;
        newnode->gender = Kl;
        newnode->parent = ortu ->nama;
        newnode->fs = NULL;
        newnode->nb = NULL;
        newnode->pr = ortu;
        newnode->ps = NULL;

        if (ortu->fs != NULL)
        { 
            temp = ortu->fs;
            while (temp->nb != NULL)
            {
                temp = temp->nb;
            }
            temp ->nb = newnode;
        }
        else
        {
            ortu->fs = newnode;
        }
}