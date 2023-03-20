#pragma once
#include <cstring>

namespace Vehicles {
	enum Type {
		RAIL,
		NAVAL,
		AIR
	};

	enum AirEngType {
		TURBOPROP,
		JET
	};

	class Vehicle {
	private:
		Type type;
		std::string model;
		float base_tariff;
		float naval_range_mod;
		float air_eng_type;

	public:
		Type get_type() {
			return this->type;
		}
		std::string get_mod() {
			return this->model;
		}
		float get_bt() {
			return this->base_tariff;
		}
		float get_nrm() {
			return this->naval_range_mod;
		}
		float get_aet() {
			return this->air_eng_type;
		}

		void set_type(Type t) {
			this->type = t;
		}
		void set_mod(std::string m) {
			this->model = m;
		}
		void set_bt(float bt) {
			this->base_tariff = bt;
		}
		void set_nrm(float nrm) {
			if (this->type == NAVAL) {
				this->naval_range_mod = nrm;
			}
		}
		void set_aet(float aet) {
			if (this->type == AIR) {
				this->air_eng_type = aet;
			}
		}

		Vehicle() {
			this->type = Type::RAIL;
			this->model = "ZPM";
			this->base_tariff = 1000;
			this->naval_range_mod = 1;
			this->air_eng_type = JET;
		}

		Vehicle(Type t, char* model, float bt, float nrm, float aet) {
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
				this->air_eng_type = JET;
			}
		}

		float cost(float mass, float distance);
	};

	class VehicleList {
	public:
		static const int CAP = 10;
	private:
		Vehicle _vehicles[CAP];
		int _size;
	public:
		VehicleList();
		int get_size();
		void insert(int index, Vehicle v);
		void remove(int index);
	};

}


