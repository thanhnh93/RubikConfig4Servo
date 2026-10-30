/*
  ESP32 30-PIN - 8 SERVO RUBIK SOLVER (AUTO MOVE LIST)
  - Board: ESP32 DevKit V1 (30 pins)
  - Thư viện: ESP32Servo
  - Chế độ: Nhập 's' từ Serial Monitor để chạy tự động theo mảng moveList[]
*/

#include <ESP32Servo.h>

// Khai báo chân GPIO kết nối cho 4 Servo xoay (viết hoa)
const int PIN_ROTATE_FRONT = 18;
const int PIN_ROTATE_RIGHT = 19;
const int PIN_ROTATE_BACK  = 21;
const int PIN_ROTATE_LEFT  = 22;

// Khai báo chân GPIO kết nối cho 4 Servo trượt (viết thường)
const int PIN_SLIDER_f = 23;
const int PIN_SLIDER_r = 25;
const int PIN_SLIDER_b = 26;
const int PIN_SLIDER_l = 27;

// Khởi tạo 4 đối tượng Servo xoay
Servo RotateFront;
Servo RotateRight;
Servo RotateBack;
Servo RotateLeft;

// Khởi tạo 4 đối tượng Servo trượt
Servo Slider_f;
Servo Slider_r;
Servo Slider_b;
Servo Slider_l;

// Góc servo slider kẹp/nhả
#define kep 0
#define nha 120

// Góc servo Rotate: Giữa(90), Thuận/CC(180), Ngược/NC(0)
#define cc   180
#define giua 90
#define nc   0
#define show 135

// Thời gian trễ giữa các bước
#define timeDelay 500//2000

/* ==============================
   1. ĐỊNH NGHĨA & BIẾN TRẠNG THÁI
   ============================== */
#define IDLE    0
#define BUSY    1

#define NORMAL  0
#define INVERT  1

int machineState = IDLE;
int cubeState    = NORMAL;

/* ==============================
   2. HÀM CƠ SỞ DÙNG CHUNG (RÚT GỌN CODE)
   ============================== */

// Thực hiện 1 chu trình xoay mặt tiêu chuẩn (4 bước)
void chuTrinhXoay(Servo &servoRotate, Servo &servoSlider, int gocXoay) {
  servoRotate.write(gocXoay); delay(timeDelay);
  servoSlider.write(nha);     delay(timeDelay);
  servoRotate.write(giua);    delay(timeDelay);
  servoSlider.write(kep);     delay(timeDelay);
}

// Thực hiện quy trình lật khối Rubik dùng chung cho Normal <-> Invert
void latKhoiRubik(int gocFront, int gocBack, int trangThaiMoi) {
  Slider_f.write(nha);         Slider_b.write(nha);        delay(timeDelay);
  RotateFront.write(gocFront); RotateBack.write(gocBack);  delay(timeDelay); // Tránh rơi
  Slider_f.write(kep);         Slider_b.write(kep);        delay(timeDelay);

  Slider_r.write(nha);         Slider_l.write(nha);        delay(timeDelay);
  RotateFront.write(giua);     RotateBack.write(giua);     delay(timeDelay);
  Slider_r.write(kep);         Slider_l.write(kep);        delay(timeDelay);

  cubeState = trangThaiMoi;
}

void KEP(){
  Serial.println("Da kep");

    Slider_f.write(kep);        Slider_b.write(kep);    delay(200);
    Slider_l.write(kep);        Slider_r.write(kep); }

void NHA(){
  Serial.println("Da nha");
    Slider_f.write(90);      Slider_b.write(90);    delay(200);
    Slider_l.write(90);      Slider_r.write(90);
}


/* ==============================
   3. THIẾT LẬP BAN ĐẦU (SETUP)
   ============================== */
void setup() {
  Serial.begin(115200);
  delay(1000);

  // Phân bổ các kênh PWM phần cứng cho ESP32
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

  // Gắn chân Servo xoay với thông số Pulse Width chuẩn
  RotateFront.attach(PIN_ROTATE_FRONT, 500, 2500);
  RotateRight.attach(PIN_ROTATE_RIGHT, 500, 2500);
  RotateBack.attach(PIN_ROTATE_BACK,   500, 2500);
  RotateLeft.attach(PIN_ROTATE_LEFT,   500, 2500);

  // Gắn chân cho 4 Servo trượt
  Slider_f.attach(PIN_SLIDER_f, 500, 2400);
  Slider_r.attach(PIN_SLIDER_r, 500, 2400);
  Slider_b.attach(PIN_SLIDER_b, 500, 2400);
  Slider_l.attach(PIN_SLIDER_l, 500, 2400);

  // Khởi tạo vị trí ban đầu: 4 servo xoay ở giữa (90), 4 servo trượt ở góc 90
  RotateFront.write(giua); RotateRight.write(giua);
  RotateBack.write(giua);  RotateLeft.write(giua);

  Slider_f.write(90); Slider_r.write(90);
  Slider_b.write(90); Slider_l.write(90);

  machineState = IDLE;
  cubeState    = NORMAL;

  Serial.println("Machine: IDLE");
  Serial.println("cubeState: NORMAL");
  Serial.println("Nhap s de bat dau.");
}

