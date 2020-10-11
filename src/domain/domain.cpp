#include "domain.hpp"
#include <memory>


using namespace domain;


// Domain Factory
SimpleDomain DomainFactory::IntRange(int first, int last) {
    return SimpleDomain(first, last);
}

/***************
* SimpleDomain *
****************/
SimpleDomain::SimpleDomain(int first, int last) : first_(first), last_(last) {}

size_t SimpleDomain::GetCardinality() const {
    return this->last_ - this->first_;
}

SimpleDomain SimpleDomain::GetComponent(int index) const {
    if(index != 0) {
        throw std::out_of_range("Index is < 0");
    }
    return *this;
}

size_t SimpleDomain::GetNumberOfComponents() const {
    return 1;
}

int SimpleDomain::GetFirst() const {
    return this->first_;
}

int SimpleDomain::GetLast() const {
    return this->last_;
}

SimpleDomain::iterator SimpleDomain::begin() const {
    return SimpleDomain::iterator(this->first_);
}

SimpleDomain::iterator SimpleDomain::end() const {
    return SimpleDomain::iterator(this->last_);
}

int SimpleDomain::IndexOfElement(DomainElement element) const {
    int i = 0;
    for(auto it = this->begin(), it_end = this->end(); it != it_end; ++it) {
        if(*it == element) { return i; }
        ++i;
    }
    return -1;
}

DomainElement SimpleDomain::ElementForIndex(int index) const {
    if(index < 0 || index > (first_ - last_ - 1)) {
        throw std::out_of_range("Index is < 0 or > " +
                std::to_string(first_ - last_ - 1) + "!\n");
    }
    return DomainElement({first_ + index});
}

bool SimpleDomain::operator==(const SimpleDomain& sd) const {
    return this->first_ == sd.first_ && this->last_ == sd.last_;
}
bool SimpleDomain::operator!=(const SimpleDomain& sd) const {
    return !(*this == sd);
}

/*************************
* SimpleDomain::iterator *
**************************/
void SimpleDomain::iterator::operator++() {
    ++curr_element_;
}

bool SimpleDomain::iterator::operator!=(const SimpleDomain::iterator& it) const {
    return curr_element_ != it.curr_element_;
}

bool SimpleDomain::iterator::operator==(const SimpleDomain::iterator& it) const {
    return this->curr_element_ == it.curr_element_;
}

DomainElement SimpleDomain::iterator::operator*() const {
    return DomainElement({curr_element_});
}


/*************************************************************************/


// CompositeDomain
CompositeDomain::CompositeDomain(std::vector<SimpleDomain> components) :
    components_(components) {
        create_cart_product();
    }

void CompositeDomain::create_cart_product() {
    std::vector<Digit> vd;

    // Start all of the iterators at the begining
    for(SimpleDomain sd : this->components_) {
        struct Digit d = {sd.begin(), sd.end(), sd.begin()};
        vd.push_back(d);
    }
    int i = 0;
    while(true) {
        // Construct first product vector by pulling
        // out the element of each vector via the iterator.
        std::vector<int> result_vec;
        for(std::vector<Digit>::iterator it = vd.begin(), it_end = vd.end();
            it != it_end; ++it) {
            result_vec.push_back((*(it->curr)).GetComponentValue(0));
        }
        this->elements_.push_back(DomainElement(result_vec));
        // Increment the rightmost one, and repeat.
        // When you reach the end, reset that one to the beginning and
        // increment next-to-last one.
        for(std::vector<Digit>::reverse_iterator it = vd.rbegin(), it_end = vd.rend();;) {
            ++(it->curr);
            if(it->curr == it->end) {
                if(it + 1 == it_end) {
                    // Last digit
                    return;
                } else {
                    // cascade
                    it->curr = it->begin;
                    ++it;
                }
            } else {
                // normaln
                break;
            }
        }
    }
}

size_t CompositeDomain::GetCardinality() const{
    size_t cardinality = 1;
    for(SimpleDomain sd : this->components_) {
        cardinality *= sd.GetCardinality();
    }
    return cardinality;
}

SimpleDomain CompositeDomain::GetComponent(int index) const{
    return this->components_.at(index);
}

size_t CompositeDomain::GetNumberOfComponents() const{
    return this->components_.size();
}

CompositeDomain::iterator CompositeDomain::begin() const {
    return CompositeDomain::iterator(this->elements_, 0);
}

CompositeDomain::iterator CompositeDomain::end() const {
    return CompositeDomain::iterator(this->elements_, this->elements_.size());
}

int CompositeDomain::IndexOfElement(DomainElement element) const {
    int i = 0;
    for(DomainElement el_ : elements_) {
        if(el_ == element) { return i; }
        ++i;
    }
    return -1;
}

DomainElement CompositeDomain::ElementForIndex(int index) const {
    size_t n = this->elements_.size();
    if(index < 0 || index >= n) {
        throw std::out_of_range("Index is < 0 or > " + std::to_string(n) + "!\n");
    }
    return this->elements_[index];
}

// CompositeDomain::iterator
void CompositeDomain::iterator::operator++() {
    ++curr_element_idx_;
}

bool CompositeDomain::iterator::operator!=(const CompositeDomain::iterator& it) const {
    return !(*this == it);
}

bool CompositeDomain::iterator::operator==(const CompositeDomain::iterator& it) const {
    return this->elements_ == it.elements_ && this->curr_element_idx_ == it.curr_element_idx_;
}

DomainElement CompositeDomain::iterator::operator*() const {
    return elements_[curr_element_idx_];
}
