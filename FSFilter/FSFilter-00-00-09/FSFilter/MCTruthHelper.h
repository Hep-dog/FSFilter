#ifndef MCTRUTHHELPER_H
#define MCTRUTHHELPER_H

#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/NTuple.h"

#include "McTruth/McParticle.h"
#include "CLHEP/Vector/LorentzVector.h"
#include <vector>
#include <string>

#include "FSFilter/FSHelper.h"
using namespace std;
using namespace Event;


// ***************************************************************
//
//  CLASS McTruthHelper
//
//    Parse truth information using the McParticleCol object
//      provided by BOSS
//
// ***************************************************************


class MCTruthHelper{

	public:

		// constructor
		MCTruthHelper(SmartDataPtr<Event::McParticleCol> mcParticleCol, int RootID );
		~MCTruthHelper();


		// return a list of McParticle pointers sorted like Lambda, ALambda, e+,...,pi-,pi0
		vector<McParticle*> MCParticleList   ()   { return m_sortedMcPList;     } 
		vector<McParticle*> allMCParticleList()   { return m_allMcPList;        } 
		vector<McParticle*> MCDecayParticleList() { return m_mcDecayList;       } 
		int                 nDecayParticles  ()   { return m_mcDecayList.size();} 

		// get the total MC energy (to check that all particles are accounted for)
		double  MCTotalEnergy();


		// flags for the decay code
		int MCDecayCode1(){ 
			if (m_mcDecayCode1 != -1) {}
			else {  m_mcDecayCode1 = 
				nParticles(kGamma)                            * 1000000 +
					nParticles(kKp)                       * 100000 +
					nParticles(kKm)                       * 10000 +
					nVertices (kKs,kPip,kPim)             * 1000 +
					nParticles(kPip)                      * 100 +
					nParticles(kPim)                      * 10 +
					nVertices (kPi0,kGamma,kGamma)        * 1; }
			return m_mcDecayCode1; 
		}

		int MCDecayCode2(){ 
			if (m_mcDecayCode2 != -1) {}
			else { m_mcDecayCode2 = nVertices(kLambda, kPp,kPim) * 100000000 +
				nVertices(kALambda,kPm,kPip)                 * 10000000 +
					nParticles(kEp)                      * 1000000 +
					nParticles(kEm)                      * 100000 +
					nParticles(kMup)                     * 10000 +
					nParticles(kMum)                     * 1000 +
					nParticles(kPp)                      * 100 +
					nParticles(kPm)                      * 10 +
					nVertices(kEta,kGamma,kGamma)        * 1; }
			return m_mcDecayCode2; 
		}

		int MCDecayCode3(){ 
			if (m_mcDecayCode3 != -1) {}
			else { m_mcDecayCode3 =  
				nParticles(kDsp)                      * 100000 +
				nParticles(kDsm)                      * 10000 +
				nParticles(kDp )                      * 1000 +
				nParticles(kDm )                      * 100 +
				nParticles(kD0 )                      * 10 +
				nParticles(kD0bar)                    * 1; }
			return m_mcDecayCode3; 
		}
		
		int MCDecayCode4(){ 
			if (m_mcDecayCode4 != -1) {}
			else { int nNu = 
				nParticles(kNuE)         +
				nParticles(kNuMu)        + 
				nParticles(kNuTau)       + 
				nParticles(kAntiNuE)     + 
				nParticles(kAntiNuMu)    + 
				nParticles(kAntiNuTau);
				m_mcDecayCode4 =  
					nParticles(kN)           * 100000 +
					nParticles(kAntiN)       * 100000 +
					nNu                      * 10000 +
					nParticles(kPsi2S)       * 1000 +
					nParticles(kHc   )       * 100 +
					nParticles(kChic1)       * 10 +
					nParticles(kJpsi )       * 1 ; }
				return  m_mcDecayCode4; 
		}

