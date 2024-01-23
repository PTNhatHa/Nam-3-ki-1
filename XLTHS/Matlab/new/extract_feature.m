function feature_vector = extract_feature(v, N_FFT, Fs, Mframe_ondinh, frame_shilft)
    % Chia tín hiệu thành các khung với độ dài N_FFT và không có sự chồng chéo
    frames = buffer(v, N_FFT, -frame_shilft);

    % Áp dụng cửa sổ Hanning vào từng khung và thực hiện FFT
    frames_windowed = frames .* hann(N_FFT);
    fft_results = get_fft_result(frames_windowed);

    % Ensure Mframe_ondinh is within the valid range
    Mframe_ondinh = min(Mframe_ondinh, size(fft_results, 2));

    % Lấy Mframe_ondinh vector FFT từ Mframe_ondinh khung ổn định
    fft_vectors = fft_results(:, 1:Mframe_ondinh);

    % Tính trung bình cộng của Mframe_ondinh vector FFT
    mean_fft = mean(abs(fft_vectors), 2);

    % Sử dụng trung bình cộng làm vector đặc trưng
    feature_vector = mean_fft;
end
