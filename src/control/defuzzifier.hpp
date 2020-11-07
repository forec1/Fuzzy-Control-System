#ifndef CONTROL_DEFUZZIFIER_HPP
#define CONTROL_DEFUZZIFIER_HPP

#include "../fuzzy/fuzzy_set.hpp"

namespace defuzzifier {
    class CenterOfArea {
        public:
            double defuzzify(fuzzy_set::MutableFuzzySet<domain::SimpleDomain> set) {
                double res = 0.0, sum = 0.0;
                for(auto e : set.GetDomain()) {
                    double val = set.GetValueAt(e);
                    res += val * e.GetComponentValue(0);
                    sum += val;
                }
                return sum == 0.0 ? 0.0 : res / sum;
            }
    };
}

#endif // CONTROL_DEFUZZIFIER_HPP