		// flag for extra final state particles
		int MCExtras(){ 
			if (m_mcExtras != -1) {}
			else { m_mcExtras = (
					nParticles(kNuE)         +
					nParticles(kNuMu)        + 
					nParticles(kNuTau)       + 
					nParticles(kAntiNuE)     + 
					nParticles(kAntiNuMu)    + 
					nParticles(kAntiNuTau))  * 1000 + 
		                        nParticles(kKl)          *  100 +
					nParticles(kN)           *   10 +
					nParticles(kAntiN)       *    1 ; }
			return m_mcExtras; 
		}

		// count the number of FSR gammas produced in this event
		int MCFSRGamma(){  
			if (m_mcFSRGamma != -1) {}					     
			else { m_mcFSRGamma = nParticles(kFSRGamma); }
			return m_mcFSRGamma; 
		}

		// id of particles coming from original particle (psi(2S),etc)
		int MCDecayParticle(unsigned int i){ 
			if (i >= m_mcDecayList.size()) return 0;
			return m_mcDecayList[i]->particleProperty(); 
		}

		// flag for the production of chi_cJ
		int MCChicProduction(){      
			if (m_mcChicProduction != -1) {}
			else if (hasDecay(kGamma,kChic0)){ m_mcChicProduction = 10; }
			else if (hasDecay(kGamma,kChic1)){ m_mcChicProduction = 11; }
			else if (hasDecay(kGamma,kChic2)){ m_mcChicProduction = 12; }
			else if (
					(hasParticle(kChic0)) ||
					(hasParticle(kChic1)) ||
					(hasParticle(kChic2)) ) { m_mcChicProduction = 1; }
			else                                    { m_mcChicProduction = 0; }
			return m_mcChicProduction; 
		}

		// flag for the production of J/psi

		int MCJPsiProduction(){      
			if (m_mcJPsiProduction != -1) {}
			else if (hasDecay(kJpsi,kPip,kPim)){ m_mcJPsiProduction = 1; }
			else if (hasDecay(kJpsi,kPi0,kPi0)){ m_mcJPsiProduction = 2; }
			else if (hasDecay(kJpsi,kEta))     { m_mcJPsiProduction = 3; }
			else if (hasDecay(kJpsi,kGamma))   { m_mcJPsiProduction = 4; }
			else if (hasDecay(kJpsi,kPi0))     { m_mcJPsiProduction = 5; }
			else if (hasParticle(kJpsi))       { m_mcJPsiProduction = 6; }
			else                               { m_mcJPsiProduction = 0; }
			return m_mcJPsiProduction; 
		}


		// flag for the production of eta_c

		int MCEtacProduction(){      
			if (m_mcEtacProduction != -1) {}
			else if (hasDecay(kEtac,kGamma))   { m_mcEtacProduction = 1; }
			else if (hasParticle(kEtac))       { m_mcEtacProduction = 2; }
			else                               { m_mcEtacProduction = 0; }
			return m_mcEtacProduction; 
		}


		// flag for the production of h_c

		int MCHcProduction(){        
			if (m_mcHcProduction != -1) {}
			else if (hasDecay(kHc,kPip,kPim)){ m_mcHcProduction = 1; }
			else if (hasDecay(kHc,kPi0,kPi0)){ m_mcHcProduction = 2; }
			else if (hasDecay(kHc,kEta))     { m_mcHcProduction = 3; }
			else if (hasDecay(kHc,kGamma))   { m_mcHcProduction = 4; }
			else if (hasDecay(kHc,kPi0))     { m_mcHcProduction = 5; }
			else if (hasParticle(kHc))       { m_mcHcProduction = 6; }
			else                             { m_mcHcProduction = 0; }
			return m_mcHcProduction; 
		}


