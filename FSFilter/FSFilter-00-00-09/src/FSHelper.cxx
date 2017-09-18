#include "FSFilter/FSHelper.h"
//**********************************************
//
//   Missing particle
//
//**********************************************
FSParticle::FSParticle(string name, bool missed):
	m_track(NULL), m_shower(NULL), m_pi0(NULL), m_eta(NULL), 
	m_vee(NULL), m_dmes(NULL), m_name(name), m_missed(missed){
		m_vtxfit  = false;
		m_mass = Mass(m_name);
		m_rawFourMomentum = HepLorentzVector(0,0,0,0);
	}
//**********************************************
//
//   TRACK
//
//**********************************************
FSParticle::FSParticle(EvtRecTrack* tk, string name, bool yuping):
	m_track(tk), m_shower(NULL), m_pi0(NULL), m_eta(NULL), 
	m_vee(NULL), m_dmes(NULL), m_name(name){
		
		m_missed=false;
		m_vtxfit  = false;
		// set mass
		m_mass = Mass(m_name);

		// get kalman track
		m_kalTrack = m_track->mdcKalTrack();

		// set pid type (setPidType is static for some reason)
		if      ((name == "pi-") ||(name == "pi+"))  m_kalTrack->setPidType(RecMdcKalTrack::pion);
		else if ((name == "K-")  ||(name == "K+" ))  m_kalTrack->setPidType(RecMdcKalTrack::kaon);
		else if ((name == "p-")  ||(name == "p+" ))  m_kalTrack->setPidType(RecMdcKalTrack::proton);
		else if ((name == "e-")  ||(name == "e+" ))  m_kalTrack->setPidType(RecMdcKalTrack::electron);
		else if ((name == "mu-") ||(name == "mu+"))  m_kalTrack->setPidType(RecMdcKalTrack::muon);

		// setup for wtrack
		if      ((name == "pi-") || (name == "pi+"))
			m_initialWTrack = WTrackParameter(m_mass, m_kalTrack->getZHelix(), m_kalTrack->getZError());
		else if ((name == "K-")  || (name == "K+"))
			m_initialWTrack = WTrackParameter(m_mass, m_kalTrack->getZHelixK(), m_kalTrack->getZErrorK());
		else if ((name == "p-")  || (name == "p+"))
			m_initialWTrack = WTrackParameter(m_mass, m_kalTrack->getZHelixP(), m_kalTrack->getZErrorP());
		else if ((name == "e-")  || (name == "e+"))
			m_initialWTrack = WTrackParameter(m_mass, m_kalTrack->getZHelixE(), m_kalTrack->getZErrorE());
		else if ((name == "mu-") || (name == "mu+"))
			m_initialWTrack = WTrackParameter(m_mass, m_kalTrack->getZHelixMu(), m_kalTrack->getZErrorMu());

		// YUPING recalibration of tracking errors
		if (yuping){
			HepVector wpip_zHel(5,0);
			if      ((name == "pi-") || (name == "pi+")){
				YUPING::calibration(m_kalTrack, wpip_zHel, 0);
				m_initialWTrack = WTrackParameter(m_mass, wpip_zHel, m_kalTrack->getZError());
			}
			else if ((name == "K-")  || (name == "K+")){
				YUPING::calibration(m_kalTrack, wpip_zHel, 1);
				m_initialWTrack = WTrackParameter(m_mass, wpip_zHel, m_kalTrack->getZError());
			}
		}

		// initial four-momentum
		m_rawFourMomentum = m_kalTrack->p4(m_mass);
		// keep track of id's
		m_trackId.push_back(tk->trackId());
	}
//**********************************************
//
//   SHOWER
//
//**********************************************
FSParticle::FSParticle(RecEmcShower* sh, string name):
	m_track(NULL), m_shower(sh), m_pi0(NULL), m_eta(NULL), 
	m_vee(NULL), m_dmes(NULL), m_name(name){
		m_missed=false;
		m_vtxfit  = false;
		m_mass = Mass(m_name);
		m_rawFourMomentum = fourMomentum(sh);
		m_showerId.push_back(sh->cellId());
	}
//**********************************************
//
//   PI0
//
//**********************************************
FSParticle::FSParticle(EvtRecPi0* pi0, string name):
	m_track(NULL), m_shower(NULL), m_pi0(pi0), m_eta(NULL),  
	m_vee(NULL), m_dmes(NULL), m_name(name){
		
		m_missed=false;
		m_vtxfit  = false;
		m_mass = Mass(m_name);
		EvtRecTrack* lo = const_cast<EvtRecTrack*>(pi0->loEnGamma()); 
		EvtRecTrack* hi = const_cast<EvtRecTrack*>(pi0->hiEnGamma()); 
		m_pi0Lo = lo->emcShower();
		m_pi0Hi = hi->emcShower();
		//m_rawFourMomentum = fourMomentum(m_pi0Lo) + fourMomentum(m_pi0Hi);
		m_rawFourMomentum = pi0->hiPfit()+pi0->loPfit(); 
		m_showerId.push_back(m_pi0Lo->cellId());
		m_showerId.push_back(m_pi0Hi->cellId());

	}
