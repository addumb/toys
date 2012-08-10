import numpy as np
import os
import pyaudio
import struct
import time

p = pyaudio.PyAudio()
samplerate = 44100
scale = 75
exponent = 5
channels = 1
chunk = 2**11
MAX = 0

def get_mic_stream():
    devinfo = p.get_default_input_device_info()
    micindex = devinfo['index']
    stream = p.open(
        format = pyaudio.paInt16,
        channels = channels,
        rate = samplerate,
        input = True,
        input_device_index = micindex,
        frames_per_buffer = chunk
    )
    return stream

# looks like http://julip.co/2012/05/arduino-python-soundlight-spectrum/ will help :)

def fftify(raw, numbuckets = 6):
    ''' uses up-top chunk and samplerate '''
    fmt = "%dH" % (len(data)/2)
    data2 = struct.unpack(fmt, data)
    data2 = np.array(data2, dtype='h')

    four = np.fft.fft(data2)
    ffty = np.abs(four[0:len(four)/2])/1000
    ffty1 = ffty[:len(ffty)/2]
    ffty2 = ffty[len(ffty)/2::] + 2
    #wtf?!
    ffty2 = ffty2[::-1]
    ffty = ffty1 + ffty2
    ffty = np.log(ffty) - 1

    #why the hell am I taking off the front and end four freqs?
    four = list(ffty)[4:-4]
    #and then cutting it in half?
    four = four[:len(four)/2]

    size = len(four)

    #and then I discretize it into 6 pieces because that guy has 6 LEDs
    levels = [sum(four[i:(i+size/numbuckets)]) for i in xrange(0,size, size/numbuckets)][:numbuckets]

    return levels

if __name__ == '__main__':
    s = get_mic_stream()
    while True:
        data = s.read(chunk)
        levels = fftify(data, 20)
        os.system('clear')
        for level in levels:
            level = max(min(level / scale, 1.0), 0.0)
            level = level ** exponent
            level = int(level * 200)
            print "*" * level
