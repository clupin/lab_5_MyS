#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <chrono>       // std::chrono
#include <random>       // std::default_random_engine
#include <vector>

#define M_PI 3.14159265358979323846
using namespace std;

class punto{
    private:
        double x, y, z, w; //z se considera para radio
    public:
        void Leer(double &x2, double &y2, double &z2, double &w2){
            x2 = x;
            y2 = y;
            z2 = z;
            w2 = w;
        }
        void Guardar(double x2, double y2, double z2, double w2){
            x = x2;
            y = y2;
            z = z2;
            w = w2;
        }
        int VerificarDentro(int tipo, int &resp){
            /*
            tipo:   1 - circunferencia
                    2 - integral_1
                    3 - integral_2
                    4 - integral_3

            resp:   1 - si esta dentro
                    0 - no esta dentro
            */
            double valor = 0;
            resp = 0;
            switch(tipo){
                case 1:
                    valor = x*x+y*y;
                    if(valor <= (z*z)){
                        resp = 1;
                    }
                    break;
                case 2:
                    valor = (3*x*x+2*x-1)/(4*x+7);
                    if(y <= valor){
                        resp = 1;
                    }
                    break;
                case 3:
                    valor = (4*x*x*x-((5*x*x-4*x)/(2*x-1))+20*x*y);
                    if(z <= valor){
                        resp = 1;
                    }
                    break;
                case 4:
                    valor = (5*x*x-4*x+2*M_PI);
                    if(w <= valor){
                        resp = 1;
                    }
                    break;
            }
        }
};

class numero{
    private:
        double x;
        int y; //y es para el intervalo que pertenece
    public:
        void Leer(double &x2, int &y2){
            x2 = x;
            y2 = y;
        }
        void Guardar(double x2){
            x = x2;
        }
        int VerificarIntervalo(vector<double> lim_sup, int &resp){
            for(int i=0; i<lim_sup.size(); i++){
                if(x<lim_sup.at(i)){
                    y=i;
                    resp=i;
                    i=100;
                }
            }
        }
};

void printLista(vector<punto> lista_puntos){
    double x, y, z, w;
    for(int i=0; i<lista_puntos.size(); i++){
        lista_puntos.at(i).Leer(x, y, z, w);
        cout<<"Punto("<<i<<") :"<<endl;
        cout<<"\tx: "<<x<<endl;
        cout<<"\ty: "<<y<<endl;
        cout<<"\tz: "<<z<<endl;
        cout<<"\tw: "<<w<<endl;
    }
}

double mean_lista(vector<numero> lista_numeros){
    double acum=0;
    int cantidad = lista_numeros.size();
    for(int i=0; i<cantidad; i++){
        double x;
        int y;
        lista_numeros.at(i).Leer(x,y);
        acum += y;
    }
    double mean = acum/cantidad;
    return mean;
}

double integral_1(int cantidad_puntos, double inte[]){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed); //Generador de número aleatorio
    uniform_real_distribution<double> coordenadas_x(inte[0], inte[1]); //generador de valores para coordenadas x de un punto

    double valor_y1 = (3*inte[0]*inte[0]+2*inte[0]-1)/(4*inte[0]+7);
    double valor_y2 = (3*inte[1]*inte[1]+2*inte[1]-1)/(4*inte[1]+7);
    uniform_real_distribution<double> coordenadas_y(valor_y1, valor_y2); //generador de valores para coordenadas y de un punto

    vector<punto> lista_puntos;
    for(int i=0; i<cantidad_puntos; i++){
        //crear puntos
        punto p;
        double x = coordenadas_x(generator);
        double y = coordenadas_y(generator);
        p.Guardar(x, y, 0, 0);
        lista_puntos.push_back(p);
    }

    double area = (inte[1]-inte[0])*(valor_y2-valor_y1);
    int resp, contador;
    contador=0;
    for(int i=0; i<lista_puntos.size(); i++){
        lista_puntos.at(i).VerificarDentro(2, resp);
        if(resp==1){
            contador++;
        }
    }
    double valor_integral_1 = (area * contador)/(lista_puntos.size())*1.0;
    return valor_integral_1;
}

double integral_2(int cantidad_puntos, double inte_1[], double inte_2[]){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed); //Generador de número aleatorio
    uniform_real_distribution<double> coordenadas_x(inte_1[0], inte_1[1]); //generador de valores para coordenadas x de un punto
    uniform_real_distribution<double> coordenadas_y(inte_2[0], inte_2[1]); //generador de valores para coordenadas y de un punto

    double valor_z1 = (4*inte_1[0]*inte_1[0]*inte_1[0]-((5*inte_1[0]*inte_1[0]-4*inte_1[0])/(2*inte_1[0]-1))+20*inte_1[0]*inte_2[0]);
    double valor_z2 = (4*inte_1[1]*inte_1[1]*inte_1[1]-((5*inte_1[1]*inte_1[1]-4*inte_1[1])/(2*inte_1[1]-1))+20*inte_1[1]*inte_2[1]);
    uniform_real_distribution<double> coordenadas_z(valor_z1, valor_z2); //generador de valores para coordenadas z de un punto

    vector<punto> lista_puntos;
    for(int i=0; i<cantidad_puntos; i++){
        //crear puntos
        punto p;
        double x = coordenadas_x(generator);
        double y = coordenadas_y(generator);
        double z = coordenadas_z(generator);
        p.Guardar(x, y, z, 0);
        lista_puntos.push_back(p);
    }

    double area = (inte_1[1]-inte_1[0])*(inte_2[1]-inte_2[0])*(valor_z2-valor_z1);
    int resp, contador;
    contador=0;
    for(int i=0; i<lista_puntos.size(); i++){
        lista_puntos.at(i).VerificarDentro(3, resp);
        if(resp==1){
            contador++;
        }
    }
    double valor_integral_2 = (area * contador)/(lista_puntos.size())*1.0;
    return valor_integral_2;
}

