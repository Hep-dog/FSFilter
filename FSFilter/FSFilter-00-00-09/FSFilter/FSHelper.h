#ifndef FSHELPER_H
#define FSHELPER_H

using namespace std;

#include <string>
#include <map>
#include "EvtRecEvent/EvtRecEvent.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "EvtRecEvent/EvtRecPi0.h" 
#include "EvtRecEvent/EvtRecEtaToGG.h" 
#include "EvtRecEvent/EvtRecVeeVertex.h"
#include "EvtRecEvent/EvtRecDTag.h"
#include "DTagTool/DTagTool.h"

#include "VertexFit/KalmanKinematicFit.h"
//#include "VertexFit/KinematicFit.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"

#include "CLHEP/Vector/LorentzVector.h"

#include "FSFilter/NTupleHelper.h"
#include "FSFilter/YUPING.h"
#include "FSFilter/Utility.h"


using namespace Utility;
class NTupleHelper;
class FSParticle;
class FSCut;
class FSMaC;


class FSMaC{

	public:

		FSMaC(const string& initialization);
		string FSName()      { return m_FSName; }
		double MassCons()    { return m_MassCons; }
		vector<string> getDaughtersName() { return m_daughterName; }
		void  Print() { 
			printf("\n");
			printf("... Check mass constraint : %s\n", m_FSName.data() ); 
			printf("... Check mass constraint : %s\n", m_submodeName.data() ); 
			printf("... Check mass constraint : constrain " ); 
			for(int i=0; i<m_daughterName.size();i++){
				printf(" %5s", m_daughterName[i].data()); 
			}
			printf(" to %5s\n", m_NameCons.data());
		}

	private:

		string         m_FSName;
		string         m_submodeName;
		string         m_NameCons;
		double         m_MassCons;
		vector<int>    m_daughterList;
		vector<string> m_daughterName;

};




class FSInfo{

	public:

		FSInfo(string FSName, NTupleHelper* nt, NTupleHelper* ntgen);
		~FSInfo();

		string FSName()                { return m_FSName;                               }

		bool exclusive()               { return (m_FSName.find("EXC") != string::npos); }
		bool inclusive()               { return (m_FSName.find("INC") != string::npos); }
		bool extracons()               { return  m_FSMaCs.size()>0; }

		vector<string> particleNames() { return m_particleNames;                        }
		vector<int>    particleStatus(){ return m_particleStatus;                       }
		int nChargedParticles()        { return m_nChargedParticles;                    }
		int nFSParticles()             { return m_particleNames.size();                 }
		bool allNeutral()              { return m_nChargedParticles == 0;               }

		NTupleHelper* NT()             { return m_NT;                                   }
		NTupleHelper* NTGen()          { return m_NTGen;                                }

		int decayCode1()               { return m_decayCode1;                           }
		int decayCode2()               { return m_decayCode2;                           }
		int decayCode3()               { return m_decayCode3;                           }
		int decayCode4()               { return m_decayCode4;                           }
		int nMissingParticles()        { return m_nMissingParticles;                    }

		bool hasParticle(string particleName){  
			for (unsigned int i = 0; i < m_particleNames.size(); i++){
				if (m_particleNames[i] == particleName) return true; }
			return false; 
		}
	
	        double MassCons(){if (extracons()) return m_FSMaCs[0]->MassCons(); else return -1; }
		bool   IsItInTheDaughgerList( const string pname ) {  
			if( m_FSMaCs.size() ==0 ) return false; 
			vector<string> list = m_FSMaCs[0]->getDaughtersName(); 
			for(int i =0; i<list.size(); i++)
				if (pname==list[i]) return true;
			return false; 
		}

		void Print(){ 
			cout << "FSFilter:  Checking the Final State " << m_FSName << endl;
			for (unsigned int i = 0; i < m_particleNames.size(); i++){
				if (m_particleStatus[i]==1)printf("FSFilter: %8s:  normal\n",m_particleNames[i].data());
				else                       printf("FSFilter: %8s: missing\n",m_particleNames[i].data());
			}
		}

		double MissingMass2(){
			if(missingMassFit()) return m_missingMassValue*m_missingMassValue; 
			else                 return 0; 
		}

