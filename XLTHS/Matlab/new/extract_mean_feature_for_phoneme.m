function mean_feature_vector = extract_mean_feature_for_phoneme(filenames, N_FFT, M, frame_shilft)
    % Khởi tạo biến tổng để tính trung bình cộng của các vector đặc trưng
    sum_feature_vector = zeros(N_FFT, 1);
   
    % Duyệt qua từng file âm thanh
    for fileIdx = 1:length(filenames)
        % Đọc âm thanh từ file
        [s, Fs] = audioread(filenames{fileIdx});

        % Lấy thông tin về âm thanh từ hàm getVoiceCenter
        [index_ondinh, Mframe_ondinh] = getVoiceCenter2(s, Fs, M, frame_shilft);
        % [indexStart, Mframe] = getVoice(s, Fs, 30);
        % [index_ondinh, Mframe_ondinh] = getVoiceCenter(indexStart, Mframe);
        % Lấy đoạn tín hiệu tương ứng với các khung có ste > 0.3
        x = getVoiceFrame(s, Fs, M, index_ondinh, Mframe_ondinh, frame_shilft);

        % Trích xuất vector FFT cho M khung tín hiệu ổn định
        feature_vector = extract_feature(x, N_FFT, Fs, Mframe_ondinh, frame_shilft);

        % Cộng dồn vào biến tổng
        sum_feature_vector = sum_feature_vector + feature_vector;
    end

    % Tính trung bình cộng của các vector đặc trưng
    mean_feature_vector = sum_feature_vector / length(filenames);
end