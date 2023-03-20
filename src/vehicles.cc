#include <vehicles/vehicles.h>
#include <cmath>
#include <stdexcept>
#include <cassert>

using namespace Vehicles;


float Vehicles::cost(float mass, float distance) {
	if (this->type == RAIL) {
		return (this->base_tariff) * mass * distance;
	}
	if (this->type == NAVAL) {
		return (this->base_tariff) * mass * (pow(this->naval_range_mod, distance / 5000));
	}
	if (this->type == AIR) {
		float air_eng_mod = 1.0;
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
	throw runtime_error("[Vehicles::cost] Invalid vehicle type.");
}

