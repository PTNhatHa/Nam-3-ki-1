function [signal, Mframe_ondinh] = getVoiceCenter(s, Mframe)
    Mframe_ondinh = ceil(Mframe/3); % Làm tròn lên số nguyên gần nhất
    signal = s(Mframe_ondinh : Mframe_ondinh*2);
end