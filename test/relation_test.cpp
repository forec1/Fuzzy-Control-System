#include "../src/fuzzy/relation.hpp"
#include <gtest/gtest.h>

class RelationTest : public ::testing::Test {
    protected:

        void SetUp() override {
            r1.set(domain::DomainElement({1, 1}), 1)
              .set(domain::DomainElement({2, 2}), 1)
              .set(domain::DomainElement({3, 3}), 1)
              .set(domain::DomainElement({4, 4}), 1)
              .set(domain::DomainElement({5, 5}), 1)
              .set(domain::DomainElement({3, 1}), 0.5)
              .set(domain::DomainElement({1, 3}), 0.5);

            r2.set(domain::DomainElement({1, 1}), 1)
              .set(domain::DomainElement({2, 2}), 1)
              .set(domain::DomainElement({3, 3}), 1)
              .set(domain::DomainElement({4, 4}), 1)
              .set(domain::DomainElement({5, 5}), 1)
              .set(domain::DomainElement({3, 1}), 0.5)
              .set(domain::DomainElement({1, 3}), 0.1);

            r3.set(domain::DomainElement({1, 1}), 1)
              .set(domain::DomainElement({2, 2}), 1)
              .set(domain::DomainElement({3, 3}), 0.3)
              .set(domain::DomainElement({4, 4}), 1)
              .set(domain::DomainElement({5, 5}), 1)
              .set(domain::DomainElement({1, 2}), 0.6)
              .set(domain::DomainElement({2, 1}), 0.6)
              .set(domain::DomainElement({2, 3}), 0.7)
              .set(domain::DomainElement({3, 2}), 0.7)
              .set(domain::DomainElement({3, 1}), 0.5)
              .set(domain::DomainElement({1, 3}), 0.5);

            r4.set(domain::DomainElement({1, 1}), 1)
              .set(domain::DomainElement({2, 2}), 1)
              .set(domain::DomainElement({3, 3}), 1)
              .set(domain::DomainElement({4, 4}), 1)
              .set(domain::DomainElement({5, 5}), 1)
              .set(domain::DomainElement({1, 2}), 0.4)
              .set(domain::DomainElement({2, 1}), 0.4)
              .set(domain::DomainElement({2, 3}), 0.5)
              .set(domain::DomainElement({3, 2}), 0.5)
              .set(domain::DomainElement({3, 1}), 0.4)
              .set(domain::DomainElement({1, 3}), 0.4);
        }

        domain::SimpleDomain u = domain::DomainFactory::IntRange(1, 6);
        domain::CompositeDomain u2 = domain::DomainFactory::Combine(u, u);

        fuzzy_set::MutableFuzzySet<domain::CompositeDomain> r1 = {u2};
        fuzzy_set::MutableFuzzySet<domain::CompositeDomain> r2 = {u2};
        fuzzy_set::MutableFuzzySet<domain::CompositeDomain> r3 = {u2};
        fuzzy_set::MutableFuzzySet<domain::CompositeDomain> r4 = {u2};
};


TEST_F(RelationTest, test1) {
    ASSERT_TRUE(fuzzy_set::Relations::is_U_times_U_relation(r1)) << "r1 nije definiran na UxU\n";
    printf("r1 je definiran na UxU -> OK\n");
}

TEST_F(RelationTest, test2) {
    ASSERT_TRUE(fuzzy_set::Relations::is_symmetric(r1)) << "r1 nije simetricna\n";
    printf("r1 je simetricna -> OK\n");
}

TEST_F(RelationTest, test3) {
    ASSERT_FALSE(fuzzy_set::Relations::is_symmetric(r2)) << "r2 je simetricna\n";
    printf("r2 nije simetricna -> OK\n");
}

TEST_F(RelationTest, test4) {
    ASSERT_TRUE(fuzzy_set::Relations::is_reflexive(r1)) << "r1 nije refleksivna\n";
    printf("r1 je refleksivna -> OK\n");
}

TEST_F(RelationTest, test5) {
    ASSERT_FALSE(fuzzy_set::Relations::is_reflexive(r3)) << "r3 je refleksivna\n";
    printf("r3 nije refleksivna -> OK\n");
}

TEST_F(RelationTest, test6) {
    ASSERT_FALSE(fuzzy_set::Relations::is_max_min_transitive(r3)) << "r3 je max-min transitivna\n";
    printf("r3 nije max-min tranzitivna -> OK\n");
}

TEST_F(RelationTest, test7) {
    ASSERT_TRUE(fuzzy_set::Relations::is_max_min_transitive(r4)) << "r4 nije max-min tranzitivna\n";
    printf("r4 je max-min tranzitivna -> OK\n");
}
