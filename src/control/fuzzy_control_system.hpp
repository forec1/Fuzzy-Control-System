#ifndef CONTROL_FUZZY_CONTROL_SYSTEM_HPP
#define CONTROL_FUZZY_CONTROL_SYSTEM_HPP

#include "rule.hpp"
#include "../operation/operation.hpp"

template<typename RuleDatabase, typename Defuzzifier>
class FuzzyControlSystem {
    private:
        RuleDatabase m_rule_databse;
        Defuzzifier m_defuzzifier;

    public:
        FuzzyControlSystem(RuleDatabase rule_database, Defuzzifier def) :
            m_rule_databse(rule_database), m_defuzzifier(def) {}

        double deduce(int L, int D, int LK, int DK, int V, int S ) {
            auto rules = m_rule_databse.get_rules();
            fuzzy_set::MutableFuzzySet<domain::SimpleDomain> res = rules[0].resolve(L, D, LK, DK, V, S);
            for(int i = 1, n = rules.size(); i < n; ++i) {
                fuzzy_set::MutableFuzzySet<domain::SimpleDomain> fset = rules[i].resolve(L, D, LK, DK, V, S);
                res = operation::Operations::binary_operation(fset, res, operation::Operations::zadeh_or());
            }
            return m_defuzzifier.defuzzify(res);
        }

};

#endif // CONTROL_FUZZY_CONTROL_SYSTEM_HPP
