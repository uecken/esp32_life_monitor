/*Press button to record,released button to playback*/
// https://github.com/m5stack/M5-ProductExampleCodes/blob/master/Core/Atom/AtomEcho/Arduino/Repeater/Repeater.ino

#include "AtomEcho.h"
#include <M5Atom.h>
#include <driver/i2s.h> //After read M5Atom.h read driver/i2s without avoiding compile // error: #error "include FreeRTOS.h"
#include "wav_on_your_mark.h"
#include "wav_set.h"
//#include "wav_pistol.h" 
//#include "wav_pistol_100ms.h"
#include "wav_pistol_monoral_faststart_monoral.h" 

// on your mark https://commons.nicovideo.jp/material/nc141161
// set https://commons.nicovideo.jp/material/nc141162
// Pistol https://commons.nicovideo.jp/material/nc2572  1

//const unsigned char *wavList[] = {wav_on_your_mark, wav_set, wav_pistol};
//const size_t wavSize[] = {sizeof(wav_on_your_mark), sizeof(wav_set), sizeof(wav_pistol)};
const unsigned char *wavList[] = {wav_on_your_mark, wav_set, pistol_monoral_faststart_monoral};
const size_t wavSize[] = {sizeof(wav_on_your_mark), sizeof(wav_set), sizeof(pistol_monoral_faststart_monoral)};

int wav = 0;

void AtomEcho::InitI2SSpeakerOrMic(int mode)
{
  esp_err_t err = ESP_OK;

  i2s_driver_uninstall(SPEAKER_I2S_NUMBER);
  i2s_config_t i2s_config = {
    .mode                 = (i2s_mode_t)(I2S_MODE_MASTER),
    .sample_rate          = 16000,
    .bits_per_sample      = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format       = I2S_CHANNEL_FMT_ALL_RIGHT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count        = 6,
    .dma_buf_len          = 60,
    .use_apll             = false,
    .tx_desc_auto_clear   = true,
    .fixed_mclk           = 0
  };
  if (mode == MODE_MIC)
  {
    i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM);
  }
  else
  {
    i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
  }

  err += i2s_driver_install(SPEAKER_I2S_NUMBER, &i2s_config, 0, NULL);

  i2s_pin_config_t tx_pin_config = {
    .bck_io_num           = CONFIG_I2S_BCK_PIN,
    .ws_io_num            = CONFIG_I2S_LRCK_PIN,
    .data_out_num         = CONFIG_I2S_DATA_PIN,
    .data_in_num          = CONFIG_I2S_DATA_IN_PIN,
  };
  err += i2s_set_pin(SPEAKER_I2S_NUMBER, &tx_pin_config);

  if (mode != MODE_MIC) {
    err += i2s_set_clk(SPEAKER_I2S_NUMBER, 16000, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
  }

  i2s_zero_dma_buffer(SPEAKER_I2S_NUMBER);
}





#ifdef false
void setup() {
  M5.begin(true, false, true);
  delay(50);
  Serial.println();
  M5.dis.drawpix(0, CRGB(128, 128, 0));
  InitI2SSpeakerOrMic(MODE_MIC);
  delay(2000);
}

void loop() {
  if (M5.Btn.isPressed())
  {
    size_t bytes_written;

    M5.dis.drawpix(0, CRGB(0, 128, 0));

    InitI2SSpeakerOrMic(MODE_SPK);

    // Random Play
    wav = (wav+1) % 3;

    // Write Speaker
    i2s_write(SPEAKER_I2S_NUMBER, wavList[wav], wavSize[wav], &bytes_written, portMAX_DELAY);
    i2s_zero_dma_buffer(SPEAKER_I2S_NUMBER);

    // Set Mic Mode
    InitI2SSpeakerOrMic(MODE_MIC);

    M5.dis.drawpix(0, CRGB(128, 128, 0));
  }

  M5.update();
}
#endif



void AtomEcho::playSound(int sound_num){
    size_t bytes_written;

    InitI2SSpeakerOrMic(MODE_SPK);
    Serial.print("---play sound---");

    // Random Play
    wav = sound_num; //0 or 1 or 2

    // Write Speaker
    i2s_write(SPEAKER_I2S_NUMBER, wavList[wav], wavSize[wav], &bytes_written, portMAX_DELAY);
    i2s_zero_dma_buffer(SPEAKER_I2S_NUMBER);

    // Set Mic Mode
    InitI2SSpeakerOrMic(MODE_MIC);
}