double integral_3(int cantidad_puntos, double inte_1[], double inte_2[], double inte_3[]){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed); //Generador de número aleatorio
    uniform_real_distribution<double> coordenadas_x(inte_1[0], inte_1[1]); //generador de valores para coordenadas x de un punto
    uniform_real_distribution<double> coordenadas_y(inte_2[0], inte_2[1]); //generador de valores para coordenadas y de un punto
    uniform_real_distribution<double> coordenadas_z(inte_3[0], inte_3[1]); //generador de valores para coordenadas y de un punto

    double valor_w1 = (5*inte_1[0]*inte_1[0]-4*inte_1[0]+2*M_PI);
    double valor_w2 = (5*inte_1[1]*inte_1[1]-4*inte_1[1]+2*M_PI);
    uniform_real_distribution<double> coordenadas_w(valor_w1, valor_w2); //generador de valores para coordenadas z de un punto

    vector<punto> lista_puntos;
    for(int i=0; i<cantidad_puntos; i++){
        //crear puntos
        punto p;
        double x = coordenadas_x(generator);
        double y = coordenadas_y(generator);
        double z = coordenadas_z(generator);
        double w = coordenadas_w(generator);
        p.Guardar(x, y, z, w);
        lista_puntos.push_back(p);
    }

    double area = (inte_1[1]-inte_1[0])*(inte_2[1]-inte_2[0])*(inte_3[1]-inte_3[0])*(valor_w2-valor_w1);
    int resp, contador;
    contador=0;
    for(int i=0; i<lista_puntos.size(); i++){
        lista_puntos.at(i).VerificarDentro(4, resp);
        if(resp==1){
            contador++;
        }
    }
    double valor_integral_3 = (area * contador)/(lista_puntos.size())*1.0;
    return valor_integral_3;
}

double pi(int cantidad_puntos, double r){
    /*
    Bajo la premisa que:
        pi * r^2        numero de puntos en circulo
    --------------- = ------------------------------
     area cuadrado         numero total de puntos
     Entonces:
           area cuadrado * numero de puntos en circulo
     pi = ---------------------------------------------
                   r^2 * numero total de puntos
    */
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed); //Generador de número aleatorio
    uniform_real_distribution<double> coordenadas(-r, r); //generador de valores para coordenadas x e y de un punto

    vector<punto> lista_puntos;
    for(int i=0; i<cantidad_puntos; i++){
        //crear puntos
        punto p;
        double x = coordenadas(generator);
        double y = coordenadas(generator);
        p.Guardar(x, y, r, 0);
        lista_puntos.push_back(p);
    }
    double area = 4*r*r;

    double a,b,c;
    int resp, contador;
    contador=0;
    for(int i=0; i<lista_puntos.size(); i++){
        lista_puntos.at(i).VerificarDentro(1, resp);
        if(resp==1){
            contador++;
        }
    }
    double valor_pi = (area * contador)/(r*r * lista_puntos.size())*1.0;
    return valor_pi;
}

double problema(int cantidad_puntos, vector<int> licencias, vector<double> lim_sup){

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed); //Generador de número aleatorio
    uniform_real_distribution<double> aleatorio(0, 1); //generador de valores para valores aleatorios entre 0 y 1

    vector<numero> lista_numeros;
    for(int i=0; i<cantidad_puntos; i++){
        numero n;
        //crear puntos
        double x = aleatorio(generator);
        n.Guardar(x);
        for(int j=0; j<lim_sup.size(); j++){
            int resp=0;
            n.VerificarIntervalo(lim_sup, resp);
            lista_numeros.push_back(n);
        }
    }
    double promedio = mean_lista(lista_numeros);
    return promedio;
}

int main(){

    //2.1.1 Estimaciones
    int puntos=5000;
    int radio_pi=1.0;
    double valor_pi = pi(puntos,radio_pi);
    cout<<"Valor de pi, estimado con "<<puntos<<" puntos, es de: "<<valor_pi<<endl;

    double inte_1[2] = {0.0, 10.0};
    double valor_int_1 = integral_1(puntos,inte_1);
    cout<<"Valor de la integral 1, estimado con "<<puntos<<" puntos, es de: "<<valor_int_1<<endl;

    inte_1[0] = 2.0; inte_1[1] = 25.0;
    double inte_2[2] = {0.0, 17.0};
    double valor_int_2 = integral_2(puntos, inte_1, inte_2);
    cout<<"Valor de la integral 2, estimado con "<<puntos<<" puntos, es de: "<<valor_int_2<<endl;

    inte_1[0] = 0.0; inte_1[1] = 5.0;
    inte_2[0] = 0.0; inte_2[1] = 10.0;
    double inte_3[2] = {0.0, 2.0};
    double valor_int_3 = integral_3(puntos, inte_1, inte_2, inte_3);
    cout<<"Valor de la integral 3, estimado con "<<puntos<<" puntos, es de: "<<valor_int_3<<endl;

    int cantidad_puntos = 1000;
    vector<int> licencias = {100, 150, 200, 250, 300};
    vector<double> lim_sup = {0.3, 0.5, 0.8, 0.95, 1};
    double prob = problema(cantidad_puntos, licencias, lim_sup);
    cout<<"Problema: "<<prob<<endl;


    return 0;
}

