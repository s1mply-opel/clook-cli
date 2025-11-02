#include "tests/test_framework.hpp"
#include "attempt.hpp"
REGISTER_TEST(dummyTest){
    Attempt a; a.incCount(); int failed = 0;

    TEST("ErrorTesting", (a.getCurrent() == 2), "Some statement about what went wrong", &failed);

    return failed == 0;
}