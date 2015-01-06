
#ifndef MODEL_H
#define MODEL_H

namespace Dodger {

    class Model {

        public:
            Model() {};
            ~Model() {};
            virtual double call(double t) = 0;
            virtual std::string json() = 0;
    };

    class LinearModel : public Model {

        public:
            LinearModel(double a, double b) {
                this->a = a;
                this->b = b;
            };
            ~LinearModel() {};
            double call(double t);
            std::string json();

        private:
            double a;
            double b;

    };

    class SinModel : public Model {

        public:
            SinModel(double a, double b, double c, double d){
                this->a = a;
                this->b = b;
                this->c = c;
                this->d = d;
            };
            ~SinModel() {};
            double call(double t);
            std::string json();

        private:
            double a;
            double b;
            double c;
            double d;

    };
}

#endif
