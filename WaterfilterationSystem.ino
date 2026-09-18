// --------- تعريف الحساسات ---------
#define TDS_SENSOR_PIN A3
#define PH_SENSOR_PIN A2

// --------- تعريف ريلايات الفالفات ---------
#define RELAY1_PIN A5  // فالف 1
#define RELAY2_PIN A4  // فالف 2

// --------- تعريف المضخات ---------
#define PUMP1 1  // مضخة 1
#define PUMP2 2  // مضخة 2
#define PUMP3 3  // مضخة 3

// --------- متغيرات TDS و pH ---------
float tdsValue = 0;
int analogTDS = 0;
float voltageTDS = 0;

float phValue = 0;
int analogPH = 0;
float voltagePH = 0;

void setup() {
  Serial.begin(9600);

  // إعداد الفالفات
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);

  // إعداد المضخات
  pinMode(PUMP1, OUTPUT);
  pinMode(PUMP2, OUTPUT);
  pinMode(PUMP3, OUTPUT);

  // -------- قراءة الحساسات --------
  analogTDS = analogRead(TDS_SENSOR_PIN);
  voltageTDS = analogTDS * (5.0 / 1023.0);
  tdsValue = (133.42 * voltageTDS * voltageTDS * voltageTDS 
              - 255.86 * voltageTDS * voltageTDS 
              + 857.39 * voltageTDS) * 0.5;

  analogPH = analogRead(PH_SENSOR_PIN);
  voltagePH = analogPH * (5.0 / 1023.0);
  phValue = 3.5 * voltagePH;

  Serial.print("TDS Value (ppm): ");
  Serial.print(tdsValue);
  Serial.print(" | pH Value: ");
  Serial.println(phValue);

  // -------- 1. تشغيل فالف1 + مضخة1 مع بعض --------
  digitalWrite(RELAY1_PIN, HIGH); // فالف 1
  digitalWrite(PUMP1, HIGH);      // مضخة 1
  delay(37600);                   // 37.6 ثانية
  digitalWrite(PUMP1, LOW);
  digitalWrite(RELAY1_PIN, LOW);

  // -------- 2. انتظار 5 دقائق --------
  delay(300000); // 5 دقائق

  // -------- 3. تشغيل مضخة2 --------
  digitalWrite(PUMP2, HIGH);
  delay(37500);  // 37.5 ثانية
  digitalWrite(PUMP2, LOW);

  // -------- 4. انتظار 6.6 دقيقة --------
  delay(396000); // 6.6 دقيقة

  // -------- 5. تشغيل فالف2 + مضخة3 مع بعض --------
  digitalWrite(RELAY2_PIN, HIGH);  // فالف2
  digitalWrite(PUMP3, HIGH);       // مضخة3
  delay(37600);                    // 37.6 ثانية
  digitalWrite(PUMP3, LOW);
  digitalWrite(RELAY2_PIN, LOW);

  // -------- 6. انتظار 10 ثواني --------
  delay(10000);

  // نهاية
  while (true);
}

void loop() {
  // فاضي
}