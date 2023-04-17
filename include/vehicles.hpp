//
// Created by bialo on 27.03.2023.
//

#ifndef VEHICLES_1_VEHICLES_HPP
#define VEHICLES_1_VEHICLES_HPP

#include<string>
#include<vector>
#include<algorithm>
#include<memory>

class Vehicle{
private:
    std::string id_;
    std::string brand_;
    std::int64_t vin_;
    inline static std::int64_t next_vin_ = 1;
public:
    Vehicle(std::string id ="", std::string brand ="") : id_(id), brand_(brand), vin_(next_vin_) {next_vin_ += 1;}
    std::string get_id() const {return id_;}
    std::string get_brand() const {return brand_;}
    virtual double get_max_speed() const = 0;
    static void reset_vin_counter() {next_vin_ = 1;}
    std::int64_t get_vin () const { return vin_; }
    virtual ~Vehicle(){}
};

class Car : public Vehicle{
private:
    double engine_hp_;
public:
    Car(std::string id  ="", std::string brand = "", double engine_hp = 0) : Vehicle(id, brand), engine_hp_(engine_hp) {}
    double get_max_speed() const override {return engine_hp_;}
};

class Bicycle : public Vehicle{
private:
    double n_gears_;
public:
    Bicycle(std::string id  ="", std::string brand = "", int n_gears = 0) : Vehicle(id, brand), n_gears_(n_gears) {}
    double get_max_speed() const override {return 3 * n_gears_;}
};

enum class Gender{
    Male,Female
};

class Driver {
public:
    Driver(std::string name, std::unique_ptr<Vehicle> p1, Gender g);

    Driver(std::string name, Gender g) : Driver(name, nullptr, g){}

    void assing_vehicle(std::unique_ptr<Vehicle>);

    std::string get_name() const { return name_;}

    Vehicle* get_vehicle() const { return vehicle_ptr_.get();}

    Driver(Driver&) = delete;
    Driver& operator=(Driver&) = delete;

    Driver(Driver&&);
    Driver& operator=(Driver&&);


private:
    std::string name_;
    std::unique_ptr<Vehicle> vehicle_ptr_;
    Gender gender_;
};

std::string to_string(const Vehicle&);
double compute_min_travel_time(double distance, const Vehicle& v);
std::string compute_min_travel_time_as_string(double distance, const Vehicle& v);

std::vector<Vehicle*> filter_vehicles(
        std::vector<Vehicle*>::const_iterator vehicles_begin,
        std::vector<Vehicle*>::const_iterator vehicles_end,
        std::function<bool (const Vehicle&)> predicate);


std::string to_string(std::vector<Vehicle*>::const_iterator vehicles_begin,
                      std::vector<Vehicle*>::const_iterator vehicles_end);

std::string to_string(const Driver&);

void assign_vehicle_to_driver(std::vector<std::unique_ptr<Vehicle>>& vehicles, Driver& owner);

#endif //VEHICLES_1_VEHICLES_HPP
