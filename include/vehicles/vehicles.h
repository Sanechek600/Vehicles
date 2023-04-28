#pragma once
#include <string>
#include <algorithm>
#include <iostream>
#define ListPtr Vehicle*

	enum VehicleType {
		RAIL = 0,
		NAVAL = 1,
		AIR = 2,
		BOOM = 3
	};

	enum AirEngType {
		TURBOPROP = 0,
		JET = 1
	};

	class Vehicle {
	private:
		VehicleType _type;
		std::string _model;
		float _base_tariff;
		float _naval_range_mod;
		AirEngType _air_eng_type;

	public:
		VehicleType get_type() const {
			return this->_type;
		}
		std::string get_mod() const {
			return this->_model;
		}
		float get_bt() const {
			return this->_base_tariff;
		}
		float get_nrm() const {
			if (this->_type == NAVAL) {
				return this->_naval_range_mod;
			}
			else {
				return 1;
			}
			
		}
		AirEngType get_aet() const {
			if (this->_type == AIR) {
				return this->_air_eng_type;
			}
			else {
				return JET;
			}
			
		}

		void set_type(VehicleType t) {
			this->_type = t;
		}
		void set_mod(std::string m) {
			this->_model = m;
		}
		void set_bt(float bt) {
			this->_base_tariff = bt;
		}
		void set_nrm(float nrm) {
			if (this->_type == NAVAL) {
				this->_naval_range_mod = nrm;
			}
		}
		void set_aet(AirEngType aet) {
			if (this->_type == AIR) {
				this->_air_eng_type = aet;
			}
		}

		Vehicle();
		Vehicle(VehicleType t, std::string model, float bt);
		Vehicle(VehicleType t, std::string model, float bt, float nrm);
		Vehicle(VehicleType t, std::string model, float bt, AirEngType aet);
		Vehicle(VehicleType t, std::string model, float bt, float nrm, AirEngType aet);
		Vehicle(const Vehicle& v);

		float cost(const float mass, const float distance);

		void Swap(Vehicle& other) noexcept;
		Vehicle& operator=(Vehicle other);
		friend istream& operator>>(istream& in, Vehicle& item);
		friend ostream& operator<<(ostream& out, const Vehicle& item);

	};

	bool operator==(const Vehicle& lv, const Vehicle& rv);
	bool operator!=(const Vehicle& lv, const Vehicle& rv);

	class VehicleList {
		ListPtr* _vehicles;
		size_t _size;
	public:	
		VehicleList();
		VehicleList(ListPtr* _vehicle, size_t _size);
		VehicleList(ListPtr* _vehicle, size_t _size, int);
		VehicleList(const VehicleList& pther);
		~VehicleList();

		ListPtr at(int i);
		int get_size();
		void set_size(size_t size);

		ListPtr operator[](int index) const;
		ListPtr& operator[](int index);
		VehicleList& operator=(VehicleList other);
		friend bool operator==(const VehicleList& list, const VehicleList& other);
		friend bool operator!=(const VehicleList& list, const VehicleList& other);

		void add(Vehicle vehicle);
		void insert(int index, Vehicle vehicle);
		void remove(int index);
		void clear();
		void print_current(int index);
		void show_all();
		void Swap(VehicleList& other) noexcept;
		int search_min_cost(const float mass, const float distance);
	};




