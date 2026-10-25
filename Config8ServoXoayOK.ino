/*
  ESP32 30-PIN - 8 SERVO CONTROL VIA SERIAL INPUT
  - Board: ESP32 DevKit V1 (30 pins)
  - Thư viện: ESP32Servo
  Cú pháp lệnh:
    • F[góc], R[góc], B[góc], L[góc] : Servo XOAY viết hoa (GPIO 18, 19, 21, 22)
    • f[góc], r[góc], b[góc], l[góc] : Servo TRUOT viết thường (GPIO 23, 25, 26, 27)
   //------------
  U (TRANG)-D(VANG)
  F (X DUONG)- B (X LA)
  R (CAM) - L (DO)
  //------------   
    • Test KEP/NHA:      KEP, NHA
    • Test xoay cac mat: FNO, BNO, R, L
                         FIN, BIN, U, D
    • Test SHOW 6 mat:  SHOWR (CAM), SHOWL (DO), SHOWB (XANH LA), 
                        SHOWF (XANH DUONG), SHOWD (VANG),SHOWU (TRANG), SHOWEND
  
*/

/*
L180 xoay 2 lan, lan thu 2 là 103 do
R180 xoay 2 lan, lan thu 2 la 100 do
*/

#include <ESP32Servo.h>

// Khai báo chân GPIO kết nối cho 4 Servo cũ (viết hoa)
const int PIN_ROTATE_FRONT = 18;
const int PIN_ROTATE_RIGHT = 19;
const int PIN_ROTATE_BACK  = 21;
const int PIN_ROTATE_LEFT  = 22;

// Khai báo chân GPIO kết nối cho 4 Servo mới (viết thường)
const int PIN_SLIDER_f = 23;
const int PIN_SLIDER_r = 25;
const int PIN_SLIDER_b = 26;
const int PIN_SLIDER_l = 27;

// Khởi tạo 4 đối tượng Servo viết hoa
Servo RotateFront;
Servo RotateRight;
Servo RotateBack;
Servo RotateLeft;

// Khởi tạo 4 đối tượng Servo viết thường
Servo Slider_f;
Servo Slider_r;
Servo Slider_b;
Servo Slider_l;

// Goc servo slider kep nha
// VD: Slider_f.write(kep);
#define kep 0
#define nha 120

// Goc servo Rotate Giua(90),CC(0),NC(180) 
// VD  RotateFront.write(giua);
#define cc 180
#define giua   90
#define nc   0
#define show 135

//time 
#define timeDelay 2000

void printGuide() {
  Serial.println("\n------------------------------------------------");
  Serial.println(">>> CÚ PHÁP LỆNH ĐIỀU KHIỂN 8 SERVO:");
  Serial.println("1. Nhóm Servo viết hoa:");
  Serial.println("  • F[góc] : RotateFront (Ví dụ: F90)");
  Serial.println("  • R[góc] : RotateRight (Ví dụ: R45)");
  Serial.println("  • B[góc] : RotateBack  (Ví dụ: B120)");
  Serial.println("  • L[góc] : RotateLeft  (Ví dụ: L0)");
  Serial.println("2. Nhóm Servo viết thường:");
  Serial.println("  • f[góc] : Slider_f    (Ví dụ: f90)");
  Serial.println("  • r[góc] : Slider_r    (Ví dụ: r45)");
  Serial.println("  • b[góc] : Slider_b    (Ví dụ: b120)");
  Serial.println("  • l[góc] : Slider_l    (Ví dụ: l0)");
  Serial.println("3. Tổng hợp:");
  Serial.println("  • ALL[góc]: Xoay TẤT CẢ 8 servo cùng lúc (Ví dụ: ALL90)");
  Serial.println("------------------------------------------------\n");
}

