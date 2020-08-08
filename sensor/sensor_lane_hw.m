%% 
clear;
% ���� �б�
img_ori=imread('lane0511.jpg');
% rgb 3ä���� ���� 1ä�η� ����.
img_gray=rgb2gray(img_ori);
% ���� ����� ���� �ڷ����� double�� ����
img_gray=double(img_gray); 
col=length(img_gray(:,1));
row=length(img_gray(1,:));
% ���� �� �Ʒ��� ���ݸ� ���
img_gray=img_gray(col/2:col,1:row);
figure(1);clf;imshow(uint8(img_gray))
% ����þ� ����. ������=5, ��=5
g1=fspecial('gaussian',[3 3],5);
% �̹����� ����þ� ���� ����. �̹����� �ణ �� ó���Ǹ鼭
% ����� �״´�.
img1=filter2(g1,img_gray,'same');
% �Һ� ����ũ�� ���� �������� ������ �����Ѵ�
sobelMaskx=[-1,0,1;-2,0,2;-1,0,1];
sobelMasky=[1,2,1;0,0,0;-1,-2,-1];
G_X=conv2(img1,sobelMaskx,'same');
G_Y=conv2(img1,sobelMasky,'same');
magnitude=(G_X.^2)+(G_Y.^2);
%  ��Ŭ���� �Ÿ��� ����=> �밢�� �Ÿ��� ����.(edge�� ũ��=����(�󸶳� �������)�� Ȯ���Ѵ�.)
magnitude=sqrt(magnitude); 
theta=atan2(G_Y,G_X);
theta=theta*180/pi;
col=length(img_gray(:,1));
row=length(img_gray(1,:));
% atan2 ��°��� ������ ��쵵 �����Ƿ� �� ��� 360�� ���� theta���� 0~360 ���̷� ������ش�.
for i=1:col
        for j=1:row
            if (theta(i,j)<0)
                theta(i,j)=360+theta(i,j);
            end
        end
end
qtheta=zeros(col,row);
for i=1:col
    for j=1:row
        if (((theta(i,j)>=0) && (theta(i,j) <22.5)) ||...
                ((theta(i,j)>=157.5) && (theta(i,j)<202.5)) ||...
                ((theta(i,j)>=337.5) && (theta(i,j)<=360)))
            qtheta(i,j)=0;
        elseif (((theta(i,j)>=22.5) && (theta(i,j) <67.5)) ...
                || ((theta(i,j)>=202.5) && (theta(i,j)<247.5)))
            qtheta(i,j)=1;
        elseif (((theta(i,j)>=67.5) && (theta(i,j) <112.5))...
                || ((theta(i,j)>=247.5) && (theta(i,j)<292.5)))
            qtheta(i,j)=2;
        elseif (((theta(i,j)>=112.5) && (theta(i,j) <157.5)) ...
                || ((theta(i,j)>=292.5) && (theta(i,j)<337.5)))
            qtheta(i,j)=3;
        end
    end
end
% �տ��� ���� theta���� �������� ������ ���� �ش� ������ �ش��ϴ� ���� �Ű� �׷�ȭ.
% �ֺ� �ȼ��� ���� �Ǵ�
BW=zeros(col,row);
for i=2:col-1
    for j=2:row-1
        % ������� ����
        if (qtheta(i,j)==0)
            BW(i,j)=(magnitude(i,j)==max([magnitude(i,j),magnitude(i,j+1),magnitude(i,j-1)]));
        % 3�ù������� ��� ����
        elseif (qtheta(i,j)==1)
            BW(i,j)=(magnitude(i,j)==max([magnitude(i,j),magnitude(i+1,j-1),magnitude(i-1,j+1)]));
        % �������� ����
        elseif (qtheta(i,j)==2)
            BW(i,j)=(magnitude(i,j)==max([magnitude(i,j),magnitude(i+1,j),magnitude(i-1,j)]));
        % 9�ù��� ����
        elseif (qtheta(i,j)==3)
            BW(i,j)=(magnitude(i,j)==max([magnitude(i,j),magnitude(i+1,j+1),magnitude(i-1,j-1)]));
        end
    end
end
BW=BW.*magnitude;
% �ּ� �Ӱ����� �ִ� �Ӱ����� ����.
T_min=0.1;T_max=0.4;
T_min=T_min* max(max(BW));T_max=T_max* max(max(BW)); %2D�� �ִ밪 ã��.
edge_final=zeros(col,row);
for i=1:col
    for j=1:row
        % ���� �Ӱ��� �̸�
        if (BW(i,j)<T_min) 
            edge_final(i,j)=0;
        % �ִ� �Ӱ��� �ʰ�
        elseif (BW(i,j)>T_max) 
            edge_final(i,j)=1;
        % �� �߰��� �ִ� ��� ������ edge�� �ȼ��� �ִ��� ���� �Ǵ�
        elseif (BW(i+1,j)>T_max || BW(i-1,j)>T_max || BW(i,j+1)>T_max ...
                || BW(i,j-1)>T_max || BW(i-1,j-1)>T_max || BW(i-1,j+1)>T_max || ...
                BW(i+1,j+1)>T_max || BW(i+1,j-1)>T_max) %�ڽ� �̿��� 8���� �α� �ȼ��� �ִ� �Ӱ��� �ʰ��� ���� �ȼ� ������ ���.
            edge_final(i,j)=1;
        end
    end
end
% ��� ���
img_canny=uint8(edge_final.*255);
output_img=img_canny;
figure();clf;imshow(output_img);title('size=3,\sigma=5,max=0.4,min=0.1');
%% ��Ʈ���� ����Ǿ� �ִ� edge�Լ� ����� edge ����.
img_ori=imread('lane0511.jpg');
img_gray=rgb2gray(img_ori);
img_gray=img_gray(length(img_gray(:,1))/2:end,1:end);
img_edge=edge(img_gray,'Canny',[0.1 0.2],0.5);
figure();imshow(img_edge);
