#include "Vertex.h"

void Vertex::copy_neighbors(int* neighbors)
{
	if (_neighbors != nullptr)
		delete_neighbors();

	_neighbors = new int[_neighbor_count];
	for (int x = 0; x < _neighbor_count; x++)
		_neighbors[x] = neighbors[x];
}

void Vertex::create_neighbors()
{
	if (_neighbors != nullptr)
		delete_neighbors();

	_neighbors = new int[_neighbor_count];
	iter = 0;	//reset iterator
}

void Vertex::delete_neighbors()
{
	if (_neighbors == nullptr) return;

	delete[] _neighbors;
	_neighbors = nullptr;
}

Vertex::Vertex(const int& neighbor_count, int* neighbors): _neighbor_count(neighbor_count)
{
	copy_neighbors(neighbors);
}

Vertex::~Vertex()
{
	delete_neighbors();
}

Vertex& Vertex::operator=(const Vertex& other)
{
	if (this == &other) return *this;

	this->set_neighbor_count(other._neighbor_count);
	this->copy_neighbors(other._neighbors);

	return *this;
}

void Vertex::set_neighbor_count(const int& count)
{
	delete_neighbors();
	_neighbor_count = count;
	create_neighbors();
}

void Vertex::add(const int& neighbor_id)
{
	if (iter >= _neighbor_count) return;

	_neighbors[iter++] = neighbor_id;
}
