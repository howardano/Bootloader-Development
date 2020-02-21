#include "Structures.h"

Node::Node(int ID_, double X_, double Y_, double Z_, bool vert) {
	node_id = ID_;
	X = X_;
	Y = Y_;
	Z = Z_;
	m_is_vertex_node = vert;
}

bool Node::operator != (const Node& right) {
	if (node_id != right.node_id || X != right.X || Y != right.Y || Z != right.Z) {
		return true;
	}
	return false;
}

Edge::Edge(int id1, int id2, int id3) {
	first_id = id1;
	last_id = id2;
	center_id = id3;
}

void Edge::Update_the_central_Node(int id) {
	center_id = id;
}

bool Edge::operator==(const Edge& right) const {
	return right.first_id == first_id && right.last_id == last_id;
}

bool Node::operator == (const Node& right) {
	return right.X == X && right.Y == Y && right.Z;
}

bool Edge:: operator<(const Edge & right) const {
	return center_id < right.center_id;
}