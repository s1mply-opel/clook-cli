#include "tests/test_framework.hpp"
#include "milestone.hpp"

REGISTER_TEST(Milestone_ConstructorTest) {
    int failed{0};

    auto milestone = Milestone("Learning C++", "desc");
    TEST("AssignNameTest", (milestone.getName() == "Learning C++"),"Cannot assign name to milestone",&failed);
    TEST("AssignDescriptionTest", (milestone.getDescription() == "desc"),"Cannot assign description to milestone",&failed);

    return failed == 0;
}

REGISTER_TEST(Milestone_AttemptManagement) {
    int failed{0};
     
    auto m = Milestone("Clook", "Clook Description");
    m.setSessionDuration(1);
    m.createAttempt("Making UI", "desc", 3);
    



    return (failed == 0);
}