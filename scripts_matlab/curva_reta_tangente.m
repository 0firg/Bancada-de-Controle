%este script gera apenas a curva de reação, com as temperaturas
%estacionarias antes e apos io degrau destacadas e mommmento do degrau
%destacado bem como acurva original e sua versao suavizada
%o degaru foi de 35 ate 50 de um fundo de escala de 0 a 100

arquivo=load('curva_30_45.txt');%le o arquivo com os dados

amostras=size(arquivo);%identifica a quantidade de dados
amostras=amostras(1,1);%salva a quantidade de dados

temperatura=arquivo(:,1);%numero de amostras feitas
tempo_s=arquivo(:,2);%tempo em que cada amostra foi feita
entrada_lamp=arquivo(:,3);%intensidade lampada no momento da amostra

temp_suavizada=smooth(temperatura,50);
tempo_s=tempo_s-tempo_s(1,1);

media=0;
tamanho_m=0;
for i=1:amostras                 
    if temperatura(i,1) >= 53.53
       media=temperatura(i,1) + media;
       tamanho_m=tamanho_m+1;
    end
end
media =media/tamanho_m;

d_y=diff(temp_suavizada);
ponto_inflec=find(d_y==max(d_y));
t_inflec=ponto_inflec;

a=d_y(t_inflec(1,1));
b=(temp_suavizada(t_inflec(1,1))-a*tempo_s(t_inflec(1,1)));
reta_t_x=(tempo_s(205,1):0.1:tempo_s(430,1));
reta_t_y=a*reta_t_x+b;
temp_ant=zeros(1,amostras)+48.37;
temp_dep=zeros(1,amostras)+53.53;


clf;
plot(tempo_s,temperatura,tempo_s,temp_suavizada,tempo_s,temp_ant,tempo_s,temp_dep, ...
    [2 2],[48.37 53.53],reta_t_x,reta_t_y)
% yline(media)
%xline(2315.49)
legend('temperatura','temperatura suavizada', ...
    'temperatura acomodada antes do degrau','temperatura acomodada depois do degrau','momento do degrau','reta tangente ao ponto');
title ('Curva de reação com reta tangete');
xlabel ('Tempo(s)');
ylabel ('Temmperatura(C)');
print -dpng -r300 curva_tangente.png  