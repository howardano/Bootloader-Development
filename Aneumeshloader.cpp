
#include "Aneumeshloader.h"

const Node AneuMeshLoader::Get_the_Node(int id) const{
	return nodes[id - 1];
}

const int AneuMeshLoader::Get_The_Last() const{
	return nodes.rbegin()->node_id;
}

void AneuMeshLoader:: LoadMesh(const std::string& filename) {
	std::ifstream file;
	file.open(filename);

	if (!file) {
		throw ErrorWithFormat(filename);
	}
	else {
		std::cout << "File was successfully opened...\n" << std::endl;
	}

	int amount = 0, dimension = 0;

	file >> amount >> dimension;
	nodes.reserve(amount);
	for (int i = 1; i <= amount; ++i) {
		Node temp_node;
		temp_node.node_id = i;
		file >> temp_node.X >> temp_node.Y >> temp_node.Z;
		temp_node.m_is_vertex_node = true;
		nodes.push_back(temp_node);
	}

	file >> amount >> dimension;
	elements.reserve(amount);
	for (int i = 1; i <= amount; i++) {
		FiniteElement temp_element;
		temp_element.element_id = i;
		file >> temp_element.material_id;
		temp_element.nodes_id.reserve(dimension);
		int temp_id;
		for (int j = 0; j < dimension; ++j) {
			file >> temp_id;
			temp_element.nodes_id.push_back(temp_id);
		}
		elements.push_back(std::move(temp_element));
	}

	file >> amount >> dimension;
	surfaces.reserve(amount);
	for (int i = 1; i <= amount; ++i) {
		SurfaceFiniteElement temp_surface;
		temp_surface.surface_id = i;
		file >> temp_surface.border_id;
		temp_surface.nodes_id.reserve(dimension);
		int temp_id;
		for (int j = 0; j < dimension; ++j) {
			file >> temp_id;
			temp_surface.nodes_id.push_back(temp_id);
		}
		surfaces.push_back(std::move(temp_surface));
	}
	std::cout << "Data was loaded, closing the file...\n" << std::endl;
	file.close();
}

const std::vector<SurfaceFiniteElement> AneuMeshLoader::get_the_surfaceki_by_surfaceID(int id) const {
	std::vector<SurfaceFiniteElement> result;
	auto current = surfaces.begin();
	auto last = surfaces.end();
	while (current != last) {
		current = find_if(current, last, [id](const SurfaceFiniteElement &nod) {
			return nod.border_id == id;
		});
		if (current != last) {
			result.push_back(*current);
			++current;
		}
	}
	return result;
}

const std::vector<Node> AneuMeshLoader::get_the_nodes_of_surface_by_ID(int border_i) const {
	std::vector<Node> result;
	auto current = surfaces.begin();
	auto last = surfaces.end();
	while (current != last) {
		current = find_if(current, last, [border_i](SurfaceFiniteElement elemento) {
			return elemento.border_id == border_i;
		});
		if (current != last) {
			for (auto& it : current->nodes_id) {
				auto helper = find_if(nodes.begin(), nodes.end(), [it](Node nod) {
					return nod.node_id == it;
				});
				result.push_back(*helper);
			}
			current++;
		}
	}
	return result;
}

const std::vector<FiniteElement> AneuMeshLoader::get_the_ki_by_material(int mat) const {
	std::vector<FiniteElement> result;
	auto current = elements.begin();
	auto last = elements.end();
	while (current != last) {
		current = find_if(current, last, [mat](FiniteElement elemento) {
			return elemento.material_id == mat;
		});
		if (current != last) {
			result.push_back(*current);
			current++;
		}
	}
	return result;
}

const std::vector<Node>& AneuMeshLoader::get_nodes() const {
	return nodes;
}

const std::vector<FiniteElement>& AneuMeshLoader::get_elements() const {
	return elements;
}

const std::vector<SurfaceFiniteElement>& AneuMeshLoader::get_surface() const {
	return surfaces;
}