		// flag for the decay of the eta
		int MCEtaDecay(){  
			if (m_mcEtaDecay != -1) {}					     
			else { m_mcEtaDecay = 
				nVertices(kEta,kGamma,kGamma)    *     1 +
				nVertices(kEta,kPi0,kPi0,kPi0)   *    10 +
				nVertices(kEta,kPip,kPim,kPi0)   *   100 +
				nVertices(kEta,kPip,kPim,kGamma) *  1000 +
				nVertices(kEta,kEp,kEm,kGamma)   * 10000 ; }
			return m_mcEtaDecay; 
		}


		// flag for the decay of the etaprime
		int MCEtaprimeDecay(){  
			if (m_mcEtaprimeDecay != -1) {}					     
			else { m_mcEtaprimeDecay = 
				nVertices(kEtaprime,kPip,kPim,kEta)   * 1 +
				nVertices(kEtaprime,kPi0,kPi0,kEta)   * 10 +
				nVertices(kEtaprime,kGamma,kRho0)     * 100 +
				nVertices(kEtaprime,kGamma,kPip,kPim) * 1000 +
				nVertices(kEtaprime,kGamma,kOmega)    * 10000 +
				nVertices(kEtaprime,kGamma,kGamma)    * 100000 +
				nVertices(kEtaprime,kPi0,kPi0,kPi0)   * 1000000; }
			return m_mcEtaprimeDecay; 
		}


		// flag for the decay of the phi
		int MCPhiDecay(){  
			if (m_mcPhiDecay != -1) {}					     
			else { m_mcPhiDecay = 
				nVertices(kPhi,kKp,kKm)          *    1 +
				nVertices(kPhi,kKs,kKl)          *   10 +
				nVertices(kPhi,kPip,kPim,kPi0)   *  100 +
				(nVertices(kPhi,kRhop,kPim)+
				 nVertices(kPhi,kRhom,kPip)+
				 nVertices(kPhi,kRho0,kPi0))     *  1000+
				nVertices(kPhi,kGamma,kEta)      * 10000; }
			return m_mcPhiDecay; 
		}


		// flag for the decay of the omega
		int MCOmegaDecay(){  
			if (m_mcOmegaDecay != -1) {}					     
			else { m_mcOmegaDecay = 
				nVertices(kOmega,kPip,kPim,kPi0) *   1 +
				nVertices(kOmega,kPi0,kGamma)    *  10 +
				nVertices(kOmega,kPip,kPim)      * 100; }
			return m_mcOmegaDecay; 
		}


		// flag for the decay of the ks
		int MCKsDecay(){  
			if (m_mcKsDecay != -1) {}					     
			else { m_mcKsDecay = 
				nVertices(kKs,kPip,kPim) * 1 +
				nVertices(kKs,kPi0,kPi0) * 10; }
			return m_mcKsDecay; 
		}




		// helper function that returns the name of a particle

		string particleType(const McParticle* mcParticle);
		string particleType(int id);

                // flag for the decay of the D(s) messon
                int  MCDTMode(const McParticle* D);  

		// helper function that prints the mcParticleCol to the screen

		void printInformation(int);


	private:

		bool isParticle (const McParticle* mcParticle, int idParticle);
		int  nParticles (int idParticle);
		bool hasParticle(int idParticle);
		void nPrimaryParticle(SmartDataPtr<Event::McParticleCol> mcParticleCol);

		int nVertices(  int idParent, 
				int idDaughter1,
				int idDaughter2,
				int idDaughter3  = 0,
				int idDaughter4  = 0,
				int idDaughter5  = 0,
				int idDaughter6  = 0,
				int idDaughter7  = 0,
				int idDaughter8  = 0,
				int idDaughter9  = 0,
				int idDaughter10 = 0
				);
		int dVertices(  int idParent, 
				int idDaughter1,
				int idDaughter2,
				int idDaughter3  = 0,
				int idDaughter4  = 0,
				int idDaughter5  = 0,
				int idDaughter6  = 0,
				int idDaughter7  = 0,
				int idDaughter8  = 0,
				int idDaughter9  = 0,
				int idDaughter10 = 0
				);
		bool hasVertex(int idParent, 
				int idDaughter1,
				int idDaughter2,
				int idDaughter3  = 0,
				int idDaughter4  = 0,
				int idDaughter5  = 0,
				int idDaughter6  = 0,
				int idDaughter7  = 0,
				int idDaughter8  = 0,
				int idDaughter9  = 0,
				int idDaughter10 = 0
				);

