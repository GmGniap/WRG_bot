
#include <Arduino.h>
#include <ATX2.h>	// ATX2 Board
                         
#include <PS2X_lib.h>                            // เรียกใช้งานไลบรารีสำหรับ PS2 Controller

#define PS2_DAT        24                        // กำหนดขา Data    เป็นขา 16
#define PS2_CMD        25                        // กำหนดขา Command เป็นขา 17
#define PS2_SEL        26                        // กำหนดขา Select  เป็นขา 18
#define PS2_CLK        27                        // กำหนดขา Clock   เป็นขา 19

PS2X ps2x;                                       // ประกาศตัวแปรสำหรับ PS2 Controller

void setup()
{
  delay(1000);                                   // หน่วงเวลา 1 วินาทีเพื่อรอให้บอร์ดพร้อมทำงาน
  glcdClear();                                   // เคลียร์ภาพทั้งหมดบนหน้าจอแสดงผล
  glcdMode(1);                                   // กำหนดให้หน้าจอแสดงผลเป็นแนวนอน
  setTextSize(2);                                // กำหนดขนาดตัวหนังสือ
    
  glcd(0, 0, "Connecting");                      // แสดงข้อความเพื่อให้รู้ว่ากำลังทำการเชื่อมต่อกับ PS2 Controller
      
  while(true)                                    // วนการทำงานเพื่อรอการเชื่อมต่อกับ PS2 Controller
  {
    // กำหนดขาที่จะเชื่อมต่กับ PS2 Controller โดยมีการเก็บค่าที่ส่งกลับมาเป็น Integer เพื่อรู้ได้ว่าเชื่อมต่อได้หรือไม่
    int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
  
    if(error == 0)                               // กรณีที่เชื่อมต่อได้ ไม่มีปัญหาอะไร (Error = 0)
    {
      glcd(0, 0, "OK           ");               // แสดงข้อความว่าเชื่อมต่อกับ PS2 Controller เรียบร้อยแล้ว
      delay(1000);                               // หน่วงเวลา 1 วินาที
      glcdClear();                               // เคลียร์ภาพทั้งหมดบนหน้าจอแสดงผล
      break;                                     // ออกจาก while(true)
    } 
    delay(500);                                  // หน่วงเวลา 500 มิลลิวินาทีเพื่อรอการเชื่อมต่อครั้งต่อไปในกรณีที่เชื่อมต่อไม่สำเร็จ
  }
}

void loop()
{
  ps2x.read_gamepad(false, false);               // อ่านข้อมูลจาก PS2 Controller
  
  if(ps2x.Button(PSB_CIRCLE))                    // ถ้าปุ่มวงกลมถูกกด
    glcd(1, 1, "Circle  ");                      // แสดงข้อความว่า Circle บนหน้าจอ
  else if(ps2x.Button(PSB_CROSS))                // ถ้าปุ่มกากบาทถูกกด
    glcd(1, 1, "Cross   ");                      // แสดงข้อความว่า Cross บนหน้าจอ
  else if(ps2x.Button(PSB_SQUARE))               // ถ้าปุ่มสี่เหลี่ยมถูกกด
    glcd(1, 1, "Square  ");                      // แสดงข้อความว่า Square บนหน้าจอ
  else if(ps2x.Button(PSB_TRIANGLE))             // ถ้าปุ่มสามเหลี่ยมถูกกด
    glcd(1, 1, "Triangle");                      // แสดงข้อความว่า Triangle บนหน้าจอ
  else if(ps2x.Button(PSB_L1))                   // ถ้าปุ่ม L1 ถูกกด
    glcd(1, 1, "L1      ");                      // แสดงข้อความว่า L1 บนหน้าจอ
  else if(ps2x.Button(PSB_L2))                   // ถ้าปุ่ม L2 ถูกกด
    glcd(1, 1, "L2      ");                      // แสดงข้อความว่า L2 บนหน้าจอ
  else if(ps2x.Button(PSB_L3))                   // ถ้าปุ่ม L3 ถูกกด
    glcd(1, 1, "L3      ");                      // แสดงข้อความว่า L3 บนหน้าจอ
  else if(ps2x.Button(PSB_R1))                   // ถ้าปุ่ม R1 ถูกกด
    glcd(1, 1, "R1      ");                      // แสดงข้อความว่า R1 บนหน้าจอ
  else if(ps2x.Button(PSB_R2))                   // ถ้าปุ่ม R2 ถูกกด
    glcd(1, 1, "R2      ");                      // แสดงข้อความว่า R2 บนหน้าจอ
  else if(ps2x.Button(PSB_R3))                   // ถ้าปุ่ม R3 ถูกกด
    glcd(1, 1, "R3      ");                      // แสดงข้อความว่า R3 บนหน้าจอ
  else if(ps2x.Button(PSB_START))                // ถ้าปุ่ม Start ถูกกด
    glcd(1, 1, "Start   ");                      // แสดงข้อความว่า Start บนหน้าจอ
  else if(ps2x.Button(PSB_SELECT))               // ถ้าปุ่ม Select ถูกกด
    glcd(1, 1, "Select  ");                      // แสดงข้อความว่า Select บนหน้าจอ
  else if(ps2x.Button(PSB_PAD_UP))               // ถ้าปุ่ม Up ถูกกด
    glcd(1, 1, "Up      ");                      // แสดงข้อความว่า Up บนหน้าจอ
  else if(ps2x.Button(PSB_PAD_DOWN))             // ถ้าปุ่ม Down ถูกกด
    glcd(1, 1, "Down    ");                      // แสดงข้อความว่า Down บนหน้าจอ
  else if(ps2x.Button(PSB_PAD_LEFT))             // ถ้าปุ่ม Left ถูกกด
    glcd(1, 1, "Left    ");                      // แสดงข้อความว่า Left บนหน้าจอ
  else if(ps2x.Button(PSB_PAD_RIGHT))            // ถ้าปุ่ม Right ถูกกด
    glcd(1, 1, "Right   ");                      // แสดงข้อความว่า Right บนหน้าจอ
  else                                           // ถ้าไม่มีปุ่มใดๆถูกกด
    glcd(1, 1, "        ");                      // ลบข้อความที่แสดงอยู่ออก
    
  delay(50);                                     // หน่วงเวลา 50 มิลลิวินาที
}
