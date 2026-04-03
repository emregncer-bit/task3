# CAN Bus Mesaj Kuyruğu Simülasyonu (Hafta 3)

## Açıklama
[cite_start]Bu proje, bir elektrikli aracın içindeki sensörlerden (hız, batarya sıcaklığı vb.) ana bilgisayara (ECU) gelen verilerin yönetimini simüle eden bir C uygulamasıdır[cite: 4, 5]. [cite_start]Birden fazla sensörün aynı anda veri göndermesi durumunda veri kaybını önlemek amacıyla **Kuyruk (Queue - FIFO)** [cite: 8] veri yapısı kullanılmıştır.

[cite_start]Önceki haftalardan farklı olarak, sistemin bellek ihtiyacı statik dizilerle değil; program başlatıldığında kullanıcının belirlediği kapasite doğrultusunda **Dinamik Bellek Yönetimi (malloc / free)** kullanılarak çalışma zamanında (runtime) ayrılmaktadır[cite: 10, 26, 27].

## Özellikler
* [cite_start]**Dinamik Bellek Tahsisi:** Kullanıcının girdiği kapasiteye göre `malloc` kullanılarak RAM'de sadece gerektiği kadar alan açılır[cite: 50, 82].
* **Dairesel Kuyruk (Circular Queue) Mantığı:** Bellek israfını önlemek için, mesajlar kuyruktan çıktıkça boşalan alanlar yeni mesajlar için tekrar kullanılabilir hale getirilir (`% kapasite` modülü ile).
* [cite_start]**Pointer ve Struct Mimarisi:** Sensör verileri `CAN_Mesaj` yapısında, kuyruk metrikleri ise `MesajKuyrugu` yapısında kapsüllenmiş ve fonksiyonlara pointer (adres) referanslarıyla aktarılmıştır[cite: 28, 29].
* **Güvenlik ve Sınır Kontrolleri (Edge Cases):**
  * [cite_start]**Kuyruk Taşması (Overflow):** Kapasite dolduğunda yeni mesaj eklenmesi engellenir[cite: 66].
  * [cite_start]**Boş Kuyruk (Underflow):** Kuyrukta mesaj yokken işlem yapılmaya çalışıldığında sistem uyarır[cite: 67].
  * [cite_start]**Bellek Sızıntısı (Memory Leak) Koruması:** Program sonlanırken `free()` fonksiyonu ile ayrılan dinamik bellek işletim sistemine güvenli bir şekilde iade edilir[cite: 63, 68].

## [cite_start]Dosya Yapısı [cite: 24]
* [cite_start]`main.c`: Kullanıcıdan kapasite bilgisini alır, belleği ayırır ve ana menü (switch-case) döngüsünü yönetir[cite: 25].
* [cite_start]`can_queue.c`: Dinamik bellek tahsisi (`kuyrukOlustur`), kuyruğa ekleme (`enqueue`), kuyruktan çıkarma (`dequeue`), yazdırma ve bellek temizleme (`bellekTemizle`) fonksiyonlarının ana gövdelerini barındırır[cite: 25].
* [cite_start]`can_queue.h`: `CAN_Mesaj` ve `MesajKuyrugu` struct tanımlamalarını, include korumalarını (`#ifndef`) ve fonksiyon prototiplerini içerir[cite: 25].
* [cite_start]`Rapor.pdf`: Neden sabit diziler yerine dinamik bellek (malloc) kullanıldığını ve CAN Bus sistemlerinde neden Stack (LIFO) yerine Queue (FIFO) yapısının tercih edildiğini detaylandıran teknik dokümantasyon[cite: 75, 78].

## Kurulum ve Çalıştırma

Projeyi derlemek ve çalıştırmak için sisteminizde `gcc` derleyicisi bulunmalıdır.

**1. Projeyi Derleme:**
Terminali açın, proje dizinine gidin ve aşağıdaki komutu çalıştırın:
```bash
gcc -Wall -Wextra -o task3 main.c can_queue.c
