#ifndef UI_H
#define UI_H
#include <TFT_eSPI.h> 
#include <SPI.h>


class UI {
  private:
    TFT_eSPI tft = TFT_eSPI(135, 240); 
  public:
    UI();
    
    void DrawBarcode(String barcode);
    void DrawStation(String st);
    void DrawTrigger(String trg,String echoTrg);
    void DrawBox();
    void DrawPanel();
    void DrawIP(String ip);
    void ShowText(int16_t x, int16_t y, String txt);
    void DrawBatteryIcon(int x, int y, int level, int width = 24, int height = 10);
    uint16_t calculateBatteryColor(int level);
    };

    #endif