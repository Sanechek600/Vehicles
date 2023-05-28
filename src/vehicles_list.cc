#include <vehicles/vehicles.h>
#include <stdexcept>
#include <utility>
#include <iostream>

using namespace std;

//Constructor/Destructor block
VehicleList::VehicleList() : _size(3) { 
    _vehicles = new Vehicle * [_size];
    _vehicles[0] = new Vehicle(RAIL, "Traine", 10);
    _vehicles[1] = new Vehicle(AIR, "Plaine", 10, JET);
    _vehicles[2] = new Vehicle(NAVAL, "Sheap", 10, 0.95);
}
VehicleList::VehicleList(ListPtr* vehicles, size_t size) {
    _size = size;

    _vehicles = new Vehicle * [_size];
    for (int i = 0; i < size; ++i) {
        _vehicles[i] = new Vehicle();
        _vehicles[i]->set_type(vehicles[i]->get_type());
        _vehicles[i]->set_mod(vehicles[i]->get_mod());
        _vehicles[i]->set_bt(vehicles[i]->get_bt());
        _vehicles[i]->set_aet(vehicles[i]->get_aet());
        _vehicles[i]->set_nrm(vehicles[i]->get_nrm());
    }
}
VehicleList::VehicleList(ListPtr* vehicles, size_t size, int) {
    _size = size;

    _vehicles = new Vehicle * [_size];
    for (int i = 0; i < size; ++i) {
        _vehicles[i] = new Vehicle();
        _vehicles[i]->set_type(vehicles[i]->get_type());
        _vehicles[i]->set_mod(vehicles[i]->get_mod());
        _vehicles[i]->set_bt(vehicles[i]->get_bt());
        _vehicles[i]->set_aet(vehicles[i]->get_aet());
        _vehicles[i]->set_nrm(vehicles[i]->get_nrm());
    }
}
VehicleList::VehicleList(const VehicleList& other) :
    _vehicles(new ListPtr[other._size]),
    _size(other._size)
{
    for (int i = 0; i < _size; ++i) {
        _vehicles[i] = new Vehicle(*other._vehicles[i]);
    }
}
VehicleList::~VehicleList() {
    for (int i = 0; i < _size; ++i) { delete _vehicles[i]; }
    delete[] _vehicles;
}

//Methods
int VehicleList::get_size() {
	return _size;
}
ListPtr VehicleList::at(int index) {
    return  _vehicles[index];
}
void VehicleList::set_size(size_t size) {
    _size = size;
}

//Operators and utilities
bool operator==(const VehicleList& list, const VehicleList& other) {
    return (list._size == other._size && **(list._vehicles) == **(other._vehicles));
}
bool operator!=(const VehicleList& list, const VehicleList& other) {
    return !(list == other);
}
VehicleList& VehicleList::operator=(VehicleList other) {
    Swap(other);
    return *this;
}
ListPtr VehicleList::operator[](int index) const {
    if (index < 0 || index >= _size)
    {
        throw runtime_error("Index out of range.");
    }
    return _vehicles[index];
}
ListPtr& VehicleList::operator[](int index)
{
    if (index < 0 || index >= _size)
    {
        throw runtime_error("Index out of range.");
    }
    return _vehicles[index];
}

void VehicleList::Swap(VehicleList& other) noexcept {
    swap(_vehicles, other._vehicles);
    swap(_size, other._size);
}


//Adding/deleting items
void VehicleList::add(const Vehicle v) {
    ++_size;
    ListPtr* vehicles = new Vehicle * [_size];
    for (int i = 0; i < _size - 1; i++) {
        vehicles[i] = new Vehicle(*this->_vehicles[i]);
    }
    vehicles[_size - 1] = new Vehicle(v);
    swap(this->_vehicles, vehicles);
}

void VehicleList::insert(int index, const Vehicle v) {
    if (index<0 || index>_size) {
        throw runtime_error("[VehicleList::insert] Index out of range.");
    }
    ++_size;
    ListPtr* vehicles = new Vehicle * [_size];
    for (int i = _size - 1; i > index; --i) {
        vehicles[i] = new Vehicle(*this->_vehicles[i - 1]);
    }
    vehicles[index] = new Vehicle(v);
    for (int i = index - 1; i >= 0; --i) {
        vehicles[i] = new Vehicle(*this->_vehicles[i]);
    }
    swap(this->_vehicles, vehicles);
}

void VehicleList::remove(int index) {
    for (int i = index; i < _size; i++) {
        _vehicles[i] = _vehicles[i + 1];
    }
    --_size;
}

void VehicleList::clear() {
    _vehicles = nullptr;
    _size = 0;
}


//Console stuff
void VehicleList::print_current(int index) {
    cout << *_vehicles[index];
}
void VehicleList::show_all() {
    cout << "All vehicles on the list:\n";
    for (int i = 0; i < _size; ++i) {
        cout << i << ':';
        print_current(i);
        cout << endl;
    }
}


int VehicleList::search_min_cost(float mass, float distance){
    float mc = 1000000000;
    int mi = 0;
    for (int i = 0; i < _size; i++) {
        if (_vehicles[i]->cost(mass, distance) < mc) {
            mc = _vehicles[i]->cost(mass, distance);
            mi = i;
        }
    }
    return mi;
}
