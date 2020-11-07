#ifndef _FUZZY_RELATION_HPP
#define _FUZZY_RELATION_HPP

#include "fuzzy_set.hpp"
#include <cmath>
#include <limits>

namespace fuzzy_set {

    class Relations {
        public:
            Relations() = default;

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

            template<class FuzzySet>
            static FuzzySet composition_of_binary_relations(const FuzzySet& r1, const FuzzySet& r2);

            template<class FuzzySet>
            static bool is_fuzzy_equivalence(const FuzzySet& relation);
    };

    template<class FuzzySet>
    bool Relations::is_fuzzy_equivalence(const FuzzySet& relation) {
        return is_symmetric(relation) && is_reflexive(relation) && is_max_min_transitive(relation);
    }

    template<class FuzzySet>
    FuzzySet Relations::composition_of_binary_relations(const FuzzySet& r1, const FuzzySet& r2) {
        domain::SimpleDomain X = r1.GetDomain().GetComponent(0);
        domain::SimpleDomain Y = r1.GetDomain().GetComponent(1);
        domain::SimpleDomain Z = r2.GetDomain().GetComponent(1);

        if(Y != r2.GetDomain().GetComponent(0)) {
            throw std::runtime_error("Domains must be the same!");
        }

        MutableFuzzySet<domain::CompositeDomain> r_compostion(domain::DomainFactory::Combine(X, Z));
        for(auto itX = X.begin(), itX_end = X.end(); itX != itX_end; ++itX) {
            for(auto itZ = Z.begin(), itZ_end = Z.end(); itZ != itZ_end; ++itZ) {
                double max = -1.0;
                for(auto itY = Y.begin(), itY_end = Y.end(); itY != itY_end; ++itY) {
                    double v = std::min(
                            r1.GetValueAt(domain::DomainElement({
                                    (*itX).GetComponentValue(0),
                                    (*itY).GetComponentValue(0)
                                    })
                                ),
                            r2.GetValueAt(domain::DomainElement({
                                    (*itY).GetComponentValue(0),
                                    (*itZ).GetComponentValue(0)
                                    })
                                )
                            );
                    if(v > max) {
                        max = v;
                    }
                }
                r_compostion.set(
                        domain::DomainElement({
                            (*itX).GetComponentValue(0),
                            (*itZ).GetComponentValue(0)
                            }),
                        max);
            }
        }
        return r_compostion;
    }

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
                if(relation.GetValueAt(domain::DomainElement({e1, e2})) < std::min(
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
            if(fabs(relation.GetValueAt(domain::DomainElement({e, e})) - 1.0) > std::numeric_limits<double>::epsilon()) {
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
                if(relation.GetValueAt(domain::DomainElement({e1, e2})) !=
                        relation.GetValueAt(domain::DomainElement({e2, e1}))) {
                    return false;
                }
            }
            ++i;
        }
        return true;
    }
}
#endif // _FUZZY_RELATION_HPP
