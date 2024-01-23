function TachTinHieu(filename, frame_size)
    [s,Fs] = audioread(filename);
    % 1 frame = frame_length ms = frame_length/1000s
    time = frame_size/1000; 
    % Chia tín hiệu âm thanh thành các khung và tính STE cho mỗi khung
    N = Fs*time; % Độ dài 1 khung
    M = round(length(s)/N);
    frame = buffer(s, N, 0);
    ste = sum(frame.^2, 1); % Tính tổng bình phương các pt trong mỗi cột của frame
    
    % Chuẩn hóa ste
    ste = ste/max(ste);
    s = s/max(s);
    % Lấy chỉ số các khung có ste > 0.1
    index = find(ste>0.1);

    % Lấy đoạn tín hiệu s tương ứng với các khung có ste>0.01
    news = zeros(length(index)*N, 1);
    for i = 1:length(index)
        news((i-1)*N+1 : i*N) = s((index(i)-1)*N+1 : index(i)*N);
    end

    % Vẽ đồ thị
    t = (1:length(s)) / Fs; % Thời gian ứng với mỗi mẫu
    frame_time = (1:length(ste))*time; % Thời gian ứng với mỗi frame
    
    figure('Name', filename);
    subplot(2,1,1);
    plot(t,s);
    hold on;
    plot(frame_time, ste, 'r', 'LineWidth', 1.5);
    xlabel('Thời gian (s)');
    ylabel('Biên độ');
    title('Signal & STE');
    xline((index(1)-1)*time, 'k', 'LineWidth', 1.5);
    xline(index(length(index))*time, 'k', 'LineWidth', 1.5);
    hold off;
    ylim([-1 1]);

    % Vẽ đồ thị
    t = (1:length(news)) / Fs; % Thời gian ứng với mỗi mẫu
    
    subplot(2,1,2);
    plot(t,news);
end