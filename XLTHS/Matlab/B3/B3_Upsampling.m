A = input('Nhập biên độ A = ');
F0 = input('Nhập tần số F0 = '); % 1000 - 15000Hz
phi = input('Nhập góc phi = ');
k = input('Nhập số lần muốn tăng tốc độ lấy mẫu k =');

Fs = 3*F0;
t = 0:1/Fs:1;
x = A*cos(2*pi*F0*t + phi);

% xUp = upsample(x, k);
xUp = interp(x, k); % tăng tốc độ lấy mẫu của một tín hiệu bằng cách nội suy
sound(x, Fs);
sound(xUp, Fs * k);

subplot(2,1,1);
stem(t,x);
ylabel('x');
xlabel('t');

t1 = interp(t, k); 
subplot(2,1,2);
stem(t1,xUp);
ylabel('xUp');
xlabel('t');