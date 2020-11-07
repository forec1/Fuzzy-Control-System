#include <vector>
#include "rule.hpp"

class AccRules {

    public:
        AccRules(operand::OperandOp t_norm, operand::OperandOp s_norm,
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
            Rule slow_down(m_t_norm, m_s_norm, m_impl_op);
            slow_down.add_and(operand::Operands::fast_speed).imply(consequent::slow_down);
            rules.push_back(slow_down);

            Rule speed_up(m_t_norm, m_s_norm, m_impl_op);
            speed_up.add_and(operand::Operands::slow_speed).imply(consequent::speed_up);
            rules.push_back(speed_up);

            Rule gain_speed(m_t_norm, m_s_norm, m_impl_op);
            gain_speed.add_and(operand::Operands::dk_away)
                      .add_and(operand::Operands::lk_away)
                      .add_and(operand::Operands::l_away)
                      .add_and(operand::Operands::d_away)
                      .imply(consequent::speed_up);
            rules.push_back(gain_speed);

            Rule turn(m_t_norm, m_s_norm, m_impl_op);
            turn.add_and(operand::Operands::lk_close)
                .add_or(operand::Operands::dk_close)
                .add_and(operand::Operands::fast_speed)
                .imply(consequent::slow_down);
        }
};
