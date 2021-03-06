#ifndef _DOMAIN_DOMAIN_HPP
#define _DOMAIN_DOMAIN_HPP

#include "domain_element.hpp"
#include <memory>

namespace domain {

/**
 * Represents simple domain whose elements are a subset of a set of integers;
 * "degraded" n-tuples where n=1.
 */
class SimpleDomain {
    private:
        // Lower bound of interval
        int first_{0};

        // Higher bound of interval
        int last_{0};

    public:

        class iterator {
            public:
                explicit iterator(int curr_element) : curr_element_(curr_element) {};

                void operator++();
                bool operator!=(const iterator& iterator) const;
                bool operator==(const iterator& iterator) const;
                iterator operator+(int offset) const;
                DomainElement operator*() const;
            private:
                int curr_element_;
        };

        /**
         * Copy constructor
         */
        SimpleDomain(const SimpleDomain& other) = default;

        SimpleDomain(SimpleDomain&& other) noexcept : first_(other.first_),
            last_(other.last_) {}

        SimpleDomain() = default;
        ~SimpleDomain() = default;

        /**
         * Constructors that recieves interval bounds.
         *
         * ...
         *
         * @param first Lower interval bound (inlcuded).
         * @param last Higher interval bound (excluded).
         */
        SimpleDomain(int first, int last);

        /**
         * Returns cardinality of domain.
         */
        [[nodiscard]] size_t GetCardinality() const;

        /**
         * Returns itself.
         * Index must be greater or equals than (>=) 0 and lower than the number of
         * components, otherwise std::out_of_range exception is thrown.
         *
         * ...
         *
         * @param index Index of component. Must be >= 0 and < number of components.
         * @throws std::out_of_range If index is < 0 or >= number of components.
         */
        [[nodiscard]] SimpleDomain GetComponent(int index) const;

        /**
        * Returns the number of simple domains participating in the
        * Cartesian set, but because this class represents simple domain
        * only that domain is in the Cartesian set, so it returns 1.
        */
        [[nodiscard]] size_t GetNumberOfComponents() const;

        /**
         * Returns ordinal number of given domain element.
         */
        [[nodiscard]] int IndexOfElement(const DomainElement& element) const;

        /**
         * Returns domain element at given ordinal number.
         *
         * ...
         *
         * @param index Ordinal number of the domain element.
         * @return Domain element at given ordinal number.
         */
        [[nodiscard]] DomainElement ElementForIndex(int index) const;

        /**
         * Returns a read iterator that points to the first element in the domain. Iteration is done in ordinary element order.
         */
        [[nodiscard]] iterator begin() const;

        /**
         * Returns a read iterator that points to the last element in the domain. Iteration is done in ordinary element order.
         */
        [[nodiscard]] iterator end() const;

        //getters
        [[nodiscard]] int GetFirst() const;
        [[nodiscard]] int GetLast() const;

        bool operator==(const SimpleDomain& sd) const;
        bool operator!=(const SimpleDomain& sd) const;
        SimpleDomain& operator=(const SimpleDomain& other);
        SimpleDomain& operator=(SimpleDomain&& other) noexcept;
};

class CompositeDomain {
    private:
        /**
         * Simple domain components that make this composit domain.
         */
        std::vector<SimpleDomain> components_;

        /**
         * Elements of this composite domain; ordered n-tuples;
         */
        std::vector<DomainElement> elements_;

        /**
         * Creates elements of this domain by using cartesian product of
         * simple domain components. Output is stored in private member
         * variable 'elements_'.
         */
        void create_cart_product();

        /**
         * Helper struct for implementing Cartesian product.
         */
        struct Digit {
            SimpleDomain::iterator begin;
            SimpleDomain::iterator end;
            SimpleDomain::iterator curr;
        };

    public:

        class iterator {
            public:
                iterator(const std::vector<DomainElement>& elements,
                        int curr_element_idx) :
                    elements_(elements), curr_element_idx_(curr_element_idx){};

                void operator++();
                bool operator!=(const iterator& it) const;
                bool operator==(const iterator& it) const;
                DomainElement operator*() const;

            private:
                const std::vector<DomainElement> &elements_;
                int curr_element_idx_;

        };

        CompositeDomain() = default;

        /**
         * Move constructor
         */
        CompositeDomain(CompositeDomain&& other) noexcept :
            components_(std::move(other.components_)),
            elements_(std::move(other.elements_)) {}

        /**
         * Copy constructor
         */
        CompositeDomain(const CompositeDomain& other) = default;

        explicit CompositeDomain(std::vector<SimpleDomain>&& components);
        ~CompositeDomain() = default;

        /**
         * Returns cardinality of domain.
         */
        [[nodiscard]] size_t GetCardinality() const;

        /**
         * Returns component of Cartesian set at given index.
         * Index must be greater or equals than (>=) 0 and lower than the number of
         * components, otherwise std::out_of_range exception is thrown.
         *
         * ...
         *
         * @param index Index of component. Must be >= 0 and < number of components.
         * @throws std::out_of_range If index is < 0 or >= number of components.
         */
        [[nodiscard]] SimpleDomain GetComponent(int index) const;

        /**
        * Returns the number of simple domains participating in the
        * Cartesian set. Elements of simple domain are "degraded" n-tuples
        * where n=1. Elements of Cartesian set are obtained with Cartesian product of simple
        * domains (ordered n-tuples where n>1)
        *
        * ...
        *
        * @see SimpleDomain
        */
        [[nodiscard]] size_t GetNumberOfComponents() const;

        /**
         * Returns ordinal number of given domain element.
         */
        [[nodiscard]] int IndexOfElement(const DomainElement& element) const;

        /**
         * Returns domain element at given ordinal number.
         *
         * ...
         *
         * @param index Ordinal number of the domain element.
         * @return Domain element at given ordinal number.
         */
        [[nodiscard]] DomainElement ElementForIndex(int index) const;

        /**
         * Returns a read iterator that points to the first element in the domain. Iteration is done in ordinary element order.
         */
        [[nodiscard]] iterator begin() const;

        /**
         * Returns a read iterator that points to the last element in the domain. Iteration is done in ordinary element order.
         */
        [[nodiscard]] iterator end() const;

        CompositeDomain& operator=(const CompositeDomain& other);
        CompositeDomain& operator=(CompositeDomain&& other) noexcept;
};


class DomainFactory {
    public:

        /**
         * Creates new domain with integer elements in interval [first, last).
         *
         * ...
         *
         * @param first Lower bound of interval (included).
         * @param last Higher bound of interval (excluded).
         */
        static SimpleDomain IntRange(int first, int last);

        /**
         * Creates new domain by combining two given domains with Cartesian product
         * and returns it.
         */
        template<class Domain>
        static CompositeDomain Combine(const Domain& d1, const Domain& d2) {
            std::vector<SimpleDomain> components;
            for(int i = 0, n = d1.GetNumberOfComponents(); i < n; ++i) {
                SimpleDomain component = d1.GetComponent(i);
                components.push_back(component);
            }
            for(int i = 0, n = d2.GetNumberOfComponents(); i < n; ++i) {
                SimpleDomain component = d2.GetComponent(i);
                components.push_back(component);
            }
            return CompositeDomain(std::move(components));
        }
};

} //namespace domain
#endif // _DOMAIN_DOMAIN_HPP