//**********************************************
//
//   ETA
//
//**********************************************
FSParticle::FSParticle(EvtRecEtaToGG* eta, string name):
	m_track(NULL), m_shower(NULL), m_pi0(NULL), m_eta(eta),  
	m_vee(NULL), m_dmes(NULL),  m_name(name){

		m_missed=false;
		m_vtxfit  = false;
		m_mass = Mass(m_name);
		EvtRecTrack* lo = const_cast<EvtRecTrack*>(eta->loEnGamma()); 
		EvtRecTrack* hi = const_cast<EvtRecTrack*>(eta->hiEnGamma()); 
		m_etaLo = lo->emcShower();
		m_etaHi = hi->emcShower();
		//m_rawFourMomentum = fourMomentum(m_etaLo) + fourMomentum(m_etaHi);
		m_rawFourMomentum = eta->hiPfit()+eta->loPfit(); 
		m_showerId.push_back(m_etaLo->cellId());
		m_showerId.push_back(m_etaHi->cellId());

	}
//**********************************************
//
//   KSHORT AND LAMBDA
//
//**********************************************
FSParticle::FSParticle(EvtRecVeeVertex* vee, string name):
	m_track(NULL), m_shower(NULL), m_pi0(NULL), m_eta(NULL), 
	m_vee(vee), m_dmes(NULL), m_name(name){

		m_missed=false;
		m_vtxfit  = false;
		m_mass = Mass(m_name);

		double mass1 = 0.0;
		double mass2 = 0.0;

		if (name == "Ks"){
			mass1 = Mass("pi+"); mass2 = Mass("pi-");
		}
		if (name == "Lambda"){
			mass1 = Mass("p+");  mass2 = Mass("pi-");
		}
		if (name == "ALambda"){
			mass1 = Mass("p-");  mass2 = Mass("pi+");
		}

		// what is the particle order??

		bool rightorder = true;
		if (name == "Ks"      && vee->pairDaughters().first->mdcKalTrack()->charge() < 0) rightorder = false;
		if (name == "Lambda"  && vee->pairDaughters().first->mdcKalTrack()->charge() < 0) rightorder = false;
		if (name == "ALambda" && vee->pairDaughters().first->mdcKalTrack()->charge() > 0) rightorder = false;

		// now store information for the first and second particles

		if (rightorder)  m_veeTrack1 = vee->pairDaughters().first;
		if (!rightorder) m_veeTrack1 = vee->pairDaughters().second;
		m_veeKalTrack1 = m_veeTrack1->mdcKalTrack();
		if (name == "Ks"){ m_veeInitialWTrack1 = WTrackParameter(mass1, m_veeKalTrack1->getZHelix() , m_veeKalTrack1->getZError()) ; }
		else             { m_veeInitialWTrack1 = WTrackParameter(mass1, m_veeKalTrack1->getZHelixP(), m_veeKalTrack1->getZErrorP()); }

		if ( rightorder) m_veeTrack2 = vee->pairDaughters().second;
		if (!rightorder) m_veeTrack2 = vee->pairDaughters().first;
		m_veeKalTrack2 = m_veeTrack2->mdcKalTrack();
		m_veeInitialWTrack2 = WTrackParameter(mass2, m_veeKalTrack2->getZHelix(), m_veeKalTrack2->getZError());

		//m_rawFourMomentum = HepLorentzVector(vee->w()[0], vee->w()[1], vee->w()[2], vee->w()[3]);
		setRawFourMomentum (m_veeInitialWTrack1.p() + m_veeInitialWTrack2.p() );
		m_trackId.push_back(m_veeTrack1->trackId());
		m_trackId.push_back(m_veeTrack2->trackId());

	}
