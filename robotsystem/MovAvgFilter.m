function avg=MovAvgFilter(x)

persistent prevAvg n xbuf
persistent firstrun

if isempty(firstrun)
    % �̵���� ������ ����� �ٲٰ� ���� ���, n���� ����
    n=10;
    xbuf=x*ones(n+1,1);
    k=1;
    prevAvg=x;
    firstrun=1;
end

for m=1:n
    xbuf(m)=xbuf(m+1);
end
xbuf(n+1)=x;

avg=prevAvg+(x-xbuf(1))/n;

prevAvg=avg;

