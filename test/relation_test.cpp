#include "../src/fuzzy/relation.hpp"
#include <gtest/gtest.h>
#include <unordered_map>

class RelationTest3 : public ::testing::Test {
    protected:
        void SetUp() override {
            r = domain::DomainFactory::Combine(u, u);

            r.set(domain::DomainElement({1, 1}), 1)
             .set(domain::DomainElement({2, 2}), 1)
             .set(domain::DomainElement({3, 3}), 1)
             .set(domain::DomainElement({4, 4}), 1)
             .set(domain::DomainElement({1, 2}), 0.3)
             .set(domain::DomainElement({2, 1}), 0.3)
             .set(domain::DomainElement({2, 3}), 0.5)
             .set(domain::DomainElement({3, 2}), 0.5)
             .set(domain::DomainElement({3, 4}), 0.2)
             .set(domain::DomainElement({4, 3}), 0.2);

            r2 = r;
        }

        SimpleDomain u = domain::DomainFactory::IntRange(1, 5);
        fuzzy_set::MutableFuzzySet<domain::CompositeDomain> r;
        fuzzy_set::MutableFuzzySet<domain::CompositeDomain> r2;

        std::vector<bool> gt = {false, true, true};
};

TEST_F(RelationTest3, test9) {
    ASSERT_FALSE(fuzzy_set::Relations::is_fuzzy_equivalence(r2));
    printf("Pocetna relacija nije neizrazita relacija simetrije -> OK\n");

    for(int i = 1; i <=3; ++i) {
        r2 = fuzzy_set::Relations::composition_of_binary_relations(r2, r);

        printf("Broj odrađenih kompozicija: %d. Relacija je:\n", i);

        domain::CompositeDomain d = r2.GetDomain();
        for(auto it = d.begin(), it_end = d.end(); it != it_end; ++it) {
            printf("mu(%s)=%lf\n", (*it).ToString().c_str(), r2.GetValueAt(*it));
        }
        EXPECT_EQ(gt[i-1], fuzzy_set::Relations::is_fuzzy_equivalence(r2));
        printf("Ova relacija je neizrazita relacija ekvivalencije? %d\n\n",
            fuzzy_set::Relations::is_fuzzy_equivalence(r2));
}

}

class RelationTest2 : public ::testing::Test {
    protected:

        void SetUp() override {
            r1.set(domain::DomainElement({1, 1}), 0.3)
               .set(domain::DomainElement({1, 2}), 1)
               .set(domain::DomainElement({3, 3}), 0.5)
               .set(domain::DomainElement({4, 3}), 0.5);

            r2.set(domain::DomainElement({1, 1}), 1)
               .set(domain::DomainElement({2, 1}), 0.5)
               .set(domain::DomainElement({2, 2}), 0.7)
               .set(domain::DomainElement({3, 3}), 1)
               .set(domain::DomainElement({3, 4}), 0.4);

            r1r2 = fuzzy_set::Relations::composition_of_binary_relations(r1, r2);

            ground_truth.push_back({domain::DomainElement({1, 1}), 0.5});
            ground_truth.push_back({domain::DomainElement({1, 2}), 0.7});
            ground_truth.push_back({domain::DomainElement({1, 3}), 0.0});
            ground_truth.push_back({domain::DomainElement({1, 4}), 0.0});
            ground_truth.push_back({domain::DomainElement({2, 1}), 0.0});
            ground_truth.push_back({domain::DomainElement({2, 2}), 0.0});
            ground_truth.push_back({domain::DomainElement({2, 3}), 0.0});
            ground_truth.push_back({domain::DomainElement({2, 4}), 0.0});
            ground_truth.push_back({domain::DomainElement({3, 1}), 0.0});
            ground_truth.push_back({domain::DomainElement({3, 2}), 0.0});
            ground_truth.push_back({domain::DomainElement({3, 3}), 0.5});
            ground_truth.push_back({domain::DomainElement({3, 4}), 0.4});
            ground_truth.push_back({domain::DomainElement({4, 1}), 0.0});
            ground_truth.push_back({domain::DomainElement({4, 2}), 0.0});
            ground_truth.push_back({domain::DomainElement({4, 3}), 0.5});
            ground_truth.push_back({domain::DomainElement({4, 4}), 0.4});
        }

        SimpleDomain u1 = domain::DomainFactory::IntRange(1, 5);
        SimpleDomain u2 = domain::DomainFactory::IntRange(1, 4);
        SimpleDomain u3 = domain::DomainFactory::IntRange(1, 5);

        fuzzy_set::MutableFuzzySet<CompositeDomain> r1 = {domain::DomainFactory::Combine(u1, u2)};
        fuzzy_set::MutableFuzzySet<CompositeDomain> r2 = {domain::DomainFactory::Combine(u2, u3)};
        fuzzy_set::MutableFuzzySet<CompositeDomain> r1r2;


        std::vector<std::pair<domain::DomainElement, double>> ground_truth;
};

TEST_F(RelationTest2, test8) {
    domain::CompositeDomain d = r1r2.GetDomain();
    int i = 0;
    for(auto it = d.begin(), it_end = d.end(); it != it_end; ++it) {
        EXPECT_DOUBLE_EQ(ground_truth[i++].second, r1r2.GetValueAt(*it));
        printf("mu(%s)=%lf\n", (*it).ToString().c_str(), r1r2.GetValueAt(*it));
    }
}

class RelationTest1 : public ::testing::Test {
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


TEST_F(RelationTest1, test1) {
    ASSERT_TRUE(fuzzy_set::Relations::is_U_times_U_relation(r1)) << "r1 nije definiran na UxU\n";
    printf("r1 je definiran na UxU -> OK\n");
}

TEST_F(RelationTest1, test2) {
    ASSERT_TRUE(fuzzy_set::Relations::is_symmetric(r1)) << "r1 nije simetricna\n";
    printf("r1 je simetricna -> OK\n");
}

TEST_F(RelationTest1, test3) {
    ASSERT_FALSE(fuzzy_set::Relations::is_symmetric(r2)) << "r2 je simetricna\n";
    printf("r2 nije simetricna -> OK\n");
}

TEST_F(RelationTest1, test4) {
    ASSERT_TRUE(fuzzy_set::Relations::is_reflexive(r1)) << "r1 nije refleksivna\n";
    printf("r1 je refleksivna -> OK\n");
}

TEST_F(RelationTest1, test5) {
    ASSERT_FALSE(fuzzy_set::Relations::is_reflexive(r3)) << "r3 je refleksivna\n";
    printf("r3 nije refleksivna -> OK\n");
}

TEST_F(RelationTest1, test6) {
    ASSERT_FALSE(fuzzy_set::Relations::is_max_min_transitive(r3)) << "r3 je max-min transitivna\n";
    printf("r3 nije max-min tranzitivna -> OK\n");
}

TEST_F(RelationTest1, test7) {
    ASSERT_TRUE(fuzzy_set::Relations::is_max_min_transitive(r4)) << "r4 nije max-min tranzitivna\n";
    printf("r4 je max-min tranzitivna -> OK\n");
}
