#include "FSFilter/MCTruthHelper.h"


MCTruthHelper::MCTruthHelper(SmartDataPtr<Event::McParticleCol> mcParticleCol, int RootID){

	// initialize flags to -1

	m_mcDecayCode1     = -1;
	m_mcDecayCode2     = -1;
	m_mcDecayCode3     = -1;
	m_mcDecayCode4     = -1;
	m_mcExtras         = -1;
	m_mcChicProduction = -1;
	m_mcJPsiProduction = -1;
	m_mcHcProduction   = -1;
	m_mcEtacProduction = -1;
	m_mcDDecay         = -1;
	m_mcEtaDecay       = -1;
	m_mcEtaprimeDecay  = -1;
	m_mcPhiDecay       = -1;
	m_mcOmegaDecay     = -1;
	m_mcKsDecay        = -1;
	m_mcFSRGamma       = -1;
	m_mcTotalEnergy    = -1;
   
	//m_particleNames    = FSInfo::getParticleNamesFromFSName( FSName );

	// make a vector of McParticle's to use in other methods
	bool strange    = false;
	bool psiDecay   = false;
	for(Event::McParticleCol::iterator mcp = mcParticleCol->begin();
			mcp != mcParticleCol->end(); mcp++){  
		// all MC particles
		m_allMcPList.push_back(*mcp);
		//
		int pdgid   =  (*mcp)->particleProperty();
		int trkidx  = ((*mcp)->mother()).trackIndex();
		int mother  = ((*mcp)->mother()).particleProperty();
		//printf("No. %3d, pdgid = %8d, mother = %8d, mass=%9.4f\n", trkidx,pdgid,mother, ((*mcp)->initialFourMomentum()).m());
		if ((*mcp)->primaryParticle() && pdgid==11 &&  mother==11 ) continue; 
		if (RootID!=-999&& (*mcp)->primaryParticle()   )    continue;
		if (              !(*mcp)->decayFromGenerator())    continue;
		//printf("pdgid = %8d, RootID = %10d\n", pdgid,RootID);
		if (abs(pdgid-RootID)<=1 || RootID==-999)
		{ 
			psiDecay  = true;
		}
		if (!psiDecay)                         continue;
		// MC particles to process further
		m_mcPList.push_back(*mcp);
		//
		if ( abs(mother-RootID)<=1 || (mother==pdgid && RootID==-999) )
		{
			if ((*mcp)->particleProperty() != kFSRGamma)
			{
				// MC particles coming from the primary decay
				m_mcDecayList.push_back(*mcp);
			}
		}
	}

	// check that we found daughters of the initial particle (psi(2S),etc)
	if (m_mcDecayList.size() == 0){
		cout << "FSFILTER WARNING:  empty decay list" << endl;
		printInformation(RootID);
		//exit(0);
	}else{
		// sort the list of decay particles
		for (unsigned int i = 0; i < m_mcDecayList.size()-1; i++)
		{
			for (unsigned int j = i+1; j < m_mcDecayList.size(); j++)
			{
				if (m_mcDecayList[i]->particleProperty() > m_mcDecayList[j]->particleProperty())
				{
					McParticle* tmp  = m_mcDecayList[j];
					m_mcDecayList[j] = m_mcDecayList[i];
					m_mcDecayList[i] = tmp;
				}
			}
		}

		// sort the vector of McParticle's
		// (extra particles)

		for (unsigned int i = 0; i < m_mcPList.size(); i++)
		{
			if (  isParticle(m_mcPList[i],kNuE)      ||
					isParticle(m_mcPList[i],kNuMu)     ||
					isParticle(m_mcPList[i],kNuTau)    ||
					isParticle(m_mcPList[i],kAntiNuE)  ||
					isParticle(m_mcPList[i],kAntiNuMu) ||
					isParticle(m_mcPList[i],kAntiNuTau)) m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kKl))          m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kN))           m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kAntiN))       m_sortedMcPList.push_back(m_mcPList[i]);
		}
		// (code 3)
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kDsp))         m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kDsm))         m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kDp))          m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kDm))          m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kD0))          m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kD0bar))       m_sortedMcPList.push_back(m_mcPList[i]);
		}

		// (code 2)
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kLambda)&&hasDaughters(m_mcPList[i],kPp,kPim))
				m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kALambda)&&hasDaughters(m_mcPList[i],kPm,kPip))
				m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kEp)) m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kEm)) m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kMup)) m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kMum)) m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kPp)) m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kPm)) m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kEta)&&hasDaughters(m_mcPList[i],kGamma,kGamma))
				m_sortedMcPList.push_back(m_mcPList[i]);
		}

		// (code 1)
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kGamma)) m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kKp)) m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kKm)) m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kKs)&&hasDaughters(m_mcPList[i],kPip,kPim))
				m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kPip)) m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kPim)) m_sortedMcPList.push_back(m_mcPList[i]);
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kPi0)&&hasDaughters(m_mcPList[i],kGamma,kGamma)) 
				m_sortedMcPList.push_back(m_mcPList[i]);
		}
	}
}


double
MCTruthHelper::MCTotalEnergy(){
	if (m_mcTotalEnergy > 0){}
	else { 
		m_mcTotalEnergy = 0.0;
		for (unsigned int i = 0; i < m_sortedMcPList.size(); i++){
			m_mcTotalEnergy += m_sortedMcPList[i]->initialFourMomentum().e();
		}
		for (unsigned int i = 0; i < m_mcPList.size(); i++){
			if (isParticle(m_mcPList[i],kFSRGamma)){
				m_mcTotalEnergy += m_mcPList[i]->initialFourMomentum().e();
			}
		}
	}
	return m_mcTotalEnergy;
}

MCTruthHelper::~MCTruthHelper(){
	FreeAll(m_mcPList);
	FreeAll(m_allMcPList);
	FreeAll(m_mcDecayList);
	FreeAll(m_sortedMcPList);
}

