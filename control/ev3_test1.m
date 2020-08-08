%%
mylego=legoev3;
mymotor1= motor(mylego, 'A');
mymotor2= motor(mylego, 'B'); % ���� �ΰ��� ��� ��Ʈ�� ���� A,B�� ����

EXE_TIME = 10; % ���� �ð�
period=0.1; % ���ø� �ֱ�
speed=40; % ���� �ӵ�
p=0.1,i=0,d=0; % ����� ��

mymotor1.Speed =speed;
mymotor2.Speed =speed; % �� ������ ���ǵ� ����

resetRotation(mymotor1);
resetRotation(mymotor2); % ���� ��ġ �ʱ�ȭ

start(mymotor1);
start(mymotor2); % ���� ȸ�� ���� 


t=timer('TimerFcn','stat=false;','StartDelay', EXE_TIME);
start(t); % Ÿ�̸� ����

%%
stat =true;
lastR1=0;
lastR2=0;
speed1=[];
speed2=[];

sumerror=0;
prv_error=0;
while stat==true % Ÿ�̸� �����ϴ� ���� �ش� ���� �ݺ�
   tic();
   r1=readRotation(mymotor1); %���� ���� ��ġ �б�
   r2=readRotation(mymotor2);
   
   speed1=[speed1 (r1-lastR1)/period]; % ���� ���� �ӵ� ���
   speed2=[speed2 (r2-lastR2)/period];
   
   diff=speed1(end)-speed2(end); % �� ���Ͱ��� �ӵ����� ���
   sumerror=sumerror+diff*period;
   drverror=(diff-prv_error)/period;
   mymotor1.Speed=mymotor1.Speed-int8(diff*p)+int8(sumerror*i)+int8(drverror*d); % �ӵ����̸�ŭ �ӵ� ����
   
   lastR1=r1;
   lastR2=r2;
   dt=toc();
   pause(period-dt);
end

stop(mymotor1);
stop(mymotor2);
plot(speed1,'k');hold on;plot(speed2,'r');
clear mylego
clear mymotor1 
clear mymotor2