std::ostream& operator << (std::ostream& out, AneuMeshLoader& in) {
	std::cout << "\nNodes:\n" << std::endl;
	for_each(in.nodes.begin(), in.nodes.end(), [](Node elemento) {
		std::cout << std::setw(10) << std::setprecision(2) << elemento.X << std::setw(10) << std::setprecision(2) << elemento.Y << std::setw(10) << std::setprecision(2) << elemento.Z << std::endl;
	});
	std::cout << "\nFiniteElements:\n" << std::endl;
	for_each(in.elements.begin(), in.elements.end(), [](FiniteElement elemento) {
		std::cout << std::setw(10) << std::setprecision(2) << elemento.nodes_id[0] << std::setw(10) << std::setprecision(2) << elemento.nodes_id[1] << std::setw(10) << std::setprecision(2) <<  elemento.nodes_id[2] << std::setw(10) << std::setprecision(2) << elemento.nodes_id[3] << std::endl;
	});
	std::cout << "\nSurfaceFiniteElements: \n" << std::endl;
	for_each(in.surfaces.begin(), in.surfaces.end(), [](SurfaceFiniteElement elemento) {
		std::cout << std::setw(10) << std::setprecision(2) << elemento.nodes_id[0] << std::setw(10) << std::setprecision(2) << elemento.nodes_id[1] << std::setw(10) << std::setprecision(2) << elemento.nodes_id[2] << std::endl;
	});
	return out;
}

std::ostream& operator << (std::ostream& out, std::vector<Node>& ino){
	for (auto it = ino.begin(); it != ino.end();) {
		std::cout << *(it++) << std::endl;
	}
	return out;
}

std::ostream& operator << (std::ostream& out, std::vector<FiniteElement>& ino) {
	for (auto it = ino.begin(); it != ino.end();) {
		std::cout << *(it++) << std::endl;
	}
	return out;
}

std::ostream& operator << (std::ostream& out, std::vector<SurfaceFiniteElement>& ino) {
	for (auto it = ino.begin(); it != ino.end();) {
		std::cout << *(it++) << std::endl;
	}
	return out;
}

std::ostream& operator << (std::ostream& out, Node& in) {
	std::cout << std::setw(10) << std::setprecision(4) << in.X << std::setw(10) << std::setprecision(4) << in.Y << std::setw(10) << std::setprecision(4) << in.Z;
	return out;
}

std::ostream& operator <<(std::ostream& out, FiniteElement& in) {
	std::cout << std::setw(10) << std::setprecision(4) << in.nodes_id[0] << std::setw(10) << std::setprecision(4) << in.nodes_id[1] << std::setw(10) << std::setprecision(4) << in.nodes_id[2] << std::setw(10) << std::setprecision(4) << in.nodes_id[3];
	return out;
}

std::ostream& operator <<(std::ostream& out, SurfaceFiniteElement& in) {
	std::cout << std::setw(10) << std::setprecision(4) << in.nodes_id[0] << std::setw(10) << std::setprecision(4) << in.nodes_id[1] << std::setw(10) << std::setprecision(4) << in.nodes_id[2];
	return out;
}

/*void AneuMeshLoader::print_Node() {
	std::cout << "Nodes needed: \n";
	for_each(nodes.begin(), nodes.end(), [](Node elemento) {
		printf("%20lf %20lf %20lf\n", elemento.X, elemento.Y, elemento.Z);;
	});
}

void AneuMeshLoader:: print_FiniteElement() {
	std::cout << "FiniteElements needed: \n";
	for_each(elements.begin(), elements.end(), [](FiniteElement elemento) {
		printf("%10d %10d %10d %10d %10d\n", elemento.material_id, elemento.nodes_id[0], elemento.nodes_id[1], elemento.nodes_id[2], elemento.nodes_id[3]);
	});
}

void AneuMeshLoader:: print_SurfaceFiniteElement() {
	std::cout << "SurfaceFiniteElements needed: \n";
	for_each(surfaces.begin(), surfaces.end(), [](SurfaceFiniteElement elemento) {
		printf("%10d %10d %10d %10d\n", elemento.border_id, elemento.nodes_id[0], elemento.nodes_id[1], elemento.nodes_id[2]);
	});
}*/

