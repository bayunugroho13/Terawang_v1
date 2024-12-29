#include <IntervalTimer.h> // library timer teensy 4.1

// Deklarasi objek IntervalTimer
IntervalTimer myTimer;

// Definisikan pin sensor
const int sensor1Pin = 1;
const int sensor2Pin = 4;
const int sensor3Pin = 8;
const int sensor4Pin = 12;
const int sensor5Pin = 22;
const int sensor6Pin = 18;
const int sensor7Pin = 14;
const int sensor8Pin = 40;

// Variabel untuk menghitung mikrodetik
volatile uint32_t microsecondsCounter = 0;

// Variabel untuk menyimpan waktu rising edge pertama
volatile unsigned long timeSensor1 = 0;
volatile unsigned long timeSensor2 = 0;
volatile unsigned long timeSensor3 = 0;
volatile unsigned long timeSensor4 = 0;
volatile unsigned long timeSensor5 = 0;
volatile unsigned long timeSensor6 = 0;
volatile unsigned long timeSensor7 = 0;
volatile unsigned long timeSensor8 = 0;

// Variabel untuk menyimpan flag apakah rising edge telah terdeteksi
volatile bool sensor1Detected = false;
volatile bool sensor2Detected = false;
volatile bool sensor3Detected = false;
volatile bool sensor4Detected = false;
volatile bool sensor5Detected = false;
volatile bool sensor6Detected = false;
volatile bool sensor7Detected = false;
volatile bool sensor8Detected = false;

// Variabel pilihan program
int state_program = 0;

// Fungsi ISR untuk timer
void timerISR() {
  microsecondsCounter++;
  //microsecondsCounter=microsecondsCounter+5;
}

// ISR untuk sensor 1
void handleSensor1() {
  if (!sensor1Detected) {
    timeSensor1 = microsecondsCounter;
    sensor1Detected = true;
  }
}

// ISR untuk sensor 2
void handleSensor2() {
  if (!sensor2Detected) {
    timeSensor2 = microsecondsCounter;
    sensor2Detected = true;
  }
}

// ISR untuk sensor 3
void handleSensor3() {
  if (!sensor3Detected) {
    timeSensor3 = microsecondsCounter;
    sensor3Detected = true;
  }
}

// ISR untuk sensor 4
void handleSensor4() {
  if (!sensor4Detected) {
    timeSensor4 = microsecondsCounter;
    sensor4Detected = true;
  }
}

// ISR untuk sensor 5
void handleSensor5() {
  if (!sensor5Detected) {
    timeSensor5 = microsecondsCounter;
    sensor5Detected = true;
  }
}

// ISR untuk sensor 6
void handleSensor6() {
  if (!sensor6Detected) {
    timeSensor6 = microsecondsCounter;
    sensor6Detected = true;
  }
}

// ISR untuk sensor 7
void handleSensor7() {
  if (!sensor7Detected) {
    timeSensor7 = microsecondsCounter;
    sensor7Detected = true;
  }
}

// ISR untuk sensor 8
void handleSensor8() {
  if (!sensor8Detected) {
    timeSensor8 = microsecondsCounter;
    sensor8Detected = true;
  }
}

void setup() {
  // Mulai komunikasi serial dengan komputer dan Bluetooth
  Serial.begin(9600); // Serial utk serial monitor
  Serial8.begin(9600); // Serial8 utk bluetooth (TX8 pin 35, RX8 pin 34)

  // Inisialisasi timer untuk memanggil fungsi timerISR setiap 1 mikrodetik
  myTimer.begin(timerISR, 1); // 1 mikrodetik

  // Set pin sensor sebagai input
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);
  pinMode(sensor4Pin, INPUT);
  pinMode(sensor5Pin, INPUT);
  pinMode(sensor6Pin, INPUT);
  pinMode(sensor7Pin, INPUT);
  pinMode(sensor8Pin, INPUT);

  // Atur interrupt untuk masing-masing sensor
  attachInterrupt(digitalPinToInterrupt(sensor1Pin), handleSensor1, RISING);
  attachInterrupt(digitalPinToInterrupt(sensor2Pin), handleSensor2, RISING);
  attachInterrupt(digitalPinToInterrupt(sensor3Pin), handleSensor3, RISING);
  attachInterrupt(digitalPinToInterrupt(sensor4Pin), handleSensor4, RISING);
  attachInterrupt(digitalPinToInterrupt(sensor5Pin), handleSensor5, RISING);
  attachInterrupt(digitalPinToInterrupt(sensor6Pin), handleSensor6, RISING);
  attachInterrupt(digitalPinToInterrupt(sensor7Pin), handleSensor7, RISING);
  attachInterrupt(digitalPinToInterrupt(sensor8Pin), handleSensor8, RISING);

  Serial.println("Alat Siap");
}