bool
MCTruthHelper::isParticle(const McParticle* mcParticle, int idParticle){

	// if the particle id's don't match, return false
	if (mcParticle->particleProperty() != idParticle) return false;

	const McParticle* mcMother        = &mcParticle->mother();

	// check if this particle is coming from another final state particle
	if ( hasDMothers(mcParticle) ) return false;
	//	
	if (mcMother){
		int idMother = mcMother->particleProperty();

		// check for pi0 --> gamma gamma
		if ((idParticle == kGamma) &&
				(idMother == kPi0 && hasDaughters(mcMother,kGamma,kGamma)))
			return false;

		// check for eta --> gamma gamma
		if ((idParticle == kGamma) &&
				(idMother == kEta && hasDaughters(mcMother,kGamma,kGamma)))
			return false;

		// check for Ks --> pi+ pi-
		if (((idParticle == kPip) || (idParticle == kPim)) &&
				(idMother == kKs && hasDaughters(mcMother,kPip,kPim)))
			return false;

		// check for Lambda --> p+ pi-
		if (((idParticle == kPp) || (idParticle == kPim)) &&
				(idMother == kLambda && hasDaughters(mcMother,kPp,kPim)))
			return false;

		// check for ALambda --> p- pi+
		if (((idParticle == kPm) || (idParticle == kPip)) &&
				(idMother == kALambda && hasDaughters(mcMother,kPm,kPip)))
			return false;

		// check for Kl decays
		if (idMother == kKl) return false;

	}
	return true;
}
//
int 
MCTruthHelper::MCDTMode(const McParticle* D){
	vector<McParticle*> m_mcDList = getDaughters(D), m_EpList;
	if (m_mcDList.size()>6) return 10000;
	//
	int Dcand = D->particleProperty();
	vector<int> daughters; daughters.clear();
	vector<int> checkers ; checkers .clear();
	//
	int kEpCh=-1; // 0 : etaprimme -->eta pi+pi-, 1: etaprime-->gamma rho0
	for (unsigned int i = 0; i < m_mcDList.size(); i++){
		int id0 = m_mcDList[i]->particleProperty();
		if(id0==kEtaprime) m_EpList.push_back(m_mcDList[i]);	
		checkers.push_back(id0);
	}
	if(m_EpList.size()==1)
	{
		if( hasDaughters(m_EpList[0], kPip, kPim, kEta)) kEpCh=0;
		if( hasDaughters(m_EpList[0], kGamma, kRho0)   ) kEpCh=1;
	}
	if ( checkers.size()==0) return -1;
	/*
	printf("D(%4d)-->",Dcand);
	for(int i=0; i<checkers.size();i++){
		if(i<checkers.size()-1)printf("%6s",particleType(checkers[i]).data());
		else                   printf("%5s\n",particleType(checkers[i]).data());   
	}
	*/
	if( Dcand ==  421 ){	
		if( dVertices(Dcand, kKm ,  kPip                         )==1            ) return     0 ; 
		if( dVertices(Dcand, kKm ,  kPip, kPi0                   )==1            ) return     1 ; 
		if( dVertices(Dcand, kKm ,  kPip, kPi0, kPi0             )==1            ) return     2 ; 
		if( dVertices(Dcand, kKm ,  kPip, kPip, kPim             )==1            ) return     3 ; 
		if( dVertices(Dcand, kKm ,  kPip, kPip, kPim, kPi0       )==1            ) return     4 ; 
		if( dVertices(Dcand, kKm ,  kPip, kEta                   )==1            ) return     5 ; 
		if( dVertices(Dcand, kKs ,  kKm , kPip                   )==1            ) return    50 ; 
		if( dVertices(Dcand, kKs ,  kKm , kPip, kPi0             )==1            ) return    51 ; 
		if( dVertices(Dcand, kKs ,  kPip, kPim                   )==1            ) return   100 ; 
		if( dVertices(Dcand, kKs ,  kPip, kPim, kPi0             )==1            ) return   101 ; 
		if( dVertices(Dcand, kKs ,  kPi0                         )==1            ) return   102 ; 
		if( dVertices(Dcand, kPip,  kPim, kPi0                   )==1            ) return   103 ; 
		if( dVertices(Dcand, kPip,  kPim                         )==1            ) return   104 ; 
		if( dVertices(Dcand, kKm ,  kKp                          )==1            ) return   105 ; 
		if( dVertices(Dcand, kKm ,  kKp , kPi0                   )==1            ) return   106 ; 
		if( dVertices(Dcand, kPi0,  kPi0                         )==1            ) return   107 ; 
		if( dVertices(Dcand, kKs ,  kKs                          )==1            ) return   108 ; 
		if( dVertices(Dcand, kKs ,  kKs , kPi0                   )==1            ) return   109 ; 
		if( dVertices(Dcand, kKs ,  kPi0, kPi0                   )==1            ) return   110 ; 
		if( dVertices(Dcand, kKs ,  kKm , kKp                    )==1            ) return   111 ; 
		if( dVertices(Dcand, kKs ,  kEta                         )==1            ) return   112 ; 
		if( dVertices(Dcand, kPi0,  kPi0, kPi0                   )==1            ) return   113 ; 
		if( dVertices(Dcand, kKs ,  kKs , kKs                    )==1            ) return   114 ; 
		if( dVertices(Dcand, kPip,  kPip, kPim, kPim             )==1            ) return   115 ; 
		if( dVertices(Dcand, kPip,  kPim, kPi0, kPi0             )==1            ) return   116 ; 
		if( dVertices(Dcand, kKm ,  kKp , kPip, kPim             )==1            ) return   117 ; 
		if( dVertices(Dcand, kKm ,  kKp , kPi0, kPi0             )==1            ) return   118 ; 
		if( dVertices(Dcand, kKs ,  kKs , kPip, kPim             )==1            ) return   119 ; 
		if( dVertices(Dcand, kPip,  kPip, kPim, kPim, kPi0       )==1            ) return   120 ; 
		if( dVertices(Dcand, kKs ,  kPip, kPip, kPim, kPim       )==1            ) return   121 ; 
		if( dVertices(Dcand, kKm ,  kKp , kPip, kPim, kPi0       )==1            ) return   122 ; 
		if( dVertices(Dcand, kKs ,  kPi0, kEta                   )==1            ) return   123 ; 
		if( dVertices(Dcand, kKs ,  kEtaprime                    )==1 && kEpCh==0) return   124 ; 
		if( dVertices(Dcand, kKs ,  kEtaprime                    )==1 && kEpCh==1) return   125 ;
	}else if( Dcand ==  411 ){	
		if( dVertices(Dcand, kKm ,  kPip, kPip                   )==1            ) return   200 ;
		if( dVertices(Dcand, kKm ,  kPip, kPip, kPi0             )==1            ) return   201 ;
		if( dVertices(Dcand, kKs ,  kPip                         )==1            ) return   202 ;
		if( dVertices(Dcand, kKs ,  kPip, kPi0                   )==1            ) return   203 ;
		if( dVertices(Dcand, kKs ,  kPip, kPip, kPim             )==1            ) return   204 ;
		if( dVertices(Dcand, kKm ,  kKp , kPip                   )==1            ) return   205 ;
		if( dVertices(Dcand, kPip,  kPi0                         )==1            ) return   206 ;
		if( dVertices(Dcand, kKp ,  kPi0                         )==1            ) return   207 ;
		if( dVertices(Dcand, kKs ,  kKp                          )==1            ) return   208 ;
		if( dVertices(Dcand, kPip,  kPip, kPim                   )==1            ) return   209 ;
		if( dVertices(Dcand, kPip,  kPi0, kPi0                   )==1            ) return   210 ;
		if( dVertices(Dcand, kKs ,  kKs , kPip                   )==1            ) return   211 ;
		if( dVertices(Dcand, kKs ,  kKp , kPi0                   )==1            ) return   212 ;
		if( dVertices(Dcand, kKs ,  kKs , kKp                    )==1            ) return   213 ;
		if( dVertices(Dcand, kPip,  kPip, kPim, kPi0             )==1            ) return   214 ;
		if( dVertices(Dcand, kKs ,  kPip, kPi0, kPi0             )==1            ) return   215 ;
		if( dVertices(Dcand, kKs ,  kKp , kPip, kPim             )==1            ) return   216 ;
		if( dVertices(Dcand, kKs ,  kKm , kPip, kPip             )==1            ) return   217 ;
		if( dVertices(Dcand, kKm ,  kKp , kPip, kPi0             )==1            ) return   218 ;
		if( dVertices(Dcand, kPip,  kPip, kPip, kPim, kPim       )==1            ) return   219 ;
		if( dVertices(Dcand, kKp ,  kPip, kPip, kPim, kPim       )==1            ) return   220 ;
		if( dVertices(Dcand, kPip,  kEta                         )==1            ) return   221 ;
		if( dVertices(Dcand, kKs ,  kPip,  kEta                  )==1            ) return   221 ;
	}else if( Dcand ==  431 ){	
		if( dVertices(Dcand, kKs ,  kKp                          )==1            ) return   400 ;
		if( dVertices(Dcand, kKm ,  kKp , kPip                   )==1            ) return   401 ;
		if( dVertices(Dcand, kKs ,  kKp , kPi0                   )==1            ) return   402 ;
		if( dVertices(Dcand, kKs ,  kKs , kPip                   )==1            ) return   403 ;
		if( dVertices(Dcand, kKm ,  kKp , kPip, kPi0             )==1            ) return   404 ;
		if( dVertices(Dcand, kKs ,  kKp , kPip, kPim             )==1            ) return   405 ;
		if( dVertices(Dcand, kKs ,  kKm , kPip, kPip             )==1            ) return   406 ;
		if( dVertices(Dcand, kKm ,  kKp , kPip, kPip, kPim       )==1            ) return   407 ;
		if( dVertices(Dcand, kPip,  kPi0                         )==1            ) return   420 ;
		if( dVertices(Dcand, kPip,  kPip, kPim                   )==1            ) return   421 ;
		if( dVertices(Dcand, kPip,  kPip, kPim, kPi0             )==1            ) return   422 ;
		if( dVertices(Dcand, kPip,  kPip, kPim, kPip, kPim       )==1            ) return   423 ;
		if( dVertices(Dcand, kPip,  kPip, kPim, kPip, kPim, kPi0 )==1            ) return   424 ;
		if( dVertices(Dcand, kPip,  kEta                         )==1            ) return   440 ;
		if( dVertices(Dcand, kPip,  kPi0, kEta                   )==1            ) return   441 ;
		if( dVertices(Dcand, kPip,  kPip, kPim, kEta             )==1            ) return   442 ;
		if( dVertices(Dcand, kPip,  kEtaprime                    )==1 && kEpCh==0) return   460 ; 
		if( dVertices(Dcand, kPip,  kPi0, kEtaprime              )==1 && kEpCh==0) return   461 ;
		if( dVertices(Dcand, kPip,  kEtaprime                    )==1 && kEpCh==1) return   480 ; 
		if( dVertices(Dcand, kPip,  kPi0, kEtaprime              )==1 && kEpCh==1) return   481 ;
		if( dVertices(Dcand, kKs ,  kPip                         )==1            ) return   500 ;
		if( dVertices(Dcand, kKs ,  kPip, kPi0                   )==1            ) return   501 ;
		if( dVertices(Dcand, kKp ,  kPip, kPim                   )==1            ) return   502 ;
		if( dVertices(Dcand, kKp ,  kPip, kPim, kPi0             )==1            ) return   503 ;
		if( dVertices(Dcand, kKm ,  kKp , kKp                    )==1            ) return   504 ;
	}else if( Dcand == -421 ){	
		if( dVertices(Dcand, kKp ,  kPim                         )==1            ) return     0 ; 
		if( dVertices(Dcand, kKp ,  kPim, kPi0                   )==1            ) return     1 ; 
		if( dVertices(Dcand, kKp ,  kPim, kPi0, kPi0             )==1            ) return     2 ; 
		if( dVertices(Dcand, kKp ,  kPim, kPim, kPip             )==1            ) return     3 ; 
		if( dVertices(Dcand, kKp ,  kPim, kPim, kPip, kPi0       )==1            ) return     4 ; 
		if( dVertices(Dcand, kKp ,  kPim, kEta                   )==1            ) return     5 ; 
		if( dVertices(Dcand, kKs ,  kKp , kPim                   )==1            ) return    50 ; 
		if( dVertices(Dcand, kKs ,  kKp , kPim, kPi0             )==1            ) return    51 ; 
		if( dVertices(Dcand, kKs ,  kPim, kPip                   )==1            ) return   100 ; 
		if( dVertices(Dcand, kKs ,  kPim, kPip, kPi0             )==1            ) return   101 ; 
		if( dVertices(Dcand, kKs ,  kPi0                         )==1            ) return   102 ; 
		if( dVertices(Dcand, kPim,  kPip, kPi0                   )==1            ) return   103 ; 
		if( dVertices(Dcand, kPim,  kPip                         )==1            ) return   104 ; 
		if( dVertices(Dcand, kKp ,  kKm                          )==1            ) return   105 ; 
		if( dVertices(Dcand, kKp ,  kKm , kPi0                   )==1            ) return   106 ; 
		if( dVertices(Dcand, kPi0,  kPi0                         )==1            ) return   107 ; 
		if( dVertices(Dcand, kKs ,  kKs                          )==1            ) return   108 ; 
		if( dVertices(Dcand, kKs ,  kKs , kPi0                   )==1            ) return   109 ; 
		if( dVertices(Dcand, kKs ,  kPi0, kPi0                   )==1            ) return   110 ; 
		if( dVertices(Dcand, kKs ,  kKp , kKm                    )==1            ) return   111 ; 
		if( dVertices(Dcand, kKs ,  kEta                         )==1            ) return   112 ; 
		if( dVertices(Dcand, kPi0,  kPi0, kPi0                   )==1            ) return   113 ; 
		if( dVertices(Dcand, kKs ,  kKs , kKs                    )==1            ) return   114 ; 
		if( dVertices(Dcand, kPim,  kPim, kPip, kPip             )==1            ) return   115 ; 
		if( dVertices(Dcand, kPim,  kPip, kPi0, kPi0             )==1            ) return   116 ; 
		if( dVertices(Dcand, kKp ,  kKm , kPim, kPip             )==1            ) return   117 ; 
		if( dVertices(Dcand, kKp ,  kKm , kPi0, kPi0             )==1            ) return   118 ; 
		if( dVertices(Dcand, kKs ,  kKs , kPim, kPip             )==1            ) return   119 ; 
		if( dVertices(Dcand, kPim,  kPim, kPip, kPip, kPi0       )==1            ) return   120 ; 
		if( dVertices(Dcand, kKs ,  kPim, kPim, kPip, kPip       )==1            ) return   121 ; 
		if( dVertices(Dcand, kKp ,  kKm , kPim, kPip, kPi0       )==1            ) return   122 ; 
		if( dVertices(Dcand, kKs ,  kPi0, kEta                   )==1            ) return   123 ; 
		if( dVertices(Dcand, kKs ,  kEtaprime                    )==1 && kEpCh==0) return   124 ; 
		if( dVertices(Dcand, kKs ,  kEtaprime                    )==1 && kEpCh==1) return   125 ;
	}else if( Dcand == -411 ){	
		if( dVertices(Dcand, kKp ,  kPim, kPim                   )==1            ) return   200 ;
		if( dVertices(Dcand, kKp ,  kPim, kPim, kPi0             )==1            ) return   201 ;
		if( dVertices(Dcand, kKs ,  kPim                         )==1            ) return   202 ;
		if( dVertices(Dcand, kKs ,  kPim, kPi0                   )==1            ) return   203 ;
		if( dVertices(Dcand, kKs ,  kPim, kPim, kPip             )==1            ) return   204 ;
		if( dVertices(Dcand, kKp ,  kKm , kPim                   )==1            ) return   205 ;
		if( dVertices(Dcand, kPim,  kPi0                         )==1            ) return   206 ;
		if( dVertices(Dcand, kKm ,  kPi0                         )==1            ) return   207 ;
		if( dVertices(Dcand, kKs ,  kKm                          )==1            ) return   208 ;
		if( dVertices(Dcand, kPim,  kPim, kPip                   )==1            ) return   209 ;
		if( dVertices(Dcand, kPim,  kPi0, kPi0                   )==1            ) return   210 ;
		if( dVertices(Dcand, kKs ,  kKs , kPim                   )==1            ) return   211 ;
		if( dVertices(Dcand, kKs ,  kKm , kPi0                   )==1            ) return   212 ;
		if( dVertices(Dcand, kKs ,  kKs , kKm                    )==1            ) return   213 ;
		if( dVertices(Dcand, kPim,  kPim, kPip, kPi0             )==1            ) return   214 ;
		if( dVertices(Dcand, kKs ,  kPim, kPi0, kPi0             )==1            ) return   215 ;
		if( dVertices(Dcand, kKs ,  kKm , kPim, kPip             )==1            ) return   216 ;
		if( dVertices(Dcand, kKs ,  kKp , kPim, kPim             )==1            ) return   217 ;
		if( dVertices(Dcand, kKp ,  kKm , kPim, kPi0             )==1            ) return   218 ;
		if( dVertices(Dcand, kPim,  kPim, kPim, kPip, kPip       )==1            ) return   219 ;
		if( dVertices(Dcand, kKm ,  kPim, kPim, kPip, kPip       )==1            ) return   220 ;
		if( dVertices(Dcand, kPim,  kEta                         )==1            ) return   221 ;
		if( dVertices(Dcand, kKs ,  kPim,  kEta                  )==1            ) return   221 ;
	}else if( Dcand == -431 ){	
		if( dVertices(Dcand, kKs ,  kKm                          )==1            ) return   400 ;
		if( dVertices(Dcand, kKp ,  kKm , kPim                   )==1            ) return   401 ;
		if( dVertices(Dcand, kKs ,  kKm , kPi0                   )==1            ) return   402 ;
		if( dVertices(Dcand, kKs ,  kKs , kPim                   )==1            ) return   403 ;
		if( dVertices(Dcand, kKp ,  kKm , kPim, kPi0             )==1            ) return   404 ;
		if( dVertices(Dcand, kKs ,  kKm , kPim, kPip             )==1            ) return   405 ;
		if( dVertices(Dcand, kKs ,  kKp , kPim, kPim             )==1            ) return   406 ;
		if( dVertices(Dcand, kKp ,  kKm , kPim, kPim, kPip       )==1            ) return   407 ;
		if( dVertices(Dcand, kPim,  kPi0                         )==1            ) return   420 ;
		if( dVertices(Dcand, kPim,  kPim, kPip                   )==1            ) return   421 ;
		if( dVertices(Dcand, kPim,  kPim, kPip, kPi0             )==1            ) return   422 ;
		if( dVertices(Dcand, kPim,  kPim, kPip, kPim, kPip       )==1            ) return   423 ;
		if( dVertices(Dcand, kPim,  kPim, kPip, kPim, kPip, kPi0 )==1            ) return   424 ;
		if( dVertices(Dcand, kPim,  kEta                         )==1            ) return   440 ;
		if( dVertices(Dcand, kPim,  kPi0, kEta                   )==1            ) return   441 ;
		if( dVertices(Dcand, kPim,  kPim, kPip, kEta             )==1            ) return   442 ;
		if( dVertices(Dcand, kPim,  kEtaprime                    )==1 && kEpCh==0) return   460 ; 
		if( dVertices(Dcand, kPim,  kPi0, kEtaprime              )==1 && kEpCh==0) return   461 ;
		if( dVertices(Dcand, kPim,  kEtaprime                    )==1 && kEpCh==1) return   480 ; 
		if( dVertices(Dcand, kPim,  kPi0, kEtaprime              )==1 && kEpCh==1) return   481 ;
		if( dVertices(Dcand, kKs ,  kPim                         )==1            ) return   500 ;
		if( dVertices(Dcand, kKs ,  kPim, kPi0                   )==1            ) return   501 ;
		if( dVertices(Dcand, kKm ,  kPim, kPip                   )==1            ) return   502 ;
		if( dVertices(Dcand, kKm ,  kPim, kPip, kPi0             )==1            ) return   503 ;
		if( dVertices(Dcand, kKp ,  kKm , kKm                    )==1            ) return   504 ;
	}
	return 10000; 
}

