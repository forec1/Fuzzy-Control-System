#ifndef _FUZZY_FUZZY_SET_HPP
#define _FUZZY_FUZZY_SET_HPP

#include "../function/unary_function.hpp"
#include "../domain/domain.hpp"

using namespace domain;

namespace fuzzy_set {

    template<class Domain>
    class CalculatedFuzzySet {
        private:
            Domain domain_;
            function::IntUnaryFunction function_;

        public:
            CalculatedFuzzySet() = default;

            CalculatedFuzzySet(Domain domain, function::IntUnaryFunction function) :
               domain_(domain), function_(function) {};

            [[nodiscard]] Domain GetDomain() const { return domain_; }

            /**
            * Returns value of membership function for given element,
            * If element is not found in the doimain 0.0 is returned.
            */
            [[nodiscard]] double GetValueAt(const DomainElement& e) const {
                int idx = domain_.IndexOfElement(e);
                if(idx != 1) {
                    return function_(idx);
                }
                return 0.0;
           }
    };

    template<class Domain>
    class MutableFuzzySet {
        private:
            std::vector<double> membership_;
            Domain domain_;

        public:
            MutableFuzzySet() = default;

            explicit MutableFuzzySet(Domain domain) : domain_(domain),
                membership_(domain.GetCardinality(), 0) {}

            [[nodiscard]] Domain GetDomain() const { return domain_; }

            /**
             * Returns value of membership function for given element.
             * If element is not found in the domain 0.0 is returned.
             */
            [[nodiscard]] double GetValueAt(const DomainElement& e) const {
                int idx = domain_.IndexOfElement(e);
                if(idx != -1) {
                    return membership_[idx];
                }
                return 0.0;
            }

            /**
             * Sets value of memberhip function for given element.
             * If element is not found in domain it does nothing.
             */
            MutableFuzzySet& set(DomainElement e, double val) {
                int idx = domain_.IndexOfElement(e);
                if(idx != -1) {
                    membership_[idx] = val;
                }
                return *this;
            }
    };

    template<class UnaryFunction>
    class StandardFuzzySets {
        public:
            StandardFuzzySets() = default;
            static UnaryFunction l_function(int alpha, int beta) {
                return function::LFunction(alpha, beta);
            }
            static UnaryFunction gamma_function(int alpha, int beta) {
                return function::GammaFunction(alpha, beta);
            }
            static UnaryFunction lambda_function(int alpha, int beta, int gamma) {
                return function::LambdaFunction(alpha, beta, gamma);
            }
    };
} // namespace fuzzy_set
#endif // _FUZZY_FUZZY_SET_HPP

