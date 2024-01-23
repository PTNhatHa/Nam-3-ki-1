xn = 0:4; % index
x = 5:-1:1;
k = 2;
y =  x(length(xn)):x(1);

% (a) First folding, then shifting
yn1 = -xn(end):-xn(1);
yn1 = yn1 + k;

% (b) First shifting, then folding
yn2 = xn + k;
yn2 = -yn2(end):-yn2(1);

%Plot
xylimit = [min([xn(1),yn1(1),yn2(1)])-1,max([xn(end),yn1(end)...
,yn2(end)])+1,min(x)-1,max(x)+1];

subplot(3,1,1); 
stem(xn,x,"filled");
axis(xylimit);
xlabel("n");
ylabel("x[n]");
title("x[n]");

subplot(3,1,2);
stem(yn1,y,"filled");
axis(xylimit);
xlabel("n");
ylabel("y1[n]");
title("(a) y1[n]: First folding, then shifting");

subplot(3,1,3);
stem(yn2,y,"filled");
axis(xylimit);
xlabel("n");
ylabel("y2[n]");
title("(b) y2[n]: First shifting, then folding");