k = 2;
[x,Fs] = audioread('Recording.wav');
soundsc(x,Fs);
pause(5);
xUp = interp(x(:,1), k);
xDown = x(1:k:length(x));

sound(xUp, Fs * k);
pause(5);
sound(xDown, Fs / k);
