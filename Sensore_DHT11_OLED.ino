#include "DHT.h"
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE, 6);

char str[10];

void drawTest(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 20, "Sensore temp/umi");
}

void setup() {
  Serial.begin(9600);
  Serial.println("Sensore temp/umi");

  dht.begin();
  u8g.firstPage();
  do {
    drawTest();
  } while ( u8g.nextPage() );
}

void loop() {

  delay(2000);
  
  float h = dht.readHumidity();

  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Impossibile leggere dati dal sensore di DHT!");
    return;
  }

  Serial.print("Umidita': ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");

  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_helvB08);

    u8g.drawStr( 0, 15, "Umidita':");
    u8g.drawStr( 80, 15, dtostrf(h, 5, 2, str));
    u8g.drawStr( 120, 15, "%");

    u8g.drawStr( 0, 45, "Temperatura:");
    u8g.drawStr( 80, 45, dtostrf(t, 5, 2, str));
    u8g.drawStr( 120, 45, "\260C");

  } while ( u8g.nextPage() );
}
