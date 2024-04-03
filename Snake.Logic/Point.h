#pragma once
#include <string>

struct point { 
	int x, y; 

	point();
	point(int, int);
	std::string ToString() const;

	bool operator==(const point&) const;
	bool operator!=(const point&) const;
	point operator +(const point&) const;
	point operator *(const int&) const;

};

