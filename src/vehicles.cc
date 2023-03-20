#include <vehicles/vehicles.h>
#include <cmath>
#include <stdexcept>
#include <cassert>

using namespace vehicles;

Vehicle::Vehicle() {
	this->type = Type::RAIL;
	this->model = "ZPM";
	this->base_tariff = 1;
	this->naval_range_mod = 1;
	this->air_eng_type = ERROR;
}
Vehicle::Vehicle(Type t, std::string model, float bt) {
	this->type = t;
	this->model = model;
	this->base_tariff = bt;
	this->air_eng_type = ERROR;
	this->naval_range_mod = 1;
}
Vehicle::Vehicle(Type t, std::string model, float bt, float nrm) {
	this->type = t;
	this->model = model;
	this->base_tariff = bt;
	if (nrm > 0.9 && nrm < 1) {
		this->naval_range_mod = nrm;
	}
	else {
		this->naval_range_mod = 1;
	}
	this->air_eng_type = ERROR;
}
Vehicle::Vehicle(Type t, std::string model, float bt, AirEngType aet) {
	this->type = t;
	this->model = model;
	this->base_tariff = bt;
	this->naval_range_mod = 1;
	if (this->type == AIR) {
		this->air_eng_type = aet;
	}
	else {
		this->air_eng_type = ERROR;
	}
}
Vehicle::Vehicle(Type t, std::string model, float bt, float nrm, AirEngType aet) {
	this->type = t;
	this->model = model;
	this->base_tariff = bt;
	if (this->type == NAVAL && nrm > 0.9 && nrm < 1) {
		this->naval_range_mod = nrm;
	}
	else {
		this->naval_range_mod = 1;
	}
	if (this->type == AIR) {
		this->air_eng_type = aet;
	}
	else {
		this->air_eng_type = ERROR;
	}
}

bool vehicles::operator==(const Vehicle& lv, const Vehicle& rv) {
	return (lv.get_type() == lv.get_type()) && (lv.get_mod() == rv.get_mod());
}
bool vehicles::operator!=(const Vehicle& lv, const Vehicle& rv) {
	return !(lv == rv);
}

float Vehicle::cost(const float mass, const float distance) {
	if (this->type == RAIL) {
		return (this->base_tariff) * mass * distance;
	}
	if (this->type == NAVAL) {
		return (this->base_tariff) * mass * distance * (pow(this->naval_range_mod, distance / 5000));
	}
	if (this->type == AIR) {
		float air_eng_mod = -1.0;
		if (this->air_eng_type == TURBOPROP) {
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
		return (this->base_tariff) * mass * air_eng_mod * distance;
	}
	throw std::runtime_error::runtime_error("[Vehicles::cost] Invalid vehicle type.");
}

