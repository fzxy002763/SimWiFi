function output = p_tau(input)
% p and tau Calculate Using Bianchi Model
% Input  : [input]
% Output : [output]
% copyright by Edward.xu(MUST)
% 280599580@qq.com
%
%------------------------- Log -------------------------- 
% 20141129 - create by Edward.xu
%--------------------------------------------------------

    global CWmin;
    global m;
    global nodeNum;
    
    p   = input(1);
    tau = input(2);
    
    sum = 0;
    for k=0:1:m-1;
        sum = (2*p)^k + sum;
    end
    
    output1_temp   = (1-tau)^(nodeNum-1);
    output(1)      = 1-output1_temp-p;
    output2_temp   = 2/(1+CWmin+p*CWmin*sum);
    output(2)      = output2_temp-tau;
    
end