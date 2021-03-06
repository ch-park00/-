%%
A=[2 8 2 14;1 6 -1 13;2 -1 2 5];
for k=1:2
    for i=k+1:3
        m=A(i,k)/A(k,k);
        for j=k+1:4 % 여기서 4열이 존재하므로 4열까지 이동해야한다.
                    % k+1을 하면 a21,a32,a31같은 항이 0으로 소거되지는 않지만
                    % 계산하는데 있어 사용하지 않으므로 문제없음.
                    % 만약 0으로 바꾸고 싶다면 k항부터 시작해야한다.
            A(i,j)=A(i,j)-m*A(k,j);
        end
    end
end

x3=A(3,4)/A(3,3);
x2=(A(2,4)-A(2,3)*x3)/A(2,2);
x1=(A(1,4)-A(1,2)*x2-A(1,3)*x3)/A(1,1);
x=zeros(1,3);
% for루프 이용해 해를 구하기.
for i=3:-1:1
    temp=0;
    if i==3
        x(1,3)=A(3,4)/A(3,3);
    else
        for j=3:-1:i+1
            temp=temp-(A(i,j)*x(1,j));
        end
    end
    x(1,i)=(temp+A(i,4))/A(i,i);
end
