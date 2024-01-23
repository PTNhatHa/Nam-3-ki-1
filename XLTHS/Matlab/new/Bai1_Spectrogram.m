filenames = {'a.wav', 'e.wav', 'u.wav', 'i.wav', 'o.wav'};
filenames2 = {'NguyenAmHuanLuyen-16k/28MVN/a.wav', 'NguyenAmHuanLuyen-16k/28MVN/e.wav', 'NguyenAmHuanLuyen-16k/28MVN/u.wav', 'NguyenAmHuanLuyen-16k/28MVN/i.wav', 'NguyenAmHuanLuyen-16k/28MVN/o.wav'};
filenames3 = {'NguyenAmHuanLuyen-16k/32MTP/a.wav', 'NguyenAmHuanLuyen-16k/32MTP/e.wav', 'NguyenAmHuanLuyen-16k/32MTP/u.wav', 'NguyenAmHuanLuyen-16k/32MTP/i.wav', 'NguyenAmHuanLuyen-16k/32MTP/o.wav'};
filenames4 = {'NguyenAmHuanLuyen-16k/36MAQ/a.wav', 'NguyenAmHuanLuyen-16k/36MAQ/e.wav', 'NguyenAmHuanLuyen-16k/36MAQ/u.wav', 'NguyenAmHuanLuyen-16k/36MAQ/i.wav', 'NguyenAmHuanLuyen-16k/36MAQ/o.wav'};
figure_width = 800;
figure_height = 600;

for i = 1:numel(filenames)
    % Read the audio file
    [audio, sample_rate] = audioread(filenames{i});
    
    % Compute the wideband spectrogram
    figure('Position', [100, 100, figure_width, figure_height]);
    spectrogram(audio, 'yaxis');
    
    % Save the spectrogram as an image
    output_filename = sprintf('Spectrogram_%d.png', i);
    saveas(gcf, output_filename);
end

% Loop over the filenames in filenames2 array
for i = 1:numel(filenames2)
    % Read the audio file
    [audio, sample_rate] = audioread(filenames2{i});
    
    % Compute the wideband spectrogram
    figure('Position', [100, 100, figure_width, figure_height]);
    spectrogram(audio, 'yaxis');
    
    % Save the spectrogram as an image
    output_filename = sprintf('Spectrogram_%d.png', i+numel(filenames));
    saveas(gcf, output_filename);
end

% Loop over the filenames in filenames3 array
for i = 1:numel(filenames3)
    % Read the audio file
    [audio, sample_rate] = audioread(filenames3{i});
    
    % Compute the wideband spectrogram
    figure('Position', [100, 100, figure_width, figure_height]);
    spectrogram(audio, 'yaxis');
    
    % Save the spectrogram as an image
    output_filename = sprintf('Spectrogram_%d.png', i+numel(filenames)+numel(filenames2));
    saveas(gcf, output_filename);
end

% Loop over the filenames in filenames4 array
for i = 1:numel(filenames4)
    % Read the audio file
    [audio, sample_rate] = audioread(filenames4{i});
    
    % Compute the wideband spectrogram
    figure('Position', [100, 100, figure_width, figure_height]);
    spectrogram(audio, 'yaxis');
    
    % Save the spectrogram as an image
    output_filename = sprintf('Spectrogram_%d.png', i+numel(filenames)+numel(filenames2)+numel(filenames3));
    saveas(gcf, output_filename);
end
