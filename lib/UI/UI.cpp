#include "UI.h"
   
UI::UI() {
  this->tft.init();
  this->tft.setRotation(1);
  this->tft.fillScreen(TFT_BLACK);
  this->tft.setTextSize(2);
  this->tft.setTextColor(TFT_WHITE);
  this->tft.setCursor(0, 0);
  this->tft.setTextDatum(MC_DATUM);
  this->tft.setTextSize(1);

  if (TFT_BL > 0) { // TFT_BL has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
    pinMode(TFT_BL, OUTPUT); // Set backlight pin to output mode
    digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
  }
  this->tft.setSwapBytes(true);
  }
    
void 
UI::DrawBarcode(String barcode){
  this->tft.fillRect(130,10,100,40,TFT_BLACK);
  this->tft.setTextColor(TFT_WHITE);

  this->tft.setTextSize(1);
  this->tft.setCursor(130,10);      
  this->tft.print("BARCODE");

  this->tft.setTextSize(2);
  this->tft.setCursor(130,25);      
  this->tft.print(barcode);
}

void
UI::ShowText(int16_t x, int16_t y, String txt)
{
  this->tft.fillRect(x,y,txt.length() * 7 ,20,TFT_BLACK);
  this->tft.setTextColor(TFT_WHITE);

  this->tft.setTextSize(1);
  this->tft.setCursor(x,y);      
  this->tft.print(txt);

}

void 
UI::DrawIP(String ip){
  this->tft.drawRect(135,115,92,13,TFT_BLACK);
  this->tft.setTextColor(TFT_WHITE);
  this->tft.setTextSize(1);
  this->tft.setCursor(140,118);      
  this->tft.print(ip);
}

void
UI::DrawTrigger(String trg,String echoTrg){
  this->tft.fillRect(15,60,60,30,TFT_BLACK);
  this->tft.setTextColor(TFT_GREENYELLOW);

  this->tft.setTextSize(1);
  this->tft.setCursor(15,60);      
  this->tft.print("TRIGGER");

  this->tft.setTextColor(TFT_WHITE);
  this->tft.setTextSize(2);
  this->tft.setCursor(15,70);      
  this->tft.print(trg);

  this->tft.fillRect(15,90,60,35,TFT_BLACK);
  this->tft.setTextColor(TFT_GREENYELLOW);

  this->tft.setTextSize(1);
  this->tft.setCursor(15,100);      
  this->tft.print("ECHOTRG");

  this->tft.setTextColor(TFT_WHITE);
  this->tft.setTextSize(2);
  this->tft.setCursor(15,110);      
  this->tft.print(echoTrg);



}

void 
UI::DrawStation(String st){
  this->tft.drawRect(6,6,70,38,TFT_WHITE);
  this->tft.fillRect(10,10,60,30,TFT_BLACK);
  this->tft.setTextColor(TFT_WHITE);

  this->tft.setTextSize(1);
  this->tft.setCursor(15,10);      
  this->tft.print("STATION");

  this->tft.setTextSize(2);
  this->tft.setCursor(15,25);      
  this->tft.print(st);
}

void 
UI::DrawBox()
{
  this->tft.fillRect(90,10,30,30,TFT_ORANGE);
  this->tft.fillRect(90,10,15,30,TFT_YELLOW);
  this->tft.drawRect(86,6,38,38,TFT_WHITE);
}

void 
UI::DrawPanel()
{
  //tft.fillRect(10,60,195,95,TFT_CYAN);
  this->tft.drawRect(6,50,225,80,TFT_WHITE);
} 


void 
UI::DrawBatteryIcon(int x, int y, int level, int width, int height) 
{
  // Cancella l'area di disegno riempiendola con sfondo nero
  tft.fillRect(x, y, width + 2, height, TFT_BLACK); // Include anche il terminale della batteria

  // Disegna la cornice della batteria
  tft.drawRect(x, y, width, height, TFT_WHITE);
  tft.drawRect(x + width, y + height / 4, 2, height / 2, TFT_WHITE); // Terminale della batteria

  // Limita il livello tra 0 e 100 per evitare errori
  level = constrain(level, 0, 100);

  // Calcola la larghezza della barra interna come float per maggiore precisione
  int barWidth = (int)((width - 4) * (level / 100.0f)); // Usa 100.0f per assicurare una divisione float

  // Ottieni il colore interpolato in base al livello di carica
  uint16_t color = calculateBatteryColor(level);

  // Riempie la barra della batteria in base al livello e al colore calcolato
  tft.fillRect(x + 2, y + 2, barWidth, height - 4, color);
}



uint16_t
UI::calculateBatteryColor(int level) 
{
  uint8_t red, green, blue;

  if (level <= 20) {
    // Interpolazione tra Rosso (255, 0, 0) e Giallo (255, 255, 0)
    float ratio = level / 20.0;
    red = 255;
    green = 255 * ratio;
    blue = 0;
  } else if (level <= 60) {
    // Interpolazione tra Giallo (255, 255, 0) e Verde (0, 255, 0)
    float ratio = (level - 20) / 40.0;
    red = 255 * (1 - ratio);
    green = 255;
    blue = 0;
  } else {
    // Interpolazione tra Verde (0, 255, 0) e Verde Scuro (0, 128, 0) per variare leggermente
    float ratio = (level - 60) / 40.0;
    red = 0;
    green = 255 * (1 - 0.5 * ratio);  // Diminuire la componente verde gradualmente
    blue = 0;
  }

  // Converti RGB a colore a 16 bit
  return tft.color565(red, green, blue);
}