//**********************************************
//
//   D Family 
//
//**********************************************
FSParticle::FSParticle(EvtRecDTag* dmes, string name, int nk):
	m_track(NULL), m_shower(NULL), m_pi0(NULL), m_eta(NULL), 
	m_vee(NULL), m_dmes(dmes), m_name(name)
{
	m_missed  = false;
	m_vtxfit  = false;
	m_mass    = Mass(m_name);
	int ntracks=0, nshowers=0;
	//
	m_trackId             . clear() ;            
	m_showerId            . clear() ;
	m_dmesTrack           . clear() ;           
	m_dmesKalTrack        . clear() ;        
	m_dmesInitialWTrack   . clear() ;   
	m_dmesVertexFitWTracks. clear() ; 
	m_dmesVertexFitWTrack . clear() ; 
	m_dmesShowers         . clear() ;   
	//	
	m_dmesTagmode         = dmes->decayMode();
	m_dmesCharge          = dmes->charge   ();
	m_dmesMass            = dmes->mass     ();
	m_dmesCharm           = dmes->charm    ();
	m_rawFourMomentum     = dmes->p4       ();
	m_dmesnKs             = nk/10000 ;
	nk                    = nk%10000 ;
	ntracks               = nk/1000  ;
	nk                    = nk%1000  ;
	nshowers              = nk/100   ;
	nk                    = nk%100   ;
	//
	SmartRefVector<EvtRecTrack> tracks  = dmes-> tracks();
	SmartRefVector<EvtRecTrack> showers = dmes->showers();
	if( ntracks != tracks.size() ) {
		printf("Number of tracks  of D is inconsistent %2d vs. %2d of %3d\n",ntracks ,(int)tracks .size(),m_dmesTagmode);
		exit(1);
	}
	if( nshowers != showers.size() ) {
		printf("Number of showers of D is inconsistent %2d vs. %2d of %3d\n",nshowers,(int)showers.size(),m_dmesTagmode);
		exit(1);
	}
	m_dmesTkFourMomentum = HepLorentzVector(0,0,0,0);
	int idep=nk/10, ifin=nk/10+nk%10; 
	for(int is=0; is<tracks.size(); is++){
		int itrk = tracks[is]->trackId();
		RecMdcKalTrack * tmpTrk= tracks[is]->mdcKalTrack();
		int iPID= 2;
		double tmass=Mass("pi+");
		if(nk>0 && is+1>=idep && is+1<ifin)
		{
			tmass=Mass("K+");
			iPID=3;	
		}
		if  (iPID==2) tmpTrk->setPidType(RecMdcKalTrack::pion);
		else          tmpTrk->setPidType(RecMdcKalTrack::kaon);
		if  (iPID==2) m_dmesInitialWTrack.push_back(WTrackParameter(tmass,tmpTrk->getZHelix() ,tmpTrk->getZError()) );
		else          m_dmesInitialWTrack.push_back(WTrackParameter(tmass,tmpTrk->getZHelixK(),tmpTrk->getZErrorK()));
		m_dmesTkFourMomentum += (tmpTrk->p4(tmass)); 
		m_dmesTrack . push_back(tracks[is]);
		m_trackId   . push_back(itrk);
	}
	//
	m_dmesShFourMomentum = HepLorentzVector(0,0,0,0);
	for(int is=0; is<showers.size(); is++){
		RecEmcShower * tmpTrk= showers[is]->emcShower();
		m_dmesShowers . push_back(tmpTrk);
		m_showerId    . push_back(tmpTrk->cellId());
		m_dmesShFourMomentum += fourMomentum(tmpTrk); 
	}
	//
	m_dmesNTracks     = m_dmesInitialWTrack.size();
	m_dmesNShowers    = m_dmesShowers.size();
	m_intFourMomentum = m_dmesShFourMomentum;
	//
	for(int iw=0; iw<m_dmesnKs; iw++){
		m_dmesLSigma[iw]=-999;
	}
	//printf("mass = %9.5f %9.5f\n", m_dmesMass, (m_dmesShFourMomentum+m_dmesTkFourMomentum).m() );
}
//**********************************************
//
//   Charmonium Family 
//
//**********************************************
// to appear here ... 
//
//
//**********************************************
//**********************************************
//**********************************************
FSParticle::~FSParticle()
{
	FreeAll(m_trackId             );            
	FreeAll(m_showerId            );
	FreeAll(m_dmesTrack           );           
	FreeAll(m_dmesKalTrack        );        
	FreeAll(m_dmesInitialWTrack   );   
	FreeAll(m_dmesVertexFitWTracks); 
	FreeAll(m_dmesVertexFitWTrack ); 
	FreeAll(m_dmesShowers         );   
}

void FSParticle::dmesClear(){
	FreeAll(m_dmesVertexFitWTracks); 
	FreeAll(m_dmesVertexFitWTrack ); 
}

int  FSParticle::dmesKsCut(double LCut){
	if(m_dmesnKs==0) return 1;
	for(int i=0; i<m_dmesnKs; i++){
            if(m_dmesLSigma[i]<LCut) return 0;
	}
	return 1;
}

void FSParticle::setdmesVertexFitWTracks(const vector<WTrackParameter>  wtracks ){
	for(int iw=0; iw<wtracks.size(); iw++){
		m_dmesVertexFitWTracks.push_back(wtracks[iw]);
		m_intFourMomentum += wtracks[iw].p(); // only for charged tracks, the neutral should be added later 
	}
}

void FSParticle::setdmesVertexFitWTrack(const vector<WTrackParameter>  wtracks ){
	for(int iw=0; iw<wtracks.size(); iw++){
		m_dmesVertexFitWTrack.push_back(wtracks[iw]);
	}
}

void FSParticle::setdmesLSigma(const vector<double> dmesLSigma){
	for(int iw=0; iw<dmesLSigma.size(); iw++){
		m_dmesLSigma[iw]=dmesLSigma[iw];
	}
}


//**********************************************
//
//   UTILITY FUNCTIONS
//
//**********************************************
HepLorentzVector
FSParticle::fourMomentum( RecEmcShower* sh ){
	return HepLorentzVector(
			sh->energy()*sin(sh->theta())*cos(sh->phi()),
			sh->energy()*sin(sh->theta())*sin(sh->phi()),
			sh->energy()*cos(sh->theta()),
			sh->energy());
}

