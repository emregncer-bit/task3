//
// Created by Emre Gencer on 3.04.2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "can_queue.h"

void kuyrukOlustur(MesajKuyrugu *k, int kapasite) {
    k->kapasite = kapasite;
    k->count = 0;
    k-> front =0;
    k->rear = 0;


    k-> mesajlar = (CAN_Mesaj  *)malloc(kapasite * sizeof(CAN_Mesaj));

    if (k->mesajlar == NULL) {
        printf("Hata bellek ayrılamadı.\n");
        exit(1);
    }
    printf("[BİLGİ] %d kapasiteli dinamik mesaj kuyruğu bellekte oluşturuldu!\n", kapasite);

}

void enqueue(MesajKuyrugu *k, CAN_Mesaj yeni_mesaj) {
    if (k->count == k->kapasite) {
        printf("[Hata] CAN Bus hattı dolu! Kapasite (%d) aşıldı. Yeni mesaj eklenemez.\n", k->kapasite);
        return;
    }

    k->mesajlar[k->rear] = yeni_mesaj;
    k->rear = (k-> rear + 1) % k->kapasite; // en arkaya bi mesaj daha eklenir
    k->count++;


    printf("[BİLGİ] Mesaj kuyruğa eklendi. (Sıradaki mesaj sayısı %d)\n", k->count);
}

void dequeue(MesajKuyrugu *k) {
    if (k->count == 0) {
        printf("İşlenecek mesaj bulunmuyor.\n");
        return;
    }

    CAN_Mesaj islenecek_Mesaj = k->mesajlar[k->front];

    printf("[İŞLENDİ] %s (ID: %d) sensöründen gelen '%.2f' verisi ana bilgisayara iletildi.\n", islenecek_Mesaj.gonderen, islenecek_Mesaj.mesaj_id, islenecek_Mesaj.veri);

    k->front = (k->front+1) % k->kapasite; // front bi sonrakina kayar
    k->count--;

    printf("Kuyrukta kalan mesaj sayısıs: %d", k->count);
}

void kuyrukYazdir(MesajKuyrugu *k) {
    if (k->count == 0) {
        printf("[Bekleyen mesajlar toplam: 0]\n");
        return;
    }

    printf("Bekleyen mesajlar toplam: %d\n", k->count);

    for (int i = 0; i<k->count; i++) {
        int gercek_index = (k->front +i) % k->kapasite;
        printf("%d. %s (ID: %d) Veri: %.2f\n", i+1, k->mesajlar[gercek_index].gonderen, k->mesajlar[gercek_index].mesaj_id, k->mesajlar[gercek_index].veri);
    }
}

void bellekTemizleme(MesajKuyrugu *k) {
    printf("Dinamik bellek (RAM) temizleniyor...\n");
    free(k->mesajlar);
    k->mesajlar =NULL;
}
