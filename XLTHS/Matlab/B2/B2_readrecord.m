[y,Fs] = audioread('Recording.wav'); % Đọc audio từ file trả về dl mẫu y với tần số Fs
soundsc(y,Fs);
pause(5);
soundsc(y,44100);% Phát lại âm thanh với tần số 44100 Hz
pause(5); % Dừng 5s
soundsc(y,16000);
pause(5);
soundsc(y,8000);