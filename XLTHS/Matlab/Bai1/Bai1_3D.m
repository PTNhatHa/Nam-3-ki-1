vowels = {'/a/', '/e/', '/i/', '/o/', '/u/'};

% Dữ liệu formants cho mỗi folder
formants24 = [
    1122, 2016, 3004;
    953, 2422, 2972;
    469, 2612, 3159;
    936, 1464, 3129;
    459, 946, 3128
];

formants25 = [
    805, 1568, 2591;
    504, 2172, 2927;
    431, 2092, 2873;
    766, 1165, 2188;
    437, 791, 3326
];

formants30 = [
    1113, 1788, 2998;
    680, 2283, 3420;
    434, 1733, 3048;
    767, 1130, 2184;
    454, 672, 1700
];

formants33 = [
    755, 1383, 2613;
    685, 1912, 2640;
    455, 2151, 2897;
    726, 1141, 2662;
    459, 815, 2573
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
    scatter3(formants(:, 1), formants(:, 2), formants(:, 3), 'filled');
    
    xlabel('F1', 'FontSize', 20);
    ylabel('F2', 'FontSize', 20);
    zlabel('F3', 'FontSize', 20);
    text(formants(:, 1), formants(:, 2), formants(:, 3), vowels, 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right', 'FontSize', 20);

    set(hAxes, 'FontSize', 20);

title(['Biểu đồ 3D giữa F1, F2 và F3 - Folder: ' folders{folderIndex}]);
    
end