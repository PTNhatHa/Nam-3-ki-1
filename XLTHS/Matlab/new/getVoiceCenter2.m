function [signal, Mframe_ondinh] = getVoiceCenter2(s, Fs,frame_size, frame_shilft)
    % 1 frame = frame_length ms = frame_length/1000s
    time = frame_size/1000; 
    % Chia tín hiệu âm thanh thành các khung và tính STE cho mỗi khung
    frame_length = Fs*time; % Độ dài 1 khung
    frame = buffer(s, frame_length, frame_shilft);
    ste = sum(frame.^2, 1); % Tính tổng bình phương các pt trong mỗi cột của frame
    
    % Chuẩn hóa ste
    ste = ste/max(ste);
    % Lấy chỉ số các khung có ste > 0.55
    index = find(ste>0.55);
    % Lấy các khung tương ứng từ tín hiệu đầu vào
    frames = frame(:, index);
    % Nối các khung theo chiều ngang
    signal = horzcat(frames(:));
    Mframe_ondinh = length(index);
end