void loop() {

  if (state_program == 0) {
    while (state_program == 0) { // Program 0 akan terus berjalan selama state_program = 0
    Idle();   
      // Periksa kembali input serial untuk kemungkinan perubahan state_program
      if (Serial8.available()) {
        String dataMasuk = Serial8.readStringUntil('\n');
        Serial.println("Sensor "+ dataMasuk +" aktif");
        if (dataMasuk == "1") {
          state_program = 1;  // Beralih ke pengukuranSensor1
        } else if (dataMasuk == "2") {
          state_program = 2;  // Beralih ke pengukuranSensor2
        } else if (dataMasuk == "3") {
          state_program = 3;  // Beralih ke pengukuranSensor3
        } else if (dataMasuk == "4") {
          state_program = 4;  // Beralih ke pengukuranSensor4
        } else if (dataMasuk == "5") {
          state_program = 5;  // Beralih ke pengukuranSensor5
        } else if (dataMasuk == "6") {
          state_program = 6;  // Beralih ke pengukuranSensor6
        } else if (dataMasuk == "7") {
          state_program = 7;  // Beralih ke pengukuranSensor7
        } else if (dataMasuk == "8") {
          state_program = 8;  // Beralih ke pengukuranSensor8
        }
      }
    }
  } else if (state_program == 1) {
    while (state_program == 1) { // Program Sensor 1 akan terus berjalan selama state_program = 1
    pengukuranSensor1();   
      // Periksa kembali input serial untuk kemungkinan perubahan state_program
      if (Serial8.available()) {
        String dataMasuk = Serial8.readStringUntil('\n');
        Serial.println("Sensor "+ dataMasuk +" aktif");
        if (dataMasuk == "0") {
          state_program = 0;  // Beralih ke Idle
        } else if (dataMasuk == "2") {
          state_program = 2;  // Beralih ke pengukuranSensor2
        } else if (dataMasuk == "3") {
          state_program = 3;  // Beralih ke pengukuranSensor3
        } else if (dataMasuk == "4") {
          state_program = 4;  // Beralih ke pengukuranSensor4
        } else if (dataMasuk == "5") {
          state_program = 5;  // Beralih ke pengukuranSensor5
        } else if (dataMasuk == "6") {
          state_program = 6;  // Beralih ke pengukuranSensor6
        } else if (dataMasuk == "7") {
          state_program = 7;  // Beralih ke pengukuranSensor7
        } else if (dataMasuk == "8") {
          state_program = 8;  // Beralih ke pengukuranSensor8
        }
      }
    }
  } else if (state_program == 2) {
    while (state_program == 2) { // Program Sensor 1 akan terus berjalan selama state_program = 2
    pengukuranSensor2(); 
      // Periksa kembali input serial untuk kemungkinan perubahan state_program
      if (Serial8.available()) {
        String dataMasuk = Serial8.readStringUntil('\n');
        Serial.println("Sensor "+ dataMasuk +" aktif");
        if (dataMasuk == "0") {
          state_program = 0;   //Beralih ke Idle
        } else if (dataMasuk == "1") {
          state_program = 1;   //Beralih ke pengukuranSensor1
        } else if (dataMasuk == "3") {
          state_program = 3;  // Beralih ke pengukuranSensor3
        } else if (dataMasuk == "4") {
          state_program = 4;  // Beralih ke pengukuranSensor4
        } else if (dataMasuk == "5") {
          state_program = 5;  // Beralih ke pengukuranSensor5
        } else if (dataMasuk == "6") {
          state_program = 6;  // Beralih ke pengukuranSensor6
        } else if (dataMasuk == "7") {
          state_program = 7;  // Beralih ke pengukuranSensor7
        } else if (dataMasuk == "8") {
          state_program = 8;  // Beralih ke pengukuranSensor8
        }
      }
    }
  } else if (state_program == 3) {
    while (state_program == 3) { // Program Sensor 3 akan terus berjalan selama state_program = 3
    pengukuranSensor3(); 
      // Periksa kembali input serial untuk kemungkinan perubahan state_program
      if (Serial8.available()) {
        String dataMasuk = Serial8.readStringUntil('\n');
        Serial.println("Sensor "+ dataMasuk +" aktif");
        if (dataMasuk == "0") {
          state_program = 0;   //Beralih ke Idle
        } else if (dataMasuk == "1") {
          state_program = 1;   //Beralih ke pengukuranSensor1
        } else if (dataMasuk == "2") {
          state_program = 2;  // Beralih ke pengukuranSensor2
        } else if (dataMasuk == "4") {
          state_program = 4;  // Beralih ke pengukuranSensor4
        } else if (dataMasuk == "5") {
          state_program = 5;  // Beralih ke pengukuranSensor5
        } else if (dataMasuk == "6") {
          state_program = 6;  // Beralih ke pengukuranSensor6
        } else if (dataMasuk == "7") {
          state_program = 7;  // Beralih ke pengukuranSensor7
        } else if (dataMasuk == "8") {
          state_program = 8;  // Beralih ke pengukuranSensor8
        }
      }
    }
  } else if (state_program == 4) {
    while (state_program == 4) { // Program Sensor 4 akan terus berjalan selama state_program = 4
    pengukuranSensor4(); 
      // Periksa kembali input serial untuk kemungkinan perubahan state_program
      if (Serial8.available()) {
        String dataMasuk = Serial8.readStringUntil('\n');
        Serial.println("Sensor "+ dataMasuk +" aktif");
        if (dataMasuk == "0") {
          state_program = 0;   //Beralih ke Idle
        } else if (dataMasuk == "1") {
          state_program = 1;   //Beralih ke pengukuranSensor1
        } else if (dataMasuk == "2") {
          state_program = 2;  // Beralih ke pengukuranSensor2
        } else if (dataMasuk == "3") {
          state_program = 3;  // Beralih ke pengukuranSensor3
        } else if (dataMasuk == "5") {
          state_program = 5;  // Beralih ke pengukuranSensor5
        } else if (dataMasuk == "6") {
          state_program = 6;  // Beralih ke pengukuranSensor6
        } else if (dataMasuk == "7") {
          state_program = 7;  // Beralih ke pengukuranSensor7
        } else if (dataMasuk == "8") {
          state_program = 8;  // Beralih ke pengukuranSensor8
        }
      }
    }
  } else if (state_program == 5) {
    while (state_program == 5) { // Program Sensor 5 akan terus berjalan selama state_program = 5
    pengukuranSensor5(); 
      // Periksa kembali input serial untuk kemungkinan perubahan state_program
      if (Serial8.available()) {
        String dataMasuk = Serial8.readStringUntil('\n');
        Serial.println("Sensor "+ dataMasuk +" aktif");
        if (dataMasuk == "0") {
          state_program = 0;   //Beralih ke Idle
        } else if (dataMasuk == "1") {
          state_program = 1;   //Beralih ke pengukuranSensor1
        } else if (dataMasuk == "2") {
          state_program = 2;  // Beralih ke pengukuranSensor2
        } else if (dataMasuk == "3") {
          state_program = 3;  // Beralih ke pengukuranSensor3
        } else if (dataMasuk == "4") {
          state_program = 4;  // Beralih ke pengukuranSensor4
        } else if (dataMasuk == "6") {
          state_program = 6;  // Beralih ke pengukuranSensor6
        } else if (dataMasuk == "7") {
          state_program = 7;  // Beralih ke pengukuranSensor7
        } else if (dataMasuk == "8") {
          state_program = 8;  // Beralih ke pengukuranSensor8
        }
      }
    }
  } else if (state_program == 6) {
    while (state_program == 6) { // Program Sensor 6 akan terus berjalan selama state_program = 6
    pengukuranSensor6(); 
      // Periksa kembali input serial untuk kemungkinan perubahan state_program
      if (Serial8.available()) {
        String dataMasuk = Serial8.readStringUntil('\n');
        Serial.println("Sensor "+ dataMasuk +" aktif");
        if (dataMasuk == "0") {
          state_program = 0;   //Beralih ke Idle
        } else if (dataMasuk == "1") {
          state_program = 1;   //Beralih ke pengukuranSensor1
        } else if (dataMasuk == "2") {
          state_program = 2;  // Beralih ke pengukuranSensor2
        } else if (dataMasuk == "3") {
          state_program = 3;  // Beralih ke pengukuranSensor3
        } else if (dataMasuk == "4") {
          state_program = 4;  // Beralih ke pengukuranSensor4
        } else if (dataMasuk == "5") {
          state_program = 5;  // Beralih ke pengukuranSensor5
        } else if (dataMasuk == "7") {
          state_program = 7;  // Beralih ke pengukuranSensor7
        } else if (dataMasuk == "8") {
          state_program = 8;  // Beralih ke pengukuranSensor8
        }
      }
    }
  } else if (state_program == 7) {
    while (state_program == 7) { // Program Sensor 7 akan terus berjalan selama state_program = 7
    pengukuranSensor7(); 
      // Periksa kembali input serial untuk kemungkinan perubahan state_program
      if (Serial8.available()) {
        String dataMasuk = Serial8.readStringUntil('\n');
        Serial.println("Sensor "+ dataMasuk +" aktif");
        if (dataMasuk == "0") {
          state_program = 0;   //Beralih ke Idle
        } else if (dataMasuk == "1") {
          state_program = 1;   //Beralih ke pengukuranSensor1
        } else if (dataMasuk == "2") {
          state_program = 2;  // Beralih ke pengukuranSensor2
        } else if (dataMasuk == "3") {
          state_program = 3;  // Beralih ke pengukuranSensor3
        } else if (dataMasuk == "4") {
          state_program = 4;  // Beralih ke pengukuranSensor4
        } else if (dataMasuk == "5") {
          state_program = 5;  // Beralih ke pengukuranSensor5
        } else if (dataMasuk == "6") {
          state_program = 6;  // Beralih ke pengukuranSensor6
        } else if (dataMasuk == "8") {
          state_program = 8;  // Beralih ke pengukuranSensor8
        }
      }
    }
  } else if (state_program == 8) {
    while (state_program == 8) { // Program Sensor 8 akan terus berjalan selama state_program = 8
    pengukuranSensor8(); 
      // Periksa kembali input serial untuk kemungkinan perubahan state_program
      if (Serial8.available()) {
        String dataMasuk = Serial8.readStringUntil('\n');
        Serial.println("Sensor "+ dataMasuk +" aktif");
        if (dataMasuk == "0") {
          state_program = 0;   //Beralih ke Idle
        } else if (dataMasuk == "1") {
          state_program = 1;   //Beralih ke pengukuranSensor1
        } else if (dataMasuk == "2") {
          state_program = 2;  // Beralih ke pengukuranSensor2
        } else if (dataMasuk == "3") {
          state_program = 3;  // Beralih ke pengukuranSensor3
        } else if (dataMasuk == "4") {
          state_program = 4;  // Beralih ke pengukuranSensor4
        } else if (dataMasuk == "5") {
          state_program = 5;  // Beralih ke pengukuranSensor5
        } else if (dataMasuk == "6") {
          state_program = 6;  // Beralih ke pengukuranSensor6
        } else if (dataMasuk == "7") {
          state_program = 7;  // Beralih ke pengukuranSensor7
        }
      }
    }
  } 
  //delay(10); // Delay untuk memberi jeda komunikasi
}

