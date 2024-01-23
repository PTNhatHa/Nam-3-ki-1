vowels = {'/a/', '/e/', '/i/', '/o/', '/u/'};

% Dữ liệu formants cho mỗi folder
formants24 = [
    1122, 2016;
    953, 2422;
    469, 2612;
    936, 1464;
    459, 946
];

formants25 = [
    805, 1568;
    504, 2172;
    431, 2092;
    766, 1165;
    437, 791
];

formants30 = [
    1113, 1788;
    680, 2283;
    434, 1733;
    767, 1130;
    454, 672
];

formants33 = [
    755, 1383;
    685, 1912;
    455, 2151;
    726, 1141;
    459, 815
];

folders = {'24FTL', '25MLM', '30FTN', '33MHP'};
formantsData = {formants24, formants25, formants30, formants33};

left = 300;
bottom = 150;
width = 800;
height = 600;

for folderIndex = 1:length(folders)
    figure('Position',[left bottom width height]);
    formants = formantsData{folderIndex};
    
    hAxes = axes;
    scatter(formants(:, 1), formants(:, 2), 'filled');
        
    xlabel('F1', 'FontSize', 20);
    ylabel('F2', 'FontSize', 20);
    
    text(formants(:, 1), formants(:, 2), vowels, 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'left', 'FontSize', 20);
    
    set(hAxes, 'FontSize', 20); % Đặt kích thước chữ của trục x, y và các số chia trục

    title(['Biểu đồ 2D giữa F1 và F2 - Folder: ' folders{folderIndex}]);
end
