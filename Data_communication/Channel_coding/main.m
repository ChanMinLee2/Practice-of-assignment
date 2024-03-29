clear;

%%% parameter
N0mat = [0.05:0.02:0.5];
% SNR, BER 체크 3개 case별로 진행
SNRres = zeros(length(N0mat),3); 
BERres = zeros(length(N0mat),3);
 
BER2res = zeros(length(N0mat),3);

%% parameter setting
Tsym = 1;
Nbit = 30000;
Fs = 100;
Fc = 10;
N0 = 0.01;

%%% QAM 신호 생성
M=4;
symTable = zeros(1,4);
for i = 1:M
    i_m = 2*pi*(i-1)/M + pi/4;
    symTable(i) = cos(i_m) + j*sin(i_m);
end
bitTable = [0 0; 0 1; 1 0; 1 1];


%% Tx
mbit = randi(2,1,Nbit) -1;
mbit_orig = mbit;

for iN0 = 1: length(N0mat)
    N0 = N0mat(iN0);

%%% Uncoded
Nsym =Nbit/2;
t = [1/Fs:1/Fs:Tsym*Nsym];
Tmax = length(t);
% basis signal 생성
phi1 = cos(2*pi*Fc*t(1:Tsym*Fs));
Es = norm(phi1);

m = zeros(1, Nbit/2);
for mi = 1:length(m)
    m(mi) = mbit(2*mi)+2*mbit(2*mi-1)+1; 
     
end
%%% 심볼신호 만들기
theta_m = 2*pi*(m-1)/M + pi/4;
bbSym = cos(theta_m) + j*sin(theta_m);
bbSym_orig = bbSym;

% RF 생성
RFsignal = zeros(1,Tmax);
for iterT = 1:Tmax
    iterSym = floor((iterT-1)/Fs)+1;
    RFsignal(iterT) = real(bbSym(iterSym))*cos(2*pi*Fc*t(iterT))/Es - imag(bbSym(iterSym))*sin(2*pi*Fc*t(iterT))/Es;
end


%% Rx + Ch
% Coherent Detection
Ich = RFsignal .* cos(2*pi*Fc*t)/Es;
Qch = RFsignal .* sin(2*pi*Fc*t)/Es;

% BBSym conversion
bbSym_rx = zeros(1,Nsym);
for i = 1:Nsym
    n_start = (i-1)*Tsym*Fs;
    bbSym_rx(i) = sum(Ich(n_start+1:n_start+Tsym*Fs)- j*Qch(n_start+1:n_start+Tsym*Fs));
end
sigPower = mean(abs(bbSym_rx).^2);

% Noise Insertion
noise = sqrt(N0)*randn(1,Nsym)+j*sqrt(N0)*randn(1,Nsym);
bbSymN_rx = bbSym_rx+noise; % r = s_m + n
noisePower = mean(abs(noise).^2);
SNR = 10*log10(sigPower/noisePower)

% Optimal Receiver
hd_bbSym = zeros(1,Nsym);
hd_bit = [];
for i = 1:Nsym
    % corr_metric = bbSymN_rx(i)*conj(symTable);
    dist_metric = -abs(bbSymN_rx(i)-symTable);
    [dummyVal, hd_index] = max(real(dist_metric));
    hd_bbSym(i) = symTable(hd_index);
    hd_bit = [hd_bit bitTable(hd_index,:)];
end

BER = sum(abs(mbit-hd_bit)>0.01) / Nbit;

%%%
SNRres(iN0,1) = SNR;
BERres(iN0,1) = BER;



%%% Repetition - channel coding - 13주차에 설명해주신다고 하심. 
coderate = 3;
Nsym =Nbit*coderate/2;
t = [1/Fs:1/Fs:Tsym*Nsym];
Tmax = length(t);
% basis signal 생성
phi1 = cos(2*pi*Fc*t(1:Tsym*Fs));
Es = norm(phi1);

mbit_rep = Enc_rep(mbit);
m = zeros(1, Nbit*coderate/2); % 45000개 공간
for mi = 1:length(m)
    m(mi) = mbit_rep(2*mi)+2*mbit_rep(2*mi-1)+1;%    index 123456
    % m(1) = mbit_rep(2)+2*mbit_rep(1)+1 // 10이라는 신호는 111000이될거고 이때
    % mbit_rep(2),(1)은 각 1, 1이라 1+2+1 = 4번신호, 
    % mbit_rep(4),(3)은 각 1, 0이라 0+2+1 = 3번신호
end
%%% 심볼신호 만들기
theta_m = 2*pi*(m-1)/M + pi/4;
bbSym = cos(theta_m) + j*sin(theta_m);
bbSym_orig = bbSym;

% RF 생성
RFsignal = zeros(1,Tmax);
for iterT = 1:Tmax
    iterSym = floor((iterT-1)/Fs)+1;
    RFsignal(iterT) = real(bbSym(iterSym))*cos(2*pi*Fc*t(iterT))/Es - imag(bbSym(iterSym))*sin(2*pi*Fc*t(iterT))/Es;
end


%% Rx + Ch
% Coherent Detection
Ich = RFsignal .* cos(2*pi*Fc*t)/Es;
Qch = RFsignal .* sin(2*pi*Fc*t)/Es;