void Idle(){
  // aksi Idle tidak terjadi apa apa
  // Reset flag deteksi untuk percobaan selanjutnya
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;

    timeSensor1 = 0;
    timeSensor2 = 0;
    timeSensor3 = 0;
    timeSensor4 = 0;
    timeSensor5 = 0;
    timeSensor6 = 0;
    timeSensor7 = 0;
    timeSensor8 = 0;
}

void pengukuranSensor1() {
  //aksi Program 1
  
  // Cek apakah seluruh sensor telah terdeteksi
  if (sensor1Detected && sensor2Detected && sensor3Detected && sensor4Detected && sensor5Detected && sensor6Detected && sensor7Detected && sensor8Detected) {
    
    // Hitung selisih waktu (ToF)
    unsigned long Tof_2 = timeSensor2 - timeSensor1;
    unsigned long Tof_3 = timeSensor3 - timeSensor1;
    unsigned long Tof_4 = timeSensor4 - timeSensor1;
    unsigned long Tof_5 = timeSensor5 - timeSensor1;
    unsigned long Tof_6 = timeSensor6 - timeSensor1;
    unsigned long Tof_7 = timeSensor7 - timeSensor1;
    unsigned long Tof_8 = timeSensor8 - timeSensor1;
    
    // Ubah tipe data dan formatting
    String dataSend1 = "#" + String(",") + String(Tof_2) + String(",") + String(Tof_3) + String(",") + String(Tof_4) + String(",") + String(Tof_5) + String(",") + String(Tof_6) + String(",") + String(Tof_7) + String(",") + String(Tof_8);

    // Kirim hasil Tof ke SerialBluetooth
    Serial8.println(dataSend1);

    // Tampilkan hasil ke serial monitor
    Serial.print("waktu tempuh (mikrodetik): ");
    Serial.println(dataSend1);

    // Reset flag deteksi untuk percobaan selanjutnya
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;
    microsecondsCounter = 0;

  } else { //jika hanya beberapa yang terdeteksi karenan gangguan maka akan di reset semua

    //reset semua waktu sensor jika hanya beberapa yang terdeteksi
    timeSensor1 = 0;
    timeSensor2 = 0;
    timeSensor3 = 0;
    timeSensor4 = 0;
    timeSensor5 = 0;
    timeSensor6 = 0;
    timeSensor7 = 0;
    timeSensor8 = 0;

    //reset flag
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;

  }
  delay(2000); 
}

