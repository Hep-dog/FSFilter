#ifndef FSFILTER_H
#define FSFILTER_H

using namespace std;

#include <string>
#include <map>

#include   "GaudiKernel/Algorithm.h"
#include   "GaudiKernel/NTuple.h"
#include   "GaudiKernel/ISvcLocator.h"
#include   "GaudiKernel/IDataProviderSvc.h"
#include   "GaudiKernel/Property.h"
#include   "GaudiKernel/Bootstrap.h"
#include   "GaudiKernel/MsgStream.h"
#include   "GaudiKernel/AlgFactory.h"

//#include "EventModel/Event.h"
#include   "EventModel/EventHeader.h"
#include   "EvtRecEvent/EvtRecEvent.h"
#include   "EvtRecEvent/EvtRecTrack.h"

#include   "VertexFit/KalmanKinematicFit.h"
#include   "VertexFit/KinematicFit.h"
#include   "VertexFit/VertexFit.h"
#include   "VertexFit/SecondVertexFit.h"
#include   "VertexFit/IVertexDbSvc.h"
//#include "VertexFit/IBeamEnergySvc.h"
#include   "VertexFit/Helix.h"
#include   "EvtRecEvent/EvtRecPi0.h" 
#include   "EvtRecEvent/EvtRecEtaToGG.h" 
#include   "EvtRecEvent/EvtRecVeeVertex.h"
#include   "EvtRecEvent/EvtRecDTag.h"
#include   "ParticleID/ParticleID.h"
#include   "McTruth/McParticle.h" 
#include   "DTagTool/DTagTool.h"
//
#include "TH1I.h"
#include "TH1F.h"
#include "TH2F.h"
//
#include   "FSFilter/FSHelper.h"
#include   "FSFilter/NTupleHelper.h"
#include   "FSFilter/MCTruthHelper.h"
#include   "FSFilter/Utility.h"
#include   "FSFilter/DTagName.h"
#include   "FSFilter/RscanDQ.h"

class MCTruthHelper;
class NTupleHelper;
using namespace Utility;

class FSFilter : public Algorithm{

	public:
		FSFilter(const std::string& name, ISvcLocator* pSvcLocator);
		StatusCode       initialize        ();
		StatusCode       execute           ();
		StatusCode       finalize          ();
		void             GetPi0            (SmartDataPtr<EvtRecPi0Col>       evtRecPi0Col      );
		void             GetEta            (SmartDataPtr<EvtRecEtaToGGCol>   evtRecEtaToGGCol  );
		void             GetKs             (SmartDataPtr<EvtRecVeeVertexCol> evtRecVeeVertexCol);
		void             GetLambda         (SmartDataPtr<EvtRecVeeVertexCol> evtRecVeeVertexCol);
		void             GetDmeson         (double, int, int, int, string);
		void             GetJpsi           (SmartDataPtr<EvtRecTrackCol> evtRecTrackCol);
		void             GetTrackAndShower (SmartDataPtr<EvtRecTrackCol> evtRecTrackCol, int totalCharged);
		int              GetTotalNoOfTrack (vector<FSParticle*> combo);
		int              GetTotalNoOfGamma (vector<FSParticle*> combo);
		bool             GoodTrack         (EvtRecTrack* p);
		bool             checkCombination  (const vector<FSParticle*>& combo, bool complete, bool inclusive);
		int              nVee              (const vector<FSParticle*>& combo);
		int              nDmes             (const vector<FSParticle*>& combo);
		void             BookHist          ();
		void             CleanEvt          ();
		void             GetEcmP4          ();
	private:
		// input parameters from the job options file
		int               m_eventCounter;// event counter
		int               m_DataMC;
		int               m_SaveMC;
		int               m_runNo , runNoKeep;
		int               m_Golden;
		int               m_RootID;
		int               m_PhotonInBarrel;
		int               m_UseDB ;
		int               m_UseHis;
		int               m_Debug ;
		int               m_pidStudies;
		int               m_trackStudies;
		int               m_neutralStudies;
		int               m_pi0Studies;
		int               m_etaStudies;
		int               m_veeStudies;
		int               m_maxShowers;
		int               m_maxExtraTracks;
		int               m_yuping;
		int               m_MassCons;
		//int               m_Mom4Cons;
		int               m_tightcut;
		int               m_ModeBest;
		int               m_printTruthInformation;
		static const int  MAXFS  = 10000;
		double            nTRK, nGAM;
		double            m_MaxPCut;
		double            m_MaxECut;
		double            m_MinPCut;
		double            m_MinECut;
		double            m_MaximumP;
		double            m_Maxi2ndP;
		double            m_MaximumE;
		double            m_Maxi2ndE;
		double            m_DelMassCut;
		double            m_cmEnergy;
		double            m_ESpread ;
		double            m_crossingAngle;
		double            m_KsSigmaCut;
		double            m_energyTolerance;
		double            m_momentumTolerance;
		double            m_maxChi2DOF;
		double            m_lowerMissingMass2;
		double            m_upperMissingMass2;
		double            m_Checking[MAXFS];
		int               m_CutPass [MAXFS];
		double            m_cutpass [MAXFS][20];
		string            m_FSNames [MAXFS];
		string            m_FSCuts  [MAXFS];
		string            m_FSMaCs  [MAXFS];
		string            m_FSMMFits[MAXFS];
		