/* ==============================
   4. VÒNG LẶP CHÍNH (LOOP)
   ============================== */
void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    // Chỉ nhận lệnh "s" khi máy đang ở trạng thái IDLE
    if (input == "kep"){
      KEP();
    }
    if (input == "nha"){
      NHA();
    }
    if (input == "s" && machineState == IDLE) {
      machineState = BUSY;
      Serial.println("Machine: BUSY");

      // Chạy tự động danh sách lệnh trong moveList[]
      Move();

      // Xử lý xong thì trở về IDLE
      machineState = IDLE;
      Serial.println("Machine: IDLE");
      Serial.println("Nhap s de chay tiep.");
    }
  }
}

/* ==============================
   5. HÀM CHẠY TỰ ĐỘNG (MOVE)
   ============================== */
void Move() {
  // Danh sách các lệnh xoay Rubik
  String moveList[] = {
    "F", "B'", "L2", "D'",
    "R'", "U", "B'", "D'",
    "L", "U'", "B2", "U",
    "B2", "D'", "R2", "B2",
    "U'", "R2", "U2", "R2","L2"
  };

  int totalMoves = sizeof(moveList) / sizeof(moveList[0]);

  for (int i = 0; i < totalMoves; i++) {
    String move = moveList[i];

    Serial.println();
    Serial.print("Lenh dang xu ly: ");
    Serial.println(move);

    Serial.print("cubeState truoc khi xu ly: ");
    Serial.println(cubeState == NORMAL ? "NORMAL" : "INVERT");

    // TRẠNG THÁI NORMAL: Xử lý F, B, R, L. Gặp U, D thì lật sang INVERT
    if (cubeState == NORMAL) {
      if (move == "F" || move == "F'" || move == "F2") {
        xuLyF(move);
      }
      else if (move == "B" || move == "B'" || move == "B2") {
        xuLyB(move);
      }
      else if (move == "R" || move == "R'" || move == "R2") {
        xuLyR(move);
      }
      else if (move == "L" || move == "L'" || move == "L2") {
        xuLyL(move);
      }
      else if (move == "U" || move == "U'" || move == "U2") {
        NormalToInvert();
        xuLyU(move);
      }
      else if (move == "D" || move == "D'" || move == "D2") {
        NormalToInvert();
        xuLyD(move);
      }
      else {
        Serial.println("Lenh khong hop le!");
      }
    }
    // TRẠNG THÁI INVERT: Xử lý U, D, F, B. Gặp R, L thì trở về NORMAL
    else if (cubeState == INVERT) {
      if (move == "U" || move == "U'" || move == "U2") {
        xuLyU(move);
      }
      else if (move == "D" || move == "D'" || move == "D2") {
        xuLyD(move);
      }
      else if (move == "F" || move == "F'" || move == "F2") {
        xuLyF(move);
      }
      else if (move == "B" || move == "B'" || move == "B2") {
        xuLyB(move);
      }
      else if (move == "R" || move == "R'" || move == "R2") {
        InvertToNormal();
        xuLyR(move);
      }
      else if (move == "L" || move == "L'" || move == "L2") {
        InvertToNormal();
        xuLyL(move);
      }
      else {
        Serial.println("Lenh khong hop le!");
      }
    }

    Serial.print("cubeState sau khi xu ly: ");
    Serial.println(cubeState == NORMAL ? "NORMAL" : "INVERT");
  }
}

/* ==============================
   6. CÁC HÀM LẬT RUBIK
   ============================== */
void NormalToInvert() {
  Serial.println("Lat Rubik: NORMAL TO INVERT");
  latKhoiRubik(180 - 5, 0 + 5, INVERT);
}

void InvertToNormal() {
  Serial.println("Lat Rubik: INVERT TO NORMAL");
  latKhoiRubik(0 + 5, 180 - 5, NORMAL);
}

/* ==============================
   7. CÁC HÀM XỬ LÝ TỪNG MẶT
   ============================== */

