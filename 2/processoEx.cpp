#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
  // printf("I am process: %d\n", getpid());
  cout << "I am process: " << getpid() << endl;
  while(1);
  exit(0);
}