% BBSym conversion
bbSym_rx = zeros(1,Nsym);
for i = 1:Nsym
    n_start = (i-1)*Tsym*Fs;
    bbSym_rx(i) = sum(Ich(n_start+1:n_start+Tsym*Fs)- j*Qch(n_start+1:n_start+Tsym*Fs));
end
sigPower = mean(abs(bbSym_rx).^2);

% Noise Insertion
noise = sqrt(N0)*randn(1,Nsym)+j*sqrt(N0)*randn(1,Nsym);
bbSymN_rx = bbSym_rx+noise; % r = s_m + n
noisePower = mean(abs(noise).^2);
SNR = 10*log10(sigPower/noisePower)

% Optimal Receiver
hd_bbSym = zeros(1,Nsym);
hd_bit = [];
for i = 1:Nsym
    % corr_metric = bbSymN_rx(i)*conj(symTable);
    dist_metric = -abs(bbSymN_rx(i)-symTable);
    [dummyVal, hd_index] = max(real(dist_metric));
    hd_bbSym(i) = symTable(hd_index);
    hd_bit = [hd_bit bitTable(hd_index,:)];
end
BER2 = sum((mbit_rep-hd_bit)>0.01) / 90000; 
BER2res(iN0,2) = BER2;
hd_bit = Dec_rep(hd_bit);
BER = sum(abs(mbit-hd_bit)>0.01) / Nbit;

%%%
SNRres(iN0,2) = SNR;
BERres(iN0,2) = BER;



%%% Linear block
mbit = mbit_orig; 
coderate_lin = 5;
Nsym = Nbit*coderate_lin/2/2; % 37500
t2 = [1/Fs:1/Fs:Tsym*Nsym]; 
Tmax_lin = length(t2);
% basis signal 생성
phi1_lin = cos(2*pi*Fc*t2(1:Tsym*Fs));
Es_lin = norm(phi1_lin);

mbit_lin = Enc_LB(mbit);
m = zeros(1, Nbit*coderate_lin/2/2); % 30000*5/2/2 = 75000 / 2 = 37500 

for mi = 1:length(m) % 75000개 비트중에서 message는 15000개 , 심볼은 37500개
    m(mi) = mbit_lin(2*mi)+2*mbit_lin(2*mi-1)+1;
end

%%% 심볼신호 만들기
theta_m = 2*pi*(m-1)/M + pi/4;
bbSym = cos(theta_m) + j*sin(theta_m);
bbSym_orig = bbSym;

% RF 생성
RFsignal = zeros(1,Tmax_lin);
for iterT = 1:Tmax_lin
    iterSym = floor((iterT-1)/Fs)+1;
    RFsignal(iterT) = real(bbSym(iterSym))*cos(2*pi*Fc*t2(iterT))/Es_lin - imag(bbSym(iterSym))*sin(2*pi*Fc*t2(iterT))/Es_lin;
end


%% Rx + Ch
% Coherent Detection
Ich = RFsignal .* cos(2*pi*Fc*t2)/Es_lin;
Qch = RFsignal .* sin(2*pi*Fc*t2)/Es_lin;

% BBSym conversion
bbSym_rx = zeros(1,Nsym);
for i = 1:Nsym
    n_start = (i-1)*Tsym*Fs;
    bbSym_rx(i) = sum(Ich(n_start+1:n_start+Tsym*Fs)- j*Qch(n_start+1:n_start+Tsym*Fs));
end
sigPower = mean(abs(bbSym_rx).^2);

% Noise Insertion
noise = sqrt(N0)*randn(1,Nsym)+j*sqrt(N0)*randn(1,Nsym);
bbSymN_rx = bbSym_rx+noise; % r = s_m + n
noisePower = mean(abs(noise).^2);
SNR = 10*log10(sigPower/noisePower)

% Optimal Receiver 
% 수신신호를 받아서 각 비트마다 hd를 하고, 그 코드에 맞춰 cordword decision
hd_bbSym = zeros(1,Nsym);
hd_bit = [];
for i = 1:Nsym
    % corr_metric = bbSymN_rx(i)*conj(symTable);
    dist_metric = -abs(bbSymN_rx(i)-symTable);
    [dummyVal, hd_index] = max(real(dist_metric));
    hd_bbSym(i) = symTable(hd_index);
    hd_bit = [hd_bit bitTable(hd_index,:)];
end
BER2 = sum((mbit_lin-hd_bit)>0.01) / 75000;
BER2res(iN0,3) = BER2;
hd_bit = Dec_LB(hd_bit);
BER = sum(abs(mbit-hd_bit)>0.01) / Nbit; 

%%%
SNRres(iN0,3) = SNR;
BERres(iN0,3) = BER;

end

figure(1)
plot(SNRres(:,1), BERres(:,1),'b')
hold on
plot(SNRres(:,2), BERres(:,2),'r')
hold on
plot(SNRres(:,3), BERres(:,3),'g')
hold on 
plot(SNRres(:,3), BER2res(:,2),'y*')
hold on
plot(SNRres(:,3), BER2res(:,3),'y-')