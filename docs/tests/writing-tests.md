Writing a Test Suite

To create a new test suite for a particular object, follow these steps:

1. File Naming

Name your file following this convention:

test_<object>.cpp


Example:

test_attempt.cpp

2. Includes

At the top of the file, include the test framework and any other required headers:

#include "tests/framework.hpp"
#include "Attempt.hpp" // Example: include the class being tested
#include <string>      // Any additional libraries you need

3. Writing Tests

Each test suite is composed of one or more registered test blocks using the following pattern:

REGISTER_TEST(<MainTest>) {
    int failed{0};

    TEST(<ChildTest>, (<Condition>), <Message>, &failed);
    TEST(<ChildTest>, (<Condition>), <Message>, &failed);
    // ... add more TEST() calls as needed

    return failed == 0;
}

🧩 Parameter Guide
Placeholder	Meaning
<MainTest>	A descriptive name for the overall object or module being tested.
<ChildTest>	A more specific section or function of the object being tested.
<Condition>	The boolean expression that must be true for the test to pass.
<Message>	The error message shown when <Condition> evaluates to false.
Example
REGISTER_TEST(AttemptClass) {
    int failed{0};

    TEST(defaultConstructor, (atmp1.getCurrent() == 0), "Default current value should be 0", &failed);
    TEST(defaultConstructor, (atmp1.getTarget() == 1), "Default target value should be 1", &failed);

    return failed == 0;
}

4. Notes

Every test must be enclosed within a REGISTER_TEST(<MainTest>) { ... } block.

Repeat this structure for each distinct group of tests.

Currently, timing benchmarks are not supported.