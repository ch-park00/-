%%
function [Xi W]=sigmaPoints(xm,P,kappa)
n=numel(xm);
Xi=zeros(n,2*n+1);
W=zeros(n,1);

Xi(:,1)=xm;
W(1)=kappa/(n+kappa);
% cholesky ��ȯ ������ ui������ ���ϱ�
U=chol((n+kappa)*P);

% 1~n��° ����
for k=1:n
    Xi(:,k+1)=xm+U(k,:)';
    W(k+1)=1/(2*(n+kappa));
end
% n+1~2n+1�� ����
for k=1:n
    Xi(:,n+k+1)=xm-U(k,:)';
    W(n+k+1)=1/(2*(n+kappa));
end
