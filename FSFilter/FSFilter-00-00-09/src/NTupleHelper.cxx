#include "FSFilter/NTupleHelper.h"
// ********************************************************************
//    EVENT INFORMATION
// ********************************************************************
void
NTupleHelper::fillEvent(
		SmartDataPtr<Event::EventHeader> eventHeader,
		SmartDataPtr<EvtRecEvent>        evtRecEvent,
		double cmEnergy, double nTRK, double nGAM){
	fillDouble("Run",        eventHeader->runNumber()   );
	fillDouble("Event",      eventHeader->eventNumber() );
	fillDouble("BeamEnergy", cmEnergy/2.0               );
	fillDouble("NTracks",    evtRecEvent->totalCharged());
	fillDouble("NShowers",   evtRecEvent->totalNeutral());
	fillDouble("Flag1",      eventHeader->flag1()       );
	fillDouble("Flag2",      eventHeader->flag2()       );
	fillDouble("nTrk",       nTRK                       );
	fillDouble("nGam",       nGAM                       );
}
// ********************************************************************
//    FOUR MOMENTA
// ********************************************************************
void
NTupleHelper::fill4Momentum(string index_name, string tag, const vector<HepLorentzVector>& p, const int size){
	
	if (m_bookingStage && !containsEntry(index_name)){
		m_Tree->addItem(index_name, m_ntupleLongMap[index_name], 0, 100);
	}
	
	m_longMap[index_name]=size;

	string combname[4]={"Px","Py","Pz","En"}, name;
	for(int i=0; i<4; i++){
		name=concatName(tag,combname[i]);
		if (m_bookingStage && !containsEntry(name)){
			m_Tree->addIndexedItem(name, m_ntupleLongMap[index_name], m_ntupleArrayMap[name]);
		}
	}
	
	if (!m_bookingStage && !containsEntry(name)){
		cout << "NTUPLEHELPER:  Variable " << name << " has not been booked." << endl;
		exit(0);
	}
	
	if (!m_bookingStage && !containsEntry(index_name)){
		cout << "NTUPLEHELPER:  Variable " << index_name << " has not been booked." << endl;
		exit(0);
	}

	for(int j=0; j< 4; j++){
		name=concatName(tag,combname[j]);
		m_arrayMap[name]= new double[100];
		for(int i=0; i<size; i++){
			if(j==0) m_arrayMap[name][i] = p[i].px();
			if(j==1) m_arrayMap[name][i] = p[i].py();
			if(j==2) m_arrayMap[name][i] = p[i].pz();
			if(j==3) m_arrayMap[name][i] = p[i].e ();
		}
	}
}
//
void
NTupleHelper::fill4Momentum(int index, string tag, const HepLorentzVector& p){
	fillDouble(concatName(tag,"Px",index), p.px());
	fillDouble(concatName(tag,"Py",index), p.py());
	fillDouble(concatName(tag,"Pz",index), p.pz());
	fillDouble(concatName(tag,"En",index), p.e());
}
//
void
NTupleHelper::fill4Momentum(int index, string tag){
	fillDouble(concatName(tag,"Px",index), 0.0);
	fillDouble(concatName(tag,"Py",index), 0.0);
	fillDouble(concatName(tag,"Pz",index), 0.0);
	fillDouble(concatName(tag,"En",index), 0.0);
}
//
void
NTupleHelper::fill4Momentum(int index, string tag, const RecEmcShower& p){
	fillDouble(concatName(tag,"Px",index), p.energy()*sin(p.theta())*cos(p.phi()));
	fillDouble(concatName(tag,"Py",index), p.energy()*sin(p.theta())*sin(p.phi()));
	fillDouble(concatName(tag,"Pz",index), p.energy()*cos(p.theta()));
	fillDouble(concatName(tag,"En",index), p.energy());
}
//
// ********************************************************************
//    SHOWER INFORMATION
// ********************************************************************
void
NTupleHelper::fillShower(int index, string tag, RecEmcShower* p, 
		vector<FSParticle*> pi0s,
		SmartDataPtr<EvtRecTrackCol> evtRecTrackCol){


	// find the best pi0 containing this shower

	double pi0Pull = 10000.0;
	for (unsigned int i = 0; i < pi0s.size(); i++){
		if (p->cellId() == pi0s[i]->pi0Lo()->cellId() ||
				p->cellId() == pi0s[i]->pi0Hi()->cellId()){
			double pi0PullTest = sqrt(fabs(pi0s[i]->pi0()->chisq()));
			if (pi0PullTest < pi0Pull) pi0Pull = pi0PullTest;
		}
	}


	// find the closest track to this shower 
	//  (copied from RhoPiAlg, mostly)

	Hep3Vector shpos(p->x(), p->y(), p->z());
	double dang = 200.; 
	for(EvtRecTrackIterator iTrk = evtRecTrackCol->begin();
			iTrk != evtRecTrackCol->end(); iTrk++){ 
		if (!(*iTrk)->isExtTrackValid()) continue;
		RecExtTrack *extTrk = (*iTrk)->extTrack();
		if (extTrk->emcVolumeNumber() == -1) continue;
		Hep3Vector extpos = extTrk->emcPosition();
		double angd = extpos.angle(shpos);
		if(angd < dang){
			dang = angd;
		}
	}
	dang = dang * 180 / 3.1415927;
	// put information in the tree
	fillDouble(concatName(tag, "Time",    index), p->time());
	fillDouble(concatName(tag, "Energy",  index), p->energy());
	fillDouble(concatName(tag, "CosTheta",index), cos(p->theta()));
	fillDouble(concatName(tag, "E925",    index), p->e3x3()/p->e5x5());
	fillDouble(concatName(tag, "Pi0Pull", index), pi0Pull);
	fillDouble(concatName(tag, "Dang",    index), dang);

}
//
void
NTupleHelper::fillMissingTrack(const vector<FSParticle*> pList, const VertexParameter beamSpot ){

        int index = pList.size();
        vector<double> Vz, Vr, Px, Py, Pz, En;
        vector<double> ProbPi, ProbK, ProbP,EoP, EMC;
	for(int i=0; i<index; i++){
		// set up particle ID information
                EvtRecTrack*   p = pList[i]->track(); 
		ParticleID* pid = ParticleID::instance();
		pid->init();
		pid->setMethod(pid->methodProbability());
		pid->setRecTrack(p);
		pid->usePidSys( pid->useDedx()  | 
				pid->useTof1()  | 
				pid->useTof2());
		pid->identify(  pid->onlyPion()     | 
				pid->onlyKaon()     | 
				pid->onlyProton());
		pid->calculate();
		ProbPi .push_back( pid->probPion()  );
		ProbK  .push_back( pid->probKaon()  );
		ProbP  .push_back( pid->probProton());

		//
                HepLorentzVector p4= pList[i]->rawFourMomentum();  
		Px.push_back(p4.x());
		Py.push_back(p4.y());
		Pz.push_back(p4.z());
		En.push_back(p4.t());
		
		// get vertex information
		RecMdcTrack *mdcTrk = p->mdcTrack();
		HepVector a = mdcTrk->helix();
		HepSymMatrix Ea = mdcTrk->err();
		HepPoint3D point0(0.,0.,0.);
		HepPoint3D IP(beamSpot.vx()); 
		VFHelix helixip(point0,a,Ea); 
		helixip.pivot(IP);
		HepVector vecipa = helixip.a();
		double RVtx = fabs(vecipa[0]);
		double ZVtx = vecipa[3];
		Vr.push_back(RVtx  );
		Vz.push_back(ZVtx  );

		// calculate E/p
		double EP = -1.0, Emc=-1;
		if (p->isMdcTrackValid() && p->isEmcShowerValid() && p->mdcTrack()->p() > 0){
			Emc  = p->emcShower()->energy();
			EP   = Emc / p->mdcTrack()->p();
		}
		//
		EMC.push_back(Emc);
		EoP.push_back(EP );
	}

	// put information in the tree
	fillArray(concatName("MissTrk","ProbPi"),  "idx_MissTrk",  ProbPi, index);
	fillArray(concatName("MissTrk","ProbK" ),  "idx_MissTrk",  ProbK , index);
	fillArray(concatName("MissTrk","ProbP" ),  "idx_MissTrk",  ProbP , index);
	fillArray(concatName("MissTrk","Vr"    ),  "idx_MissTrk",  Vr    , index);
	fillArray(concatName("MissTrk","Vz"    ),  "idx_MissTrk",  Vz    , index);
	fillArray(concatName("MissTrk","Px"    ),  "idx_MissTrk",  Px    , index);
	fillArray(concatName("MissTrk","Py"    ),  "idx_MissTrk",  Py    , index);
	fillArray(concatName("MissTrk","Pz"    ),  "idx_MissTrk",  Pz    , index);
	fillArray(concatName("MissTrk","En"    ),  "idx_MissTrk",  En    , index);
	fillArray(concatName("MissTrk","EMC"   ),  "idx_MissTrk",  EMC   , index);
	fillArray(concatName("MissTrk","EoP"   ),  "idx_MissTrk",  EoP   , index);
	//
        FreeAll(ProbPi);
        FreeAll(ProbK );
        FreeAll(ProbP );
        FreeAll(Vr    );
        FreeAll(Vz    );
        FreeAll(Px    );
        FreeAll(Py    );
        FreeAll(Pz    );
        FreeAll(En    );
        FreeAll(EMC   );
        FreeAll(EoP   );
}
// ********************************************************************
//    TRACK INFORMATION
// ********************************************************************
void
NTupleHelper::fillTrack(int index, string tag, EvtRecTrack* p, 
		VertexParameter beamSpot, int pidStudies){


	// set up particle ID information

	ParticleID* pid = ParticleID::instance();
	pid->init();
	pid->setMethod(pid->methodProbability());
	pid->setRecTrack(p);
	pid->usePidSys(pid->useDedx()  | 
			pid->useTof1()  | 
			pid->useTof2());
	pid->identify(pid->onlyPion()     | 
			pid->onlyKaon()     | 
			pid->onlyProton()   | 
			pid->onlyElectron() | 
			pid->onlyMuon());
	pid->calculate();
	double ProbPi = pid->probPion();
	double ProbK  = pid->probKaon();
	double ProbP  = pid->probProton();
	double ProbE  = pid->probElectron();
	double ProbMu = pid->probMuon();


	// get vertex information
	//  (copied from RhoPiAlg)

	RecMdcTrack *mdcTrk = p->mdcTrack();
	HepVector a = mdcTrk->helix();
	HepSymMatrix Ea = mdcTrk->err();
	HepPoint3D point0(0.,0.,0.);
	HepPoint3D IP(beamSpot.vx()); 
	VFHelix helixip(point0,a,Ea); 
	helixip.pivot(IP);
	HepVector vecipa = helixip.a();
	double RVtx = fabs(vecipa[0]);
	double ZVtx = vecipa[3];


	// calculate E/p

	double EP = -1.0, Emc=-1;
	if (p->isMdcTrackValid() && p->isEmcShowerValid() && p->mdcTrack()->p() > 0){
		Emc  = p->emcShower()->energy();
		EP   = Emc / p->mdcTrack()->p();
	}

	// put information in the tree
	fillDouble(concatName(tag,"ProbPi",  index), ProbPi);
	fillDouble(concatName(tag,"ProbK",   index), ProbK);
	fillDouble(concatName(tag,"ProbP",   index), ProbP);
	fillDouble(concatName(tag,"ProbMu",  index), ProbMu);
	fillDouble(concatName(tag,"ProbE",   index), ProbE);
	fillDouble(concatName(tag,"RVtx",    index), RVtx);
	fillDouble(concatName(tag,"ZVtx",    index), ZVtx);
	fillDouble(concatName(tag,"CosTheta",index), cos(p->mdcTrack()->theta()));
	fillDouble(concatName(tag,"EP",      index), EP);
	fillDouble(concatName(tag,"Emc",     index), Emc);
	if (!pidStudies) return;

	double probPH = -1.0;
	double normPH = -1.0;
	double errorPH = -1.0;
	if (p->mdcDedx()){
		probPH  = p->mdcDedx()->probPH();
		normPH  = p->mdcDedx()->normPH();
		errorPH = p->mdcDedx()->errorPH();
	}
	fillDouble(concatName(tag,"ProbPH", index), probPH);
	fillDouble(concatName(tag,"NormPH", index), normPH);
	fillDouble(concatName(tag,"ErrorPH",index), errorPH);
	//fillDouble(concatName(tag,"Index",  index), trackIndex);
}
// ********************************************************************
//    PI0 INFORMATION
// ********************************************************************
void
NTupleHelper::fillPi0(int index, string tag, EvtRecPi0* p){
	fillDouble(concatName(tag,"Mass",index),p->unconMass());
	fillDouble(concatName(tag,"Chi2",index),p->chisq());
}
// ********************************************************************
//    ETA INFORMATION
// ********************************************************************
void
NTupleHelper::fillEta(int index, string tag, EvtRecEtaToGG* p){
	fillDouble(concatName(tag,"Mass",index),p->unconMass());
	fillDouble(concatName(tag,"Chi2",index),p->chisq());
}
// ********************************************************************
//    KS INFORMATION
// ********************************************************************
void
NTupleHelper::fillVee(int index, string tag, EvtRecVeeVertex* p, double LSigma){
	fillDouble(concatName(tag,"Mass",  index), p->mass());
	fillDouble(concatName(tag,"Chi2",  index), p->chi2());
	fillDouble(concatName(tag,"LSigma",index), LSigma);
}
// ********************************************************************
//    Dmeson INFORMATION
// ********************************************************************
void
NTupleHelper::fillDmes(int index, string tag, EvtRecDTag* p){
	fillDouble(concatName(tag,"type"         ,index), p->type());
	fillDouble(concatName(tag,"mass"         ,index), p->mass());
	fillDouble(concatName(tag,"mBC"          ,index), p->mBC());
	fillDouble(concatName(tag,"deltaE"       ,index), p->deltaE());
	fillDouble(concatName(tag,"charge"       ,index), p->charge());
	fillDouble(concatName(tag,"charm"        ,index), p->charm());
	fillDouble(concatName(tag,"mode"         ,index), p->decayMode());
	fillDouble(concatName(tag,"numOfChildren",index), p->numOfChildren());
}
// ********************************************************************
//    TRY TO TAG PSI(2S) --> PI0 PI0 JPSI 
// ********************************************************************
void
NTupleHelper::fillJPsiFinder(SmartDataPtr<EvtRecPi0Col> evtRecPi0Col){

	HepLorentzVector pcm(p4psi);

	// look for psi --> pi0 pi0 J/psi

	double jpsiPiPiRecoil = -10000.0;
	for(EvtRecPi0Col::iterator iPi01 = evtRecPi0Col->begin(); iPi01 != evtRecPi0Col->end(); iPi01++){
		if ((*iPi01)->chisq() >100 ) continue; 
		if (((*iPi01)->unconMass() < 0.110) || ((*iPi01)->unconMass() > 0.150))continue;
		EvtRecTrack* lo1 = const_cast<EvtRecTrack*>((*iPi01)->loEnGamma()); 
		RecEmcShower* loShower = lo1->emcShower();
		if (!((loShower->energy() > 0.025) && (loShower->time() >= 0) && (loShower->time() <= 14) &&
					(((abs(cos(loShower->theta())) < 0.80) && (loShower->energy() > 0.025)) || 
					 ((abs(cos(loShower->theta())) < 0.92) &&
					  (abs(cos(loShower->theta())) > 0.86) && (loShower->energy() > 0.050))))) continue;
		EvtRecTrack* hi1 = const_cast<EvtRecTrack*>((*iPi01)->hiEnGamma()); 
		RecEmcShower* hiShower = hi1->emcShower();
		if (!((hiShower->energy() > 0.025) && (hiShower->time() >= 0) && (hiShower->time() <= 14) &&
					(((abs(cos(hiShower->theta())) < 0.80) && (hiShower->energy() > 0.025)) || 
					 ((abs(cos(hiShower->theta())) < 0.92) &&
					  (abs(cos(hiShower->theta())) > 0.86) && (hiShower->energy() > 0.050))))) continue;
		HepLorentzVector p1 = (*iPi01)->hiPfit()+(*iPi01)->loPfit();
		for(EvtRecPi0Col::iterator iPi02 = iPi01+1      ; iPi02 != evtRecPi0Col->end()  ; iPi02++){
			if(iPi01==iPi02) continue;
			if ((*iPi02)->chisq() >100 ) continue; 
			if (((*iPi02)->unconMass() > 0.110) || ((*iPi02)->unconMass() < 0.150))continue;
			EvtRecTrack* lo2 = const_cast<EvtRecTrack*>((*iPi02)->loEnGamma()); 
			if(lo2 == lo1) continue; 
			if(lo2 == hi1) continue; 
			RecEmcShower* loShower = lo2->emcShower();
			if (!((loShower->energy() > 0.025) && (loShower->time() >= 0) && (loShower->time() <= 14) &&
						(((abs(cos(loShower->theta())) < 0.80) && (loShower->energy() > 0.025)) || 
						 ((abs(cos(loShower->theta())) < 0.92) &&
						  (abs(cos(loShower->theta())) > 0.86) && (loShower->energy() > 0.050))))) continue;
			EvtRecTrack* hi2 = const_cast<EvtRecTrack*>((*iPi02)->hiEnGamma()); 
			if(hi2 == lo1) continue; 
			if(hi2 == hi1) continue; 
			RecEmcShower* hiShower = hi2->emcShower();
			if (!((hiShower->energy() > 0.025) && (hiShower->time() >= 0) && (hiShower->time() <= 14) &&
						(((abs(cos(hiShower->theta())) < 0.80) && (hiShower->energy() > 0.025)) || 
						 ((abs(cos(hiShower->theta())) < 0.92) &&
						  (abs(cos(hiShower->theta())) > 0.86) && (hiShower->energy() > 0.050))))) continue;
			HepLorentzVector p2 = (*iPi02)->hiPfit()+(*iPi02)->loPfit();

			double mjpsi = (pcm-p1-p2).m();
			if (fabs(mjpsi - 3.096916) < fabs(jpsiPiPiRecoil))
				jpsiPiPiRecoil = mjpsi - 3.096916;
		}
	}

	// put information in the tree
	fillDouble("JPsiPi0Pi0Recoil", jpsiPiPiRecoil);
}


