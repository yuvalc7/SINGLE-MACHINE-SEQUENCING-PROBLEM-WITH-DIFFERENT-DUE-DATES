//
// Created by yuval on 25/09/2020.
//


#include <vector>
using  namespace std;
class Scheduling_Naive {
    /*---- Fields ----*/
private:
    int*  p_j;
    int* d_j ;
    int* index_permutation ;//Go over all the permutations on the Task Vector indexes
    int* optimal_permutation;//The optimal order of the tasks from task 0 ..
    int Min_Late = INT_MAX;
    int size;

    /*---- Constructors ----*/
public:
      Scheduling_Naive(int p_j [] , int d_j [] , int size);
    /*---- Methods ----*/
      void Min_Late_times();

};



