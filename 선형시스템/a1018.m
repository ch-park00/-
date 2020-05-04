%%
d=[0 5 5 0 -5 5 0 -5 -5 0 5 -5 0;...
    0 -5 5 0 5 5 0 5 -5 0 -5 -5 0;...
    20 0 0 20 0 0 -20 0 0 -20 0 0 20;...
    1 1 1 1 1 1 1 1 1 1 1 1 1];
% p�� ������ ���͹�ȣ�� �ǹ�
p=[1 2 3;4 5 6;5 6 7;8 9 10;9 10 11;11 12 13;1 8 9;2 3 7];
c=['b';'r';'g';'w';'k';'c';'m';'y'];
%%
orbit=[0,0,20];
for x1=0:0.15:20
    clf;
    psi=4*pi*x1/20; %x1�� 20��ŭ �̵��ϴ� ���� 4pi��ŭ ȸ��

    Rz_u=[cos(psi) -sin(psi) 0 x1;sin(psi) cos(psi) 0 0;0 0 1 0;0 0 0 1];
    y=Rz_u*d;
    line([y(1,:) y(1,1)], [y(2,:) y(2,1)],[y(3,:) y(3,1)]);
    line([40 0 0],[0 0 0],[0 0 0],'color','r');
    line([0 0 0],[0 40 0],[0 0 0],'color','g');
    line([0 0 0],[0 0 0],[0 0 40],'color','k');
    
    orbit=[orbit;y(1,1) y(2,1) y(3,1)]; %����ø��� orbit�����Ͱ� �߰���(ũ�Ⱑ Ŀ��)
    line(orbit(:,1), orbit(:,2),orbit(:,3));
    
    for i=1:1:8
       patch([y(1,p(i,1)) y(1,p(i,2)) y(1,p(i,3))], [y(2,p(i,1)) y(2,p(i,2)) y(2,p(i,3))],...
          [y(3,p(i,1)) y(3,p(i,2)) y(3,p(i,3))],c(i));
    end
   xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');
   axis([-60 60 -60 60 -60 60]);grid;
   pause(0.000001);
end

%% x3�̵��ϸ鼭 yaw(�̵� �Ÿ��� ����)
x3=0;orbit=[20,0,20];
for deg=0:2:720
    clf;
    x1=20*cos(deg*pi/180)+randn(1); % �� �κп� �������� �������μ� step�� �����ϰ� �߻���Ų��
    x2=20*sin(deg*pi/180)+randn(1); %
    x3=x3-20/361+randn(1);          %
    psi=8*deg*pi/180; %���� 2����
    Rz_round=[cos(psi) -sin(psi) 0 x1;sin(psi) cos(psi) 0 x2;0 0 1 x3;0 0 0 1];
    y=Rz_round*d;
    line([y(1,:) y(1,1)], [y(2,:) y(2,1)],[y(3,:) y(3,1)]);
    line([60 0 0],[0 0 0],[0 0 0],'color','r');
    line([0 0 0],[0 60 0],[0 0 0],'color','g');
    line([0 0 0],[0 0 0],[0 0 60],'color','k');
    
    orbit=[orbit;y(1,1) y(2,1) y(3,1)];
    line(orbit(:,1), orbit(:,2),orbit(:,3));
    
    for i=1:1:8
       patch([y(1,p(i,1)) y(1,p(i,2)) y(1,p(i,3))], [y(2,p(i,1)) y(2,p(i,2)) y(2,p(i,3))],...
          [y(3,p(i,1)) y(3,p(i,2)) y(3,p(i,3))],c(i));
    end
   xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');
   axis([-60 60 -60 60 -60 60]);grid;
   pause(0.000001);
end

%%
x3=0;
orbit=[0,0,20];
vpoint=[60,60,60]; % ���� �ٶ󺸴� ��ǥ
vgain=10000;

for x1=0:0.15:20
   clf;
   psi=4*pi*x1/20;
      Rz_u=[cos(psi) -sin(psi) 0 x1;sin(psi) cos(psi) 0 0;0 0 1 0;0 0 0 1];

   y_before=Rz_u*d;
   dist_vpoint=sqrt((y_before(1,1)-vpoint(1))^2+(y_before(2,1)-vpoint(2))^2+(y_before(3,1)-vpoint(3))^2);
   
   
   
   y=y_before./(dist_vpoint^2).*vgain;
   
   line([y(1,:) y(1,1)],[y(2,:) y(2,1)],[y(3,:) y(3,1)]);
   line([40,0,0],[0 0 0],[0 0 0],'color','r');
   line([0,0,0],[0 40 0],[0 0 0],'color','g');
   line([0,0,0],[0 0 0],[0 0 40],'color','k');
   orbit=[orbit;y(1,1) y(2,1) y(3,1)];
   line(orbit(:,1),orbit(:,2),orbit(:,3));
   
   for i=1:1:8
       patch([y(1,p(i,1)) y(1,p(i,2)) y(1,p(i,3))], [y(2,p(i,1)) y(2,p(i,2)) y(2,p(i,3))],...
          [y(3,p(i,1)) y(3,p(i,2)) y(3,p(i,3))],c(i));
   end
    
   xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');
   axis([-60 60 -60 60 -60 60]);
   view([60 60 60]);grid;
   pause(0.00001);
end

%% 145 ����
