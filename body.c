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