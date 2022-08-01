#include <gtest/gtest.h>

extern "C"
{
    #include <adhan/astronomical.h>
    #include <adhan/prayer_times.h>
}

int main(int argc, char **argv) {
    putenv((char *) "TZ=UTC");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