void pengukuranSensor2() {
  // aksi Program 2

  // Cek apakah seluruh sensor telah terdeteksi
  if (sensor1Detected && sensor2Detected && sensor3Detected && sensor4Detected && sensor5Detected && sensor6Detected && sensor7Detected && sensor8Detected) {
     
    // Hitung selisih waktu (ToF)
    unsigned long Tof_1 = timeSensor1 - timeSensor2;
    unsigned long Tof_3 = timeSensor3 - timeSensor2;
    unsigned long Tof_4 = timeSensor4 - timeSensor2;
    unsigned long Tof_5 = timeSensor5 - timeSensor2;
    unsigned long Tof_6 = timeSensor6 - timeSensor2;
    unsigned long Tof_7 = timeSensor7 - timeSensor2;
    unsigned long Tof_8 = timeSensor8 - timeSensor2;

    String dataSend2 = String(Tof_1) + String(",") + "#" + String(",") + String(Tof_3) + String(",") + String(Tof_4) + String(",") + String(Tof_5) + String(",") + String(Tof_6) + String(",") + String(Tof_7) + String(",") + String(Tof_8);

    // Kirim hasil Tof ke SerialBluetooth
    Serial8.println(dataSend2);

    // Tampilkan hasil ke serial monitor
    Serial.print("waktu tempuh (mikrodetik): ");
    Serial.println(dataSend2);

    // Reset flag deteksi untuk percobaan selanjutnya
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;
    microsecondsCounter = 0;

  } else { //jika hanya beberapa yang terdeteksi karenan gangguan maka akan di reset semua

    //reset semua waktu sensor jika hanya beberapa yang terdeteksi
    timeSensor1 = 0;
    timeSensor2 = 0;
    timeSensor3 = 0;
    timeSensor4 = 0;
    timeSensor5 = 0;
    timeSensor6 = 0;
    timeSensor7 = 0;
    timeSensor8 = 0;

    //reset flag
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;

  }
  delay(2000);  
}

