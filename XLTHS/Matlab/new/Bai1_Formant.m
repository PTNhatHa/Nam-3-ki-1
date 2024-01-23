% Define the filenames of the audio files
filenames = {'NguyenAmHuanLuyen-16k/23MTL/a.wav', 'NguyenAmHuanLuyen-16k/23MTL/e.wav', 'NguyenAmHuanLuyen-16k/23MTL/u.wav', 'NguyenAmHuanLuyen-16k/23MTL/i.wav', 'NguyenAmHuanLuyen-16k/23MTL/o.wav'};
filenames2 = {'NguyenAmHuanLuyen-16k/28MVN/a.wav', 'NguyenAmHuanLuyen-16k/28MVN/e.wav', 'NguyenAmHuanLuyen-16k/28MVN/u.wav', 'NguyenAmHuanLuyen-16k/28MVN/i.wav', 'NguyenAmHuanLuyen-16k/28MVN/o.wav'};
filenames3 = {'NguyenAmHuanLuyen-16k/32MTP/a.wav', 'NguyenAmHuanLuyen-16k/32MTP/e.wav', 'NguyenAmHuanLuyen-16k/32MTP/u.wav', 'NguyenAmHuanLuyen-16k/32MTP/i.wav', 'NguyenAmHuanLuyen-16k/32MTP/o.wav'};
filenames4 = {'NguyenAmHuanLuyen-16k/36MAQ/a.wav', 'NguyenAmHuanLuyen-16k/36MAQ/e.wav', 'NguyenAmHuanLuyen-16k/36MAQ/u.wav', 'NguyenAmHuanLuyen-16k/36MAQ/i.wav', 'NguyenAmHuanLuyen-16k/36MAQ/o.wav'};
% Perform formant extraction for each file
formant_table = cell(length(filenames)+1, 4);  % Initialize a cell array for the formant table

% Set column names
formant_table{1, 1} = 'File';
formant_table{1, 2} = 'F1';
formant_table{1, 3} = 'F2';
formant_table{1, 4} = 'F3';

for i = 1:length(filenames)
    % Load the audio file
    [audio, sr] = audioread(filenames{i});

    % Perform formant extraction using LPC
    order = 12; % LPC order (adjust as needed)

    % Apply LPC analysis
    [A, ~] = lpc(audio, order);

    % Get formant frequencies from LPC coefficients
    lpc_formants = roots(A);
    lpc_formants = lpc_formants(imag(lpc_formants) >= 0);  % Retain only real and positive roots
    lpc_formants = sort(atan2(imag(lpc_formants), real(lpc_formants)) * (sr / (2*pi)));  % Convert roots to Hz

    % Ignore any formant frequency below a certain threshold
    threshold = 100;  % Adjust as needed
    lpc_formants = lpc_formants(lpc_formants >= threshold);

    % Store the formant frequencies in the table
    [~, file_name, ~] = fileparts(filenames{i});  % Extract the file name without the path
    formant_table{i+1, 1} = file_name;  % File name
    formant_table{i+1, 2} = round(lpc_formants(1));  % F1 (rounded to the nearest integer)
    formant_table{i+1, 3} = round(lpc_formants(2));  % F2 (rounded to the nearest integer)
    formant_table{i+1, 4} = round(lpc_formants(3));  % F3 (rounded to the nearest integer)
end

% Create a figure and uitable
figure;
uitable('Data', formant_table, 'ColumnName', formant_table(1,:), 'Units', 'Normalized', 'Position', [0.1, 0.1, 0.8, 0.8]);

% Set the title
title('Formant Frequencies');