int
MCTruthHelper::nParticles(int idParticle){
	int n = 0;
	for (unsigned int i = 0; i < m_mcPList.size(); i++){
		if ( hasDMothers(m_mcPList[i])         ) continue;
		if (isParticle(m_mcPList[i],idParticle)) n++;
	}
	if (n > 14){
		cout    << "FSFilter WARNING:  found " << n << " generated particles "
			<< "with ID = " << idParticle << " but returning 14 " << endl;
		return 14;
	}
	return n;
}



bool
MCTruthHelper::hasParticle(int idParticle){
	return (nParticles(idParticle) > 0);
}


vector<McParticle*> 
MCTruthHelper::getDaughters(const McParticle* P){
	vector<McParticle*> daughters; daughters.clear(); 
	bool isLEAF = P->leafParticle();
	if ( isLEAF ) return daughters;	
	int  Did  =  abs(P->particleProperty());
	bool Dmes = (Did==kD0 || Did==kDp || Did==kDsp);
	//
	SmartRefVector<McParticle> daughtersCheck = P->daughterList();
	for (int j = 0; j < daughtersCheck.size(); j++){
		bool     leaf = daughtersCheck[j]->leafParticle(); 
		int        id = daughtersCheck[j]->particleProperty();
		McParticle  M = daughtersCheck[j]->mother(); 
		int       idM = M.particleProperty();
		if (id == kFSRGamma) continue;
		if( leaf ) {
			daughters.push_back(daughtersCheck[j]); 
			continue;
		}
		// 
		if (id == kGamma && (idM=kPi0 || idM==kEta ))                                   continue;
		if (id == kGamma && Dmes && (idM==kEtaprime && hasDaughters(&M, kGamma, kRho0)))continue;
		//
		if ( id==kPi0 && hasDaughters(daughtersCheck[j],kGamma,kGamma)){
			daughters.push_back(daughtersCheck[j]); 
			continue;
		}
		if ( id==kEta && hasDaughters(daughtersCheck[j],kGamma,kGamma)){
			daughters.push_back(daughtersCheck[j]); 
			continue;
		}
		if (id==kEtaprime&& Dmes &&
				(hasDaughters(daughtersCheck[j],kPip,kPim,kEta)||hasDaughters(daughtersCheck[j],kGamma,kRho0))){
			daughters.push_back(daughtersCheck[j]); // only for D tag cases,  potential bug for other usage  
			continue;
		}
		if ( id==kKs && hasDaughters(daughtersCheck[j],kPip,kPim)){
			daughters.push_back(daughtersCheck[j]); 
			continue;
		}
		if ( id==kLambda && hasDaughters(daughtersCheck[j],kPp,kPim)){
			daughters.push_back(daughtersCheck[j]); 
			continue;
		}
		if ( id==kALambda && hasDaughters(daughtersCheck[j],kPm,kPip)){
			daughters.push_back(daughtersCheck[j]); 
			continue;
		}
		//
		vector<McParticle*> VP=	getDaughters(daughtersCheck[j]);
		for (int k = 0; k < VP.size(); k++){
			daughters.push_back(VP[k]); 
		}
	}	
	return daughters;	
}

