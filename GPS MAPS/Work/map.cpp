#include"GPS.h"



int main()
{
	GPS::Point2D a(52.2323132146653, 12.248467365);//где ты
	GPS::Point2D b(52.1324675433442, 12.2324353531);//куда едешь
	GPS::Point2D c(51.2314343435355, 12.34231433677);//куда надо дальше
	GPS::courseAzimuth(a, b, c);//полный азимут
	a.azimuthTo(b); //азиму 2 точек
	a.distanceTo(c); //расстояние 






	return 0;
}