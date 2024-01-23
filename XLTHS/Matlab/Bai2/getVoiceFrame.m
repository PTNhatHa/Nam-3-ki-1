function [news] = getVoiceFrame(s, Fs, frame_length, index_start, Mframe)
    % 1 frame = 10ms = 10/1000s = 0.01s
    time = frame_length/1000;     
    % Số mẫu 1 frame
    N = Fs*time;
    % Lấy đoạn tín hiệu s tương ứng với các khung có ste>0.01
    news = zeros(Mframe*N, 1);
    j=1;
    for i = index_start:index_start+Mframe
        news((j-1)*N+1 : j*N) = s((i-1)*N+1 : i*N);
        j=j+1;
    end
end