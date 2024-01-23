% Đọc tín hiệu âm thanh
[x, fs] = audioread('signals/NguyenAmHuanLuyen-16k/23MTL/a.wav');
[signal, index, frame_size_ondinh] = getVoiceCenter2(x, fs, 27, 0);

% Tạo spectrogram của tín hiệu đã xử lý
figure;
spectrogram(x, 5*10^(-3)*fs, 3*10^(-3)*fs, 1024, fs, 'yaxis');
title('Spectrogram of Processed Signal');
ylabel('Frequency (Hz)');
xlabel('Time (s)');
figure;
spectrogram(signal, 5*10^(-3)*fs, 3*10^(-3)*fs, 1024, fs, 'yaxis');
title('Spectrogram of Processed Signal');
ylabel('Frequency (Hz)');
xlabel('Time (s)');