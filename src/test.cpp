#include <cstdio>
#include <vector>
#include "control/rule.hpp"
#include "operation/operation.hpp"

int main(void) {

    Rule rule1(operation::ZadehAndFunction::value_at,
               operation::ZadehOrFunction::value_at,
               operation::ZadehAndFunction::value_at);

    rule1.add_and(operand::Operands::fast_speed).imply(consequent::slow_down);
    auto res = rule1.resolve(25, 25, 25, 25, 70, 25);

    for(auto it = res.GetDomain().begin(); it != res.GetDomain().end(); ++it) {
        printf("element=%s, val=%lf\n", (*it).ToString().c_str(), res.GetValueAt(*it));
    }
    return 0;
}

