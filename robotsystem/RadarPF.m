%%
function [pos,vel,alt]=RadarPF(z,dt)
persistent x
persistent firstrun
persistent pt wt
persistent Npt
if isempty(firstrun)
    % �ʱⰪ
    x=[0 90 1100]';
    % ��ƼŬ ����
    Npt=1000;
    % ���Ժ����� ������ ������ �߰�
    pt(1,:)=x(1)+0.1*x(1)*randn(1,Npt);
    pt(2,:)=x(2)+0.1*x(2)*randn(1,Npt);
    pt(3,:)=x(3)+0.1*x(3)*randn(1,Npt);
    wt=ones(1,Npt)*1/Npt;
    firstrun=1;
end
% ��� ��ƼŬ���� �ý��� �𵨿� ����
for k=1:Npt
    pt(:,k)=fx(pt(:,k),dt)+randn(3,1);
end
% ��ƼŬ�� ����ġ ���.�� ����ġ�� ������ z�� ����Ҽ��� ����ġ�� Ŀ���� �ȴ�.
for k=1:Npt
    wt(k)=wt(k)*normpdf(z,hx(pt(:,k)),10);
end
% ������ ���
wt=wt/sum(wt);
x=pt*wt';
pos=x(1);
vel=x(2);
alt=x(3);
% resampling ����(SIR �˰���)
% ���� ��� ����ġ�� ���� ����.
wtc=cumsum(wt);
% 0~1 ���� ���ο� 1000���� ��ƼŬ�� �������� ����
rpt=rand(Npt,1);
% �� ������ �´� ��ƼŬ ���� ����
[~,ind1]=sort([rpt;wtc']);
ind=find(ind1<=Npt)-[0:Npt-1]';
pt=pt(:,ind);
% ����ġ �ʱ�ȭ
wt=ones(1,Npt)*1/Npt;
end
function xp=fx(x,dt)
A=eye(3)+dt*[0 1 0;0 0 0;0 0 0];
xp=A*x;
end
function zp=hx(xhat)

x1=xhat(1);
x3=xhat(3);
zp=sqrt(x1^2+x3^2);
end