		bool   constrain4Mom ()             { return m_Constrain4Mom ; }
		bool   missingMassFit()             { return m_missingMassFit; }
		double missingMassValue()           { return m_missingMassValue; }
		void   setMissingMass(double m)     { m_missingMassValue = m; }
		void   addMissingParticle(string p) {
			m_nMissingParticles++;
			m_missedParticle = p;
			m_missingMassFit = true;
			m_particleNames .push_back(p); 
			m_particleStatus.push_back(0); 
			setMissingMass(Mass(p)); 
		}


		vector< vector<FSParticle*> >& particleCombinations() { return m_particleCombinations; }


		// check to see if a certain event hypothesis satisfies the list of 
		// cuts on intermediate masses, etc.

		bool evaluateFSCuts( const vector<FSParticle*>& particleCombination,
				const HepLorentzVector& pInitial, string fourVectorType );


		// externally set the list of particle combinations

		void setParticleCombinations( const vector< vector<FSParticle*> >& particleCombinations)
		{ m_particleCombinations = particleCombinations; }


		// add a new FSCut (a cut on intermediate mass, for example)

		void addFSCut(FSCut* fsCut){ m_FSCuts.push_back(fsCut); }
		// add a new FSMaC (a Constraint on intermediate mass)
		void addFSMaC(FSMaC* fsMaC){ m_FSMaCs.push_back(fsMaC); }

		// static functions to unpack the final state name and parse strings

		static vector<string> getParticleNamesFromFSName   ( const string& FSName );
		static vector<int>    getDecayCodeFromParticleNames( const vector<string>& particleNames );
		static vector<int>    getDecayCodeFromFSName       ( const string& FSName );
		static vector<string> parseString                  ( const string& inputString );
		static int    getNChargedParticlesFromParticleNames( const vector<string>& particleNames, const vector<string>& particleStatus);

	 	private:
			string m_FSName;
			vector<string> m_particleNames;
			vector<int>    m_particleStatus;
			int            m_nChargedParticles;
			int            m_nMissingParticles;
			NTupleHelper*  m_NT;
			NTupleHelper*  m_NTGen;

			int m_decayCode1;
			int m_decayCode2;
			int m_decayCode3;
			int m_decayCode4;

			bool   m_hasKs;

			bool   m_Constrain4Mom ;
			bool   m_missingMassFit;
			double m_missingMassValue;
			string m_missedParticle;
			// returns all combinations of indices for a submode of this final state
			// example:  final state = K+ K- pi+ pi+ pi- pi- pi0  submode = pi+ pi0
			//           returns 2,6; 3,6
			vector< vector<unsigned int> >& submodeIndices(const string& submodeName);

			vector<FSCut*>                                m_FSCuts;
			vector<FSMaC*>                                m_FSMaCs;
			vector<vector<FSParticle*> >                  m_particleCombinations;
			map<string, vector< vector <unsigned int> > > m_submodeIndices;


};

class FSParticle{

	public:

		FSParticle(string           name, bool missed);
		FSParticle(EvtRecTrack*       tk, string name, bool yuping = false);
		FSParticle(RecEmcShower*      sh, string name);
		FSParticle(EvtRecPi0*        pi0, string name);
		FSParticle(EvtRecEtaToGG*    eta, string name);
		FSParticle(EvtRecVeeVertex*  vee, string name);
		FSParticle(EvtRecDTag*      dmes, string name, int);
		~FSParticle();
      
		// TRACK
		EvtRecTrack*     track()          { return m_track; }
		RecMdcKalTrack*  kalTrack()       { return m_kalTrack; }
		WTrackParameter  initialWTrack()  { return m_initialWTrack; }
		WTrackParameter  vertexFitWTrack(){ return m_vertexFitWTrack; }   
		void setVertexFitWTrack(const WTrackParameter& wtrack){ m_vertexFitWTrack = wtrack; }

		// SHOWER
		RecEmcShower* shower(){ return m_shower; }

		// PI0
		EvtRecPi0*    pi0()   { return m_pi0;    }
		RecEmcShower* pi0Lo() { return m_pi0Lo;  }
		RecEmcShower* pi0Hi() { return m_pi0Hi;  }

