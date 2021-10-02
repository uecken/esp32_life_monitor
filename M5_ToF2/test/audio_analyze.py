
#======= 音声ファイル再生時からの立ち上がり時間を取得し、pistol.wav再生開始から音がなるまでの時間を測定 ==========

import sys
import scipy.io.wavfile
import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import find_peaks
 

##============ trigger =============
## https://watlab-blog.com/2019/05/02/trigger/#i
def trigger(data, Tlevel):
    data = data - Tlevel    #波形全体をトリガレベルでオフセット

    #位置情報 i と判定値 jを初期化
    i = 0
    j = True
 
    #ゼロクロス点探査Whileループ
    #ループ停止条件＝トリガを検出した場合と検出されなかった場合のどちらか
    while j == True:
 
        #最初のループはiを増分させるだけ
        if i == 0:
            i = i + 1
 
        #波形を全て探査した場合はjを強制的に判定値jをFalseにしてiに-1（未検出の意味）を代入
        elif i + 1 == len(data):
            j = False
            i = -1
        #前の値(i-1)と今の値(i)で符号を比較し判定値jに渡す。iを増分させる。
        else:
            j = np.sign(data[i-1]) == np.sign(data[i])
            i = i + 1
    return i



#======= 音声ファイル再生時からの立ち上がり時間を取得 ==========
#音声ファイル読み込み
args = sys.argv
wav_filename = args[1]
rate, data = scipy.io.wavfile.read(wav_filename)
 
 
#（振幅）の配列を作成
data = data / max(data)
 
##### 周波数成分を表示する #####
#縦軸：dataを高速フーリエ変換する（時間領域から周波数領域に変換する）
#fft_data = np.abs(np.fft.fft(data))    
#横軸：周波数の取得　　#np.fft.fftfreq(データ点数, サンプリング周期)
#freqList = np.fft.fftfreq(data.shape[0], d=1.0/rate)  
#データプロット
print(rate,max(data))
plt.plot(data)
#plt.xlim(0, 8000) #0～8000Hzまで表示
plt.savefig(wav_filename + ".png")
i = trigger(data, 0.5) * (1 / rate)
print(i)
