#include "tests/test_framework.hpp"
#include "attempt.hpp"
REGISTER_TEST(dummyTest){
    Attempt a; a.incCount(); int failed = 0;

<<<<<<< HEAD
    TEST((a.getCurrent() == 2), "asdas", &failed);
=======
    TEST("ErrorTesting", (a.getCurrent() == 2), "Some statement about what went wrong", &failed);
>>>>>>> dev

    return failed == 0;
}