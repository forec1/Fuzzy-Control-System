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

std::string DomainElement::ToString() const {
    std::string s = "(";
    for(auto it = values_.begin(); it != values_.end(); ++it) {
        s += std::to_string(*it);
        if(it + 1 != values_.end()) {
            s += " ";
        }
    }
    s += ")";
    return s;
}