void pengukuranSensor3() {
  // aksi Program 3

  // Cek apakah seluruh sensor telah terdeteksi
  if (sensor1Detected && sensor2Detected && sensor3Detected && sensor4Detected && sensor5Detected && sensor6Detected && sensor7Detected && sensor8Detected) {
     
    // Hitung selisih waktu (ToF)
    unsigned long Tof_1 = timeSensor1 - timeSensor3;
    unsigned long Tof_2 = timeSensor2 - timeSensor3;
    unsigned long Tof_4 = timeSensor4 - timeSensor3;
    unsigned long Tof_5 = timeSensor5 - timeSensor3;
    unsigned long Tof_6 = timeSensor6 - timeSensor3;
    unsigned long Tof_7 = timeSensor7 - timeSensor3;
    unsigned long Tof_8 = timeSensor8 - timeSensor3;

    String dataSend3 = String(Tof_1) + "," + String(Tof_2) + "," + "#" + "," + String(Tof_4) + "," + String(Tof_5) + "," + String(Tof_6) + "," + String(Tof_7) + "," + String(Tof_8);

    // Kirim hasil Tof ke SerialBluetooth
    Serial8.println(dataSend3);

    // Tampilkan hasil ke serial monitor
    Serial.print("waktu tempuh (mikrodetik): ");
    Serial.println(dataSend3);

    // Reset flag deteksi untuk percobaan selanjutnya
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;
    microsecondsCounter = 0;
  }

  else { //jika hanya beberapa yang terdeteksi karenan gangguan maka akan di reset semua

    //reset semua waktu sensor jika hanya beberapa yang terdeteksi
    timeSensor1 = 0;
    timeSensor2 = 0;
    timeSensor3 = 0;
    timeSensor4 = 0;
    timeSensor5 = 0;
    timeSensor6 = 0;
    timeSensor7 = 0;
    timeSensor8 = 0;

    //reset flag
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;

  }

  delay(2000);   
}

