k = 2;
f = 3000;
Fs = 3 * f;
t = 0:1/Fs:1;

x = cos(2*pi*f*t);

xDown = x(1:k:length(x)); % lấy một tập con của các phần tử trong vector x với bước nhảy là k

sound(x, Fs);
sound(xDown, Fs / k);

% using general function
% xUp = upsample(x, k);
% xDown = downsample(x, k);