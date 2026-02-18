#include <stdio.h>
#include <math.h> // fabs() için

// ====== ECU ve Araç Değişkenleri ======
float currentSpeed = 0.0;       // Mevcut hız (km/h)
float targetSpeed = 100.0;      // Hedef hız (km/h)
float distanceToCarAhead = 100.0; // Öndeki araca mesafe (m)
float leadCarSpeed = 90.0;      // Öndeki aracın hızı (km/h)

// ====== Parametreler ======
float timeStep = 1.0;           // 1 saniyelik adımlar
float maxAccel = 5.0;           // Maksimum hızlanma km/h/s
float maxDecel = 10.0;          // Maksimum yavaşlama km/h/s
float safeDistance = 20.0;      // Güvenli mesafe (m)

// ====== Fonksiyon Prototipleri ======
void readSensors();
void controlThrottle();
void updateSpeed();

int main() {
    printf("Geliştirilmiş Adaptive Cruise Control Simülasyonu Başladı 🚗\n\n");

    for(int t = 0; t < 20; t++) { // 20 saniyelik simülasyon
        readSensors();
        controlThrottle();
        updateSpeed();
        printf("Zaman: %2d s | Hız: %6.2f km/h | Mesafe: %6.2f m | Öndeki Araç Hızı: %6.2f km/h\n",
               t, currentSpeed, distanceToCarAhead, leadCarSpeed);
    }

    printf("\nSimülasyon Bitti ✅\n");
    return 0;
}

// ====== Sensör Verilerini Simüle Et ======
void readSensors() {
    // Öndeki araç sabit hızla ilerliyor, mesafe değişiyor
    distanceToCarAhead -= leadCarSpeed * (timeStep / 3.6); // km/h -> m/s
}

// ====== ECU Hız Kontrolü ======
void controlThrottle() {
    float speedDifference = targetSpeed - currentSpeed;

    // Mesafe kontrolü
    if(distanceToCarAhead < safeDistance) {
        // Güvenli mesafe altına düşerse öndeki araç hızına yaklaş
        float desiredSpeed = fmin(currentSpeed, leadCarSpeed);
        float decel = fmin(maxDecel, currentSpeed - desiredSpeed);
        currentSpeed -= decel * (timeStep);
        if(currentSpeed < 0) currentSpeed = 0;
    } else {
        // Hedef hıza doğru kademeli hızlan
        float accel = fmin(maxAccel, speedDifference);
        currentSpeed += accel * (timeStep);
        if(currentSpeed > targetSpeed) currentSpeed = targetSpeed;
    }
}

// ====== Araç Hızını Güncelle ======
void updateSpeed() {
    // Bu basit simülasyonda hız zaten controlThrottle ile güncelleniyor
}
