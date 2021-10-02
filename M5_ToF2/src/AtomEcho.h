#ifndef AtomEcho_H
#define AtomEcho_H

#define CONFIG_I2S_BCK_PIN      19
#define CONFIG_I2S_LRCK_PIN     33
#define CONFIG_I2S_DATA_PIN     22
#define CONFIG_I2S_DATA_IN_PIN  23

#define SPEAKER_I2S_NUMBER      I2S_NUM_0

#define MODE_MIC                0
#define MODE_SPK                1

class AtomEcho{
    int wav = 0;
public:
    void InitI2SSpeakerOrMic(int mode=MODE_MIC);
    //void playSound(void);
    void playSound(int sound_num);
};
#endif