// ********************************************************************
//    TRY TO TAG PSI(2S) --> PI+ PI- JPSI AND GAMMA GAMMA JPSI
// ********************************************************************

void
NTupleHelper::fillJPsiFinder(SmartDataPtr<EvtRecTrackCol> evtRecTrackCol){

	HepLorentzVector pcm(p4psi);

	// look for psi --> pi+ pi- J/psi

	double jpsiPiPiRecoil = -10000.0;
	for(EvtRecTrackIterator iTrk1 = evtRecTrackCol->begin();
			iTrk1 != evtRecTrackCol->end(); iTrk1++){ 
		if((*iTrk1)->isMdcKalTrackValid()){
			RecMdcKalTrack* mdcKalTrack1 = (*iTrk1)->mdcKalTrack();
			mdcKalTrack1->setPidType(RecMdcKalTrack::pion);
			for(EvtRecTrackIterator iTrk2 = iTrk1;
					iTrk2 != evtRecTrackCol->end(); iTrk2++){ 
				if((*iTrk2)->isMdcKalTrackValid() && 
						(*iTrk2)->trackId() != (*iTrk1)->trackId()){
					RecMdcKalTrack* mdcKalTrack2 = (*iTrk2)->mdcKalTrack();
					if (mdcKalTrack1->charge() == mdcKalTrack2->charge()) continue;
					mdcKalTrack2->setPidType(RecMdcKalTrack::pion);
					HepLorentzVector p1 = mdcKalTrack1->p4(0.139570);
					HepLorentzVector p2 = mdcKalTrack2->p4(0.139570);
					double mjpsi = (pcm-p1-p2).m();
					if (fabs(mjpsi - 3.096916) < fabs(jpsiPiPiRecoil))
						jpsiPiPiRecoil = mjpsi - 3.096916;
				}
			}
		}
	}

	// look for psi --> gamma gamma J/psi

	double jpsiGGRecoil = -10000.0;
	for(EvtRecTrackIterator iG1 = evtRecTrackCol->begin();
			iG1 != evtRecTrackCol->end(); iG1++){ 
		if((*iG1)->isEmcShowerValid()){
			RecEmcShower* sh1 = (*iG1)->emcShower();
			for(EvtRecTrackIterator iG2 = iG1;
					iG2 != evtRecTrackCol->end(); iG2++){ 
				if((*iG2)->isEmcShowerValid() &&
						(*iG2)->emcShower()->cellId() != (*iG1)->emcShower()->cellId()){
					RecEmcShower* sh2 = (*iG2)->emcShower();
					HepLorentzVector p1(sh1->energy()*sin(sh1->theta())*cos(sh1->phi()), 
							sh1->energy()*sin(sh1->theta())*sin(sh1->phi()), 
							sh1->energy()*cos(sh1->theta()),
							sh1->energy());
					HepLorentzVector p2(sh2->energy()*sin(sh2->theta())*cos(sh2->phi()), 
							sh2->energy()*sin(sh2->theta())*sin(sh2->phi()), 
							sh2->energy()*cos(sh2->theta()),
							sh2->energy());
					double mjpsi = (pcm-p1-p2).m();
					if (fabs(mjpsi - 3.096916) < fabs(jpsiGGRecoil))
						jpsiGGRecoil = mjpsi - 3.096916;
				}
			}
		}
	}

	// put information in the tree
	fillDouble("JPsiPiPiRecoil", jpsiPiPiRecoil);
	fillDouble("JPsiGGRecoil"  ,   jpsiGGRecoil);
}
// ********************************************************************
//    MC TRUTH INFORMATION
// ********************************************************************
void
NTupleHelper::fillMCTruth(MCTruthHelper* mc, FSInfo* fs, int RootID, string tag){
	fillDouble("MCDecayCode1",       mc->MCDecayCode1()     );
	fillDouble("MCDecayCode2",       mc->MCDecayCode2()     );
	fillDouble("MCDecayCode3",       mc->MCDecayCode3()     );
	fillDouble("MCDecayCode4",       mc->MCDecayCode4()     );
	fillDouble("MCExtras",           mc->MCExtras()         );
	fillDouble("MCTotalEnergy",      mc->MCTotalEnergy()    );
	fillDouble("MCChicProduction",   mc->MCChicProduction() );
	fillDouble("MCJPsiProduction",   mc->MCJPsiProduction() );
	fillDouble("MCHcProduction",     mc->MCHcProduction()   );
	fillDouble("MCEtacProduction",   mc->MCEtacProduction() );
	fillDouble("MCEtaDecay",         mc->MCEtaDecay()       );
	fillDouble("MCEtaprimeDecay",    mc->MCEtaprimeDecay()  );
	fillDouble("MCPhiDecay",         mc->MCPhiDecay()       );
	fillDouble("MCOmegaDecay",       mc->MCOmegaDecay()     );
	fillDouble("MCKsDecay",          mc->MCKsDecay()        );
	fillDouble("MCFSRGamma",         mc->MCFSRGamma()       );
	fillDouble("MCDecayParticle1",   mc->MCDecayParticle(0) );
	fillDouble("MCDecayParticle2",   mc->MCDecayParticle(1) );
	fillDouble("MCDecayParticle3",   mc->MCDecayParticle(2) );
	fillDouble("MCDecayParticle4",   mc->MCDecayParticle(3) );
	fillDouble("MCDecayParticle5",   mc->MCDecayParticle(4) );
	fillDouble("MCDecayParticle6",   mc->MCDecayParticle(5) );
	//
	vector<McParticle*> mcPList    = mc->MCParticleList();
	//mc->printInformation(RootID);
	//printf("No. of MC particles is %5d\n",mcPList.size() );
	if (fs && fs->exclusive()){
		int    m_numParticle=0;
		double mc_pdgid[100];
		double mc_px[100],mc_py[100],mc_pz[100],mc_pe[100];
		vector <HepLorentzVector> mcp4list; mcp4list.clear();
		int D0Mode=-1, D0bMode=-1, DpMode=-1, DmMode=-1, DspMode=-1, DsmMode=-1;
		for (int i=0; i < mcPList.size(); i++){
			int pdgid   = mcPList[i]->particleProperty();
			if( pdgid== 411 ) DpMode   = mc->MCDTMode (mcPList[i]);
			if( pdgid==-411 ) DmMode   = mc->MCDTMode (mcPList[i]);
			if( pdgid== 421 ) D0Mode   = mc->MCDTMode (mcPList[i]);
			if( pdgid==-421 ) D0bMode  = mc->MCDTMode (mcPList[i]);
			if( pdgid== 431 ) DsmMode  = mc->MCDTMode (mcPList[i]);
			if( pdgid==-431 ) DspMode  = mc->MCDTMode (mcPList[i]);
			//
			HepLorentzVector p4p     =  (mcPList[i])->initialFourMomentum();
			mcp4list.push_back(p4p);
			mc_pdgid[m_numParticle]  = pdgid;
			mc_px [m_numParticle]    = p4p.x();
			mc_py [m_numParticle]    = p4p.y();
			mc_pz [m_numParticle]    = p4p.z();
			mc_pe [m_numParticle]    = p4p.t();
			m_numParticle += 1;
			if(m_numParticle>100 )
			{
				cout<<"m_numParticle >  100: "<<m_numParticle<<endl;
				break;
			}
		}// end of mc particle loop
		//
		if (  
				(fs->decayCode1() == mc->MCDecayCode1()) && 
				(fs->decayCode2() == mc->MCDecayCode2()) &&
				(fs->decayCode3() == mc->MCDecayCode3()) &&
				(fs->decayCode4() == mc->MCDecayCode4()) &&
				(mc->MCExtras() == 0)){
			fillDouble("MCSignal",1.0);
		}else{ 
			fillDouble("MCSignal",0.0);
		}
		//
		if( mcp4list.size()>1){
			char index[30];
			for(int ki=0; ki<mcp4list.size()-1; ki++){
				for(int kj=ki+1; kj<mcp4list.size(); kj++){
					sprintf(index ,"MCMass%d%d",ki+1,kj+1);
					fillDouble((string)index,(mcp4list[ki]+mcp4list[kj]).m());
				}
			}
		}
		if( mcp4list.size()>2){
			char index[30];
			for(int ki=0; ki<mcp4list.size()-2; ki++){
				for(int kj=ki+1; kj<mcp4list.size()-1; kj++){
					for(int kk=kj+1; kk<mcp4list.size(); kk++){
						sprintf(index ,"MCMass%d%d%d",ki+1,kj+1,kk+1);
						fillDouble((string)index,(mcp4list[ki]+mcp4list[kj]+mcp4list[kk]).m());
					}
				}
			}
		}
		fillDouble("TagModeDp" , DpMode  );
		fillDouble("TagModeDm" , DmMode  );
		fillDouble("TagModeD0" , D0Mode  );
		fillDouble("TagModeD0b", D0bMode );
		fillDouble("TagModeDsp", DspMode );
		fillDouble("TagModeDsm", DsmMode );
		fillArray ("pdgid"     , "indexmc", (double*)mc_pdgid ,  m_numParticle);
		fillArray ("mc_Px"     , "indexmc", (double*)mc_px    ,  m_numParticle);
		fillArray ("mc_Py"     , "indexmc", (double*)mc_py    ,  m_numParticle);
		fillArray ("mc_Pz"     , "indexmc", (double*)mc_pz    ,  m_numParticle);
		fillArray ("mc_En"     , "indexmc", (double*)mc_pe    ,  m_numParticle);
	}
}

