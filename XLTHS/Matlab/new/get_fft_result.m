function fft_result = get_fft_result(frame)
    N_FFT = size(frame, 1); % Số chiều của FFT
    fft_result = fft(frame, N_FFT); % Áp dụng FFT cho mỗi khung
end