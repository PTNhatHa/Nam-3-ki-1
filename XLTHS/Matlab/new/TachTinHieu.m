function TachTinHieu(s, Fs,frame_size, frame_shilft)
    % 1 frame = frame_length ms = frame_length/1000s
    time = frame_size/1000; 
    % Chia tín hiệu âm thanh thành các khung và tính STE cho mỗi khung
    frame_length = Fs*time; % Độ dài 1 khung
    frame = buffer(s, frame_length, frame_shilft);
    ste = sum(frame.^2, 1); % Tính tổng bình phương các pt trong mỗi cột của frame
    
    % Chuẩn hóa ste
    ste = ste/max(ste);
    % Lấy chỉ số các khung có ste > 0.1
    index = find(ste>0.1);
    % Lấy các khung tương ứng từ tín hiệu đầu vào
    frames = frame(:, index);
    % Nối các khung theo chiều ngang
    signal = horzcat(frames(:));

    % Vẽ đồ thị
    t = (1:length(s)) / Fs; % Thời gian ứng với mỗi mẫu
    frame_time = (1:round(length(frame)))*time; % Thời gian ứng với mỗi frame
    
    plot(t,s);
    hold on;
    plot(frame_time, ste, 'r', 'LineWidth', 1.5);
    xlabel('Thời gian (s)');
    ylabel('Biên độ');
    title('Signal & STE');
    xline((index(1)-1)*time, 'k', 'LineWidth', 1.5);
    xline(index(length(index))*time, 'k', 'LineWidth', 1.5);
    hold off;

end