		int nDecays(    int idDaughter1,
				int idDaughter2,
				int idDaughter3  = 0,
				int idDaughter4  = 0,
				int idDaughter5  = 0,
				int idDaughter6  = 0,
				int idDaughter7  = 0,
				int idDaughter8  = 0,
				int idDaughter9  = 0,
				int idDaughter10 = 0
				);
		bool hasDecay(  int idDaughter1,
				int idDaughter2,
				int idDaughter3  = 0,
				int idDaughter4  = 0,
				int idDaughter5  = 0,
				int idDaughter6  = 0,
				int idDaughter7  = 0,
				int idDaughter8  = 0,
				int idDaughter9  = 0,
				int idDaughter10 = 0
				);

		bool hasDaughters(const McParticle* mcParticle, 
				int idDaughter1,
				int idDaughter2,
				int idDaughter3  = 0,
				int idDaughter4  = 0,
				int idDaughter5  = 0,
				int idDaughter6  = 0,
				int idDaughter7  = 0,
				int idDaughter8  = 0,
				int idDaughter9  = 0,
				int idDaughter10 = 0
				);

		bool DhasDaughters(const McParticle* mcParticle, 
				int idDaughter1,
				int idDaughter2,
				int idDaughter3  = 0,
				int idDaughter4  = 0,
				int idDaughter5  = 0,
				int idDaughter6  = 0,
				int idDaughter7  = 0,
				int idDaughter8  = 0,
				int idDaughter9  = 0,
				int idDaughter10 = 0
				);
		vector<McParticle*> getDaughters(const McParticle* mcParticle);
		bool hasDMothers(const McParticle* mcParticle, const int mid=411);


		template <typename T> void FreeDelAll( T & t ) {
			for(int i=0; i<t.size(); i++) delete t[i];
			//
			T tmp; 	t.swap(tmp);
		}
		
		template <typename T> void FreeAll( T & t ) {
			T tmp; 	t.swap(tmp);
		}

