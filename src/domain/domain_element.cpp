#include "domain_element.hpp"

domain::DomainElement::DomainElement(domain::DomainElement&& other) noexcept :
    m_values(std::move(other.m_values)) {}

domain::DomainElement::DomainElement(const std::vector<int>& values) :
    m_values(values) {};

domain::DomainElement::DomainElement(std::vector<int>&& values) noexcept :
    m_values(std::move(values)) {}

size_t domain::DomainElement::GetNumberOfComponents() const {
    return m_values.size();
}

int domain::DomainElement::GetComponentValue(int index) const {
    return m_values[index];
}

bool domain::DomainElement::operator==(const DomainElement& e) const {
    return this->m_values == e.m_values;
}

domain::DomainElement& domain::DomainElement::operator=(DomainElement&& other) noexcept {
    if(this != &other) {
        this->m_values = std::move(other.m_values);
    }
    return *this;
}

domain::DomainElement& domain::DomainElement::operator=(const DomainElement& other) {
    if(*this != other) {
        this->m_values = other.m_values;
    }
    return *this;
}

bool domain::DomainElement::operator!=(const DomainElement& e) const {
    return !(*this == e);
}

std::string domain::DomainElement::ToString() const {
    std::string s("(");
    for(auto it = m_values.begin(); it != m_values.end(); ++it) {
        s += std::to_string(*it);
        if(it + 1 != m_values.end()) {
            s += " ";
        }
    }
    s += ")";
    return s;
}
