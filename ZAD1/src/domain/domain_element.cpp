#include "domain_element.hpp"

using namespace domain;

DomainElement::DomainElement(std::vector<int> values) : values_(values) {};

size_t DomainElement::GetNumberOfComponents() const {
    return values_.size();
}

int DomainElement::GetComponentValue(int index) const {
    return values_[index];
}

DomainElement DomainElement::Of(std::vector<int> values) {
    return DomainElement(values);
}

bool DomainElement::operator==(const DomainElement& e) const {
    return this->values_ == e.values_;
}

bool DomainElement::operator!=(const DomainElement& e) const {
    return !(*this == e);
}
