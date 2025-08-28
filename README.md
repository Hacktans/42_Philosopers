# Philosophers (Dining Philosophers Problem)

Bu proje, klasik **Dining Philosophers Problem** (Yemek Yiyen Filozoflar Problemi) simülasyonunu C programlama dili ile pthread kütüphanesi kullanarak implementasyonu içermektedir. Bu problem, eş zamanlı programlama, thread synchronization ve deadlock prevention konularını öğretmek için kullanılan klasik bir bilgisayar bilimi problemidir.

## 📋 Proje Açıklaması

Yemek Yiyen Filozoflar Problemi şu şekilde tanımlanır:
- N sayıda filozof yuvarlak bir masada oturur
- Her filozofun önünde bir tabak spagetti vardır
- Filozoflar arasında N adet çatal bulunur (her iki filozof arasında bir çatal)
- Filozoflar sadece düşünür, yer ve uyur
- Yemek yemek için her filozof iki çatala ihtiyaç duyar (sol ve sağ)
- Bir filozof ölürse (belirtilen süre içinde yemek yemezse) simülasyon sona erer

## 🚀 Derleme ve Çalıştırma

### Derleme
```bash
make
```

### Temizleme
```bash
make clean    # Object dosyalarını sil
make fclean   # Tüm derlenmiş dosyaları sil
make re       # Temizle ve yeniden derle
```

### Çalıştırma
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

#### Parametreler:
- `number_of_philosophers`: Filozof sayısı (1-200 arası)
- `time_to_die`: Ölüm süresi (milisaniye)
- `time_to_eat`: Yemek yeme süresi (milisaniye)
- `time_to_sleep`: Uyku süresi (milisaniye)
- `number_of_times_each_philosopher_must_eat`: (Opsiyonel) Her filozofun minimum yemek sayısı

## 💡 Kullanım Örnekleri

```bash
# 5 filozof, 800ms'de ölüm, 200ms yeme, 200ms uyku
./philo 5 800 200 200

# 4 filozof, her biri 3 kez yemek yemeli
./philo 4 410 200 200 3

# Tek filozof durumu (özel durum)
./philo 1 800 200 200
```

## 🏗️ Proje Yapısı

```
philo/
├── main.c          # Ana program ve thread yönetimi
├── actions.c       # Filozof davranışları (düşünme, yeme, uyuma)
├── parse.c         # Komut satırı argümanları ayrıştırma
├── utils.c         # Yardımcı fonksiyonlar ve mutex yönetimi
├── utils2.c        # Ek yardımcı fonksiyonlar
├── philo.h         # Header dosyası ve struct tanımları
├── makefile        # Derleme kuralları
└── README.md       # Proje dokümantasyonu
```

## 🔧 Temel Fonksiyonlar

### Ana Fonksiyonlar:
- `routine()`: Her filozof için ana thread rutini
- `dead_monitor()`: Filozofların ölüm durumunu kontrol eden thread
- `is_eating()`: Yeme davranışı ve çatal yönetimi
- `is_sleeping()`: Uyku davranışı
- `is_thinking()`: Düşünme davranışı

### Yardımcı Fonksiyonlar:
- `get_time()`: Mevcut zamanı milisaniye olarak döndürür
- `print_action()`: Thread-safe çıktı yazdırma
- `my_usleep()`: Kesintiye uğrayabilen uyku fonksiyonu
- `is_dead()`: Filozof ölüm durumu kontrolü

## 🔄 Program Akışı

1. **Başlatma**: Komut satırı argümanları ayrıştırılır
2. **Mutex İnisiyalizasyonu**: Çatallar ve kontrol mutex'leri oluşturulur
3. **Thread Oluşturma**: Her filozof için bir thread oluşturulur
4. **Simülasyon**: Filozoflar yeme-uyuma-düşünme döngüsüne girer
5. **Monitoring**: Ayrı bir thread filozofların ölüm durumunu izler
6. **Sonlandırma**: Ölüm veya yeme hedefine ulaşılınca program sonlanır

## ⚙️ Thread Synchronization

Proje aşağıdaki mutex'leri kullanır:
- **Fork Mutex'leri**: Her çatal için ayrı mutex
- **Print Mutex**: Çıktı yazdırma için thread-safety
- **Meal Mutex**: Yemek sayısı ve son yemek zamanı için
- **Death Mutex**: Ölüm durumu kontrolü için

## 🔍 Deadlock Prevention

Deadlock'u önlemek için:
- Çift numaralı filozoflar önce sol, sonra sağ çatalı alır
- Tek numaralı filozoflar önce sağ, sonra sol çatalı alır
- Tek numaralı filozoflara küçük bir gecikme eklenir

## ⚠️ Özel Durumlar

- **Tek Filozof**: Özel olarak ele alınır (sadece bir çatal olduğu için yemek yiyemez)
- **Ölüm Kontrolü**: Her eylemden önce ölüm durumu kontrol edilir
- **Meal Count**: Opsiyonel parametre ile minimum yemek sayısı kontrolü

## 📊 Çıktı Formatı

```
[timestamp] [philosopher_id] [action]
```

Örnek:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

## 🐛 Hata Durumları

- Geçersiz parametre sayısı
- Negatif veya sıfır değerler
- 200'den fazla filozof
- Sayısal olmayan parametreler
- Bellek ayırma hataları

## 📝 Notlar

- Bu implementasyon 42 School standardlarına uygun olarak yazılmıştır
- Race condition'ları önlemek için dikkatli mutex kullanımı yapılmıştır
- Memory leak'ler önlenmiş ve tüm kaynaklar temizlenmiştir
- Program norminette uyumludur

## 👨‍💻 Geliştirici

**hadalici** - 42 İstanbul öğrencisi

---

Bu proje, concurrent programming, thread synchronization ve resource sharing konularını pratik bir şekilde öğretmeyi amaçlamaktadır.
