function [index_ondinh, Mframe_ondinh] = getVoiceCenter(index_start, Mframe)
    part_size = ceil(Mframe/3); % Làm tròn lên số nguyên gần nhất
    index_ondinh = index_start + part_size;
    Mframe_ondinh = part_size;
end