bool 
MCTruthHelper::hasDMothers(const McParticle* P, const int mid){
	Event::McParticle M = *P; 
	while( M.particleProperty() != M.mother().particleProperty() ){
		int id = abs(M.mother().particleProperty()); 
		if ( id == kD0 || id==kDp || id==kDsp || id==mid) return true;
		M=M.mother();	
	}
	return false;
}

bool
MCTruthHelper::DhasDaughters(
		const McParticle* mcParticle, 
		int idDaughter1,
		int idDaughter2,
		int idDaughter3,
		int idDaughter4,
		int idDaughter5,
		int idDaughter6,
		int idDaughter7,
		int idDaughter8,
		int idDaughter9,
		int idDaughter10
		){
	// create a vector of daughter id's to search for
	vector<int> idDaughters;
	if (idDaughter1  != 0)  idDaughters.push_back( idDaughter1);
	if (idDaughter2  != 0)  idDaughters.push_back( idDaughter2);
	if (idDaughter3  != 0)  idDaughters.push_back( idDaughter3);
	if (idDaughter4  != 0)  idDaughters.push_back( idDaughter4);
	if (idDaughter5  != 0)  idDaughters.push_back( idDaughter5);
	if (idDaughter6  != 0)  idDaughters.push_back( idDaughter6);
	if (idDaughter7  != 0)  idDaughters.push_back( idDaughter7);
	if (idDaughter8  != 0)  idDaughters.push_back( idDaughter8);
	if (idDaughter9  != 0)  idDaughters.push_back( idDaughter9);
	if (idDaughter10 != 0)  idDaughters.push_back(idDaughter10);
	if (idDaughters.size() < 2) return false;

	// create a vector of daughter id's from the McParticle
	vector<int> idDaughtersCheck;
	vector<McParticle*> daughtersCheck = getDaughters(mcParticle);
	for (int j = 0; j < daughtersCheck.size(); j++){
		int id = (*(daughtersCheck[j])).particleProperty();    
		if (id != kFSRGamma) idDaughtersCheck.push_back(id);
	}

	// if the numbers of daughters don't match return false
	if (idDaughters.size() != idDaughtersCheck.size()) return false;

	// sort the vectors of daughter id's
	for (unsigned int i1 = 0; i1 < idDaughters.size()-1; i1++){
		for (unsigned int i2 = i1+1; i2 < idDaughters.size(); i2++){
			if (idDaughters[i1] > idDaughters[i2]){
				int temp = idDaughters[i1];
				idDaughters[i1] = idDaughters[i2];
				idDaughters[i2] = temp;
			}
			if (idDaughtersCheck[i1] > idDaughtersCheck[i2]){
				int temp = idDaughtersCheck[i1];
				idDaughtersCheck[i1] = idDaughtersCheck[i2];
				idDaughtersCheck[i2] = temp;
			}
		}
	}

	// check if the daughter id's match
	for (unsigned int i1 = 0; i1 < idDaughters.size(); i1++)
	{
		if (idDaughters[i1] != idDaughtersCheck[i1]) return false;
	}
	return true;
}