void pengukuranSensor4() {
  // aksi Program 4

  // Cek apakah seluruh sensor telah terdeteksi
  if (sensor1Detected && sensor2Detected && sensor3Detected && sensor4Detected && sensor5Detected && sensor6Detected && sensor7Detected && sensor8Detected) {
     
    // Hitung selisih waktu (ToF)
    unsigned long Tof_1 = timeSensor1 - timeSensor4;
    unsigned long Tof_2 = timeSensor2 - timeSensor4;
    unsigned long Tof_3 = timeSensor3 - timeSensor4;
    unsigned long Tof_5 = timeSensor5 - timeSensor4;
    unsigned long Tof_6 = timeSensor6 - timeSensor4;
    unsigned long Tof_7 = timeSensor7 - timeSensor4;
    unsigned long Tof_8 = timeSensor8 - timeSensor4;

    String dataSend4 = String(Tof_1) + "," + String(Tof_2) + ","  + String(Tof_3) + "," + "#" + "," + String(Tof_5) + "," + String(Tof_6) + "," + String(Tof_7) + "," + String(Tof_8);

    // Kirim hasil Tof ke SerialBluetooth
    Serial8.println(dataSend4);

    // Tampilkan hasil ke serial monitor
    Serial.print("waktu tempuh (mikrodetik): ");
    Serial.println(dataSend4);

    // Reset flag deteksi untuk percobaan selanjutnya
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;
    microsecondsCounter = 0;

  } else { //jika hanya beberapa yang terdeteksi karenan gangguan maka akan di reset semua

    //reset semua waktu sensor jika hanya beberapa yang terdeteksi
    timeSensor1 = 0;
    timeSensor2 = 0;
    timeSensor3 = 0;
    timeSensor4 = 0;
    timeSensor5 = 0;
    timeSensor6 = 0;
    timeSensor7 = 0;
    timeSensor8 = 0;

    //reset flag
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;

  }
  delay(2000);   
}

