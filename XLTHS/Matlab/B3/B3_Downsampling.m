A = input('Nhập biên độ A = ');
F0 = input('Nhập tần số F0 = '); % 1000 - 15000Hz
phi = input('Nhập góc phi = ');
k = input('Nhập số lần muốn giảm tốc độ lấy mẫu k =');

Fs = 3*F0;
t = 0:1/Fs:1;
x = A*cos(2*pi*F0*t + phi);

% xDown = downsample(x, k);
xDown = x(1:k:length(x)); % lấy một tập con của các phần tử trong vector x với bước nhảy là k

sound(x, Fs);
sound(xDown, Fs / k);

subplot(2,1,1);
stem(t,x);
ylabel('x');
xlabel('t');

t1 = t(1:k:length(t)); 
subplot(2,1,2);
stem(t1,xDown);
ylabel('xDown');
xlabel('t');