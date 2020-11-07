#ifndef CONTROL_RULE_HPP
#define CONTROL_RULE_HPP

#include <vector>
#include "operand.hpp"
#include "consequent.hpp"

class Rule{
    private:
        operand::OperandOp m_s_norm;
        operand::OperandOp m_t_norm;
        operand::OperandOp m_implication_op;
        std::vector<operand::OperandS> rules;
        consequent::FS m_implication;

    public:
        Rule(operand::OperandOp t_norm, operand::OperandOp s_norm,
                operand::OperandOp implication_op) :
            m_t_norm(t_norm), m_s_norm(s_norm), m_implication_op(implication_op) {}

        Rule& add_and(operand::OperandS operand) {
            operand.set_operation(m_s_norm);
            this->rules.push_back(operand);
            return *this;
        }

        Rule& add_or(operand::OperandS operand) {
            operand.set_operation(m_t_norm);
            this->rules.push_back(operand);
            return *this;
        }

        void imply(consequent::FS implication) {
            this->m_implication = implication;
        }

        fuzzy_set::MutableFuzzySet<domain::SimpleDomain> resolve(
                int L, int D, int LK, int DK, int V, int S) {

            double affiliation = rules[0].GetValueAt(L, D, LK, DK, V, S);
            operand::OperandOp op = rules[0].get_op();
            for(int i = 1, n = rules.size(); i < n; ++i) {
                double curr_affiliation = rules[i].GetValueAt(L, D, LK, DK, V, S);
                affiliation = op(curr_affiliation, affiliation);
                op = rules[i].get_op();
            }

            fuzzy_set::MutableFuzzySet<domain::SimpleDomain> result(m_implication.GetDomain());
            for(auto it = m_implication.GetDomain().begin();
                    it != m_implication.GetDomain().end(); ++it) {
                double y_aff = m_implication.GetValueAt(*it);
                y_aff = m_implication_op(affiliation, y_aff);
                result.set(*it, y_aff);
            }
            return result;
        }
};
#endif
