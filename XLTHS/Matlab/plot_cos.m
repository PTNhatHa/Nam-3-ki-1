t = [-pi/2:pi/100:4*pi];
x = cos(t);
subplot(3,1,1);
plot(t,x); % Vẽ hình sin từ 0->2pi

n = [-20:0.01:20];
x1 = cos(n*pi);
x2 = cos(n*pi*(2/3));
subplot(3,1,2); % Chia cửa sổ figure thành 2 hàng 1 cột và chọn vùng số 2
plot(n,x1);  % Vẽ đồ thị x1 theo n trên vùng số 2
subplot(3,1,3);
plot(n,x2); 