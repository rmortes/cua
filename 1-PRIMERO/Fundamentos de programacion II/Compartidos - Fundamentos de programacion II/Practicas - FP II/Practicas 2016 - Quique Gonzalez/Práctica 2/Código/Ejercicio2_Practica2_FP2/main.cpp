#include <iostream>
#include <matrizt.h>
#include <matrizgt.h>
#include <matrizct.h>
#include <matrizst.h>
#include <vectorht.h>
#include <vectorvt.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
 int main (void){
     srand(time(NULL));
     MatrizT<float> m1(4,4);
     cout<<m1;
     return 0;
 }
