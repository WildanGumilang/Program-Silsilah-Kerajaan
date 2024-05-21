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
				if (king.root == NULL && King.root == NULL) {
					insertKing(&king, &King, tahun);
				}else {
					insertBangsawan(&king, &King, tahun);
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
					insertMate(king, King, tahun);
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
					showDetailNodeMati(king, King, namaNode, personAT);
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
				deleteBangsawan(&king, King, Delete, tahun);
					if (runtuh) {
						printf("\tKERAJAAN INI TELAH RUNTUH, YANG TERSISA HANYALAH CERITA. \n");
					}
				}
				system("pause");
			}
			break;
			case '5' :
				aboutKerajaan(king, King, tahun, runtuh);
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