void pengukuranSensor5() {
  // aksi Program 5

  // Cek apakah seluruh sensor telah terdeteksi
  if (sensor1Detected && sensor2Detected && sensor3Detected && sensor4Detected && sensor5Detected && sensor6Detected && sensor7Detected && sensor8Detected) {
     
    // Hitung selisih waktu (ToF)
    unsigned long Tof_1 = timeSensor1 - timeSensor5;
    unsigned long Tof_2 = timeSensor2 - timeSensor5;
    unsigned long Tof_3 = timeSensor3 - timeSensor5;
    unsigned long Tof_4 = timeSensor4 - timeSensor5;
    unsigned long Tof_6 = timeSensor6 - timeSensor5;
    unsigned long Tof_7 = timeSensor7 - timeSensor5;
    unsigned long Tof_8 = timeSensor8 - timeSensor5;

    String dataSend5 = String(Tof_1) + "," + String(Tof_2) + ","  + String(Tof_3) + "," + String(Tof_4) + "," + "#" + "," + String(Tof_6) + "," + String(Tof_7) + "," + String(Tof_8);

    // Kirim hasil Tof ke SerialBluetooth
    Serial8.println(dataSend5);

    // Tampilkan hasil ke serial monitor
    Serial.print("waktu tempuh (mikrodetik): ");
    Serial.println(dataSend5);

    // Reset flag deteksi untuk percobaan selanjutnya
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;
    microsecondsCounter = 0;

  } else { //jika hanya beberapa yang terdeteksi karenan gangguan maka akan di reset semua

    //reset semua waktu sensor jika hanya beberapa yang terdeteksi
    timeSensor1 = 0;
    timeSensor2 = 0;
    timeSensor3 = 0;
    timeSensor4 = 0;
    timeSensor5 = 0;
    timeSensor6 = 0;
    timeSensor7 = 0;
    timeSensor8 = 0;

    //reset flag
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;

  }
  delay(2000);   
}

void pengukuranSensor6() {
  // aksi Program 6

  // Cek apakah seluruh sensor telah terdeteksi
  if (sensor1Detected && sensor2Detected && sensor3Detected && sensor4Detected && sensor5Detected && sensor6Detected && sensor7Detected && sensor8Detected) {
     
    // Hitung selisih waktu (ToF)
    unsigned long Tof_1 = timeSensor1 - timeSensor6;
    unsigned long Tof_2 = timeSensor2 - timeSensor6;
    unsigned long Tof_3 = timeSensor3 - timeSensor6;
    unsigned long Tof_4 = timeSensor4 - timeSensor6;
    unsigned long Tof_5 = timeSensor5 - timeSensor6;
    unsigned long Tof_7 = timeSensor7 - timeSensor6;
    unsigned long Tof_8 = timeSensor8 - timeSensor6;

    String dataSend6 = String(Tof_1) + "," + String(Tof_2) + ","  + String(Tof_3) + "," + String(Tof_4) + "," + String(Tof_5) + "," + "#" + "," + String(Tof_7) + "," + String(Tof_8);

    // Kirim hasil Tof ke SerialBluetooth
    Serial8.println(dataSend6);

    // Tampilkan hasil ke serial monitor
    Serial.print("waktu tempuh (mikrodetik): ");
    Serial.println(dataSend6);

    // Reset flag deteksi untuk percobaan selanjutnya
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;
    microsecondsCounter = 0;

  } else { //jika hanya beberapa yang terdeteksi karenan gangguan maka akan di reset semua

    //reset semua waktu sensor jika hanya beberapa yang terdeteksi
    timeSensor1 = 0;
    timeSensor2 = 0;
    timeSensor3 = 0;
    timeSensor4 = 0;
    timeSensor5 = 0;
    timeSensor6 = 0;
    timeSensor7 = 0;
    timeSensor8 = 0;

    //reset flag
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;

  }
  delay(2000);   
}

