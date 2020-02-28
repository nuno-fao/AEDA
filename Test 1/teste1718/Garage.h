/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>
#include "car.h"
using namespace std;

template <class Vehicle>
class Garage {
	std::vector<Vehicle *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Vehicle *> getVehicles() const;
	void setVehicles(std::vector<Vehicle *> vehicles);
	int getCapacity() const;
	bool addVehicle(Vehicle *vehicle);
	Vehicle* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();
};

class NoSuchVehicleException {
public:
	NoSuchVehicleException() { }
};

class NoSuchBrandException {
    string brand;
public:
    NoSuchBrandException(string brand): brand(brand){}
    string getBrand(){return brand;}
};

template <class Vehicle>
Garage<Vehicle>::Garage(int size) : capacity(size) {
}

template <class Vehicle>
Garage<Vehicle>::~Garage() {
	typename std::vector<Vehicle *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}

template<class Vehicle>
std::vector<Vehicle *> Garage<Vehicle>::getVehicles() const {
	return vehicles;
}

template<class Vehicle>
void Garage<Vehicle>::setVehicles(std::vector<Vehicle*> vehicles) {
	this->vehicles = vehicles;
}

template<class Vehicle>
int Garage<Vehicle>::getCapacity() const {
	return capacity;
}

template<class Vehicle>
bool Garage<Vehicle>::addVehicle(Vehicle *vehicle) {
    if(vehicles.size()!=capacity){
        for(typename vector<Vehicle *>::iterator it=vehicles.begin();it!=vehicles.end();++it){
            if(**it==*vehicle){
                return false;
            }
        }
        vehicles.push_back(vehicle);
        return true;
    }
    return false;
}


bool comp(Car* v1, Car* v2){
    if(v1->getBrand()==v2->getBrand()){
        return v1->getPrice()>v2->getPrice();
    }
    return v1->getBrand()<v2->getBrand();
}

template<class Vehicle>
void Garage<Vehicle>::sortVehicles(){
    sort(vehicles.begin(),vehicles.end(),comp);
}

template<class Vehicle>
Vehicle* Garage<Vehicle>::removeVehicle(std::string brand, std::string model){
    for (typename std::vector<Vehicle *>::iterator it = vehicles.begin(); it != vehicles.end(); it++) {
        if ((*it)->getBrand() == brand && (*it)->getModel() == model) {
            Vehicle* out=*it;
            vehicles.erase(it);
            return out;
        }
    }
    throw NoSuchVehicleException();
}

template<class Vehicle>
float Garage<Vehicle>::avgPrice(std::string brand) const {
    unsigned count = 0, total = 0;
    for(unsigned i=0;i<vehicles.size();i++){
        if((vehicles.at(i))->getBrand()==brand){
            count++;
            total+=(vehicles.at(i))->getPrice();
        }
    }
    if(count==0) throw NoSuchBrandException(brand);
    return total/count;
}
#endif /* SRC_GARAGE_H_ */
