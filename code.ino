#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ================= PINS ================= */
#define MQ2_PIN A0      // GAS
#define MQ135_PIN A1    // AIR QUALITY / NH3
#define MQ7_PIN A2      // CO

#define DHTPIN 2
#define DHTTYPE DHT22

#define GREEN_LED 9
#define RED_LED 8
#define BUZZER 10

/* ================= SAFE / DANGER LIMITS ================= */
#define MQ2_DANGER_PPM    350
#define MQ7_DANGER_PPM    300
#define MQ135_DANGER_PPM  600

#define TEMP_LIMIT 45
#define HUM_LIMIT  85

DHT dht(DHTPIN, DHTTYPE);

/* ================= STATE ================= */
unsigned long lastDHTRead = 0;

/* ================= LAST VALUES ================= */
float lastCO=-1, lastGas=-1, lastNH3=-1, lastTemp=-100, lastHum=-100;
bool firstLogDone = false;

/* ================= STABLE ADC READ ================= */
int readStableADC(int pin) {
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(pin);
    delay(2);
  }
  return sum / 10;
}

/* ================= SENSOR-WISE ADC → PPM ================= */
// MQ7 – CO
float mq7_to_ppm(int adc) {
  adc = constrain(adc, 100, 900);
  return map(adc, 100, 900, 0, 1000);
}

// MQ2 – Gas
float mq2_to_ppm(int adc) {
  adc = constrain(adc, 120, 850);
  return map(adc, 120, 850, 0, 600);
}

// MQ135 – Air Quality / NH3 (less sensitive now)
float mq135_to_ppm(int adc) {
  adc = constrain(adc, 150, 750);
  return map(adc, 150, 750, 0, 800);
}

void setup() {
  Serial.begin(9600);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.print("AIRGUARD-X");
  lcd.setCursor(0,1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {

  /* ===== READ MQ (STABLE) ===== */
  int coADC  = readStableADC(MQ7_PIN);
  int gasADC = readStableADC(MQ2_PIN);
  int nh3ADC = readStableADC(MQ135_PIN);

  float coPPM  = mq7_to_ppm(coADC);
  float gasPPM = mq2_to_ppm(gasADC);
  float nh3PPM = mq135_to_ppm(nh3ADC);

  /* ===== READ DHT ===== */
  float temperature = lastTemp;
  float humidity    = lastHum;

  if (millis() - lastDHTRead > 2000) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t) && !isnan(h)) {
      temperature = t;
      humidity = h;
    }
    lastDHTRead = millis();
  }

  /* ===== CHANGE CHECK ===== */
  bool valueChanged =
    abs(coPPM-lastCO)>=5 ||
    abs(gasPPM-lastGas)>=5 ||
    abs(nh3PPM-lastNH3)>=5 ||
    abs(temperature-lastTemp)>=0.5 ||
    abs(humidity-lastHum)>=1 ||
    !firstLogDone;

  if (!valueChanged) return;

  /* ===== DANGER LOGIC (EXACT AS REQUESTED) ===== */
  bool coDanger   = coPPM  >= MQ7_DANGER_PPM;
  bool gasDanger  = gasPPM >= MQ2_DANGER_PPM;
  bool nh3Danger  = nh3PPM >= MQ135_DANGER_PPM;
  bool tempDanger = temperature >= TEMP_LIMIT;
  bool humDanger  = humidity >= HUM_LIMIT;

  bool anyDanger = coDanger || gasDanger || nh3Danger || tempDanger || humDanger;

  /* ===== SERIAL LOG ===== */
  Serial.println("\n=========== AIRGUARD-X ===========");
  Serial.print("MQ2  (Gas) : "); Serial.print(gasPPM); Serial.println(" ppm");
  Serial.print("MQ7  (CO)  : "); Serial.print(coPPM);  Serial.println(" ppm");
  Serial.print("MQ135(AQ)  : "); Serial.print(nh3PPM); Serial.println(" ppm");
  Serial.print("Temp       : "); Serial.print(temperature); Serial.println(" C");
  Serial.print("Humidity   : "); Serial.print(humidity); Serial.println(" %");

  if (anyDanger) {
    Serial.print("🚨 DANGER → ");
    if (gasDanger) Serial.print("GAS ");
    if (coDanger)  Serial.print("CO ");
    if (nh3Danger) Serial.print("AIR ");
    if (tempDanger)Serial.print("TEMP ");
    if (humDanger) Serial.print("HUM ");
    Serial.println();
  } else {
    Serial.println("STATUS : SAFE (Environment Clear)");
  }

  /* ===== LCD ===== */
  lcd.clear();
  if (anyDanger) {
    lcd.print("DANGER DUE TO");
    lcd.setCursor(0,1);
    bool f=true;
    if (gasDanger){lcd.print("GAS");f=false;}
    if (coDanger){lcd.print(f?"CO":"+CO");f=false;}
    if (nh3Danger){lcd.print(f?"AIR":"+AIR");f=false;}
    if (tempDanger){lcd.print(f?"TEMP":"+TEMP");f=false;}
    if (humDanger){lcd.print(f?"HUM":"+HUM");}
  } else {
    lcd.print("AIR SAFE");
    lcd.setCursor(0,1);
    lcd.print("ENV CLEAR");
  }

  /* ===== ACTUATORS ===== */
  digitalWrite(RED_LED, anyDanger);
  digitalWrite(BUZZER, anyDanger);
  digitalWrite(GREEN_LED, !anyDanger);

  /* ===== UPDATE ===== */
  lastCO = coPPM;
  lastGas = gasPPM;
  lastNH3 = nh3PPM;
  lastTemp = temperature;
  lastHum = humidity;
  firstLogDone = true;
}
