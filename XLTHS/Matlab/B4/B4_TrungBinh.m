k = input("Nhập số phần tử của x[n]: ");
n = 1:k;
x = randi([-10,10],1,k);
y = 1:k;
y(1) = x(1)/3;
y(2) = (x(1) + x(2))/3;
for i=3:1:k
    y(i) = (x(i) + x(i-1) + x(i-2))/3;
end

subplot(2,1,1);
stem(n,x,"filled");
xlabel("n");
ylabel("x[n]");
title("x[n]");

subplot(2,1,2);
stem(n,y,"filled");
xlabel("n");
ylabel("y[n]");
title("y[n]: Trung bình trượt 3 mẫu tín hiệu liên tiếp");