bool
FSParticle::duplicate(FSParticle* fsp){

	vector<int> trackId2 = fsp->trackId();
	if (m_trackId.size() > 0 && trackId2.size() > 0){
		for (unsigned int i = 0; i < m_trackId.size(); i++){
			for (unsigned int j = 0; j < trackId2.size(); j++){
				if (m_trackId[i] == trackId2[j]) return true;
			}
		}
		if ( name() == fsp->name() && m_trackId[0] > trackId2[0]) return true;
	}

	vector<int> showerId2 = fsp->showerId();
	if (m_showerId.size() > 0 && showerId2.size() > 0){
		for (unsigned int i = 0; i < m_showerId.size(); i++){
			for (unsigned int j = 0; j < showerId2.size(); j++){
				if (m_showerId[i] == showerId2[j]) return true;
			}
		}
		if ( name() == fsp->name() && m_showerId[0] > showerId2[0]) return true;
	}

	return false;
}

void 
FSParticle::PrintTrackAndShowers(){
	cout<<" Tracks: "; 
	for(int i=0; i<m_trackId .size(); i++) cout<<m_trackId [i]<<", "; 
	cout<<";Showers "; 
	for(int i=0; i<m_showerId.size(); i++) cout<<m_showerId[i]<<", "; 
	cout<<endl; 
}

