#include <gtest/gtest.h>
#include "../src/fuzzy_set/fuzzy_set.hpp"

class FuzzySetTest : public ::testing::Test {
    protected:

        void SetUp() override {
            set1.set(domain::DomainElement::Of({0}), 1.0)
                .set(domain::DomainElement::Of({1}), 0.8)
                .set(domain::DomainElement::Of({2}), 0.6)
                .set(domain::DomainElement::Of({3}), 0.4)
                .set(domain::DomainElement::Of({4}), 0.2);
        }

        domain::SimpleDomain d = DomainFactory::IntRange(0, 11);
        fuzzy_set::MutableFuzzySet<domain::SimpleDomain> set1 = {d};
        std::vector<double> gt = {1.0, 0.8, 0.6, 0.4, 0.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

        domain::SimpleDomain d2 = DomainFactory::IntRange(-5, 6);
        function::LambdaFunction function = fuzzy_set::StandardFuzzySets
            <function::LambdaFunction>::lambda_function(
                    d2.IndexOfElement(domain::DomainElement::Of({-4})),
                    d2.IndexOfElement(domain::DomainElement::Of({0})),
                    d2.IndexOfElement(domain::DomainElement::Of({4}))
                    );
        fuzzy_set::CalculatedFuzzySet<
            domain::SimpleDomain,
            function::LambdaFunction
        > set2 = {d2, function};

        std::vector<double> gt2 = {0.0, 0.0, 0.25, 0.5, 0.75, 1.0, 0.75, 0.5, 0.25, 0.0, 0.0};
};


TEST_F(FuzzySetTest, CalculatedFuzzySetTest) {
    ASSERT_EQ(set2.GetDomain().GetCardinality(), 11);

    printf("Set2:\n");
    int i = 0;
    for(auto it = set2.GetDomain().begin(), it_end = set2.GetDomain().end();
            it != it_end; ++it) {

        double val = set2.GetValueAt(*it);
        EXPECT_EQ(val, gt2[i++]);
        printf("d(%d) = %.6lf\n",(*it).GetComponentValue(0), val);
    }

}


TEST_F(FuzzySetTest, MutableFuzzySetTest) {
    ASSERT_EQ(set1.GetDomain().GetCardinality(), 11);

    printf("Set1:\n");

    int i = 0;
    for(auto it = set1.GetDomain().begin(), it_end = set1.GetDomain().end();
            it != it_end; ++it) {

        double val = set1.GetValueAt(*it);
        EXPECT_EQ(val, gt[i++]);
        printf("d(%d) = %.6lf\n", i, val);
    }
}
