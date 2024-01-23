function [signal, index_ondinh, Mframe_ondinh] = getVoiceCenter(s, index_start, Mframe)
    part_size = ceil(Mframe/3); % Làm tròn lên số nguyên gần nhất
    index_ondinh = [index_start + part_size, index_start + part_size*2];
    Mframe_ondinh = part_size;
    signal = s(index_ondinh(1) : index_ondinh(2));
end