//**********************************************
//
//   PARSE FINAL STATE INFORMATION
//
//**********************************************
FSInfo::FSInfo(string FSName, NTupleHelper* nt, NTupleHelper* ntgen){
	m_FSName            = FSName;
	m_NT                = nt;
	m_NTGen             = ntgen;
	m_nMissingParticles = 0;
	m_Constrain4Mom     = 1;
	m_FSMaCs.clear();
	m_FSCuts.clear();

	cout << "\t\t"<< endl;
	cout << "FSFilter:  Initializing Final State " << FSName << endl;

	m_missedParticle = "";
	string singleParticles[28] = {
		"pi0"    ,
		"pi-"    ,
		"pi+"    ,
		"Ks"     ,
		"K-"     ,
		"K+"     ,
		"gamma"  ,
		//
		"eta"    ,
		"p-"     ,
		"p+"     ,
		"mu-"    ,
		"mu+"    ,
		"e-"     ,
		"e+"     ,
		"ALambda",
		"Lambda" ,
		//
		"D0bar"  ,
		"D0"     ,
		"D-"     ,
		"D+"     ,
		"Ds-"    , 
		"Ds+"    ,
		//	
		"J/psi"  , 
		"chi_c1" , 
		"h_c"    , 
		"psi(2S)", 
		"nu"     ,
		"n0" 
	};
	//
	int index = 0, idash=0;
	vector<string> particleNamesTmp;
	vector<int>    particleStatusTmp;
	for (int i = m_FSName.size()-1; i >= 0 && index < 28; i--){
		string digit = m_FSName.substr(i,1);
		if (            (digit == "0") || (digit == "1") || 
				(digit == "2") || (digit == "3") || 
				(digit == "4") || (digit == "5") || 
				(digit == "6") || (digit == "7") || 
				(digit == "8") || (digit == "9")
				){
			int num = atoi(digit.c_str());
			for (int j = 0; j < num; j++){
				particleNamesTmp .push_back(singleParticles[index]);
				particleStatusTmp.push_back(1);
			}
			index++;
		}else if (digit == "M" || digit == "m" ){
			m_nMissingParticles++;
			m_missingMassFit = true; 
			particleNamesTmp .push_back(singleParticles[index]);
			particleStatusTmp.push_back(0);
			m_missedParticle = singleParticles[index];
			setMissingMass(Mass(m_missedParticle));
			index++;
		}else if (digit == "_" ){
			if( idash==0){
				index =  7;
				idash++;
			}else if (idash==1){
				index=16;
				idash++;
			}else{
				index = 22;
				idash++;
			}
		}
	}
	//
	for (int i = particleNamesTmp.size()-1; i >= 0; i--){
		m_particleNames .push_back(particleNamesTmp[i] );
		m_particleStatus.push_back(particleStatusTmp[i]);
	}
	//
	m_nChargedParticles = 0;
	m_decayCode1 = 0;
	m_decayCode2 = 0;
	m_decayCode3 = 0;
	m_decayCode4 = 0;
	for (unsigned int i = 0; i < m_particleNames.size(); i++){
		if      (m_particleNames[i] == "pi0"    ){ m_decayCode1 += 1;           if(m_particleStatus[i]!=0)m_nChargedParticles += 0; }
		else if (m_particleNames[i] == "pi-"    ){ m_decayCode1 += 10;          if(m_particleStatus[i]!=0)m_nChargedParticles += 1; }
		else if (m_particleNames[i] == "pi+"    ){ m_decayCode1 += 100;         if(m_particleStatus[i]!=0)m_nChargedParticles += 1; }
		else if (m_particleNames[i] == "Ks"     ){ m_decayCode1 += 1000;        if(m_particleStatus[i]!=0)m_nChargedParticles += 2; }
		else if (m_particleNames[i] == "K-"     ){ m_decayCode1 += 10000;       if(m_particleStatus[i]!=0)m_nChargedParticles += 1; }
		else if (m_particleNames[i] == "K+"     ){ m_decayCode1 += 100000;      if(m_particleStatus[i]!=0)m_nChargedParticles += 1; }
		else if (m_particleNames[i] == "gamma"  ){ m_decayCode1 += 1000000;     if(m_particleStatus[i]!=0)m_nChargedParticles += 0; }
		//
		else if (m_particleNames[i] == "eta"    ){ m_decayCode2 += 1;           if(m_particleStatus[i]!=0)m_nChargedParticles += 0; }
		else if (m_particleNames[i] == "p-"     ){ m_decayCode2 += 10;          if(m_particleStatus[i]!=0)m_nChargedParticles += 1; }
		else if (m_particleNames[i] == "p+"     ){ m_decayCode2 += 100;         if(m_particleStatus[i]!=0)m_nChargedParticles += 1; }
		else if (m_particleNames[i] == "mu-"    ){ m_decayCode2 += 1000;        if(m_particleStatus[i]!=0)m_nChargedParticles += 1; }
		else if (m_particleNames[i] == "mu+"    ){ m_decayCode2 += 10000;       if(m_particleStatus[i]!=0)m_nChargedParticles += 1; }
		else if (m_particleNames[i] == "e-"     ){ m_decayCode2 += 100000;      if(m_particleStatus[i]!=0)m_nChargedParticles += 1; }
		else if (m_particleNames[i] == "e+"     ){ m_decayCode2 += 1000000;     if(m_particleStatus[i]!=0)m_nChargedParticles += 1; }
		else if (m_particleNames[i] == "ALambda"){ m_decayCode2 += 10000000;    if(m_particleStatus[i]!=0)m_nChargedParticles += 2; }
		else if (m_particleNames[i] == "Lambda" ){ m_decayCode2 += 100000000;   if(m_particleStatus[i]!=0)m_nChargedParticles += 2; }
		//
		else if (m_particleNames[i] == "D0bar"  ){ m_decayCode3 += 1;           if(m_particleStatus[i]!=0)m_nChargedParticles += 6; }
		else if (m_particleNames[i] == "D0"     ){ m_decayCode3 += 10;          if(m_particleStatus[i]!=0)m_nChargedParticles += 6; }
		else if (m_particleNames[i] == "D-"     ){ m_decayCode3 += 100;         if(m_particleStatus[i]!=0)m_nChargedParticles += 5; }
		else if (m_particleNames[i] == "D+"     ){ m_decayCode3 += 1000;        if(m_particleStatus[i]!=0)m_nChargedParticles += 5; }
		else if (m_particleNames[i] == "Ds-"    ){ m_decayCode3 += 10000;       if(m_particleStatus[i]!=0)m_nChargedParticles += 5; }
		else if (m_particleNames[i] == "Ds+"    ){ m_decayCode3 += 100000;      if(m_particleStatus[i]!=0)m_nChargedParticles += 5; }
		//
		else if (m_particleNames[i] == "J/psi"  ){ m_decayCode4 += 1;           if(m_particleStatus[i]!=0)m_nChargedParticles += 0; }
		else if (m_particleNames[i] == "chi_c1" ){ m_decayCode4 += 10;          if(m_particleStatus[i]!=0)m_nChargedParticles += 0; }
		else if (m_particleNames[i] == "h_c"    ){ m_decayCode4 += 100;         if(m_particleStatus[i]!=0)m_nChargedParticles += 0; }
		else if (m_particleNames[i] == "psi(2S)"){ m_decayCode4 += 1000;        if(m_particleStatus[i]!=0)m_nChargedParticles += 0; }
		else if (m_particleNames[i] == "nu"     ){ m_decayCode4 += 10000;       if(m_particleStatus[i]!=0)m_nChargedParticles += 0; }
		else if (m_particleNames[i] == "n0"     ){ m_decayCode4 += 100000;      if(m_particleStatus[i]!=0)m_nChargedParticles += 0; }
	}
	//
	if( inclusive() )          m_Constrain4Mom=0;
	if(m_nMissingParticles>1)  m_Constrain4Mom=0;
	//
        Print();
	/*
	for (unsigned int i = 0; i < m_particleNames.size(); i++){
		cout << "FSFilter:      " << m_particleNames[i];
		if( m_particleStatus[i] ) cout << endl;
		else                      cout <<" is missing"<<endl;
	}
	*/
}

FSInfo::~FSInfo(){
	FreeAll   (  m_particleNames );
	FreeAll   (  m_particleStatus);
	FreeDelAll(  m_FSCuts        );
	FreeDelAll(  m_FSMaCs        );
	if(m_NT    ) delete m_NT   ;
	if(m_NTGen ) delete m_NTGen;
}

//**********************************************
//
//   FSCut constructor
//
//**********************************************

