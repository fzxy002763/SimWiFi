% CA Throughput Using Bianchi Model
% copyright by Edward.xu(MUST)
% 280599580@qq.com
%
%------------------------- Log -------------------------- 
% 20141130 - create by Edward.xu
% 20150311 - rewrite by Edward.xu as the model change
% 20150316 - rewrite by Edward.xu for model the CSMA/CQ
% 20160505 - rewrite by Edward.xu for model the CSMA/CA
%--------------------------------------------------------

function ana = bianchi(rate,L_p,Pd,Per)

    %mac prob
    global CWmin;
    global m;
    global nodeNum;

    CWmin      = 31;
    m          = 5;
    
    data_rate  = rate;

    L_ph       = 208;
    L_mh       = 224;
    L_Header   = (L_ph + L_mh);
    L_Payload  =  L_p * 8;
    L_Ack      = (L_ph + 14 * 8);

    t_SIFS     = 10; 
    t_SLOT     = 20;
    t_DIFS     = t_SIFS + t_SLOT * 2;
    t_PROP     = 0;
 
    t_Header   = L_Header  / data_rate;
    t_Payload  = L_Payload / data_rate;
    t_Ack      = L_Ack     / data_rate;
    t_p        = t_Header + t_Payload;
   
    t_s       = t_DIFS + t_p + t_SIFS + t_Ack + 2*t_PROP;
    %    t_s       =  t_p + t_SIFS + t_Ack + 2*t_PROP;
    t_c       = t_s;
    
    alpha_beta_temp = fsolve(@p_tau,[0 0],optimset('Display','off'));
    alpha           = alpha_beta_temp(1);
    beta            = alpha_beta_temp(2);
    
    Ptr_temp    = (1 - beta)^nodeNum;
    Ptr         = 1 - Ptr_temp;
    Ps_temp     = (1 - beta)^(nodeNum-1);
    Ps          = nodeNum * beta * Ps_temp;
    
    P1  = 1 - Ptr;
    T1  = t_SLOT;
    
    P2  = Ps;
    T2  = t_s ;
    
    P3  = Ptr - Ps;
    T3  = t_c ;
    
    t_all  = (P1 * T1 + P2 * T2 + P3 * T3);
    lambda_rate = (Pd*1+(1-Pd)*Per) * Ps / (t_all);
    ana         = L_Payload * lambda_rate; 
    
end
