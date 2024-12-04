#include "HexCoord.h"

double HexCoord::distance(const HexCoord& other)
{
    HexCoord vec = *this - other;
    return (abs(vec.q) + abs(vec.r) + abs(vec.s)) / 2.0;
}

HexCoord HexVectors::NorthWest = HexCoord(0, -1, 1);
HexCoord HexVectors::NorthEast = HexCoord(1, -1, 0);
HexCoord HexVectors::West = HexCoord(-1, 0, 1);
HexCoord HexVectors::East = HexCoord(1, 0, -1);
HexCoord HexVectors::SouthWest = HexCoord(-1, 1, 0);
HexCoord HexVectors::SouthEast = HexCoord(0, 1, -1);
HexCoord HexVectors::Vectors[6] = {
    HexVectors::NorthWest,
    HexVectors::NorthEast,
    HexVectors::East,
    HexVectors::SouthEast,
    HexVectors::SouthWest,
    HexVectors::West
};

AxialVectors AxialVectors::NorthWest = { 0,-1 };
AxialVectors AxialVectors::NorthEast = { 1,-1 };
AxialVectors AxialVectors::West = { -1,0 };
AxialVectors AxialVectors::East = { 1,0 };
AxialVectors AxialVectors::SouthWest = { -1,1 };
AxialVectors AxialVectors::SouthEast = { 0,1 };
AxialVectors AxialVectors::Vectors[6] = {
    AxialVectors::NorthWest,
    AxialVectors::NorthEast,
    AxialVectors::East,
    AxialVectors::SouthEast,
    AxialVectors::SouthWest,
    AxialVectors::West
};