FSCut::FSCut(const string& initialization){


	// divide the initialization string into seperate words

	vector<string> words = FSInfo::parseString(initialization);

	if (words.size() != 5){
		cout << "FSFilter ERROR: wrong arguments to FSCut parameter: " << endl;
		cout << initialization << endl;
		exit(0);
	}

	// save input as member data

	m_FSName       = words[0];
	m_submodeName  = words[1];
	m_cutType      = words[2];
	m_lowCut  = atof(words[3].c_str());
	m_highCut = atof(words[4].c_str());


	// quick checks

	if (            m_cutType != "RawRecoil"        && m_cutType != "RawMass"        &&
			m_cutType != "IntRecoil"        && m_cutType != "IntMass"        &&
			m_cutType != "FitRecoil"        && m_cutType != "FitMass"        &&
			m_cutType != "RawRecoilSquared" && m_cutType != "RawMassSquared" &&
			m_cutType != "IntRecoilSquared" && m_cutType != "IntMassSquared" &&
			m_cutType != "FitRecoilSquared" && m_cutType != "FitMassSquared" ){
		cout << "FSFilter ERROR: wrong arguments to FSCut parameter: " << endl;
		cout << initialization << endl;
		cout << "cutType must be RawRecoil, RawMass, IntRecoil, FitRecoil, etc. " << endl;
		exit(0);
	}

}

//**********************************************
//
//   FSInfo functions to evaluate FSCuts
//
//**********************************************
vector< vector<unsigned int> >&
FSInfo::submodeIndices(const string& submodeName){

	if (m_submodeIndices.find(submodeName) != m_submodeIndices.end())
		return m_submodeIndices[submodeName];

	vector<string> submodeParticles = FSInfo::getParticleNamesFromFSName( submodeName );

	static vector< vector<unsigned int> > indices; FreeAll(indices);

	for (unsigned int i = 0; i < submodeParticles.size(); i++){

		vector< vector<unsigned int> > indicesTemp = indices;
		indices.clear();

		vector<unsigned int> pList;
		for (unsigned int j = 0; j < m_particleNames.size(); j++){
			if (submodeParticles[i] == m_particleNames[j]) pList.push_back(j);
		}
		if (pList.size() == 0) return indices;

		for (unsigned int ipl = 0; ipl < pList.size(); ipl++){
			if (i == 0){
				vector<unsigned int> combo;
				combo.push_back(pList[ipl]);
				indices.push_back(combo);
			}
			else{
				for (unsigned int itmp = 0; itmp < indicesTemp.size(); itmp++){
					vector<unsigned int> combo = indicesTemp[itmp];
					bool duplicate = false;
					for (unsigned int ic = 0; ic < combo.size(); ic++){
						if (pList[ipl] <= combo[ic]){
							duplicate = true;
							continue;
						}
					}
					if (!duplicate){
						combo.push_back(pList[ipl]);
						indices.push_back(combo);
					}
				}
			}
		}
	}

	m_submodeIndices[submodeName] = indices;
	return m_submodeIndices[submodeName];

}


bool
FSInfo::evaluateFSCuts( const vector<FSParticle*>& particleCombination,
		const HepLorentzVector& pInitial, string fourVectorType ){



	for (unsigned int icut = 0; icut < m_FSCuts.size(); icut++){
		FSCut* fscut = m_FSCuts[icut];
		bool lRaw = fscut->Raw();
		bool lInt = fscut->Int();
		bool lFit = fscut->Fit();
		if ((lRaw && fourVectorType != "Raw") ||
				(lInt && fourVectorType != "Int") ||
				(lFit && fourVectorType != "Fit")) continue;
		bool pass = false;

		vector< vector<unsigned int> > indices = submodeIndices(fscut->submodeName());

		for (unsigned int i = 0; i < indices.size(); i++){
			vector<unsigned int> indexCombo = indices[i];

			HepLorentzVector pTotal(0.0, 0.0, 0.0, 0.0);
			for (unsigned int j = 0; j < indexCombo.size(); j++){
				if (lRaw) pTotal += particleCombination[indexCombo[j]]->rawFourMomentum();
				if (lInt) pTotal += particleCombination[indexCombo[j]]->intFourMomentum();
				if (lFit) pTotal += particleCombination[indexCombo[j]]->fitFourMomentum();
			}

			if (fscut->Mass()){ 
				double x;
				if (fscut->Squared()){ x = pTotal.m2(); }
				else                 { x = pTotal.m(); }
				if (x > fscut->lowCut() && x < fscut->highCut()){ pass = true; break; }
			}

			else if (fscut->Recoil()){ 
				HepLorentzVector pMiss = pInitial - pTotal;
				double x;
				if (fscut->Squared()){ x = pMiss.m2(); }
				else                 { x = pMiss.m(); }
				if (x > fscut->lowCut() && x < fscut->highCut()){ pass = true; break; }
			}
		}


		if (!pass) return false;

	}

	return true;

}