// thanh add xoay tu mat FBRL
void xuLyLenh(String input) {
  input.trim();

  if (input == "FNO") {
    Serial.println("xoay F - normal");

    RotateFront.write(cc);  delay(timeDelay);
    Slider_f.write(nha);    delay(timeDelay);
    RotateFront.write(giua);delay(timeDelay);
    Slider_f.write(kep);    delay(timeDelay);
  }
  else if (input == "BNO") {
    Serial.println("xoay B - normal");

    RotateBack.write(cc);   delay(timeDelay);
    Slider_b.write(nha);    delay(timeDelay);
    RotateBack.write(giua); delay(timeDelay);
    Slider_b.write(kep);    delay(timeDelay);
  }
  else if (input == "R") {
    Serial.println("xoay R");
    
    RotateRight.write(cc);  delay(timeDelay);
    Slider_r.write(nha);    delay(timeDelay);
    RotateRight.write(giua);delay(timeDelay);
    Slider_r.write(kep);    delay(timeDelay);
  }
  else if (input == "L") {
    Serial.println("xoay L");

    RotateLeft.write(cc);   delay(timeDelay);
    Slider_l.write(nha);    delay(timeDelay);
    RotateLeft.write(giua); delay(timeDelay);
    Slider_l.write(kep);    delay(timeDelay);
  }
  else if (input == "U") {
    Serial.println("xoay U");
    
    RotateLeft.write(cc);     delay(timeDelay);
    Slider_l.write(nha);    delay(timeDelay);
    RotateLeft.write(giua);   delay(timeDelay);
    Slider_l.write(kep);    delay(timeDelay);
  }
  else if (input == "D") {
    Serial.println("xoay D");

    RotateRight.write(cc);   delay(timeDelay);
    Slider_r.write(nha);    delay(timeDelay);
    RotateRight.write(giua); delay(timeDelay);
    Slider_r.write(kep);    delay(timeDelay);
  }
  else if (input == "FIN") {
    Serial.println("xoay F - invert");

    RotateFront.write(cc);  delay(timeDelay);
    Slider_f.write(nha);    delay(timeDelay);
    RotateFront.write(giua);delay(timeDelay);
    Slider_f.write(kep);    delay(timeDelay);
  }
  else if (input == "BIN") {
    Serial.println("xoay B - invert");

    RotateBack.write(cc);   delay(timeDelay);
    Slider_b.write(nha);    delay(timeDelay);
    RotateBack.write(giua); delay(timeDelay);
    Slider_b.write(kep);    delay(timeDelay);
  }
  else if (input == "KEP") {
    Serial.println("Da kep");

    Slider_f.write(kep);    
    Slider_b.write(kep);
    delay(200);
    Slider_l.write(kep);    
    Slider_r.write(kep);    
  }
  else if (input == "KEPFB") {
    Serial.println("Da kep FB");
    Slider_f.write(kep); Slider_b.write(kep);  delay(200);  
  }
  else if (input == "KEPRL") {
    Serial.println("Da kep RL");
    Slider_r.write(kep); Slider_l.write(kep);  delay(200);  
  }
  else if (input == "NHA") {
    Serial.println("Da nha");
    Slider_f.write(90);    
    Slider_b.write(90);
    delay(200);
    Slider_l.write(90);    
    Slider_r.write(90);    
  }
  else if (input == "NHAFB") {
    Serial.println("Da kep FB");
    Slider_f.write(nha); Slider_b.write(nha);  delay(200);  
  }
  else if (input == "NHARL") {
    Serial.println("Da kep FB");
    Slider_r.write(nha); Slider_l.write(nha);  delay(200);  
  }
  else if (input == "LATPHAI") {
    Serial.println("Da LAT PHAI");
    RotateFront.write(180); RotateBack.write(0);   delay(200);  
  }
  else if (input == "LATGIUA") {
    Serial.println("Da LAT GIUA");
    RotateFront.write(90); RotateBack.write(90);   delay(200);  
  }
  else if (input == "LATTRAI") {
    Serial.println("Da LAT TRAI");
    RotateFront.write(0); RotateBack.write(180);   delay(200);  
  }
  // TEST SHOW RLB

  // dang show thanh
  else if (input == "SHOWR") {
    Serial.println("DA SHOW R");

    RotateRight.write(90+45);delay(timeDelay);
    Slider_r.write(nha); Slider_l.write(nha);delay(timeDelay); 
    RotateFront.write(0); RotateBack.write(180);  delay(timeDelay);  
  }//OK
  else if (input == "SHOWL") {
    Serial.println("DA SHOW L");

    RotateFront.write(90); RotateBack.write(90);RotateLeft.write(90);delay(timeDelay);  //FB xoay 90
    Slider_r.write(kep); Slider_l.write(kep);  delay(timeDelay);  // LR kep

    RotateRight.write(90+45-50);delay(timeDelay);// R xoay ve init OK
    RotateLeft.write(90+45);delay(timeDelay);    // F XOAY MOI
    Slider_r.write(nha); Slider_l.write(nha);  delay(timeDelay);
    RotateFront.write(180); RotateBack.write(0);  delay(timeDelay);          
  }// OK
  else if (input == "SHOWB") {
    Serial.println("DA SHOW B");

    RotateRight.write(90);//delay(timeDelay);
    RotateFront.write(90); RotateBack.write(90);  delay(timeDelay);  //FB xoay nguoc lai
    Slider_r.write(kep); Slider_l.write(kep);  delay(timeDelay);  // LR kep
   
    RotateLeft.write(90+45-45); delay(timeDelay);// L XOAY VE INIT? 50 TO 45
    RotateBack.write(90+45);delay(timeDelay);// B XOAY MOI

    Slider_f.write(nha); Slider_b.write(nha);delay(timeDelay); 
    RotateRight.write(0); RotateLeft.write(180);  delay(timeDelay);         
  }
  else if (input == "SHOWF") {
    Serial.println("DA SHOW F");

    RotateRight.write(90); RotateLeft.write(90);  delay(timeDelay);  //FB xoay nguoc lai
    Slider_f.write(kep); Slider_b.write(kep);  delay(timeDelay);  // LR kep
   
    RotateBack.write(90+45-50); delay(timeDelay);// B XOAY VE INIT?
    RotateFront.write(90+45);delay(timeDelay);    // F XOAY MOI

    Slider_f.write(nha); Slider_b.write(nha);delay(timeDelay); 
    RotateRight.write(180); RotateLeft.write(0);  delay(timeDelay); 
  }//OK
  else if (input == "SHOWD") {
    Serial.println("DA SHOW D");
  // dang check
    RotateRight.write(90); RotateLeft.write(90);RotateBack.write(90);  delay(timeDelay);  //FB xoay nguoc lai
    Slider_f.write(kep); Slider_b.write(kep);  delay(timeDelay);  // LR kep
   
    RotateFront.write(90+45-50); delay(timeDelay);// F XOAY VE INIT?
    Slider_f.write(nha); Slider_b.write(nha);delay(timeDelay); 

    RotateFront.write(180); RotateBack.write(0);delay(timeDelay);
    Slider_f.write(kep); Slider_b.write(kep);delay(timeDelay);// BI ROT
 
    Slider_r.write(nha); Slider_l.write(nha);delay(timeDelay);
    RotateFront.write(90); RotateBack.write(90);delay(timeDelay);

    Slider_r.write(kep); Slider_l.write(kep);delay(timeDelay);
    RotateRight.write(90+45);delay(timeDelay);// SHOW D
    Slider_r.write(nha); Slider_l.write(nha);delay(timeDelay);
    RotateFront.write(0); RotateBack.write(180);delay(timeDelay);
  }//OK
  else if (input == "SHOWU") {
    Serial.println("DA SHOW U");
  
    RotateFront.write(90); RotateBack.write(90);  delay(timeDelay);  //QUAY PHAI
    Slider_r.write(kep); Slider_l.write(kep);  delay(timeDelay);  // LR kep
   
    RotateRight.write(90+45-50); delay(timeDelay);// R XOAY VE INIT?
    RotateLeft.write(90+45); delay(timeDelay);// L XOAY MOI
    Slider_r.write(nha); Slider_l.write(nha);delay(timeDelay); 

    RotateFront.write(180); RotateBack.write(0);delay(timeDelay);// SHOW U
  }//OK
  else if (input == "SHOWEND") {
    Serial.println("DA SHOW END");
  // dang check
    RotateFront.write(90); RotateBack.write(90);RotateRight.write(90);  delay(timeDelay);  //QUAY PHAI
   
    Slider_r.write(kep); Slider_l.write(kep);  delay(timeDelay);  // LR kep
    RotateLeft.write(90+45-45); delay(timeDelay);// L XOAY VE INIT?
   
    Slider_f.write(nha); Slider_b.write(nha);delay(timeDelay); 
    RotateFront.write(0); RotateBack.write(180);delay(timeDelay);// SHOW U
    Slider_f.write(kep); Slider_b.write(kep);delay(timeDelay); 

    Slider_r.write(nha); Slider_l.write(nha);delay(timeDelay); 
    RotateFront.write(90); RotateBack.write(90);delay(timeDelay);//check
    
     Slider_r.write(kep); Slider_l.write(kep);delay(timeDelay); 
  }
  else {
    Serial.println("Lenh khong hop le");
  }
}