		// ETA
		EvtRecEtaToGG* eta()   { return m_eta;   }
		RecEmcShower*  etaLo() { return m_etaLo; }
		RecEmcShower*  etaHi() { return m_etaHi; }
      
		// D & Ds
		void                        dmesClear           (); 
		EvtRecDTag*                 dmes                () {return m_dmes;                }
		vector<EvtRecTrack*>        dmesTrack           () {return m_dmesTrack;           }
		vector<RecMdcKalTrack*>     dmesKalTrack        () {return m_dmesKalTrack;        }
		vector<WTrackParameter>     dmesInitialWTrack   () {return m_dmesInitialWTrack;   }
		vector<WTrackParameter>     dmesVertexFitWTracks() {return m_dmesVertexFitWTracks;}
		vector<WTrackParameter>     dmesVertexFitWTrack () {return m_dmesVertexFitWTrack; }
		vector<RecEmcShower*>       dmesShowers         () {return m_dmesShowers;         }
		double*                     dmesLSigma          () {return m_dmesLSigma;          } 
		HepLorentzVector            dmesShFourMomentum  () {return m_dmesShFourMomentum;  }
		double                      dmesMass            () {return m_dmesMass;            } 
		int                         dmesTagmode         () {return m_dmesTagmode;         } 
		int                         dmesnKs             () {return m_dmesnKs    ;         } 
		int                         dmesCharm           () {return m_dmesCharm  ;         } 
		int                         dmesCharge          () {return m_dmesCharge ;         } 
		int                         dmesNTracks         () {return m_dmesNTracks;         } 
		int                         dmesNShowers        () {return m_dmesNShowers;        } 
		void                        setdmesLSigma       (const vector<double> dmesLSigma);
		int                         dmesKsCut           (double LCut=2.0) ; 
		void                        setdmesVertexFitWTracks(const vector<WTrackParameter> wtracks);
		void                        setdmesVertexFitWTrack (const vector<WTrackParameter> wtracks);

		// KSHORT AND LAMBDA
		EvtRecVeeVertex* vee()                 { return m_vee; }
		EvtRecTrack*     veeTrack1()           { return m_veeTrack1; }
		RecMdcKalTrack*  veeKalTrack1()        { return m_veeKalTrack1; }
		WTrackParameter  veeInitialWTrack1()   { return m_veeInitialWTrack1; }
		WTrackParameter  veeVertexFitWTrack1() { return m_veeVertexFitWTrack1; }
		EvtRecTrack*     veeTrack2()           { return m_veeTrack2; }
		RecMdcKalTrack*  veeKalTrack2()        { return m_veeKalTrack2; }
		WTrackParameter  veeInitialWTrack2()   { return m_veeInitialWTrack2; }
		WTrackParameter  veeVertexFitWTrack2() { return m_veeVertexFitWTrack2; }
		WTrackParameter  veeVertexFitWTrack()  { return m_veeVertexFitWTrack; }
		double           veeLSigma()           { return m_veeLSigma; }
		void setVeeVertexFitWTrack1(const WTrackParameter& wtrack){ m_veeVertexFitWTrack1 = wtrack; }
		void setVeeVertexFitWTrack2(const WTrackParameter& wtrack){ m_veeVertexFitWTrack2 = wtrack; }
		void setVeeVertexFitWTrack (const WTrackParameter& wtrack){ m_veeVertexFitWTrack  = wtrack; }
		void setVeeLSigma          (double veeLSigma)             { m_veeLSigma = veeLSigma; }

		// COMMON INFORMATION
		string           name()             { return m_name;  }
		double           mass()             { return m_mass;  }
		bool             missed()           { return m_missed;}
		bool             vtxfit_done()      { return m_vtxfit;}
		void             set_miss(bool miss){ m_missed = miss;}
		//
		HepLorentzVector rawFourMomentum()  { return m_rawFourMomentum; }
		HepLorentzVector intFourMomentum()  { return m_intFourMomentum; }
		HepLorentzVector fitFourMomentum()  { return m_fitFourMomentum; }
		//
		void setRawFourMomentum (const HepLorentzVector& p) {m_rawFourMomentum  = p;}
		void setIntFourMomentum (const HepLorentzVector& p) {m_intFourMomentum  = p;}
		void setFitFourMomentum (const HepLorentzVector& p) {m_fitFourMomentum  = p;}


