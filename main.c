#include <stdio.h>
#include <conio.h>
#include "header.h"

int main() {
	Root king;
	king.root = NULL;
	char pilMenu[10];
	int tahun;
	introSilan();
	printf("\n\tTahun Kerajaan : ");
	scanf("%d", &tahun);
	
	for(;;) {
		fflush(stdin);
		system("cls");
		displayNamaKingdom();
		printf("\n\t\t===== WELCOME TO THE KINGDOM OF ENGLAND =====\n\n");
		printf("\t[1] Tambah Bangsawan\n");
		printf("\t[2] Tambah Pasangan\n");
		printf("\t[0] Keluar\n\n");
		printf("\tMasukkan pilihan : ");
		gets(pilMenu);
		char choice = pilMenu[0];
		switch(choice) {
			case '1': 
				infotype name;
				name = (infotype) malloc(sizeof(infotype));
				infotype parent;
				parent = (infotype) malloc(sizeof(infotype));
				char jk;
				bool G;
				if (king.root == NULL)
				{
					system("cls");
					printf("\n\t======================== TAMBAH BANGSAWAN ========================\n\n");
					printf("\tMasukkan Nama Bangsawan : ");
					scanf("%s", name);
					do{
						printf("\tJenis Kelamin (L/P) : ");
						scanf(" %c", &jk);
						if(jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p' ){
							printf("\tData Jenis Kelamin Tidak Sesuai, Silahkan Masukkan yang Sesuai.\n");
						}
					} while (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p' );
					
					int umur;
					do{
						printf("\tUsia : ");
						scanf("%d", &umur);
						if( umur < 18 ){
							printf("\tUsia tidak terpenuhi, masukkan usia yang valid.\n");
						}
					} while ( umur < 18 );
					infotype status;
					if(jk == 'L' || jk == 'l'){
						G = TRUE;
						status = "Raja";
					} else if (jk == 'P' || jk == 'p')
					{
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
					printf("\n\tSelamat Kepada %s Telah Menjadi %s Baru di Kerajaan Ini.\n\n\t", king.root->nama,status);
					system("pause");
				}else {
					nbAddr pr;
					infotype child;
					child = (infotype) malloc(sizeof(infotype));
					parent = (infotype) malloc(sizeof(infotype));
					do
					{
					system("cls");
					printf("\n\t======================== TAMBAH BANGSAWAN ========================\n\n");
					printf("\n\tMasukkan Nama Orang Tua Bangsawan : ");
					scanf("%s", parent);
					pr = searchNode(king,parent);
					if(pr == NULL){
						printf("\n\tData '%s' Tidak Ada, Silahkan Masukkan Nama Lain.\n", parent);
					} else if(isSingle(pr)){
						printf("\n\t%s Belum Menikah, Belum Bisa Mempunyai Anak.\n",pr->nama);
					}
					
					} while (pr == NULL || isSingle(pr));

					do
					{
					printf("\n\tNama Anak : ");
					scanf("%s", child);
						if(searchNode(king,child) != NULL){
							printf("\n\tNama Sudah Ada, Silahkan Masukkan Nama Lain.\n");
						}
					} while (searchNode(king,child) != NULL);
					
					do
					{
					printf("\tJenis kelamin (L/P) : ");
					scanf(" %c", &jk);
						if(jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p' ){
							printf("\n\tData Jenis Kelamin Tidak Sesuai, Silahkan Masukkan yang Sesuai.\n");
						}
					} while (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p' );
					infotype gender;
					if(jk == 'L' || jk == 'l'){
						G = TRUE;
						gender = "Putra";
					} else if (jk == 'P' || jk == 'p')
					{
						G = FALSE;
						gender = "Putri";
					}
					insertNode(child,G,pr);
					printf("\n\tPada tahun %d, telah lahir '%s', %s dari :\n\t\t\t-%s\n\t\t\t-%s .\n\n\t",tahun,child,gender,pr->nama,pr->ps->nama);
					 system("pause");
				}
				break;
			case '2':
			if (king.root == NULL)
			{
				system("cls");
				printf("\n\t=============================== MEMILIH PASANGAN ===============================\n\n");
				printf("\tTENTUKAN DULU PEMIMPIN KERAJAAN\n\n\t");
				 system("pause");
			}else {
			infotype bride;
			bride = (infotype) malloc(sizeof(infotype));
			nbAddr mates;
            mateAddr pair;
			infotype soulmate;
			soulmate = (infotype) malloc(sizeof(infotype));
			system("cls");
			printf("\n\t=============================== MEMILIH PASANGAN ===============================\n\n");
			do{
				printf("\tNama Bangsawan : ");
				scanf("%s", bride);
				mates = searchNode(king,bride);
						if(mates == NULL){
							printf("\tNama Tidak Ada, Silahkan Masukkan Nama Lain.\n");
						} else if(mates->ps != NULL){
							printf("\tBangsawan Ini Sudah Memiliki Pasangan, Tidak Bisa Menikah Lagi.\n");
							 system("pause");
						}else if(mates->age < 6){
							printf("\tUsia masih tidak mencukupi\n");
						}
					} while (mates == NULL || mates->age < 6);
					
					if (mates->ps != NULL)
					{
						break;
					}
					
					if(mates->gender == FALSE){
						printf("\tNama Suami Bangsawan : ");
					} else{
						printf("\tNama Istri Bangsawan : ");
					}
				scanf("%s",soulmate);
				int umur;
				do{
					printf("\tUsia : ");
					scanf("%d", &umur);
						if(umur < 6 || umur > 150){
							printf("\n\tUsia tidak valid, harap masukkan kembali.\n");
						}
					} while (umur < 6 || umur > 150);
                
                do{
					printf("\tJenis kelamin (L/P) : ");
					scanf(" %c", &jk);
						if(jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p' ){
							printf("\n\tData Jenis Kelamin Tidak Sesuai, Silahkan Masukkan yang Sesuai.\n");
						}
					} while (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p' );
					
				setMate(mates,soulmate, jk, umur);
				printf("\n\tPada tahun %d, %s dan %s menikah.\n\n\t",tahun,bride,soulmate);
				 system("pause");
				}
				break;
	}
	return 0;
}



