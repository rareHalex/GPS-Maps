#include"GPS.h"



int main()
{
	GPS::Point2D a(52.2323132146653, 12.248467365);//��� ��
	GPS::Point2D b(52.1324675433442, 12.2324353531);//���� �����
	GPS::Point2D c(51.2314343435355, 12.34231433677);//���� ���� ������
	GPS::courseAzimuth(a, b, c);//������ ������
	a.azimuthTo(b); //����� 2 �����
	a.distanceTo(c); //���������� 






	return 0;
}