void 
NTupleHelper::fillMCTruthDT(MCTruthHelper* mc, FSInfo* fs, int RootID ){
	//printf("\n\n"); 
	if (fs){
		vector<McParticle*> mcPList    = mc->allMCParticleList();
		vector<McParticle*> mcDList    = mc->MCParticleList();
		//
		int  rootIndex  = -1, m_numParticle=0;
		bool psiDecay   = false;
		bool strange    = false;
		double mc_pdgid[100], mc_motheridx[100], mc_trkidx[100];
		double mc_px[100], mc_py[100], mc_pz[100], mc_pe[100];
		int ISRTag =  1;
		int D0Mode = -1, D0bMode=-1, DpMode=-1, DmMode=-1, DspMode=-1, DsmMode=-1;
		for (int i=0; i < mcPList.size(); i++)
		{
			if (            mcPList[i]->primaryParticle()      &&
					mcPList[i]->particleProperty()==11 &&
					mcPList[i]->mother().particleProperty()==11 ) strange = true;
			if (            mcPList[i]->primaryParticle()    ) continue;
			if (           !mcPList[i]->decayFromGenerator() ) continue;
			int pdgid   =   mcPList[i]->particleProperty();
			int trkidx  =   mcPList[i]->trackIndex();
			int mthidx  =  (mcPList[i]->mother()).trackIndex();
			int mother  =  (mcPList[i]->mother()).particleProperty();
			if (pdgid == -22                      ) continue;
			if (pdgid ==  22     && mother == 111 ) continue;
			if (abs(pdgid)== 11  && mother == 111 ) continue;
			if (pdgid ==  22     && mother == 221 ) continue;
			//printf("No. %3d %3d, pdgid = %8d, mother = %8d, mass=%9.4f\n", 
			//i, mthidx,pdgid,mother,((mcPList[i])->initialFourMomentum()).m());
			if ( pdgid == RootID || pdgid == 23 )
			{ 
				psiDecay  = true;
				rootIndex = mcPList[i]->trackIndex();
			}
			if (!psiDecay)                   continue;
			//int midx               = mthidx - rootIndex;
			int midx               = mthidx;
			HepLorentzVector p4p   = mcPList[i]->initialFourMomentum();
			//printf("No. %3d %3d, pdgid = %8d, mother = %8d, midx=%8d, mass=%9.4f\n", 
			//i, mthidx,pdgid,mother,midx,((allmcPList[i])->initialFourMomentum()).m());
			//if ( strange && mother!=RootID ) midx--;
			//
			if( pdgid== 411 ) DpMode  = mc->MCDTMode (mcPList[i]);
			if( pdgid==-411 ) DmMode  = mc->MCDTMode (mcPList[i]);
			if( pdgid== 421 ) D0Mode  = mc->MCDTMode (mcPList[i]);
			if( pdgid==-421 ) D0bMode = mc->MCDTMode (mcPList[i]);
			if( pdgid== 431 ) DsmMode = mc->MCDTMode (mcPList[i]);
			if( pdgid==-431 ) DspMode = mc->MCDTMode (mcPList[i]);
			mc_motheridx[m_numParticle] = midx   ;
			mc_trkidx   [m_numParticle] = trkidx ;
			mc_pdgid    [m_numParticle] = pdgid  ;
			mc_px       [m_numParticle] = p4p.x();
			mc_py       [m_numParticle] = p4p.y();
			mc_pz       [m_numParticle] = p4p.z();
			mc_pe       [m_numParticle] = p4p.t();
			m_numParticle++;
			if(m_numParticle>100 )
			{
				cout<<"m_numParticle >  100: "<<m_numParticle<<endl;
				break;
			}
		}// end of mc particle loop
		//
		int np=fs->nFSParticles();
		if (  (              np == mcDList.size()    ) && 
				(fs->decayCode1() == mc->MCDecayCode1()) && 
				(fs->decayCode2() == mc->MCDecayCode2()) &&
				(fs->decayCode3() == mc->MCDecayCode3()) &&
				(fs->decayCode4() == mc->MCDecayCode4()) &&
				(mc->MCExtras() == 0))
		{
			fillDouble("MCSignal",1.0);
			vector <HepLorentzVector> mcp4list; mcp4list.clear();
			for (int i=0; i < np; i++){
				mcp4list.push_back((mcDList[i])->initialFourMomentum());
			}
			if( np>1){
				char index[30];
				for(int ki=0; ki<np-1; ki++){
					for(int kj=ki+1; kj<np; kj++){
						sprintf(index ,"MCMass%d%d",ki+1,kj+1);
						fillDouble((string)index,(mcp4list[ki]+mcp4list[kj]).m());
					}
				}
			}
			if( np>2 ){
				char index[30];
				for(int ki=0; ki<np-2; ki++){
					for(int kj=ki+1; kj<np-1; kj++){
						for(int kk=kj+1; kk<np; kk++){
							sprintf(index ,"MCMass%d%d%d",ki+1,kj+1,kk+1);
							fillDouble((string)index,(mcp4list[ki]+mcp4list[kj]+mcp4list[kk]).m());
						}
					}
				}
			}
		}else{ 
			fillDouble("MCSignal",0.0);
			if( np>1){
				char index[30];
				for(int ki=0; ki<np-1; ki++){
					for(int kj=ki+1; kj<np; kj++){
						sprintf(index ,"MCMass%d%d",ki+1,kj+1);
						fillDouble((string)index,0.0);
					}
				}
			}
			if( np>2){
				char index[30];
				for(int ki=0; ki<np-2; ki++){
					for(int kj=ki+1; kj<np-1; kj++){
						for(int kk=kj+1; kk<np; kk++){
							sprintf(index ,"MCMass%d%d%d",ki+1,kj+1,kk+1);
							fillDouble((string)index,0.0);
						}
					}
				}
			}
		}
		//
		fillDouble("TagModeDp" ,  DpMode  );
		fillDouble("TagModeDm" ,  DmMode  );
		fillDouble("TagModeD0" ,  D0Mode  );
		fillDouble("TagModeD0b",  D0bMode );
		fillDouble("TagModeDsp",  DspMode );
		fillDouble("TagModeDsm",  DsmMode );
		fillArray ("pdgid"     , "indexmc", (double*)mc_pdgid     , m_numParticle);
		fillArray ("trkidx"    , "indexmc", (double*)mc_trkidx    , m_numParticle);
		fillArray ("motheridx" , "indexmc", (double*)mc_motheridx , m_numParticle);
		fillArray ("mc_Px"     , "indexmc", (double*)mc_px        , m_numParticle);
		fillArray ("mc_Py"     , "indexmc", (double*)mc_py        , m_numParticle);
		fillArray ("mc_Pz"     , "indexmc", (double*)mc_pz        , m_numParticle);
		fillArray ("mc_En"     , "indexmc", (double*)mc_pe        , m_numParticle);
	}
}
// ********************************************************************
//    HELPER FUNCTIONS
// ********************************************************************
NTupleHelper::NTupleHelper(NTuple::Tuple* Tree, HepLorentzVector p4){
	m_Tree         = Tree;
	p4psi          =   p4;
	m_bookingStage = true;
	m_doubleMap.clear();
	if( m_Tree == NULL )
		cout    << "ERROR:  null tree pointer -- "
			<< "check for duplicate final states in configuration"
			<< endl; assert( m_Tree != NULL );
}

