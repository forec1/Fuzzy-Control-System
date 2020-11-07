#ifndef DOMAIN_DOMAIN_ELEMENT_HPP
#define DOMAIN_DOMAIN_ELEMENT_HPP

#include <string>
#include <vector>

namespace domain {

/**
 * Models one element of fuzzy set domain. Instances of this class
 * represent concrete orderd n-tuples.
 */
class DomainElement {
    private:

        /**
         * Values of n-tuples.
         */
        std::vector<int> m_values;

    public:

        /**
         * Copy constructor
         */
        DomainElement(const DomainElement& other) = default;

        /**
         * Move constructor
         */
        DomainElement(DomainElement&& other) noexcept;

        explicit DomainElement(const std::vector<int>& values);
        explicit DomainElement(std::vector<int>&& values) noexcept;

        /**
         * Destructor
         */
        ~DomainElement() = default;

        /**
        * Returns size of the tuple.
        */
        [[nodiscard]] size_t GetNumberOfComponents() const;

        /**
        * Returns value of the tuple at given index.
        */
        [[nodiscard]] int GetComponentValue(int index) const;

        bool operator==(const DomainElement& e) const;
        bool operator!=(const DomainElement& e) const;

        /**
         * Move assigment
         */
        DomainElement& operator=(DomainElement&& other) noexcept;

        /**
         * Copy assigment
         */
        DomainElement& operator=(const DomainElement& other);;

        [[nodiscard]] std::string ToString() const;
};
} //namespace domain

#endif  // DOMAIN_DOMAIN_ELEMENT_HPP
