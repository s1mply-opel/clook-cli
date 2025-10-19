#include "tests/test_framework.hpp"
#include "attempt.hpp"

REGISTER_TEST(defaultConstructorTest){
    Attempt atmp; int failed{0};

    TEST((atmp.getCurrent() == 1), "Default current value not 0", &failed);
    TEST((atmp.getTarget() == 2), "Default target value not 1", &failed);
    TEST((atmp.getName() == "A"), "Default name value not empty", &failed);

    return failed == 0;
}

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

    return failed == 0;
}