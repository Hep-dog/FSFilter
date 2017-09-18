#ifndef Event_EvtRecJpsiTag_H
#define Event_EvtRecJpsiTag_H

#include "GaudiKernel/ObjectVector.h"
#include "GaudiKernel/ContainedObject.h"
#include "GaudiKernel/SmartRef.h"
#include "GaudiKernel/SmartRefVector.h"
#include "EventModel/EventModel.h"
#include "CLHEP/Matrix/Vector.h"
#include "CLHEP/Matrix/SymMatrix.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include <utility>
#include <vector>

using CLHEP::HepVector;
using CLHEP::HepSymMatrix;
using namespace EventModel;
extern const CLID & CLID_EvtRecJpsiTag;

// 
// To store D Tagged events.
// Author : Chunlei Liu   Date: 2009.1.26
//
class EvtRecJpsiTag : virtual public ContainedObject {
	public:
		virtual const CLID& clID() const {return EvtRecJpsiTag::classID();}
		static  const CLID& classID() {return CLID_EvtRecJpsiTag;}

		EvtRecJpsiTag();
		~EvtRecJpsiTag() {;}

		EvtRecJpsiTag(const EvtRecJpsiTag&);
		EvtRecJpsiTag & operator = (const EvtRecJpsiTag &);


		//selection critera type defined with enum type

		enum SelType
		{
			Loose,
			Tight,
			Default
		};

		//  All decay modes are defined as enum types here
		enum DecayMode
		{
			kEtactoKKPi,

			kJPsitoLL = 100,
			kJPsitoPiPiPi0,

			kUnknown  = 10000

		};

		DecayMode decayMode()    const {return m_decayMode     ;}
		SelType type()           const {return m_type          ;}
		double  Mass()           const {return m_mass          ;}
		int     Charge()         const {return m_charge        ;}
		int     NumOfChildren()  const {return m_numOfChildren ;}
		HepLorentzVector p4()    const {return m_p4            ;}


		SmartRefVector<EvtRecTrack>  tracks()      { return m_tracks;}
		SmartRefVector<EvtRecTrack>  showers()     { return m_showers;}
		SmartRefVector<EvtRecTrack>  otherTracks() { return m_otherTracks;}
		SmartRefVector<EvtRecTrack>  otherShowers(){ return m_otherShowers;}
		SmartRefVector<EvtRecTrack>  pionId()      { return m_pionId;}
		SmartRefVector<EvtRecTrack>  kaonId()      { return m_kaonId;}


		void setdecayMode(DecayMode decayMode) {m_decayMode=decayMode;}
		void settype(SelType type) {m_type=type;}
		void setmass(double mass)  {m_mass=mass;}
		void setcharge(int charge) {m_charge=charge;}
		void setnumOfChildren(int numOfChildren) {m_numOfChildren=numOfChildren;}
		void setp4(HepLorentzVector p4) {m_p4=p4;}

		void addTrack       (const SmartRef<EvtRecTrack> track)  { m_tracks      .push_back(track) ;}
		void addShower      (const SmartRef<EvtRecTrack> shower) { m_showers     .push_back(shower);}
		void addOtherTrack  (const SmartRef<EvtRecTrack> track)  { m_otherTracks .push_back(track) ;}
		void addOtherShower (const SmartRef<EvtRecTrack> shower) { m_otherShowers.push_back(shower);}
		void addPionId      (const SmartRef<EvtRecTrack> pionId) { m_pionId      .push_back(pionId);}
		void addKaonId      (const SmartRef<EvtRecTrack> kaonId) { m_kaonId      .push_back(kaonId);}


		void setTracks      (const SmartRefVector<EvtRecTrack> tracks ) {m_tracks       =  tracks;}
		void setShowers     (const SmartRefVector<EvtRecTrack> showers) {m_showers      = showers;}
		void setPionId      (const SmartRefVector<EvtRecTrack> pionId ) {m_pionId       =  pionId;}
		void setKaonId      (const SmartRefVector<EvtRecTrack> kaonId ) {m_kaonId       =  kaonId;}
		void setOtherTracks (const SmartRefVector<EvtRecTrack> tracks ) {m_otherTracks  =  tracks;}
		void setOtherShowers(const SmartRefVector<EvtRecTrack> showers) {m_otherShowers = showers;}

	private:
		DecayMode                    m_decayMode;
		SelType                      m_type;
		double                       m_mass;
		int                          m_charge;
		unsigned int                 m_numOfChildren;
		HepLorentzVector             m_p4;
		SmartRefVector<EvtRecTrack>  m_tracks;
		SmartRefVector<EvtRecTrack>  m_showers;
		SmartRefVector<EvtRecTrack>  m_otherTracks;
		SmartRefVector<EvtRecTrack>  m_otherShowers;
		SmartRefVector<EvtRecTrack>  m_electronId;
		SmartRefVector<EvtRecTrack>  m_muonId;
		SmartRefVector<EvtRecTrack>  m_pionId;
		SmartRefVector<EvtRecTrack>  m_kaonId;
		SmartRefVector<EvtRecTrack>  m_protonId;
};

typedef ObjectVector<EvtRecJpsiTag> EvtRecJpsiTagCol;
typedef EvtRecJpsiTagCol::iterator  EvtRecJpsiTagIterator;
#endif

