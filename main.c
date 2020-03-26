#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define KIRMIZI         "\x1b[31m"
#define YESIL           "\xlb[32m"
#define SARI            "\x1b[33m"
#define MAVI            "\x1b[34m"
#define MACENTA         "\x1b[35m"
#define CYAN            "\x1b[36m"
#define BEYAZ           "\x1b[37m"
#define RENK_SIFIRLA    "\x1b[0m"

#define OYUN_ALANI_BOYUT 20
char oyun_alani[OYUN_ALANI_BOYUT][OYUN_ALANI_BOYUT];

int mevcut_oyuncu = 1;
int birinci_oyuncu_puan = 0;
int ikinci_oyuncu_puan = 0;
int bulunan_sos_sayisi = 0;
int onceki_sos_sayisi = 0;

void oyun_alani_sifirla();
void oyun_alani_ciz();
void hamle_yap(int mevcut_oyuncu_gosterge);
void ekrani_temizle();
void oyun_alani_denetle();
int oyun_sonu_denetle();
void puan_tablosu_ciz();
void oyun_sonu_ekrani_ciz();
void giris_ekrani_ciz();


int main()
{
    giris_ekrani_ciz();
    ekrani_temizle();
    oyun_alani_sifirla();

    while(!oyun_sonu_denetle()){
        puan_tablosu_ciz();
        oyun_alani_ciz();
        hamle_yap(mevcut_oyuncu);
        ekrani_temizle();
    }

    oyun_sonu_ekrani_ciz();


    printf("\n\n\n\n\n");

    return 0;
}

void oyun_alani_sifirla(){

    int oyun_alani_satir;
    int oyun_alani_sutun;

    for(oyun_alani_satir = 0; oyun_alani_satir < OYUN_ALANI_BOYUT; oyun_alani_satir++){
        for(oyun_alani_sutun = 0; oyun_alani_sutun < OYUN_ALANI_BOYUT; oyun_alani_sutun++){
            oyun_alani[oyun_alani_satir][oyun_alani_sutun] = '.';
        }
    }

}

void oyun_alani_ciz(){

    int oyun_alani_satir;
    int oyun_alani_sutun;

    printf("    ");

    for(oyun_alani_sutun = 0; oyun_alani_sutun < OYUN_ALANI_BOYUT; oyun_alani_sutun++){
        printf("%2d ",oyun_alani_sutun+1);
    }

    printf("\n");

    for(oyun_alani_satir = 0; oyun_alani_satir < OYUN_ALANI_BOYUT; oyun_alani_satir++){

        printf("%2d ",oyun_alani_satir+1);

        for(oyun_alani_sutun = 0; oyun_alani_sutun < OYUN_ALANI_BOYUT; oyun_alani_sutun++){
            printf("%3c",oyun_alani[oyun_alani_satir][oyun_alani_sutun]);
        }

        printf("\n");

    }
}

void hamle_yap(int mevcut_oyuncu_gosterge){
    int hamle_satir;
    int hamle_sutun;
    char hamle_harf;
    printf("\n\n");

        printf("%d. oyuncu lutfen hamle yapilacak koordinati(x y) giriniz: >> ",mevcut_oyuncu_gosterge);
        scanf(" %d %d",&hamle_satir,&hamle_sutun);

        if(hamle_satir > 0 && hamle_satir <= OYUN_ALANI_BOYUT && hamle_sutun>0 && hamle_sutun <= OYUN_ALANI_BOYUT){
            hamle_satir -= 1;
            hamle_sutun -= 1;
            printf("Hamle yapilacak harfi(s/o) giriniz: >> ");
            scanf(" %c",&hamle_harf);

            if(hamle_harf == 's' || hamle_harf == 'o'){
                if(oyun_alani[hamle_satir][hamle_sutun] == '.'){
                    oyun_alani[hamle_satir][hamle_sutun] = hamle_harf;
                    oyun_alani_denetle();
                }else{
                    printf(KIRMIZI "%d. oyuncu, isaretlediginiz alan zaten dolu!" RENK_SIFIRLA, mevcut_oyuncu_gosterge);

                    delay(1800);
                }
            }else{
                printf("Hatali bir harf girisi yaptiniz lutfen tekrar giris yapin!\n");
                delay(1800);
            }



        }else{
            printf("Hatali bir koordinat girdiniz lutfen tekrar giris yapin!\n");
            delay(1800);
        }






    //scanf();
    /*

    */
}

