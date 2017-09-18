//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

#ifndef DTagName_h
#define DTagName_h

#include <map>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>  
#include "FSFilter/Utility.h"
//
using namespace std;
using namespace Utility;
//
enum DecayMode
{
	kD0toKPi,
	kD0toKPiPi0,
	kD0toKPiPi0Pi0,
	kD0toKPiPiPi,

	kD0toKPiPiPiPi0,
	kD0toKPiEta,

	kD0toKsKPi = 50,
	kD0toKsKPiPi0,

	kD0toKsPiPi = 100,
	kD0toKsPiPiPi0,
	kD0toKsPi0,

	kD0toPiPiPi0,
	kD0toPiPi,
	kD0toKK,
	kD0toKKPi0,
	kD0toPi0Pi0,
	kD0toKsKs,
	kD0toKsKsPi0,
	kD0toKsPi0Pi0,
	kD0toKsKK,
	kD0toKsEta,
	kD0toPi0Pi0Pi0,

	kD0toKsKsKs,
	kD0toPiPiPiPi,
	kD0toPiPiPi0Pi0,
	kD0toKKPiPi,
	kD0toKKPi0Pi0,
	kD0toKsKsPiPi,
	kD0toPiPiPiPiPi0,
	kD0toKsPiPiPiPi,
	kD0toKKPiPiPi0,
	kD0toKsPi0Eta,

	kD0toKsEPPiPiEta,
	kD0toKsEPRhoGam,

	kDptoKPiPi =200,
	kDptoKPiPiPi0,
	kDptoKsPi,
	kDptoKsPiPi0,
	kDptoKsPiPiPi,
	kDptoKKPi,

	kDptoPiPi0,
	kDptoKPi0,
	kDptoKsK,
	kDptoPiPiPi,
	kDptoPiPi0Pi0,
	kDptoKsKsPi,
	kDptoKsKPi0,
	kDptoKsKsK,
	kDptoPiPiPiPi0,
	kDptoKsPiPi0Pi0,
	kDptoKsKplusPiPi,
	kDptoKsKminusPiPi,
	kDptoKKPiPi0,
	kDptoPiPiPiPiPi,
	kDptoKPiPiPiPi,
	kDptoPiEta,
	kDptoKsPiEta,

	kDstoKsK = 400,
	kDstoKKPi,
	kDstoKsKPi0,
	kDstoKsKsPi,
	kDstoKKPiPi0,
	kDstoKsKplusPiPi,
	kDstoKsKminusPiPi,
	kDstoKKPiPiPi,

	kDstoPiPi0 = 420,
	kDstoPiPiPi,
	kDstoPiPiPiPi0,
	kDstoPiPiPiPiPi,
	kDstoPiPiPiPiPiPi0,

	kDstoPiEta = 440,
	kDstoPiPi0Eta,
	kDstoPiPiPiEta,

	kDstoPiEPPiPiEta = 460,
	kDstoPiPi0EPPiPiEta,

	kDstoPiEPRhoGam = 480,
	kDstoPiPi0EPRhoGam,

	kDstoKsPi = 500,
	kDstoKsPiPi0,
	kDstoKPiPi,
	kDstoKPiPiPi0,
	kDstoKKK,

	kUnknown = 10000
};
const int MaxMode=83;
//
class DTagName {
	public :
		DTagName();
		~DTagName();
		void init();
		//
		char*         GetPName      (const int,            string mode ="number" );
		char*         GetMName      (const int,            string mode ="number" );
		double        GetBr         (const int,            string mode ="number" );
		double        GetdBr        (const int,            string mode ="number" );
		int           GetStatus     (const int,            string mode ="number" );
		int           GetStatus     (const int, const int, string mode ="number" );
		void          SetStatus     (const int, const int, string mode ="number" );
		void          SetStatus     (const int, const int, const int, string mode ="number" );
		DecayMode     find_Mode     (const int );
		int           find_Numb     (const int );
		double        GetSumOfBr    (string    );
		int           GetNumOfDaughters(const int decaymode, string p);
		int           GetNKinDTag   (const int decaymode);
		void          SetAll        ( );
		void          SetOnlyGolden ( );
		void          SetGoldenIJ   ( );
		void          SetAllCharged ( );
		void          SetAllNeutral ( );
		void          SetOnlyOnePi0 ( );
		inline int    GetNmode      ( ){ return (int)Vdmode.size();}
	private:
		vector<int>          Vdmode  ;
		map<int, double    > Br      ;
		map<int, double    > dBr     ;
		map<int, char*     > PName   ;
		map<int, char*     > MName   ;
		map<int, int       > Status  ;
		map<int, DecayMode > NoMode  ;
		map<DecayMode, int > NKinDTag;
		int  StatIJ[MaxMode][MaxMode];
};
#endif
