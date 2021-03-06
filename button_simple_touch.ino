#if 1

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 200
#define MAXPRESSURE 1000

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn, on_btn2, off_btn2, on_btn3, off_btn3, on_btn4, off_btn4;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup(void)
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(0);            //PORTRAIT
    tft.fillScreen(BLACK);
    on_btn.initButton(&tft,  60, 80, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
    off_btn.initButton(&tft, 180, 80, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);
    on_btn.drawButton(false);
    off_btn.drawButton(false);
    tft.fillRect(40, 10, 160, 40, RED);
    
    on_btn2.initButton(&tft,  60, 180, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
    off_btn2.initButton(&tft, 180, 180, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);
    on_btn2.drawButton(false);
    off_btn2.drawButton(false);
    tft.fillRect(40, 110, 160, 40, RED);

    on_btn3.initButton(&tft,  60, 280, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
    off_btn3.initButton(&tft, 180, 280, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);
    on_btn3.drawButton(false);
    off_btn3.drawButton(false);
    tft.fillRect(40, 210, 160, 40, RED);
    
    on_btn4.initButton(&tft,  60, 380, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
    off_btn4.initButton(&tft, 180, 380, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);
    on_btn4.drawButton(false);
    off_btn4.drawButton(false);
    tft.fillRect(40, 310, 160, 40, RED);
}

/* two buttons are quite simple
 */
void loop(void)
{
    bool down = Touch_getXY();
    on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
    off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
    if (on_btn.justReleased())
        on_btn.drawButton();
    if (off_btn.justReleased())
        off_btn.drawButton();
    if (on_btn.justPressed()) {
        on_btn.drawButton(true);
        tft.fillRect(40, 10, 160, 40, GREEN);
    }
    if (off_btn.justPressed()) {
        off_btn.drawButton(true);
        tft.fillRect(40, 10, 160, 40, RED);
    }

    on_btn2.press(down && on_btn2.contains(pixel_x, pixel_y));
    off_btn2.press(down && off_btn2.contains(pixel_x, pixel_y));
    if (on_btn2.justReleased())
        on_btn2.drawButton();
    if (off_btn2.justReleased())
        off_btn2.drawButton();
    if (on_btn2.justPressed()) {
        on_btn2.drawButton(true);
        tft.fillRect(40, 110, 160, 40, BLUE);
    }
    if (off_btn2.justPressed()) {
        off_btn2.drawButton(true);
        tft.fillRect(40, 110, 160, 40, RED);
    }

    on_btn3.press(down && on_btn3.contains(pixel_x, pixel_y));
    off_btn3.press(down && off_btn3.contains(pixel_x, pixel_y));
    if (on_btn3.justReleased())
        on_btn3.drawButton();
    if (off_btn3.justReleased())
        off_btn3.drawButton();
    if (on_btn3.justPressed()) {
        on_btn3.drawButton(true);
        tft.fillRect(40, 210, 160, 40, YELLOW);
    }
    if (off_btn3.justPressed()) {
        off_btn3.drawButton(true);
        tft.fillRect(40, 210, 160, 40, RED);
    }

    on_btn4.press(down && on_btn4.contains(pixel_x, pixel_y));
    off_btn4.press(down && off_btn4.contains(pixel_x, pixel_y));
    if (on_btn4.justReleased())
        on_btn4.drawButton();
    if (off_btn4.justReleased())
        off_btn4.drawButton();
    if (on_btn4.justPressed()) {
        on_btn4.drawButton(true);
        tft.fillRect(40, 310, 160, 40, CYAN);
    }
    if (off_btn4.justPressed()) {
        off_btn4.drawButton(true);
        tft.fillRect(40, 310, 160, 40, RED);
    }
}
#endif