NTupleHelper::~NTupleHelper(){
}

void
NTupleHelper::write(){
	
	for (map<string,double>::iterator mapItr = m_doubleMap.begin();
			mapItr != m_doubleMap.end(); mapItr++){
		m_ntupleDoubleMap[mapItr->first] = mapItr->second;
	}
	
	for (map<string,int>::iterator mapItr = m_longMap.begin();
			mapItr != m_longMap.end(); mapItr++){
		m_ntupleLongMap[mapItr->first] = mapItr->second;
	}
	
	for (map<string,double*>::iterator mapItr = m_arrayMap.begin();
			mapItr != m_arrayMap.end(); mapItr++){
		for(int i=0; i< 100; i++) { 
			m_ntupleArrayMap[mapItr->first][i] =  *(mapItr->second + i);
		}
	}

	m_Tree->write();

	for (map<string,double*>::iterator mapItr = m_arrayMap.begin();
			mapItr != m_arrayMap.end(); mapItr++){
		delete mapItr->second;
	}
	m_bookingStage = false;
	//cout<<mapItr->first<<" "<<sizeof(*(mapItr->second))<<endl;
	//for(int i=0; i<m_ntupleLongMap["idx_mc"]; i++) {
}


void NTupleHelper::fillDouble(string name, double value){
	if (m_bookingStage && !containsEntry(name)){
		m_Tree->addItem(name,m_ntupleDoubleMap[name]);
	}
	if (!m_bookingStage && !containsEntry(name)){
		cout << "NTUPLEHELPER:  Variable " << name << " has not been booked." << endl;
		exit(0);
	}
	m_doubleMap[name] = value;
}

