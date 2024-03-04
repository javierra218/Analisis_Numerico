/**
 * @file biseccion.h
 * @author Javier Rojas 
 * @brief 
 * @version 0.1
 * @date 2024-03-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef BISECCION_H
#define BISECCION_H

#include <string>
#include <cmath>
#include "expression.h"



using std::string;

namespace raices{
    
    class biseccion{
        public:
        /**
         * @brief Construct a new biseccion object
         * 
         * @param str_func 
         */
            biseccion(string str_func):f(str_func){

            }
            /**
             * @brief 
             * 
             * @param xa 
             * @param xb 
             * @param tol 
             * @param n 
             * @return double 
             */
            double encontrar(double xa, double xb, double tol, int n){
                //paso 1
                int i = 1;
                //paso 2 calcular el punto medio y evaluar el subintervalo
                double xAnt= (xa+xb)/2.0f;
                if (f(xa)*f(xAnt)>0.0f){
                    xa=xAnt;
                }else{
                    xb=xAnt;
                }
                //paso 3
                while(i<=n){
                    //paso 4
                    double xNueva=(xa+xb)/2.0f;
                    double erp= fabs((xNueva-xAnt)/xNueva)*100.0f;
                    //paso 5
                    if(fabs(f(xNueva))<DBL_EPSILON || erp<tol){
                        return xNueva;
                    }
                    //paso 6
                    i++;
                    //paso 7
                    if (f(xa)*f(xNueva)>0.0f){
                        xa=xNueva;
                    }else{
                        xb=xNueva;
                    }

                    xAnt=xNueva;
                }
				return NAN;
				

            }
        private:
            expression f; //evaludor de la funcion
    };
};

#endif
