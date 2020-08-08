%% 
panel=imread('Panel1_fix.jpg'); % ����� �г� �̹���
point=imread('point_fix.jpg'); % ����� �ٴ� �̹���
handle=imread('handle.jpg'); % �ڵ� �̹���

load temp.txt; % can ������ �ҷ�����
rpmdata=temp(:,2); % can data �� RPM�� ���� ������
rot_point=round(-0.03*rpmdata); % RPM �ٴ� ���� ��� 
d_len=length(rot_point);
figure()
for i=1:9:d_len % ������� ��ũ ����
    point2=imrotate(point,rot_point(i,1)); % ����� RPM�� �°� ȸ��
    handle2=imrotate(handle,temp(i,1)); % �ڵ� ȸ��
    len_pt2=round(length(point2)/2);
    len=round(length(handle2)/2);
   if len_pt2~=300 % �̹��� ũ�� ����
      point2=point2(len_pt2-299:len_pt2+300,len_pt2-299:len_pt2+300,:);
   end
   if len~=125 % �̹��� ũ�� ����
       handle2=handle2(len-124:len+125,len-124:len+125,:);
   end
    final=point2+panel; % �ٴð� ����� �ռ�
    subplot(211);imshow(final);
    subplot(212);imshow(handle2);
    pause(0.01);
end