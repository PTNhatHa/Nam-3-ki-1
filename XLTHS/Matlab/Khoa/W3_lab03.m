k = 2;

[x, Fs] = audioread('Recording (2).m4a');
duration = length(x) / Fs - 1;

% Up = zeros(1, k * length(x));
% xUp(1:k:length(xUp)) = x;
xUp = interp(x, k);

xDown = x(1:k:length(x));


sound(x, Fs);
pause(duration);


sound(xUp, Fs * k);
%sound(xDown, Fs / k);