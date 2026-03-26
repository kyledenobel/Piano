% read in audio sample
[x,Fs] = audioread(fullfile(pwd, "piano_recordings", "A#.wav"));

% calculate input window.
T = 0.25;
win = Fs*T;

% calculate spectrogram
[s,f,t] = spectrogram(x, win, [], [], Fs);

% display spectrogram with hertz
figure(1)
spectrogram(x, win, [], [], Fs,'yaxis')
ylim([0, 1.2])

% display frequencies at 1 second into audio sample
figure(2)
plot(f, abs(s(:,find(t>1, 1))))
xlim([0,1500])


[v, i] = max(sum(s, 1));
audio_power__ = abs(s(:, i).^2);
freq_indices = find(islocalmax(audio_power__, 1, 'MaxNumExtrema',5, 'MinProminence',100), 5);
f(freq_indices)