		bool duplicate(FSParticle* fsp);
		vector<int> trackId()  { return m_trackId;  }
		vector<int> showerId() { return m_showerId; }

		HepLorentzVector fourMomentum( RecEmcShower* sh );

		void   PrintTrackAndShowers ( );

	private:

		EvtRecTrack*                m_track;
		RecMdcKalTrack*             m_kalTrack;
		WTrackParameter             m_initialWTrack;
		WTrackParameter             m_vertexFitWTrack;

		RecEmcShower*               m_shower;

		EvtRecPi0*                  m_pi0;
		RecEmcShower*               m_pi0Lo;
		RecEmcShower*               m_pi0Hi;

		EvtRecEtaToGG*              m_eta;
		RecEmcShower*               m_etaLo;
		RecEmcShower*               m_etaHi;

		EvtRecVeeVertex*            m_vee;
		EvtRecTrack*                m_veeTrack1;
		RecMdcKalTrack*             m_veeKalTrack1;
		WTrackParameter             m_veeInitialWTrack1;
		WTrackParameter             m_veeVertexFitWTrack1;
		EvtRecTrack*                m_veeTrack2;
		RecMdcKalTrack*             m_veeKalTrack2;
		WTrackParameter             m_veeInitialWTrack2;
		WTrackParameter             m_veeVertexFitWTrack2;
		WTrackParameter             m_veeVertexFitWTrack;
		double                      m_veeLSigma;

		EvtRecDTag*                 m_dmes;
		vector<EvtRecTrack*>        m_dmesTrack;
		vector<RecMdcKalTrack*>     m_dmesKalTrack;
		vector<WTrackParameter>     m_dmesInitialWTrack;
		vector<WTrackParameter>     m_dmesVertexFitWTracks;
		vector<WTrackParameter>     m_dmesVertexFitWTrack;
		vector<RecEmcShower*>       m_dmesShowers;
		HepLorentzVector            m_dmesShFourMomentum;
		HepLorentzVector            m_dmesTkFourMomentum;
		double                      m_dmesLSigma[10];
		double                      m_dmesMass   ; 	
		int                         m_dmesnKs    ;
		int    	                    m_dmesTagmode;
		int                         m_dmesCharm  ;
		int                         m_dmesCharge ;
		int                         m_dmesNTracks;
		int                         m_dmesNShowers;

		string m_name;
		double m_mass;
		bool   m_missed, m_vtxfit;
		HepLorentzVector            m_rawFourMomentum;
		HepLorentzVector            m_intFourMomentum;
		HepLorentzVector            m_vtxFourMomentum;
		HepLorentzVector            m_fitFourMomentum;

		vector<int>                 m_trackId;
		vector<int>                 m_showerId;
};

//********************************************************************
//********************************************************************
//********************************************************************
//
//   The FSCut class:  defines cuts on intermediate masses
//                     and recoil masses
//
//********************************************************************
//********************************************************************
//********************************************************************


class FSCut{

	public:

		FSCut(const string& initialization);

		string FSName()      { return m_FSName; }
		string submodeName() { return m_submodeName; }
		string cutType()     { return m_cutType; }
		double lowCut()      { return m_lowCut;  }
		double highCut()     { return m_highCut; }

		bool Raw()     { return (m_cutType.find("Raw")     != string::npos); }
		bool Int()     { return (m_cutType.find("Int")     != string::npos); }
		bool Fit()     { return (m_cutType.find("Fit")     != string::npos); } 
		bool Recoil()  { return (m_cutType.find("Recoil")  != string::npos); }
		bool Mass()    { return (m_cutType.find("Mass")    != string::npos); }
		bool Squared() { return (m_cutType.find("Squared") != string::npos); }


	private:

		string m_FSName;
		string m_submodeName;
		string m_cutType;
		double m_lowCut;
		double m_highCut;

};
#endif
