#include "domain.hpp"
#include <memory>


using namespace domain;


// Domain
SimpleDomain DomainFactory::IntRange(int first, int last) {
    return SimpleDomain(first, last);
}

template<class Domain>
CompositeDomain Combine(const Domain& d1, const Domain& d2) {
    std::vector<SimpleDomain> components;
    for(int i = 0, n = d1.GetCardinality(); i < n; ++i) {
        SimpleDomain component = d1.GetComponent(i);
        components.push_back(component);
    }
    for(int i = 0, n = d2.GetCardinality(); i < n; ++i) {
        SimpleDomain component = d2.GetComponent(i);
        components.push_back(component);
    }
    return CompositeDomain(components);
}

// SimpleDomain
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


// CompositeDomain
CompositeDomain::CompositeDomain(std::vector<SimpleDomain> components) :
    components_(components) {
        create_cart_product();
    }

void CompositeDomain::create_cart_product() {
    
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

//TODO
CompositeDomain::iterator CompositeDomain::begin() const {
    return CompositeDomain::iterator(*this);
}

//TODO
CompositeDomain::iterator CompositeDomain::end() const {
    return CompositeDomain::iterator(*this);
}

//SimpleDomain::iterator
void SimpleDomain::iterator::operator++() {
    ++curr_element_;
}

bool SimpleDomain::iterator::operator!=(const SimpleDomain::iterator& it) const {
    return curr_element_ != it.curr_element_;
}

bool SimpleDomain::iterator::operator==(const SimpleDomain::iterator& it) const {
    return !(*this != it);
}

DomainElement SimpleDomain::iterator::operator*() const {
    return DomainElement({curr_element_});
}



void CompositeDomain::iterator::operator++() {
    ++curr_element_idx_;
}

bool CompositeDomain::iterator::operator!=(const CompositeDomain::iterator& it) const {
    return true;
}

bool CompositeDomain::iterator::operator==(const CompositeDomain::iterator& it) const {
    return true;
}

DomainElement CompositeDomain::iterator::operator*() const {
    return cart_product_elements_[curr_element_idx_];
}








