%%
function vel=Getvel()

persistent Velp Posp

if isempty(Posp)
    Posp=0;
    Velp=80;
end

dt=0.1;
w=0+10*randn;
% ��ġ=���� ��ġ+�ӵ�*�ð�
Posp=Posp+Velp*dt;
% ������ ���� �ӵ� ������
Velp=80+w;
vel=Velp;
