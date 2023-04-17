 #include "gtest/gtest.h"

#include "vehicles.hpp"

TEST(VehiclesTest, Implementation) {


    // Użyto ASSERT_XXX, gdyż dalsze warunki testowe mają sens tylko wówczas,
    //   gdy wektor zawiera (co najmniej) dwie składowe. Jeśli warunek nie jest
    //   spełniony, należy bezwzględnie przerwać dalsze wykonywanie testów
    //   (inaczej np. wywołanie `v.get_elem(0)` może rzucić wyjątek, jeśli
    //   kontener jest pusty.
    // EXPECT_XXX jedynie oznacza test jako "nie powiódł się", jednak pozwala na
    //   wykonywanie dalszych instrukcji w ramach tego testu, co często umożlwia
    //   uzyskanie dalszych informacji diagnostycznych (np. tu - informację
    //   o faktycznej wartości obu (!) składowych, niezależnie od tego, czy są
    //   to wartości poprawne, czy też nie.
    Car car1("1", "Volvo",100);
    Bicycle bicycle1("2", "Cross",3);
    ASSERT_EQ(car1.get_max_speed(),100);
    ASSERT_EQ(bicycle1.get_max_speed(),9);
}

TEST(VehiclesTest, to_string) {
    Car car1("1", "Volvo",100);
    Bicycle bicycle1("2", "Cross",3);
    ASSERT_EQ(to_string(car1),"1 :  Volvo");
    ASSERT_EQ(to_string(bicycle1), "2 :  Cross");
}

TEST(VehiclesTest, compute_min_travel_time) {
    Car car1("1", "Volvo",100);
    Bicycle bicycle1("2", "Cross",3);
    double distance = 100;
    double distance2 = 90;
    ASSERT_EQ(compute_min_travel_time(distance, car1), 1);
    ASSERT_EQ(compute_min_travel_time(distance2, bicycle1), 10);
}
TEST(VehiclesTest, compute_min_travel_time_as_string) {
    Car car1("1", "Volvo",100);
    Bicycle bicycle1("2", "Cross",3);
    double distance = 100;
    double distance2 = 90;
    ASSERT_EQ(compute_min_travel_time_as_string(distance, car1), "1 h");
    ASSERT_EQ(compute_min_travel_time_as_string(distance2, bicycle1), "10 h");
}

TEST(VehiclesTest, filter) {
    Car car1("KR 001", "", 100.0);
    Car car2("K 000 1R", "", 200.0);
    Bicycle bicycle("RK 1", "", 0);

    std::function<bool (const Vehicle&)> find_substr = [](const Vehicle& vehicle) {
        return vehicle.get_id().find("KR") != std::string::npos;
    };

    std::vector<Vehicle*> vehicles = { &car1, &bicycle, &car2 };
    std::vector<Vehicle*> filtered_check = {&car1};
    std::vector<Vehicle*> filtered = filter_vehicles(vehicles.cbegin(), vehicles.cend(), find_substr);
    ASSERT_EQ(filtered, filtered_check);
}

TEST(VehicleTest, VIN) {
    Vehicle::reset_vin_counter();

    Car car1("", "", 100.0);
    Car car2("", "", 100.0);

    EXPECT_EQ(car1.get_vin(), 1);
    EXPECT_EQ(car2.get_vin(), 2);
}