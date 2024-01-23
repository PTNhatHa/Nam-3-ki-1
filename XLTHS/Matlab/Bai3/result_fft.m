function result_fft(filtered_signal, fs, frame_length, frame_shift, win_func, N_FFT)
    window = feval(win_func, frame_length);

    frame_length = round(frame_length);
    frame_shift = round(frame_shift);
    fft_results = [];

    for i = 1:frame_shift:(length(filtered_signal) - frame_length + 1)
        frame = filtered_signal(i:i+frame_length-1);
        windowed_frame = frame .* window;
        fft_frame = fft(windowed_frame, N_FFT);
        fft_results = [fft_results; abs(fft_frame(1:N_FFT/2))];
    end
    average_fft = mean(fft_results, 1);
    frequencies = (0:N_FFT/2-1) * (fs / N_FFT);
end

