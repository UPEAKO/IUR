#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <vector>
#include "Point.h"
using namespace std;

const double PI = 3.1415926535;

string doubleToString(double d) {
	stringstream ss;
	ss.precision(DBL_DECIMAL_DIG);
	ss << d;
	return ss.str();
}

string line(double L, double B) {
	 return doubleToString(L) + "," + doubleToString(B) + "," + doubleToString(0);
}

int main() {
	//所有点
	vector<Point> points;
	ifstream f;
	f.open("E:/work/points.txt");
	double L1, B1, Ve, Vn;
	f >> L1 >> B1 >> Ve >> Vn;
	points.push_back(Point("start",L1, B1));
	//另一端点处经度度增加值 1:100万 1度->111km
	double signNum = (10 * PI) / (111 * 180);
	//另一端点处 L B
	double L2 = L1 + Ve * signNum * cos(B1);
	double B2 = B1 + Vn * signNum;
	points.push_back(Point("end",L2, B2));
	
	double multi = 0.9;
	double tempL = L1 + Ve * signNum * cos(B1) * multi;
	double tempB = B1 + Vn * signNum * multi;
	points.push_back(Point("temp", tempL, tempB));
	//所需两点
	double multi1 = 0.1;
	double arrowL1 = tempL + cos(tempB) * signNum * Vn * multi1;
	double arrowB1 = tempB - signNum * Ve * multi1;
	points.push_back(Point("arrow1", arrowL1, arrowB1));
	double arrowL2 = tempL - cos(tempB) * signNum * Vn * multi1;
	double arrowB2 = tempB + signNum * Ve * multi1;
	points.push_back(Point("arrow2", arrowL2, arrowB2));

	ofstream ofs("E:/work/pointsResult.kml");
	string s1 = R"(<?xml version="1.0" encoding="UTF-8"?>
<kml xmlns = "http://www.opengis.net/kml/2.2">
  <Document>
    <name>lines</name>
    <Style id="sign1">
      <LineStyle>
        <color>ff0000ff</color>
	    <width>0.5</width>
      </LineStyle>
    </Style>
      <Placemark>
        <name>line1</name>
        <styleUrl>#sign1</styleUrl>
        <LineString>
           <coordinates>
    )";
	string s2 = R"(
           </coordinates>
         </LineString>
      </Placemark>
    )";
	string s3 = R"(
 </Document>
</kml>
    )";
	ofs << s1;
	ofs << "         " + line(L1,B1) << endl;
	ofs << "             " + line(L2,B2) << endl;
	ofs << "             " + line(arrowL1,arrowB1) << endl;
	ofs << "             " + line(L2,B2) << endl;
	ofs << "             " + line(arrowL2,arrowB2);
	ofs << s2;
	/*
	for (int i = 0; i < points.size(); i++) {
		ofs << R"(<Placemark>
		  <name>)";
		ofs << points.at(i).name;
		ofs << R"(</name>
		  <Point>
			  <coordinates>)";
		ofs << line(points.at(i).L, points.at(i).B);
		ofs << R"(</coordinates>
		  </Point>
	  </Placemark>)";
	}
	*/
	ofs << s3 << endl;
	system("pause");
	return 0;
}

//此方式废了
/*
    //直角边
	double rLen = 1;
	//斜率1
	double k1 = Vn / Ve;
	//垂直斜率
	double k2 = -1 / k1;
	//返回箭头0.3cm处LB
	double tempL = L2 - cos(B2) *signNum * rLen * Ve / sqrt(Ve * Ve + Vn * Vn);
	double tempB = B2 - signNum * rLen * Vn / sqrt(Ve * Ve + Vn * Vn);
	points.push_back(Point("temp", tempL, tempB));
	cout << tempL << "," << tempB << endl;
	//所需两点
	double arrowL1 = tempL + cos(tempB) * rLen * signNum;
	double arrowB1 = tempB - k2 * rLen * signNum;
	points.push_back(Point("arrow1", arrowL1, arrowB1));
	double arrowL2 = tempL - cos(tempB) * rLen * signNum;
	double arrowB2 = tempB + k2 * rLen * signNum;
	points.push_back(Point("arrow2", arrowL2, arrowB2));
*/


//大概可以
/*
//arrow
	double Len = 1;
	double alpha = atan(Ve / Vn);//仿测量学
	double alpha1 = alpha - (PI - PI / 4);
	if (alpha1 < 0)
		alpha1 += 2 * PI;
	double arrowL1 = L2 + Len * sin(alpha1) * signNum * cos(B2);
	double arrowB1 = B2 + Len * cos(alpha1) * signNum;
	double alpha2 = alpha + (PI - PI / 4);
	points.push_back(Point("arrow1", arrowL1, arrowB1));
	if (alpha1 > 2 * PI)
		alpha1 -= 2 * PI;
	double arrowL2 = L2 + Len * sin(alpha2) * signNum * cos(B2);
	double arrowB2 = B2 + Len * cos(alpha2) * signNum;
	points.push_back(Point("arrow2", arrowL2, arrowB2));
*/


//大概可以
/*
    double multi = 0.9;
	double tempL = L1 + Ve * signNum * cos(B1) * multi;
	double tempB = B1 + Vn * signNum * multi;
	points.push_back(Point("temp", tempL, tempB));
	//所需两点
	double multi1 = 10;
	double arrowL1 = tempL + cos(tempB) * signNum * Vn /multi1;
	double arrowB1 = tempB - signNum * Ve / multi1;
	points.push_back(Point("arrow1", arrowL1, arrowB1));
	double arrowL2 = tempL - cos(tempB) * signNum * Vn / multi1;
	double arrowB2 = tempB + signNum * Ve / multi1;
	points.push_back(Point("arrow2", arrowL2, arrowB2));
*/