bool
MCTruthHelper::hasDaughters(
		const McParticle* mcParticle, 
		int idDaughter1,
		int idDaughter2,
		int idDaughter3,
		int idDaughter4,
		int idDaughter5,
		int idDaughter6,
		int idDaughter7,
		int idDaughter8,
		int idDaughter9,
		int idDaughter10
		){

	// create a vector of daughter id's to search for
	vector<int> idDaughters;
	if (idDaughter1  != 0)  idDaughters.push_back( idDaughter1);
	if (idDaughter2  != 0)  idDaughters.push_back( idDaughter2);
	if (idDaughter3  != 0)  idDaughters.push_back( idDaughter3);
	if (idDaughter4  != 0)  idDaughters.push_back( idDaughter4);
	if (idDaughter5  != 0)  idDaughters.push_back( idDaughter5);
	if (idDaughter6  != 0)  idDaughters.push_back( idDaughter6);
	if (idDaughter7  != 0)  idDaughters.push_back( idDaughter7);
	if (idDaughter8  != 0)  idDaughters.push_back( idDaughter8);
	if (idDaughter9  != 0)  idDaughters.push_back( idDaughter9);
	if (idDaughter10 != 0)  idDaughters.push_back(idDaughter10);
	if (idDaughters.size() < 2) return false;

	// create a vector of daughter id's from the McParticle
	vector<int> idDaughtersCheck;
	SmartRefVector<McParticle> daughtersCheck = mcParticle->daughterList();
	for (int j = 0; j < daughtersCheck.size(); j++){
		int id = (*(daughtersCheck[j])).particleProperty();    
		if (id != kFSRGamma) idDaughtersCheck.push_back(id);
	}

	// if the numbers of daughters don't match return false
	if (idDaughters.size() != idDaughtersCheck.size()) return false;

	// sort the vectors of daughter id's
	for (unsigned int i1 = 0; i1 < idDaughters.size()-1; i1++){
		for (unsigned int i2 = i1+1; i2 < idDaughters.size(); i2++){
			if (idDaughters[i1] > idDaughters[i2]){
				int temp = idDaughters[i1];
				idDaughters[i1] = idDaughters[i2];
				idDaughters[i2] = temp;
			}
			if (idDaughtersCheck[i1] > idDaughtersCheck[i2]){
				int temp = idDaughtersCheck[i1];
				idDaughtersCheck[i1] = idDaughtersCheck[i2];
				idDaughtersCheck[i2] = temp;
			}
		}
	}

	// check if the daughter id's match
	for (unsigned int i1 = 0; i1 < idDaughters.size(); i1++)
	{
		if (idDaughters[i1] != idDaughtersCheck[i1]) return false;
	}
	return true;
}


