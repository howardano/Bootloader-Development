#ifndef ANEUMESHLOADER_H
#define ANEUMESHLOADER_H

#include "Exceptionen.h"
#include "Structures.h"
#include "Algorithm.h"
#include <unordered_set>
#include <exception>
#include <functional>
#include <iostream>
#include <set>
#include <iomanip>
#include <fstream>

template <class T>
inline void hashCombine(std::size_t& seed, const T& v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename _T>
inline void hashVal(std::size_t& o_seed, const _T& p_val) {
	hashCombine(o_seed, p_val);
}

template <typename _Types>
inline std::size_t hashVal(const _Types& edge1, const _Types& edge2) {
	std::size_t seed = 0;
	hashVal(seed, edge1);
	hashVal(seed, edge2);
	return seed;
}

class MyHashFunction {
public:
	std::size_t operator() (const Edge& ed) const {
		return hashVal(ed.first_id > ed.last_id ? ed.first_id : ed.last_id, ed.first_id > ed.last_id ? ed.last_id : ed.first_id);
	}
};

class MeshLoader {
protected:
	std::vector<Node> nodes;
	std::vector<FiniteElement> elements;
	std::vector<SurfaceFiniteElement> surfaces;
public:
	virtual void LoadMesh() {};
};

class AneuMeshLoader : MeshLoader {
public:
	void put_in_center();

	/*void print_Node();

	void print_FiniteElement();

	void print_SurfaceFiniteElement();*/

	const std::vector<Node>& get_nodes() const;

	const std::vector<FiniteElement>& get_elements() const;

	const std::vector<SurfaceFiniteElement>& get_surface() const;

	const std::vector<FiniteElement> get_the_element_by_ID(int id1, int id2, int id3) const;

	const std::vector<FiniteElement> get_the_ki_by_material(int mat) const;

	const std::vector<Node> get_the_nodes_of_surface_by_ID(int border_i) const;

	const std::vector<SurfaceFiniteElement> get_the_surfaceki_by_surfaceID(int id) const;

	void LoadMesh(const std::string& filename);

	const std::vector<FiniteElement> get_the_element_by_edge(int id1, int id2) const;

	std::vector<std::vector<Node>> Get_Neighbours();

	const int Get_The_Last() const;

	const Node Get_the_Node(int id) const;

	friend std::ostream& operator << (std::ostream& out, AneuMeshLoader& in);
};

std::ostream& operator << (std::ostream& out, std::vector<Node>& ino);

std::ostream& operator << (std::ostream& out, std::vector<FiniteElement>& ino);

std::ostream& operator << (std::ostream& out, std::vector<SurfaceFiniteElement>& ino);

#endif