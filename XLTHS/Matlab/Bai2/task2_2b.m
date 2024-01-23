filenames_a = {'NguyenAmHuanLuyen-16k/24FTL/a.wav'};
% Số chiều của FFT
list_N_FFT = [512, 1024, 2048];
frame_size = 27;
frame_shilft = -1;
% Đọc tệp âm thanh
[s, Fs] = audioread(filenames_a{1});
% Lấy thông tin về âm thanh từ hàm getVoiceCenter
[signal, index_ondinh, frame_size_ondinh] = getVoiceCenter2(s, Fs, frame_size, frame_shilft);
for index = 1:3
    time = frame_size / 1000;
    frame_length = Fs * time; % Độ dài 1 khung
    % Chia tín hiệu thành các khung với độ dài frame_length và không có sự chồng chéo
    frames = buffer(signal, frame_length, frame_shilft);
    % Lấy một khung từ frames
    single_frame = frames(1, :);
    disp(single_frame);
    % Áp dụng cửa sổ Hanning vào khung và thực hiện FFT
    single_frame_windowed = single_frame .* hann(frame_length);
    fft_result = get_fft_result(single_frame_windowed, list_N_FFT(index));
end
