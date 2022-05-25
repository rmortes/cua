#include "matriz.h"




int main (void){
    srand(time(NULL));
   //matriz a (5,5);
  // matriz b (5,5);
  // matriz c;
  // c=a-b;

   matriz a (5,5);
   matrizc b (5);
   matrizc c;
   c=a-b;




   cout<<a<<endl;
   cout<<b<<endl;
   cout<<c;
    getch();
    return(0);
}
