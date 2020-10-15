namespace function {

    class GammaFunction {
        public:
            GammaFunction(int alpha, int beta) : alpha_(alpha), beta_(beta) {}
            double value_at(int x) const;

        private:
            int alpha_, beta_;
    };
    class LFunction {
        public:
            LFunction(int alpha, int beta) : alpha_(alpha), beta_(beta) {}
            double value_at(int x) const;

        private:
            int alpha_, beta_;
    };
    class LambdaFunction {
        public:
            LambdaFunction(int alpha, int beta, int gamma) :
                alpha_(alpha), beta_(beta), gamma_(gamma) {}
            double value_at(int x) const;

        private:
            int alpha_, beta_, gamma_;
    };

    double GammaFunction::value_at(int x) const {
        if(x < alpha_) { return 0.0; }
        if(x >= beta_) { return 1.0; }

        return ((double) beta_ - x) / ((double) beta_ - alpha_);

    }

    double LFunction::value_at(int x) const {
        if(x < alpha_) { return 1.0; }
        if(x >= beta_) { return 0.0; }

        return ((double) x - alpha_) / ((double) beta_ - alpha_);
    }

    double LambdaFunction::value_at(int x) const {
        if(x < alpha_) { return 0.0; }
        if(alpha_ <= x && x < beta_) {
            double ret_val = ((double) x - (double)alpha_) / ((double) beta_ - (double)alpha_);
            return ret_val;
        }
        if(beta_ <= x && x < gamma_) {
            double ret_val = ((double) gamma_ - (double)x) / ((double) gamma_ - (double)beta_);
            return ret_val;
        }
        return 0.0;
    }
}
