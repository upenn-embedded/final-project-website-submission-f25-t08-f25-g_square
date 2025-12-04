/**************  Blynk Configuration  **************/
#define BLYNK_TEMPLATE_ID "TMPL2RxO5oMDJ"
#define BLYNK_TEMPLATE_NAME "ESE5190 FINAL PROJECT"
#define BLYNK_AUTH_TOKEN "6uFiIKoqjKAZu7xGze7QNy2dZKlWuA5r"

#define BLYNK_PRINT Serial

#include <Arduino.h>
#include "driver/i2s.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

/**************  WiFi  **************/
#define MY_SSID     "asdfghj"
#define MY_PASSWORD "12345678"

char auth[] = BLYNK_AUTH_TOKEN;

/**************  GPIO for Blynk virtual pins **************/
// V0 -> IO11, V1 -> IO10, V2 -> IO7, V3 -> IO3
const int PIN_V0 = 11;
const int PIN_V1 = 10;
const int PIN_V2 = 7;
const int PIN_V3 = 3;

/**************  ATmega FALL input signal  **************/
#define ATMEGA_SIGNAL_PIN 5   

bool fallNotifiedRecently = false;
unsigned long lastFallTime = 0;
const unsigned long FALL_COOLDOWN_MS = 10000;   // 10-second cooldown

/**************  I2S Microphone Related  **************/
// Using I2S0
#define I2S_PORT       I2S_NUM_0

// Wiring
#define PIN_I2S_BCLK   17      // SPH0645 BCLK -> GPIO17
#define PIN_I2S_LRCL   18      // SPH0645 LRCL/WS -> GPIO18
#define PIN_I2S_DOUT   14      // SPH0645 DOUT -> GPIO14

const int BUFFER_LEN = 256;
int32_t i2sBuffer[BUFFER_LEN];

// Debounce (single beat detection)
unsigned long lastBeatMs = 0;

// Noise baseline (tracking smoothed peak values)
float noiseFloor = 0.0f;

// Sound counting and activation window
bool active = false;               // Whether the system is currently in an active sound-detection window
unsigned long activeUntilMs = 0;   // Active window expiration timestamp
unsigned long soundCount = 0;      // Sound events detected within current window (up to 4)

// Active window duration (ms), e.g., 2000ms groups sound events together
const unsigned long ACTIVE_WINDOW_MS = 2000;

/**************  I2S Initialization  **************/
void setupI2SMic()
{
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = BUFFER_LEN,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = PIN_I2S_BCLK,
    .ws_io_num = PIN_I2S_LRCL,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = PIN_I2S_DOUT
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
  i2s_zero_dma_buffer(I2S_PORT);
}

/**************  Clap-triggered 50ms HIGH pulse  **************/
void pulseHigh50msByClap(int gpioPin, uint8_t vPin)
{
  // Send a 50ms HIGH pulse
  digitalWrite(gpioPin, HIGH);
  Blynk.virtualWrite(vPin, 1);

  Serial.printf("Clap -> GPIO%d HIGH pulse (50ms), V%d=1\n", gpioPin, vPin);

  delay(50);   // Hold HIGH for 50ms (small blocking, negligible impact)

  digitalWrite(gpioPin, LOW);
  Blynk.virtualWrite(vPin, 0);

  Serial.printf("GPIO%d LOW (pulse finished)\n", gpioPin);
}

/**************  Handle clap patterns and trigger V0–V3  **************/
void handleClapPattern(unsigned long count)
{
  if (count == 0) return;

  Serial.printf("Clap pattern finished: %lu times\n", count);

  switch (count) {
    case 1:
      // 1 clap → IO11 (V0)
      pulseHigh50msByClap(PIN_V0, V0);
      break;
    case 2:
      // 2 claps → IO10 (V1)
      pulseHigh50msByClap(PIN_V1, V1);
      break;
    case 3:
      // 3 claps → IO7 (V2)
      pulseHigh50msByClap(PIN_V2, V2);
      break;
    case 4:
      // 4 claps → IO3 (V3)
      pulseHigh50msByClap(PIN_V3, V3);
      break;
    default:
      // Ignore >4 claps
      break;
  }
}

/**************  Blynk Button Callbacks  **************/
BLYNK_WRITE(V0) {
  int v = param.asInt();
  digitalWrite(PIN_V0, v ? HIGH : LOW);
  Serial.printf("[V0] %s -> GPIO%d %s\n",
                v ? "PRESS" : "RELEASE",
                PIN_V0, v ? "HIGH" : "LOW");
}

BLYNK_WRITE(V1) {
  int v = param.asInt();
  digitalWrite(PIN_V1, v ? HIGH : LOW);
  Serial.printf("[V1] %s -> GPIO%d %s\n",
                v ? "PRESS" : "RELEASE",
                PIN_V1, v ? "HIGH" : "LOW");
}

BLYNK_WRITE(V2) {
  int v = param.asInt();
  digitalWrite(PIN_V2, v ? HIGH : LOW);
  Serial.printf("[V2] %s -> GPIO%d %s\n",
                v ? "PRESS" : "RELEASE",
                PIN_V2, v ? "HIGH" : "LOW");
}

BLYNK_WRITE(V3) {
  int v = param.asInt();
  digitalWrite(PIN_V3, v ? HIGH : LOW);
  Serial.printf("[V3] %s -> GPIO%d %s\n",
                v ? "PRESS" : "RELEASE",
                PIN_V3, v ? "HIGH" : "LOW");
}

/**************  ATmega FALL Detection  **************/
void checkAtmegaSignal() {
  int sig = digitalRead(ATMEGA_SIGNAL_PIN);

  if (sig == HIGH) {
    unsigned long now = millis();

    if (!fallNotifiedRecently || (now - lastFallTime > FALL_COOLDOWN_MS)) {
      Serial.println("FALL detected via ATMEGA_SIGNAL_PIN HIGH!");

      // Blynk notification
      Blynk.logEvent("epuppy_fall", "ePuppy has fallen!");

      fallNotifiedRecently = true;
      lastFallTime = now;
    }
  }
}

/**************  Process I2S Mic & Clap Logic (Non-blocking)  **************/
void processMic()
{
  size_t bytes_read = 0;

  // Non-blocking read: timeout = 0 (prevents blocking Blynk.run())
  esp_err_t res = i2s_read(
    I2S_PORT,
    (void *)i2sBuffer,
    sizeof(i2sBuffer),
    &bytes_read,
    0
  );

  if (!(res == ESP_OK && bytes_read > 0)) {
    return; // No data this cycle
  }

  int samples = bytes_read / sizeof(int32_t);

  // ---- 1. Find max absolute value of current audio batch ----
  int32_t maxAbs = 0;
  for (int i = 0; i < samples; i++) {
    int32_t raw = i2sBuffer[i];

    // Shift 32-bit SPH0645 data into usable amplitude range
    int32_t s = raw >> 14;
    if (s < 0) s = -s;

    if (s > maxAbs) {
      maxAbs = s;
    }
  }

  // ---- 2. Adaptive noise baseline ----
  const float NOISE_ALPHA = 0.980f;
  noiseFloor = NOISE_ALPHA * noiseFloor + (1.0f - NOISE_ALPHA) * (float)maxAbs;

  // ---- 3. Threshold: baseline + offset ----
  float threshold = noiseFloor + 4000.0f;

  // ---- 4. Debounce & detect “beat” events ----
  const unsigned long DEBOUNCE_MS = 150;
  unsigned long now = millis();
  int beat = 0;

  if ((float)maxAbs > threshold && (now - lastBeatMs) > DEBOUNCE_MS) {
    beat = 1;
    lastBeatMs = now;
  } else {
    beat = 0;
  }

  // ========= 5. Activation window & sound counting (max 4) =========

  // (1) If currently active, check timeout → end clap sequence
  if (active && now > activeUntilMs) {
    if (soundCount > 0) {
      handleClapPattern(soundCount);
    }
    active = false;
    soundCount = 0;
  }

  // (2) New beat detected
  if (beat == 1) {
    if (!active) {
      // Start new sound-detection window
      active = true;
      soundCount = 1;
      activeUntilMs = now + ACTIVE_WINDOW_MS;
    } else {
      // Already active
      if (now <= activeUntilMs) {
        if (soundCount < 4) {
          soundCount++;
        } else {
          soundCount = 1;  // Reset after 4 claps
        }
        activeUntilMs = now + ACTIVE_WINDOW_MS;  // Extend window
      } else {
        // Shouldn't happen often; safety reset
        soundCount = 1;
        activeUntilMs = now + ACTIVE_WINDOW_MS;
      }
    }
  }
}

/**************  setup  **************/
void setup() {
  Serial.begin(115200);
  delay(1000);

  // ---- Blynk GPIO initialization ----
  pinMode(PIN_V0, OUTPUT);
  pinMode(PIN_V1, OUTPUT);
  pinMode(PIN_V2, OUTPUT);
  pinMode(PIN_V3, OUTPUT);

  digitalWrite(PIN_V0, LOW);
  digitalWrite(PIN_V1, LOW);
  digitalWrite(PIN_V2, LOW);
  digitalWrite(PIN_V3, LOW);

  // ---- ATmega input ----
  pinMode(ATMEGA_SIGNAL_PIN, INPUT);

  // ---- I2S microphone ----
  setupI2SMic();

  // ---- Connect to Blynk ----
  Serial.println("Connecting to Blynk...");
  Blynk.begin(auth, MY_SSID, MY_PASSWORD);
  Serial.println("Connected to Blynk Cloud!");
}

/**************  loop  **************/
void loop() {
  Blynk.run();          // Handle Blynk events
  checkAtmegaSignal();  // Check ATmega FALL signal
  processMic();         // Process microphone & clap-detection logic
}
