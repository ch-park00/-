function xlpf=LPF(x)

persistent prevX
persistent firstrun

if isempty(firstrun)
   prevX=x;
   
   firstrun=1;
end
% ���İ� ��ȭ�� ���� �м�, �̵���� ���Ϳ����� ������ �߻��ϴ� ���� ����
alpha=0.9;
xlpf=alpha*prevX+(1-alpha)*x;

prevX=xlpf;