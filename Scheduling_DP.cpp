//
// Created by yuval on 29/09/2020.
//

#include "Scheduling_DP.h"
#include <string>
using  namespace std;
//#include <algorithm>    // std::next_permutation
#include <iostream>

/*---- Constructors ----*/
Scheduling_DP:: Scheduling_DP( int p_j [], int d_j [] , int size)
{
    this->p_j = p_j;
    this->d_j = d_j;
    this->size = size;
    //this->counter = 0;
    index_permutation = new int [size];
    for (int i = 0; i < this->size ; i++){
        index_permutation[i] = i+1;
    }
}
/*---- Methods ----*/
void Scheduling_DP :: Min_Late_times(){
    // for subset 1
    for (int i = 0; i < size ; i++){
        int current_Time = p_j[i];
        int current_Late =( current_Time - d_j[i]  < 0) ? 0 :  current_Time - d_j[i] ;
        string key = to_string(index_permutation[i]);
        F_j_1 [key] = {key , current_Late};
    }

    //for subset 2 and above
    for (int i = 2 ; i <= size ; i++) {
        int *data = new int[i];//Temporary array to store current combination
        combinationUtil(index_permutation, size, i, 0, data, 0);
        setMin();
    }
    cout << "final result" << endl;
    if(F_j_1.size() > 0){
        cout << "optimal permutation" << " : "<< F_j_1.begin()->second.order << endl;
        cout << "minimum late : " << F_j_1.begin()->second.F << endl;
    }
    else{
        cout << "optimal permutation" << " : " << F_j_2.begin()->second.order << endl;
        cout << "minimum late : " << F_j_2.begin()->second.F << endl;
    }
}

/* arr[]  ---> Input Array
   n      ---> Size of input array
   r      ---> Size of a combination to be store
   index  ---> Current index in data[]
   data[] ---> Temporary array to store current combination
   i      ---> index of current element in arr[]     */
void Scheduling_DP ::combinationUtil(int *arr, int n, int r, int index, int *data, int i ) {
    // Current subset is ready, store it
    if (index == r) {
        string key = "";
        for (int j = 0; j < r; j++)
            key = key + to_string(data[j]);
        if(F_j_2.empty() || !F_j_1.empty() && F_j_2.begin()->first.length() > F_j_1.begin()->first.length()){F_j_2[key] = {"",0};}
        else{F_j_1[key] = {"",0};}
        return;
    }
    // When no more elements are there to put in data[]
    if (i >= n)
        return;
    // current is included, put next at next location
    data[index] = arr[i];
    combinationUtil(arr, n, r, index + 1, data, i + 1  );
    // current is excluded, replace it with next
    // (Note that i+1 is passed, but index is not
    // changed)
    combinationUtil(arr, n, r, index, data, i + 1 );
}

void Scheduling_DP ::setMin() {

    if( F_j_1.begin()->first.length() > F_j_2.begin()->first.length()){
        for(auto it = F_j_1.begin() ; it != F_j_1.end() ; it++ ){
            string key = it->first;
            int length = key.length();
            //init C_J
            int C_J = 0;
            for(int i = 0 ; i < length ; i++){
                int v = key[i] - 48;
                C_J = C_J + p_j[v-1];
            }
            int compare = 0; // final minimum value
            string final_key = ""; // order of combination
            //find the minimal (key , value) and save it in local variable
            for(int i = 0 ; i < length ; i++){
                string current_key = "";
                int dj = 0;
                int max = 0;
                if( i == 0){//first iteration
                    dj = key[key.length()-1] - 48;
                    max = (C_J - d_j[dj-1] < 0 ) ? 0 : C_J - d_j[dj-1];
                    current_key = key.substr(0,key.length()-1);
                    compare = max + F_j_2[current_key].F;
                    final_key =  key;
                }
                else if (i + 1 < length){//in the middle
                    dj = key[i]-48;
                    max = (C_J - d_j[dj-1] < 0) ? 0 : C_J - d_j[dj-1];
                    current_key = key.substr(0,i) + key.substr(i+1,key.length()) ;
                    if(compare > max + F_j_2[current_key].F) {
                        compare = max + F_j_2[current_key].F;
                        final_key = current_key + key[i];
                    }
                }
                else{//last iteration
                    dj = key[0]-48;
                    max = (C_J - d_j[dj-1] < 0) ? 0 : C_J - d_j[dj-1];
                    current_key = key.substr(1,key.length());
                    if(compare > max + F_j_2[current_key].F) {
                        compare = max + F_j_2[current_key].F;
                        final_key = current_key + key[0];
                    }
                }
            }
            //store the minimal (key , value)
            F_j_1[key] = {final_key , compare};
        }
        F_j_2.clear();
    }
    else{
        for(auto it = F_j_2.begin() ; it != F_j_2.end() ; it++ ){
            string key = it->first;
            int length = key.length();

            //init C_J
            int C_J = 0;
            for(int i = 0 ; i < length ; i++){
                int v = key[i] - 48;
                C_J = C_J + p_j[v-1];
            }
            int compare = 0; // final minimum value
            string final_key = ""; // order of combination
            //find the minimal (key , value) and save it in local variable
            for(int i = 0 ; i < length ; i++){
                string current_key = "";
                int dj = 0;
                int max = 0;
                if( i == 0){//first iteration
                    dj = key[key.length()-1] - 48;
                    max = (C_J - d_j[dj-1] < 0 ) ? 0 : C_J - d_j[dj-1];
                    current_key = key.substr(0,key.length()-1);
                    compare = max + F_j_1[current_key].F;
                    final_key =  key;
                }
                else if (i + 1 < length){//in the middle
                    dj = key[i]-48;
                    max = (C_J - d_j[dj-1] < 0) ? 0 : C_J - d_j[dj-1];
                    current_key = key.substr(0,i) + key.substr(i+1,key.length()) ;
                    if(compare > max + F_j_1[current_key].F) {
                        compare = max + F_j_1[current_key].F;
                        final_key = current_key + key[i];
                    }
                }
                else{//last iteration
                    dj = key[0]-48;
                    max = (C_J - d_j[dj-1] < 0) ? 0 : C_J - d_j[dj-1];
                    current_key = key.substr(1,key.length());
                    if(compare > max + F_j_1[current_key].F) {
                        compare = max + F_j_1[current_key].F;
                        final_key = current_key + key[0];
                    }
                }
            }
            //store the minimal (key , value)
            F_j_2[key] = {final_key , compare};
        }
        F_j_1.clear();
    }
}