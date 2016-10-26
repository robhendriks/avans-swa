//
// Created by robbie on 24-10-2016.
//

#include "gtest/gtest.h"
#include "person_json_repository.h"

class person_json_repository_fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    person_json_repository* repository;

    person_json_repository_fixture() : Test() {
        repository = new person_json_repository();
    }

    virtual ~person_json_repository_fixture() {
        delete repository;
    }
};

TEST_F(person_json_repository_fixture, add_test) {
    person* new_person = new person(1, "Robbie", 21);

    repository->load();
    repository->save(*new_person);
    repository->commit();

    // Call load again so the data is taken from the saved json file
    repository->load();
    person* get_person = repository->get_by_key(new_person->get_id());

    // Assertions
    EXPECT_EQ(new_person->get_id(), get_person->get_id());
    EXPECT_EQ(new_person->get_name(), get_person->get_name());
    EXPECT_EQ(new_person->get_age(), get_person->get_age());

    // Clean
    delete new_person;
    delete get_person;
}
