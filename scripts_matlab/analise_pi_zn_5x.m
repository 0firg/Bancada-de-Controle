arquivo=load('zn_38_53_pi_5_x.txt');%le o arquivo com os dados

amostras=size(arquivo);%identifica a quantidade de dados
amostras=amostras(1,1);%salva a quantidade de dados

temperatura=arquivo(:,1);
setpoint=arquivo(:,2);
erro=arquivo(:,3);
tempo_s=arquivo(:,4);
entrada_lamp=arquivo(:,5);

tempo_s=tempo_s-tempo_s(1,1);

subplot(2,1,1);
plot(tempo_s,temperatura,tempo_s,ones(amostras,1)*53,'r', ...
    tempo_s,ones(amostras,1)*53*1.05,'g',tempo_s,ones(amostras,1)*53*0.95,'g', ...
    tempo_s,ones(amostras,1)*53*1.01,'m',tempo_s,ones(amostras,1)*53*0.99,'m')
legend('temperatura','setpoint(53ºC)','5% em relaçãoo ao setpoin','5% em relaçãoo ao setpoin', ...
    '1% em relaçãoo ao setpoin','1% em relaçãoo ao setpoin');
title ('Controlador Pi(integrador x 5) ');
xlabel ('Tempo(s)');
ylabel ('Temmperatura(C)');
subplot(2,1,2);
plot(tempo_s,erro,tempo_s,zeros(amostras,1),'r', ...
    tempo_s,ones(amostras,1)*53*0.05,'g',tempo_s,ones(amostras,1)*53*-0.05,'g', ...
    tempo_s,ones(amostras,1)*53*0.01,'m',tempo_s,ones(amostras,1)*53*-0.01,'m')
legend('erro','0','5% em relaçãoo ao setpoin','5% em relaçãoo ao setpoin', ...
    '1% em relaçãoo ao setpoin','1% em relaçãoo ao setpoin');
title ('Erro');
xlabel ('Tempo(s)');
ylabel ('Erro');
print -dpng -r300 controlador_pi_5x.png 