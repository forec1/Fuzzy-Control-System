#include "operand.hpp"

template<typename Operand1, typename Operand2, typename Operator>
class FuzzyRelation {
    private:
        Operand1 o1;
        Operand2 o2;
        Operator o;

    public:
        double value_at(int L, int D, int LK, int DK, int V, int S) {
            double val1 = o1.value_at(L, D, LK, DK, V, S);
            double val2 = o2.value_at(L, D, LK, DK, V, S);
            return o.value_at(val1, val2);
        }
};
