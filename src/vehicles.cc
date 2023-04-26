#include <vehicles/vehicles.h>
#include <cmath>
#include <stdexcept>
#include <cassert>
#include <utility>
#include <iostream>

using namespace vehicles;
using namespace std;

Vehicle::Vehicle() {
	this->_type = Type::RAIL;
	this->_model = "ZPM";
	this->_base_tariff = 1;
	this->_naval_range_mod = 1;
	this->_air_eng_type = ERROR;
}
Vehicle::Vehicle(Type t, std::string model, float bt) {
	this->_type = t;
	this->_model = model;
	this->_base_tariff = bt;
	this->_air_eng_type = ERROR;
	this->_naval_range_mod = 1;
}
Vehicle::Vehicle(Type t, std::string model, float bt, float nrm) {
	this->_type = t;
	this->_model = model;
	this->_base_tariff = bt;
	if (nrm > 0.9 && nrm < 1) {
		this->_naval_range_mod = nrm;
	}
	else {
		this->_naval_range_mod = 1;
	}
	this->_air_eng_type = ERROR;
}
Vehicle::Vehicle(Type t, std::string model, float bt, AirEngType aet) {
	this->_type = t;
	this->_model = model;
	this->_base_tariff = bt;
	this->_naval_range_mod = 1;
	if (this->_type == AIR) {
		this->_air_eng_type = aet;
	}
	else {
		this->_air_eng_type = ERROR;
	}
}
Vehicle::Vehicle(Type t, std::string model, float bt, float nrm, AirEngType aet) {
	this->_type = t;
	this->_model = model;
	this->_base_tariff = bt;
	if (this->_type == NAVAL && nrm > 0.9 && nrm < 1) {
		this->_naval_range_mod = nrm;
	}
	else {
		this->_naval_range_mod = 1;
	}
	if (this->_type == AIR) {
		this->_air_eng_type = aet;
	}
	else {
		this->_air_eng_type = ERROR;
	}
}
Vehicle::Vehicle(const Vehicle& v) {
	_type = v.get_type();
	_model = v.get_mod();
	_base_tariff = v.get_bt();
	_naval_range_mod = v.get_nrm();
	_air_eng_type = v.get_aet();
}

bool vehicles::operator==(const Vehicle& item, const Vehicle& other) {
	return ((item.get_type() == other.get_type()) &&
		(item.get_mod() == other.get_mod()) &&
		(item.get_nrm() == other.get_nrm()) &&
		(item.get_aet() == other.get_aet()) &&
		(item.get_bt() == other.get_bt()));
}
bool vehicles::operator!=(const Vehicle& item, const Vehicle& other) {
	return !(item == other);
}
Vehicle& Vehicle::operator=(Vehicle other) {
	Swap(other);
	return *this;
}
istream& operator>>(std::istream& in, Type& item_type) {
	int type;
	in >> type;
	switch (type) {
	case 0:
		item_type = RAIL;
		break;
	case 1:
		item_type = NAVAL;
		break;
	case 2:
		item_type = AIR;
		break;
	case 3:
		item_type = BOOM;
		break;
	default:
		throw std::runtime_error("Wrong type exception");
	}
	return in;
}


void Vehicle::Swap(Vehicle& other) {
	swap(_type, other._type);
	swap(_base_tariff, other._base_tariff);
	swap(_model, other._model);
	swap(_air_eng_type, other._air_eng_type);
	swap(_naval_range_mod, other._naval_range_mod);
}

float Vehicle::cost(const float mass, const float distance) {
	if (this->_type == RAIL) {
		return (this->_base_tariff) * mass * distance;
	}
	if (this->_type == NAVAL) {
		return (this->_base_tariff) * mass * distance * (pow(this->_naval_range_mod, distance / 5000));
	}
	if (this->_type == AIR) {
		float air_eng_mod = -1.0;
		if (this->_air_eng_type == TURBOPROP) {
			if (distance < 1000) {
				air_eng_mod = 0.5;
			}
			else {
				air_eng_mod = 1.5;
			}
		}
		else {
			if (distance < 1000) {
				air_eng_mod = 1.5;
			}
			else {
				air_eng_mod = 0.5;
			}
		}
		return (this->_base_tariff) * mass * air_eng_mod * distance;
	}
	throw runtime_error("[Vehicles::cost] Invalid vehicle type.");
}

