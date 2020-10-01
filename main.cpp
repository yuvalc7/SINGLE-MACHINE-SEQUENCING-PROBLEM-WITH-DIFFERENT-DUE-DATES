
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include "Scheduling_Naive.h"
#include "Scheduling_DP.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <unordered_map>

using  namespace std;


int main () {
    srand(std::time(nullptr));
    ofstream my_file ("Scheduling.txt", std::ofstream ::trunc);
    int size = 0;
    //choose number of task randomly and fill duration and deadlines for each task randomly
    if(my_file.is_open()){
        size = rand() % 10;
        for (int i = 0 ; i < size ; i++){
            my_file << rand() % 100 << " ";
        }
        my_file << " \n" ;
        for (int j = 0; j < size ; ++j) {
            my_file << rand() % 100 << " ";
        }
        my_file.close();
    }
    //read
    string line;
    ifstream myfile ("Scheduling.txt");
    bool deadlines = false;
    int *p_j  = new int[size];
    int *d_j  = new int [size];
    int counter = 0;
    if(myfile.is_open()){
        while (getline(myfile, line , ' ' )){
            if(counter < size && !deadlines){
                p_j[counter] = stoi(line);
            }
           else if(counter > size) {
                deadlines = true;
                counter = 0;
            }
             if(deadlines) {
               d_j[counter] = stoi(line);
            }
            counter++;
        }
        my_file.close();
    }
        for (int k = 0; k <  size; k ++) {
        cout << "time for the particular job: "<< p_j[k] << "   deadline:  " << d_j[k] << endl;
    }
    Scheduling_DP *dp = new Scheduling_DP(p_j,d_j,size);
    dp->Min_Late_times();
   Scheduling_Naive *sn = new Scheduling_Naive(p_j,d_j,size);
    sn->Min_Late_times();

    return 0;
}

