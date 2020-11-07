#ifndef _FUNCTION_UNARY_FUNCTION_HPP
#define _FUNCTION_UNARY_FUNCTION_HPP

#include <functional>

namespace function {

    using IntUnaryFunction = std::function<double(int)>;

    class GammaFunction {
        public:
            GammaFunction(int alpha, int beta) : alpha_(alpha), beta_(beta) {}
            [[nodiscard]] double value_at(int x) const {
                if(x < alpha_) { return 0.0; }
                if(x >= beta_) { return 1.0; }

                return (static_cast<double>(x) - static_cast<double>(alpha_)) /
                    (static_cast<double>(beta_) - static_cast<double>(alpha_));
            }
            double operator()(int x) const noexcept{
                return value_at(x);
            }

        private:
            int alpha_, beta_;
    };

    class LFunction {
        public:
            LFunction(int alpha, int beta) : alpha_(alpha), beta_(beta) {}
            [[nodiscard]] double value_at(int x) const {
                if(x < alpha_) { return 1.0; }
                if(x >= beta_) { return 0.0; }

                return (static_cast<double>(x) - static_cast<double>(alpha_)) /
                    (static_cast<double>(beta_) - static_cast<double>(alpha_));
            }

            double operator()(int x) const noexcept {
                return value_at(x);
            }

        private:
            const int alpha_, beta_;
    };

    class LambdaFunction {
        public:
            LambdaFunction(int alpha, int beta, int gamma) :
                alpha_(alpha), beta_(beta), gamma_(gamma) {}

            [[nodiscard]] double value_at(int x) const {
                if(x < alpha_) { return 0.0; }
                if(alpha_ <= x && x < beta_) {
                    double ret_val = (static_cast<double>(x) - static_cast<double>(alpha_)) /
                        (static_cast<double>(beta_) - static_cast<double>(alpha_));
                    return ret_val;
                }
                if(beta_ <= x && x < gamma_) {
                    double ret_val = (static_cast<double>(gamma_) - static_cast<double>(x)) /
                        (static_cast<double>(gamma_) - static_cast<double>(beta_));
                    return ret_val;
                }
                return 0.0;
            }
            double operator()(int x) const noexcept {
                return value_at(x);
            }

        private:
            const int alpha_, beta_, gamma_;
    };


} // namespace function
#endif // _FUNCTION_UNARY_FUNCTION_HPP