void NTupleHelper::fillLong(string name, int value){
	if (m_bookingStage && !containsEntry(name)){
		m_Tree->addItem(name,m_ntupleLongMap[name]);
	}
	if (!m_bookingStage && !containsEntry(name)){
		cout << "NTUPLEHELPER:  Variable " << name << " has not been booked." << endl;
		exit(0);
	}
	m_longMap[name] = value;
}



void 
NTupleHelper::fillArray(string name, string index_name, double* value, int size){
	
	if (m_bookingStage && !containsEntry(index_name)){
		m_Tree->addItem(index_name, m_ntupleLongMap[index_name], 0, 100);
	}
	
	m_longMap[index_name]=size;

	if (m_bookingStage && !containsEntry(name)){
		m_Tree->addIndexedItem(name, m_ntupleLongMap[index_name], m_ntupleArrayMap[name]);
	}
	
	if (!m_bookingStage && !containsEntry(name)){
		cout << "NTUPLEHELPER:  Variable " << name << " has not been booked." << endl;
		exit(0);
	}
	
	if (!m_bookingStage && !containsEntry(index_name)){
		cout << "NTUPLEHELPER:  Variable " << index_name << " has not been booked." << endl;
		exit(0);
	}

	m_arrayMap[name]= new double[100];
	for(int i=0; i<size; i++){
		//printf("value %2d = %10f\n", i, *(value+i));
		m_arrayMap[name][i] = *(value+i);
	}
}

