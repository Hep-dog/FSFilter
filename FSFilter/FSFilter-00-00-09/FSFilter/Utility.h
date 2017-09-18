#ifndef LEAKAGE_H
#define LEAKAGE_H
#include <string>
using namespace std;
namespace Utility
{
	template <typename T> void FreeDelAll( T & t ) 
	{
		for(int i=0; i<t.size(); i++) delete t[i];
		T tmp; 	t.swap(tmp);
	}

	template <typename T> void FreeAll( T & t ) 
	{
		T tmp; 	t.swap(tmp);
	}

	double Mass(const string name);
}
#endif
