function [indexStart,Mframe] = getVoice(s, Fs, frame_length)
    % 1 frame = 10ms = 10/1000s = 0.01s
    time = frame_length/1000; 
    % Số mẫu 1 frame
    N = Fs*time;
    % Số frame 
    M = length(s)/N;
    
    % Tính STE
    ste = zeros(round(M),1);
    m=1;
    for i = 1:round(M)
        for j = 1:N
            ste(i) = ste(i) + s(m).^2;
            m=m+1;
            if(m>length(s)) 
                break;
            end
        end
    end
    
    % Chuẩn hóa STE, s (0-1)
    ste = ste/max(ste);

    % Lấy chỉ số các khung có ste>0.1
    index = find(ste>0.1);

    indexStart = index(1);
    Mframe = length(index);
end