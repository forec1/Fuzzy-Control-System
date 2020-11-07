#include <vector>
#include "rule.hpp"

class SteerRules {

    public:
        SteerRules(operand::OperandOp t_norm, operand::OperandOp s_norm,
                operand::OperandOp impl_op) :
            m_t_norm(t_norm), m_s_norm(s_norm), m_impl_op(impl_op) { make_rules(); }

        std::vector<Rule> get_rules() {
            return rules;
        }

    private:
        operand::OperandOp m_t_norm;
        operand::OperandOp m_s_norm;
        operand::OperandOp m_impl_op;
        std::vector<Rule> rules;

        void make_rules() {
            Rule turn_right(m_t_norm, m_s_norm, m_impl_op);
            turn_right.add_and(operand::Operands::lk_close).imply(consequent::turn_right);
            rules.push_back(turn_right);

            Rule turn_left(m_t_norm, m_s_norm, m_impl_op);
            turn_left.add_and(operand::Operands::dk_close).imply(consequent::turn_left);
            rules.push_back(turn_left);
        }
};
