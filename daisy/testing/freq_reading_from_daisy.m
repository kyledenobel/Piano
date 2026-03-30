% analyze the frequencies produced by the daisy seed

mtx = readmatrix("putty_log_files/putty.log");
mtx = mtx(2:numel(mtx));
Fs = 9600/2;

figure(1)
plot(mtx)

subnote = mtx(43000:46000);

subnote = subnote - movmean(subnote, 100);
figure(2)
plot(subnote)

F = fft(subnote);
F = fftshift(F);
F = abs(F);
freqHz = (-(length(F) - 1)/2:1:(length(F) - 1)/2)*Fs/length(F);
%freqHz = fftshift(freqHz);
figure(3)
plot(freqHz, F);
xlim([-1000, 1000])


player = audioplayer(rescale(mtx), Fs);
play(player)