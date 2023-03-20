#include <gtest/gtest.h>

#include <vehicles/vehicles.h>

TEST(VehicleTests, SumStubTest1) {
    // Arrange
    Vehicles::Vehicles Vehi
    
    // Act
    int r = sum_stub(lhs, rhs);
    
    // Assert
    EXPECT_EQ(r, 5);
}

TEST(VehicleTests, SumStubTest2) {
    // Arrange
    int lhs = -1;
    int rhs = 3;
    
    // Act
    int r = sum_stub(lhs, rhs);
    
    // Assert
    EXPECT_EQ(r, 2);
}
