#include <vehicles/vehicles.h>
#include <stdexcept>

using namespace vehicles;
using namespace std;

VehicleList::VehicleList() : _size(0) {}

int VehicleList::get_size() {
	return _size;
}

Vehicle VehicleList::operator[](const int index) const {
    if (index < 0 || _size <= index) {
        throw out_of_range("[VehicleList::operator[]] Index is out of range.");
    }

    return _vehicles[index];
}

void VehicleList::add(const Vehicle v) {
    if (_size == CAP) {
        throw runtime_error("[VehicleList::add] Capacity is reached.");
    }

    _vehicles[_size] = v;
    ++_size;
}

void VehicleList::insert(int index, const Vehicle v) {
    if (_size == CAP) {
        throw runtime_error("[VehicleList::add] Capacity is reached.");
    }

    for (int i = _size; i > index; i--) {
        _vehicles[i] = _vehicles[i - 1];
    }
    _vehicles[index] = v;
    ++_size;
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
