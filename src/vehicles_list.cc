#include <vehicles/vehicles.h>
#include <stdexcept>
#include <utility>

using namespace vehicles;
using namespace std;

//Constructor/Destructor block
VehicleList::VehicleList() : _size(0) {}
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

//Operators and utilities
ListPtr VehicleList::operator[](int index) const {
    if (index < 0 || _size <= index) {
        throw out_of_range("[VehicleList::operator[]] Index is out of range.");
    }

    return _vehicles[index];
}
bool vehicles::operator==(const VehicleList& list, const VehicleList& other) {
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

void VehicleList::Swap(VehicleList& other) {
    swap(_vehicles, other._vehicles);
    swap(_size, other._size);
}

void VehicleList::add(const Vehicle v) {
    _vehicles[_size] = new Vehicle(v);
    ++_size;
}

void VehicleList::insert(int index, const Vehicle v) {
    if (index<0 || index>_size) {
        throw runtime_error("[VehicleList::add] Index out of range.");
    }
    ++_size;
    ListPtr* vehicles = new Vehicle * [_size];
    for (int i = _size; i > index; i--) {
        vehicles[i] = new Vehicle(*this->_vehicles[i]);
    }
    vehicles[index] = new Vehicle(v);
    for (int i = _size - 1; i > index; --i) {
        vehicles[i] = new Vehicle(*this->_vehicles[i - 1]);
    }
    swap(this->_vehicles, vehicles);
}

void VehicleList::remove(int index) {
    for (int i = index; i < _size; i++) {
        _vehicles[i] = _vehicles[i + 1];
    }
    --_size;
}



int vehicles::search_min_cost(VehicleList vl, float mass, float distance){
    float mc = 1000000000;
    int mi = 10000;
    for (int i = 0; i < vl.get_size(); i++) {
        if (vl[i].cost(mass, distance) < mc) {
            mc = vl[i].cost(mass, distance);
            mi = i;
        }
    }
    return mi;
}
