#include <gtest/gtest.h>
#include <vehicles/vehicles.h>
#include <string>
#include <stdexcept>
#define ListPtr Vehicle*

using namespace std;

TEST(VehicleTests, EqTest) {
	Vehicle v1(RAIL, "TRAINE_1", 1);
	Vehicle v2(RAIL, "TRAINE_1", 1);

	EXPECT_EQ(v1, v2);
}
TEST(VehicleTests, GetterTest1) {
    // Arrange
    Vehicle v1;
    v1.set_type(NAVAL);
    v1.set_mod("BOAT");
    v1.set_bt(1.0);
    v1.set_nrm(0.95);
    v1.set_aet(JET);

    // Act
    VehicleType t = v1.get_type();
    std::string s = v1.get_mod();
    float bt = v1.get_bt();
    float nrm = v1.get_nrm();
    AirEngType aet = v1.get_aet();


    // Assert
    EXPECT_EQ(t, 1);
    EXPECT_EQ(s, "BOAT");
    EXPECT_NEAR(bt, 1.0, 0.001);
    EXPECT_NEAR(nrm, 0.95, 0.001);
}
TEST(VehicleTests, CostTest_NAVAL) {
    // Arrange
    Vehicle v1;
    v1.set_type(NAVAL);
    v1.set_mod("BOATE");
    v1.set_bt(1.0);
    v1.set_nrm(0.95);
    v1.set_aet(JET);

    // Act
    float cost = v1.cost(20, 10000);


    // Assert
    EXPECT_NEAR(cost, 180500.0, 0.001);
}
TEST(VehicleTests, CostTest_RAIL) {
    // Arrange
    Vehicle v1;
    v1.set_type(RAIL);
    v1.set_mod("TRAINE");
    v1.set_bt(1.0);
    v1.set_nrm(0.95);
    v1.set_aet(JET);

    // Act
    float cost = v1.cost(20, 1000);


    // Assert
    EXPECT_NEAR(cost, 20000.0, 0.001);
}

TEST(VehicleTests, CostTest_AIR) {
    // Arrange
    Vehicle v1;
    v1.set_type(AIR);
    v1.set_mod("PLAINE");
    v1.set_bt(1.0);
    v1.set_nrm(0.95);
    v1.set_aet(TURBOPROP);

    // Act
    float cost = v1.cost(20, 5000);


    // Assert
    EXPECT_NEAR(cost, 150000.0, 0.001);
}
TEST(VehicleTests, ListTest1) {
    VehicleList VL = VehicleList();

    Vehicle v1 = Vehicle(RAIL, "Traine", 10);
    Vehicle v2 = Vehicle(AIR, "Plaine", 10, JET);
    Vehicle v3 = Vehicle(NAVAL, "Sheap", 10, 0.95);

    EXPECT_EQ(*VL[0], v1);
    EXPECT_EQ(*VL[1], v2);
    EXPECT_EQ(*VL[2], v3);
    EXPECT_EQ(VL.get_size(), 3);

}

TEST(VeicleTests, ExceptionTest) {
    Vehicle v1(BOOM, "TRAINE", 1, TURBOPROP);
    EXPECT_ANY_THROW(float cost = v1.cost(20, 10000););
}

TEST(VehicleTests, ListTest_INSERT) {
    VehicleList VL = VehicleList();
    
    Vehicle v1 = Vehicle(RAIL, "Traine", 100);
    Vehicle v2 = Vehicle(AIR, "Plaine", 100, JET);
    Vehicle v3 = Vehicle(NAVAL, "Sheap", 100, 0.95);


    VL.add(v1);
    VL.add(v2);
    VL.add(v3);
    

    EXPECT_EQ(*VL[3], v1);
    EXPECT_EQ(*VL[4], v2);
    EXPECT_EQ(*VL[5], v3);

}

TEST(VehicleTests, ListTest_REMOVE) {
    VehicleList VL = VehicleList();
    Vehicle train1(RAIL, "TRAINE_1", 1);
    Vehicle plane1(AIR, "PLAINE_1", 1, TURBOPROP);
    Vehicle boat1(NAVAL, "BOATE_1", 1, 0.95);
    Vehicle train2(RAIL, "TRAINE_2", 0.9);
    Vehicle plane2(AIR, "PLAINE_2", 1.4, JET);
    Vehicle boat2(NAVAL, "BOATE_2", 1.1, 0.92);


    VL.add(train1);
    VL.add(plane1);
    VL.add(boat1);
    VL.add(train2);
    VL.add(plane2);
    VL.add(boat2);
    VL.remove(2);



    EXPECT_EQ(*VL[2], train1);


}

TEST(VehicleTests, ListTest_SEARCH) {
    VehicleList VL = VehicleList();

    int mi = VL.search_min_cost(10, 50);

    EXPECT_EQ(mi, 2);
}