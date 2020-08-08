%%
function [pos vel]=DvKalman(z)

persistent A H Q R
persistent x P
persistent firstRun

if isempty(firstRun)
    % �ʱⰪ ����
    firstRun=1;
    dt=0.1;
    A=[1 dt;0 1];
    H=[1 0];
    Q=[1 0;0 3];
    R=10;
    
    x=[0;20];
    P=5*eye(2);
end
% ������ ����
xp=A*x;
% ���� ���л� ����
Pp=A*P*A'+Q;
% Į�� �̵� ���
K=Pp*H'*inv(H*Pp*H'+R);
% ������ ���
x=xp+K*(z-H*xp);
% �������л� ���
P=Pp-K*H*Pp;
% ��ġ
pos=x(1);
% �ӵ�
vel=x(2);