void ekrani_temizle(){
    system("@cls||clear");
}

void oyun_alani_denetle(){
    int oyun_alani_satir;
    int oyun_alani_sutun;

    bulunan_sos_sayisi = 0;
    for(oyun_alani_satir = 0; oyun_alani_satir < OYUN_ALANI_BOYUT; oyun_alani_satir++){
        for(oyun_alani_sutun = 0; oyun_alani_sutun < OYUN_ALANI_BOYUT; oyun_alani_sutun++){
            //Yatay Sos Tespiti
            if(oyun_alani[oyun_alani_satir][oyun_alani_sutun] == 'o' && oyun_alani[oyun_alani_satir][oyun_alani_sutun-1] == 's' && oyun_alani[oyun_alani_satir][oyun_alani_sutun+1] == 's'){
                if(oyun_alani_sutun != 0 && oyun_alani_sutun != OYUN_ALANI_BOYUT-1){
                    bulunan_sos_sayisi += 1;
                }
            }
            //Dikey Sos Tespiti
            if(oyun_alani[oyun_alani_satir][oyun_alani_sutun] == 'o' && oyun_alani[oyun_alani_satir-1][oyun_alani_sutun] == 's' && oyun_alani[oyun_alani_satir+1][oyun_alani_sutun] == 's'){
                if(oyun_alani_satir != 0 && oyun_alani_satir != OYUN_ALANI_BOYUT-1){
                    bulunan_sos_sayisi += 1;
                }
            }
            //Sag Carpraz Sos Tespiti
            if(oyun_alani[oyun_alani_satir][oyun_alani_sutun] == 'o' && oyun_alani[oyun_alani_satir+1][oyun_alani_sutun-1] == 's' && oyun_alani[oyun_alani_satir-1][oyun_alani_sutun+1] == 's'){
                if(oyun_alani_satir != 0 && oyun_alani_satir != OYUN_ALANI_BOYUT-1 && oyun_alani_sutun != 0 && oyun_alani_sutun != OYUN_ALANI_BOYUT-1){
                    bulunan_sos_sayisi += 1;
                }
            }
            //Sol Carpraz Sos Tespiti
            if(oyun_alani[oyun_alani_satir][oyun_alani_sutun] == 'o' && oyun_alani[oyun_alani_satir-1][oyun_alani_sutun-1] == 's' && oyun_alani[oyun_alani_satir+1][oyun_alani_sutun+1] == 's'){
                if(oyun_alani_satir != 0 && oyun_alani_satir != OYUN_ALANI_BOYUT-1 && oyun_alani_sutun != 0 && oyun_alani_sutun != OYUN_ALANI_BOYUT-1){
                    bulunan_sos_sayisi += 1;
                }
            }

        }
    }

    if(onceki_sos_sayisi == bulunan_sos_sayisi){
        if(mevcut_oyuncu == 1){
            mevcut_oyuncu = 2;
        }else if(mevcut_oyuncu == 2){
            mevcut_oyuncu = 1;
        }
    }else{
        if(mevcut_oyuncu == 1){
            birinci_oyuncu_puan += bulunan_sos_sayisi - onceki_sos_sayisi;
        }else if(mevcut_oyuncu == 2){
            ikinci_oyuncu_puan += bulunan_sos_sayisi - onceki_sos_sayisi;
        }
    }

    onceki_sos_sayisi = bulunan_sos_sayisi;

}

void puan_tablosu_ciz(){
    printf("1. oyuncunun puani: %d \n2. oyuncunun puani: %d \n\n\n",birinci_oyuncu_puan,ikinci_oyuncu_puan);
}

