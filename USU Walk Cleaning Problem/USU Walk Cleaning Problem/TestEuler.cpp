#include <iostream>
#include <iomanip>
#include <fstream>
#include "graph.h"
#include <assert.h>
using namespace std;

int main ()
{  	ofstream fout;
	fout.open("tourOut.txt");
	assert(fout);

   Graph g("prog7A.txt",fout);
   g.computeTour(fout);
   fout << std::endl;

   Graph g1("prog7B.txt",fout);
   g1.computeTour(fout);
   fout << std::endl;

   Graph g2("prog7C.txt",cout);
   g2.computeTour(cout);
   std::cout << std::endl;

   char c;
   std::cin >> c;
   return 0;
}