const std::vector<FiniteElement> AneuMeshLoader:: get_the_element_by_ID(int id1, int id2, int id3) const {
	std::vector <FiniteElement> result;
	auto current = elements.begin();
	auto last = elements.end();
	while (current != last) {
		current = find_if(current, last, [id1, id2, id3](FiniteElement elemento) {
			return std::find(elemento.nodes_id.begin(), elemento.nodes_id.end(), id1) != elemento.nodes_id.end()
				&& std::find(elemento.nodes_id.begin(), elemento.nodes_id.end(), id2) != elemento.nodes_id.end()
				&& std::find(elemento.nodes_id.begin(), elemento.nodes_id.end(), id3) != elemento.nodes_id.end(); });
		if (current != last) {
			result.push_back(*current);
			++current;
		}
	}
/*	std::cout << "FiniteElements you need:\n" << std::endl;
	for_each(result.begin(), result.end(), [](FiniteElement elemento) {
		printf("%10d %10d %10d %10d %10d\n", elemento.material_id, elemento.nodes_id[0], elemento.nodes_id[1], elemento.nodes_id[2], elemento.nodes_id[3]);
	});*/
	return result;
}

std::vector<std::vector<Node>> AneuMeshLoader:: Get_Neighbours() {
	std::vector<std::set<int>> result_int(nodes.size() + 1);
	for (auto& it : elements)
		for (auto node_it : it.nodes_id) {
			for (auto node_it2 : it.nodes_id)
				result_int[node_it].insert(node_it2);
			result_int[node_it].erase(node_it);
		}

	std::vector<std::vector<Node>> result(nodes.size() + 1);
	for (int i = 1; i < nodes.size() + 1; ++i) {
		std::vector<Node> temp_vec;
		temp_vec.reserve(result_int[i].size());
		for (auto& it_set : result_int[i])
			temp_vec.push_back(Get_the_Node(it_set));
		result[i] = std::move(temp_vec);
	}
	return result;
}

const std::vector<FiniteElement> AneuMeshLoader::get_the_element_by_edge(int id1, int id2) const {
	std::vector<FiniteElement> result;
	auto current = elements.begin();
	auto last = elements.end();
	while (current != last) {
		current = find_if(current, last, [id1, id2](FiniteElement elemento) {
			return std::find(elemento.nodes_id.begin(), elemento.nodes_id.end(), id1) != elemento.nodes_id.end() &&
				std::find(elemento.nodes_id.begin(), elemento.nodes_id.end(), id2) != elemento.nodes_id.end();
		});
		if (current != last) {
			result.push_back(*current);
			current++;
		}
	}
	return result;
}

void AneuMeshLoader:: put_in_center() {
	std::unordered_set<Edge, MyHashFunction> edges;
	for (auto& it : elements) {
		for (int i = 0; i < 3; ++i)
			for (int j = i + 1; j < 4; ++j) {
				Edge current_edge(it.nodes_id[i], it.nodes_id[j], 0);
				auto founded_edge = edges.find(current_edge);
				if (founded_edge == edges.end()) {
					Node left_node = Get_the_Node(it.nodes_id[i]);
					Node right_node = Get_the_Node(it.nodes_id[j]);
					int center_id_ = Get_The_Last() + 1;
					Node center_node(center_id_, (left_node.X + right_node.X) / 2,
						(left_node.Y + right_node.Y) / 2, (left_node.Z + right_node.Z) / 2, false);

					current_edge.Update_the_central_Node(center_id_);
					nodes.push_back(center_node);
					edges.insert(current_edge);
					it.nodes_id.push_back(center_id_);
				}
				else {
					it.nodes_id.push_back(founded_edge->center_id);
				}
			}
		it.nodes_id.shrink_to_fit();
	}
	for (auto& it : surfaces) {
		for (auto i = 0; i < 3; ++i)
			for (auto j = i + 1; j < 3; ++j) {
				Edge current_edge(it.nodes_id[i], it.nodes_id[j], 0);
				auto founded_edge = edges.find(current_edge);
				if (founded_edge != edges.end())
					it.nodes_id.push_back(founded_edge->center_id);
			}
		it.nodes_id.shrink_to_fit();
	}
	surfaces.shrink_to_fit();
	nodes.shrink_to_fit();
}