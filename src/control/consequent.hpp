#ifndef CONTROL_CONSEQUENT_HPP
#define CONTROL_CONSEQUENT_HPP

#include "../fuzzy/fuzzy_set.hpp"
#include "../function/unary_function.hpp"

namespace consequent {
    using FS = fuzzy_set::CalculatedFuzzySet<domain::SimpleDomain>;

    domain::SimpleDomain acc_domain = domain::SimpleDomain(-50, 50);
    domain::SimpleDomain angle_domain = domain::SimpleDomain(-90, 91);

    const FS speed_up = FS(
            acc_domain, function::IntUnaryFunction(function::LambdaFunction(60, 65, 70)));

    const FS slow_down = FS(
            acc_domain, function::IntUnaryFunction(function::LFunction(5, 25)));

    const FS turn_left = FS(
            angle_domain, function::IntUnaryFunction(function::GammaFunction(150, 180)));

    const FS turn_right = FS(
            angle_domain, function::IntUnaryFunction(function::LFunction(0, 30)));
}
#endif  //  CONTROL_CONSEQUENT_HPP

