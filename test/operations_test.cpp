#include "../src/operation/operation.hpp"
#include <gtest/gtest.h>

class OperationTest : public ::testing::Test {
    protected:

        void SetUp() override {
            set1.set(domain::DomainElement({0}), 1.0)
                .set(domain::DomainElement({1}), 0.8)
                .set(domain::DomainElement({2}), 0.6)
                .set(domain::DomainElement({3}), 0.4)
                .set(domain::DomainElement({4}), 0.2);
        }

        SimpleDomain d = domain::DomainFactory::IntRange(0, 11);
        fuzzy_set::MutableFuzzySet<domain::SimpleDomain> set1{d};
        std::vector<double> gt_not = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
        std::vector<double> gt_u = {1.0, 0.8, 0.6, 0.6, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
        std::vector<double> gt_h = {0.0, 0.16, 0.24, 0.24, 0.16, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
};


void check_and_print(MutableFuzzySet<SimpleDomain> set, std::vector<double> gt, std::string heading) {
    std::cout<< heading << std::endl;
    int i = 0;
    for(auto it = set.GetDomain().begin(), it_end = set.GetDomain().end();
            it != it_end; ++it) {

        double val = set.GetValueAt(*it);
        EXPECT_DOUBLE_EQ(val, gt[i++]);
        printf("d(%d) = %.6lf\n",(*it).GetComponentValue(0), val);
    }
    printf("\n");
}


TEST_F(OperationTest, OperationsTest) {
    printf("set1:\n");
    for(auto it = set1.GetDomain().begin(), it_end = set1.GetDomain().end();
            it != it_end; ++it) {

        double val = set1.GetValueAt(*it);
        printf("d(%d) = %.6lf\n",(*it).GetComponentValue(0), val);
    }
    printf("\n");

    MutableFuzzySet<SimpleDomain> not_set1 = operation::Operations::
        unary_operation(set1, operation::Operations::zadeh_not());
    check_and_print(not_set1, gt_not, "not_set1:");

    MutableFuzzySet<SimpleDomain> set_union = operation::Operations::
        binary_operation(set1, not_set1, operation::Operations::zadeh_or());
    check_and_print(set_union, gt_u, "set1 union not_set1:");


    MutableFuzzySet<SimpleDomain> hinters = operation::Operations::
        binary_operation(set1, not_set1, operation::HamacherTNormFunction(1.0));
    check_and_print(hinters, gt_h,
            "Set1 intersection with notSet1 using parameterised Hamacher T norm with parametr 1.0:");

    printf("set1:\n");
    for(auto it = set1.GetDomain().begin(), it_end = set1.GetDomain().end();
            it != it_end; ++it) {

        double val = set1.GetValueAt(*it);
        printf("d(%d) = %.6lf\n",(*it).GetComponentValue(0), val);
    }

}
