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
	if (strcmp(nama,Pcur->nama) == 0) { 
		return Pcur;
	}
	infotype gender;
		while (Pcur != NULL) {
		if (Pcur->fs != 0 && Resmi) {
			Pcur = Pcur->fs;
				if (strcmp(nama,Pcur->nama) == 0) { 
					return Pcur;
					}
		} else if (Pcur->nb != NULL) {
			Pcur = Pcur->nb;
				if (strcmp(nama,Pcur->nama) == 0) { 
					return Pcur;
					}
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

void insertKing(Root *king, ATRoot *King, int tahun) {
    infotype name = (infotype) malloc(sizeof(infotype));
	infotype parent = (infotype) malloc(sizeof(infotype));
    char jk;
    bool G;

    system("cls");
    printf("\n\t======================== TAMBAH BANGSAWAN ========================\n\n");
    printf("\tMasukkan Nama Raja atau Ratu: ");
    gets(name);

    do {
        printf("\tJenis Kelamin (L/P): ");
        scanf(" %c", &jk);
        if (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p') {
            printf("\tJenis Kelamin Tidak Valid, Silahkan Masukkan yang Sesuai.\n");
        }
    } while (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p');

    int umur;
    do {
        printf("\tUsia: ");
        scanf("%d", &umur);
        if (umur < 40) {
            printf("\tRaja atau Ratu Pertama Minimal Berusia 40 Tahun.\n");
        }
    } while (umur < 40);

    const char *status;
    if (jk == 'L' || jk == 'l') {
        G = true;
        status = "Raja";
    } else if (jk == 'P' || jk == 'p') {
        G = false;
        status = "Ratu";
    }

    // Tree 1
    nbAddr lead = (TNode *)malloc(sizeof(TNode));
    lead->nama = name;
    lead->gender = G;
    lead->age = umur;
    lead->fs = NULL;
    lead->nb = NULL;
    lead->pr = NULL;
    lead->ps = NULL;
    king->root = lead;

    // Tree 2
    anAddr head = (ANode *)malloc(sizeof(ANode));
    head->nama = name;
    head->gender = G;
    head->age = umur;
    head->fs = NULL;
    head->nb = NULL;
    head->pr = NULL;
    head->pair = "";
    head->status = true;
    head->ydeath = 0;
    King->root = head;

    printf("\n\tPujian tinggi bagi %s yang kini memegang peran sebagai %s dalam sejarah Kerajaan ini.\n\n\t", king->root->nama, status);

    const char *filetree = "sejarah_kerajaan.txt";
    saveTreeToFile(*king, filetree, tahun, name, true);
    system("pause");
}

bool deleteNode(Root * X, infotype nama, int tahun){
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
		
		const char* filenode = "daftar_raja.txt";
		saveNodeToFile(filenode, nDel, tahun);
		
		nbAddr nextKing = nDel->fs;
		(*X).root = nextKing;
		if(nextKing == NULL){
		printf("\tTIDAK ADA PENERUS KERAJAAN\n\n\t");
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
    if (Pcur->fs != NULL) {
        printf("\n\t==========================================\n");
        printf("\t|         GARIS SUKSESI KERAJAAN          |\n");
        printf("\t==========================================\n");
        while (Pcur != NULL) {
            if (Pcur->fs != 0 && Resmi) {
                Pcur = Pcur->fs;
                if (!isRoot(X, Pcur)) {
                    printf("\t| \033[0m \033[1;32m%d. %s\n", index, Pcur->nama);
					printf("\033[0m \033[38;2;255;165;0m");
                    printf("\t------------------------------------------\n");
                    index++;
                }
            } else if (Pcur->nb != NULL) {
                Pcur = Pcur->nb;
                if (!isRoot(X, Pcur)) {
                    printf("\t| \033[0m \033[1;32m%d. %s\n", index, Pcur->nama);
					printf("\033[0m \033[38;2;255;165;0m");
                    printf("\t------------------------------------------\n");
                    index++;
                }
                Resmi = true;
            } else {
                Pcur = Pcur->pr;
                Resmi = false;
            }
        }
        printf("\t==========================================\n");
    } else {
        printf("\t==========================================\n");
        printf("\t| Raja di Kerajaan Ini Belum Memiliki Penerus |\n");
        printf("\t==========================================\n");
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
            printf("\033[0m \033[1;32m%s\n", X->nama);
			printf("\033[0m \033[38;2;255;165;0m"); // Reset warna ke default
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
void showDetailNode(Root X, ATRoot x, infotype node) {

	nbAddr person;
	person = searchNode(X, node);
	if (person == NULL) {
		anAddr personAT;
		personAT = searchNodeAT(x, node);
		showDetailNodeMati(X, x, node, personAT);
	} else {
		printf("\n\t========================= DETAIL BANGSAWAN HIDUP =========================\n\n");
		
		if (isRoot(X, person)) {
			printf("\tNama Bangsawan\t: \033[0m \033[1;32m%s\033[0m \033[38;2;255;165;0m\n", person->nama);
			printf("\tUsia\t\t: %d\n", person->age);
		} else {
			infotype gender = (person->gender == true) ? "Putra" : "Putri";
			printf("\tNama Bangsawan\t: \033[0m \033[1;32m%s\033[0m \033[38;2;255;165;0m %s dari %s \n", person->nama, gender, person->parent);
			printf("\tUsia\t\t: %d\n", person->age);
			printf("\tPewaris Tahta \t: ke-%d\n", countPenerus(X, person->nama));
		}
		if (isSingle(person)) {
			printf("\tStatus \t\t: Belum Menikah\n");
		} else {
			printf("\tStatus \t\t: Sudah Menikah\n");
			printf("\tPasangan \t: %s\n", person->ps->nama);
			printf("\tUsia Pasangan \t: %d\n", person->ps->age);
			int jumlahAnak = countAnak(X, person);
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
					if (strcmp(node->nama,Pcur->parent) == 0){
						index++;
					}
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
					if (strcmp(nama,Pcur->nama) == 0) {
						return index;
						}
					index++;
				}
			} else if (Pcur->nb != NULL) {
				Pcur = Pcur->nb;
				if (!isRoot(X,Pcur)) {
					if (strcmp(nama,Pcur->nama) == 0) { 
						return index;
					}
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
	if (strcmp(nama,Pcur->nama) == 0) { 
		return Pcur;
	}

	infotype gender;
		while (Pcur != NULL) {
		if (Pcur->fs != 0 && Resmi) {
			Pcur = Pcur->fs;
				if (strcmp(nama,Pcur->nama) == 0) { 
					return Pcur;
				}
		} else if (Pcur->nb != NULL) {
			Pcur = Pcur->nb;
				if (strcmp(nama,Pcur->nama) == 0) { 
					return Pcur;
					}
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
                printf("\033[0m \033[1;32m%s\n", X->nama); // Warna hijau
            } else {
                printf("\033[0m \033[1;31m%s\n", X->nama); // Warna merah
            }
            
            printf("\033[0m \033[38;2;255;165;0m"); // Reset warna ke default
		}
        displayFamilyAT(X->fs, Level + 1);
        displayFamilyAT(X->nb, Level);
    }
}

int countGenerasi(ATRoot x) {
    if (x.root == NULL) {
		return 0;
	}
    int depth = 1;
    nbAddr currentNode = x.root;
    int currentDepth = 1;

    while (currentNode != NULL) {
        if (currentNode->fs != NULL) {
            currentNode = currentNode->fs;
            currentDepth++;
            if (currentDepth > depth) {
                depth = currentDepth;
            }
        } else {
            while (currentNode != NULL && currentNode->nb == NULL) {
                currentNode = currentNode->pr;
                currentDepth--;
            }
            if (currentNode != NULL) {
                currentNode = currentNode->nb;
            }
        }
    }
    return depth;
}

void saveNodeToFile(const char* filename, nbAddr node, int tahun) {
    FILE *fp;
    fp = fopen(filename, "a");
    if (node == NULL) {
        printf("Node Tidak ada.\n");
        return;
    }
    if (fp == NULL) {
        printf("Gagal Membuka file.\n");
    } else {
        fprintf(fp, "\n");
        fprintf(fp, "=================================================\n");
        fprintf(fp, "|                   BANGSAWAN                   |\n");
        fprintf(fp, "=================================================\n");
        fprintf(fp, "| Nama          : %-30s |\n", node->nama);
        fprintf(fp, "| Umur          : %-30d |\n", node->age);
        fprintf(fp, "| Gender        : %-30s |\n", node->gender ? "Laki-laki" : "Perempuan");
        fprintf(fp, "| Nama Pasangan : %-30s |\n", (node->ps != NULL) ? node->ps->nama : "Tidak Ada");
        fprintf(fp, "| Tahun Kematian: %-30d |\n", tahun);
        fprintf(fp, "=================================================\n");
        fprintf(fp, "\n");
        fclose(fp);
    }
}


void writeFamilyToFile(FILE *file, nbAddr X, int Level) {
    if (X != NULL) {
        fprintf(file, "\t");
        if (X->nama != NULL && strcmp(X->nama, "") != 0) {
            int i;
            for (i = 1; i <= Level; i++) {
                if (i < Level) {
                    fprintf(file, "\t|  ");
                } else {
                    fprintf(file, "\t|--");
                }
            }
            fprintf(file, "%s\n", X->nama);
        }
        writeFamilyToFile(file, X->fs, Level + 1);
        writeFamilyToFile(file, X->nb, Level);
    }
}

void saveTreeToFile(Root tree, const char *filename, int tahun, infotype nama, bool tambah) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Gagal membuka file.\n");
        return;
    }

    fprintf(file, "===========================================================\n");
    fprintf(file, "                     Update Silsilah Kerajaan              \n");
    fprintf(file, "===========================================================\n\n");

    fprintf(file, "Tahun : %d\n", tahun);
    if (tambah) {
        fprintf(file, "Telah lahir seorang bangsawan dengan nama : %s\n", nama);
    } else {
        fprintf(file, "Telah gugur seorang bangsawan dengan nama : %s\n", nama);
    }
	fprintf(file, "Silsilah Kerajaan setelah peristiwa ini :\n");
    writeFamilyToFile(file, tree.root, 0);
    fprintf(file, "\n===========================================================\n\n");

    fclose(file);
}

void printFileContent(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Gagal membuka file.\n");
        return;
    }
	system("cls");
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

int countNode(nbAddr root) {
    if (root == NULL) {
        return 0;
    }
    nbAddr Pcur = root;
    int count = 0;
    bool Resmi = true;
    while (Pcur != NULL) {
        if (Resmi) {
            count++;
        }
        if (Pcur->fs != NULL && Resmi) {
            Pcur = Pcur->fs;
        } else if (Pcur->nb != NULL) {
            Pcur = Pcur->nb;
            Resmi = true;
        } else {
            Pcur = Pcur->pr;
            Resmi = false;
            while (Pcur != NULL && Pcur->nb == NULL) {
                Pcur = Pcur->pr;
            }
            if (Pcur != NULL) {
                Pcur = Pcur->nb;
                Resmi = true;
            }
        }
    }
    return count;
}

void insertBangsawan(Root *king, ATRoot *King, int tahun) {
    infotype name = (infotype)malloc(100 * sizeof(char));
    infotype parent = (infotype)malloc(100 * sizeof(char));
    char jk;
    bool G;

    nbAddr pr;
    anAddr prAT;
    infotype child = (infotype)malloc(100 * sizeof(char));

    do {
        system("cls");
        printf("\n\t============================================================\n");
        printf("\t=                  TAMBAH BANGSAWAN                         =\n");
        printf("\t============================================================\n\n");
        printf("\tMasukkan Nama Orang Tua dari Bangsawan: ");
        gets(parent);
        pr = searchNode(*king, parent);
        prAT = searchNodeAT(*King, parent);
        if (pr == NULL) {
            printf("\n\t'%s' Tidak Ada dalam Kerajaan, Silahkan Masukkan Nama Lain.\n", parent);
        } else if (isSingle(pr)) {
            printf("\n\t%s Belum Menikah, Belum Bisa Memiliki Anak.\n", pr->nama);
        }
    } while (pr == NULL || isSingle(pr));

    do {
        printf("\n\tNama Bangsawan: ");
        gets(child);
        if (searchNode(*king, child) != NULL) {
            printf("\n\tNama Sudah Ada dalam Kerajaan, Bangsawan Tidak diperbolehkan Memiliki Nama yang Sama. Silahkan Masukkan Nama Lain.\n");
        }
    } while (searchNode(*king, child) != NULL);

    do {
        printf("\tJenis kelamin (L/P): ");
        scanf(" %c", &jk);
        if (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p') {
            printf("\n\tJenis Kelamin Tidak Valid, Silahkan Masukkan yang Sesuai.\n");
        }
    } while (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p');

    infotype gender;
    if (jk == 'L' || jk == 'l') {
        G = true;
        gender = "Putra";
    } else if (jk == 'P' || jk == 'p') {
        G = false;
        gender = "Putri";
    }
    insertNode(child, G, pr);
    insertNodeAT(child, G, prAT);

    printf("\n\t=========================================\n");
    printf("\t=  Pada tahun %d, telah lahir '%s', %s dari :\n", tahun, child, gender);
    printf("\t=  - %s\n", pr->nama);
    printf("\t=  - %s\n", pr->ps->nama);
    printf("\t=========================================\n\n");

    const char* filetree = "sejarah_kerajaan.txt";
    saveTreeToFile(*king, filetree, tahun, child, true);
    system("pause");
}

void insertMate(Root x, ATRoot X, int tahun) {

	char jk;
	infotype bride;
	bride = (infotype) malloc(sizeof(infotype));
	nbAddr mates;
	mateAddr pair;
	infotype soulmate;
	soulmate = (infotype) malloc(sizeof(infotype));
    int umur;

    system("cls");
    printf("\n\t==============================================================\n");
    printf("\t=                 MEMILIH PASANGAN                             =\n");
    printf("\t==============================================================\n\n");
    do {
        printf("\tMasukkan Nama Bangsawan: ");
        gets(bride);
        mates = searchNode(x, bride);
        if (mates == NULL) {
            printf("\n\tNama '%s' tidak ditemukan dalam Kerajaan. Masukkan nama lain.\n", bride);
        } else if (mates->ps != NULL) {
            printf("\n\t%s sudah memiliki pasangan. Tidak dapat menikah lagi.\n", bride);
            system("pause");
            return;
        } else if (mates->age < 20) {
            printf("\n\tUsia minimal untuk menikah adalah 20 tahun.\n");
        }
    } while (mates == NULL || mates->age < 20);

    if (mates->ps != NULL) {
        return;
    }

    if (mates->gender == false) {
        printf("\tMasukkan Nama Suami Bangsawan: ");
    } else {
        printf("\tMasukkan Nama Istri Bangsawan: ");
    }
    gets(soulmate);

    do {
        printf("\tMasukkan Usia Pasangan: ");
        scanf("%d", &umur);
        if (umur < 18) {
            printf("\n\tUsia minimal pasangan adalah 18 tahun. Masukkan usia yang sesuai.\n");
        }
    } while (umur < 18);

    do {
        printf("\tMasukkan Jenis Kelamin Pasangan (L/P): ");
        scanf(" %c", &jk);
        if (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p') {
            printf("\n\tJenis Kelamin tidak valid. Masukkan yang sesuai (L/P).\n");
        }
    } while (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p');

    setMate(mates, soulmate, X, umur, jk);
    printf("\n\tPada tahun %d, '%s' dan '%s' resmi menikah.\n\n\t", tahun, bride, soulmate);
    system("pause");
}

void showDetailNodeMati(Root x, ATRoot X, infotype nama, anAddr person) {
    anAddr personAT = person;

    if (personAT == NULL) {
        printf("\n\t========================= DETAIL BANGSAWAN TIDAK DITEMUKAN =========================\n\n");
        printf("\t\tBangsawan tidak ditemukan atau nama Bangsawan salah.\n\n");
        system("pause");
    } else {
        printf("\n\t========================= DETAIL BANGSAWAN MATI =========================\n\n");

        if (isRootAT(X, personAT)) {
            printf("\tNama Bangsawan\t: \033[0m \033[1;31m%s\033[0m \033[38;2;255;165;0m\n", personAT->nama);
            printf("\033[0m \033[38;2;255;165;0m");
        } else {
            infotype gender = (personAT->gender == true) ? "Putra" : "Putri";
            printf("\tNama Bangsawan\t: \033[0m \033[1;31m%s\033[0m \033[38;2;255;165;0m %s dari %s \n", personAT->nama, gender, personAT->parent);
        }
        if (personAT->pair == NULL || strcmp(personAT->pair, "") == 0) {
            if (personAT->status == false) {
                printf("\tStatus \t\t: Telah Wafat di usia %d pada tahun %d\n", personAT->age, personAT->ydeath);
            } else {
                printf("\tStatus \t\t: Masih Hidup, %d tahun\n", personAT->age);
            }
            printf("\tStatus \t\t: Belum Menikah\n");
        } else {
            if (personAT->status == false) {
                printf("\tStatus \t\t: Telah Wafat di usia %d pada tahun %d\n", personAT->age, personAT->ydeath);
            } else {
                printf("\tStatus \t\t: Masih Hidup, %d tahun\n", personAT->age);
            }
            printf("\tStatus \t\t: Sudah Menikah\n");
            printf("\tPasangan \t: %s\n", personAT->pair);
            printf("\n");
        }
        system("pause");
    }
}

void deleteBangsawan(Root* x, ATRoot X, infotype Delete, int tahun) {
    if (deleteNode(x, Delete, tahun)) {
        const char* filetree = "sejarah_kerajaan.txt";
        saveTreeToFile(*x, filetree, tahun, Delete, false);

        anAddr deleteAT = searchNodeAT(X, Delete);
        if (setDeleteAT(deleteAT, tahun)) {
            printf("\tPeristiwa Ini Akan dikenang, %s Akan selalu diingat dalam Kerajaan Ini.\n\n", Delete);
        }
    }
}

void aboutKerajaan(Root x, ATRoot X, int tahun, bool runtuh) {
    char pilih[10];
    if (!runtuh && x.root == NULL) {
        printf("\n\tKerajaan Ini belum Memiliki Anggota\n");
        system("pause");
        return;
    }
    int selectedOption = 1;
    while (1) {
        system("cls");
        printf("\n\n\n\n\n");
        if (!runtuh) {
            printf("\n\t\t\t\t\t=============================================================\n");
            printf("\t\t\t\t\t=                       DETAIL KERAJAAN                      =\n");
            printf("\t\t\t\t\t=============================================================\n");
            printf("\t\t\t\t\tTahun\t\t\t: %d\n", tahun);
            printf("\t\t\t\t\tNama Kerajaan\t\t: Kingdom of the Netherlands\n");
            printf("\t\t\t\t\tNama Raja/Ratu\t\t: %s \n", x.root->nama);
            printf("\t\t\t\t\tGenerasi Terakhir\t: Generasi ke-%d\n", countGenerasi(X));
            printf("\t\t\t\t\tJumlah Bangsawan Aktif\t: %d\n\n", countNode(x.root));
        }
        const char *highlight = "\033[0m \033[38;2;255;215;0m"; // warna highlight
        const char *reset = "\033[0m \033[38;2;255;165;0m"; // warna reset

        printf("\t\t\t\t\t\t==================================================\n");
        printf("\t\t\t\t\t\t=          DETAIL LAIN TENTANG KERAJAAN          =\n");
        printf("\t\t\t\t\t\t==================================================\n\n");

        printf("\t\t\t\t\t\t==================================================\n");
        printf("\t\t\t\t\t\t                       MENU                      \n");
        printf("\t\t\t\t\t\t==================================================\n");
        printf("\t\t\t\t\t\t   %s%s [1] Tampilkan Garis Suksesi            %s\n", selectedOption == 1 ? highlight : " ", selectedOption == 1 ? ">>>" : "  ", selectedOption == 1 ? reset : "");
        printf("\t\t\t\t\t\t   %s%s [2] Tampilkan seluruh Silsilah Kerajaan        %s\n", selectedOption == 2 ? highlight : " ", selectedOption == 2 ? ">>>" : "  ", selectedOption == 2 ? reset : "");
        printf("\t\t\t\t\t\t   %s%s [3] Tampilkan Timeline Peristiwa       %s\n", selectedOption == 3 ? highlight : " ", selectedOption == 3 ? ">>>" : "  ", selectedOption == 3 ? reset : "");
        printf("\t\t\t\t\t\t   %s%s [4] Tampilkan Pendahulu yang Pernah    \n\t\t\t\t\t\t            Menjadi Raja%s\n", selectedOption == 4 ? highlight : " ", selectedOption == 4 ? ">>>" : "  ", selectedOption == 4 ? reset : "");
        printf("\t\t\t\t\t\t   %s%s [0] Kembali                            %s\n", selectedOption == 0 ? highlight : " ", selectedOption == 0 ? ">>>" : "  ", selectedOption == 0 ? reset : "");
        printf("\t\t\t\t\t\t==================================================\n");

        int ch = getch();
        switch (ch) {
            case 72:  // Up arrow key
                selectedOption--;
                if (selectedOption < 0) selectedOption = 4;
                break;
            case 80:  // Down arrow key
                selectedOption++;
                if (selectedOption > 4) selectedOption = 0;
                break;
            case 13:  // Enter key
                switch (selectedOption) {
                    case 1:
                        if (!runtuh) {
                            showGarisSuksesi(x);
                            system("pause");
                        } else {
                            printf("\tKERAJAAN INI TELAH RUNTUH, YANG TERSISA HANYALAH CERITA. \n");
                            system("pause");
                        }
                        break;
                    case 2:
                        displayFamilyAT(X.root, 0);
                        system("pause");
                        break;
                    case 3:
                        printFileContent("sejarah_kerajaan.txt");
                        system("pause");
                        break;
                    case 4:
                        printFileContent("daftar_raja.txt");
                        system("pause");
                        break;
                    case 0:
                        return;
                    default:
                        printf("\n\tPilihanmu salah, pilih lagi!\n\t");
                        system("pause");
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void introCreator() {
    const char sentence[] = "\n\n\n\n\n\t\t\t\t\t\t\t\tCreated by : \n\n\t\t\t\t\t\tAlqan Nazra\t\t\t231511068\n\t\t\t\t\t\tMuhammad Wildan Gumilang\t231511087\n\t\t\t\t\t\tRyuki Haga Budiarto\t\t231511091\n\n\t\t\t\t\t\t\t1C-D3 Teknik Informatika \n\t\t\t\t\t\t\tPoliteknik Negeri Bandung\n\t\t\t\t\t\t\t\t  2024\n";
    int i;

    for (i = 0; sentence[i] != 0; i++) {
        Sleep(50);
        printf("%c", sentence[i]);
    }
    Sleep(100);
    system("pause");
    system("cls");
}

void displayMenu(int selectedOption) {
    const char *highlight = "\033[0m \033[38;2;255;215;0m";
    const char *reset = "\033[0m \033[38;2;255;165;0m";   

    printf("\t\t\t\t\t\t===========================================\n");
    printf("\t\t\t\t\t\t=         WELCOME TO THE KINGDOM           =\n");
    printf("\t\t\t\t\t\t=             OF NETHERLANDS               =\n");
    printf("\t\t\t\t\t\t===========================================\n\n");

    printf("\t\t\t\t\t\t===========================================\n");
    printf("\t\t\t\t\t\t                 MAIN MENU                 \n");
    printf("\t\t\t\t\t\t===========================================\n");
    printf("\t\t\t\t\t\t   %s%s [1] Tambah Bangsawan                 %s\n", selectedOption == 1 ? highlight : " ", selectedOption == 1 ? ">>>" : "", selectedOption == 1 ? reset : "");
    printf("\t\t\t\t\t\t   %s%s [2] Tambah Pasangan                  %s\n", selectedOption == 2 ? highlight : " ", selectedOption == 2 ? ">>>" : "", selectedOption == 2 ? reset : "");
    printf("\t\t\t\t\t\t   %s%s [3] Cari Bangsawan di Kerajaan Ini   %s\n", selectedOption == 3 ? highlight : " ", selectedOption == 3 ? ">>>" : "", selectedOption == 3 ? reset : "");
    printf("\t\t\t\t\t\t   %s%s [4] Bacok Bangsawan                  %s\n", selectedOption == 4 ? highlight : " ", selectedOption == 4 ? ">>>" : "", selectedOption == 4 ? reset : "");
    printf("\t\t\t\t\t\t   %s%s [5] Tentang Kerajaan                 %s\n", selectedOption == 5 ? highlight : " ", selectedOption == 5 ? ">>>" : "", selectedOption == 5 ? reset : "");
    printf("\t\t\t\t\t\t   %s%s [6] Lakukan Timeskip                 %s\n", selectedOption == 6 ? highlight : " ", selectedOption == 6 ? ">>>" : "", selectedOption == 6 ? reset : "");
    printf("\t\t\t\t\t\t   %s%s [0] Keluar                           %s\n", selectedOption == 0 ? highlight : " ", selectedOption == 0 ? ">>>" : "", selectedOption == 0 ? reset : "");
    printf("\t\t\t\t\t\t===========================================\n");
}