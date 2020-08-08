%%
clear all;
NoOfImg=24;
Xmsaved=zeros(2,NoOfImg);
Xhsaved=zeros(2,NoOfImg);
Xcsaved=zeros(2,NoOfImg);
Xrsaved=zeros(2,NoOfImg);
figure(1)
for k=1:NoOfImg
    % ������ �� ���� ��ȯ
    [xm,ym,rx,ry]=GetBallPos(k);
    % ���� Į�� ���� ����
    [xh,yh]=TrackKalman(xm,ym);
    % R �迭�� ��ȭ��Ų Į������ ����
    [xr,yr]=TrackKalmanQR(xm,ym);
    hold on;
    plot(xm,ym,'r*');
    plot(xh,yh,'bs');
    pause(1)
    
    Xmsaved(:,k)=[xm ym]';
    Xhsaved(:,k)=[xh yh]';
    Xcsaved(:,k)=[rx ry]';
    Xrsaved(:,k)=[xr yr]';
end
% ���ÿ� ���� �� ��ȭ �׷��� ���
figure(2);hold on;
plot(Xmsaved(1,:),Xmsaved(2,:),'r*');
plot(Xhsaved(1,:),Xhsaved(2,:),'bs');
plot(Xrsaved(1,:),Xrsaved(2,:),'bo');
set(gca,'Ydir','reverse');
legend('Object Detection','Kalman Filtere tracking Before QR change',...
    'After QR change','Location','northwest');
box on;
xlabel('x (pixel)');ylabel('y (pixel)');

%%
t=1:NoOfImg;
x1=Xmsaved(1,:);
x2=Xhsaved(1,:);
x3=Xcsaved(1,:);
x4=Xrsaved(1,:);
y1=Xmsaved(2,:);
y2=Xhsaved(2,:);
y3=Xcsaved(2,:);
y4=Xrsaved(2,:);
% x ��ǥ
figure;hold on;plot(t,x1,'r');plot(t,x2,'b');plot(t,x3,'k');plot(t,x4,'g');
legend('detection','kalman before QR change','real','QR change');xlabel('sample Number'),ylabel(' x value (pixel)');
% y ��ǥ
figure;hold on;plot(t,y1,'r');plot(t,y2,'b');plot(t,y3,'k');plot(t,y4,'g');
legend('detection','kalman before QR change','real','QR change','Location','northwest');xlabel('sample Number'),ylabel(' y value (pixel)');

%%
