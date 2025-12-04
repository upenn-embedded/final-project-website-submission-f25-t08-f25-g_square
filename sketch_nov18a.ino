/**************  Blynk 配置  **************/
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

/**************  Blynk 相关 GPIO  **************/
// V0 -> IO11, V1 -> IO10, V2 -> IO7, V3 -> IO3
const int PIN_V0 = 11;
const int PIN_V1 = 10;
const int PIN_V2 = 7;
const int PIN_V3 = 3;

/**************  ATmega FALL 输入信号  **************/
#define ATMEGA_SIGNAL_PIN 5   

bool fallNotifiedRecently = false;
unsigned long lastFallTime = 0;
const unsigned long FALL_COOLDOWN_MS = 10000;   // 10 秒冷却时间

/**************  I2S 麦克风相关  **************/
// 使用 I2S0
#define I2S_PORT       I2S_NUM_0

// 接线（按你的实际板子改）
#define PIN_I2S_BCLK   17      // SPH0645 BCLK -> GPIO17
#define PIN_I2S_LRCL   18      // SPH0645 LRCL/WS -> GPIO18
#define PIN_I2S_DOUT   14      // SPH0645 DOUT -> GPIO14

const int BUFFER_LEN = 256;
int32_t i2sBuffer[BUFFER_LEN];

// 防抖（单次敲击）
unsigned long lastBeatMs = 0;

// 噪声基线（用峰值的平滑值）
float noiseFloor = 0.0f;

// 声音计数与激活窗口
bool active = false;               // 当前是否处于激活状态
unsigned long activeUntilMs = 0;   // 激活状态持续到的时间点
unsigned long soundCount = 0;      // 在当前激活期间检测到的声音次数（最多 4）

// 激活窗口长度（毫秒），比如 2000ms 内有声音就算同一轮
const unsigned long ACTIVE_WINDOW_MS = 2000;


/**************  I2S 初始化  **************/
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

/**************  拍手触发的 50ms 高电平脉冲  **************/
void pulseHigh50msByClap(int gpioPin, uint8_t vPin)
{
  // 发一个 50ms 的高电平脉冲
  digitalWrite(gpioPin, HIGH);
  Blynk.virtualWrite(vPin, 1);

  Serial.printf("Clap -> GPIO%d HIGH pulse (50ms), V%d=1\n", gpioPin, vPin);

  delay(50);   // 维持 50ms 高电平（会短暂阻塞，但影响很小）

  digitalWrite(gpioPin, LOW);
  Blynk.virtualWrite(vPin, 0);

  Serial.printf("GPIO%d LOW (pulse finished)\n", gpioPin);
}

/**************  根据拍次数触发 V0~V3 对应的 IO  **************/
void handleClapPattern(unsigned long count)
{
  if (count == 0) return;

  Serial.printf("Clap pattern finished: %lu times\n", count);

  switch (count) {
    case 1:
      // 拍一次 -> IO11 (V0) 输出 50ms 高脉冲
      pulseHigh50msByClap(PIN_V0, V0);
      break;
    case 2:
      // 拍两次 -> IO10 (V1) 输出 50ms 高脉冲
      pulseHigh50msByClap(PIN_V1, V1);
      break;
    case 3:
      // 拍三次 -> IO7 (V2) 输出 50ms 高脉冲
      pulseHigh50msByClap(PIN_V2, V2);
      break;
    case 4:
      // 拍四次 -> IO3 (V3) 输出 50ms 高脉冲
      pulseHigh50msByClap(PIN_V3, V3);
      break;
    default:
      // >4 的情况目前忽略
      break;
  }
}

/**************  Blynk 按钮回调  **************/
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

/**************  ATmega FALL 检测  **************/
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

