recObj = audiorecorder(44100,16,1); % Tạo đối tượng audiorecorder
disp('Bắt đầu ghi âm'); % Hiển thị chuối
recordblocking(recObj,3); % Ghi âm trong 3 giây
disp('Kết thúc ghi âm');
y = getaudiodata(recObj); % Lấy dữ liệu âm thanh từ đối tượng
sound(y,44100);% Phát lại âm thanh với tần số 44100 Hz
pause(4);
sound(y,16000);
pause(4);
sound(y,8000);
