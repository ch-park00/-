A=[0.7 0.1 0;0.2 0.9 0.2;0.1 0 0.8];
x=[25 20 55]';
y=A*x;
z=A*y;
u=A*z;
t=[2004 2009 2014 2019];
plot(t, [x y z u]);
hold on;
plot(t,[x(1) y(1) z(1) u(1)],'d','color','b');
plot(t,[x(2) y(2) z(2) u(2)],'o','color','r');
plot(t,[x(3) y(3) z(3) u(3)],'*','color','k');
xlabel('year');
ylabel('percentage');
legend('C','I','R');
text(2014,30,'201401653 ��ö��');