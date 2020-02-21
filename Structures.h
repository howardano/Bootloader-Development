#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>
#include <stdio.h>
#include <iostream>

struct Node {
	int node_id = 0;
	double X = 0, Y = 0, Z = 0;
	bool m_is_vertex_node = false;
	Node() {};
	Node(int ID_, double X_, double Y_, double Z_, bool vert);

	bool operator != (const Node& right);

	bool operator == (const Node& right);

	friend std::ostream& operator << (std::ostream& out, Node& in);
};

struct FiniteElement {
	int element_id = 0;
	int material_id = 0;
	std::vector <int> nodes_id;

	friend std::ostream& operator <<(std::ostream& out, FiniteElement& in);
};

struct SurfaceFiniteElement : public FiniteElement {
	int surface_id = 0;
	int border_id = 0;
	friend std::ostream& operator <<(std::ostream& out, SurfaceFiniteElement& in);
};

struct Edge {
	int first_id = 0;
	int last_id = 0;
	int center_id = 0;

	Edge() {};

	Edge(int id1, int id2, int id3);

	void Update_the_central_Node(int id);

	bool operator==(const Edge& right) const;

	bool operator<(const Edge& right) const;
};

#endif