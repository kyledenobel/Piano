% script to test the enclosure functions by listening to a piano note
% NOTE:only play a section at a time. Top section plays piano note, bottom
% plays just a sine wave at the fundamental frequency. You must run the
% 'spectral_analysis.m' script first in order to populate some variables.


Fs = 10000;
t = 0:(1/Fs):3;

function output=model_func(params, t)
    output=zeros(size(t));
    for tind = 1:length(t)
        if t(tind) < params(1)
            output(tind) = (params(2) / params(1)) * t(tind);
        else
            output(tind) = params(2) * exp(-params(3) * ((t(tind)-params(1))^params(4)));
        end
    end
end


note = zeros(1, numel(t));
for i = 1:5
    f1 = frequencies_to_use(i);
    enc = model_func(harmonics_parameters(i, :), t);
    enc = enc./max(harmonics_parameters(:,2));
    figure
    plot(enc)
    note = note + enc.*cos(2*pi*f1*t);
end

note = note./5;

figure
plot(note)

player = audioplayer(note, Fs);
play(player)


%%
f1 = frequencies_to_use(1);
note = cos(2*pi*f1*t);
player = audioplayer(note, Fs);
play(player)