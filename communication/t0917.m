%%
N=10000; %���ǹ��� ���� ������ ���ؼ��� 10000������ �������Ѵ�
x=rand(N,1);
histogram(x,'normalization','pdf')

%%
a=100;b=200;
x=rand(10000,1);
y=a+(b-a)*x;
histogram(y,'normalization','pdf')
m=mean(y);
s=var(y);
s=std(y);
Y=2*y;Z=4*y-2;
m1=mean([Y Z])
v1=var([Y Z])
s1=std([Y Z])

%%
N=1e5;
x=randn(N,1);
histogram(x,'normalization','pdf');
xx=linspace(-5,5,100);
f=pdf('Normal',xx,0,1); %normal����,xx�� ��������,���0,ǥ������1
hold on;
plot(xx,f,'Linewidth',2);
grid on;

%%
load rpdata z;
m=mean(z);s=std(z);
histogram(z,'normalization','pdf');
x=linspace(min(z),max(z),100);
f=pdf('Normal',x,m,s);
hold on;
plot(x,f,'r-','Linewidth',2)
