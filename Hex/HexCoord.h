#pragma once
#include <math.h>

//cubical hex coordinates
class HexCoord
{
private:
public:
	int q, r, s;
	HexCoord() :q(0), r(0), s(0) {}
	HexCoord(const int& coordQ, const int& coordR, const int& coordS) :q(coordQ), r(coordR), s(coordS) {}

	/*functions*/
	void add(const HexCoord& other) { q += other.q; r += other.r; s += other.s; }
	void subtract(const HexCoord& other) { q -= other.q; r -= other.r; s -= other.s; }
	double distance(const HexCoord& other);

	/*operator overloading*/
	HexCoord operator+(const HexCoord& other) const
	{ 
		HexCoord res;
		res.q = q + other.q;
		res.r = r + other.r;
		res.s = s + other.s;
		return res;
	}
	HexCoord& operator+=(const HexCoord& other) { this->add(other); return *this; }
	HexCoord operator-(const HexCoord& other) const
	{
		HexCoord res;
		res.q = q - other.q;
		res.r = r - other.r;
		res.s = s - other.s;
		return res;
	}
	HexCoord& operator-=(const HexCoord& other) { this->subtract(other); return *this; }
};

//class containing static hex vectors to properly move on hex plane
struct HexVectors 
{
	static HexCoord NorthWest;
	static HexCoord NorthEast;
	static HexCoord West;
	static HexCoord East;
	static HexCoord SouthEast;
	static HexCoord SouthWest;
	static HexCoord Vectors[6];
};

//class containing static axial vectors to proerly move on hex plane -> used to move properly on the hex array
struct AxialVectors
{
	int p, q;
	static AxialVectors NorthWest;
	static AxialVectors NorthEast;
	static AxialVectors West;
	static AxialVectors East;
	static AxialVectors SouthEast;
	static AxialVectors SouthWest;
	static AxialVectors Vectors[6];
};