#include <windows.h>
#include <vehicles/vehicles.h>
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

void menu() {
	system("cls");
	cout << "Welcome, please, choose from 1 to 6" << endl;
	cout << "1 - Insert an element into the list at the specified index" << endl;
	cout << "2 - Remove an element from the list at the specified index" << endl;
	cout << "3 - Show the vehicle list" << endl;
	cout << "4 - Search for a vehicle with minimal cost of transportation" << endl;
	cout << "5 - View tranportation costs" << endl;
	cout << "6 - End session" << endl;
	cout << "> ";
}

int main() {
	VehicleList VL = VehicleList();
	Vehicle item = Vehicle();
	int input = 0;
	int idx;
	while (input != 6) {
		menu();
		cin >> input;
		float dist = 0;
		float mass = 0;
		switch (input) {
		case 1:
			system("cls");
			VL.show_all();
			cout << "Isertion index: ";
			cin >> idx;
			cin >> item;
			VL.insert(idx, item);
			break;
		case 2:
			system("cls");
			VL.show_all();
			cout << "Removal index: ";
			cin >> idx;
			VL.remove(idx);
			break;
		case 3:
			system("cls");
			VL.show_all();
			break;
		case 4:
			system("cls");
			VL.show_all();
			cout << "Distance (km): ";
			cin >> dist;
			cout << "Mass of cargo (kg): ";
			cin >> mass;
			idx = VL.search_min_cost(mass, dist);
			cout << "Vehicle with minimal tranportation cost: " << VL.at(idx)->get_mod() << endl;
			break;
		case 5:
			system("cls");
			VL.show_all();
			cout << "Index of needed vehicle: ";
			cin >> idx;
			cout << "Distance (km): ";
			cin >> dist;
			cout << "Mass of cargo (kg): ";
			cin >> mass;
			cout << "Cost of transportaion: " << VL.at(idx)->cost(mass, dist) << endl;
			break;
		}
		if (input != 6)
			system("pause");
	}
}