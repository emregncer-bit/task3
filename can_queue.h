//
// Created by Emre Gencer on 3.04.2026.
//

#ifndef TASK3_CAN_QUEUE_H
#define TASK3_CAN_QUEUE_H

typedef struct {
    int mesaj_id;
    float veri;
    char gonderen[30];
} CAN_Mesaj;

typedef struct {
    CAN_Mesaj *mesajlar;
    int kapasite;
    int front;
    int rear;
    int count;
} MesajKuyrugu;

void kuyrukOlustur(MesajKuyrugu *k, int kapasite);
void enqueue(MesajKuyrugu *k, CAN_Mesaj yeni_mesaj);
void dequeue(MesajKuyrugu *k);
void kuyrukYazdir(MesajKuyrugu *k);
void bellekTemizle(MesajKuyrugu *k);

#endif //TASK3_CAN_QUEUE_H