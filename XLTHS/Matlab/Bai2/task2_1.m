filenames = {'NguyenAmHuanLuyen-16k/23MTL/a.wav', 'NguyenAmHuanLuyen-16k/24FTL/a.wav', 'NguyenAmHuanLuyen-16k/32MTP/a.wav'};

filenames2 = {'NguyenAmHuanLuyen-16k/28MVN/a.wav', 'NguyenAmHuanLuyen-16k/28MVN/e.wav', 'NguyenAmHuanLuyen-16k/28MVN/u.wav', 'NguyenAmHuanLuyen-16k/28MVN/i.wav', 'NguyenAmHuanLuyen-16k/28MVN/o.wav'};
filenames3 = {'NguyenAmHuanLuyen-16k/24FTL/a.wav', 'NguyenAmHuanLuyen-16k/24FTL/e.wav', 'NguyenAmHuanLuyen-16k/24FTL/u.wav', 'NguyenAmHuanLuyen-16k/24FTL/i.wav', 'NguyenAmHuanLuyen-16k/24FTL/o.wav'};
filenames4 = {'NguyenAmHuanLuyen-16k/30FTN/a.wav', 'NguyenAmHuanLuyen-16k/30FTN/e.wav', 'NguyenAmHuanLuyen-16k/30FTN/u.wav', 'NguyenAmHuanLuyen-16k/30FTN/i.wav', 'NguyenAmHuanLuyen-16k/30FTN/o.wav'};


for k = 1:length(filenames)
    [s,Fs] = audioread(filenames{k});
    % % Biểu đồ bài 2.1
    % TachTinHieu(filenames2{k},10);

    frame_shilft = 0;
    frame_size = 30;
    [x_ondinh, index_ondinh, Mframe_ondinh] = getVoiceCenter2(s,Fs,frame_size,frame_shilft);
    [x, index, Mframe] = getVoice(s,Fs,frame_size,frame_shilft);
    % [signal, index_ondinh, Mframe_ondinh] = getVoiceCenter(s, index(1), Mframe);

    figure('Name', filenames{k});
    subplot(3,1,1);
    t = (1:length(s)) / Fs;
    plot(t,s);
    hold on;
    xlabel('Thời gian (s)');
    ylabel('Biên độ');
    title('Bài 2.1: Tín hiệu');
    xline((index(1) - 1)*(frame_size/1000), 'r', 'LineWidth', 1.5);
    xline((index(length(index)))*(frame_size/1000), 'r', 'LineWidth', 1.5);
    hold off;

    subplot(3,1,2);
    t = (1:length(x)) / Fs;
    plot(t,x);
    hold on;
    xlabel('Thời gian (s)');
    ylabel('Biên độ');
    title('Bài 2.2a: Xác định vùng ổn định');
    xline((index_ondinh(1) - index(1) - 1)*(frame_size/1000), 'r', 'LineWidth', 1.5);
    xline((index_ondinh(length(index_ondinh)) - index(1))*(frame_size/1000), 'r', 'LineWidth', 1.5);
    hold off;

    subplot(3,1,3);
    t = (1:length(x_ondinh)) / Fs;
    plot(t,x_ondinh);
    xlabel('Thời gian (s)');
    ylabel('Biên độ');
    title('Bài 2.2a: Vùng ổn định');
    pause(3);
end
