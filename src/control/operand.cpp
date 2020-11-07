#include "operand.hpp"
namespace operand {
    int get_L(int L, int D, int LK, int DK, int V, int S) {
    return L;
    }

    int get_D(int L, int D, int LK, int DK, int V, int S) {
    return D;
    }

    int get_LK(int L, int D, int LK, int DK, int V, int S) {
    return LK;
    }

    int get_DK(int L, int D, int LK, int DK, int V, int S) {
    return DK;
    }

    int get_V(int L, int D, int LK, int DK, int V, int S) {
    return V;
    }

    int get_S(int L, int D, int LK, int DK, int V, int S) {
    return S;
    }

    const domain::SimpleDomain OperandDomain::distance = domain::SimpleDomain(0, 1301);

    const OperandS Operands::lk_close = OperandS(
    OperandDomain::distance, function::IntUnaryFunction(function::LFunction(40, 50)), get_LK
    );

    const OperandS Operands::dk_close = OperandS(
    OperandDomain::distance, function::IntUnaryFunction(function::LFunction(40, 50)), get_DK
    );

    const OperandS Operands::lk_away = OperandS(
    OperandDomain::distance, function::IntUnaryFunction(function::GammaFunction(60, 70)), get_LK
    );

    const OperandS Operands::dk_away = OperandS(
    OperandDomain::distance, function::IntUnaryFunction(function::GammaFunction(60, 70)), get_DK
    );

    const OperandS Operands::l_away = OperandS(
    OperandDomain::distance, function::IntUnaryFunction(function::GammaFunction(50, 70)), get_L
    );

    const OperandS Operands::d_away = OperandS(
    OperandDomain::distance, function::IntUnaryFunction(function::GammaFunction(50, 70)), get_L
    );

    const OperandS Operands::fast_speed = OperandS(
    OperandDomain::distance, function::IntUnaryFunction(function::GammaFunction(55, 75)), get_V
    );

    const OperandS Operands::slow_speed = OperandS(
    OperandDomain::distance, function::IntUnaryFunction(function::LFunction(20, 40)), get_V
    );
}
