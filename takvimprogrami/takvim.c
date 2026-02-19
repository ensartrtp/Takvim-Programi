#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>

// Artýk yýl olup olmadýðýný kontrol eden fonksiyon
int artikYilMi(int yil) {
    return (yil % 4 == 0 && (yil % 100 != 0 || yil % 400 == 0));
}

// Bir yýlýn, belirli bir ayýndaki ilk günün hangi gün olduðunu hesaplayan fonksiyon
int ilkgunuhesaplama(int yil, int ay) {
    if (ay <= 2) {  // Ocak ve Þubat için yýlý bir önceki yýla ayarla
        ay += 12;
        yil--;
    }

    int ayinIlkGunu = 1;                // Her zaman ayýn ilk günü
    int yilinSonIkýBasamagi = yil % 100;        // Yýlýn son iki basamaðý
    int c = yil / 100;        // Yýlýn ilk iki basamaðý

    int h = (ayinIlkGunu + (13 * (ay + 1)) / 5 + yilinSonIkýBasamagi + (yilinSonIkýBasamagi / 4) + (c / 4) - 2 * c) % 7;

    return (h + 5) % 7;  // Pazartesi = 0 olacak þekilde düzenlendi
}




// Ayýn gün sayýsýný döndüren fonksiyon
int aydakiGunler(int ay, int yil) {
    if (ay == 2) return artikYilMi(yil) ? 29 : 28;  // Þubat
    if (ay == 4 || ay == 6 || ay == 9 || ay == 11) return 30;  // Nisan, Haziran, Eylül, Kasým
    return 31;  // Diðer aylar
}

void yazdirmafonks(int yil) {
    const char* aylar[] = { "OCAK", "SUBAT", "MART", "NISAN", "MAYIS", "HAZIRAN",
                            "TEMMUZ", "AGUSTOS", "EYLUL", "EKIM", "KASIM", "ARALIK" };

    printf("\nYIL: %d\n", yil);

    for (int ay = 1; ay <= 12; ay++) {
        printf("\n | - - - - - - - - - - - - - - - - - - - - - -| \n");
        printf("\n%15s \n", aylar[ay - 1]);
        printf("Pzt Sal Car Per Cum Cmt Paz\n");

        int ilkgun = ilkgunuhesaplama(yil, ay);  // Ayýn ilk gününü hesapla
        int gunler = aydakiGunler(ay, yil);      // Ayýn toplam gün sayýsýný al

        // Ýlk gün için boþluk býrak
        for (int i = 0; i < ilkgun; i++) {
            printf("    ");
        }

        // Ayýn günlerini yazdýr
        for (int gun = 1; gun <= gunler; gun++) {
            // Cumartesi ve Pazar için kýrmýzý renk
            if ((ilkgun + gun) % 7 == 6 || (ilkgun + gun) % 7 == 0) {
                printf("\033[31m%3d \033[0m", gun);  // Kýrmýzý renk
            }
            else {
                printf("%3d ", gun);  // Normal renk
            }

            // Pazar gününden sonra yeni satýra geç
            if ((ilkgun + gun) % 7 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }
}


// Çýkýþ onay ekranýný yazdýran fonksiyon
void cikisekraniniyazdir() {
    system("cls");
    printf("\n\n");
    printf("Cikmak istediginizden emin misiniz? (E/H)\n");
}

// Ana menüyü yazdýran fonksiyon
void anamenuyuyazdir() {
    system("CLS");
    printf("\n\n\n\n\n%20c", 201);
    for (int i = 0; i < 80; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    for (int i = 0; i < 7; i++) {
        printf("%20c %80c\n", 186, 186);
    }
    printf("%20c                            TAKVIM PROGRAMI %37c \n", 186, 186);
    printf("%20c                Devam etmek icin 'D' veya 'd' tusuna basiniz%21c \n", 186, 186);
    printf("%20c                Cikis icin ESC tusuna basiniz        %28c\n", 186, 186);
    for (int i = 0; i < 7; i++) {
        printf("%20c %80c\n", 186, 186);
    }
    printf("%20c", 200);
    for (int i = 0; i < 80; i++) {
        printf("%c", 205);
    }
    printf("%c", 188);
}

// Yýl giriþi yapan fonksiyon
int gecerlibiryilal() {
    int takvimyili;
    while (1) {
        system("CLS"); // Ekraný temizle
        printf("\n\n\n\n                            TAKVIM PROGRAMI\n");
        printf("                       - - - - - - - - - - - - - - - - - - - - - - ");
        printf("\n\n\n\n                    Takvim yilini giriniz (1910-2090 arasi):\n\n\n");
        scanf_s("%d", &takvimyili); // Kullanýcýdan yýl al

        if (takvimyili >= 1910 && takvimyili <= 2090) {
            return takvimyili; // Geçerli yýl döndürülür
        }
        else {
            // Hatalý tarih mesajýný göster
            printf("\nHatali yil! Lutfen 1910 ile 2090 arasinda bir yil giriniz.\n");
            printf("\nDevam etmek icin bir tusa basiniz...");
            _getch(); // Kullanýcýdan bir tuþa basmasýný bekle
        }
    }
}


int main() {
    char ch;
    int yil;

    while (1) {
        anamenuyuyazdir(); // Ana menüyü göster

        ch = _getch(); // Kullanýcýdan bir tuþ bekle

        if (ch == 27) { // ESC tuþuna basýldýysa
            cikisekraniniyazdir(); // Çýkýþ ekranýný göster
            ch = _getch(); // Onay için tuþ bekle

            if (ch == 'e' || ch == 'E') {
                break; // Program sonlanýr
            }
        }
        else if (ch == 'd' || ch == 'D') { // Devam etmek için
            yil = gecerlibiryilal(); // Kullanýcýdan yýl al
            system("CLS");
            yazdirmafonks(yil); // Yýlýn takvimini yazdýr
            printf("\nAna menuye donmek icin bir tusa basiniz...");
            _getch(); // Devam etmeden önce bekle
        }
    }

    return 0;
}