int
MCTruthHelper::nDecays(
		int  idDaughter1,
		int  idDaughter2,
		int  idDaughter3,
		int  idDaughter4,
		int  idDaughter5,
		int  idDaughter6,
		int  idDaughter7,
		int  idDaughter8,
		int  idDaughter9,
		int idDaughter10
		){
	int n = 0;
	for (unsigned int i = 0; i < m_mcPList.size(); i++){
		McParticle* mcp = m_mcPList[i];
		if (hasDaughters(mcp,    
					idDaughter1,
					idDaughter2,
					idDaughter3,
					idDaughter4,
					idDaughter5,
					idDaughter6,
					idDaughter7,
					idDaughter8,
					idDaughter9,
					idDaughter10
					)) n++;
	}
	if (n > 14){
		cout << "FSFilter WARNING:  found " << n << " generated decays with "
			<< "daughters = " 
			<< idDaughter1  << " "
			<< idDaughter2  << " "
			<< idDaughter3  << " "
			<< idDaughter4  << " "
			<< idDaughter5  << " "
			<< idDaughter6  << " "
			<< idDaughter7  << " "
			<< idDaughter8  << " "
			<< idDaughter9  << " "
			<< idDaughter10 << " "
			<< " but returning 14 " << endl;
		return 14;
	}
	return n;
}