		VertexParameter   m_beamSpot;
		HepLorentzVector  p4psi;
		HepVector         m_cpu;

		//
		// vectors  of all types of particle and a map of them
		vector<FSParticle*>  DspList      ;
		vector<FSParticle*>  DsmList      ;
		vector<FSParticle*>  DpList       ;
		vector<FSParticle*>  DmList       ;
		vector<FSParticle*>  D0List       ;
		vector<FSParticle*>  D0barList    ;
		vector<FSParticle*>  lambdaList   ;
		vector<FSParticle*>  alambdaList  ;
		vector<FSParticle*>  mupList      ;
		vector<FSParticle*>  mumList      ;
		vector<FSParticle*>  epList       ;
		vector<FSParticle*>  emList       ;
		vector<FSParticle*>  ppList       ;
		vector<FSParticle*>  pmList       ;
		vector<FSParticle*>  etaList      ;
		vector<FSParticle*>  gammaList    ;
		vector<FSParticle*>  kpList       ;
		vector<FSParticle*>  kmList       ;
		vector<FSParticle*>  ksList       ;
		vector<FSParticle*>  pipList      ;
		vector<FSParticle*>  pimList      ;
		vector<FSParticle*>  pi0List      ;
		vector<FSParticle*>  ParticleTrash; // to prevent memory leakage  
		map< string, vector<FSParticle*> > DictPList;

		// vector of all final states to be analyzed
		vector<FSInfo*>                     m_FSInfoVector;
		DTagTool *                          dtagTool;
		DTagName *                          dtagName;
		RscanDQ  *                          rscanDQ ;

		// save time by only reconstructing particles 
		// if they appear in m_FSInfoVector
		bool m_findEp;
		bool m_findEm;
		bool m_findMup;
		bool m_findMum;
		bool m_findPip;
		bool m_findPim;
		bool m_findKp;
		bool m_findKm;
		bool m_findPp;
		bool m_findPm;
		bool m_findGamma;
		bool m_findPi0;
		bool m_findEta;
		bool m_findKs;
		bool m_findLambda;
		bool m_findaLambda;
		bool m_findD0;    
		bool m_findD0bar; 
		bool m_findDp;    
		bool m_findDm;    
		bool m_findDsp;    
		bool m_findDsm;    

		// MCTruthHelper object
		MCTruthHelper* m_mcTruthHelper;

		// tree for generator level information
		NTupleHelper* m_ntGEN;
		//
		TH1D* h_TrkPar_R     ;
		TH1D* h_TrkPar_Z     ;
		TH1D* h_TrkPar_P     ;
		TH1D* h_TrkPar_COS   ;
		TH1D* h_TrkPar_PHI   ;
		TH1D* h_InfEMC_T     ;
		TH1D* h_InfEMC_E     ;
		TH1D* h_InfEMC_COS   ;
		TH1D* h_InfEMC_PHI   ;
		TH1D* h_ComPar_Pi0   ;
		TH1D* h_ComPi0_Chi2  ;
		TH1D* h_ComPar_Eta   ;
		TH1D* h_ComEta_Chi2  ;
		TH1D* h_ComPar_Ks    ;
		TH1D* h_ComKs_Chi2   ;
		TH1D* h_ComPar_Lamb  ;
		TH1D* h_ComLam_Chi2  ;
		TH1D* h_ComPar_D0    ;
		TH1D* h_ComPar_Dp    ;
		TH1D* h_ComPar_Dsp   ;
		TH1D* h_ComdE_D0     ;
		TH1D* h_ComdE_Dp     ;
		TH1D* h_ComdE_Dsp    ;
		TH1D* h_ComMbc_D0     ;
		TH1D* h_ComMbc_Dp     ;
		TH1D* h_ComMbc_Dsp    ;
};
#endif