void pengukuranSensor7() {
  // aksi Program 7

  // Cek apakah seluruh sensor telah terdeteksi
  if (sensor1Detected && sensor2Detected && sensor3Detected && sensor4Detected && sensor5Detected && sensor6Detected && sensor7Detected && sensor8Detected) {
     
    // Hitung selisih waktu (ToF)
    unsigned long Tof_1 = timeSensor1 - timeSensor7;
    unsigned long Tof_2 = timeSensor2 - timeSensor7;
    unsigned long Tof_3 = timeSensor3 - timeSensor7;
    unsigned long Tof_4 = timeSensor4 - timeSensor7;
    unsigned long Tof_5 = timeSensor5 - timeSensor7;
    unsigned long Tof_6 = timeSensor6 - timeSensor7;
    unsigned long Tof_8 = timeSensor8 - timeSensor7;

    String dataSend7 = String(Tof_1) + "," + String(Tof_2) + ","  + String(Tof_3) + "," + String(Tof_4) + "," + String(Tof_5) + "," + String(Tof_6) + "," + "#" + "," + String(Tof_8);

    // Kirim hasil Tof ke SerialBluetooth
    Serial8.println(dataSend7);

    // Tampilkan hasil ke serial monitor
    Serial.print("waktu tempuh (mikrodetik): ");
    Serial.println(dataSend7);

    // Reset flag deteksi untuk percobaan selanjutnya
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;
    microsecondsCounter = 0;

  } else { //jika hanya beberapa yang terdeteksi karenan gangguan maka akan di reset semua

    //reset semua waktu sensor jika hanya beberapa yang terdeteksi
    timeSensor1 = 0;
    timeSensor2 = 0;
    timeSensor3 = 0;
    timeSensor4 = 0;
    timeSensor5 = 0;
    timeSensor6 = 0;
    timeSensor7 = 0;
    timeSensor8 = 0;

    //reset flag
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;
  }

  delay(2000);   
}

void pengukuranSensor8() {
  // aksi Program 8

  // Cek apakah seluruh sensor telah terdeteksi
  if (sensor1Detected && sensor2Detected && sensor3Detected && sensor4Detected && sensor5Detected && sensor6Detected && sensor7Detected && sensor8Detected) {
     
    // Hitung selisih waktu (ToF)
    unsigned long Tof_1 = timeSensor1 - timeSensor8;
    unsigned long Tof_2 = timeSensor2 - timeSensor8;
    unsigned long Tof_3 = timeSensor3 - timeSensor8;
    unsigned long Tof_4 = timeSensor4 - timeSensor8;
    unsigned long Tof_5 = timeSensor5 - timeSensor8;
    unsigned long Tof_6 = timeSensor6 - timeSensor8;
    unsigned long Tof_7 = timeSensor7 - timeSensor8;

    String dataSend8 = String(Tof_1) + "," + String(Tof_2) + ","  + String(Tof_3) + "," + String(Tof_4) + "," + String(Tof_5) + "," + String(Tof_6) + "," + String(Tof_7) + "," + "#";

    // Kirim hasil Tof ke SerialBluetooth
    Serial8.println(dataSend8);

    // Tampilkan hasil ke serial monitor
    Serial.print("waktu tempuh (mikrodetik): ");
    Serial.println(dataSend8);

    // Reset flag deteksi untuk percobaan selanjutnya
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;
    microsecondsCounter = 0;

  } else { //jika hanya beberapa yang terdeteksi karenan gangguan maka akan di reset semua

    //reset semua waktu sensor jika hanya beberapa yang terdeteksi
    timeSensor1 = 0;
    timeSensor2 = 0;
    timeSensor3 = 0;
    timeSensor4 = 0;
    timeSensor5 = 0;
    timeSensor6 = 0;
    timeSensor7 = 0;
    timeSensor8 = 0;

    //reset flag
    sensor1Detected = false;
    sensor2Detected = false;
    sensor3Detected = false;
    sensor4Detected = false;
    sensor5Detected = false;
    sensor6Detected = false;
    sensor7Detected = false;
    sensor8Detected = false;

  }
  
  delay(2000);   
}
