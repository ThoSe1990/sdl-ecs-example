#include "cwt_gtest.hpp"

int main(int argc, char** argv)
{
    std::cout << "************************" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}