filenames_a = {'NguyenAmHuanLuyen-16k/24FTL/a.wav'};
list_N_FFT = [512, 1024, 2048];
frame_size = 27;
frame_shilft = -1;
figure('Name', sprintf('Mean feature FFT plots for %s', filenames_a{1}));
title(sprintf(' (%s)', filenames_a{1}));
% Đọc tệp âm thanh
[s, Fs] = audioread(filenames_a{1});
% Lấy thông tin về âm thanh từ hàm getVoiceCenter
[signal, index_ondinh, frame_size_ondinh] = getVoiceCenter2(s, Fs, frame_size, frame_shilft);
% Trích xuất vector FFT cho M khung tín hiệu ổn định
for index = 1:3
    feature_vector = extract_feature(signal, list_N_FFT(index), Fs, frame_size_ondinh);
    % Vẽ biểu đồ
    subplot(3, 1, index);
    plot(1:length(feature_vector)/2, feature_vector(1:length(feature_vector)/2));
    title(sprintf('Mean feature FFT of NFFT = %d ', list_N_FFT(index)));
end