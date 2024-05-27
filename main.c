#include <stdio.h>
#include <conio.h>
#include "header.h"

int main() {
    Root king;
    ATRoot King;
    king.root = NULL;
    King.root = NULL;
    int pilMenu;
    int tahun;
    bool runtuh = false;
    int selectedOption = 1;

    printf("\033[1;36m");
    introCreator();
    printf("\033[0m \033[38;2;255;165;0m");

    printf("\n\tTahun Kerajaan : ");
    scanf("%d", &tahun);
    getchar();

    printf("\033[0m \033[38;2;255;215;0m");
    system("cls");
    printFileContent("assets/castle.txt");
    system("pause");
    system("cls");

    while (1) {
        fflush(stdin);
        printf("\033[0m \033[38;2;255;165;0m");
        system("cls");
        printf("\n\n\n\n");        
        printFileContent("assets/identity.txt");
        printf("\n");
        displayFamily(king.root, 0);
        printf("\n\n");
        displayMenu(selectedOption);

        // printf("\t\t\t\t\t\t===========================================\n");
        // printf("\t\t\t\t\t\t=                MAIN MENU                 =\n");
        // printf("\t\t\t\t\t\t===========================================\n");
        // printf("\t\t\t\t\t\t=    [1] Tambah Bangsawan                 =\n");
        // printf("\t\t\t\t\t\t=    [2] Tambah Pasangan                  =\n");
        // printf("\t\t\t\t\t\t=    [3] Cari Bangsawan di Kerajaan Ini   =\n");
        // printf("\t\t\t\t\t\t=    [4] Bacok Bangsawan                  =\n");
        // printf("\t\t\t\t\t\t=    [5] Tentang Kerajaan                 =\n");
        // printf("\t\t\t\t\t\t=    [6] Lakukan Timeskip                 =\n");
        // printf("\t\t\t\t\t\t=    [0] Keluar                           =\n");
        // printf("\t\t\t\t\t\t===========================================\n");
        // printf("\t\t\t\t\t\tPilihan Anda : ");
        // scanf("%d", &pilMenu);
        // getchar();

        int ch = getch();
        switch (ch) {
            case 72:  // Up arrow key
                selectedOption--;
                if (selectedOption < 0) selectedOption = 6;
                break;
            case 80:  // Down arrow key
                selectedOption++;
                if (selectedOption > 6) selectedOption = 0;
                break;
            case 13:  // Enter key
                switch (selectedOption) {
                    case 1: 
                        if (runtuh) {
                            printf("\tKERAJAAN INI TELAH RUNTUH\n");
                            system("pause");
                            break;
                        }
                        if (king.root == NULL && King.root == NULL) {
                            insertKing(&king, &King, tahun);
                        } else {
                            insertBangsawan(&king, &King, tahun);
                        }
                        break;
                    case 2:
                        if (runtuh) {
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
                    case 3:
                        if (king.root == NULL && !runtuh) {
                            system("cls");
                            printf("\tKerajaan Belum Terbentuk.\n\n\t");
                            system("pause");
                        } else if (runtuh) {
                            infotype namaNode;
                            namaNode = (infotype) malloc(sizeof(infotype));
                            system("cls");
                            printf("\tNama Bangsawan : ");
                            gets(namaNode);
                            anAddr personAT = searchNodeAT(King, namaNode);
                            showDetailNodeMati(king, King, namaNode, personAT);
                        } else {
                            infotype namaNode;
                            namaNode = (infotype) malloc(sizeof(infotype));
                            nbAddr info;
                            system("cls");
                            printf("\tNama Bangsawan : ");
                            gets(namaNode);
                            showDetailNode(king, King, namaNode);
                        }
                        break;
                    case 4:
                        if (runtuh) {
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
                            gets(Delete);
                            nbAddr del = searchNode(king, Delete);
                            if (isRoot(king, del)) {
                                if (del->fs == NULL) {
                                    runtuh = true;
                                }
                            }
                            deleteBangsawan(&king, King, Delete, tahun);
                            if (runtuh) {
                                printf("\tKERAJAAN INI TELAH RUNTUH, YANG TERSISA HANYALAH CERITA. \n");
                            }
                            system("pause");
                        }
                        break;
                    case 5:
                        aboutKerajaan(king, King, tahun, runtuh);
                        break;
                    case 6:
                        if (runtuh) {
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
                    case 0:
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
                break;
            default:
                break;
        }
    }
    printf("\033[0m");
    return 0;
}