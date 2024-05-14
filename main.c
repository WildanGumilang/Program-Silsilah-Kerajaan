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
	printf("\n\tTahun Kerajaan : ");
	scanf("%d", &tahun);
	
	for(;;) {
		fflush(stdin);
		system("cls");
		displayFamily(king.root, 0);
		printf("\n\t\t===== WELCOME TO THE KINGDOM OF NETHERLAND =====\n\n");
		printf("\t[1] Tambah Bangsawan\n");
		printf("\t[2] Tambah Pasangan\n");
		printf("\t[3] Cari Bangsawan di Kerajaan Ini\n");
		printf("\t[4] Bacok Bangsawan\n");
		printf("\t[5] Tentang Kerajaan\n");
		printf("\t[6] Lakukan Timeskip\n");
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
				if (king.root == NULL && King.root == NULL)
				{
					system("cls");
					printf("\n\t======================== TAMBAH BANGSAWAN ========================\n\n");
					printf("\tMasukkan Nama Raja atau Ratu : ");
					scanf("%s", name);
					do{
						printf("\tJenis Kelamin (L/P) : ");
						scanf(" %c", &jk);
						if(jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p' ){
							printf("\tJenis Kelamin Tidak Valid, Silahkan Masukkan yang Sesuai.\n");
						}
					} while (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p' );
					
					int umur;
					do{
						printf("\tUsia : ");
						scanf("%d", &umur);
						if( umur < 40 ){
							printf("\tRaja atau Ratu Pertama Minimal Berusia 40 Tahun.\n");
						}
					} while ( umur < 40 );
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

					//tree 2
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
					printf("\n\tSelamat Kepada %s Telah Menjadi %s di Kerajaan Ini.\n\n\t", king.root->nama,status);
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
						printf("\n\tMasukkan Nama Orang Tua dari Bangsawan : ");
						scanf("%s", parent);
						pr = searchNode(king,parent);
						if(pr == NULL){
							printf("\n\t'%s' Tidak Ada dalam Kerajaan, Silahkan Masukkan Nama Lain.\n", parent);
						} else if(isSingle(pr)){
							printf("\n\t%s Belum Menikah, Belum Bisa Memiliki Anak.\n",pr->nama);
						}
					} while (pr == NULL || isSingle(pr));

					do
					{
						printf("\n\tNama Bangsawan : ");
						scanf("%s", child);
							if(searchNode(king,child) != NULL){
								printf("\n\tNama Sudah Ada dalam Kerajaan, Bangsawan Tidak diperbolehkan Memiliki Nama yang Sama. Silahkan Masukkan Nama Lain.\n");
							}
					} while (searchNode(king,child) != NULL);
					
					do
					{
						printf("\tJenis kelamin (L/P) : ");
						scanf(" %c", &jk);
							if(jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p' ){
								printf("\n\tJenis Kelamin Tidak Valid, Silahkan Masukkan yang Sesuai.\n");
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
					printf("\tKerajaan ini Belum Terbentuk. Silahkan Tentukan Raja/Ratu Terlebih Dahulu.\n\n\t");
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
								printf("\tNama Tidak Ada Dalam Kerajaan, Silahkan Masukkan Nama Lain.\n");
							} else if(mates->ps != NULL){
								printf("\tBangsawan Ini Sudah Memiliki Pasangan, Ia Tidak Bisa Menikah Lagi.\n");
								system("pause");
							}else if(mates->age < 20){
								printf("\tUsia Bangsawan Minimal Berusia 20 Tahun untuk Menikah.\n");
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
							if(umur < 18){
								printf("\n\tUsia Pasangan Minimal Berusia 18 Tahun. Silahkan Masukkan Usia yang Sesuai.\n");
							}
						} while (umur < 18);
					
					do{
						printf("\tJenis kelamin (L/P) : ");
						scanf(" %c", &jk);
							if(jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p' ){
								printf("\n\tJenis Kelamin Tidak Valid, Silahkan Masukkan yang Sesuai.\n");
							}
						} while (jk != 'L' && jk != 'P' && jk != 'l' && jk != 'p' );
						
					setMate(mates,soulmate, King, umur, jk);
					printf("\n\tPada tahun %d, %s dan %s menikah.\n\n\t",tahun,bride,soulmate);
					system("pause");
					}
					break;
			case '3':
			    if (king.root == NULL) {
			        system("cls");
			        printf("\tKerajaan Belum Terbentuk.\n\n\t");
			        system("pause");
			    } else {
			        infotype namaNode;
					namaNode = (infotype) malloc(sizeof(infotype));
			        nbAddr info;
			        system("cls");
			        printf("\tNama Bangsawan : ");
			        scanf("%s", namaNode);
			        showDetailNode(king,namaNode);
			    }
			    break;
			case '4':
			if (king.root == NULL){
				system("cls");
				printf("\n\t========================= BACOK BANGSAWAN =========================\n\n");
				printf("\tKerajaan Ini Belum Terbentuk.\n\n\t");
				system("pause");
			}else {
				system("cls");
				printf("\n\t========================= BACOK BANGSAWAN =========================\n\n");
				infotype Delete;
				Delete = (infotype) malloc(sizeof(infotype));
				printf("\tMasukkan Nama Bangsawan yang Akan Dibacok : ");
				scanf( "%s", Delete);
				deleteNode(&king,Delete);
				system("pause");
			}
			break;
			case '5' :
				char pilih[10];
				for(;;) {
					system("cls");
					printf("\n\t============= DETAIL KERAJAAN =============\n");
					printf("\tTahun\t\t: %d\n",tahun);
					printf("\tNama Kerajaan\t: Kingdom of the Netherlands\n");	
					printf("\tNama Raja/Ratu\t: %s \n", king.root->nama);
					printf("\tJumlah Generasi di Kerajaan\t:\n\n");
					printf("\t=============== DETAIL LAIN TENTANG KERAJAAN ===============\n");
					printf("\t[1] Tampilkan Garis Suksesi\n");
					printf("\t[2] Tampilkan Keseluruhan Silsilah Kerajaan\n");
					printf("\t[3] Tampilkan Bangsawan yang Pernah Menjadi Raja\n");
					printf("\t[0] Kembali\n\n");
					printf("\tMasukkan pilihan : ");
					gets(pilih);
					char choice = pilih[0];
					switch(choice) {
						case '1':
							showGarisSuksesi(king);
							system("pause");
							break;
						case '2':
						
							system("pause");
							break;
						case '3':
							
							system("pause");
							break;
						case '0':
							break;
						default:
							printf("\n\tPilihanmu salah, pilih lagi!\n\t");
							system("pause");
							break;
					}
				}
			case '6':
				if (king.root == NULL) {
					system("cls");
					printf("\n\t==================== TAMBAH TAHUN ====================\n\n");
					printf("\tKerajaan ini Belum Terbentuk. Silahkan Tentukan Raja/Ratu Terlebih Dahulu.\n\n\t");
					system("pause");
				} else {
				system("cls");
				int tambah ;
					printf("\n\t========================= TAMBAH TAHUN ==========================\n\n");
					printf("\n\tTahun Saat Ini : %d.\n\n\tTambah tahun :  ",tahun);
					scanf("%d",&tambah);
					if(tambah < 1){
						printf("\n\tAngka Tidak Valid, Silahkan Masukkan Kembali.");
					} else {
						addTahun(&tahun,tambah,king, King);
						printf("\n\tPenambahan tahun telah berhasil\n\tTahun saat ini : %d\n\n\t",tahun);
					}
					system("pause");
				}
				break;
			case '0':
				return 0;
			default:
				printf("\n\tPilihan tidak ada, silahkan Pilih Lagi!\n\n\t");
				system("pause");
				break;
		}
	}
	return 0;
}


