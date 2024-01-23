A = input('Nhập biên độ A = ');
F0 = input('Nhập tần số F0 = '); % 1000 - 15000Hz
phi = input('Nhập góc phi = ');
n = 0:2000;
Fs1 = 3*F0;
Fs2 = 1.5*F0;
t1 = n/Fs1;
t2 = n/Fs2;
x1 = A*cos(2*pi*F0*t1 + phi);
x2 = A*cos(2*pi*F0*t2 + phi);

subplot(2,1,1); % Chia cửa sổ đồ thị thành 2 hàng và 1 cột, chọn vùng đầu tiên
stem(t1,x1, "filled"); % Vẽ đồ thị rời rạc của x1 theo t1
ylabel('x1[n]'); % Đặt nhãn cho trục y
xlabel('t');

subplot(2,1,2);
stem(t2,x2,"filled");
ylabel('x2[n]');
xlabel('t');

soundsc(x1,Fs1);
pause(5); 
soundsc(x2,Fs2);