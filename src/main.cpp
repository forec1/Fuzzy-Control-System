#include <string>
#include <iostream>
#include <sstream>

#include "control/fuzzy_control_system.hpp"
#include "control/acc_rule_database.hpp"
#include "control/steer_rule_database.hpp"
#include "control/defuzzifier.hpp"

int main(void) {

    AccRules acc_rules(operation::ZadehAndFunction::value_at,
                    operation::ZadehOrFunction::value_at,
                    operation::ZadehAndFunction::value_at);
    defuzzifier::CenterOfArea def;

    FuzzyControlSystem<AccRules, defuzzifier::CenterOfArea> acc_cntrl_sys(acc_rules, def);

    SteerRules steer_rules(operation::ZadehAndFunction::value_at,
                    operation::ZadehOrFunction::value_at,
                    operation::ZadehAndFunction::value_at);

    FuzzyControlSystem<SteerRules, defuzzifier::CenterOfArea> steer_cntrl_sys(steer_rules, def);

    std::string line;
    int L, D, LK, DK, V, S;
    while(getline(std::cin, line)) {
        if('K' == line[0]) return 0;
        std::istringstream is(line);
        is >> L >> D >> LK >> DK >> V >> S;
        double K = steer_cntrl_sys.deduce(L, D, LK, DK, V, S);
        double A = acc_cntrl_sys.deduce(L, D, LK, DK, V, S);
        std::cout << (int) A << ' ' << (int) K << std::endl;
    }

}
