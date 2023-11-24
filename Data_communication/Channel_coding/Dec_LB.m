function mbit = Dec_LB(resmbit)

%res = 75000, mbit = 30000
mbit = zeros(1, 2*length(resmbit)/5);

% 00 >> 00000 >> 0 0 0 0 0, 01 >> 01111 >> 0 1 1 1 1,
% 10 >> 10100 >> 1 0 1 0 0, 11 >> 11011 >> 1 1 0 1 1
cordwords = [0 0 0 0 0; 0 1 1 1 1; 1 0 1 0 0; 1 1 0 1 1];
decisionPoint = [0 0 0 0];
decision = [0 0; 0 1; 1 0; 1 1];

minIndex = 0;

% soft decision 
k = 0;
for i = 1:2:length(mbit)-1
    %resmbit(5*i-4:5*i); 
    k = k+1;
    
    if(k == 10000)
        1;
    end

    resmbit(5*(k-1)+1 : 5*(k-1)+5); %debug
    
    for j = 1:5
        if(cordwords(1,j) ~= resmbit(1,j+5*(k-1))) 
            decisionPoint(1) = decisionPoint(1)+1;
        end
        if(cordwords(2,j) ~= resmbit(1,j+5*(k-1)))
            decisionPoint(2) = decisionPoint(2)+1;
        end
        if(cordwords(3,j) ~= resmbit(1,j+5*(k-1)))
            decisionPoint(3) = decisionPoint(3)+1;
        end
        if(cordwords(4,j) ~= resmbit(1,j+5*(k-1)))
            decisionPoint(4) = decisionPoint(4)+1;
        end
    end

    [~, minIndex] = min(decisionPoint);
    
    mbit(i:i+1) = decision(minIndex,1:2);
    decisionPoint(1:4) = [0 0 0 0];
end
mbit;