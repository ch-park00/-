%%
clear all;
dt=0.05;
t=0:dt:20;

Nsamples=length(t);

Xsaved=zeros(Nsamples,3);
X1saved=zeros(Nsamples,3);
X2saved=zeros(Nsamples,3);
Zsaved=zeros(Nsamples,1);

for k=1:Nsamples
    % ������ ����
    r=GetRadar(dt);
    % ��ƼŬ ���� ������ ���
    [pos,vel,alt]=RadarPF(r,dt);
    % UKF ������ ���
    [pos1,vel1,alt1]=RadarUKF(r,dt);
    % EKF ������ ���
    [pos2,vel2,alt2]=RadarEKF(r,dt);
    % �ռ� ���� ������ ����
    Xsaved(k,:)=[pos vel alt];
    X1saved(k,:)=[pos1 vel1 alt1];
    X2saved(k,:)=[pos2 vel2 alt2];
    % ������ ����
    Zsaved(k)=r;
end

t=0:dt:(Nsamples-1)*dt;
% �ð� ��ȭ�� ���� �ӵ� ��ȭ �׷��� plot
figure(1);
plot(t,Xsaved(:,2),'b');hold on;
plot(t,X1saved(:,2),'r');
plot(t,X2saved(:,2),'k');
legend('particle filter','UKF','EKF','location','northwest');
%legend('particle filter','UKF');
xlabel('Time [sec]');ylabel('Velocity [m/s]');
title('R change');

% �ð� ��ȭ�� ���� ���� ��ȭ �׷��� plot
figure(2);
plot(t,Xsaved(:,3),'b');hold on;
plot(t,X1saved(:,3),'r');
plot(t,X2saved(:,3),'k');
%legend('particle filter','UKF');
legend('particle filter','UKF','EKF','location','northwest');
xlabel('Time [sec]');ylabel('Altitude [m]');
title('R change');

% �ð� ��ȭ�� ���� ��ġ�� ��ȭ �׷��� plot
figure(3);
plot(t,Xsaved(:,1),'b');hold on;
plot(t,X1saved(:,1),'r');
plot(t,X2saved(:,1),'k');
%legend('particle filter','UKF');
legend('particle filter','UKF','EKF','location','northwest');
xlabel('Time [sec]');ylabel('Position [m]');
title('R change');

%%
clear all;
dt=0.05;
t=0:dt:20;

Nsamples=length(t);

Xsaved=zeros(Nsamples,3);
X1saved=zeros(Nsamples,3);
X2saved=zeros(Nsamples,3);
Zsaved=zeros(Nsamples,1);
for k=1:Nsamples
    % ������ ����
    r=GetRadar(dt);
    % ��ƼŬ ���� ������ ���
    [pos,vel,alt]=RadarPF(r,dt);
    % UKF ������ ���
    [pos1,vel1,alt1]=RadarUKF(r,dt);
    % EKF ������ ���
    [pos2,vel2,alt2]=RadarEKF(r,dt);
    % �ռ� ���� ������ ����
    Xsaved(k,:)=[pos vel alt];
    X1saved(k,:)=[pos1 vel1 alt1];
    X2saved(k,:)=[pos2 vel2 alt2];
    % ������ ����
    Zsaved(k)=r;
end

t=0:dt:(Nsamples-1)*dt;
%�ð� ��ȭ�� ���� �ӵ� ��ȭ �׷��� plot
figure(7);
plot(t,Xsaved(:,2));hold on;
plot(t,X1saved(:,2),'r');
plot(t,X2saved(:,2),'k');
legend('particle filter','UKF','EKF','location','northwest');
xlabel('Time [sec]');ylabel('Velocity [m/s]');
title('[0 150 1500]');
% %�ð� ��ȭ�� ���� ���� ��ȭ �׷��� plot
figure(8);
plot(t,Xsaved(:,3));hold on;
plot(t,X1saved(:,3),'r');
plot(t,X2saved(:,3),'k');
legend('particle filter','UKF','EKF','location','northwest');
xlabel('Time [sec]');ylabel('Altitude [m]');
title('[0 150 1500]');
% title('particle=1000');
% 
% %�ð� ��ȭ�� ���� ��ġ�� ��ȭ �׷��� plot
figure(9);
plot(t,Xsaved(:,1));hold on;
plot(t,X1saved(:,1),'r');
plot(t,X2saved(:,1),'k');
% %legend('particle filter','UKF');
% legend('10','100','10000');
legend('particle filter','UKF','EKF','location','northwest');
xlabel('Time [sec]');ylabel('Position [m]');
title('[0 150 1500]');