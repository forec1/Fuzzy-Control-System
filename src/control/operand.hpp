#ifndef CONTROL_OPERAND_HPP
#define CONTROL_OPERAND_HPP

#include "../fuzzy/fuzzy_set.hpp"

namespace operand {

    using ParamPickerFunc = std::function<int(int, int, int, int, int, int)>;
    using OperandOp = std::function<double(double, double)>;

    template<class Domain>
    class Operand {
        private:
            fuzzy_set::CalculatedFuzzySet<Domain> m_fuzzy_set;
            ParamPickerFunc m_get_param;
            OperandOp m_op;

        public:
            Operand(fuzzy_set::CalculatedFuzzySet<Domain> fuzzy_set, ParamPickerFunc get_param) :
                m_fuzzy_set(fuzzy_set), m_get_param(get_param){}

            Operand(Domain domain,function::IntUnaryFunction function, ParamPickerFunc get_param) :
            m_fuzzy_set(domain, function), m_get_param(get_param)  {}

            [[nodiscard]] Domain GetDomain() const { return m_fuzzy_set.GetDomain(); }

            [[nodiscard]] double GetValueAt(int L, int D, int LK, int DK, int V, int S) {
                int param = m_get_param(L, D, LK, DK, V, S);
                domain::DomainElement e({param});
                return m_fuzzy_set.GetValueAt(e);
            }

            void set_operation(OperandOp&& op) {
                m_op = op;
            }

            void set_operation(const OperandOp& op) {
                m_op = op;
            }

            OperandOp get_op() {
                return m_op;
            }

    };

    using OperandS = Operand<domain::SimpleDomain>;

    class OperandDomain {
        public:
            static const domain::SimpleDomain distance;
            static const domain::SimpleDomain angle;
    };

    struct Operands {
        static const OperandS lk_close;
        static const OperandS dk_close;
        static const OperandS lk_away;
        static const OperandS dk_away;
        static const OperandS l_away;
        static const OperandS d_away;
        static const OperandS slow_speed;
        static const OperandS fast_speed;
    };
}
#endif