//**********************************************
//
//   FSInfo: MODE NUMBERING UTILITIES, ETC.
//
//**********************************************
vector<string>
FSInfo::getParticleNamesFromFSName( const string& FSName ){


	// some quick checks

	if ((FSName.size() == 0) ||
			(FSName.find("_") == string::npos)){
		cout << "FSFilter ERROR: error in final state name: " << FSName << endl;
		exit(1);
	}


	// a list of allowed particle names

	string singleParticles[28] = {
		"pi0", "pi-", "pi+",
		"Ks",  "K-",  "K+",
		"gamma",
		"eta",
		"p-",  "p+",
		"mu-", "mu+",
		"e-",  "e+",
		"ALambda", "Lambda",
		"D0bar"  ,
		"D0"     ,
		"D-"     ,
		"D+"     ,
		"Ds-"    , 
		"Ds+"    , 
		"J/psi"  , 
		"chi_c1" , 
		"h_c"    , 
		"psi(2S)", 
		"nu"     , 
		"n0" 
	};

	// parse FSName digit by digit, starting at the end

	int index = 0, idash=0;
	vector<string> particleNamesTmp;
	for (int i = FSName.size()-1; i >= 0 && index < 28; i--){
		string digit = FSName.substr(i,1);
		if (  (digit == "0") || (digit == "1") || 
				(digit == "2") || (digit == "3") || 
				(digit == "4") || (digit == "5") || 
				(digit == "6") || (digit == "7") || 
				(digit == "8") || (digit == "9")){
			int num = atoi(digit.c_str());
			for (int j = 0; j < num; j++){
				particleNamesTmp.push_back(singleParticles[index]);
			}
			index++;
		}else if (digit == "M" || digit == "m" ){
			particleNamesTmp .push_back(singleParticles[index]);
			index++;
		}else if (digit == "_" ){
			if( idash==0){
				index =  7;
				idash++;
			}else if(idash== 1){
				index = 16;
				idash++;
			}else{
				index = 22;
				idash++;
			}
		}
		else{
			break;
		}
	}

	// make sure we have particles

	if (particleNamesTmp.size() == 0){
		cout << "FSFilter ERROR: error in final state name: " << FSName << endl;
		exit(1);
	}

	// now reverse the order of the particle names

	vector<string> particleNames;
	for (int i = particleNamesTmp.size()-1; i >= 0; i--){
		particleNames   .push_back(particleNamesTmp[i]);
	}

	return particleNames;

}

vector<int>
FSInfo::getDecayCodeFromParticleNames( const vector<string>& particleNames ){

	int decayCode1 = 0;
	int decayCode2 = 0;
	int decayCode3 = 0;
	int decayCode4 = 0;
	for (unsigned int i = 0; i < particleNames.size(); i++){
		if      (particleNames[i] == "pi0"      ){ decayCode1 += 1;           }
		else if (particleNames[i] == "pi-"      ){ decayCode1 += 10;          }
		else if (particleNames[i] == "pi+"      ){ decayCode1 += 100;         }
		else if (particleNames[i] == "Ks"       ){ decayCode1 += 1000;        }
		else if (particleNames[i] == "K-"       ){ decayCode1 += 10000;       }
		else if (particleNames[i] == "K+"       ){ decayCode1 += 100000;      }
		else if (particleNames[i] == "gamma"    ){ decayCode1 += 1000000;     }
		//
		else if (particleNames[i] == "eta"      ){ decayCode2 += 1;           }
		else if (particleNames[i] == "p-"       ){ decayCode2 += 10;          }
		else if (particleNames[i] == "p+"       ){ decayCode2 += 100;         }
		else if (particleNames[i] == "mu-"      ){ decayCode2 += 1000;        }
		else if (particleNames[i] == "mu+"      ){ decayCode2 += 10000;       }
		else if (particleNames[i] == "e-"       ){ decayCode2 += 100000;      }
		else if (particleNames[i] == "e+"       ){ decayCode2 += 1000000;     }
		else if (particleNames[i] == "ALambda"  ){ decayCode2 += 10000000;    }
		else if (particleNames[i] == "Lambda"   ){ decayCode2 += 100000000;   }
		//
		else if (particleNames[i] == "D0bar"    ){ decayCode3 += 1;           }
		else if (particleNames[i] == "D0"       ){ decayCode3 += 10;          }
		else if (particleNames[i] == "D-"       ){ decayCode3 += 100;         }
		else if (particleNames[i] == "D+"       ){ decayCode3 += 1000;        }
		else if (particleNames[i] == "Ds-"      ){ decayCode3 += 10000;       }
		else if (particleNames[i] == "Ds+"      ){ decayCode3 += 100000;      }
		//
		else if (particleNames[i] == "J/psi"    ){ decayCode4 += 1;           }
		else if (particleNames[i] == "chi_c1"   ){ decayCode4 += 10;          }
		else if (particleNames[i] == "h_c"      ){ decayCode4 += 100;         }
		else if (particleNames[i] == "psi(2S)"  ){ decayCode4 += 1000;        }
		else if (particleNames[i] == "nu"       ){ decayCode4 += 10000;       }
		else if (particleNames[i] == "n0"       ){ decayCode4 += 100000;      }
	}
	vector<int> decayCode; decayCode.clear();
	decayCode.push_back(decayCode1);
	decayCode.push_back(decayCode2);
	decayCode.push_back(decayCode3);
	decayCode.push_back(decayCode4);
	return decayCode;
}


