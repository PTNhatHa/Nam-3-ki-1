vowels = {'a', 'e', 'i', 'o', 'u'};
folders = {'24FTL', '25MLM', '30FTN', '33MHP'};

formants24 = {1122, 2016, 3004, 953, 2422, 2972, 469, 2612, 3159, 936, 1464, 3129, 459, 946, 3128};
formants25 = {805, 1568, 2591, 504, 2172, 2927, 431, 2092, 2873, 766, 1165, 2188, 437, 791, 3326};
formants30 = {1113, 1788, 2998, 680, 2283, 3420, 434, 1733, 3048, 767, 1130, 2184, 454, 672, 1700};
formants33 = {755, 1383, 2613, 685, 1912, 2640, 455, 2151, 2897, 726, 1141, 2662, 459, 815 , 2573};

formants = {formants24, formants25, formants30, formants33};

left = 300;
bottom = 150;
width  = 800; % Width of figure
height = 600; % Height of figure (by default in pixels)

for folderIndex = 1:length(folders)
    folder = folders{folderIndex};
    formantData = formants{folderIndex};
    for vowelIndex = 1:length(vowels)
        vowel = vowels{vowelIndex};
        path = strcat('NguyenAmHuanLuyen-16k/', folder, '/', vowel, '.wav');

        % Đọc file âm thanh .wav
        [s, fs] = audioread(path);

        % Tạo đồ thị ảnh phổ
        figure('Name', ['Vowels of ' folder], 'Position', [left bottom width height]);
        %spectrogram(signal, window_length, overlapse, N_FFT, frequency, y_axis)
        spectrogram(s, 5*10^(-3)*fs, 3*10^(-3)*fs, 1024, fs, 'yaxis');

        % Lấy giá trị trên trục y và lưu vào yt
        yt = get(gca, 'YTick');
        set(gca, 'YTick',yt, 'YTickLabel',yt*1E+3);

        % Thêm chú thích cụ thể
        title(['Vowel: ' vowel ' - Folder: ' folder]);
        xlabel('Time (s)');
        ylabel('Frequency (Hz)');

        % Vẽ các tần số formant
        hold on
        xline = [0 2];
        yline1 = [formantData{(3*vowelIndex)-2}/1000 formantData{(3*vowelIndex)-2}/1000];
        yline2 = [formantData{(3*vowelIndex)-1}/1000 formantData{(3*vowelIndex)-1}/1000];
        yline3 = [formantData{3*vowelIndex}/1000 formantData{3*vowelIndex}/1000];
        line(xline,yline1, 'Color', '#1901FF', 'LineStyle', '-','LineWidth',2);
        line(xline,yline2, 'Color', '#FF43F2', 'LineStyle', '-','LineWidth',2);
        line(xline,yline3, 'Color', '#FF0000', 'LineStyle', '-','LineWidth',2);
        legend('F1', 'F2', 'F3');
        hold off
    end
end