		static const int kPsi2S	         =  100443;     
		static const int kPsi3770        =   30443;     
		static const int kGamma	         =      22;         
		static const int kFSRGamma       =     -22;        
		static const int kZ0   	         =      23;         
		static const int kCluster        =      91;         
		static const int kString         =      92;         
		static const int kHc             =   10443;      
		static const int kChic0          =   10441;      
		static const int kChic1	         =   20443;      
		static const int kChic2	         =     445; 
		static const int kChic0p         =      61;      
		static const int kChic1p         =      62;      
		static const int kChic2p         =      63; 
		static const int kJpsi           =     443;        
		static const int kEtac	         =     441;        
		static const int kPhi            =     333;        
		static const int kOmega          =     223;        
		static const int kPi0 	         =     111;        
		static const int kPip 	         =     211;        
		static const int kPim 	         =    -211;       
		static const int kRho0           =     113;        
		static const int kRhop           =     213;        
		static const int kRhom           =    -213;       
		static const int kA00            =   10111;        
		static const int kA0p            =   10211;        
		static const int kA0m            =  -10211;        
		static const int kB10            =   10113;        
		static const int kB1p            =   10213;        
		static const int kB1m            =  -10213;       
		static const int kA10            =   20113;        
		static const int kA1p            =   20213;        
		static const int kA1m            =  -20213;       
		static const int kF01370         =   10221;       
		static const int kF01500         =   50221;       
		static const int kH1             =   10223;       
		static const int kH1p            =   10333;       
		static const int kA20            =     115;        
		static const int kA2p            =     215;        
		static const int kA2m            =    -215;       
		static const int kEtaprime       =     331;        
		static const int kEta 	         =     221;        
		static const int kKs	            =     310;        
		static const int kKl	            =     130;        
		static const int kKp  	         =     321;        
		static const int kKm  	         =    -321;       
		static const int kPp  	         =    2212;       
		static const int kPm  	         =   -2212;      
		static const int kN              =    2112;       
		static const int kAntiN          =   -2112;      
		static const int kEp  	         =     -11;         
		static const int kEm  	         =      11;        
		static const int kMup 	         =     -13;         
		static const int kMum 	         =      13;        
		static const int kTaup 	         =     -15;        
		static const int kTaum 	         =      15;         
		static const int kNuE            =      12;         
		static const int kNuMu           =      14;         
		static const int kNuTau          =      16;         
		static const int kAntiNuE        =     -12;        
		static const int kAntiNuMu       =     -14;        
		static const int kAntiNuTau      =     -16;        
		static const int kF0600          = 9000221;    
		static const int kK0             =     311;        
		static const int kAntiK0         =    -311;       
		static const int kKstarp         =     323;        
		static const int kKstarm         =    -323;       
		static const int kKstar0         =     313;        
		static const int kAntiKstar0     =    -313;
		static const int kK10            =   10313;        
		static const int kAntiK10        =  -10313;
		static const int kK0star0        =   10311;        
		static const int kAntiK0star0    =  -10311;        
		static const int kK0starp        =   10321;        
		static const int kK0starm        =  -10321;        
		static const int kK1p            =   10323;        
		static const int kK1m            =  -10323;        
		static const int kLambda         =    3122;
		static const int kALambda        =   -3122;
		static const int kD0             =     421;
		static const int kD0bar          =    -421;
		static const int kDp             =     411;
		static const int kDm             =    -411;
		static const int kDsp            =     431;
		static const int kDsm            =    -431;
		static const int kDstarP         =     413;
		static const int kDstarM         =    -413;
		static const int kDstar          =     423;
		static const int kAntiDstar      =    -423;
		static const int kDsstarP        =     433;
		static const int kDsstarM        =    -433;
		static const int kPsi4040        = 9000443;
		static const int kPsi4160        = 9010443;
		static const int kPsi4415        = 9020443;
		static const int kY4260          = 9030443;
		static const int kY4360          = 9040443;
		static const int kDeltapp        =    2224;
		static const int kAntiDeltapp    =   -2224;
		static const int kSigma0         =    3212;
		static const int kAntiSigma0     =   -3212;
		static const int kSigmastarm     =    3114;
		static const int kAntiSigmastarp =   -3114;
		static const int kXi0            =    3322;
		static const int kAntiXi0        =   -3322;
		static const int kXistarp        =    3314;
		static const int kAntiXistarm    =   -3314;

		vector<McParticle*> m_allMcPList;
		vector<McParticle*> m_mcPList;
		vector<McParticle*> m_sortedMcPList;
		vector<McParticle*> m_mcDecayList;


		int    m_nDecays     ;
		int    m_mcDecayCode1;
		int    m_mcDecayCode2;
		int    m_mcDecayCode3;
		int    m_mcDecayCode4;
		int    m_mcExtras;
		int    m_mcChicProduction;
		int    m_mcJPsiProduction;
		int    m_mcHcProduction;
		int    m_mcEtacProduction;
		int    m_mcDDecay;
		int    m_mcEtaDecay;
		int    m_mcEtaprimeDecay;
		int    m_mcPhiDecay;
		int    m_mcOmegaDecay;
		int    m_mcKsDecay;
		int    m_mcFSRGamma;
		double m_mcTotalEnergy;
		vector<string> m_particleNames;
};
#endif
