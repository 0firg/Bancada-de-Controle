arquivo=load('zn_38_53_p.txt');%le o arquivo com os dados

amostras=size(arquivo);%identifica a quantidade de dados
amostras=amostras(1,1);%salva a quantidade de dados

temperatura=arquivo(:,1);
setpoint=arquivo(:,2);
erro=arquivo(:,3);
tempo_s=arquivo(:,4);
entrada_lamp=arquivo(:,5);

tempo_s=tempo_s-tempo_s(1,1);

subplot(2,1,1);
plot(tempo_s,temperatura,tempo_s,ones(amostras,1)*45,'g',tempo_s,ones(amostras,1)*53,'r')
legend('temperatura','valor maximo atingido','setpoint');
title ('Controlador P ');
xlabel ('Tempo(s)');
ylabel ('Temmperatura(C)');
subplot(2,1,2);
plot(tempo_s,erro,tempo_s,zeros(amostras,1),'r')
legend('erro','0');
title ('Erro');
xlabel ('Tempo(s)');
ylabel ('Erro');
print -dpng -r300 controlador_p.png 