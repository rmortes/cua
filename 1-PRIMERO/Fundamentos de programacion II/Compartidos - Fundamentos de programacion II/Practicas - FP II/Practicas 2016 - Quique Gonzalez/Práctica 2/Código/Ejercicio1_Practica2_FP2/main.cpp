#include <iostream>
#include <matriz.h>
#include <matrizg.h>
#include <matrizc.h>
#include <matrizs.h>
#include <vectorh.h>
#include <vectorv.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int main (void){
    srand(time(NULL));
    MatrizC M1(5);
    Matriz M2 (4,4);
    MatrizC M3;
    cout<<M1<<endl;
    cout<<M2<<endl;
    M3=M1+M2;
    cout<<M3;
    return 0;
}