/**************  处理 I2S 麦克风 & 拍手逻辑（非阻塞）  **************/
void processMic()
{
  size_t bytes_read = 0;

  // 非阻塞读取：timeout = 0，避免卡住 Blynk.run()
  esp_err_t res = i2s_read(
    I2S_PORT,
    (void *)i2sBuffer,
    sizeof(i2sBuffer),
    &bytes_read,
    0   // 不等待
  );

  if (!(res == ESP_OK && bytes_read > 0)) {
    return; // 本轮没有数据，直接返回
  }

  int samples = bytes_read / sizeof(int32_t);

  // ---- 1. 本批的最大绝对值作为峰值 ----
  int32_t maxAbs = 0;
  for (int i = 0; i < samples; i++) {
    int32_t raw = i2sBuffer[i];

    // 把 SPH0645 的 32bit 数据压到合理范围
    int32_t s = raw >> 14;
    if (s < 0) s = -s;

    if (s > maxAbs) {
      maxAbs = s;
    }
  }

  // ---- 2. 自适应噪声基线 ----
  const float NOISE_ALPHA = 0.980f;   // 越接近1，变化越慢
  noiseFloor = NOISE_ALPHA * noiseFloor + (1.0f - NOISE_ALPHA) * (float)maxAbs;

  // ---- 3. 阈值：基线 + 偏移 ----
  float threshold = noiseFloor + 4000.0f;

  // ---- 4. 防抖：检测单个敲击（beat） ----
  const unsigned long DEBOUNCE_MS = 150;
  unsigned long now = millis();
  int beat = 0;

  if ((float)maxAbs > threshold && (now - lastBeatMs) > DEBOUNCE_MS) {
    beat = 1;
    lastBeatMs = now;
  } else {
    beat = 0;
  }

  // ========= 5. 激活逻辑 + 声音计数（最多 4 次） =========

  // （1）如果当前处于激活状态，检查是否超时 -> 一轮拍手结束
  if (active && now > activeUntilMs) {
    // 窗口结束 -> 认为一轮拍手结束，处理本轮拍数
    if (soundCount > 0) {
      handleClapPattern(soundCount);
    }
    // 然后重置
    active = false;
    soundCount = 0;
  }

  // （2）本次有检测到新的“有效声音事件”（beat == 1）
  if (beat == 1) {
    if (!active) {
      // 之前是未激活状态 -> 现在开始一次新的“声音检测窗口”
      active = true;
      soundCount = 1;                   // 新一轮从 1 开始
      activeUntilMs = now + ACTIVE_WINDOW_MS;
    } else {
      // 本来就处于激活状态
      if (now <= activeUntilMs) {
        // 仍然在窗口内
        if (soundCount < 4) {
          // 未到 4 次，继续自增
          soundCount++;
        } else {
          // 已经是 4 次，再来一次就重新从 1 开始计数
          soundCount = 1;
        }
        // 每次有声音，都延长窗口
        activeUntilMs = now + ACTIVE_WINDOW_MS;
      } else {
        // 虽然 active == true，但窗口超时（保险分支），重新开始一轮
        soundCount = 1;
        activeUntilMs = now + ACTIVE_WINDOW_MS;
      }
    }
  }

  // 如需调试：
  /*
  Serial.print("max=");
  Serial.print(maxAbs);
  Serial.print(" floor=");
  Serial.print(noiseFloor);
  Serial.print(" thr=");
  Serial.print(threshold);
  Serial.print(" beat=");
  Serial.print(beat);
  Serial.print(" active=");
  Serial.print(active ? 1 : 0);
  Serial.print(" count=");
  Serial.println(soundCount);
  */
}

/**************  setup  **************/
void setup() {
  Serial.begin(115200);
  delay(1000);

  // ---- Blynk GPIO 初始化 ----
  pinMode(PIN_V0, OUTPUT);
  pinMode(PIN_V1, OUTPUT);
  pinMode(PIN_V2, OUTPUT);
  pinMode(PIN_V3, OUTPUT);

  digitalWrite(PIN_V0, LOW);
  digitalWrite(PIN_V1, LOW);
  digitalWrite(PIN_V2, LOW);
  digitalWrite(PIN_V3, LOW);

  // ---- ATmega 输入 ----
  pinMode(ATMEGA_SIGNAL_PIN, INPUT);

  // ---- I2S 麦克风 ----
  setupI2SMic();

  // ---- 连接到 Blynk ----
  Serial.println("Connecting to Blynk...");
  Blynk.begin(auth, MY_SSID, MY_PASSWORD);
  Serial.println("Connected to Blynk Cloud!");
}

/**************  loop  **************/
void loop() {
  Blynk.run();          // 处理 Blynk
  checkAtmegaSignal();  // 检测 ATmega FALL 信号
  processMic();         // 处理麦克风 & 拍手逻辑
}