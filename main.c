#include <stdio.h>
#include <stdlib.h>
#include "can_queue.h"

int main(void) {
    MesajKuyrugu kuyruk;
    int secim = 0, mesaj_id = 0, kapasite = 0;
    float veri = 0.0f;
    char gonderen[30];

    printf("[SİSTEM] CAN Bus kapasitesini belirleyin.\n");
    if (scanf("%d", &kapasite) != 1) {
        printf("Hata\n");
        return 1;
    }

    kuyrukOlustur(&kuyruk, kapasite);


    CAN_Mesaj gecici_mesaj;

    while (1) {
        printf("\n--- CAN BUS İLETİŞİM SİSTEMİ ---\n"); //
        printf("1. Sensörden Mesaj Üret (Kuyruğa Ekle)\n"); //
        printf("2. Bekleyen İlk Mesajı İşle (Kuyruktan Çıkar)\n"); //
        printf("3. Bekleyen Mesajları Göster\n"); //
        printf("4. Çıkış\n"); //
        printf("Seçiminiz: ");
        if (scanf("%d", &secim) != 1) {
            printf("Hata\n");
            while (getchar() != '\n') {
                secim = 0;
                continue;
            }
        }
        printf("\n");

        switch (secim) {
            case 1:
                printf("Sensör Adı: \n");
                scanf("%s", gecici_mesaj.gonderen);
                printf("Mesaj ID: \n");
                scanf("%d", &gecici_mesaj.mesaj_id);
                printf("Veri: \n");
                scanf("%f", &gecici_mesaj.veri);

                enqueue(&kuyruk, gecici_mesaj);
                break;

            case 2:
                dequeue(&kuyruk);
                break;

            case 3:
                kuyrukYazdir(&kuyruk);
                break;

            case 4:
                bellekTemizle(&kuyruk);
                printf("Sistem güvenli bir şekilde kapatıldı\n");
                return 0;
            default:
                printf("HATA Geçersiz seçim. Lütfen 1-4 arası bir değer girin.\n");
                break;
        }


    }

}