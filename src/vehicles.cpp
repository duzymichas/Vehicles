//
// Created by bialo on 27.03.2023.
//
#include <vehicles.hpp>
#include <string>
#include <sstream>

Driver::Driver(std::string name, std::unique_ptr<Vehicle> p1, Gender g){
    name_ = std::move(name);
    vehicle_ptr_ = std::move(p1);
    gender_ = g;
}

Driver::Driver(Driver&& other){
    name_ = other.name_;
    vehicle_ptr_ = std::move(other.vehicle_ptr_);
}

Driver& Driver::operator=(Driver&& other){
    name_ = other.name_;
    vehicle_ptr_ = std::move(other.vehicle_ptr_);
    return (*this);
}

void Driver::assing_vehicle(std::unique_ptr<Vehicle> vehicle_ptr){
    vehicle_ptr_ = std::move(vehicle_ptr);
}

std::string to_string(const Vehicle& v){
    std::stringstream ss;
    ss << v.get_id() << " :  " << v.get_brand();
    return ss.str();
}

double compute_min_travel_time(double distance, const Vehicle& v){
    return distance/v.get_max_speed();
}

std::string compute_min_travel_time_as_string(double distance, const Vehicle& v){
    std::stringstream ss;
    ss << compute_min_travel_time(distance, v) << " h";
    return ss.str();
}


std::vector<Vehicle*> filter_vehicles(
        std::vector<Vehicle*>::const_iterator vehicles_begin,
        std::vector<Vehicle*>::const_iterator vehicles_end,
        std::function<bool (const Vehicle&)> predicate){
    std::vector<Vehicle*> reg;
    std::copy_if(vehicles_begin, vehicles_end, std::back_inserter(reg), [&predicate](const Vehicle* v){return predicate(*v);});
    return reg;
}
std::string to_string(std::vector<Vehicle*>::const_iterator vehicles_begin,
                      std::vector<Vehicle*>::const_iterator vehicles_end){
    std::ostringstream oss;
    for(std::vector<Vehicle*>::const_iterator it = vehicles_begin; it < vehicles_end; it++){
        std::string s = to_string(**it);
        oss << s << "\n";
    }
    return oss.str();
}

std::string to_string(const Driver& driver){
    std::ostringstream oss;
    oss << driver.get_name() << " : [";
    if(driver.get_vehicle() == nullptr) {
        oss << "no vehicle]";
    }
    else{
        oss << to_string(*(driver.get_vehicle())) << "]";
    }
    return oss.str();
}

void assign_vehicle_to_driver(std::vector<std::unique_ptr<Vehicle>>& vehicles, Driver& owner){
    if (!vehicles.empty()){
        auto last_it = vehicles.end() - 1;
        owner.assing_vehicle(std::move(*last_it));
        vehicles.erase(last_it);
    }
    else{
        std::unique_ptr<Vehicle> ptr;
        owner.assing_vehicle(nullptr);
    }
}