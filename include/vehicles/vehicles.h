#pragma once
#include <string>

namespace vehicles {
	enum Type {
		RAIL,
		NAVAL,
		AIR
	};

	enum AirEngType {
		TURBOPROP,
		JET,
		ERROR
	};

	class Vehicle {
	private:
		Type type;
		std::string model;
		float base_tariff;
		float naval_range_mod;
		AirEngType air_eng_type;

	public:
		Type get_type() const {
			return this->type;
		}
		std::string get_mod() const {
			return this->model;
		}
		float get_bt() const {
			return this->base_tariff;
		}
		float get_nrm() const {
			if (this->type == NAVAL) {
				return this->naval_range_mod;
			}
			else {
				return 1;
			}
			
		}
		AirEngType get_aet() const {
			if (this->type == AIR) {
				return this->air_eng_type;
			}
			else {
				return ERROR;
			}
			
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
		void set_aet(AirEngType aet) {
			if (this->type == AIR) {
				this->air_eng_type = aet;
			}
		}

		Vehicle();

		Vehicle(Type t, std::string model, float bt);

		Vehicle(Type t, std::string model, float bt, float nrm);

		Vehicle(Type t, std::string model, float bt, AirEngType aet);

		Vehicle(Type t, std::string model, float bt, float nrm, AirEngType aet);

		float cost(const float mass, const float distance);

	};

	bool operator==(const Vehicle& lv, const Vehicle& rv);
	bool operator!=(const Vehicle& lv, const Vehicle& rv);

	class VehicleList {
	public:
		static const int CAP = 127;
	private:
		Vehicle _vehicles[CAP];
		int _size;
	public:
		VehicleList();
		Vehicle operator[](int index) const;
		int get_size();
		void add(Vehicle v);
		void insert(int index, Vehicle v);
		void remove(int index);
	};
	int search_min_cost(const VehicleList vl, const float mass, const float distance);
}


