k = 2;
f = 3000;
Fs = 3 * f;
t = 0:1/Fs:1;

x = cos(2*pi*f*t);

xUp = interp(x, k);
% xUp = zeros(1, k * length(x));
% xUp(1:k:length(xUp)) = x;

sound(x, Fs);
sound(xUp, Fs * k);

% using general function
% xUp = upsample(x, k);
% xDown = downsample(x, k);