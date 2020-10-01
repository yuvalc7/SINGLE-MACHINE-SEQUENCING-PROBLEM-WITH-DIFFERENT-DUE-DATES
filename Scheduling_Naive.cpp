//
// Created by yuval on 25/09/2020.
//

#include "Scheduling_Naive.h"
using  namespace std;
#include <algorithm>    // std::next_permutation
#include <iostream>

/*---- Constructors ----*/
Scheduling_Naive:: Scheduling_Naive( int p_j [], int d_j [] , int size)
{
    this->p_j = p_j;
    this->d_j = d_j;
    this->size = size;
    //init_index_permutation();
    index_permutation = new int [size];
    for (int i = 0; i < this->size ; i++){
        index_permutation[i] = i;
    }
}
/*---- Methods ----*/
 void Scheduling_Naive :: Min_Late_times(){
    int current_Late = 0 ;
    int current_Time;
    do {
        current_Time = 0;
        current_Late = 0 ;
        for(int i = 0 ; i < size; i++ ){
            current_Time += p_j[index_permutation[i]];
            current_Late+=( current_Time - d_j[index_permutation[i]]  < 0) ? 0 :  current_Time - d_j[index_permutation[i]] ;
            if(Min_Late < current_Late)break;
        }
        if(current_Late<Min_Late){
            Min_Late=current_Late;
            //optimal_permutation.clear();
            optimal_permutation = new int [size];
            for(int i=0 ; i<size ; i++){//save the better pemutation
                //optimal_permutation.push_back(index_permutation.at(i));
                optimal_permutation[i] = index_permutation[i];
            }
        }
    } while ( std::next_permutation(index_permutation,index_permutation+size));
    cout << "optimal permutation index : " ;
    for(int i = 0 ; i < size ; i++){
        cout << optimal_permutation[i]<< ", ";
    }
    cout << endl;
    cout << "Min Late: " << Min_Late;
 }
