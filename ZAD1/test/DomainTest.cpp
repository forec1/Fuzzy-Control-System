#include <gtest/gtest.h>
#include <memory>
#include "../src/domain/domain.hpp"

using namespace domain;

class CompositeDomainTest : public ::testing::Test {
    protected:

        void SetUp() override {
            sd1 = DomainFactory::IntRange(0, 5);
            sd2 = DomainFactory::IntRange(0, 3);
            cd1 = DomainFactory::Combine(sd1, sd2);
        }

        SimpleDomain sd1;
        SimpleDomain sd2;
        CompositeDomain cd1;

        std::vector<DomainElement> ground_truth = {
            DomainElement({0, 0}),
            DomainElement({0, 1}),
            DomainElement({0, 2}),
            DomainElement({1, 0}),
            DomainElement({1, 1}),
            DomainElement({1, 2}),
            DomainElement({2, 0}),
            DomainElement({2, 1}),
            DomainElement({2, 2}),
            DomainElement({3, 0}),
            DomainElement({3, 1}),
            DomainElement({3, 2}),
            DomainElement({4, 0}),
            DomainElement({4, 1}),
            DomainElement({4, 2}),
        };
};

class SimpleDomainTest : public ::testing::Test {
    protected:

        void SetUp() override {
            sd2 = DomainFactory::IntRange(2, 10);
            sd_ptr1 = std::make_shared<SimpleDomain>(10, 30);
        }

        SimpleDomain sd1 = {-5, 5};
        SimpleDomain sd2;
        SimpleDomain sd3 = {0, 0};
        SimpleDomain sd4;
        std::shared_ptr<SimpleDomain> sd_ptr1;
};

TEST_F(CompositeDomainTest, ElementIndexTest) {
    EXPECT_EQ(ground_truth[0], cd1.ElementForIndex(0));
    EXPECT_EQ(ground_truth[5], cd1.ElementForIndex(5));
    EXPECT_EQ(ground_truth[14], cd1.ElementForIndex(14));
    EXPECT_EQ(cd1.IndexOfElement(DomainElement::Of({4, 1})), 13);
}

TEST_F(CompositeDomainTest, GetComponentTest) {
    EXPECT_THROW(cd1.GetComponent(-1), std::out_of_range);
    EXPECT_THROW(cd1.GetComponent(15), std::out_of_range);
    EXPECT_THROW(cd1.GetComponent(100), std::out_of_range);
    EXPECT_EQ(cd1.GetComponent(0), sd1);
    EXPECT_EQ(cd1.GetComponent(1), sd2);
}

TEST_F(CompositeDomainTest, GetCardinalityTest) {
    EXPECT_EQ(cd1.GetCardinality(), 15);
}

TEST_F(CompositeDomainTest, create_cart_productTest) {
    printf("Elementi domene cd1({0, 5}, {0, 3}):\n");
    int i = 0;
    for(CompositeDomain::iterator it = cd1.begin(), it_end = cd1.end();
            it != it_end; ++it, ++i) {
        EXPECT_EQ(*it, ground_truth[i]);
        std::cout <<"Element domene: "<< (*it).ToString() << std::endl;
    }
}

TEST_F(SimpleDomainTest, SimpleDomainIteratorTest) {
    int i = sd1.GetFirst();
    printf("Elementi domene sd1{-5, 5}:\n");
    for(auto it = sd1.begin(), it_end = sd1.end(); it != it_end; ++it, ++i) {
        printf("Element domene: %d\n", (*it).GetComponentValue(0));
        EXPECT_EQ((*it).GetComponentValue(0), i);
        EXPECT_TRUE(!(it == it_end));
    }

    i = sd2.GetFirst();
    printf("Elementi domene sd2{2, 10}:\n");
    for(auto it = sd2.begin(), it_end = sd2.end(); it != it_end; ++it, ++i) {
        printf("Element domene: %d\n", (*it).GetComponentValue(0));
        EXPECT_EQ((*it).GetComponentValue(0), i);
        EXPECT_TRUE(!(it == it_end));
    }

    i = sd_ptr1->GetFirst();
    printf("Elementi domene sd_ptr1{10, 30}:\n");
    for(auto it = sd_ptr1->begin(), it_end = sd_ptr1->end(); it != it_end; ++it, ++i) {
        printf("Element domene: %d\n", (*it).GetComponentValue(0));
        EXPECT_EQ((*it).GetComponentValue(0), i);
        EXPECT_TRUE(!(it == it_end));
    }

    i = 0;
    printf("Elementi domene sd3{0, 0}:\n");
    for(auto it = sd3.begin(), it_end = sd3.end(); it != it_end; ++it, ++i) {
        printf("Element domene: %d\n", (*it).GetComponentValue(0));
        EXPECT_EQ((*it).GetComponentValue(0), i);
        EXPECT_TRUE(!(it == it_end));
    }

    i = 0;
    printf("Elementi domene sd4:\n");
    for(auto it = sd4.begin(), it_end = sd4.end(); it != it_end; ++it, ++i) {
        printf("Element domene: %d\n", (*it).GetComponentValue(0));
        EXPECT_EQ((*it).GetComponentValue(0), i);
        EXPECT_TRUE(!(it == it_end));
    }
}

bool SimpleDomainEQ(const SimpleDomain *sd1, const SimpleDomain *sd2) {
    return sd1->GetFirst() == sd2->GetFirst() &&
        sd1->GetLast() == sd2->GetLast();
}

TEST_F(SimpleDomainTest, GetComponent) {
    EXPECT_THROW(sd1.GetComponent(-1), std::out_of_range);
    EXPECT_THROW(sd1.GetComponent(2), std::out_of_range);
    EXPECT_THROW(sd_ptr1->GetComponent(-1), std::out_of_range);
    EXPECT_THROW(sd_ptr1->GetComponent(2), std::out_of_range);

    SimpleDomain sd = sd1.GetComponent(0);
    EXPECT_TRUE(SimpleDomainEQ(&sd1, &sd)) << "sd1.first=" << sd1.GetFirst() << " sd1.last="
        << sd1.GetLast() << " sd_ptr->first=" << sd.GetFirst() << " sd_ptr->last=" <<
        sd.GetLast();
}

TEST_F(SimpleDomainTest, GetCardinalityOnEmpty) {
    EXPECT_EQ(sd3.GetCardinality(), 0);
    EXPECT_EQ(sd4.GetCardinality(), 0);
}

TEST_F(SimpleDomainTest, GetCardinalityNormal) {
    EXPECT_EQ(sd1.GetCardinality(), 10);
    EXPECT_EQ(sd2.GetCardinality(), 8);
}

TEST_F(SimpleDomainTest, GetCardinalityWithSharedPtr) {
    EXPECT_EQ(sd_ptr1->GetCardinality(), 20);
}