void setup() {
  Serial.begin(115200);
  delay(1000);

  // Cho phép phân bổ các kênh PWM phần cứng cho ESP32
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Thiết lập tần số tiêu chuẩn cho các Servo (50Hz)
  RotateFront.setPeriodHertz(50);
  RotateRight.setPeriodHertz(50);
  RotateBack.setPeriodHertz(50);
  RotateLeft.setPeriodHertz(50);

  Slider_f.setPeriodHertz(50);
  Slider_r.setPeriodHertz(50);
  Slider_b.setPeriodHertz(50);
  Slider_l.setPeriodHertz(50);

  // Gắn chân Servo với thông số Pulse Width chuẩn (Giữ nguyên cấu hình cũ)
  RotateFront.attach(PIN_ROTATE_FRONT, 500, 2500); // OK
  RotateRight.attach(PIN_ROTATE_RIGHT, 500, 2500); // to do 180 OK,
  RotateBack.attach(PIN_ROTATE_BACK,   500, 2500); // OK  500, 2400
  RotateLeft.attach(PIN_ROTATE_LEFT,   500, 2500); // to do  500,2500

  // Gắn chân cho 4 Servo mới (viết thường)
  // gia tri can cali
  Slider_f.attach(PIN_SLIDER_f, 500, 2400);
  Slider_r.attach(PIN_SLIDER_r, 500, 2400);
  Slider_b.attach(PIN_SLIDER_b, 500, 2400);
  Slider_l.attach(PIN_SLIDER_l, 500, 2400);

  // 4 servo xoay vi tri giua (90)
  // 4 servo truot vi tri nha
  RotateFront.write(giua);  RotateRight.write(giua);
  RotateBack.write(giua);  RotateLeft.write(giua);

  Slider_f.write(90);  Slider_r.write(90);
  Slider_b.write(90);  Slider_l.write(90);

  Serial.println("\n=== rubik ready ===");
  //printGuide();
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Xóa khoảng trắng và ký tự xuống dòng dư thừa
    // thanh them xu ly tung mat FBRL
  if (input == "KEP" || input == "NHA"|| 
      input == "KEPFB" || input == "KEPRL"||
      input == "NHAFB" || input == "NHARL"||
      input == "LATPHAI" || input == "LATGIUA"|| input == "LATTRAI"||
      input == "FNO" || input == "BNO"|| input == "R"|| input == "L"||
      input == "FIN" || input == "BIN"|| input == "U"|| input == "D"||
      input == "SHOWR"|| input == "SHOWL"|| input == "SHOWB"|| 
      input == "SHOWF"||  input == "SHOWD" || input == "SHOWU"||
      input == "SHOWEND") {
    xuLyLenh(input);
    return;
  }

    //

    if (input.length() == 0) return;

    // Phân biệt chuỗi ALL không phân biệt hoa thường
    String upperInput = input;
    upperInput.toUpperCase();

       // --- 2. Lệnh điều khiển Servo viết hoa (F, R, B, L) ---
    if (input.startsWith("F")) {
      int angle = input.substring(1).toInt();
      if (angle >= 0 && angle <= 180) {
        RotateFront.write(angle);
        Serial.print("-> [RotateFront] xoay đến góc: ");
        Serial.print(angle);
        Serial.println(" độ");
      } else {
        Serial.println("❌ Lỗi: Góc nhập vào phải từ 0 đến 180!");
      }
    }
    else if (input.startsWith("R")) {
      int angle = input.substring(1).toInt();
      if (angle >= 0 && angle <= 180) {
        RotateRight.write(angle);
        Serial.print("-> [RotateRight] xoay đến góc: ");
        Serial.print(angle);
        Serial.println(" độ");
      }/* 
      else if (angle>100){
          RotateRight.writeMicroseconds(3000); //THANH
        Serial.print("-> [RotateRight] xoay đến góc mili: ");
        Serial.print(angle);
        Serial.println(" độ");
      }*/
      else {
        Serial.println("❌ Lỗi: Góc nhập vào phải từ 0 đến 180!");
      }
    }
    else if (input.startsWith("B")) {
      int angle = input.substring(1).toInt();
      if (angle >= 0 && angle <= 180) {
        RotateBack.write(angle);
        Serial.print("-> [RotateBack] xoay đến góc: ");
        Serial.print(angle);
        Serial.println(" độ");
      } else {
        Serial.println("❌ Lỗi: Góc nhập vào phải từ 0 đến 180!");
      }
    }
    else if (input.startsWith("L")) {
      int angle = input.substring(1).toInt();
      if (angle >= 0 && angle <= 180) {
        RotateLeft.write(angle);
        Serial.print("-> [RotateLeft] xoay đến góc: ");
        Serial.print(angle);
        Serial.println(" độ");
      } else {
        Serial.println("❌ Lỗi: Góc nhập vào phải từ 0 đến 180!");
      }
    }
    // --- 3. Lệnh điều khiển Servo viết thường (f, r, b, l) ---
    else if (input.startsWith("f")) {
      int angle = input.substring(1).toInt();
      if (angle >= 0 && angle <= 180) {
        Slider_f.write(angle);
        Serial.print("-> [Slider_f] xoay đến góc: ");
        Serial.print(angle);
        Serial.println(" độ");
      } else {
        Serial.println("❌ Lỗi: Góc nhập vào phải từ 0 đến 180!");
      }
    }
    else if (input.startsWith("r")) {
      int angle = input.substring(1).toInt();
      if (angle >= 0 && angle <= 180) {
        Slider_r.write(angle);
        Serial.print("-> [Slider_r] xoay đến góc: ");
        Serial.print(angle);
        Serial.println(" độ");
      } else {
        Serial.println("❌ Lỗi: Góc nhập vào phải từ 0 đến 180!");
      }
    }
    else if (input.startsWith("b")) {
      int angle = input.substring(1).toInt();
      if (angle >= 0 && angle <= 180) {
        Slider_b.write(angle);
        Serial.print("-> [Slider_b] xoay đến góc: ");
        Serial.print(angle);
        Serial.println(" độ");
      } else {
        Serial.println("❌ Lỗi: Góc nhập vào phải từ 0 đến 180!");
      }
    }
    else if (input.startsWith("l")) {
      int angle = input.substring(1).toInt();
      if (angle >= 0 && angle <= 180) {
        Slider_l.write(angle);
        Serial.print("-> [Slider_l] xoay đến góc: ");
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