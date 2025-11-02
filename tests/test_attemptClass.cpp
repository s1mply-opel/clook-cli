#include "tests/test_framework.hpp"
#include "attempt.hpp"

<<<<<<< HEAD
REGISTER_TEST(defaultConstructorTest){
    Attempt atmp; int failed{0};

    TEST((atmp.getCurrent() == 1), "Default current value not 0", &failed);
    TEST((atmp.getTarget() == 2), "Default target value not 1", &failed);
    TEST((atmp.getName() == "A"), "Default name value not empty", &failed);
=======
REGISTER_TEST(Attempt_defaultConstructorTest){
    Attempt atmp; int failed{0};

    TEST("DefaultCurrentValue", (atmp.getCurrent() == 0), "Default current value not 0", &failed);
    TEST("DefaultTargetValue", (atmp.getTarget() == 1), "Default target value not 1", &failed);
    TEST("DefaultNameValue", (atmp.getName() == ""), "Default name value not empty", &failed);
>>>>>>> dev

    return failed == 0;
}

<<<<<<< HEAD
REGISTER_TEST(targetConstructorTest) {
    Attempt atmp(2); int failed {0};

    TEST((atmp.getTarget() == 2), "Target value can't be assigned", &failed);

    return failed == 0;
}

REGISTER_TEST(nameConstructorTest) {
    Attempt atmp("AttmptName"); int failed {0};

    TEST((atmp.getName() == "AttmptName"), "Attempt name can't be assigned", &failed);

    return failed == 0;
}

REGISTER_TEST(fullConstructorTest) {
    Attempt atmp("AttmptName", 5); int failed {0};

    TEST((atmp.getName() == "AttmptName"), "Attempt name can't be assigned", &failed);
    TEST((atmp.getTarget() == 5), "Target value can't be assigned", &failed);
=======
REGISTER_TEST(Attempt_fullConstructorTest) {
    Attempt atmp("AttmptName", "desc", 5); int failed {0};

    TEST("AssignedNameValue", (atmp.getName() == "AttmptName"), "Attempt name can't be assigned", &failed);
    TEST("AssignedDescValue", (atmp.getDescription() == "desc"), "Attempt description can't be assigned", &failed);
    TEST("AssignedTargetValue", (atmp.getTarget() == 5), "Target value can't be assigned", &failed);
>>>>>>> dev

    return failed == 0;
}