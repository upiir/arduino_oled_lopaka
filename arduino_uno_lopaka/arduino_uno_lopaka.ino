// simple project using Arduino UNO and 128x64 SSD1306 IIC OLED Display, created by upir, 2023
// youtube channel: https://www.youtube.com/upir_upir

// YOUTUBE VIDEO: https://youtu.be/Eyvzw_ujcS0
// WOKWI sketch: https://wokwi.com/projects/372481402319579137
// More videos with Arduino UNO and OLED screens: https://www.youtube.com/playlist?list=PLjQRaMdk7pBZ1UV3IL5ol8Qc7R9k-kwXA

// Links from the video:
// 128x64 SSD1306 OLED Display 1.54": https://s.click.aliexpress.com/e/_DCYdWXb 
// 128x64 SSD1306 OLED Display 0.96": https://s.click.aliexpress.com/e/_DCKdvnh
// 128x64 SSD1306 OLED Display 2.42": https://s.click.aliexpress.com/e/_DFdMoTh
// Arduino UNO: https://s.click.aliexpress.com/e/_AXDw1h

#include <Arduino.h>
#include <U8g2lib.h>

#include <Wire.h> // library requires for IIC communication

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // initialization for the used OLED display

// images from https://lopaka.app/
static const unsigned char image_Lock_7x8_bits[] U8X8_PROGMEM = {0x1c,0x22,0x22,0x7f,0x7f,0x77,0x7f,0x3e};
static const unsigned char image_Bluetooth_Idle_5x8_bits[] U8X8_PROGMEM = {0x04,0x0d,0x16,0x0c,0x0c,0x16,0x0d,0x04};
static const unsigned char image_Volup_8x6_bits[] U8X8_PROGMEM = {0x48,0x8c,0xaf,0xaf,0x8c,0x48};
static const unsigned char image_Alert_9x8_bits[] U8X8_PROGMEM = {0x10,0x00,0x38,0x00,0x28,0x00,0x6c,0x00,0x6c,0x00,0xfe,0x00,0xee,0x00,0xff,0x01};

int progress = 0;
char buffer[20];

void setup(void) {
  u8g2.begin(); // start the u8g2 library
}

void loop(void) {
  u8g2.clearBuffer();					// clear the internal memory

  // code from https://lopaka.app/
  u8g2.setBitmapMode(1);
  u8g2.drawFrame(12, 21, 104, 20);
  // progress bar fill
  u8g2.drawBox(14, 23, progress, 16);
  u8g2.setFont(u8g2_font_helvB08_tr);
  sprintf(buffer, "Progress: %d%%", progress);
  u8g2.drawStr(33, 53, buffer);
  
	u8g2.setFont(u8g2_font_haxrcorp4089_tr);
	u8g2.drawStr(0, 7, "Progress Bar Screen");
	u8g2.drawLine(0, 9, 127, 9);
	u8g2.drawXBMP( 100, 0, 7, 8, image_Lock_7x8_bits);
	u8g2.drawXBMP( 111, 0, 5, 8, image_Bluetooth_Idle_5x8_bits);
	u8g2.drawXBMP( 120, 1, 8, 6, image_Volup_8x6_bits);
	u8g2.drawXBMP( 22, 45, 9, 8, image_Alert_9x8_bits);


  u8g2.sendBuffer();					// transfer internal memory to the display
  //delay(1000);  // one second delay, but we are only displaying a static image, so it makes no difference

  progress = (progress + 1) % 101;
}
