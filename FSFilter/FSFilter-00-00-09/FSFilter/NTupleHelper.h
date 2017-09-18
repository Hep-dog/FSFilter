#ifndef NTUPLEHELPER_H
#define NTUPLEHELPER_H

using namespace std;

#include <string>
#include <map>
#include "EvtRecEvent/EvtRecEvent.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "EvtRecEvent/EvtRecDTag.h"
#include "DTagTool/DTagTool.h"
#include "ParticleID/ParticleID.h"

#include "FSFilter/FSHelper.h"
#include "FSFilter/MCTruthHelper.h"
#include "FSFilter/Utility.h"

#include "CLHEP/Vector/LorentzVector.h"

#include "GaudiKernel/NTuple.h"

using namespace Utility;
class FSParticle;
class FSInfo;
class MCTruthHelper;


// ***************************************************************
//
//  CLASS NTupleHelper
//
//    a utility to keep track of and fill trees
//
// ***************************************************************

class NTupleHelper{

	public:

		// constructor takes a Tuple object created by BOSS

		NTupleHelper(NTuple::Tuple* Tree, HepLorentzVector p4);
		~NTupleHelper();


		// generic routine to fill a tree variable;
		//   if the variable doesn't yet exist, it is created

		void fillDouble(string name, double  value);
		void fillLong  (string name, int     value);
		void fillArray (string name, string index_name, double* value, int size);
		void fillArray (string name, string index_name, vector<double> value, int size);

		// fill specific information

		void fill4Momentum   (string index_name, string tag, const vector<HepLorentzVector>& p, const int size);
		void fill4Momentum   (int index, string tag, const HepLorentzVector& p);
		void fill4Momentum   (int index, string tag, const RecEmcShower& p);
		void fill4Momentum   (int index, string tag);
		void fillShower      (int index, string tag, RecEmcShower* p,
				vector<FSParticle*> pi0s,
				SmartDataPtr<EvtRecTrackCol> evtRecTrackCol);
		void fillTrack       (int index, string tag, EvtRecTrack* p,
				VertexParameter beamSpot, int pidStudies=0 );
		void fillPi0         (int index, string tag, EvtRecPi0* p);
		void fillEta         (int index, string tag, EvtRecEtaToGG* p);
		void fillVee         (int index, string tag, EvtRecVeeVertex* p, double LSigma);
		void fillDmes        (int index, string tag, EvtRecDTag* p);
		void fillEvent(SmartDataPtr<Event::EventHeader> eventHeader,
				SmartDataPtr<EvtRecEvent> evtRecEvent, double cmEnergy, double nTRK=-1, double nGAM=-1);
		void fillMCTruth     (MCTruthHelper* mc, FSInfo* fs = NULL, int RootID=100443, string tag="MC");
		void fillMCTruthDT   (MCTruthHelper* mc, FSInfo* fs = NULL, int RootID=100443);
		void fillJPsiFinder  (SmartDataPtr<EvtRecTrackCol> evtRecTrackCol);
		void fillJPsiFinder  (SmartDataPtr<EvtRecPi0Col>   evtRecPi0Col);
		void fillMissingTrack(const vector<FSParticle*> pList, const VertexParameter beamSpot);


		// write the tree

		void write();

	private:

		bool containsEntry(string name);

		NTuple::Tuple*    m_Tree;
		HepLorentzVector  p4psi;


		map<string, NTuple::Item<double>  >  m_ntupleDoubleMap;
		map<string, double>  m_doubleMap;
		
		map<string, NTuple::Item<int>     >    m_ntupleLongMap;
		map<string, int>     m_longMap;
		
		map<string, NTuple::Array<double> >   m_ntupleArrayMap;
		map<string, double*>                        m_arrayMap;

		
		bool m_bookingStage;

		string concatName(string prefix, string base, int index);
		string concatName(string prefix, string base);

};

#endif
