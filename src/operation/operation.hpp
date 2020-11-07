#include "../fuzzy/fuzzy_set.hpp"

using namespace fuzzy_set;

namespace operation {

    class ZadehNotFunction {
        public:
            static double value_at(double x) { return 1.0 - x; }
    };

    class ZadehOrFunction {
        public:
            static double value_at(double x1, double x2) { return std::max(x1, x2); }
    };

    class ZadehAndFunction {
        public:
            static double value_at(double x1, double x2) { return std::min(x1, x2); }
    };

    class HamacherTNormFunction {
        public:
            explicit HamacherTNormFunction(double t) : t_(t) {};
            double value_at(double x1, double x2) {
                return (x1 * x2) / (t_ + (1 - t_)*(x1 + x1 - x1*x2));
            }
        private:
            double t_;
    };

    class HamacherSNormFunction {
        public:
            HamacherSNormFunction(double t) : t_(t) {};
            double value_at(double x1, double x2) {
                return (x1 + x2 - (2 - t_)*x1*x2) / (1 - (1 - t_)*x1*x2);
            }
        private:
            double t_;
    };

    class Operations {
        public:
            Operations() {}

            template<class FuzzySet, class UnaryFunction>
            static FuzzySet binary_operation(FuzzySet set1, FuzzySet set2, UnaryFunction function);

            template<class FuzzySet, class BinaryFunction>
            static FuzzySet unary_operation(FuzzySet set, BinaryFunction function);

            static ZadehNotFunction zadeh_not();
            static ZadehOrFunction zadeh_or();
            static ZadehAndFunction zadeh_and();

            static HamacherTNormFunction hamacher_t_norm(double t);
            static HamacherSNormFunction hamacher_s_norm(double t);
    };


    ZadehNotFunction Operations::zadeh_not() {
        return ZadehNotFunction();
    }

    ZadehOrFunction Operations::zadeh_or() {
        return ZadehOrFunction();
    }

    ZadehAndFunction Operations::zadeh_and() {
        return ZadehAndFunction();
    }
    HamacherTNormFunction hamacher_t_norm(double t) {
        return HamacherTNormFunction(t);
    }
    HamacherSNormFunction hamacher_s_norm(double t) {
        return HamacherSNormFunction(t);
    }

    template<class FuzzySet, class UnaryFunction> FuzzySet Operations::
        unary_operation(FuzzySet set, UnaryFunction function) {
            auto domain = set.GetDomain();
            FuzzySet new_set = set;
            for(auto it = domain.begin(), it_end = domain.end(); it != it_end; ++it) {
                double val = function.value_at(set.GetValueAt(*it));
                new_set.set(*it, val);
        }
        return new_set;
    }

    template<class FuzzySet, class UnaryFunction> FuzzySet Operations::
        binary_operation(FuzzySet set1, FuzzySet set2, UnaryFunction function) {
            auto domain1 = set1.GetDomain();
            auto domain2 = set2.GetDomain();
            if(domain1 != domain2) {
                throw std::runtime_error("Domains are different!");
            }

            FuzzySet new_set = set1;
            for(auto it = domain1.begin(), it_end = domain1.end(); it != it_end; ++it) {
                double val1 = set1.GetValueAt(*it);
                double val2 = set2.GetValueAt(*it);
                double new_val = function.value_at(val1, val2);
                new_set.set(*it, new_val);
            }
            return new_set;
        }
}

