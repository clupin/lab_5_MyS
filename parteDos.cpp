/*
 * File:   main.cpp
 * Author: Bustamante
 *
 * Created on 19 de noviembre de 2016, 20:43
 */

#include <cstdlib>
#include <vector>
#include <random>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <iostream>

using namespace std;

/*
 * Que hace     : Calcula el valor de la distribución con el valor de entrada
 * Que recibe   : El valor de x y un int que funciona para saber si se utiliza la primera o la segunda distribución
 * Que devuelve : Un double con el valor de la distribución en el punto
 */
double targetdist(double x, int decision){
    double probX = 0;
    if(decision == 1){ //Estamos ocupando la primera distribución
        probX = exp(-(x*x)) * (2 + sin(x*5) + sin(x*2));
    }
    else{ //Estamo ocupando la segunda distribución
        const float PI = 3.1415927;
        probX = exp(-(x*x*x)) * (8 + cos(3*x) + sin(x) + (2*PI));
    }
    return probX; //Retornamos el valos
}

/*
 * Que hace     :
 * Que recibe   :
 * Que devuelve : 
 */
double MHstep(int x0, int sigma, int decision){
    double x1;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count(); //se setea el seed con el reloj del procesador
    default_random_engine generador (seed); //Generador de número aleatorio
    normal_distribution<double> distribution_normal(x0,sigma); //distribución normal con mu = x0 y sigma = sigma ingresado por parámetro
    uniform_real_distribution<double> distribution_uniform(0,1); //distribución uniforma real entre 0 y 1
    double xp = distribution_normal(generador); //se genera un valor aleatorio para x candidato
    cout<<xp<<endl; //se muestra por pantalla el número
    double accprob = targetdist(xp, decision) / targetdist(x0, decision); //se calcula la probabilidad del candidato
    double u = ((double) rand() / (RAND_MAX)); //se calcula la probabilidad de que se acepte

    if(u <= accprob){ //si es mayor la probabilidad, se acepta
        x1 = xp;
    }
    else{ //si no, se rechaza y se devuelve el mismo número
        x1 = x0;
    }
    return x1;
}

/*
 * Que hace     : Realiza todo el tráfico de datos entre las distintas funciones, es la función principal para obtener la serie de números
 * Que recibe   : El sigma de la distribución y la decisión para saber si trabajmos con la primera distribución o la segunda
 * Que devuelve : Un vector con los valores encontrados
 */
vector<double> MHsimple(double sigma, int decision){
    vector<double> lista;
    int burnin = 0; //Cantidad de valores que no se van a utilizar
    int lag = 1; //Iteraciones entre entre los muestreos sucesivos
    int nsamp = 1000; //Cantidad de muestras
    int x = -1; //Valor inicial
    for(int i = 0; i < burnin; i++){ //Acá se eliminan todos los valores hasta el valor de burnin
        x = MHstep(x, sigma, decision);
    }
    for(int i = 0; i < nsamp; i++){ //Acá se inicia el muestreo
        for(int j = 0; j < lag; j++){
            x = MHstep(x, sigma, decision); //se obtiene el valor de X
        }
        lista.push_back(x); //se guarda el valor de x
    }
    return lista; //se retorna la lista 
}

/*
 * Main, desde donde se llaman todos las funciones y se controla el flujo del programa
 */
int main(int argc, char** argv) {
    vector<double> lista; //Se inicia el vector
    int decision = -1; //variable para controlar si se utiliza la primera distribución o la segunda
    cout<<"Ingrese: \n1 para calcular el caso normal \n2 para calcular la función g(x)"<<endl;
    cin>>decision; //se captura el valor de la decisión
    switch(decision){
        case 1: //en el caso de sea la primera distribución
        {
            lista = MHsimple(50, decision); //acá la desviación estandar es por defecto 50
            cout<<"Los valores encontrados son: "<<endl;
            for(unsigned int i = 0; i < 1000; i++){ //se muestran los valores encontrados
                cout << lista.at(i) << " ";
            }
            break;
        }
        case 2: //en el caso de que sea la segunda distribución
        {
            cout<<"Ingrese el valor de sigma: "<<endl;
            double sigma;
            cin>>sigma; //se caputa el valor de sigma
            if(sigma){ //se valida el valor ingresado
                lista = MHsimple(sigma, decision);
                cout<<"Los valores encontrados son: "<<endl;
                for(unsigned int i = 0; i < 1000; i++){
                    cout << lista.at(i) << " ";
                }
            }
            else{
                cout<<"Debe ingresar un valor númerico, revise el manual para mayor información."<<endl;
            }
            break;
        }
        default: //si las opciones no corresponden
        {
            cout<<"No ingresó una opción válida, vuelva a ejecutar el programa."<<endl;
            break;
        }
    }
    return 0;
}

