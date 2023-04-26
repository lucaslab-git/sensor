#include <Arduino.h>
//-----Sensor-Bibo-----//

#define S0RP A7
#define S1RP A6
#define S2RP A5
#define S3RP A4
#define S4RP A3
#define S5RP A2
#define S6RP A1
#define S7RP A0

#define S0LP A15
#define S1LP A14
#define S2LP A13
#define S3LP A12
#define S4LP A11
#define S5LP A10
#define S6LP A9
#define S7LP A8

int S0R = 0;
int S1R = 0;
int S2R = 0;
int S3R = 0;
int S4R = 0;
int S5R = 0;
int S6R = 0;
int S7R = 0;

int S0L = 0;
int S1L = 0;
int S2L = 0;
int S3L = 0;
int S4L = 0;
int S5L = 0;
int S6L = 0;
int S7L = 0;

int sensorvalues[15];
String valuecolor[15];

struct Farbe
{
  int untere_grenze;
  int obere_grenze;
  int referenzwert;
};

struct Farbe schwarz, weiss, gruen;

void berechnung_werte(int neuer_wert, Farbe color)
{
  color.referenzwert = (2 * color.referenzwert + neuer_wert) / 3;

  color.untere_grenze = color.referenzwert - 2;
  color.obere_grenze = color.referenzwert + 2;
}

void validierung_werte(Farbe color, String scolor)
{
  for (size_t i = 0; i < 15; i++)
  {

    if (sensorvalues[i] <= color.obere_grenze && sensorvalues[i] >= color.untere_grenze)
    {
      berechnung_werte(sensorvalues[i], color);
      valuecolor[i] = scolor;
    }
  }
}

void Ausgabe()
{
  /*for (size_t i = 0; i < 14; i++)
  {
    Serial.print("|" + String(sensorvalues[i]));
  }
  Serial.println("");*/

  for (size_t i = 0; i < 14; i++)
  {
    Serial.print("|" + String(valuecolor[i]));
  }
  Serial.println("");
}

void setup()
{
  Serial.begin(9600);

  weiss.referenzwert = analogRead(S0LP);
  weiss.untere_grenze = analogRead(S0LP) - 2;
  weiss.obere_grenze = analogRead(S0LP) + 2;
  Serial.println(weiss.referenzwert);
  delay(2000);
  schwarz.referenzwert = analogRead(S7LP);
  schwarz.untere_grenze = analogRead(S7LP) - 2;
  schwarz.obere_grenze = analogRead(S7LP) + 2;
  Serial.println(schwarz.referenzwert);
  for (size_t i = 0; i < 15; i++)
  {
    valuecolor[i] = "--";
  }

  delay(500);
}

void loop()
{
  sensorvalues[0] = analogRead(S0LP);
  sensorvalues[1] = analogRead(S1LP);
  sensorvalues[2] = analogRead(S2LP);
  sensorvalues[3] = analogRead(S3LP);
  sensorvalues[4] = analogRead(S4LP);
  sensorvalues[5] = analogRead(S5LP);
  sensorvalues[6] = analogRead(S6LP);
  sensorvalues[7] = analogRead(S7LP);

  sensorvalues[8] = analogRead(S0RP);
  sensorvalues[9] = analogRead(S1RP);
  sensorvalues[10] = analogRead(S2RP);
  sensorvalues[11] = analogRead(S3RP);
  sensorvalues[12] = analogRead(S4RP);
  sensorvalues[13] = analogRead(S5RP);
  sensorvalues[14] = analogRead(S6RP);
  sensorvalues[15] = analogRead(S7RP);

  validierung_werte(weiss, "--");
  validierung_werte(schwarz, "SS");
  Ausgabe();

  delay(500);
}
