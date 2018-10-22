#pragma once
#include <string>
using namespace std;

class Point {
public:
	Point(string name,double L, double B) {
		this->name = name;
		this->L = L;
		this->B = B;
	}
	string name;
	double L;
	double B;
};
