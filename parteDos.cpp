/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
#include <chrono>       // std::chrono
#include <iostream>

using namespace std;

double targetdist(double x, int decision){
    double probX = 0;
    if(decision == 1){
        probX = exp(-(x*x)) * (2 + sin(x*5) + sin(x*2));
    }
    else{
        const float PI = 3.1415927;
        probX = exp(-(x*x*x)) * (8 + cos(3*x) + sin(x) + (2*PI));
    }
    return probX;
}

double MHstep(int x0, int sigma, int decision){
    double x1;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generador (seed); //Generador de número aleatorio

    normal_distribution<double> distribution_normal(x0,sigma);
    uniform_real_distribution<double> distribution_uniform(0,1);
    double xp = distribution_normal(generador);
    cout<<xp<<endl;
    double accprob = targetdist(xp, decision) / targetdist(x0, decision);
    double u = ((double) rand() / (RAND_MAX));

    if(u <= accprob){
        x1 = xp;
    }
    else{
        x1 = x0;
    }
    return x1;
}

vector<double> MHsimple(double sigma, int decision){
    vector<double> lista;
    int burnin = 0;
    int lag = 1;
    int nsamp = 1000;
    int x = -1;
    //double *X = new double[nsamp];

    for(int i = 0; i < burnin; i++){
        x = MHstep(x, sigma, decision);
    }
    for(int i = 0; i < nsamp; i++){
        for(int j = 0; j < lag; j++){
            x = MHstep(x, sigma, decision);
        }
        //X[i] = x;
        lista.push_back(x);
    }
    //return X;
    return lista;
}

/*
 *
 */
int main(int argc, char** argv) {
    //double *X = new double[1000];
    vector<double> lista;
    int decision = -1;
    cout<<"Ingrese: \n1 para calcular el caso normal \n2 para calcular la función g(x)"<<endl;
    cin>>decision;
    switch(decision){
        case 1:
        {
            //X = MHsimple(50, decision);
            lista = MHsimple(50, decision);
            cout<<"Los valores encontrados son: "<<endl;
            for(unsigned int i = 0; i < 1000; i++){
                //cout << *(X + i) << " ";
                cout << lista.at(i) << " ";
            }
            break;
        }
        case 2:
        {
            cout<<"Ingrese el valor de sigma: "<<endl;
            double sigma;
            cin>>sigma;
            //X = MHsimple(sigma, decision);
            lista = MHsimple(sigma, decision);
            cout<<"Los valores encontrados son: "<<endl;
            for(unsigned int i = 0; i < 1000; i++){
                //cout << *(X + i) << " ";
                cout << lista.at(i) << " ";
            }
            break;
        }
        default:
        {
            cout<<"No ingresó una opción válida, vuelva a ejecutar el programa."<<endl;
            break;
        }
    }
    return 0;
}

