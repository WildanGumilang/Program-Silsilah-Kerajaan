#include "header.h"

int main()
{
    Root tree;
    tree.root = NULL;
    int pilihan,nilai,nilaiinduk;

    printf("Selamat Datang Pada kerjaan belanda");
    do
    {
        printf("\nOperasi Pohon Non-Biner\n");
        printf("1. Buat Keturunan\n");
        printf("2. Sisipkan Node\n");
         scanf("%d", &pilihan);
        nbAddr nodeHapus; // Pindahkan deklarasi ke bagian awal blok switch

        switch(pilihan) 
        {
            case 1:
            infotype inama;
            inama = (infotype)malloc(sizeof(infotype));
            infotype ortu;
            ortu = (infotype)malloc(sizeof(infotype));
            bool X;
            char sex;
            if (tree.root == NULL)
            {
                system("cls");
                printf("\nMasukkan nama keturunan");
                scanf("\n%s", inama);
                printf("\nMasukkan Kelamin");
                do
                {
                    printf ("\nJenis Kelamin (L/P)");
                    scanf("%c", &sex);
                } while (sex != 'L' && sex != 'l' && sex != 'l' && sex != 'p');
                int umur;
                printf ("\nUmur: ");
                scanf ("%d", &umur);
                if (sex == 'L' || sex == 'l')
                {
                    X = true;
                }
                if (sex == 'P' || sex == 'p')
                {
                    X = false;
                }
                
                nbAddr root;
                root = (TNode*)malloc(sizeof(TNode));
                root ->nama = inama;
                root ->gender = X;
                root ->age = umur;
                root ->pr = NULL;
                root ->ps = NULL;
                root ->nb = NULL;
                root ->fs = NULL;
                tree.root = root;
            }
            else
            {
                nbAddr pr;
                infotype anak;
                anak = (infotype) malloc(sizeof(infotype));
                ortu = (infotype) malloc(sizeof(infotype));
                    system("cls");
                    printf("Nambah Keturunan");
                    printf("\nMasukkan Orangtua: ");
                    scanf("%s", ortu);
                    pr =  searchNode(tree,ortu); // Masih error

                    printf("\nnama anak : ");
                    scanf ("%s", anak);

                    printf("\nMasukkan Kelamin");
                do
                {
                    printf ("\nJenis Kelamin (L/P)");
                    scanf("%c", &sex);
                } while (sex != 'L' && sex != 'l' && sex != 'P' && sex != 'p');
                int umur;
                printf ("\nUmur: ");
                scanf ("%d", &umur);
                if (sex == 'L' || sex == 'l')
                {
                    X = true;
                }
                if (sex == 'P' || sex == 'p')
                {
                    X = false;
                }
                nbInsert(anak,sex,umur,pr);
                printf("\n\tanak '%s',kelamin %c Umru %d dari :\n\t\t\t-%s",anak,sex,umur,pr->nama);
				system("pause");
            }
                break;
            case 2:
                break;
        } 
    } while (pilihan != 2);
    
    return 0;
}