int oyun_sonu_denetle(){
    int oyun_alani_satir;
    int oyun_alani_sutun;
    int kalan_bosluk = 0;

    for(oyun_alani_satir = 0; oyun_alani_satir < OYUN_ALANI_BOYUT; oyun_alani_satir++){
        for(oyun_alani_sutun = 0; oyun_alani_sutun < OYUN_ALANI_BOYUT; oyun_alani_sutun++){
            if(oyun_alani[oyun_alani_satir][oyun_alani_sutun] == '.'){
                kalan_bosluk += 1;
            }
        }
    }


    if(kalan_bosluk == 0){
        return 1;
    }else{
        return 0;
    }
}

void oyun_sonu_ekrani_ciz(){
     printf("1. oyuncunun puani: %d \n2. oyuncunun puani: %d\n\n\n",birinci_oyuncu_puan,ikinci_oyuncu_puan);

     if(birinci_oyuncu_puan > ikinci_oyuncu_puan){
        printf("Birinci oyuncu kazandi!");
     }else if(ikinci_oyuncu_puan > birinci_oyuncu_puan){
        printf("Ikinci oyuncu kazandi!");
     }else{
        printf("Berabere!");
     }

     char tekrar_oyna;

    do{
     printf("Tekrar oynamak ister misiniz?(e/h): ");
     scanf(" %c",&tekrar_oyna);

     if(tekrar_oyna == 'e'){
        ekrani_temizle();
        main();
     }else if(tekrar_oyna == 'h'){
        exit(1);
     }else{
        printf("Hatali giris yaptiniz");
     }
    }while(1);

}

void giris_ekrani_ciz(){
    char baslangic_kontrol;

    while(1){
        printf("===============================\n");
        printf(" SSSSSSSSS OOOOOOOOO SSSSSSSSS\n" );
        printf(" S         O       O S        \n" );
        printf(" S         O       O S        \n" );
        printf(" SSSSSSSSS O       O SSSSSSSSS\n" );
        printf("         S O       O         S\n" );
        printf("         S O       O         S\n" );
        printf(" SSSSSSSSS OOOOOOOOO SSSSSSSSS\n" );
        printf("===============================\n");
        printf("       Burak Can TEMIZEL\n");
        printf("===============================\n");
        printf("Kurallar:\n");
        printf("1-)\n");
        printf("2-)\n");
        printf("3-)\n");
        printf("4-)\n");
        printf("5-)\n");
        printf("===============================\n");
        printf("\n\nOyuna baslamak icin 'e' cikmak icin 'h' giriniz: >> ");

        scanf(" %c",&baslangic_kontrol);

        if(baslangic_kontrol == 'e'){
            /*while(1){
                printf("Oyun alaninin boyutunu giriniz(minimum:3 ve maksimum:20): >>");
                scanf("%d",&OYUN_ALANI_BOYUT);
                if(OYUN_ALANI_BOYUT >=3 && OYUN_ALANI_BOYUT <=20){
                        break;
                }
            }
            */
            break;
        }else if(baslangic_kontrol == 'h'){
            exit(0);
        }else{
            printf(MAVI "%c .ci Hatali giris yaptiniz!" RENK_SIFIRLA,baslangic_kontrol);
            delay(1000);
            ekrani_temizle();
        }
    }

}


//Baþlýk Çizimi
/*

    //printf(YESIL " SSSSSSSSS OOOOOOOOO SSSSSSSSS\n" RENK_SIFIRLA);
    //printf(MAVI " S         O       O S        \n" RENK_SIFIRLA);
    //printf(KIRMIZI " S         O       O S        \n" RENK_SIFIRLA);
    //printf(YESIL " SSSSSSSSS O       O SSSSSSSSS\n" RENK_SIFIRLA);
    //printf(MAVI "         S O       O         S\n" RENK_SIFIRLA);
    //printf(KIRMIZI "         S O       O         S\n" RENK_SIFIRLA);
    //printf(YESIL " SSSSSSSSS OOOOOOOOO SSSSSSSSS\n" RENK_SIFIRLA);
    //printf(MAVI "===============================\n" RENK_SIFIRLA);
*/

































