%Read the result from txt
clear;clc;clf;
NowDir    = pwd;
cd ../Result/CA;
ResultDir = pwd;
ReadPath  = dir(fullfile(ResultDir,'*.txt'));
NumTxt    = length(ReadPath);
for iterRead = 1:NumTxt
   CA_data(iterRead,:) = importdata(strcat(pwd,'\',ReadPath(iterRead).name));
end
cd(NowDir);
clear -regexp [^CA_data];

%sim result
sim_CA = CA_data;

nodeNumPath = 1:1:30;
global nodeNum;
OFDM_rate   = 11;
Payload     = 1500;
Pd          = 1;
Per         = 0;
for i=1:1:length(nodeNumPath)
    nodeNum = nodeNumPath(i);
    ana_CA(i) = bianchi(OFDM_rate,Payload,Pd,Per);
end

ana_plot = sim_CA;
sim_plot = ana_CA;

plot(nodeNumPath,ana_plot,nodeNumPath,sim_plot);
legend('sim','ana');
%axis([1 30 0 54]);
grid on;

r_error = abs(ana_CA-sim_CA)./sim_CA;
r_error = mean(r_error)*100;

fprintf('Relative error = %.2f%%\n',r_error);