void xuLyF(String move) {
  Serial.print("Xu ly mat F - NORMAL: ");
  if (move == "F") {
    Serial.println("Xoay F (90 do thuan)");
    chuTrinhXoay(RotateFront, Slider_f, cc);
  }
  else if (move == "F'") {
    Serial.println("Xoay F' (90 do nguoc)");
    chuTrinhXoay(RotateFront, Slider_f, nc);
  }
  else if (move == "F2") {
    Serial.println("Xoay F2 (180 do)");
    chuTrinhXoay(RotateFront, Slider_f, cc); // Lần 1
    chuTrinhXoay(RotateFront, Slider_f, cc); // Lần 2
  }
}

void xuLyB(String move) {
  Serial.print("Xu ly mat B - NORMAL: ");
  if (move == "B") {
    Serial.println("Xoay B (90 do thuan)");
    chuTrinhXoay(RotateBack, Slider_b, cc);
  }
  else if (move == "B'") {
    Serial.println("Xoay B' (90 do nguoc)");
    chuTrinhXoay(RotateBack, Slider_b, nc);
  }
  else if (move == "B2") {
    Serial.println("Xoay B2 (180 do)");
    chuTrinhXoay(RotateBack, Slider_b, cc); // Lần 1
    chuTrinhXoay(RotateBack, Slider_b, cc); // Lần 2
  }
}

void xuLyR(String move) {
  Serial.print("Xu ly mat R: ");
  if (move == "R") {
    Serial.println("Xoay R (90 do thuan)");
    chuTrinhXoay(RotateRight, Slider_r, cc);
    chuTrinhXoay(RotateRight, Slider_r, 100); // Bù 100
  }
  else if (move == "R'") {
    Serial.println("Xoay R' (90 do nguoc)");
    chuTrinhXoay(RotateRight, Slider_r, nc);
  }
  else if (move == "R2") {
    Serial.println("Xoay R2 (180 do)");
    chuTrinhXoay(RotateRight, Slider_r, cc);  // Xoay R1
    chuTrinhXoay(RotateRight, Slider_r, cc);  // Xoay R2
    chuTrinhXoay(RotateRight, Slider_r, 100); // Xoay 100 bù thêm
  }
}

void xuLyL(String move) {
  Serial.print("Xu ly mat L: ");
  if (move == "L") {
    Serial.println("Xoay L (90 do thuan)");
    chuTrinhXoay(RotateLeft, Slider_l, cc);
    chuTrinhXoay(RotateLeft, Slider_l, 103); // Bù 103
  }
  else if (move == "L'") {
    Serial.println("Xoay L' (90 do nguoc)");
    chuTrinhXoay(RotateLeft, Slider_l, nc);
  }
  else if (move == "L2") {
    Serial.println("Xoay L2 (180 do)");
    chuTrinhXoay(RotateLeft, Slider_l, cc);  // Lần 1
    chuTrinhXoay(RotateLeft, Slider_l, cc);  // Lần 2
    chuTrinhXoay(RotateLeft, Slider_l, 103); // Bù 103
  }
}

void xuLyU(String move) {
  Serial.print("Xu ly mat UP: ");
  // Giống xoay L
  if (move == "U") {
    Serial.println("Xoay U (90 do thuan)");
    chuTrinhXoay(RotateLeft, Slider_l, cc);
    chuTrinhXoay(RotateLeft, Slider_l, 103); // Bù 103
  }
  else if (move == "U'") {
    Serial.println("Xoay U' (90 do nguoc)");
    chuTrinhXoay(RotateLeft, Slider_l, nc);
  }
  else if (move == "U2") {
    Serial.println("Xoay U2 (180 do)");
    chuTrinhXoay(RotateLeft, Slider_l, cc);  // Lần 1
    chuTrinhXoay(RotateLeft, Slider_l, cc);  // Lần 2
    chuTrinhXoay(RotateLeft, Slider_l, 103); // Bù 103
  }
}

void xuLyD(String move) {
  Serial.print("Xu ly mat DOWN: ");
  // Giống mặt R
  if (move == "D") {
    Serial.println("Xoay D (90 do thuan)");
    chuTrinhXoay(RotateRight, Slider_r, cc);
    chuTrinhXoay(RotateRight, Slider_r, 100); // Bù 100
  }
  else if (move == "D'") {
    Serial.println("Xoay D' (90 do nguoc)");
    chuTrinhXoay(RotateRight, Slider_r, nc);
  }
  else if (move == "D2") {
    Serial.println("Xoay D2 (180 do)");
    chuTrinhXoay(RotateRight, Slider_r, cc);  // Xoay R1
    chuTrinhXoay(RotateRight, Slider_r, cc);  // Xoay R2
    chuTrinhXoay(RotateRight, Slider_r, 100); // Xoay 100 bù thêm
  }
}