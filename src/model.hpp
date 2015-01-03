
#ifndef MODEL_H
#define MODEL_H

class Model {

    public:
        Model() {};
        ~Model() {};
        double call(double t) {
            return t;
        };

};

class LinearModel : public Model {

    public:
        LinearModel(double m, double b) {
            this->m = m;
            this->b = b;
        };
        ~LinearModel() {};
        double call(double t);

    private:
        double m;
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

    private:
        double a;
        double b;
        double c;
        double d;

};

#endif
