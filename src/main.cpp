#include <Arduino.h>


// Port für einzelne Sensoren
// Links nach Rechts (in Fahrtrichtung)
#define S0LP A0
#define S1LP A1
#define S2LP A2
#define S3LP A3
#define S4LP A4
#define S5LP A5
#define S6LP A6
#define S7LP A7

#define S0RP A8
#define S1RP A9
#define S2RP A10
#define S3RP A11
#define S4RP A12
#define S5RP A13
#define S6RP A14
#define S7RP A15

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


int sensorvalues[15]; //Für die Werte des einzelnen Sensors
String valuecolor[15]; //Für die Ausgabe und oder weiterverarbeitung

struct Farbe
{
  int untere_grenze;
  int obere_grenze;
  int referenzwert;
};

struct Farbe schwarz, weiss, gruen;


void berechnung_werte(int neuer_wert, Farbe color)
{
  //Der alte Referenzwert wird mehr gewichtet 
  color.referenzwert = (2 * color.referenzwert + neuer_wert) / 3;

  //Toleranz von jedem Sensor ist +-2
  color.untere_grenze = color.referenzwert - 2;
  color.obere_grenze = color.referenzwert + 2;
}

void validierung_werte(Farbe color, String scolor)
{
  //Für jeden Value
  for (size_t i = 0; i < 15; i++)
  {
    //Überprüfung ob Wert in Range liegt
    if (sensorvalues[i] <= color.obere_grenze && sensorvalues[i] >= color.untere_grenze)
    {
      //Grenz- und Toleranzwerte neu berechnen
      berechnung_werte(sensorvalues[i], color);
      valuecolor[i] = scolor; //Am besten color.aktuelleFarbe
    }
  }
}

void Ausgabe()
{
  /*Serial.print("Start: ");
  for (size_t i = 0; i < 16; i++)
  {
    Serial.print(String(sensorvalues[i]) + ",");
  }
  Serial.println("");*/

  for (size_t i = 0; i < 16; i++)
  {
    Serial.print("|" + String(valuecolor[i]));
  }
  Serial.println("");
}

void kal_weiss(){
  weiss.referenzwert = abs(analogRead(S0LP) - 2); // S0LP -> Sensorelement Links äußester Sensor
  weiss.untere_grenze = abs(analogRead(S0LP) - 2) - 2;
  weiss.obere_grenze = abs(analogRead(S0LP) - 2) + 2;
  Serial.println("Weiss kal: " + weiss.referenzwert);
}

void kal_schwarz(){
  schwarz.referenzwert = analogRead(S7LP); // S7LP -> Sensorelement Links mittiger Sensor
  schwarz.untere_grenze = analogRead(S7LP) - 2;
  schwarz.obere_grenze = analogRead(S7LP) + 2;
  Serial.println("Schwarz kal:" + schwarz.referenzwert);
}


void setup()
{
  Serial.begin(9600);

  //kalibrierung der Werte 
  kal_weiss();  
  delay(100);
  kal_schwarz();
  delay(1000);

  // Für schönere Ausgabe
  for (size_t i = 0; i < 15; i++) 
  {
    valuecolor[i] = "--";
  }

  delay(500);
}

void loop()
{
  //Einlesen der Werte 
  /*
  ,28,25,24,23,23,25,24,25,24,25,26,26,25,24
  ,27,26,23,22,24,25,24,25,25,25,25,26,25,24
  ,27,25,23,23,24,25,25,26,25,25,26,26,25,24
  ,27,25,24,22,24,25,25,26,25,25,25,26,25,23
  */
  sensorvalues[0] = abs(analogRead(S0LP) - 2);
  sensorvalues[1] = abs(analogRead(S1LP));
  sensorvalues[2] = abs(analogRead(S2LP) + 1);
  sensorvalues[3] = abs(analogRead(S3LP) + 2);
  sensorvalues[4] = abs(analogRead(S4LP) + 1);
  sensorvalues[5] = abs(analogRead(S5LP));
  sensorvalues[6] = abs(analogRead(S6LP));
  sensorvalues[7] = abs(analogRead(S7LP));

  sensorvalues[8] = abs(analogRead(S0RP));
  sensorvalues[9] = abs(analogRead(S1RP));
  sensorvalues[10] = abs(analogRead(S2RP));
  sensorvalues[11] = abs(analogRead(S3RP));
  sensorvalues[12] = abs(analogRead(S4RP) - 1);
  sensorvalues[13] = abs(analogRead(S5RP) - 1);
  sensorvalues[14] = abs(analogRead(S6RP));
  sensorvalues[15] = abs(analogRead(S7RP) + 4);

  validierung_werte(weiss, "--");
  validierung_werte(schwarz, "SS");

  Ausgabe();

  delay(50);
}
