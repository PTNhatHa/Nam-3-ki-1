A = input('Nhập biên độ A = ');
phi = input('Nhập góc phi = ');
n = -100:100; % Tạo vecto [-10 -9 ... 9 10]
x1 = A*cos(pi*n + phi);
x2 = A*cos((2/3)*pi*n + phi);

subplot(2,1,1); % Chia cửa sổ đồ thị thành 2 hàng và 1 cột, chọn vùng đầu tiên
stem(n,x1, "filled"); % Vẽ đồ thị rời rạc của x1 theo n
ylabel('x1[n]'); % Đặt nhãn cho trục y
title('Tín hiệu rời rạc x1[n]');
subplot(2,1,2);
stem(n,x2,"filled");
ylabel('x2[n]');
title('Tín hiệu rời rạc x2[n]');