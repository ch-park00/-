%%
function [z vel]=GetPos()

persistent Velp Posp

if isempty(Posp)
    Posp=0;
    Velp=80;
end

dt=0.1;
% ������
w=0+10*randn;
v=0+10*randn;
% ��ġ=������ġ*�ӵ�*�ð�+������
z=Posp+Velp*dt+v;
% ������ ���� ����
Posp=z-v;
% �ӵ�
Velp=80+w;
vel=Velp;

