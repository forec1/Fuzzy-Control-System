#include "fuzzy_set.hpp"
#include <math.h>
#include <limits>

namespace fuzzy_set {

    class Relations {
        public:
            Relations() {}

            /**
             * Checks whether the domain over which the fuzzy set
             * of Cartesian product is defined is UxU.
             */
            template<class FuzzySet>
            static bool is_U_times_U_relation(const FuzzySet& relation);

            /**
             * Checks whether it is a symmetric fuzzy relation
             * defined over a domain of the form U x U.
             */
            template<class FuzzySet>
            static bool is_symmetric(const FuzzySet& relation);

            template<class FuzzySet>
            static bool is_reflexive(const FuzzySet& relation);

            template<class FuzzySet>
            static bool is_max_min_transitive(const FuzzySet& relation);
    };

    template<class FuzzySet>
    bool Relations::is_max_min_transitive(const FuzzySet& relation) {
        if(!is_U_times_U_relation(relation)) { return false; }

        domain::CompositeDomain cd = relation.GetDomain();
        for(auto it1 = cd.begin(), it1_end = cd.end(); it1 != it1_end; ++it1) {
            for(auto it2 = cd.begin(), it2_end = cd.end(); it2 != it2_end; ++it2) {
                if((*it1).GetComponentValue(1) != (*it2).GetComponentValue(0)) {
                    continue;
                }

                int e1 = (*it1).GetComponentValue(0);
                int e2 = (*it2).GetComponentValue(1);
                if(relation.GetValueAt(domain::DomainElement::Of({e1, e2})) < std::min(
                                relation.GetValueAt(*it1),
                                relation.GetValueAt(*it2)
                                )) {
                    return false;
                }
            }
        }
        return true;
    }

    template<class FuzzySet>
    bool Relations::is_reflexive(const FuzzySet& relation) {
        if(!is_U_times_U_relation(relation)) { return false; }

        domain::CompositeDomain cd = relation.GetDomain();
        domain::SimpleDomain sd = cd.GetComponent(0);

        for(auto it = sd.begin(), it_end = sd.end(); it != it_end; ++it) {
            int e = (*it).GetComponentValue(0);
            if(fabs(relation.GetValueAt(domain::DomainElement::Of({e, e})) - 1.0) > std::numeric_limits<double>::epsilon()) {
                return false;
            }
        }
        return true;
    }

    template<class FuzzySet>
    bool Relations::is_U_times_U_relation(const FuzzySet& relation) {
        if(relation.GetDomain().GetNumberOfComponents() != 2) {
            return false;
        };
        return relation.GetDomain().GetComponent(0) == relation.GetDomain().GetComponent(1);
    }

    template<class FuzzySet>
    bool Relations::is_symmetric(const FuzzySet& relation) {
        if(!is_U_times_U_relation(relation)) { return false; }

        domain::CompositeDomain cd = relation.GetDomain();
        domain::SimpleDomain sd1 = cd.GetComponent(0);
        domain::SimpleDomain sd2 = cd.GetComponent(1);

        int i = 0;
        for(auto it1 = sd1.begin(), it_end1 = sd1.end(); it1 != it_end1; ++it1) {
            for(auto it2 = sd2.begin() + i, it_end2 = sd2.end(); it2 != it_end2; ++it2) {
                int e1 = (*it1).GetComponentValue(0);
                int e2 = (*it2).GetComponentValue(0);
                if(relation.GetValueAt(domain::DomainElement::Of({e1, e2})) !=
                        relation.GetValueAt(domain::DomainElement::Of({e2, e1}))) {
                    return false;
                }
            }
            ++i;
        }
        return true;
    }
}

