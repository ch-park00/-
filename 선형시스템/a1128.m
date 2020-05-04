%% image �о����
s=[];
M=27;
icol=92;irow=112;
N=icol*irow;

for i=1:M
   img=imread(['C:\Users\chpark\Documents\MATLAB\PCA\database\training\' num2str(i,'%03g') '.bmp']);
   img=img(:,:,1);
   temp=reshape(img',N,1);
   temp=double(temp);
   s=[s temp];
end
%% ���� ��� �л� ���ϰ� ǥ��ȭ(-128~128�� ������ ����)��Ű��
X=zeros(N,M);
for i=1:M
   temp=s(:,i);
   m=mean(temp);
   st=std(temp);
   Z=(temp-m)/st;
   X(:,i)=Z*128+128; %s=128+128*z
   
end
%�̹��� ���
figure(2);
for i=1:M
   img=reshape(X(:,i),icol,irow);
   img=uint8(img');
   subplot(ceil(sqrt(M)),ceil(sqrt(M)),i);
   imshow(img);
end
%% �� ��� ���ϱ�
m=mean(X,2);
img=reshape(m,icol,irow);
img=uint8(img');
 figure(3);
 imshow(img);
 title('��� ��','fontsize',12);
%A�� ����� ������
A=zeros(N,M);
for i=1:M
   A(:,i)=double(X(:,i))-m; 
end

%% ���л���� ���ϰ� eigenvector�� eigenvalue���ϱ�
%10304���� eigenvalue�� ���´�.-->��귮�� �ʹ� �����Ƿ� ����
L=A'*A/(M-1);
[v,lamda]=eig(L);

[lamda,index]=sort(lamda);
vtemp=zeros(size(v));
len=length(index);
for i=1:len
    vtemp(:,i)=v(:,len+1-index(i));
end
V=vtemp;
%U=A*v_i
U=[];
for i=1:size(V,2)
   U=[U (A*V(:,i))];
end

U_norm=[];
for i=1:size(U,2)
   U_norm(:,i)=U(:,i)./norm(U(:,i)); 
end

%%

 figure(4);
 for i=1:size(U_norm,2)
    img=reshape(U_norm(:,i),icol,irow);
    img=img';
    img=histeq(img,255);
    subplot(ceil(sqrt(M)),ceil(sqrt(M)),i);
    imshow(img);
 end

%% 
omega=[];
for h=1:size(A,2)
   ww=[];
   for i=1:size(U_norm,2)
      weightofimage=dot(A(:,h),U_norm(:,i));
      ww=[ww;weightofimage];
   end
   omega=[omega ww];
end

%%
cnt=0;
for zz=1:M

    %Inputimage=input('�ν��� ���� ��ȣ�� �Է��ϼ���\n');
Inputimage=imread(['C:\Users\chpark\Documents\MATLAB\PCA\database\test\' num2str(zz,'%03g') '.bmp']);
Inputimage=Inputimage(:,:,1);
temp=reshape(double(Inputimage)',irow*icol,1);
me=mean(temp);
st=std(temp);
Z=(temp-me)/st;
x_hat=Z*128+128;
a_hat=x_hat-m;
omega_h=[];
for i=1:M
   o=dot(a_hat,U_norm(:,i));
   omega_h=[omega_h; o];
end
e=[];
for i=1:size(omega,2)
   mag=norm(omega_h-omega(:,i));
   e=[e mag];
end
[temp idx]=min(e);
disp([num2str(zz), '�� ���Է��� ' num2str(idx), '�� �󱼵����ͷ� �νĵǾ����ϴ�']);
if idx==zz
   cnt=cnt+1; 
end

end
disp(['�� �νķ��� ' num2str(cnt/M*100), '%�Դϴ�']);
