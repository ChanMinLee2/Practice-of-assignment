function resmbit = Enc_LB(mbit)
% linear block 방식 enc

% 2차원 mbit를 입력받아 5차원 bits로 변환하기 위한 공간생성
resmbit = zeros(1, 5*length(mbit)/2);

% generator 생성 (현재 경우에서는 01, 10의 cordwords)
% 00 >> 00000 >> 0 0 0 0 0, 01 >> 01111 >> 0 1 1 1 1,
% 10 >> 10100 >> 1 0 1 0 0, 11 >> 11011 >> 1 1 0 1 1

generator = [0 0 0 0 0; 0 1 1 1 1; 1 0 1 0 0; 1 1 0 1 1];

j = 0;

for i = 1:2:length(mbit)-1
    j = j+1;
    if ((mbit(i) == 0) && mbit(i+1) == 0) 
        resmbit(1,5*j-4:5*j) = generator(1,1:5);

    elseif ((mbit(i) == 0) && mbit(i+1) == 1) 
        resmbit(1,5*j-4:5*j) = generator(2,1:5);

    elseif ((mbit(i) == 1) && mbit(i+1) == 0) 
        resmbit(1,5*j-4:5*j) = generator(3,1:5);

    elseif ((mbit(i) == 1) && mbit(i+1) == 1) 
        resmbit(1,5*j-4:5*j) = generator(4,1:5);
    end
end