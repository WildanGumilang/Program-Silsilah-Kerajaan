#include <stdio.h>
#include <conio.h>
#include "header.h"

int main() {
	Root king;
	ATRoot King;
	king.root = NULL;
	King.root = NULL;
	char pilMenu[10];
	int tahun;
	bool runtuh = false;
	printf("\n\tTahun Kerajaan : ");
	scanf("%d", &tahun);
	
	for(;;) {
		fflush(stdin);
		system("cls");
		displayFamily(king.root, 0);
		printf("\n");
		printf("\t===========================================\n");
		printf("\t=         WELCOME TO THE KINGDOM           =\n");
		printf("\t=             OF NETHERLANDS               =\n");
		printf("\t===========================================\n\n");

		printf("\t===========================================\n");
		printf("\t=                  MAIN MENU               =\n");
		printf("\t===========================================\n");
		printf("\t=  [1] Tambah Bangsawan                    =\n");
		printf("\t=  [2] Tambah Pasangan                     =\n");
		printf("\t=  [3] Cari Bangsawan di Kerajaan Ini      =\n");
		printf("\t=  [4] Bacok Bangsawan                     =\n");
		printf("\t=  [5] Tentang Kerajaan                    =\n");
		printf("\t=  [6] Lakukan Timeskip                    =\n");
		printf("\t=  [0] Keluar                              =\n");
		printf("\t===========================================\n");

		printf("\n\tMasukkan pilihan : ");



		gets(pilMenu);
		char choice = pilMenu[0];
		switch(choice) {
			case '1': 
				if (runtuh){
					printf("\tKERAJAAN INI TELAH RUNTUH\n");
					system("pause");
					break;
				}
				infotype name;
				name = (infotype) malloc(sizeof(infotype));
				infotype parent;
				parent = (infotype) malloc(sizeof(infotype));
				char jk;
				bool G;
				if (king.root == NULL && King.root == NULL) {
					system("cls");
					printf("\n\t======================== TAMBAH BANGSAWAN ========================\n\n");
					printf("\tMasukkan Nama Raja atau Ratu : ");
					scanf("%s", name);
					do {
						printf("\tJenis Kelamin (L/P) : ");
						scanf(" %c", &jk);
						if (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p') {
							printf("\tJenis Kelamin Tidak Valid, Silahkan Masukkan yang Sesuai.\n");
						}
					} while (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p');
					
					int umur;
					do {
						printf("\tUsia : ");
						scanf("%d", &umur);
						if (umur < 40) {
							printf("\tRaja atau Ratu Pertama Minimal Berusia 40 Tahun.\n");
						}
					} while (umur < 40);
					
					const char* status;
					bool G;
					if (jk == 'L' || jk == 'l') {
						G = TRUE;
						status = "Raja";
					} else if (jk == 'P' || jk == 'p') {
						G = FALSE;
						status = "Ratu";
					} 

					nbAddr lead;
					lead = (TNode*)malloc(sizeof(TNode));
					lead->nama = name;
					lead->gender = G;
					lead->age = umur;
					lead->fs = NULL;
					lead->nb = NULL;
					lead->pr = NULL;
					lead->ps = NULL;
					king.root = lead;

					// Tree 2
					anAddr head;
					head = (ANode*)malloc(sizeof(ANode));
					head->nama = name;
					head->gender = G;
					head->age = umur;
					head->fs = NULL;
					head->nb = NULL;
					head->pr = NULL;
					head->pair = "";
					head->status = true;
					head->ydeath = 0;
					King.root = head;

					printf("\n\tPujian tinggi bagi %s yang kini memegang peran sebagai %s dalam sejarah Kerajaan ini.\n\n\t", king.root->nama, status);

					const char* filetree = "sejarah_kerajaan.txt";
					saveTreeToFile(king, filetree, tahun, name, true);
					system("pause");
				}else {
					nbAddr pr;
					anAddr prAT;
					infotype child;
					child = (infotype) malloc(sizeof(infotype));
					parent = (infotype) malloc(sizeof(infotype));
					do {
						system("cls");
						printf("\n\t============================================================\n");
						printf("\t=                  TAMBAH BANGSAWAN                         =\n");
						printf("\t============================================================\n\n");
						printf("\tMasukkan Nama Orang Tua dari Bangsawan : ");
						scanf("%s", parent);
						pr = searchNode(king, parent);
						prAT = searchNodeAT(King, parent);
						if (pr == NULL) {
							printf("\n\t'%s' Tidak Ada dalam Kerajaan, Silahkan Masukkan Nama Lain.\n", parent);
						} else if (isSingle(pr)) {
							printf("\n\t%s Belum Menikah, Belum Bisa Memiliki Anak.\n", pr->nama);
						}
					} while (pr == NULL || isSingle(pr));

					do {
						printf("\n\tNama Bangsawan : ");
						scanf("%s", child);
						if (searchNode(king, child) != NULL) {
							printf("\n\tNama Sudah Ada dalam Kerajaan, Bangsawan Tidak diperbolehkan Memiliki Nama yang Sama. Silahkan Masukkan Nama Lain.\n");
						}
					} while (searchNode(king, child) != NULL);

					do {
						printf("\tJenis kelamin (L/P) : ");
						scanf(" %c", &jk);
						if (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p') {
							printf("\n\tJenis Kelamin Tidak Valid, Silahkan Masukkan yang Sesuai.\n");
						}
					} while (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p');

					infotype gender;
					const char* genderStr;
					if (jk == 'L' || jk == 'l') {
						G = TRUE;
						gender = "Putra";
						genderStr = "Putra";
					} else if (jk == 'P' || jk == 'p') {
						G = FALSE;
						gender = "Putri";
						genderStr = "Putri";
					}
					insertNode(child, G, pr);
					insertNodeAT(child, G, prAT);

					printf("\n\t=========================================\n");
					printf("\t=  Pada tahun %d, telah lahir '%s', %s dari :\n", tahun, child, genderStr);
					printf("\t=  - %s\n", pr->nama);
					printf("\t=  - %s\n", pr->ps->nama);
					printf("\t=========================================\n\n");

					const char* filetree = "sejarah_kerajaan.txt";
					saveTreeToFile(king, filetree, tahun, child, true);
					system("pause");
				}
				break;
			case '2':
				if (runtuh){
					printf("\tKERAJAAN INI TELAH RUNTUH\n");
					system("pause");
					break;
					}
				if (king.root == NULL) {
					system("cls");
					printf("\n\t==============================================================\n");
					printf("\t=                 MEMILIH PASANGAN                             =\n");
					printf("\t==============================================================\n\n");
					printf("\tKerajaan ini belum terbentuk. Silakan tentukan Raja/Ratu terlebih dahulu.\n\n\t");
					system("pause");
				} else {
					infotype bride;
					bride = (infotype) malloc(sizeof(infotype));
					nbAddr mates;
					mateAddr pair;
					infotype soulmate;
					soulmate = (infotype) malloc(sizeof(infotype));
					system("cls");
					printf("\n\t==============================================================\n");
					printf("\t=                 MEMILIH PASANGAN                             =\n");
					printf("\t==============================================================\n\n");
					do {
						printf("\tMasukkan Nama Bangsawan: ");    
						scanf("%s", bride);
						mates = searchNode(king, bride);
						if (mates == NULL) {
							printf("\n\tNama '%s' tidak ditemukan dalam Kerajaan. Masukkan nama lain.\n", bride);
						} else if (mates->ps != NULL) {
							printf("\n\t%s sudah memiliki pasangan. Tidak dapat menikah lagi.\n", bride);
							system("pause");
						} else if (mates->age < 20) {
							printf("\n\tUsia minimal untuk menikah adalah 20 tahun.\n");
						}
					} while (mates == NULL || mates->age < 20);
					
					if (mates->ps != NULL) {
						break;
					}
					
					if (mates->gender == FALSE) {
						printf("\tMasukkan Nama Suami Bangsawan: ");
					} else {
						printf("\tMasukkan Nama Istri Bangsawan: ");
					}
					scanf("%s", soulmate);
					int umur;
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
					
					setMate(mates, soulmate, King, umur, jk);
					printf("\n\tPada tahun %d, '%s' dan '%s' resmi menikah.\n\n\t", tahun, bride, soulmate);
					system("pause");
				}
				break;
			case '3':
			    if (king.root == NULL && !runtuh) {
			        system("cls");
			        printf("\tKerajaan Belum Terbentuk.\n\n\t");
			        system("pause");
			    } else if (runtuh) {
					infotype namaNode;
					namaNode = (infotype) malloc(sizeof(infotype));
					system("cls");
			        printf("\tNama Bangsawan : ");
			        scanf("%s", namaNode);
					anAddr personAT = searchNodeAT(King, namaNode);
					if (personAT == NULL) {
						printf("\n\t========================= DETAIL BANGSAWAN TIDAK DITEMUKAN =========================\n\n");
						printf("\t\tBangsawan tidak ditemukan atau nama Bangsawan salah.\n\n");
						system("pause");
					} else {
						printf("\n\t========================= DETAIL BANGSAWAN MATI =========================\n\n");
						
						if (isRootAT(King, personAT)) {
							printf("\tNama Bangsawan\t: \033[31m%s\033[0m\n", personAT->nama);
							printf("\033[0m");
						} else {
							infotype gender = (personAT->gender == true) ? "son" : "daughter";
							printf("\tNama Bangsawan\t: \033[31m%s\033[0m %s of %s \n", personAT->nama, gender, personAT->parent);
						}
						if (personAT->pair == "") {
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
				} else {
			        infotype namaNode;
					namaNode = (infotype) malloc(sizeof(infotype));
			        nbAddr info;
			        system("cls");
			        printf("\tNama Bangsawan : ");
			        scanf("%s", namaNode);
			        showDetailNode(king, King, namaNode);
			    }
			    break;
			case '4':
				if (runtuh){
					printf("\tKERAJAAN INI TELAH RUNTUH\n");
					system("pause");
					break;
				}
			if (king.root == NULL) {
				system("cls");
				printf("\n\t==============================================================\n");
				printf("\t=                    BACOK BANGSAWAN                          =\n");
				printf("\t==============================================================\n\n");
				printf("\tKerajaan ini belum terbentuk.\n\n\t");
				system("pause");
			} else {
				system("cls");
				printf("\n\t==============================================================\n");
				printf("\t=                    BACOK BANGSAWAN                          =\n");
				printf("\t==============================================================\n\n");
				infotype Delete;
				Delete = (infotype) malloc(sizeof(infotype));
				printf("\tMasukkan Nama Bangsawan yang Akan Dibacok : ");
				scanf("%s", Delete);
				nbAddr del = searchNode(king, Delete);
				if(isRoot(king, del)) {
					if(del->fs == NULL){
						runtuh = true;
					}
				}
				if (deleteNode(&king, Delete, tahun)) {
					const char* filetree = "sejarah_kerajaan.txt";
					saveTreeToFile(king, filetree, tahun, Delete, false);

					anAddr deleteAT = searchNodeAT(King, Delete);
					if (setDeleteAT(deleteAT, tahun)) {
						printf("\tPeristiwa Ini Akan dikenang, %s Akan selalu diingat dalam Kerajaan Ini.\n\n", Delete);
					}
					if (runtuh) {
						printf("\tKERAJAAN INI TELAH RUNTUH, YANG TERSISA HANYALAH CERITA. \n");
					}
				}
				system("pause");
			}
			break;
			case '5' :
				char pilih[10];
				for(;;) {
					system("cls");
					if (!runtuh) {
						printf("\n\t=============================================================\n");
						printf("\t=                       DETAIL KERAJAAN                      =\n");
						printf("\t=============================================================\n");
						printf("\tTahun\t\t\t: %d\n", tahun);
						printf("\tNama Kerajaan\t\t: Kingdom of the Netherlands\n");
						printf("\tNama Raja/Ratu\t\t: %s \n", king.root->nama);
						printf("\tGenerasi Terakhir\t: Generasi ke-%d\n", countGenerasi(King));
						printf("\tJumlah Bangsawan Aktif\t: %d\n\n", countNode(king.root));
					}
					printf("\t=============================================================\n");
					printf("\t=                    DETAIL LAIN TENTANG KERAJAAN            =\n");
					printf("\t=============================================================\n");
					printf("\t[1] Tampilkan Garis Suksesi\n");
					printf("\t[2] Tampilkan Keseluruhan Silsilah Kerajaan\n");
					printf("\t[3] Tampilkan Timeline Struktur Kerajaan\n");
					printf("\t[4] Tampilkan Bangsawan gugur yang Pernah Menjadi Pemimpin\n");
					printf("\t[0] Kembali\n\n");
					printf("\tMasukkan pilihan : ");

					gets(pilih);
					char choice = pilih[0];
					switch(choice) {
						case '1':
							if(!runtuh) {
								showGarisSuksesi(king);
								system("pause");
							} else {
								printf("\tKERAJAAN INI TELAH RUNTUH, YANG TERSISA HANYALAH CERITA. \n");
								system("pause");
							}
							break;
						case '2':
							displayFamilyAT(King.root, 0);
							system("pause");
							break;
						case '3':
							const char* filetree = "sejarah_kerajaan.txt";
							printFileContent(filetree);
							system("pause");
							break;
						case '4':
							const char* filenode = "daftar_raja.txt";
							printFileContent(filenode);
							system("pause");
							break;
						case '0':
							break;
						default:
							printf("\n\tPilihanmu salah, pilih lagi!\n\t");
							system("pause");
							break;
					}
					break;
				}
				break;
			case '6':
				if (runtuh){
					printf("\tKERAJAAN INI TELAH RUNTUH\n");
					system("pause");
					break;
				}
				if (king.root == NULL) {
					system("cls");
					printf("\n\t==================== TAMBAH TAHUN ====================\n\n");
					printf("\tKerajaan belum terbentuk. Harap tentukan Raja/Ratu terlebih dahulu.\n\n");
					system("pause");
				} else {
					system("cls");
					int tambah;
					printf("\n\t==================== TAMBAH TAHUN ====================\n\n");
					printf("\tTahun Saat Ini : %d\n\n", tahun);
					printf("\tMasukkan jumlah tahun yang ingin ditambahkan : ");
					scanf("%d", &tambah);
					if (tambah < 1) {
						printf("\n\tMasukkan angka yang valid. Penambahan tahun tidak bisa kurang dari 1.\n");
					} else {
						addTahun(&tahun, tambah, king, King);
						printf("\n\tPenambahan tahun berhasil.\n\tTahun saat ini sekarang : %d\n\n", tahun);
					}
					system("pause");
				}
				break;
			case '0':
				system("cls");
				printf("\n\t========================================================================\n");
				printf("\t=              TERIMA KASIH TELAH MENGGUNAKAN PROGRAM INI              =\n");
				printf("\t========================================================================\n\n");
				printf("\t  Semoga Kerajaan Ini diberkahi Oleh Allah Subhanahu wa ta'ala, aamiin.\n\n");
				printf("\t========================================================================\n\n\t");
				return 0;
			default:
				printf("\n\tPilihan tidak ada, silahkan Pilih Lagi!\n\n\t");
				system("pause");
				break;
		}
	}
	return 0;
}


