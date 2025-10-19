#include "tests/test_framework.hpp"
#include "attempt.hpp"
REGISTER_TEST(dummyTest){
    Attempt a; a.incCount(); int failed = 0;

    TEST((a.getCurrent() == 2), "asdas", &failed);

    return failed == 0;
}