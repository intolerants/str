/////\// UFRN-CT-DCA
// Disciplina: Sistemas Operacionais
// Programa: sleep.c


#include <iostream> // para: cout
#include <stdio.h>
#include <unistd.h> // para: sleep()


using std::cout;

//using namespace std;


int main ( )
{

  time_t time1, time2;

  time1 = time( (time_t *) 0);  // apontando o ponteiro para null.
  sleep(10);
  time2 = time( (time_t *) 0);  // apontando o ponteiro para null.
  cout << "O programa dormiu " << time2 - time1 << " segundos" <<'\n';
  return(0);
}

