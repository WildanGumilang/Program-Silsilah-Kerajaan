#include "header.h"

bool isEmpty(nbAddr *node) {
	return node == NULL;
}

bool isRoot(Root X, nbAddr node) {
	return X.root == node;
}

bool isSingle(nbAddr Person) {
	return Person->ps == NULL;
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
    if (newnode == NULL) {
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


bool deleteNode(Root * X, infotype nama){
  nbAddr nDel;
  bool del = true;
  nDel = searchNode(*X,nama);
  if (nDel == NULL){
    	printf("\n\tNama bangsawan tidak ditemukan\n\t", nama);
		system("pause");
		del = false;
		return false;
    } else if(isRoot(*X,nDel)){ // JIKA RAJA WAFAT
		if (nDel->gender) {
			printf("\tRaja telah wafat ...\n");
		} else{
			printf("\tRatu telah wafat ...\n");	
		}
		
		
		nbAddr nextKing = nDel->fs;
		(*X).root = nextKing;
		if(nextKing == NULL){
		printf("\tTIDAK ADA PENERUS KERAJAAN, BUTUH PEMIMPIN BARU\n\n\t");
		} else {
			printf("\tKini pemimpin baru telah diangkat, yakni %s\n", (*X).root->nama);
			printf("\tTHE ERA OF %s HAS BEGUN !!!!!\n\n\t",(*X).root->nama);
			nextKing->pr = NULL;

			if (nextKing->fs != NULL){
				nbAddr Current = nDel;
				nbAddr brother = Current->nb;
				nbAddr myBro;
				Current = Current->fs;
				bool loop = true;
				while (Current != NULL && loop) {
						if(Current->nb != NULL){
							myBro = Current->nb;
						} else {
							myBro = NULL;
						}
						
						if (Current->fs == NULL) {
							if (Current->nb != NULL) {
								Current->fs = Current->nb;
								nbAddr bro =  Current->nb;
								while (bro != NULL) {
									bro->pr = Current;
									bro = bro->nb;
								}
								loop = false;
							}
						}
						
						Current->nb = brother;
						nbAddr bro =  Current->nb;
						while (bro != NULL) {
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
				while (bro != NULL) {
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
			while (Current != NULL && loop) {
				if(Current->nb != NULL){
					myBro = Current->nb;
				} else {
					myBro = NULL;
				}

				if (Current->fs == NULL){
					if (Current->nb != NULL){
						Current->fs = Current->nb;
						nbAddr bro =  Current->nb;
						while (bro != NULL){
							bro->pr = Current;
							bro = bro->nb;
						}
						loop = false;
					}
				}
						
				Current->nb = brother;
				nbAddr bro =  Current->nb;
				while (bro != NULL){
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
		while (bDelete->nb != nDel) {
			bDelete = bDelete->nb;
		}
		if (nDel->fs != NULL ){ // jika nDel memiliki anak
			bDelete->nb = nDel->fs;
			nbAddr Current = nDel;
			nbAddr brother = Current->nb;
			nbAddr myBro;
			Current = Current->fs;
			bool loop = true;
			while (Current != NULL && loop){
				if(Current->nb != NULL){
					myBro = Current->nb;
				} else {
					myBro = NULL;
				}
			
				if (Current->fs == NULL){
					if (Current->nb != NULL){
						Current->fs = Current->nb;
						nbAddr bro =  Current->nb;
						while (bro != NULL){
							bro->pr = Current;
							bro = bro->nb;
						}
						loop = false;
					}
				}
						
				Current->nb = brother;
				nbAddr bro =  Current->nb;
				while (bro != NULL){
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
	if (del){
		nDel->fs = NULL;
		nDel->nb = NULL;
		nDel->pr = NULL;
		free(nDel);
		return true;
	}
}

void showGarisSuksesi(Root X) {
	nbAddr Pcur;
	bool Resmi;
	int index;
	
	index = 1;
	Resmi = true;
	Pcur = X.root;
	if(Pcur->fs != NULL) {
		printf("\n\t============= GARIS SUKSESI =============\n");
		while (Pcur != NULL) {
			if (Pcur->fs != 0 && Resmi) {
				Pcur = Pcur->fs;
				if (!isRoot(X,Pcur)) {
					printf("\t%d. %s\n", index, Pcur->nama);
					index++;
				}
			} else if (Pcur->nb != NULL) {
				Pcur = Pcur->nb;
				if (!isRoot(X,Pcur)) {
					printf("\t%d. %s\n", index, Pcur->nama);
					index++;
				}
				Resmi = true;
			} else {
				Pcur = Pcur->pr;
				Resmi = false;
			}
		}
	} else {
		printf("\tRaja di Kerajaan Ini Belum Memiliki Penerus.\n\t");
	}
}

void displayFamily(nbAddr X, int Level) {
	if (X != NULL) {
    	printf("\t");
        if (X->nama != NULL && strcmp(X->nama, "") != 0) {
            int i;
            for (i = 1; i <= Level; i++) {
                if (i < Level) {
                    printf("\t|  ");
                }else {
                    printf("\t|--");
                }
            }
            printf("%s\n", X->nama);
        }
        displayFamily(X->fs, Level + 1);
        displayFamily(X->nb, Level);
    }
}


//modifikasi
void setMate(nbAddr Person, infotype mate, ATRoot X, int umur, bool sex) {
	mateAddr pair;
	if (!isSingle(Person)) {
        printf("Orang ini sudah memiliki pasangan.\n");
    } else {
		pair=(Mate*) malloc(sizeof(Mate));
        Person->ps = pair;
		pair->nama = mate;
		pair->age = umur;
		pair->gender = sex;

		anAddr personAT = searchNodeAT(X, Person->nama);
		personAT->pair = mate;
    }
}

//modifikasi
void showDetailNode(Root X,ATRoot x, infotype node) {

	nbAddr person;
	person = searchNode(X, node);
	if (person == NULL) {
		anAddr personAT;
		personAT = searchNodeAT(x, node);
		if (personAT == NULL) {
			printf("\n\tBangsawan Tidak Ditemukan, Atau Nama Bangsawan Salah.\n\n");
			system("pause");
		} else {
			printf("\n\t=============================== DETAIL BANGSAWAN MATI ===============================\n\n");
			
			if (isRootAT(x,personAT)) {
				printf("\tNama Bangsawan\t: %s\n", personAT->nama);
			} else {
				infotype gender;
				if(personAT->gender == true){
					gender = "son";
				}else {
					gender = "daughter";
				}
				printf("\tNama Bangsawan\t: %s %s of %s \n", personAT->nama,gender,personAT->parent);
			}
			if (personAT->pair == "") {
				if (personAT->status == false) {
					printf("\tStatus \t\t: Telah Wafat diumur %d pada tahun %d\n", personAT->age, personAT->ydeath);
				} else {
					printf("\tStatus \t\t: Masih Hidup, %d tahun\n", personAT->age);
				}
				printf("\tStatus \t\t: Belum Menikah\n", personAT->nama);
			} else {
				if (personAT->status == false) {
					printf("\tStatus \t\t: Telah Wafat diumur %d pada tahun %d\n", personAT->age, personAT->ydeath);
				} else {
					printf("\tStatus \t\t: Masih Hidup, %d tahun\n", personAT->age);
				}
				printf("\tStatus \t\t: Sudah Menikah\n");
				printf("\tPasangan \t: %s\n", personAT->pair);
				printf("\n");
			}
			system("pause");
		}
	} else {
		printf("\n\t=============================== DETAIL BANGSAWAN HIDUP ===============================\n\n");
		
		if (isRoot(X,person)) {
			printf("\tNama Bangsawan\t: %s\n", person->nama);
			printf("\tUsia\t\t: %d\n",person->age);
		} else {
			infotype gender;
			printf("\tUsia\t\t: %d\n",person->age);
			if(person->gender == true){
				gender = "son";
			}else {
				gender = "daughter";
			}
			printf("\tNama Bangsawan\t: %s %s of %s \n", person->nama,gender,person->parent);
			printf("\tPewaris Tahta \t: ke-%d\n", countPenerus(X, person->nama));
		}
		if (isSingle(person)) {
			printf("\tStatus \t\t: Belum Menikah\n", person->nama);
		} else {
			printf("\tStatus \t\t: Sudah Menikah\n");
			printf("\tPasangan \t: %s\n", person->ps->nama);
			printf("\tUsia Pasangan \t: %d\n", person->ps->age);
			int jumlahAnak = countAnak(X,person);
			printf("\tJumlah Anak\t: %d\n", jumlahAnak);
			printf("\n");
		}
		system("pause");
	}
}


//modifikasi
void addTahun(int * tahun, int penambahan, Root X, ATRoot x){
	*tahun += penambahan;
	nbAddr Pcur = X.root;
	anAddr PcurAT = x.root;
    Pcur->age = Pcur->age + penambahan;
	if (PcurAT->status == true) {
		PcurAT->age = PcurAT->age + penambahan;
	}
	if (Pcur->ps != NULL) {
		Pcur->ps->age = Pcur->ps->age +  penambahan;
	}
	bool Resmi = true;
	if(Pcur->fs != NULL) {
		while (Pcur != NULL) {
			if (Pcur->fs != 0 && Resmi) {
				Pcur = Pcur->fs;
				PcurAT = PcurAT->fs;
				if(!isRoot(X,Pcur)){
					Pcur->age = Pcur->age + penambahan;
					if (PcurAT->status == true) {
						PcurAT->age = PcurAT->age + penambahan;
					}
					if (Pcur->ps != NULL) {
						Pcur->ps->age = Pcur->ps->age + penambahan;
					}
				}
				
			} else if (Pcur->nb != NULL) {
				Pcur = Pcur->nb;
				PcurAT = PcurAT->nb;
				if(!isRoot(X,Pcur)){
					Pcur->age = Pcur->age + penambahan;
					if (PcurAT->status == true) {
						PcurAT->age = PcurAT->age + penambahan;
					}
					if (Pcur->ps != NULL) {
					Pcur->ps->age = Pcur->ps->age + penambahan;
				}
				}
				Resmi = true;
			} else {
				Pcur = Pcur->pr;
				PcurAT = PcurAT->pr;
				Resmi = false;
			}
		}
	} 
}

int countAnak(Root X ,nbAddr node) {
	nbAddr Pcur;
	bool Resmi;
	int index;
	
	index = 0;
	Resmi = true;
	Pcur = X.root;
	if(Pcur->fs != NULL) {
		while (Pcur != NULL) {
			if (Pcur->fs != 0 && Resmi) {
				Pcur = Pcur->fs;
				if (!isRoot(X,Pcur)) {
					if (strcmp(node->nama,Pcur->parent) == 0) { 
						index++;
					}
				}
			} else if (Pcur->nb != NULL) {
				Pcur = Pcur->nb;
				if (!isRoot(X,Pcur)) {
					if (strcmp(node->nama,Pcur->parent) == 0)
					{ index++;}
				}
				Resmi = true;
			} else {
				Pcur = Pcur->pr;
				Resmi = false;
			}
		}
	} 
	return index;
}

int countPenerus(Root X, infotype nama) {
	nbAddr Pcur;
	bool Resmi;
	int index;
	
	index = 1;
	Resmi = true;
	Pcur = X.root;
	if(Pcur->fs != NULL) {
		while (Pcur != NULL) {
			if (Pcur->fs != 0 && Resmi) {
				Pcur = Pcur->fs;
				if (!isRoot(X,Pcur)) {
					if (strcmp(nama,Pcur->nama) == 0)
					{ return index;}
					index++;
				}
			} else if (Pcur->nb != NULL) {
				Pcur = Pcur->nb;
				if (!isRoot(X,Pcur)) {
					if (strcmp(nama,Pcur->nama) == 0)
					{ return index;}
					index++;
				}
				Resmi = true;
			} else {
				Pcur = Pcur->pr;
				Resmi = false;
			}
		}
	} 
}


// tree 2

bool isEmptyAT(anAddr *node) {
	return node == NULL;
}

bool isRootAT(ATRoot X, anAddr node) {
	return X.root == node;
}

void insertNodeAT(infotype nama, bool gender, anAddr parent) {
    anAddr temp;
    anAddr newnode;
    newnode = (ANode*)malloc(sizeof(ANode));
    if (newnode == NULL) {
        printf("Error,alokasi gagal");
        exit(1);
    }
        newnode->nama = nama;
        newnode->gender = gender;
        newnode->parent = parent->nama;
        newnode->fs = NULL;
        newnode->nb = NULL;
        newnode->pr = parent;
		newnode->age = 0;
		newnode->pair = "";
		newnode->status = true; // hidup
		newnode->ydeath = 0;

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

anAddr searchNodeAT(ATRoot X,infotype nama) {
	anAddr Pcur;
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

bool setDeleteAT(anAddr person, int tahun) {
    if (person != NULL) {
        person->status = false;
        person->ydeath = tahun;
		if (person->status == false) {
			printf("\tPembacokan BERHASIL.\n");
		} else {
			printf("\tPembacokan GAGAL.\n");
		}
		return true;
    } else {
		return false;
	}
}

void displayFamilyAT(anAddr X, int Level) {
	if (X != NULL) {
    	printf("\t");
        if (X->nama != NULL && strcmp(X->nama, "") != 0) {
            int i;
            for (i = 1; i <= Level; i++) {
                if (i < Level) {
                    printf("\t|  ");
                }else {
                    printf("\t|--");
                }
            }
            if (X->status) {
				printf("%s (hidup)\n", X->nama);
			} else {
				printf("%s (wafat)\n", X->nama);
			}
		}
        displayFamilyAT(X->fs, Level + 1);
        displayFamilyAT(X->nb, Level);
    }
}