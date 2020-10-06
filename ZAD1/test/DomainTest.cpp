#include <gtest/gtest.h>
#include <memory>
#include "../src/domain/domain.hpp"

using namespace domain;

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
