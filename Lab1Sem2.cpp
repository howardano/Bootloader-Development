#include <stdio.h>
#include "Aneumeshloader.h"
#include <string>
#include <vector>
#include <set>
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

int main()
{
	AneuMeshLoader object;
	AneuMeshLoader object2;
	std::string path = "MeshExample.aneu";
	std::string path2 = "MeshExample1.txt";
	try {
		object2.LoadMesh(path2);
	}
	catch (ErrorWithFormat &ex) {
		std::cerr << ex.what() << std::endl;
	}
	object.LoadMesh(path);
	std::cout << "Your object: \n" << std::endl;
	std::cout << object;
	std::cout << "\nGot the nodes needed:\n" << std::endl;
	std::vector<Node> example1 = object.get_nodes();
	std::cout << example1;
	std::cout << "\nGot the element_by_id needed:\n" << std::endl;
	std::vector<FiniteElement> example2 = object.get_the_element_by_ID(13, 14, 10);
	std::cout << example2;
	std::cout << "\nGot the surface by id:\n" << std::endl;
	std::vector<Node> example3 = object.get_the_nodes_of_surface_by_ID(12);
	std::cout << example3;
	std::cout << "\nGot the ki by material id:\n" << std::endl;
	std::vector<FiniteElement> example4 = object.get_the_ki_by_material(1);
	std::cout << example4;
	std::cout << "Got the surface ki by id:\n" << std::endl;
	std::vector<SurfaceFiniteElement> example5 = object.get_the_surfaceki_by_surfaceID(11);
	std::cout << example5;
	std::cout << "Putting new nodes in center...\n" << std::endl;
	object.put_in_center();
	std::cout << object;
	_getch();
}

