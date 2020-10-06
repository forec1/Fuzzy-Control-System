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
        std::vector<int> values_;

    public:
       DomainElement(std::vector<int> values);

       /**
        * Returns size of the tuple.
        */
       size_t GetNumberOfComponents() const;

       /**
        * Returns value of the tuple at given index.
        */
       int GetComponentValue(int index) const;

       /**
        * Creates new DomainElement with specified values.
        */
       static DomainElement Of(std::vector<int> values);

       bool operator==(const DomainElement& e) const;
       bool operator!=(const DomainElement& e) const;
};
}