vector<int>
FSInfo::getDecayCodeFromFSName( const string& FSName ){

	return getDecayCodeFromParticleNames(getParticleNamesFromFSName(FSName));

}


int
FSInfo::getNChargedParticlesFromParticleNames( const vector<string>& particleNames, const vector<string>& particleStatus  ){

	int nChargedParticles = 0;
	for (unsigned int i = 0; i < particleNames.size(); i++){
		if      (particleNames[i] == "pi0"    ){ if(particleStatus[i]!=0) nChargedParticles += 0; }
		else if (particleNames[i] == "pi-"    ){ if(particleStatus[i]!=0) nChargedParticles += 1; }
		else if (particleNames[i] == "pi+"    ){ if(particleStatus[i]!=0) nChargedParticles += 1; }
		else if (particleNames[i] == "Ks"     ){ if(particleStatus[i]!=0) nChargedParticles += 2; }
		else if (particleNames[i] == "K-"     ){ if(particleStatus[i]!=0) nChargedParticles += 1; }
		else if (particleNames[i] == "K+"     ){ if(particleStatus[i]!=0) nChargedParticles += 1; }
		else if (particleNames[i] == "gamma"  ){ if(particleStatus[i]!=0) nChargedParticles += 0; }
		//
		else if (particleNames[i] == "eta"    ){ if(particleStatus[i]!=0) nChargedParticles += 0; }
		else if (particleNames[i] == "p-"     ){ if(particleStatus[i]!=0) nChargedParticles += 1; }
		else if (particleNames[i] == "p+"     ){ if(particleStatus[i]!=0) nChargedParticles += 1; }
		else if (particleNames[i] == "mu-"    ){ if(particleStatus[i]!=0) nChargedParticles += 1; }
		else if (particleNames[i] == "mu+"    ){ if(particleStatus[i]!=0) nChargedParticles += 1; }
		else if (particleNames[i] == "e-"     ){ if(particleStatus[i]!=0) nChargedParticles += 1; }
		else if (particleNames[i] == "e+"     ){ if(particleStatus[i]!=0) nChargedParticles += 1; }
		else if (particleNames[i] == "ALambda"){ if(particleStatus[i]!=0) nChargedParticles += 2; }
		else if (particleNames[i] == "Lambda" ){ if(particleStatus[i]!=0) nChargedParticles += 2; }
		//
		else if (particleNames[i] == "D0bar"  ){ if(particleStatus[i]!=0) nChargedParticles += 6; }
		else if (particleNames[i] == "D0"     ){ if(particleStatus[i]!=0) nChargedParticles += 6; }
		else if (particleNames[i] == "D-"     ){ if(particleStatus[i]!=0) nChargedParticles += 5; }
		else if (particleNames[i] == "D+"     ){ if(particleStatus[i]!=0) nChargedParticles += 5; }
		else if (particleNames[i] == "Ds-"    ){ if(particleStatus[i]!=0) nChargedParticles += 5; }
		else if (particleNames[i] == "Ds+"    ){ if(particleStatus[i]!=0) nChargedParticles += 5; }
		else if (particleNames[i] == "J/psi"  ){ if(particleStatus[i]!=0) nChargedParticles += 0; }
		else if (particleNames[i] == "chi_c1" ){ if(particleStatus[i]!=0) nChargedParticles += 0; }
		else if (particleNames[i] == "h_c"    ){ if(particleStatus[i]!=0) nChargedParticles += 0; }
		else if (particleNames[i] == "psi(2S)"){ if(particleStatus[i]!=0) nChargedParticles += 0; }
		else if (particleNames[i] == "nu"     ){ if(particleStatus[i]!=0) nChargedParticles += 0; }
		else if (particleNames[i] == "n0"     ){ if(particleStatus[i]!=0) nChargedParticles += 0; }
	}
	return nChargedParticles;

}

vector<string>
FSInfo::parseString( const string& inputString ){

	vector<string> words;
	string word("");
	for (unsigned int j = 0; j < inputString.size(); j++){
		if (!isspace(inputString[j])){
			word += inputString[j];
			if ((j == (inputString.size()-1))&&(!word.empty())){
				words.push_back(word);
				word = "";
			}
		} 
		else if (!word.empty()){
			words.push_back(word);
			word = "";
		}
	}
	return words;
}

//**********************************************
//
//   FSMaC constructor
//
//**********************************************

FSMaC::FSMaC(const string& initialization){


	// divide the initialization string into seperate words

	vector<string> words = FSInfo::parseString(initialization);

	if (words.size() != 3){
		cout << "FSFilter ERROR: wrong arguments to FSMaC parameter: " << endl;
		cout << initialization << endl;
		exit(0);
	}

	// save input as member data

	m_FSName       = words[0];
	m_submodeName  = words[1];
	m_NameCons     = words[2];
	m_MassCons     = Mass(words[2]);
	m_daughterName = FSInfo::getParticleNamesFromFSName( m_submodeName );

	// quick checks

	if ( 0 ){
		cout << "FSFilter ERROR: wrong arguments to FSMaC parameter: " << endl;
		cout << initialization << endl;
		exit(0);
	}

}


