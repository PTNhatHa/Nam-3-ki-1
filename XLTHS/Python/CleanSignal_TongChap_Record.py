import wave
import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import convolve

with wave.open('FHU_RE_005.wav', 'rb') as wav_file:
    # Lấy tốc độ khung của tệp âm thanh
    frame_rate = wav_file.getframerate()
    # Lấy số khung trong tệp âm thanh
    num_frames = wav_file.getnframes()
    # Đọc tất cả các khung từ tệp âm thanh => dùng để XLTHS
    frames = wav_file.readframes(num_frames)
    # Convert the frames to integers
    samples = np.frombuffer(frames, dtype=np.int16)

# Create an array of indices for the x-axis
x_axis = np.arange(num_frames)

# Plot the samples against the x-axis
plt.subplot(4,1,1)
plt.plot(x_axis, samples)

# Set the title and labels for the plot
plt.title('Waveform of FHU_RE_005.wav')
plt.xlabel('Sample Index')
plt.ylabel('Amplitude')

L = num_frames
n = np.arange(L)
#Nhiễu Gauss
A = 0.5 #công suất nhiễu
d = A*np.random.randn(L)
#noisy signal
x = samples + d

hNQ = np.ones(3)/3
y2 = convolve(x, hNQ, mode='same')

plt.subplot(4,1,3)
plt.plot(n,y2)
plt.title('3-points smoothed y2[n]')
plt.show()