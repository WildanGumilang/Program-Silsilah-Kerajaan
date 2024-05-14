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

void deleteNode(Root *X, infotype nama)
{
    nbAddr nDel;
    bool del = true;
    nDel = searchNode(*X,nama);
    if (nDel == NULL)
    {
    	 printf("\n\tNama bangsawan tidak ditemukan\n\t", nama);
		 system("pause");
		 del = false;
    } else if(isRoot(*X,nDel)){ // JIKA RAJA WAFAT
		if (nDel->gender)
		{
			printf("\tRaja telah wafat ...\n");
		} else{
			printf("\tRatu telah wafat ...\n");	
		}
        

        nbAddr nextKing = nDel->fs;
		(*X).root = nextKing;
		if(nextKing == NULL){
		printf("\tTidak ada penerus kerjaan!\n\n\t");
		} else {
			printf("\tKini pemimpin baru telah diangkat, yakni %s\n", (*X).root->nama);
			printf("\tEra %s telah dimulai!\n\n\t",(*X).root->nama);
		
		nextKing->pr = NULL;
		if (nextKing->fs != NULL) 
		{
			nbAddr Current = nDel;
			nbAddr brother = Current->nb;
			nbAddr myBro;
			Current = Current->fs;
			bool loop = true;
			while (Current != NULL && loop)
			{
					if(Current->nb != NULL){
						myBro = Current->nb;
					} else {
						myBro = NULL;
					}
					

					if (Current->fs == NULL)
					{
						if (Current->nb != NULL)
						{
							Current->fs = Current->nb;
							nbAddr bro =  Current->nb;
							while (bro != NULL)
							{
								bro->pr = Current;
								bro = bro->nb;
							}
							loop = false;
						}
					}
						
						Current->nb = brother;
						nbAddr bro =  Current->nb;
						while (bro != NULL)
						{
							bro->pr = Current->pr;
							bro = bro->nb;
						}
						
						brother = myBro;
					
					Current = Current->fs;
			}
			

		} else if (nextKing->nb != NULL){
						nextKing->fs = nextKing->nb;
						nextKing->nb->pr = nextKing; 
						nbAddr bro =  nextKing->nb;
						while (bro != NULL)
						{
							bro->pr = nextKing;
							bro = bro->nb;
						}
						nextKing->nb = NULL;
			
		} 
	}
	}
	
	// JIKA YANG MATI ADALAH ANAK PERTAMA
	else if(nDel->pr->fs == nDel){ 
		printf("\n\n\tBangsawan %s Telah Meninggal.\n\n\t", nDel->nama );
		if(nDel->fs != NULL){ 				   // Jika nDel memiliki anak 
			 // fs merupakan anak pertama nDel
			nDel->fs->pr = nDel->pr; // Orang tua dari fs diganti menjadi orang tua nDel
			nDel->pr->fs = nDel->fs; // Anak pertama dari Orang tua nDel menjadi fs
		
			nbAddr Current = nDel;
			nbAddr brother = Current->nb;
			nbAddr myBro = Current->nb;
			Current = Current->fs;
			bool loop = true;
			while (Current != NULL && loop)
			{
					if(Current->nb != NULL){
						myBro = Current->nb;
					} else {
						myBro = NULL;
					}
					

					if (Current->fs == NULL)
					{
						if (Current->nb != NULL)
						{
							Current->fs = Current->nb;
							nbAddr bro =  Current->nb;
							while (bro != NULL)
							{
								bro->pr = Current;
								bro = bro->nb;
							}
							loop = false;
						}
					}
						
						Current->nb = brother;
						nbAddr bro =  Current->nb;
						while (bro != NULL)
						{
							bro->pr = Current->pr;
							bro = bro->nb;
						}
						
						brother = myBro;
					
					Current = Current->fs;
			}
			
	} else {
		if(nDel->nb != NULL){
			nDel->pr->fs = nDel->nb;
		} else {
			nDel->pr->fs = NULL;
		}
	}

	} // JIKA YANG MATI BUKAN ANAK PERTAMA 
	else if(nDel->pr->fs != nDel){
		printf("\n\n\tBangsawan %s Telah Meninggal.\n\n\t", nDel->nama );
		nbAddr bDelete = nDel->pr->fs;
		while (bDelete->nb != nDel)
		{
			bDelete = bDelete->nb;
		}
		if (nDel->fs != NULL ) // jika nDel memiliki anak
		{
			bDelete->nb = nDel->fs;
			nbAddr Current = nDel;
			nbAddr brother = Current->nb;
			nbAddr myBro;
			Current = Current->fs;
		bool loop = true;
			while (Current != NULL && loop)
			{
					if(Current->nb != NULL){
						myBro = Current->nb;
					} else {
						myBro = NULL;
					}
					

					if (Current->fs == NULL)
					{
						if (Current->nb != NULL)
						{
							Current->fs = Current->nb;
							nbAddr bro =  Current->nb;
							while (bro != NULL)
							{
								bro->pr = Current;
								bro = bro->nb;
							}
							loop = false;
						}
					}
						
						Current->nb = brother;
						nbAddr bro =  Current->nb;
						while (bro != NULL)
						{
							bro->pr = Current->pr;
							bro = bro->nb;
						}
						
						brother = myBro;
					
					Current = Current->fs;
			}
			
				
				} else if (nDel->fs == NULL){
					bDelete->nb = nDel->nb;
		}
	}
	if (del)
	{
	nDel->fs = NULL;
	nDel->nb = NULL;
	nDel->pr = NULL;
	free(nDel);
	}
}