#include "tests/test_framework.hpp"
#include "attempt.hpp"

REGISTER_TEST(Attempt_defaultConstructorTest){
    Attempt atmp; int failed{0};

    TEST("DefaultCurrentValue", (atmp.getCurrent() == 0), "Default current value not 0", &failed);
    TEST("DefaultTargetValue", (atmp.getTarget() == 1), "Default target value not 1", &failed);
    TEST("DefaultNameValue", (atmp.getName() == ""), "Default name value not empty", &failed);

    return failed == 0;
}

REGISTER_TEST(Attempt_fullConstructorTest) {
    Attempt atmp("AttmptName", "desc", 5); int failed {0};

    TEST("AssignedNameValue", (atmp.getName() == "AttmptName"), "Attempt name can't be assigned", &failed);
    TEST("AssignedDescValue", (atmp.getDescription() == "desc"), "Attempt description can't be assigned", &failed);
    TEST("AssignedTargetValue", (atmp.getTarget() == 5), "Target value can't be assigned", &failed);

    return failed == 0;
}