void 
NTupleHelper::fillArray(string name, string index_name, vector<double> value, int size){
	
	if (m_bookingStage && !containsEntry(index_name)){
		m_Tree->addItem(index_name, m_ntupleLongMap[index_name], 0, 100);
	}
	
	m_longMap[index_name]=size;

	if (m_bookingStage && !containsEntry(name)){
		m_Tree->addIndexedItem(name, m_ntupleLongMap[index_name], m_ntupleArrayMap[name]);
	}
	
	if (!m_bookingStage && !containsEntry(name)){
		cout << "NTUPLEHELPER:  Variable " << name << " has not been booked." << endl;
		exit(0);
	}
	
	if (!m_bookingStage && !containsEntry(index_name)){
		cout << "NTUPLEHELPER:  Variable " << index_name << " has not been booked." << endl;
		exit(0);
	}

	m_arrayMap[name]= new double[100];
	for(int i=0; i<size; i++){
		m_arrayMap[name][i] = value[i];
	}
}




bool
NTupleHelper::containsEntry(string name){

	map<string,double>::iterator mapItr1 = m_doubleMap.find(name);
	if (mapItr1 != m_doubleMap.end()) return true;
	
	map<string,int>::iterator mapItr2 = m_longMap.find(name);
	if (mapItr2 != m_longMap.end()) return true;
	
	map<string,double*>::iterator mapItr3 = m_arrayMap.find(name);
	if (mapItr3 != m_arrayMap.end()) return true;
	
	return false;
}

string 
NTupleHelper::concatName(string tag, string base, int index){
	stringstream name;
	name << tag;
	name << base;
	name << "P";
	name << index;
	return name.str();
}

string 
NTupleHelper::concatName(string tag, string base){
	stringstream name;
	name << tag;
	name << base;
	return name.str();
}