bool
MCTruthHelper::hasDecay(
		int idDaughter1,
		int idDaughter2,
		int idDaughter3,
		int idDaughter4,
		int idDaughter5,
		int idDaughter6,
		int idDaughter7,
		int idDaughter8,
		int idDaughter9,
		int idDaughter10
		){
	return (nDecays(
				idDaughter1,
				idDaughter2,
				idDaughter3,
				idDaughter4,
				idDaughter5,
				idDaughter6,
				idDaughter7,
				idDaughter8,
				idDaughter9,
				idDaughter10
				) > 0);
}



int
MCTruthHelper::nVertices(int idParent, 
		int idDaughter1,
		int idDaughter2,
		int idDaughter3,
		int idDaughter4,
		int idDaughter5,
		int idDaughter6,
		int idDaughter7,
		int idDaughter8,
		int idDaughter9,
		int idDaughter10
		){
	int n = 0;
	for (unsigned int i = 0; i < m_mcPList.size(); i++){
		McParticle* mcp = m_mcPList[i];
		if (hasDMothers(mcp)) continue;
		if (mcp->particleProperty() == idParent && 
				hasDaughters(mcp,
					idDaughter1,
					idDaughter2,
					idDaughter3,
					idDaughter4,
					idDaughter5,
					idDaughter6,
					idDaughter7,
					idDaughter8,
					idDaughter9,
					idDaughter10
					)) n++;
	}
	if (n > 14){
		cout << "FSFilter WARNING:  found " << n << " generated vertices with "
			<< "parent = " << idParent << " and "
			<< "daughters = " 
			<< idDaughter1  << " "
			<< idDaughter2  << " "
			<< idDaughter3  << " "
			<< idDaughter4  << " "
			<< idDaughter5  << " "
			<< idDaughter6  << " "
			<< idDaughter7  << " "
			<< idDaughter8  << " "
			<< idDaughter9  << " "
			<< idDaughter10 << " "
			<< " but returning 14" << endl;
		return 14;
	}
	return n;
}

int
MCTruthHelper::dVertices(
		int idParent, 
		int idDaughter1,
		int idDaughter2,
		int idDaughter3,
		int idDaughter4,
		int idDaughter5,
		int idDaughter6,
		int idDaughter7,
		int idDaughter8,
		int idDaughter9,
		int idDaughter10
		){

	int n = 0;
	for (unsigned int i = 0; i < m_mcPList.size(); i++){
		McParticle* mcp = m_mcPList[i];
		if (mcp->particleProperty() == idParent && 
				DhasDaughters(mcp,
					idDaughter1 ,
					idDaughter2 ,
					idDaughter3 ,
					idDaughter4 ,
					idDaughter5 ,
					idDaughter6 ,
					idDaughter7 ,
					idDaughter8 ,
					idDaughter9 ,
					idDaughter10)
				) n++;
	}
	
	if (n > 14){
		cout << "FSFilter WARNING:  found " << n << " generated vertices with "
			<< "parent = " << idParent << " and "
			<< "daughters = " 
			<< idDaughter1  << " "
			<< idDaughter2  << " "
			<< idDaughter3  << " "
			<< idDaughter4  << " "
			<< idDaughter5  << " "
			<< idDaughter6  << " "
			<< idDaughter7  << " "
			<< idDaughter8  << " "
			<< idDaughter9  << " "
			<< idDaughter10 << " "
			<< " but returning 14" << endl;
		return 14;
	}
	return n;
}



bool
MCTruthHelper::hasVertex(
		int idParent, 
		int idDaughter1,
		int idDaughter2,
		int idDaughter3,
		int idDaughter4,
		int idDaughter5,
		int idDaughter6,
		int idDaughter7,
		int idDaughter8,
		int idDaughter9,
		int idDaughter10
		){
	return (nVertices(
				idParent,
				idDaughter1,
				idDaughter2,
				idDaughter3,
				idDaughter4,
				idDaughter5,
				idDaughter6,
				idDaughter7,
				idDaughter8,
				idDaughter9,
				idDaughter10
				) > 0);
}


string
MCTruthHelper::particleType(const McParticle* mcParticle){

	return particleType(mcParticle->particleProperty());

}


