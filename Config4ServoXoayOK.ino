/*
  ESP32 30-PIN - 4 SERVO CONTROL VIA SERIAL INPUT
  - Board: ESP32 DevKit V1 (30 pins)
  - Thư viện: ESP32Servo
  - Danh sách Servo:
    + SliderFront: GPIO 18
    + SliderRight: GPIO 19
    + SliderBack:  GPIO 21
    + SliderLeft:  GPIO 22

    • F[góc] : Điều khiển SliderFront (Ví dụ: F90, F0, F180)
  • R[góc] : Điều khiển SliderRight (Ví dụ: R45, R180)
  • B[góc] : Điều khiển SliderBack  (Ví dụ: B120)
  • L[góc] : Điều khiển SliderLeft  (Ví dụ: L0)
  • ALL[góc]: Xoay TẤT CẢ 4 servo cùng lúc (Ví dụ: ALL90)
*/

#include <ESP32Servo.h>

// Khai báo chân GPIO kết nối cho 4 Servo
const int PIN_SLIDER_FRONT = 18;
const int PIN_SLIDER_RIGHT = 19;
const int PIN_SLIDER_BACK  = 21;
const int PIN_SLIDER_LEFT  = 22;

// Khởi tạo 4 đối tượng Servo riêng biệt
Servo SliderFront;
Servo SliderRight;
Servo SliderBack;
Servo SliderLeft;

void printGuide() {
  Serial.println("\n------------------------------------------------");
  Serial.println(">>> CÚ PHÁP LỆNH ĐIỀU KHIỂN SERVO:");
  Serial.println("Format: [Tên Servo][Góc]");
  Serial.println("  • F[góc] : Điều khiển SliderFront (Ví dụ: F90, F0, F180)");
  Serial.println("  • R[góc] : Điều khiển SliderRight (Ví dụ: R45, R180)");
  Serial.println("  • B[góc] : Điều khiển SliderBack  (Ví dụ: B120)");
  Serial.println("  • L[góc] : Điều khiển SliderLeft  (Ví dụ: L0)");
  Serial.println("  • ALL[góc]: Xoay TẤT CẢ 4 servo cùng lúc (Ví dụ: ALL90)");
  Serial.println("------------------------------------------------\n");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=== HỆ THỐNG ĐIỀU KHIỂN 4 SERVO ESP32 ===");

  // Cho phép phân bổ các kênh PWM phần cứng cho ESP32
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Thiết lập tần số tiêu chuẩn cho các Servo (50Hz)
  SliderFront.setPeriodHertz(50);
  SliderRight.setPeriodHertz(50);
  SliderBack.setPeriodHertz(50);
  SliderLeft.setPeriodHertz(50);

  // Gắn chân Servo với thông số Pulse Width chuẩn (500us - 2400us)
  SliderFront.attach(PIN_SLIDER_FRONT, 500, 2500);//OK
  SliderRight.attach(PIN_SLIDER_RIGHT, 320, 2500);//OK
  SliderBack.attach(PIN_SLIDER_BACK,   500, 2400);//OK
  SliderLeft.attach(PIN_SLIDER_LEFT,   450, 2500);// OK

  // Khởi tạo đưa toàn bộ 4 Servo về vị trí 0 độ
  SliderFront.write(90);
  SliderRight.write(90);
  SliderBack.write(90);
  SliderLeft.write(90);

  printGuide();
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Xóa khoảng trắng và ký tự xuống dòng dư thừa
    input.toUpperCase(); // Chuyển chữ hoa để xử lý dễ dàng

    if (input.length() == 0) return;

    // --- 1. Lệnh điều khiển TẤT CẢ 4 Servo (Ví dụ: ALL90) ---
    if (input.startsWith("ALL")) {
      int angle = input.substring(3).toInt();
      if (angle >= 0 && angle <= 180) {
        SliderFront.write(angle);
        SliderRight.write(angle);
        SliderBack.write(angle);
        SliderLeft.write(angle);
        Serial.print("-> Đã xoay TẤT CẢ 4 Servo sang góc: ");
        Serial.print(angle);
        Serial.println(" độ");
      } else {
        Serial.println("❌ Lỗi: Góc nhập vào phải từ 0 đến 180!");
      }
    }
    // --- 2. Lệnh điều khiển SliderFront (Ví dụ: F90) ---
    else if (input.startsWith("F")) {
      int angle = input.substring(1).toInt();
      if (angle >= 0 && angle <= 180) {
        SliderFront.write(angle);
        Serial.print("-> [SliderFront] xoay đến góc: ");
        Serial.print(angle);
        Serial.println(" độ");
      } else {
        Serial.println("❌ Lỗi: Góc nhập vào phải từ 0 đến 180!");
      }
    }
    // --- 3. Lệnh điều khiển SliderRight (Ví dụ: R90) ---
    else if (input.startsWith("R")) {
      int angle = input.substring(1).toInt();
      if (angle >= 0 && angle <= 180) {
        SliderRight.write(angle);
        Serial.print("-> [SliderRight] xoay đến góc: ");
        Serial.print(angle);
        Serial.println(" độ");
      } else {
        Serial.println("❌ Lỗi: Góc nhập vào phải từ 0 đến 180!");
      }
    }
    // --- 4. Lệnh điều khiển SliderBack (Ví dụ: B90) ---
    else if (input.startsWith("B")) {
      int angle = input.substring(1).toInt();
      if (angle >= 0 && angle <= 180) {
        SliderBack.write(angle);
        Serial.print("-> [SliderBack] xoay đến góc: ");
        Serial.print(angle);
        Serial.println(" độ");
      } else {
        Serial.println("❌ Lỗi: Góc nhập vào phải từ 0 đến 180!");
      }
    }
    // --- 5. Lệnh điều khiển SliderLeft (Ví dụ: L90) ---
    else if (input.startsWith("L")) {
      int angle = input.substring(1).toInt();
      if (angle >= 0 && angle <= 180) {
        SliderLeft.write(angle);
        Serial.print("-> [SliderLeft] xoay đến góc: ");
        Serial.print(angle);
        Serial.println(" độ");
      } else {
        Serial.println("❌ Lỗi: Góc nhập vào phải từ 0 đến 180!");
      }
    }
    // Cú pháp không hợp lệ
    else {
      Serial.println("❌ Cú pháp không đúng! Vui lòng đọc hướng dẫn bên dưới:");
      printGuide();
    }
  }
}