string
MCTruthHelper::particleType(int id){

	string name("");

	if      (id == kPsi2S)           name = "psi(2S)";
	else if (id == kPsi3770)         name = "psi(3770)";
	else if (id == kGamma)           name = "gamma";
	else if (id == kFSRGamma)        name = "FSRgamma";
	else if (id == kZ0   )           name = "Z^0";
	else if (id == kCluster)         name = "Cluster";
	else if (id == kString )         name = "String";
	else if (id == kHc)              name = "h_c";
	else if (id == kChic0)           name = "chi_c0";
	else if (id == kChic1)           name = "chi_c1";
	else if (id == kChic2)           name = "chi_c2";
	else if (id == kChic0p)          name = "chi'_c0";
	else if (id == kChic1p)          name = "chi'_c1";
	else if (id == kChic2p)          name = "chi'_c2";
	else if (id == kJpsi)            name = "J/psi";
	else if (id == kEtac)            name = "eta_c";
	else if (id == kPhi)             name = "phi";
	else if (id == kOmega)           name = "omega";
	else if (id == kPi0)             name = "pi0";
	else if (id == kPip)             name = "pi+";
	else if (id == kPim)             name = "pi-";
	else if (id == kRho0)            name = "rho0";
	else if (id == kRhop)            name = "rho+";
	else if (id == kRhom)            name = "rho-";
	else if (id == kA00 )            name = "a_00";
	else if (id == kA0p )            name = "a_0+";
	else if (id == kA0m )            name = "a_0-";
	else if (id == kB10 )            name = "b_10";
	else if (id == kB1p )            name = "b_1+";
	else if (id == kB1m )            name = "b_1-";
	else if (id == kA10 )            name = "a_10";
	else if (id == kA1p )            name = "a_1+";
	else if (id == kA1m )            name = "a_1-";
	else if (id == kF01370)          name = "f0(1370)";
	else if (id == kF01500)          name = "f0(1500)";
	else if (id == kH1  )            name = "h_1";
	else if (id == kH1p )            name = "h'_1";
	else if (id == kA20 )            name = "a_20";
	else if (id == kA2p )            name = "a_2+";
	else if (id == kA2m )            name = "a_2-";
	else if (id == kEtaprime)        name = "etaprime";
	else if (id == kEta)             name = "eta";
	else if (id == kKs)              name = "K_S0";
	else if (id == kKl)              name = "K_L0";
	else if (id == kKp)              name = "K+";
	else if (id == kKm)              name = "K-";
	else if (id == kPp)              name = "p+";
	else if (id == kPm)              name = "p-";
	else if (id == kN)               name = "N";
	else if (id == kAntiN)           name = "anti-N";
	else if (id == kEp)              name = "e+";
	else if (id == kEm)              name = "e-";
	else if (id == kMup)             name = "mu+";
	else if (id == kMum)             name = "mu-";
	else if (id == kTaup)            name = "tau+";
	else if (id == kTaum)            name = "tau-";
	else if (id == kNuE)             name = "nu";
	else if (id == kNuMu)            name = "nu";
	else if (id == kNuTau)           name = "nu";
	else if (id == kAntiNuE)         name = "nu";
	else if (id == kAntiNuMu)        name = "nu";
	else if (id == kAntiNuTau)       name = "nu";
	else if (id == kF0600)           name = "f0(600)";
	else if (id == kK0)              name = "K0";
	else if (id == kAntiK0)          name = "K0";
	else if (id == kKstarp)          name = "K*+";
	else if (id == kKstarm)          name = "K*-";
	else if (id == kKstar0)          name = "K*0";
	else if (id == kAntiKstar0)      name = "K*0";
	else if (id == kK0star0)         name = "K_0*0";
	else if (id == kAntiK0star0)     name = "Anti-K_0*0";
	else if (id == kK0starp)         name = "K_0*+";
	else if (id == kK0starm)         name = "K_0*-";
	else if (id == kK10   )          name = "K_10";
	else if (id == kK1p   )          name = "K_1+";
	else if (id == kK1m   )          name = "K_1-";
	else if (id == kAntiK10)         name = "anti-K_10";
	else if (id == kLambda)          name = "Lambda";
	else if (id == kALambda)         name = "anti-Lambda";
	else if (id == kD0     )         name = "D0";
	else if (id == kD0bar  )         name = "D0bar";
	else if (id == kDp     )         name = "D+";
	else if (id == kDm     )         name = "D-";
	else if (id == kDsp    )         name = "Ds+";
	else if (id == kDsm    )         name = "Ds-";
	else if (id == kDstarP )         name = "D*+";
	else if (id == kDstarM )         name = "D*-";
	else if (id == kDstar )          name = "D*";
	else if (id == kAntiDstar)       name = "anti-D*";
	else if (id == kDsstarP)         name = "D_s*+";
	else if (id == kDsstarM)         name = "D_s*-";
	else if (id == kY4260  )         name = "Y(4260)";
	else if (id == kY4360  )         name = "Y(4360)";
	else if (id == kPsi4040)         name = "psi(4040)";
	else if (id == kPsi4160)         name = "psi(4160)";
	else if (id == kPsi4415)         name = "psi(4415)";
	else if (id == kDeltapp)         name = "Delta++";
	else if (id == kAntiDeltapp)     name = "Delta--";
	else if (id == kSigma0 )         name = "Sigma0";
	else if (id == kAntiSigma0 )     name = "anti-Sigma0";
	else if (id == kSigmastarm )     name = "Sigma*+";
	else if (id == kAntiSigmastarp ) name = "anti-Sigma*-";
	else if (id == kXi0        )     name = "Xi0";
	else if (id == kAntiXi0        ) name = "anti-Xi0";
	else if (id == kXistarp    )     name = "Xi*+";
	else if (id == kAntiXistarm    ) name = "anti-Xi*-";
	else if (abs(id)<9             ) name = "e+e-";
	else{
		stringstream ss;
		ss << id;
		name = ss.str();
	}
	return name;
}


void
MCTruthHelper::printInformation(int RootID){

	cout << "--------  TRUTH INFORMATION ------------" << endl;
	cout << "MCDecayCode1 = " << MCDecayCode1() << endl;
	cout << "MCDecayCode2 = " << MCDecayCode2() << endl;
	cout << "MCDecayCode3 = " << MCDecayCode3() << endl;
	//cout << "MCDecayCode4 = " << MCDecayCode4() << endl;
	cout << "MCExtras     = " << MCExtras() << endl;
	cout << "----------------------------------------" << endl;
	for (unsigned int i = 0; i < m_mcDecayList.size(); i++) {
		printf("MCDecayParticle%1d = %10s\n",i, particleType(m_mcDecayList[i]).data());
	}
	cout << "----------------------------------------" << endl;
	for (unsigned int i = 0; i < m_mcPList.size(); i++) {
		McParticle* mcp = m_mcPList[i]; 

		int pdgid   =  mcp->particleProperty();
		int mother  = (mcp->mother()).particleProperty();
		if (pdgid == kFSRGamma                ) continue;
		if (pdgid == kGamma  && mother == kPi0) continue;
		if (abs(pdgid)== kEp && mother == kPi0) continue;
		if (RootID==-999 || !(mcp->primaryParticle()) && mcp->decayFromGenerator()){
			if(pdgid!=mother)printf("**  %10s from %10s\n",particleType(mcp).data(), particleType(&(mcp->mother())).data() );
			else             printf("**  %10s from %10s\n",particleType(mcp).data(), "e+e-" );
		}else{
			//cout << particleType(mcp) << endl;
		}
	}
	cout << "----------------------------------------" << endl;
}

