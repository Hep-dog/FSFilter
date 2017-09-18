#include <sstream> 
#include <iostream>
#include "TStopwatch.h"
#include "FSFilter/FSFilter.h"

//********************************************************************
//********************************************************************
//********************************************************************
//
//   CONSTRUCTOR
//
//********************************************************************
//********************************************************************
//********************************************************************

FSFilter::FSFilter(const std::string& name, ISvcLocator* pSvcLocator) :
	Algorithm(name,pSvcLocator) 
{
	//********************************************************************
	//
	//   READ PROPERTIES FROM THE JOB OPTIONS FILE
	//
	//********************************************************************
	// Options and Configuration
	declareProperty("DATAMC",                m_DataMC                = 0       );
	declareProperty("SaveMC",                m_SaveMC                = 1       );
	declareProperty("Golden",                m_Golden                = 1       );
	declareProperty("runNumber",             m_runNo                 = 29677   );
	declareProperty("UseDB",                 m_UseDB                 = 0       );
	declareProperty("UseHis",                m_UseHis                = 0       );
	declareProperty("Debug",                 m_Debug                 = 0       );
	declareProperty("MassCons",              m_MassCons              = 1       );
	declareProperty("UsePid",                m_trackStudies          = 0       );
	declareProperty("pidStudies",            m_pidStudies            = 0       );
	declareProperty("neutralStudies",        m_neutralStudies        = 0       );
	declareProperty("pi0Studies",            m_pi0Studies            = 0       );
	declareProperty("etaStudies",            m_etaStudies            = 0       );
	declareProperty("veeStudies",            m_veeStudies            = 0       );
	declareProperty("YUPING",                m_yuping                = 0       );
	declareProperty("ModeBest",              m_ModeBest              = 1       );
	declareProperty("TightCut",              m_tightcut              = 1       );
	declareProperty("RootID",                m_RootID                = 100443  );
	declareProperty("cmEnergy",              m_cmEnergy              = 3.686093);
	declareProperty("ESpread",               m_ESpread               = 0.000900);
	declareProperty("crossingAngle",         m_crossingAngle         = 0.011   );
	declareProperty("printTruthInformation", m_printTruthInformation = 0       );
	// Cuts of pre-Selection 
	declareProperty("MaxPCut",               m_MaxPCut               = 5.0     );
	declareProperty("MaxECut",               m_MaxECut               = 5.0     );
	declareProperty("MinPCut",               m_MinPCut               = 0.0     );
	declareProperty("MinECut",               m_MinECut               = 0.0     );
	declareProperty("PhotonInBarrel",        m_PhotonInBarrel        = 0       );
	declareProperty("maxExtraTracks",        m_maxExtraTracks        = 10      );
	declareProperty("maxShowers",            m_maxShowers            = 30      );
	declareProperty("maxKinematicFitChi2DOF",m_maxChi2DOF            = 100.0   );
	declareProperty("energyTolerance",       m_energyTolerance       = 0.500   );
	declareProperty("momentumTolerance",     m_momentumTolerance     = 0.500   );
	declareProperty("lowerMissingMass2",     m_lowerMissingMass2     =-25.00   );
	declareProperty("upperMissingMass2",     m_upperMissingMass2     = 25.00   );
	declareProperty("DelMassCut",            m_DelMassCut            = 0.050   );
	declareProperty("KsSigmaCut",            m_KsSigmaCut            = 2.000   );
	//
	// determine which final states to reconstruct
	for (int i = 0; i < MAXFS; i++){ 
		stringstream name;
		name << "FS"; name << i;
		declareProperty(name.str(),m_FSNames[i]="");
		m_CutPass [i]=0;
		m_Checking[i]=0;
		for (int j = 0; j < 20; j++) m_cutpass[i][j]=0;
	}
	//
	// parameters for cuts on intermediate states
	for (int i = 0; i < MAXFS; i++){
		stringstream parname;
		parname << "FSCut";
		parname << i;
		declareProperty(parname.str(),m_FSCuts[i]);
	}
	// Extra mass constrain on final states 
	for (int i = 0; i < MAXFS; i++){
		stringstream parname;
		parname << "FSMaC";
		parname << i;
		declareProperty(parname.str(),m_FSMaCs[i]);
	}
	//
	// parameters for missing mass fits
	for (int i = 0; i < MAXFS; i++){
		stringstream parname;
		parname << "FSMMFit";
		parname << i;
		declareProperty(parname.str(),m_FSMMFits[i]);
	}
	//********************************************************************
	//
	//   INITIALIZE GLOBAL VARIABLES
	//
	//********************************************************************

	// initialize the event counter

	m_eventCounter = 0;

	h_TrkPar_R     = NULL ;
	h_TrkPar_Z     = NULL ;
	h_TrkPar_P     = NULL ;
	h_TrkPar_COS   = NULL ;
	h_TrkPar_PHI   = NULL ;
	h_InfEMC_T     = NULL ;
	h_InfEMC_E     = NULL ;
	h_InfEMC_COS   = NULL ;
	h_InfEMC_PHI   = NULL ;
	h_ComPar_Pi0   = NULL ;
	h_ComPi0_Chi2  = NULL ;
	h_ComPar_Eta   = NULL ;
	h_ComEta_Chi2  = NULL ;
	h_ComPar_Ks    = NULL ;
	h_ComKs_Chi2   = NULL ;
	h_ComPar_Lamb  = NULL ;
	h_ComLam_Chi2  = NULL ;
	h_ComPar_D0    = NULL ;
	h_ComPar_Dp    = NULL ;
	h_ComPar_Dsp   = NULL ;
	h_ComdE_D0     = NULL ;
	h_ComdE_Dp     = NULL ;
	h_ComdE_Dsp    = NULL ;
	h_ComMbc_D0    = NULL ;
	h_ComMbc_Dp    = NULL ;
	h_ComMbc_Dsp   = NULL ;
	//
	dtagTool       = NULL ;
	dtagName       = NULL ;
	m_mcTruthHelper= NULL ;
}


//********************************************************************
//********************************************************************
//********************************************************************
//
//   INITIALIZE
//
//********************************************************************
//********************************************************************
//********************************************************************


StatusCode FSFilter::initialize(){


	//********************************************************************
	//
	//   CREATE TREES AND SET UP FSINFO OBJECTS
	//
	//********************************************************************

	// only reconstruct particles if we need to

	m_findEp        = false;
	m_findEm        = false;
	m_findMup       = false;
	m_findMum       = false;
	m_findPip       = false;
	m_findPim       = false;
	m_findKp        = false;
	m_findKm        = false;
	m_findPp        = false;
	m_findPm        = false;
	m_findGamma     = false;
	m_findPi0       = false;
	m_findEta       = false;
	m_findKs        = false;
	m_findLambda    = false;
	m_findaLambda   = false;
	m_findD0        = false;
	m_findD0bar     = false;
	m_findDp        = false;
	m_findDm        = false;
	m_findDsp       = false;
	m_findDsm       = false;


	m_cpu           = HepVector(10, 0);
	runNoKeep       = m_runNo;
	rscanDQ         = new RscanDQ(m_runNo);
	//double mpsi     = m_cmEnergy;
	//4psi.set(m_cmEnergy*sin(m_crossingAngle),0.0,0.0,m_cmEnergy);
	GetEcmP4();

	if ( m_DataMC==1 ) m_SaveMC=0;

	// create trees for each final state and store them in FSInfo objects
	for (int i = 0; i < MAXFS; i++){
		if (m_FSNames[i] != ""){
			// a tree for reconstructed information
			string ntName("nt");  ntName += m_FSNames[i];
			string ntFullName("FILE1/");  ntFullName += ntName;
			NTupleHelper* nt = new NTupleHelper( ntupleSvc()->book(ntFullName,CLID_ColumnWiseTuple, ntName), p4psi );

			// a tree for generated information
			string ntGenName("ntGEN");  ntGenName += m_FSNames[i];
			NTupleHelper* ntgen = NULL;
			if ( m_DataMC==0 ){
				if (ntGenName.find("EXC") != string::npos){
					ntGenName.erase(ntGenName.find("EXC"),3);
					string ntGenFullName("FILE1/");  ntGenFullName += ntGenName;
					ntgen = new NTupleHelper(ntupleSvc()->book(ntGenFullName, CLID_ColumnWiseTuple, ntGenName), p4psi);
				}
			}
			// create an FSFinfo object
			FSInfo* fsInfo = new FSInfo(m_FSNames[i],nt,ntgen);
			m_FSInfoVector.push_back(fsInfo);

			// check to see which particles we need to reconstruct
			if ( fsInfo->hasParticle("e+"     ) ) m_findEp     = true;
			if ( fsInfo->hasParticle("e-"     ) ) m_findEm     = true;
			if ( fsInfo->hasParticle("mu+"    ) ) m_findMup    = true;
			if ( fsInfo->hasParticle("mu-"    ) ) m_findMum    = true;
			if ( fsInfo->hasParticle("pi+"    ) ) m_findPip    = true;
			if ( fsInfo->hasParticle("pi-"    ) ) m_findPim    = true;
			if ( fsInfo->hasParticle("K+"     ) ) m_findKp     = true;
			if ( fsInfo->hasParticle("K-"     ) ) m_findKm     = true;
			if ( fsInfo->hasParticle("p+"     ) ) m_findPp     = true;
			if ( fsInfo->hasParticle("p-"     ) ) m_findPm     = true;
			if ( fsInfo->hasParticle("gamma"  ) ) m_findGamma  = true;
			if ( fsInfo->hasParticle("pi0"    ) ) m_findPi0    = true;
			if ( fsInfo->hasParticle("eta"    ) ) m_findEta    = true;
			if ( fsInfo->hasParticle("Ks"     ) ) m_findKs     = true;
			if ( fsInfo->hasParticle("Lambda" ) ) m_findLambda = true;
			if ( fsInfo->hasParticle("ALambda") ) m_findaLambda= true;
			if ( fsInfo->hasParticle("D0"     ) ) m_findD0     = true;
			if ( fsInfo->hasParticle("D0bar"  ) ) m_findD0bar  = true;
			if ( fsInfo->hasParticle("D+"     ) ) m_findDp     = true;
			if ( fsInfo->hasParticle("D-"     ) ) m_findDm     = true;
			if ( fsInfo->hasParticle("Ds+"    ) ) m_findDsp    = true;
			if ( fsInfo->hasParticle("Ds-"    ) ) m_findDsm    = true;
		}
	}
	if(m_UseHis) BookHist();
	//********************************************************************
	//
	//   CREATE FSCUT/FSMAC OBJECTS
	//
	//********************************************************************
	for (unsigned int i = 0; i < MAXFS; i++){
		if (m_FSCuts[i] != ""){
			FSCut* fscut = new FSCut(m_FSCuts[i]);
			bool found = false;
			for (unsigned int ifs = 0; ifs < m_FSInfoVector.size(); ifs++){
				if (m_FSInfoVector[ifs]->FSName() == fscut->FSName()){
					m_FSInfoVector[ifs]->addFSCut(fscut);
					found = true;
					break;
				}
			}
			if (!found){
				cout << "FSFilter ERROR: could not find a final state for the " << endl;
				cout << "  FSCut with these arguments: " << endl;
				cout << m_FSCuts[i] << endl;
				cout << "  and final state = " << fscut->FSName() << endl;
				exit(0);
			}
		}
		if (m_FSMaCs[i] != ""){
			FSMaC* fsmac = new FSMaC(m_FSMaCs[i]);
			bool found = false;
			for (unsigned int ifs = 0; ifs < m_FSInfoVector.size(); ifs++){
				if (m_FSInfoVector[ifs]->FSName() == fsmac->FSName()){
					fsmac->Print();
					m_FSInfoVector[ifs]->addFSMaC(fsmac);
					found = true;
					break;
				}
			}
			if (!found){
				cout << "FSFilter ERROR: could not find a final state for the " << endl;
				cout << "  FSMac with these arguments: " << endl;
				cout << m_FSMaCs[i] << endl;
				cout << "  and final state = " << fsmac->FSName() << endl;
				exit(0);
			}
		}

	}
	//********************************************************************
	//
	//   ADD MISSING MASS FITS
	//
	//********************************************************************
	for (unsigned int i = 0; i < MAXFS; i++){
		if (m_FSMMFits[i] != ""){

			vector<string> pars = FSInfo::parseString(m_FSMMFits[i]);

			if (pars.size() != 2){
				cout << "FSFilter ERROR: bad FSMMFit" << i << " parameter: " 
					<< m_FSMMFits[i] << endl;
				exit(0);
			}

			bool found = false;
			for (unsigned int ifs = 0; ifs < m_FSInfoVector.size(); ifs++){
				if (m_FSInfoVector[ifs]->FSName() == pars[0]){
					m_FSInfoVector[ifs]->addMissingParticle(pars[1].c_str());
					cout << "\t\t"<< endl;
					cout << "FSFilter:  Noticing the Final State " << pars[0] <<" missing one "<<pars[1]<< endl;
					m_FSInfoVector[ifs]->Print();
					found = true;
					break;
				}
			}
			if (!found){
				cout << "FSFilter ERROR: could not find a final state for the " << endl;
				cout << "  FSMMFit" << i << " with these arguments: " << endl;
				cout << m_FSMMFits[i] << endl;
				exit(0);
			}else{
				;
			}

		}
	}

	for (unsigned int i = 0; i < m_FSInfoVector.size(); i++){
		FSInfo* fs = m_FSInfoVector[i];
		int n = fs->nMissingParticles();
		if( n>1) {
			printf("\nChannel %3d: %s ",i, fs->FSName().data());
			printf("has %3d missing particles, please check ... \n",n);
			fs->Print();
			exit(1);	
		}		
	} 
	//
	if( m_findD0 || m_findD0bar || m_findDp || m_findDm || m_findDsp || m_findDsm) 
	{ 
		dtagName = new DTagName();
		dtagName->SetOnlyGolden();
	}
	//********************************************************************
	//
	//   PERFORM CHECKS ON THE INPUT AND EXIT IF THERE ARE PROBLEMS
	//
	//********************************************************************

	// make sure all final states are currently supported
	if(m_Debug){
		for (unsigned int i = 0; i < m_FSInfoVector.size(); i++){
			FSInfo* fs = m_FSInfoVector[i];
			vector<string> particleNames = fs->particleNames();
			printf("Channel %3d: %s\n",i, fs->FSName().data());
			fs->Print(); 			
		} 
	}
	cout << "\t\t"<< endl;
	return StatusCode::SUCCESS;
}

//********************************************************************
//********************************************************************
//********************************************************************
//
//   EXECUTE
//
//********************************************************************
//********************************************************************
//********************************************************************
StatusCode FSFilter::execute(){
	//********************************************************************
	//
	//   EXTRACT INFORMATION FROM THE FRAMEWORK
	//
	//********************************************************************


	TStopwatch timer;
	// event header
	m_cutpass[0][0]++;
	if(m_Debug) m_Checking[0]++;
	SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),EventModel::EventHeader);
	if(!eventHeader)    { cout<<"  eventHeader   Failed!"<<endl; return StatusCode::SUCCESS; }
	int runNumber   = eventHeader->runNumber();
	int eventNumber = eventHeader->eventNumber();
	m_eventCounter++;
	if (m_eventCounter % 1000 == 1) 
		printf( "event counter (run, event) = %8d (%8d, %8d)\n", 
				m_eventCounter , runNumber, eventNumber );

	// event information
	SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(), EventModel::EvtRec::EvtRecEvent);
	if(!evtRecEvent )   { cout<<"  evtRecEvent   Failed!"<<endl; return StatusCode::SUCCESS; }
	if(m_Debug>0) printf("\n\nStarting ...%10d %10d %10d %3d\n", runNumber, eventNumber, m_eventCounter, evtRecEvent->totalTracks());

	// track collection
	SmartDataPtr<EvtRecTrackCol> evtRecTrackCol(eventSvc(),  EventModel::EvtRec::EvtRecTrackCol);
	if(!evtRecTrackCol) { cout<<"  evtRecTrkCol  Failed!"<<endl; return StatusCode::SUCCESS; }
	if(evtRecEvent->totalTracks()!=evtRecTrackCol->size())       return StatusCode::SUCCESS;
	if(evtRecEvent->totalTracks()> 50                    )       return StatusCode::SUCCESS;

	// pi0 --> gamma gamma
	SmartDataPtr<EvtRecPi0Col> evtRecPi0Col(eventSvc(), EventModel::EvtRec::EvtRecPi0Col);
	if(!evtRecPi0Col) { cout<<"  evtRecPi0Col  Failed!"<<endl; return StatusCode::SUCCESS; }

	// eta --> gamma gamma
	SmartDataPtr<EvtRecEtaToGGCol> evtRecEtaToGGCol(eventSvc(), EventModel::EvtRec::EvtRecEtaToGGCol);
	if(!evtRecEtaToGGCol) { cout<<"  evtRecEtaToGGCol  Failed!"<<endl; return StatusCode::SUCCESS; }

	// Ks --> pi+ pi- and Lambda --> p+ pi- and ALambda --> p- pi+
	SmartDataPtr<EvtRecVeeVertexCol> evtRecVeeVertexCol(eventSvc(), EventModel::EvtRec::EvtRecVeeVertexCol);
	if(!evtRecVeeVertexCol) { cout<<"  evtRecVeeVertexCol  Failed!"<<endl; return StatusCode::SUCCESS; }
	//
	// Pointer to dtagTool 
	if( m_findD0 || m_findD0bar || m_findDp || m_findDm || m_findDsp || m_findDsm){
		dtagTool = new DTagTool();
		dtagTool->setPID( m_tightcut );
		if( dtagTool->isDTagListEmpty() ){
			if( m_Debug>2 ) cout<<" no D candidates found"<<endl;
		}
	}
	if( runNumber!=runNoKeep){
		runNoKeep=abs(runNumber);
		rscanDQ->init(abs(runNumber));
		GetEcmP4();
	}
	if(m_Debug) m_Checking[1]++;

	// beam spot
	HepPoint3D   vBeamSpot(0., 0., 0.);
	HepSymMatrix evBeamSpot(3, 0);
	evBeamSpot[0][0] = 1.0E+12;
	evBeamSpot[1][1] = 1.0E+12;
	evBeamSpot[2][2] = 1.0E+12;

	if(m_UseDB){
		IVertexDbSvc*  vtxsvc;
		Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
		if(vtxsvc->isVertexValid()){
			double* dbv = vtxsvc->PrimaryVertex(); 
			double*  vv = vtxsvc->SigmaPrimaryVertex();  
			for (unsigned int ivx = 0; ivx < 3; ivx++){
				vBeamSpot[ivx] = dbv[ivx];
				evBeamSpot[ivx][ivx] = vv[ivx] * vv[ivx];
			}
		}
		else{
			cout << "FSFILTER ERROR:  Could not find a vertex from VertexDbSvc" << endl;
			exit(0);
		}
	}
	m_beamSpot.setVx ( vBeamSpot);
	m_beamSpot.setEvx(evBeamSpot);

	if(m_Debug) m_Checking[2]++;

	// beam energy (still doesn't work)

	//IBeamEnergySvc* beamEnergySvc;
	//Gaudi::svcLocator()->service("BeamEnergySvc",beamEnergySvc);
	//cout << endl << endl << endl << "TESTING BEAM ENERGY" << endl;
	//cout << beamEnergySvc->getbeamE() << endl << endl << endl << endl;


	//********************************************************************
	//
	//   PARSE TRUTH INFORMATION AND WRITE TO THE GENERATOR TREES
	//
	//********************************************************************
	if (runNumber > 0 )  m_SaveMC = 0;
	if (runNumber < 0 && m_SaveMC ){
		if(m_Debug>0) {
			cout<< "root particle is " << m_RootID <<" " << m_cmEnergy <<endl;
		}
		// extract truth information from the framework and set up a MCTruthHelper object
		SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(),EventModel::MC::McParticleCol); 
		m_mcTruthHelper = new MCTruthHelper(mcParticleCol, m_RootID);
		if (m_printTruthInformation && m_mcTruthHelper->nDecayParticles()>0){
			m_mcTruthHelper->printInformation(m_RootID);
		}
		//
		// write to the mode-dependent generator trees
		if (m_mcTruthHelper->nDecayParticles()>0){ 
			for (unsigned int ifs = 0; ifs < m_FSInfoVector.size(); ifs++){
				FSInfo* fs = m_FSInfoVector[ifs];
				if(m_Debug>2) {
					printf("\nChannel %3d: %s \n",ifs, fs->FSName().data());
					printf("decaycode1 = %12d\n", fs->decayCode1());
					printf("decaycode2 = %12d\n", fs->decayCode2());
					printf("decaycode3 = %12d\n", fs->decayCode3());
					//printf("decaycode4 = %12d\n", fs->decayCode4());
				}
				if (fs->exclusive() && m_RootID!=-999 &&
						(m_mcTruthHelper->MCDecayCode1() == fs->decayCode1()) &&
						(m_mcTruthHelper->MCDecayCode2() == fs->decayCode2()) &&
						(m_mcTruthHelper->MCDecayCode3() == fs->decayCode3()) &&
						//(m_mcTruthHelper->MCDecayCode4() == fs->decayCode4()) &&
						(m_mcTruthHelper->MCExtras()     == 0)
					)
				{
					NTupleHelper* nt = fs->NTGen();
					nt->fillEvent  (eventHeader, evtRecEvent, m_cmEnergy);
					nt->fillMCTruth(m_mcTruthHelper, fs, m_RootID,  "MC");
					nt->write();
				}
			}
		}
		//
		//does this generated event make sense???
		double mcTotalEnergy = m_mcTruthHelper->MCTotalEnergy();
		if (m_Debug>2 &&(mcTotalEnergy > 1.1*m_cmEnergy || mcTotalEnergy < 0.9*m_cmEnergy)){
			printf("FSFilter SKIPPING EVENT, Total ENERGY=%11.4f" , mcTotalEnergy       );
			printf("RUN   NUMBER                         = %10d"  , runNumber           );
			printf("EVENT NUMBER                         = %10d"  , eventNumber         );
			printf("FLAG 1                               = %10d"  , eventHeader->flag1());
			printf("FLAG 2                               = %10d"  , eventHeader->flag2());
			m_mcTruthHelper->printInformation(m_RootID);
			return StatusCode::SUCCESS;
		}
	}
	if(m_Debug) m_Checking[3]++;

	//********************************************************************
	//
	//   MAKE INITIAL REQUIREMENTS TO SPEED PROCESSING
	//
	//********************************************************************
	// check the total number of showers

	if (evtRecEvent->totalNeutral() > m_maxShowers){ 
		CleanEvt();	return StatusCode::SUCCESS;}
	if(m_Debug) m_Checking[4]++;
	//********************************************************************
	//
	//   CREATE LISTS OF PARTICLES
	//
	//********************************************************************
	// get Track and showers 
	timer.Start();
	GetTrackAndShower(evtRecTrackCol, evtRecEvent->totalCharged());
	timer.Stop(); m_cpu[0] += timer.CpuTime();
	if( m_MaximumP>m_MaxPCut || m_MaximumE>m_MaxECut || m_MaximumP<m_MinPCut || m_MaximumE<m_MinECut  ) {
		CleanEvt();	return StatusCode::SUCCESS;}
	m_cutpass[0][1]++;
	nGAM=gammaList.size();
	//
	//
	timer.Start();
	// get etas
	if (m_findEta){GetEta(evtRecEtaToGGCol)  ;}
	// get pi0s
	if (m_findPi0){GetPi0(evtRecPi0Col)      ;}
	// get kshorts
	if (m_findKs ){GetKs (evtRecVeeVertexCol);}
	// get Lambdas
	if (m_findLambda || m_findaLambda ){GetLambda(evtRecVeeVertexCol);}
	timer.Stop(); m_cpu[1] += timer.CpuTime();
	// get D mesons 
	timer.Start();
	if ( m_findD0    ) GetDmeson(Mass("D0"   ),   0, 34,  0, "D0"   );
	if ( m_findD0bar ) GetDmeson(Mass("D0bar"),   0, 34,  0, "D0bar");
	if ( m_findDp    ) GetDmeson(Mass("D+"   ),  34, 57, +1, "D+"   );
	if ( m_findDm    ) GetDmeson(Mass("D-"   ),  34, 57, -1, "D-"   );
	if ( m_findDsp   ) GetDmeson(Mass("Ds+"  ),  57, 82, +1, "Ds+"  );
	if ( m_findDsm   ) GetDmeson(Mass("Ds-"  ),  57, 82, -1, "Ds-"  );
	timer.Stop(); m_cpu[2] += timer.CpuTime();
	//
	// get Jpsi, psi(2S), chi_c1, and h_c  
	// To be done. J/psi, psi(2S), chi_c1, h_c and nu have to be set missing at present	
	//
	DictPList.insert(pair<string, vector<FSParticle*> > ("gamma"  , gammaList  )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("pi-"    , pimList    )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("pi+"    , pipList    )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("K+"     , kpList     )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("K-"     , kmList     )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("p+"     , ppList     )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("p-"     , pmList     )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("e+"     , epList     )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("e-"     , emList     )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("mu+"    , mupList    )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("mu-"    , mumList    )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("eta"    , etaList    )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("pi0"    , pi0List    )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("Ks"     , ksList     )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("Lambda" , lambdaList )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("aLambda", alambdaList)); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("D0"     , D0List     ));
	DictPList.insert(pair<string, vector<FSParticle*> > ("D0bar"  , D0barList  )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("D+"     , DpList     )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("D-"     , DmList     )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("Ds+"    , DspList    )); 
	DictPList.insert(pair<string, vector<FSParticle*> > ("Ds-"    , DsmList    ));
	// 
	//********************************************************************
	//
	//   LOOP OVER FINAL STATES
	//
	//********************************************************************

	for (unsigned int ifs = 0; ifs < m_FSInfoVector.size(); ifs++){
		m_cutpass[ifs][2]++;

		// get information about this final state
		FSInfo* fsinfo                = m_FSInfoVector[ifs];
		NTupleHelper* NT              = fsinfo->NT();
		bool exclusive                = fsinfo->exclusive();
		bool inclusive                = fsinfo->inclusive();
		vector<string> particleNames  = fsinfo->particleNames();
		vector<int>    particleStatus = fsinfo->particleStatus();

		// check number of tracks
		if (exclusive){
			if (evtRecEvent->totalCharged() > fsinfo->nChargedParticles()+m_maxExtraTracks) continue;
		}
		m_cutpass[ifs][3]++;

		//********************************************************************
		//
		//   PUT TOGETHER ALL COMBINATIONS OF PARTICLES FOR THIS FINAL STATE
		//
		//********************************************************************
		timer.Start();
		vector< vector< FSParticle* > > pCombos; pCombos.clear();
		for (unsigned int ifsp = 0; ifsp < particleNames.size(); ifsp++){
			int   status = particleStatus[ifsp];
			vector< FSParticle* >  pList ; pList.clear(); 
			if( status == 1 ) pList  = DictPList[particleNames[ifsp]];
			else{
				pList.push_back(new FSParticle(particleNames[ifsp], true));
				ParticleTrash.push_back(pList[0]); // save address for releasing memory
			}
			vector< vector< FSParticle* > > pCombosTemp = pCombos; pCombos.clear();
			if  ( pList.size() == 0 ) break;
			for ( unsigned int ipl = 0; ipl < pList.size(); ipl++ ){
				if ( ifsp == 0 ) {
					vector< FSParticle* > combo1; combo1.clear();
					combo1.push_back(pList[ipl]); 
					if (checkCombination(combo1,(combo1.size()==particleNames.size()),fsinfo->inclusive()||fsinfo->missingMassFit() ))
						pCombos.push_back(combo1);
				} 
				else 
				{
					for (unsigned int itc = 0; itc < pCombosTemp.size(); itc++){
						vector< FSParticle* > combo2 = pCombosTemp[itc];
						bool duplicate = false;
						if  ( !pList[ipl]->missed() ) {  
							for (unsigned int ic = 0; ic < combo2.size(); ic++){
								if ( combo2[ic]->missed() ) continue;
								bool shared = pList[ipl]->duplicate(combo2[ic]);
								if ( shared ) { duplicate = true; break; }
							}
							if ( duplicate ) continue;
						}
						combo2.push_back(pList[ipl]); 
						if (checkCombination(combo2,(combo2.size()==particleNames.size()),fsinfo->inclusive()||fsinfo->missingMassFit() ))
							pCombos.push_back(combo2);
						if (pCombos.size() > 100000) break;
					}
				}
				if (pCombos.size() > 100000) break;
			}
			if (pCombos.size() > 100000) break;
		}
		timer.Stop();
		m_cpu[3] += timer.CpuTime();
		//	
		if(m_Debug>1)
			printf("Channel: %20s, No. = %10d, Size of pCombos is %4d\n",
					fsinfo->FSName().data(), ifs, pCombos.size()); 
		if( pCombos.size() ==  0) continue;
		if( pCombos.size() >99999) {
			printf("FSFilter WAENING: possible combination is too many, %5d, Skipping ... \n",(int)pCombos.size());
			cout << "\tRun      = " << runNumber;
			cout << ", Event    = " << eventNumber;
			cout << ", NTracks  = " << evtRecEvent->totalCharged();
			cout << ", NShowers = " << evtRecEvent->totalNeutral() << endl;
			cout << "\t\tFINAL STATE = " << fsinfo->FSName() << endl;
			continue;
		}
		m_cutpass[ifs][4]++;
		//********************************************************************
		//
		//   LOOP OVER PARTICLE COMBINATIONS
		//
		//********************************************************************
		//********************************************************************
		//
		for (unsigned int i = 0; i < pCombos.size(); i++){
			m_cutpass[ifs][5]++;
			vector<FSParticle*> combo = pCombos[i];
			double ntrk = GetTotalNoOfTrack(combo); // expected nTrk
			double ngam = GetTotalNoOfGamma(combo); // expected nGam
			double nvee = nVee             (combo); // expected nVee 
			if (exclusive){
				if (evtRecEvent->totalCharged() > ntrk + m_maxExtraTracks) continue;
				if (nGAM                        > ngam + m_maxExtraTracks) continue;
			}
			//********************************************************************
			//
			//   CUT ON THE TOTAL ENERGY AND MOMENTUM TO SAVE TIME
			//
			//********************************************************************

			HepLorentzVector totalP4(0.0, 0.0, 0.0, 0.0);
			for (int t = 0; t < combo.size(); t++){
				if(!combo[t]->missed() ) totalP4 += combo[t]->rawFourMomentum();
				if( combo[t]->dmes()   ) combo[t]->dmesClear();
			}
			for (int t = 0; t < combo.size(); t++){
				if( combo[t]->missed() ) combo[t]->setRawFourMomentum (p4psi-totalP4);
			}
			double missingEnergy = (p4psi-totalP4).  e();
			double missingMass   = (p4psi-totalP4).  m();
			double missingMass2  = (p4psi-totalP4). m2();
			if(m_Debug>3) printf("totp4 = %10.4f %10.4f %10.4f %10.4f\n",totalP4.px(), totalP4.py(), totalP4.pz(), totalP4.e());
			//
			if (exclusive ){
				if( fsinfo->missingMassFit() ){
					if(fabs(missingMass-fsinfo->missingMassValue())>m_energyTolerance)continue;
				}	
				else if (fabs(missingEnergy)                      >m_energyTolerance)continue;
			}
			m_cutpass[ifs][6]++;
			//
			if (exclusive && !fsinfo->missingMassFit() ){
				double missingP = (p4psi-totalP4).rho();	
				if (fabs(missingP)>m_momentumTolerance) continue;
			}
			m_cutpass[ifs][7]++;
			//
			if (inclusive){
				if (missingMass2 < m_lowerMissingMass2) continue;
				if (missingMass2 > m_upperMissingMass2) continue;
			}
			m_cutpass[ifs][8]++;

			//********************************************************************
			//
			//   MAKE CUTS ON INTERMEDIATE PARTICLE COMBINATIONS (RAW 4-VECTORS)
			//
			//********************************************************************

			if (!(fsinfo->evaluateFSCuts(combo,p4psi,"Raw"))) continue;
			m_cutpass[ifs][9]++;

			//********************************************************************
			//
			//   DO THE PRIMARY VERTEX FITTING
			//
			//********************************************************************
			VertexParameter primaryVertex(m_beamSpot);

			// set up a helper vertex with large errors

			VertexParameter wideVertex;
			HepPoint3D vWideVertex(0., 0., 0.);
			HepSymMatrix evWideVertex(3, 0);

			evWideVertex[0][0] = 1.0e12;
			evWideVertex[1][1] = 1.0e12;
			evWideVertex[2][2] = 1.0e12;

			wideVertex.setVx(vWideVertex);
			wideVertex.setEvx(evWideVertex);
			// set up for a primary vertex fit

			VertexFit* vtxfit = VertexFit::instance();
			vtxfit->init();

			// only do the vertex fit if there are at least two tracks
			// coming from the primary; otherwise primaryVertex will 
			// contain the beamSpot

			bool doVertexFit = false;
			int vtxFitTrack = 0;
			for (unsigned int j = 0; j < combo.size(); j++){
				FSParticle* fsp = combo[j];
				if (fsp->missed()) continue;
				if (fsp->track()) vtxFitTrack+=1;
				if (fsp->dmes ()){
					int ntracks  = fsp-> dmesNTracks(); 
					int nKs      = fsp-> dmesnKs    (); 	
					vtxFitTrack += (ntracks-2*nKs);
				}
			}
			if( m_Debug>3     ) printf("vtxFitTracks =  %5d\n",vtxFitTrack);	
			if( vtxFitTrack >1) doVertexFit = true;

			if (doVertexFit){
				// add tracks that come from the primary
				vtxFitTrack = 0;
				vector<int> vtxList; vtxList.clear();
				for (unsigned int j = 0; j < combo.size(); j++){
					FSParticle* fsp = combo[j];
					if(m_Debug>1) printf("name %9s, no. = %2d, status = %2d\n", fsp->name().data(), j, fsp->missed());
					if (fsp->missed()) continue;
					if (fsp->track() ){
						vtxList.push_back(vtxFitTrack);
						vtxfit->AddTrack (vtxFitTrack++,fsp->initialWTrack());
					}
					if ( fsp->dmes() ){
						int ntracks  = fsp-> dmesNTracks(); 
						int nKs      = fsp-> dmesnKs    (); 	
						if( ntracks>2*nKs ){
							vector<WTrackParameter> dmesInitialWTrack = fsp->dmesInitialWTrack();
							for(int iw=2*nKs; iw<ntracks; iw++){
								vtxList.push_back(vtxFitTrack);
								vtxfit->AddTrack (vtxFitTrack++, dmesInitialWTrack[iw]);
							}
						}	
					}
				}

				// add the initial vertex with large errors
				vtxfit->AddVertex(0, wideVertex, vtxList);

				// do the fit
				timer.Start();
				bool VFITOK = vtxfit->Fit(0);
				timer.Stop();
				m_cpu[6] += timer.CpuTime();
				if( !VFITOK   ) continue;
				if( m_Debug>2 ) printf("V: chisq =  %9.5f\n", vtxfit->chisq(0)); 
				vtxfit->Swim(0);

				// save track parameters after the vertex fit
				vtxFitTrack = 0;
				for (unsigned int j = 0; j < combo.size(); j++){
					FSParticle* fsp = combo[j];
					if (fsp->missed()) continue;
					if (m_Debug>3)printf("V j= %2d, fsp->dmes() = %d\n", j, fsp->dmes());
					if (fsp->track() ) fsp->setVertexFitWTrack(vtxfit->wtrk(vtxFitTrack++));
					if (fsp->dmes()  ) {
						int ntracks  = fsp-> dmesNTracks (); 	
						int nshowers = fsp-> dmesNShowers(); 
						int nKs      = fsp-> dmesnKs     (); 	
						if( m_Debug>2 )printf("V: The meson is %8s, tagmode, ntrk, nneu, mass = %3d, %3d, %3d, %8.5f\n",
								((fsp->name()).data()), fsp->dmesTagmode(), ntracks, nshowers, Mass(fsp->name())); 
						if(ntracks>0){
							vector<WTrackParameter> vertexfitwtracks; vertexfitwtracks.clear(); 
							if(m_Debug>2)printf("V ntracks =  %3d, wtracks = %3d\n", ntracks, vertexfitwtracks.size());
							for(int iw=2*nKs;iw<ntracks; iw++){
								vertexfitwtracks.push_back(vtxfit->wtrk(vtxFitTrack++));
							}
							if(m_Debug>2)printf("V ntracks =  %3d, wtracks = %3d\n", ntracks, vertexfitwtracks.size());
							fsp->setdmesVertexFitWTracks(vertexfitwtracks); // save and added to m_vtxFourMomentum
							FreeAll(vertexfitwtracks); 
						}	
					}
				}
				// save the primary vertex
				primaryVertex.setVx (vtxfit-> Vx(0));
				primaryVertex.setEvx(vtxfit->Evx(0));
				FreeAll(vtxList);
			}else if ( vtxFitTrack==1 ){ // only one charged track except pi and p from Ks and Lambda
				vtxFitTrack = 0;
				for (unsigned int j = 0; j < combo.size(); j++){
					FSParticle* fsp = combo[j];
					if (fsp->missed()) continue;
					if (m_Debug>3)printf("V j= %2d, fsp->dmes() = %d\n", j, fsp->dmes());
					if (fsp->track() ) {
						vtxFitTrack++;
						fsp->setVertexFitWTrack(fsp->initialWTrack());
					}
					if (fsp->dmes()  ) {
						int ntracks  = fsp-> dmesNTracks (); 	
						int nshowers = fsp-> dmesNShowers(); 
						int nKs      = fsp-> dmesnKs     (); 	
						vector<WTrackParameter> dmesinitialwtrack = fsp->dmesInitialWTrack();
						if( m_Debug>2 )printf("V: The meson is %8s, tagmode, ntrk, nneu, mass = %3d, %3d, %3d, %8.5f\n",
								((fsp->name()).data()), fsp->dmesTagmode(), ntracks, nshowers, Mass(fsp->name())); 
						if(ntracks>0){
							vector<WTrackParameter> vertexfitwtracks; vertexfitwtracks.clear(); 
							if(m_Debug>2)printf("V ntracks =  %3d, wtracks = %3d\n", ntracks, vertexfitwtracks.size());
							for(int iw=2*nKs;iw<ntracks; iw++){
								vtxFitTrack++;
								vertexfitwtracks.push_back(dmesinitialwtrack[iw]);
							}
							if(m_Debug>2)printf("V ntracks =  %3d, wtracks = %3d\n", ntracks, vertexfitwtracks.size());
							fsp->setdmesVertexFitWTracks(vertexfitwtracks);
							FreeAll(vertexfitwtracks); 
						}	
					}
				}
				if(vtxFitTrack!=1)printf("vtxFitTrack should be 1, but it is %3d\n", vtxFitTrack);
				// take the beamspot as the vertex  
				primaryVertex.setVx (m_beamSpot. vx());
				primaryVertex.setEvx(m_beamSpot.Evx());
			}

			//********************************************************************
			//
			//   DO THE SECONDARY VERTEX FITTING
			//
			//********************************************************************
			// loop over secondary vertices

			for (unsigned int j = 0; j < combo.size(); j++){
				if (combo[j]->missed()) continue;
				if (combo[j]->dmes()  ){
					FSParticle* fsp = combo[j];
					int ntracks  = fsp-> dmesNTracks(); 
					int nKs      = fsp-> dmesnKs    (); 
					if(m_Debug>2)printf("ntracks, nKs =  %5d %5d\n",ntracks, nKs);	
					vector<WTrackParameter> dmesinitialwtrack = fsp->dmesInitialWTrack();
					vector<double>          dmesLSigma      ; dmesLSigma      .clear();
					vector<WTrackParameter> vertexfitwtracks; vertexfitwtracks.clear(); 
					vector<WTrackParameter> vertexfitwtrack ; vertexfitwtrack .clear(); 
					for(int ik=0; ik<nKs; ik++){
						VertexFit* vtxfit2 = VertexFit::instance();
						vtxfit2->init();

						// add the daughters
						vtxfit2->AddTrack(0,dmesinitialwtrack[ik*2+0]);
						vtxfit2->AddTrack(1,dmesinitialwtrack[ik*2+1]);

						// add an initial vertex with large errors
						vtxfit2->AddVertex(0, wideVertex, 0, 1);

						// do the fit
						timer.Start();
						vtxfit2->Fit(0);
						vtxfit2->Swim(0);
						vtxfit2->BuildVirtualParticle(0);
						timer.Stop();
						m_cpu[4] += timer.CpuTime();

						// now initialize a second vertex fit

						SecondVertexFit* svtxfit = SecondVertexFit::instance();
						svtxfit->init();

						// add the primary vertex

						svtxfit->setPrimaryVertex(primaryVertex);

						// add the secondary vertex

						svtxfit->setVpar(vtxfit2->vpar(0));

						// add the Ks or lambda

						svtxfit->AddTrack(0,vtxfit2->wVirtualTrack(0));

						// do the second vertex fit

						timer.Start();
						svtxfit->Fit();
						timer.Stop();
						m_cpu[5] += timer.CpuTime();

						// save the new ks parameters
						vertexfitwtracks.push_back(vtxfit2->wtrk(0));
						vertexfitwtracks.push_back(vtxfit2->wtrk(1));
						vertexfitwtrack .push_back(svtxfit->wpar() );
						dmesLSigma.push_back(svtxfit->decayLength()/svtxfit->decayLengthError());
					}
					fsp->setdmesVertexFitWTracks(vertexfitwtracks); // save and added to m_vtxFourMomentum
					fsp->setdmesVertexFitWTrack (vertexfitwtrack ); // just save 2nd vertex track
					fsp->setdmesLSigma          (dmesLSigma      );
					FreeAll(dmesinitialwtrack);
					FreeAll(dmesLSigma       );
					FreeAll(vertexfitwtracks );
					FreeAll(vertexfitwtrack  );
				}
				if (combo[j]->vee()){
					FSParticle* fsp = combo[j];

					// initialize a vertex fit for Ks --> pi+ pi- 
					//  or Lambda --> p+ pi- or ALambda --> p- pi+

					VertexFit* vtxfit2 = VertexFit::instance();
					vtxfit2->init();

					// add the daughters

					vtxfit2->AddTrack(0,fsp->veeInitialWTrack1());
					vtxfit2->AddTrack(1,fsp->veeInitialWTrack2());

					// add an initial vertex with large errors

					vtxfit2->AddVertex(0, wideVertex, 0, 1);

					// do the fit

					timer.Start();
					bool OKst = vtxfit2->Fit(0);
					if(m_Debug>3) printf("1st vtxfit: Chi2 = %10.0f, status = %2d \n", vtxfit2->chisq(), OKst);
					//if( !OKst ) continue;
					vtxfit2->Swim(0);
					vtxfit2->BuildVirtualParticle(0);
					timer.Stop();
					m_cpu[4] += timer.CpuTime();

					// now initialize a second vertex fit
					SecondVertexFit* svtxfit = SecondVertexFit::instance();
					svtxfit->init();

					// add the primary vertex
					svtxfit->setPrimaryVertex(primaryVertex);

					// add the secondary vertex
					svtxfit->setVpar(vtxfit2->vpar(0));

					// add the Ks or lambda

					svtxfit->AddTrack(0,vtxfit2->wVirtualTrack(0));

					// do the second vertex fit
					timer.Start();
					svtxfit->Fit();
					timer.Stop();
					m_cpu[5] += timer.CpuTime();

					// save the new ks parameters
					fsp->setVeeVertexFitWTrack1(vtxfit2->wtrk(0));
					fsp->setVeeVertexFitWTrack2(vtxfit2->wtrk(1));
					fsp->setVeeVertexFitWTrack (svtxfit->wpar());
					fsp->setVeeLSigma(svtxfit->decayLength()/svtxfit->decayLengthError());
					if(m_Debug>3) printf("2nd vtxfit: Chi2 = %10.0f, len = %10.4f, sigma = %10.4f\n",svtxfit->chisq(), svtxfit->decayLength(), svtxfit->decayLengthError());
				}
			}
			m_cutpass[ifs][10]++;

			//********************************************************************
			//
			//   SAVE INTERMEDIATE 4-VECTORS
			//
			//********************************************************************
			HepLorentzVector VtotP4(0.0, 0.0, 0.0, 0.0);
			for (unsigned int j = 0; j < combo.size(); j++){
				FSParticle* fsp = combo[j];
				if (fsp->missed())continue; 
				if (fsp->shower()){
					fsp->setIntFourMomentum(fsp->rawFourMomentum());
				}
				if (fsp->track()){
					fsp->setIntFourMomentum(fsp->vertexFitWTrack().p());
				}
				if (fsp->pi0()){
					fsp->setIntFourMomentum (fsp->pi0()->loPfit()+fsp->pi0()->hiPfit());
				}
				if (fsp->eta()){
					fsp->setIntFourMomentum (fsp->eta()->loPfit()+fsp->eta()->hiPfit());
				}
				if (fsp->vee()){
					fsp->setIntFourMomentum (fsp->veeVertexFitWTrack().p());
				}
				if (fsp->dmes()){
					;// done already for D candidates 
				}
				VtotP4 += fsp->intFourMomentum();
			}
			for (unsigned int j = 0; j < combo.size(); j++){
				FSParticle* fsp = combo[j];
				if(fsp->missed()) fsp->setIntFourMomentum (p4psi-VtotP4);
			}
			//********************************************************************
			//
			//   MAKE CUTS ON INTERMEDIATE PARTICLE COMBINATIONS (INT 4-VECTORS)
			//
			//********************************************************************

			if (!(fsinfo->evaluateFSCuts(combo,p4psi,"Int"))) continue;
			m_cutpass[ifs][11]++;
			//********************************************************************
			//
			//   DO THE 1C KINEMATIC FITTING on D mesons and save the 4 momentum and chisq
			//
			//********************************************************************

			//********************************************************************
			//
			//   DO THE KINEMATIC FITTING
			//
			//********************************************************************

			// initialize
			KalmanKinematicFit* kmfit = KalmanKinematicFit::instance();
			//KinematicFit* kmfit = KinematicFit::instance();
			kmfit->init();

			// add the beam spot or the vertex or anything??
			kmfit->setBeamPosition (m_beamSpot. vx());
			kmfit->setVBeamPosition(m_beamSpot.Evx());
			kmfit->setEspread(m_ESpread);

			// add final state particles
			int kinFitTrack = 0;
			int kinFitDOF   = 0;
			int kinFitConstraint = 0;
			vector<int> exList; exList.clear();
			for (unsigned int j = 0; j < combo.size(); j++){
				FSParticle* fsp = combo[j];
				if ( fsinfo->extracons() && (fsp->missed() || fsp->shower() || fsp->track()) ){
					if( fsinfo->IsItInTheDaughgerList(fsp->name()) ) exList.push_back(kinFitTrack);
				}
				if (fsp->missed()){
					kmfit->AddMissTrack(kinFitTrack++, fsp->mass());
				}	
				if (fsp->shower()){
					kmfit->AddTrack(kinFitTrack++,0.0,fsp->shower());
				}
				if (fsp->track()){
					kmfit->AddTrack(kinFitTrack++,fsp->vertexFitWTrack());
				}
				if (fsp->pi0()  ){
					kmfit->AddTrack(kinFitTrack++,0.0,fsp->pi0Lo());
					kmfit->AddTrack(kinFitTrack++,0.0,fsp->pi0Hi());
					if(m_MassCons && !fsinfo->IsItInTheDaughgerList(fsp->name()) ){
						kmfit->AddResonance(kinFitConstraint++,fsp->mass(),kinFitTrack-2,kinFitTrack-1);
						kinFitDOF++;
					}else if ( fsinfo->IsItInTheDaughgerList(fsp->name()) ){
						exList.push_back(kinFitTrack-2);
						exList.push_back(kinFitTrack-1);
					}	
				}
				if (fsp->eta() ){
					kmfit->AddTrack(kinFitTrack++,0.0,fsp->etaLo());
					kmfit->AddTrack(kinFitTrack++,0.0,fsp->etaHi());
					if(m_MassCons && !fsinfo->IsItInTheDaughgerList(fsp->name()) ){
						kmfit->AddResonance(kinFitConstraint++,fsp->mass(),kinFitTrack-2,kinFitTrack-1);
						kinFitDOF++;
					}else if ( fsinfo->IsItInTheDaughgerList(fsp->name()) ){
						exList.push_back(kinFitTrack-2);
						exList.push_back(kinFitTrack-1);
					}
				}
				if (fsp->vee() ){
					kmfit->AddTrack(kinFitTrack++,fsp->veeVertexFitWTrack1());
					kmfit->AddTrack(kinFitTrack++,fsp->veeVertexFitWTrack2());
					if(m_MassCons && !fsinfo->IsItInTheDaughgerList(fsp->name()) ){
						kmfit->AddResonance(kinFitConstraint++,fsp->mass(),kinFitTrack-2, kinFitTrack-1);
						//kmfit->AddTrack(kinFitTrack++,fsp->veeVertexFitWTrack());
						kinFitDOF++;
					}else if ( fsinfo->IsItInTheDaughgerList(fsp->name()) ){
						exList.push_back(kinFitTrack-2);
						exList.push_back(kinFitTrack-1);
					}
				}
				if (fsp->dmes()){
					int ntracks  = fsp-> dmesNTracks (); 
					int nshowers = fsp-> dmesNShowers(); 
					vector<WTrackParameter> dmesVertexFitWTracks = fsp->dmesVertexFitWTracks(); 
					vector<RecEmcShower*>   dmesshowers          = fsp->dmesShowers();
					//
					if( m_Debug>2 ) printf("check:  ntracks =  %3d, wtracks = %3d\n", ntracks, dmesVertexFitWTracks.size());
					//
					vector<int> trkl; trkl.clear();
					HepLorentzVector p4D(0,0,0,0);
					if( ntracks>0 ){
						for(int iw=0; iw<ntracks; iw++){
							trkl.push_back(kinFitTrack);
							kmfit->AddTrack (kinFitTrack++,dmesVertexFitWTracks[iw]);
							if( m_Debug>2 ) {
								HepLorentzVector p = dmesVertexFitWTracks[iw].p();
								p4D+=p;
								printf("K: tracks  %3d, mass %9.5f %9.5f %9.5f %9.5f %9.5f\n", 
										kinFitTrack, dmesVertexFitWTracks[iw].mass(), p.x(), p.y(), p.z(), p.e()); 
							}
						}
					}	
					if( nshowers>0 ){
						for(int iw=0; iw<nshowers; iw++){
							trkl.push_back(kinFitTrack);
							kmfit->AddTrack (kinFitTrack++, 0.0, dmesshowers[iw]);
							if( m_Debug>2 ) {
								const RecEmcShower p = *(dmesshowers[iw]);
								HepLorentzVector psh(
										p.energy()*sin(p.theta())*cos(p.phi()), 
										p.energy()*sin(p.theta())*sin(p.phi()),
										p.energy()*cos(p.theta()), 
										p.energy());
								p4D+=psh;
								printf("K: showers %3d, mass %9.5f %9.5f %9.5f %9.5f %9.5f\n", kinFitTrack, 0.0, psh.x(), psh.y(), psh.z(), psh.e());
							}	
						}
					}
					if(m_MassCons){
						kmfit->AddResonance(kinFitConstraint++, fsp->mass(), trkl);
						kinFitDOF++;
						if( m_Debug>2 ) { for(int ik=0; ik<trkl.size(); ik++) cout<<trkl[ik]<<" "; cout<<endl;}
					}
					if( m_Debug>2 ) printf("K: The meson is %8s, tagmode, ntrk, nneu, mass = %3d, %3d, %3d, %9.5f, %9.5f, %9.5f\n", 
							(fsp->name()).data(),fsp->dmesTagmode(), ntracks, nshowers, 
							fsp->mass(), fsp->dmesMass(), p4D.m());
				}
			}
			// add the extra mass constraint 
			if ( fsinfo->extracons() && exList.size()>1 ){
				kmfit->AddResonance(kinFitConstraint++, fsinfo->MassCons(), exList);
				if( m_Debug>2 ) {
					printf("FSFilter: constrain ");
					for(int ic=0; ic<exList.size(); ic++)
						printf("%3d",exList[ic]); 
					printf(" to %9.4f\n",fsinfo->MassCons());
				}
			}
			// add the initial four momentum
			if ( fsinfo->constrain4Mom() ){
				kmfit->AddFourMomentum(kinFitConstraint++, p4psi);
				if( fsinfo->missingMassFit() ) kinFitDOF += 1;
				else                           kinFitDOF += 4;
			}
			// do the fit and make a very loose cut on the resulting chi2
			if (kinFitConstraint>0){
				timer.Start();
				kmfit->setChisqCut(m_maxChi2DOF*kinFitDOF);
				bool KFITOK = kmfit->Fit();
				timer.Stop();
				m_cpu[7] += timer.CpuTime();
				if( m_Debug>2 ) printf("K: chisq =  %9.5f\n", kmfit->chisq()); 
				if( exclusive && !KFITOK   ) continue;
				m_cutpass[ifs][12]++;
				if( exclusive && (kmfit->chisq()/kinFitDOF>m_maxChi2DOF || kmfit->chisq()<0) ) continue;
				m_cutpass[ifs][13]++;
			}else{
				m_cutpass[ifs][12]++;
				m_cutpass[ifs][13]++;
			}
			//
			if (kinFitConstraint > 0){ //if no 4-momentum constraint, the fitted 4-momentum seems strange, need more check for inclusive analysis. In this case, the fitted p4 will not be used.
				kinFitTrack = 0;
				for (unsigned int j = 0; j < combo.size(); j++){
					FSParticle* fsp = combo[j];
					if (fsp->missed()){
						if (exclusive || fsinfo->constrain4Mom() )
						{
							fsp->setFitFourMomentum(kmfit->pfit(kinFitTrack++));
						}else{
							fsp->setFitFourMomentum(HepLorentzVector(0.0,0.0,0.0,0.0));
							kinFitTrack++;
						}
					}
					if (fsp->shower() || fsp->track()){
						if ( fsinfo->constrain4Mom() ){
							fsp->setFitFourMomentum ( kmfit->pfit(kinFitTrack++) );
						}else{
							fsp->setFitFourMomentum ( fsp->intFourMomentum()     );
						}
					}
					if (fsp->pi0() || fsp->eta() || fsp->vee() ){
						fsp->setFitFourMomentum ( kmfit->pfit(kinFitTrack++) + kmfit->pfit(kinFitTrack++) );
					}
					if (fsp->dmes()){
						int ntracks  = fsp-> dmesNTracks (); 	
						int nshowers = fsp-> dmesNShowers(); 	
						int nKs      = fsp-> dmesnKs(); 	
						HepLorentzVector p4t(0,0,0,0);	
						for(int iw=0; iw<ntracks+nshowers; iw++){
							p4t += kmfit->pfit(kinFitTrack+iw);
						}
						fsp->setFitFourMomentum (p4t);
						kinFitTrack += (ntracks+nshowers);
					}	
				}
			}
			//********************************************************************
			//
			//   MAKE CUTS ON INTERMEDIATE PARTICLE COMBINATIONS (FIT 4-VECTORS)
			//
			//********************************************************************

			if (exclusive && !(fsinfo->evaluateFSCuts(combo,p4psi,"Fit"))) continue;
			m_cutpass[ifs][14]++;

			//********************************************************************
			//
			//   RECORD INFORMATION
			//
			//********************************************************************
			// record event level information

			timer.Start();
			if( m_Debug>2 ) printf("F: fill 4 ... %3d %3d\n",i, ifs); 
			NT->fillEvent(eventHeader, evtRecEvent, m_cmEnergy, nTRK, nGAM);
			NT->fillJPsiFinder(evtRecTrackCol);
			NT->fillJPsiFinder(evtRecPi0Col);
			if (runNumber < 0 && m_SaveMC && m_RootID != -999) 
				NT->fillMCTruthDT(m_mcTruthHelper, fsinfo, m_RootID);

			if( m_Debug>2 ) printf("F: fill 4 ... global\n");

			// record odds and ends that have no other place
			NT->fillDouble("ntrk",           ntrk         );
			NT->fillDouble("ngam",           ngam         );
			NT->fillDouble("nvee",           nvee         );
			NT->fillDouble("MissingMass2",   missingMass2 );
			NT->fillDouble("TotalP",         totalP4.mag());
			NT->fillDouble("MaxP",           m_MaximumP   );
			NT->fillDouble("P2nd",           m_Maxi2ndP   );
			NT->fillDouble("MaxE",           m_MaximumE   );
			NT->fillDouble("E2nd",           m_Maxi2ndE   );

			if (doVertexFit) NT->fillDouble("VChi2",vtxfit->chisq(0));
			else             NT->fillDouble("VChi2",-1.0);

			if (exclusive || m_MassCons || fsinfo->constrain4Mom() ){
				NT->fillDouble("Chi2",   kmfit->chisq());
				NT->fillDouble("Chi2DOF",kmfit->chisq()/kinFitDOF);
			}

			if (inclusive){
				NT->fillDouble("TotalEnergy",    totalP4.e()  );
				NT->fillDouble("TotalPx",        totalP4.px() );
				NT->fillDouble("TotalPy",        totalP4.py() );
				NT->fillDouble("TotalPz",        totalP4.pz() );
			}

			for (unsigned int j = 0; j < combo.size(); j++){
				FSParticle* fsp = combo[j];
				bool simpleTrk = 
					fsp->name()=="pi+" || fsp->name()=="pi-" || 
					fsp->name()=="K+"  || fsp->name()=="K-"  || 
					fsp->name()=="p+"  || fsp->name()=="p-"  || 
					fsp->name()=="e+"  || fsp->name()=="e-"  || 
					fsp->name()=="mu+" || fsp->name()=="mu-"  ; 
				if (fsp->missed() && simpleTrk) {
					vector< FSParticle* >  MissingList =  DictPList[fsp->name()];
					NT->fillMissingTrack(MissingList, m_beamSpot);
				}
			}
			// record particle level information
			vector<HepLorentzVector>  rawp4list, vtxp4list, kmfp4list; 
			rawp4list.clear();  vtxp4list.clear(); kmfp4list.clear();
			//
			char index[30],prefix[30];
			kinFitTrack = 0;
			for (unsigned int j = 0; j < combo.size(); j++){
				FSParticle* fsp = combo[j];
				if(m_Debug>2)printf("F j= %2d, fsp->dmes() = %d\n", j, fsp->dmes());
				rawp4list.push_back(fsp->rawFourMomentum());
				vtxp4list.push_back(fsp->intFourMomentum());
				kmfp4list.push_back(fsp->fitFourMomentum());
				if (fsp->missed()){
					kinFitTrack++;
				}
				if (fsp->shower()){
					const RecEmcShower p = *(fsp->shower());
					kinFitTrack++;
					NT->fillShower(j+1,"Sh",fsp->shower(),pi0List,evtRecTrackCol);
				}
				if (fsp->track()){
					kinFitTrack++;
					NT->fillTrack(j+1,"Tk",fsp->track(),m_beamSpot,m_pidStudies);
				}
				if (fsp->pi0()){
					kinFitTrack+=2;
					NT->fillPi0   (j+1,"Pi0",    fsp->pi0());
					NT->fillShower(j+1,"Pi0ShLo",fsp->pi0Lo(),pi0List,evtRecTrackCol);
					NT->fillShower(j+1,"Pi0ShHi",fsp->pi0Hi(),pi0List,evtRecTrackCol);
				}
				if (fsp->eta()){
					kinFitTrack+=2;
					NT->fillEta   (j+1,"Eta",    fsp->eta());
					NT->fillShower(j+1,"EtaShLo",fsp->etaLo(),pi0List,evtRecTrackCol);
					NT->fillShower(j+1,"EtaShHi",fsp->etaHi(),pi0List,evtRecTrackCol);
				}
				if (fsp->vee()){
					kinFitTrack+=2;
					NT->fillVee  (j+1,"Vee"   ,fsp->vee()      ,fsp->veeLSigma());
					NT->fillTrack(j+1,"VeeTk1",fsp->veeTrack1(),m_beamSpot,m_pidStudies);
					NT->fillTrack(j+1,"VeeTk2",fsp->veeTrack2(),m_beamSpot,m_pidStudies);
				}
				//
				if (fsp->dmes()){
					int ntracks  = fsp-> dmesNTracks (); 	
					int nshowers = fsp-> dmesNShowers(); 	
					if (exclusive || m_MassCons){
						vector<HepLorentzVector> p4list; p4list.clear();
						for(int iw=0; iw<ntracks+nshowers; iw++){
							p4list.push_back(kmfit->pfit(kinFitTrack+iw));
						}
						sprintf(index ,"idx_D%d", j+1);
						sprintf(prefix,"D%d"    , j+1);
						NT->fill4Momentum((string)index,(string)prefix,p4list,p4list.size());
					}
					sprintf(index ,"DmesgoldenP%d",j+1);
					NT->fillDouble((string)index,dtagName->GetStatus(fsp->dmesTagmode(), "mode"));
					sprintf(index ,"KsLSigmaCutP%d",j+1);
					NT->fillDouble((string)index,fsp->dmesKsCut(m_KsSigmaCut));
					NT->fillDmes (j+1,"Dmes", fsp->dmes());
					kinFitTrack += (ntracks+nshowers);
				}
			}
			//
			NT->fill4Momentum("idx_raw","raw_", rawp4list, rawp4list.size());
			if(inclusive)NT->fill4Momentum("idx_vtx","vtx_", vtxp4list, vtxp4list.size());
			//if(exclusive)NT->fill4Momentum("idx_kmf","kmf_", kmfp4list, kmfp4list.size());
			if(   1     )NT->fill4Momentum("idx_kmf","kmf_", kmfp4list, kmfp4list.size());
			if( rawp4list.size()>0 && inclusive){
				for(int ki=0; ki<rawp4list.size(); ki++){
					sprintf(index ,"Rreco%d",ki+1);
					NT->fillDouble((string)index,(p4psi-rawp4list[ki]).m2());
					if ( vtxp4list.size()==rawp4list.size()) {
						sprintf(index ,"Vreco%d",ki+1);
						NT->fillDouble((string)index,(p4psi-vtxp4list[ki]).m2());
					}
					if ( kmfp4list.size()==rawp4list.size()) {
						sprintf(index ,"Kreco%d",ki+1);
						NT->fillDouble((string)index,(p4psi-kmfp4list[ki]).m2());
					}
				}
			}
			if( rawp4list.size()>1 ){
				for(int ki=0; ki<rawp4list.size()-1; ki++){
					for(int kj=ki+1; kj<rawp4list.size(); kj++){
						sprintf(index ,"RMass%d%d",ki+1,kj+1);
						NT->fillDouble((string)index,(rawp4list[ki]+rawp4list[kj]).m());
						if (    1    ) {
							sprintf(index ,"KMass%d%d",ki+1,kj+1);
							NT->fillDouble((string)index,(kmfp4list[ki]+kmfp4list[kj]).m());
							//continue;
						}
						sprintf(index ,"Rreco%d%d",ki+1,kj+1);
						NT->fillDouble((string)index,(p4psi-rawp4list[ki]-rawp4list[kj]).m());
						if ( vtxp4list.size()==rawp4list.size()) {
							sprintf(index ,"Vreco%d%d",ki+1,kj+1);
							NT->fillDouble((string)index,(p4psi-vtxp4list[ki]-vtxp4list[kj]).m2());
						}
						if ( kmfp4list.size()==rawp4list.size()) {
							sprintf(index ,"Kreco%d%d",ki+1,kj+1);
							NT->fillDouble((string)index,(p4psi-kmfp4list[ki]-kmfp4list[kj]).m2());
						}
					}
				}
			}
			if( rawp4list.size()>2 ){
				for(int ki=0; ki<rawp4list.size()-2; ki++){
					for(int kj=ki+1; kj<rawp4list.size()-1; kj++){
						for(int kk=kj+1; kk<rawp4list.size(); kk++){
							sprintf(index ,"RMass%d%d%d",ki+1,kj+1,kk+1);
							NT->fillDouble((string)index,(rawp4list[ki]+rawp4list[kj]+rawp4list[kk]).m());
							if (   1     ) {
								sprintf(index ,"KMass%d%d%d",ki+1,kj+1,kk+1);
								NT->fillDouble((string)index,(kmfp4list[ki]+kmfp4list[kj]+kmfp4list[kk]).m());
								//continue;
							}
							sprintf(index ,"Rreco%d%d%d",ki+1,kj+1,kk+1);
							NT->fillDouble((string)index,(p4psi-rawp4list[ki]-rawp4list[kj]-rawp4list[kk]).m());
							if ( vtxp4list.size()==rawp4list.size()) {
								sprintf(index ,"Vreco%d%d%d",ki+1,kj+1,kk+1);
								NT->fillDouble((string)index,(p4psi-vtxp4list[ki]-vtxp4list[kj]-vtxp4list[kk]).m2());
							}
							if ( kmfp4list.size()==rawp4list.size()) {
								sprintf(index ,"Kreco%d%d%d",ki+1,kj+1,kk+1);
								NT->fillDouble((string)index,(p4psi-kmfp4list[ki]-kmfp4list[kj]-kmfp4list[kk]).m2());
							}
						}
					}
				}
			}
			if( rawp4list.size()>3 ){
				for(int kl=0; kl<rawp4list.size()-3; kl++){
					for(int ki=kl+1; ki<rawp4list.size()-2; ki++){
						for(int kj=ki+1; kj<rawp4list.size()-1; kj++){
							for(int kk=kj+1; kk<rawp4list.size(); kk++){
								sprintf(index ,"RMass%d%d%d%d",kl+1,ki+1,kj+1,kk+1);
								NT->fillDouble((string)index,(rawp4list[kl]+rawp4list[ki]+rawp4list[kj]+rawp4list[kk]).m());
								if (   1     ) {
									sprintf(index ,"KMass%d%d%d%d",kl+1,ki+1,kj+1,kk+1);
									NT->fillDouble((string)index,(kmfp4list[kl]+kmfp4list[ki]+kmfp4list[kj]+kmfp4list[kk]).m());
									//continue;
								}
								sprintf(index ,"Rreco%d%d%d%d",kl+1,ki+1,kj+1,kk+1);
								NT->fillDouble((string)index,(p4psi-rawp4list[kl]-rawp4list[ki]-rawp4list[kj]-rawp4list[kk]).m());
								if ( vtxp4list.size()==rawp4list.size()) {
									sprintf(index ,"Vreco%d%d%d%d",kl+1,ki+1,kj+1,kk+1);
									NT->fillDouble((string)index,(p4psi-vtxp4list[kl]-vtxp4list[ki]-vtxp4list[kj]-vtxp4list[kk]).m2());
								}
								if ( kmfp4list.size()==rawp4list.size()) {
									sprintf(index ,"Kreco%d%d%d%d",kl+1,ki+1,kj+1,kk+1);
									NT->fillDouble((string)index,(p4psi-kmfp4list[kl]-kmfp4list[ki]-kmfp4list[kj]-kmfp4list[kk]).m2());
								}
							}
						}
					}
				}
			}
			//
			timer.Stop();
			m_cpu[8] += timer.CpuTime();
			//
			// write the tree
			m_CutPass[ifs]++;
			timer.Start();
			NT->write();
			timer.Stop();
			m_cpu[9] += timer.CpuTime();
			//
			FreeAll(rawp4list);
			FreeAll(vtxp4list);
			FreeAll(kmfp4list);
		}
	}
	//
	CleanEvt();
	//
	if ( m_Debug>0 ) printf("END\n");
	//
	return StatusCode::SUCCESS;
}
//********************************************************************
//********************************************************************
//********************************************************************
//
//   FINALIZE
//
//********************************************************************
//********************************************************************
//********************************************************************
StatusCode FSFilter::finalize(){

	char message[15][40]={
		"Input Number of   Evts ",//  0 
		"After maximum E&P  Cut ",//  1
		"Events  input  FS loop ",//  2
		"nChrg  protection  Cut ",//  3
		"nCombo greater than  0 ",//  4
		"Before  E and P    Cut ",//  5
		"Missing Energy     Cut ",//  6
		"Missing Momentum   Cut ",//  7
		"Missing Mass       Cut ",//  8
		"Raw   4-Momentum   Cut ",//  9
		"Vertex Fit  Successful ",// 10
		"Int   4-Momentum   Cut ",// 11
		"Kine   Fit  Successful ",// 12
		"KineFit Chisq      Cut ",// 13
		"Fit   4-Momentum   Cut " // 14
	};	

	printf("\n");
	cout << "Total events = " << m_eventCounter << endl;
	for(int i=0; i<m_FSInfoVector.size(); i++){
		printf("\n");
		printf("%27s\n", (m_FSInfoVector[i]->FSName()).data());
		for(int j=0; j<15; j++){
			if     (j==0)printf("%3d) %30s: %10d %10.2f%%\n",j,message[j],(int)m_cutpass[0][j],m_cutpass[0][j]/m_cutpass[0][j-0]*100);
			else if(j< 2)printf("%3d) %30s: %10d %10.2f%%\n",j,message[j],(int)m_cutpass[0][j],m_cutpass[0][j]/m_cutpass[0][j-1]*100);
			else if(j==2)printf("%3d) %30s: %10d %10.2f%%\n",j,message[j],(int)m_cutpass[i][j],m_cutpass[i][j]/m_cutpass[0][j-1]*100);
			else         printf("%3d) %30s: %10d %10.2f%%\n",j,message[j],(int)m_cutpass[i][j],m_cutpass[i][j]/m_cutpass[i][j-1]*100);
		}
	}

	printf("\n");
	for(int i=0; i<m_FSInfoVector.size(); i++){
		printf("%27s fill number :%10d\n", (m_FSInfoVector[i]->FSName()).data(), m_CutPass[i]);
	}

	printf("\n");
	if(m_Debug>1){
		for(int i=0; i<20; i++){
			printf("Just for checking  :%2d, %10d\n", i, (int)m_Checking[i]);
		}
	}

	printf("\n");
	if(m_Debug>-1){
		char CPUmess[10][40]={
			"Simple particle preparing takes ",
			"Combination partile ...   takes ",
			"D meson  list preparing   takes ",
			"Combinations  preparing   takes ",
			"2nd vertex fit (1st fit)  takes ",
			"2nd vertex fit (2nd fit)  takes ",
			"1st vertex fit            takes ",
			"kinematic  fit            takes ",
			"Filling variables         takes ",
			"Writing ntuple            takes "
		};	
		for(int i=0; i<10; i++){
			printf("%s:%2d, %10.2f secs\n",CPUmess[i], i, m_cpu[i]);
		}
	}
	printf("\n\n\n");
	//
	FreeDelAll(m_FSInfoVector);
	if( m_findD0 || m_findD0bar || m_findDp || m_findDm || m_findDsp || m_findDsm){
		if(dtagName) {delete dtagName; dtagName=NULL;}
	}
	//if(rscanDQ) delete rscanDQ;
	//
	return StatusCode::SUCCESS;
}
//
void FSFilter::GetPi0(SmartDataPtr<EvtRecPi0Col> evtRecPi0Col){
	for(EvtRecPi0Col::iterator iPi0 = evtRecPi0Col->begin(); 
			iPi0 != evtRecPi0Col->end(); iPi0++){
		if(m_UseHis) {
			h_ComPar_Pi0 ->Fill((*iPi0)->unconMass(),1.0);
			h_ComPi0_Chi2->Fill((*iPi0)->chisq()    ,1.0);}
			//	
			if (((*iPi0)->chisq() < 2500) && 
					((*iPi0)->unconMass() > 0.115) && 
					((*iPi0)->unconMass() < 0.150) || m_pi0Studies ){
				EvtRecTrack* lo = const_cast<EvtRecTrack*>((*iPi0)->loEnGamma()); 
				RecEmcShower* loShower = lo->emcShower();
				if (m_neutralStudies || (loShower->energy() > 0.025) && 
						(loShower->time() >= 0) && (loShower->time() <= 14) &&
						(((abs(cos(loShower->theta())) < 0.80) && (loShower->energy() > 0.025)) || 
						 ((abs(cos(loShower->theta())) < 0.92) &&
						  (abs(cos(loShower->theta())) > 0.86) && (loShower->energy() > 0.050)))){
					EvtRecTrack* hi = const_cast<EvtRecTrack*>((*iPi0)->hiEnGamma()); 
					RecEmcShower* hiShower = hi->emcShower();
					if (m_neutralStudies || (hiShower->energy() > 0.025) && 
							(hiShower->time() >= 0) && (hiShower->time() <= 14) &&
							(((abs(cos(hiShower->theta())) < 0.80) && (hiShower->energy() > 0.025)) || 
							 ((abs(cos(hiShower->theta())) < 0.92) &&
							  (abs(cos(hiShower->theta())) > 0.86) && (hiShower->energy() > 0.050)))){
						pi0List.push_back(new FSParticle(*iPi0,"pi0"));
					}
				}
			}
	}
}
//
void FSFilter::GetEta(SmartDataPtr<EvtRecEtaToGGCol> evtRecEtaToGGCol){
	for(EvtRecEtaToGGCol::iterator iEta = evtRecEtaToGGCol->begin(); 
			iEta != evtRecEtaToGGCol->end(); iEta++){
		if(m_UseHis) {
			h_ComPar_Eta ->Fill((*iEta)->unconMass(),1.0);
			h_ComEta_Chi2->Fill((*iEta)->chisq()    ,1.0);}
			if (((*iEta)->chisq() < 2500) && 
					((*iEta)->unconMass() > 0.505) && 
					((*iEta)->unconMass() < 0.570) || m_etaStudies ) {
				EvtRecTrack* lo = const_cast<EvtRecTrack*>((*iEta)->loEnGamma()); 
				RecEmcShower* loShower = lo->emcShower();
				if ( m_neutralStudies ||  (loShower->energy() > 0.025) && 
						(loShower->time() >= 0) && (loShower->time() <= 14) &&
						(((abs(cos(loShower->theta())) < 0.80) && (loShower->energy() > 0.025)) || 
						 ((abs(cos(loShower->theta())) < 0.92) &&
						  (abs(cos(loShower->theta())) > 0.86) && (loShower->energy() > 0.050)))){
					EvtRecTrack* hi = const_cast<EvtRecTrack*>((*iEta)->hiEnGamma()); 
					RecEmcShower* hiShower = hi->emcShower();
					if ( m_neutralStudies || (hiShower->energy() > 0.025) && 
							(hiShower->time() >= 0) && (hiShower->time() <= 14) &&
							(((abs(cos(hiShower->theta())) < 0.80) && (hiShower->energy() > 0.025)) || 
							 ((abs(cos(hiShower->theta())) < 0.92) &&
							  (abs(cos(hiShower->theta())) > 0.86) && (hiShower->energy() > 0.050)))){
						etaList.push_back(new FSParticle(*iEta,"eta"));
					}
				}
			}
	}
}
//
void FSFilter::GetKs(SmartDataPtr<EvtRecVeeVertexCol> evtRecVeeVertexCol){
	// [[ vertexId is the pdgID ]]
	for(EvtRecVeeVertexCol::iterator iKs = evtRecVeeVertexCol->begin(); 
			iKs != evtRecVeeVertexCol->end(); iKs++){
		if(m_UseHis) {
			h_ComPar_Ks  ->Fill((*iKs)->mass(),1.0); 
			h_ComKs_Chi2 ->Fill((*iKs)->chi2(),1.0);}
			if ( (*iKs)->vertexId() == 310 ) { 
				if ( m_veeStudies || 
						((*iKs)->mass() > 0.487) &&
						((*iKs)->mass() < 0.511) &&
						((*iKs)->chi2() < 100)){
					ksList.push_back(new FSParticle(*iKs,"Ks"));
				}
			}
	}
}
//
void FSFilter::GetLambda(SmartDataPtr<EvtRecVeeVertexCol> evtRecVeeVertexCol){
	for(EvtRecVeeVertexCol::iterator iL = evtRecVeeVertexCol->begin(); 
			iL != evtRecVeeVertexCol->end(); iL++){
		if(m_UseHis) {
			h_ComPar_Lamb->Fill((*iL)->mass(),1.0); 
			h_ComLam_Chi2->Fill((*iL)->chi2(),1.0);}
			if (m_findLambda&&((*iL)->vertexId() == 3122) ) {
				if(m_veeStudies || ((*iL)->mass() > 1.100) &&
						((*iL)->mass() < 1.130) &&
						((*iL)->chi2() < 100)){
					lambdaList.push_back(new FSParticle(*iL,"Lambda"));
				}
			}
			if ( m_findaLambda&& ((*iL)->vertexId() == -3122) ){
				if(m_veeStudies || ((*iL)->mass() > 1.100) &&
						((*iL)->mass() < 1.130) &&
						((*iL)->chi2() < 100)){
					alambdaList.push_back(new FSParticle(*iL,"ALambda"));
				}
			}
	}
}
//
void FSFilter::GetTrackAndShower(SmartDataPtr<EvtRecTrackCol> evtRecTrackCol, int totalCharged){
	nTRK      =0;
	m_MaximumP=0.001;
	m_Maxi2ndP=0.000;
	m_MaximumE=0.001;
	m_Maxi2ndE=0.000;
	for(EvtRecTrackIterator iTrk = evtRecTrackCol->begin(); iTrk != evtRecTrackCol->end(); iTrk++){ 

		// get photons
		if (m_findGamma && (*iTrk)->trackId() >= totalCharged )
		{
			if((*iTrk)->isEmcShowerValid()){
				RecEmcShower* emcShower = (*iTrk)->emcShower();
				if(m_UseHis) {
					h_InfEMC_T  ->Fill( emcShower->time()     , 1.0); 
					h_InfEMC_E  ->Fill( emcShower->energy()   , 1.0); 
					h_InfEMC_PHI->Fill( emcShower->phi()      , 1.0); 
					h_InfEMC_COS->Fill(cos(emcShower->theta()), 1.0); 
				}
				if ( m_neutralStudies || (emcShower->energy() > 0.025) && 
						(emcShower->time() >= 0) && (emcShower->time() <= 14) &&
						(((abs(cos(emcShower->theta())) < 0.80) && (emcShower->energy() > 0.025)) || 
						 ((abs(cos(emcShower->theta())) < 0.92) &&
						  (abs(cos(emcShower->theta())) > 0.86) && (emcShower->energy() > 0.050)))){
					gammaList.push_back(new FSParticle(emcShower,"gamma"));
					if( emcShower->energy()>m_MaximumE ) {
						m_Maxi2ndE = m_MaximumE;
						m_MaximumE = emcShower->energy();  
					}
				}
			}
		}

		if ( (*iTrk)->trackId() >= totalCharged             ) continue;
		if (!(*iTrk)->isMdcKalTrackValid()                  ) continue;
		if ( GoodTrack(*iTrk)                               ) nTRK++;
		// get tracks
		if(  (   (m_findPip)||(m_findKp)||(m_findPp)||(m_findEp)||(m_findMup)||
					(m_findPim)||(m_findKm)||(m_findPm)||(m_findEm)||(m_findMum)   )&&
				(*iTrk)->isMdcKalTrackValid()){

			RecMdcKalTrack* mdcKalTrack = (*iTrk)->mdcKalTrack();

			// set up pid (but only make very rough pid cuts)

			ParticleID* pid = ParticleID::instance();
			pid->init();
			pid->setMethod(pid->methodProbability());
			pid->setRecTrack(*iTrk);
			pid->usePidSys( 
					pid->useDedx()  | 
					pid->useTof1()  | 
					pid->useTof2()
					);
			pid->identify(  
					pid->onlyPion()     | 
					pid->onlyKaon()     | 
					pid->onlyProton()   | 
					pid->onlyElectron() | 
					pid->onlyMuon());
			pid->calculate();

			// get pions
			if (m_findPip || m_findPim){
				if ( (pid->IsPidInfoValid() && pid->probPion() > 1.0e-5) || m_trackStudies==0 ){
					if(m_findPip&&mdcKalTrack->charge()>0) pipList.push_back(new FSParticle(*iTrk,"pi+",m_yuping));
					if(m_findPim&&mdcKalTrack->charge()<0) pimList.push_back(new FSParticle(*iTrk,"pi-",m_yuping));
				}
			}

			// get kaons
			if (m_findKp||m_findKm){
				if ( (pid->IsPidInfoValid() && pid->probKaon() > 1.0e-5) ||  m_trackStudies==0){
					if (m_findKp&&mdcKalTrack->charge() > 0) kpList.push_back(new FSParticle(*iTrk,"K+",m_yuping));
					if (m_findKm&&mdcKalTrack->charge() < 0) kmList.push_back(new FSParticle(*iTrk,"K-",m_yuping));
				}
			}

			// get protons
			if (m_findPp || m_findPm){
				if ( (pid->IsPidInfoValid() && pid->probProton() > 1.0e-5) || m_trackStudies==0){
					if (m_findPp&&mdcKalTrack->charge() > 0) ppList.push_back(new FSParticle(*iTrk,"p+",m_yuping));
					if (m_findPm&&mdcKalTrack->charge() < 0) pmList.push_back(new FSParticle(*iTrk,"p-",m_yuping));
				}
			}

			// get electrons
			if (m_findEp || m_findEm){
				if ( (pid->IsPidInfoValid() && pid->probElectron() > 1.0e-5) || m_trackStudies==0 ){
					if (m_findEp&&mdcKalTrack->charge()>0) epList.push_back(new FSParticle(*iTrk,"e+",m_yuping));
					if (m_findEm&&mdcKalTrack->charge()<0) emList.push_back(new FSParticle(*iTrk,"e-",m_yuping));
				}
			}

			// get muons
			if (m_findMup || m_findMum){
				if ( (pid->IsPidInfoValid() && pid->probMuon() > 1.0e-5) || m_trackStudies==0 ){
					if (m_findMup&&mdcKalTrack->charge()>0) mupList.push_back(new FSParticle(*iTrk,"mu+",m_yuping));
					if (m_findMum&&mdcKalTrack->charge()<0) mumList.push_back(new FSParticle(*iTrk,"mu-",m_yuping));
				}
			}
		}
	}
}
// not ready
void FSFilter::GetJpsi  (SmartDataPtr<EvtRecTrackCol> evtRecTrackCol){

	for(EvtRecTrackIterator iTrk1 = evtRecTrackCol->begin();
			iTrk1 != evtRecTrackCol->end(); iTrk1++){ 
		if((*iTrk1)->isMdcKalTrackValid()){
			RecMdcKalTrack* mdcKalTrack1 = (*iTrk1)->mdcKalTrack();
			double Emc1=0; 
			if( (*iTrk1)->isEmcShowerValid() ){
				RecEmcShower* emcShower1 = (*iTrk1)->emcShower();
				Emc1=emcShower1->energy();  
			}
			double chi_e1=99, chi_u1=99; 
			if ( (*iTrk1)->isMdcDedxValid() ){ 
				RecMdcDedx* dedxTrk1 = (*iTrk1)->mdcDedx();
				chi_e1= dedxTrk1->chiE(); chi_u1=dedxTrk1->chiMu();
			}	
			for(EvtRecTrackIterator iTrk2 = iTrk1;
					iTrk2 != evtRecTrackCol->end(); iTrk2++){ 
				if((*iTrk2)->isMdcKalTrackValid() && 
						(*iTrk2)->trackId() != (*iTrk1)->trackId()){
					RecMdcKalTrack* mdcKalTrack2 = (*iTrk2)->mdcKalTrack();
					if (mdcKalTrack1->charge() == mdcKalTrack2->charge()) continue;
					double Emc2=0; 
					if( (*iTrk2)->isEmcShowerValid() ){
						RecEmcShower* emcShower2 = (*iTrk2)->emcShower();
						Emc2=emcShower2->energy();  
					}
					double chi_e2=99, chi_u2=99; 
					if ( (*iTrk2)->isMdcDedxValid() ){ 
						RecMdcDedx* dedxTrk2 = (*iTrk2)->mdcDedx();
						chi_e2= dedxTrk2->chiE(); chi_u2=dedxTrk2->chiMu();
					}	
					double Emcll  = Emc1+Emc2;
					double chi2e  = chi_e1*chi_e1+chi_e2*chi_e2;   	
					double chi2u  = chi_u1*chi_u1+chi_u2*chi_u2;  
					HepLorentzVector p1,p2; 
					if(  Emcll>1.0 || ( Emcll>0.6 && chi2e<chi2u ) ){ 
						mdcKalTrack1->setPidType(RecMdcKalTrack::electron);
						mdcKalTrack2->setPidType(RecMdcKalTrack::electron);
						p1 = mdcKalTrack1->p4(Mass("e+"));
						p2 = mdcKalTrack2->p4(Mass("e+"));
					}else{
						mdcKalTrack1->setPidType(RecMdcKalTrack::muon);
						mdcKalTrack2->setPidType(RecMdcKalTrack::muon);
						p1 = mdcKalTrack1->p4(Mass("mu+"));
						p2 = mdcKalTrack2->p4(Mass("mu+"));
					}
					double mjpsi = (p1+p2).m();
					if (mjpsi <3.2 && mjpsi>2.9 ) 
						;
				}
			}
		}
	}
}
//
void FSFilter::GetDmeson(double m_def, int im_dep, int im_fin, int charge, string DName){

	int charm=+1, ic=0;
	if( DName=="D0bar" || DName=="D-" || DName=="Ds-") charm  = -1;

	if( m_ModeBest ){
		EvtRecDTagCol::iterator iD_s = (EvtRecDTagCol::iterator)0;
		for( int idm =im_dep; idm<im_fin; idm++)
		{
			vector<int> mode = dtagTool->mode( (int)dtagName->find_Mode(idm) );
			double mass_cand = 999.;
			for( int icand=0; icand < mode.size(); icand++) {
				if( m_Golden && dtagName->GetStatus(mode[icand])<1 )         continue;
				EvtRecDTagCol::iterator iD = dtagTool->modes_begin()+mode[icand];
				if( m_tightcut  && ( (*iD)->type()   != EvtRecDTag::Tight) ) continue;
				if( charge == 0 && ( (*iD)->charm()  == -charm           ) ) continue;
				if( charge != 0 && ( (*iD)->charge() !=  charge          ) ) continue;
				double DelMass = fabs( (*iD)->mass()-m_def );
				if ( DelMass < mass_cand ) {
					mass_cand  = DelMass;
					iD_s    = iD;
				}				
			}
			if ( mass_cand < m_DelMassCut ){
				ic++;
				int decaymode = (*iD_s)->decayMode(); 
				if(m_UseHis) {
					if(DName=="D0"   || DName=="D0bar"){
						h_ComMbc_D0 ->Fill((*iD_s)->mBC()   , 1.0); 
						h_ComPar_D0 ->Fill((*iD_s)->mass()  , 1.0);
						h_ComdE_D0  ->Fill((*iD_s)->deltaE(), 1.0); 
					}	
					if(DName=="D+"   || DName=="D-"   ){
						h_ComMbc_Dp ->Fill((*iD_s)->mBC()   , 1.0); 
						h_ComPar_Dp ->Fill((*iD_s)->mass()  , 1.0); 
						h_ComdE_Dp  ->Fill((*iD_s)->deltaE(), 1.0); 
					}
					if(DName=="Ds+"  || DName=="Ds-"  ){
						h_ComMbc_Dsp->Fill((*iD_s)->mBC()   , 1.0); 
						h_ComPar_Dsp->Fill((*iD_s)->mass()  , 1.0);
						h_ComdE_Dsp ->Fill((*iD_s)->deltaE(), 1.0); 
					}
				}	
				if(DName=="D0"   )D0List   .push_back(new FSParticle(*iD_s,DName,dtagName->GetNKinDTag(decaymode)));
				if(DName=="D0bar")D0barList.push_back(new FSParticle(*iD_s,DName,dtagName->GetNKinDTag(decaymode)));
				if(DName=="D+"   )DpList   .push_back(new FSParticle(*iD_s,DName,dtagName->GetNKinDTag(decaymode)));
				if(DName=="D-"   )DmList   .push_back(new FSParticle(*iD_s,DName,dtagName->GetNKinDTag(decaymode)));
				if(DName=="Ds+"  )DspList  .push_back(new FSParticle(*iD_s,DName,dtagName->GetNKinDTag(decaymode)));
				if(DName=="Ds-"  )DsmList  .push_back(new FSParticle(*iD_s,DName,dtagName->GetNKinDTag(decaymode)));
			}
		}
	}else{
		for( int idm =im_dep; idm<im_fin; idm++)
		{
			vector<int> mode = dtagTool->mode( (int)dtagName->find_Mode(idm));
			double mass_cand = 999.;
			for( int icand=0; icand < mode.size(); icand++) {
				if( m_Golden && dtagName->GetStatus(mode[icand])<1 )         continue;
				EvtRecDTagCol::iterator iD = dtagTool->modes_begin()+mode[icand];
				if( m_tightcut  && ( (*iD)->type()   != EvtRecDTag::Tight) ) continue;
				if( charge == 0 && ( (*iD)->charm()  == -charm           ) ) continue;
				if( charge != 0 && ( (*iD)->charge() !=  charge          ) ) continue;
				double DelMass = fabs( (*iD)->mass()-m_def );
				if ( DelMass < m_DelMassCut ){
					ic++;
					int decaymode = (*iD)->decayMode(); 
					if(m_UseHis) {
						if(DName=="D0"   || DName=="D0bar"){
							h_ComMbc_D0 ->Fill((*iD)->mBC()   , 1.0); 
							h_ComPar_D0 ->Fill((*iD)->mass()  , 1.0); 
							h_ComdE_D0  ->Fill((*iD)->deltaE(), 1.0); 
						}
						if(DName=="D+"   || DName=="D-"   ){
							h_ComMbc_Dp ->Fill((*iD)->mBC()   , 1.0); 
							h_ComPar_Dp ->Fill((*iD)->mass()  , 1.0);
							h_ComdE_Dp  ->Fill((*iD)->deltaE(), 1.0); 
						}	
						if(DName=="Ds+"  || DName=="Ds-"  ){
							h_ComMbc_Dsp->Fill((*iD)->mBC()   , 1.0); 
							h_ComPar_Dsp->Fill((*iD)->mass()  , 1.0); 
							h_ComdE_Dsp ->Fill((*iD)->deltaE(), 1.0); 
						}
					}
					if(DName=="D0"   )D0List   .push_back(new FSParticle(*iD,DName,dtagName->GetNKinDTag(decaymode)));
					if(DName=="D0bar")D0barList.push_back(new FSParticle(*iD,DName,dtagName->GetNKinDTag(decaymode)));
					if(DName=="D+"   )DpList   .push_back(new FSParticle(*iD,DName,dtagName->GetNKinDTag(decaymode)));
					if(DName=="D-"   )DmList   .push_back(new FSParticle(*iD,DName,dtagName->GetNKinDTag(decaymode)));
					if(DName=="Ds+"  )DspList  .push_back(new FSParticle(*iD,DName,dtagName->GetNKinDTag(decaymode)));
					if(DName=="Ds-"  )DsmList  .push_back(new FSParticle(*iD,DName,dtagName->GetNKinDTag(decaymode)));
				}
			}
		}
	}
	if(m_Debug>2) printf("%3d %6s candidates \n", ic, DName.data());	
}
//
bool
FSFilter::GoodTrack(EvtRecTrack* p){

	// get vertex information
	RecMdcKalTrack *mdcKalTrk = p->mdcKalTrack();
	mdcKalTrk->setPidType(RecMdcKalTrack::pion); //all tracks assumed as pi, which may cause some differences on cosine theta
	RecMdcTrack *mdcTrk = p->mdcTrack();
	HepVector    a      = mdcTrk->helix();
	HepSymMatrix Ea     = mdcTrk->err();
	HepPoint3D point0(0.,0.,0.);
	HepPoint3D IP(m_beamSpot.vx()); 
	VFHelix helixip(point0,a,Ea); 
	helixip.pivot(IP);
	HepVector vecipa = helixip.a();
	double RVtx      = vecipa[0];
	double ZVtx      = vecipa[3];
	double pp        = mdcKalTrk->p();
	double pt        = mdcKalTrk->pxy();
	double theta     = mdcKalTrk->theta();
	double phi       = mdcKalTrk->phi();
	//
	if(m_UseHis) {
		h_TrkPar_R  ->Fill( RVtx     , 1.0); 
		h_TrkPar_Z  ->Fill( ZVtx     , 1.0); 
		h_TrkPar_P  ->Fill( pp       , 1.0); 
		h_TrkPar_COS->Fill(cos(theta), 1.0); 	
		h_TrkPar_PHI->Fill(  phi     , 1.0); }	
		//
		if( fabs(RVtx)>1          ) return false;
		if( fabs(ZVtx)>10         ) return false;
		if( fabs(cos(theta))>0.93 ) return false;	
		if( pp>m_MaximumP) {
			m_Maxi2ndP = m_MaximumP;
			m_MaximumP = pp;
		}	
		return true;
}
//
int 
FSFilter::GetTotalNoOfTrack(vector< FSParticle* > combo ){
	int ntrk=0;
	for (int t = 0; t < combo.size(); t++){
		if(!combo[t]->missed()) {
			ntrk += ((combo[t]->trackId()).size());
		}
	}
	return ntrk;
}
//
int 
FSFilter::GetTotalNoOfGamma(vector< FSParticle* > combo ){
	int ntrk=0;
	for (int t = 0; t < combo.size(); t++){
		if(!combo[t]->missed()) {
			ntrk += ((combo[t]->showerId()).size());
		}
	}
	return ntrk;
}

//********************************************************************
//********************************************************************
//********************************************************************
//
//   CHECK THE ENERGY AND MOMENTUM BALANCE OF A GIVEN FINAL STATE
//
//********************************************************************
//********************************************************************
//********************************************************************

bool
FSFilter::checkCombination(const vector<FSParticle*>& combo, bool complete, bool inclusive){

	if (inclusive) return true;
	// if the combination isn't yet complete, just check to make sure there
	//  is no excess energy outside of the energy tolerance
	if (!complete){

		double totalEnergy = 0.0;
		for (int i = 0; i < combo.size(); i++){
			if(!combo[i]->missed()) totalEnergy += combo[i]->rawFourMomentum().e();
		}

		double excessEnergy = totalEnergy - p4psi.e();

		if (excessEnergy > m_energyTolerance) return false;
		return true;

	}


	// if the combination is complete, calculate the total energy and momentum
	HepLorentzVector pTotal(0.0, 0.0, 0.0, 0.0);
	for (int i = 0; i < combo.size(); i++){
		if(!combo[i]->missed())	pTotal += combo[i]->rawFourMomentum();
	}

	HepLorentzVector pMissing = p4psi - pTotal;

	// if the combination is complete and exclusive, check the energy
	//   and momentum balance
	if (fabs(pMissing.e())          > m_energyTolerance  ) return false;
	if (fabs(pMissing.vect().mag()) > m_momentumTolerance) return false;
	return true;
}
//
int 
FSFilter::nVee(const vector<FSParticle*>& combo){

	int Vee=0;	
	for (int i = 0; i < combo.size(); i++){
		if( combo[i]->vee()  ) Vee++;
		if( combo[i]->dmes() ) Vee+=(combo[i]->dmesnKs());	
	}
	return Vee;
}
//
int 
FSFilter::nDmes(const vector<FSParticle*>& combo){

	int ndmes=0;	
	for (int i = 0; i < combo.size(); i++){
		if( combo[i]->dmes() ) ndmes++;	
	}

	return ndmes;
}
//
void
FSFilter::BookHist(){
	const double PI=3.1415926535;
	h_TrkPar_R    = new TH1D("TrkPar_R   ", "", 200,  -10,  10  ) ;
	h_TrkPar_Z    = new TH1D("TrkPar_Z   ", "", 200,  -30,  30  ) ;
	h_TrkPar_P    = new TH1D("TrkPar_P   ", "", 200,    0,  2.5 ) ;
	h_TrkPar_COS  = new TH1D("TrkPar_COS ", "", 200, -1.0,  1.0 ) ;
	h_TrkPar_PHI  = new TH1D("TrkPar_PHI ", "", 200,  -PI,  PI  ) ;
	//
	h_InfEMC_T    = new TH1D("InfEMC_T   ", "", 100,  -10,  30  ) ;
	h_InfEMC_E    = new TH1D("InfEMC_E   ", "", 200,    0,  2.5 ) ;
	h_InfEMC_COS  = new TH1D("InfEMC_COS ", "", 200, -1.0,  1.0 ) ;
	h_InfEMC_PHI  = new TH1D("InfEMC_PHI ", "", 200,  -PI,  PI  ) ;
	//
	h_ComPar_Pi0  = new TH1D("ComPar_Pi0 ", "", 100, 0.08,  0.16) ;
	h_ComPi0_Chi2 = new TH1D("ComPi0_Chi2", "", 200, 0.00,1000.0) ;
	h_ComPar_Eta  = new TH1D("ComPar_Eta ", "", 100,  0.5,  0.6 ) ;
	h_ComEta_Chi2 = new TH1D("ComEta_Chi2", "", 200, 0.00,1000.0) ;
	h_ComPar_Ks   = new TH1D("ComPar_Ks  ", "", 100, 0.45,  0.55) ;
	h_ComKs_Chi2  = new TH1D("ComKs_Chi2 ", "", 200, 0.00,1000.0) ;
	h_ComPar_Lamb = new TH1D("ComPar_Lamb", "", 100, 1.08,  1.15) ;
	h_ComLam_Chi2 = new TH1D("ComLam_Chi2", "", 200, 0.00,1000.0) ;
	//
	h_ComPar_D0   = new TH1D("ComPar_D0  ", "", 100, Mass("D0" )-m_DelMassCut, Mass("D0" )+m_DelMassCut ) ;
	h_ComPar_Dp   = new TH1D("ComPar_Dp  ", "", 100, Mass("D+" )-m_DelMassCut, Mass("D+" )+m_DelMassCut ) ;
	h_ComPar_Dsp  = new TH1D("ComPar_Dsp ", "", 100, Mass("Ds+")-m_DelMassCut, Mass("Ds+")+m_DelMassCut ) ;
	h_ComdE_D0    = new TH1D("ComdE_D0   ", "", 500,-0.4, 0.1) ;
	h_ComdE_Dp    = new TH1D("ComdE_Dp   ", "", 500,-0.4, 0.1) ;
	h_ComdE_Dsp   = new TH1D("ComdE_Dsp  ", "", 500,-0.4, 0.1) ;
	h_ComMbc_D0   = new TH1D("ComMbc_D0  ", "", 100, Mass("D0" )-m_DelMassCut, p4psi.e()/2.0 ) ;
	h_ComMbc_Dp   = new TH1D("ComMbc_Dp  ", "", 100, Mass("D+" )-m_DelMassCut, p4psi.e()/2.0 ) ;
	h_ComMbc_Dsp  = new TH1D("ComMbc_Dsp ", "", 100, Mass("Ds+")-m_DelMassCut, p4psi.e()/2.0 ) ;
}
//
void
FSFilter::CleanEvt(){
	//********************************************************************
	//
	//         CLEAN UP MEMORY
	//
	//********************************************************************
	FreeDelAll(  DspList      );
	FreeDelAll(  DsmList      );
	FreeDelAll(  DpList       );
	FreeDelAll(  DmList       );
	FreeDelAll(  D0List       );
	FreeDelAll(  D0barList    );
	FreeDelAll(  lambdaList   );
	FreeDelAll(  alambdaList  );
	FreeDelAll(  epList       );
	FreeDelAll(  emList       );
	FreeDelAll(  mupList      );
	FreeDelAll(  mumList      );
	FreeDelAll(  ppList       );
	FreeDelAll(  pmList       );
	FreeDelAll(  etaList      );
	FreeDelAll(  gammaList    );
	FreeDelAll(  kpList       );
	FreeDelAll(  kmList       );
	FreeDelAll(  ksList       );
	FreeDelAll(  pipList      );
	FreeDelAll(  pimList      );
	FreeDelAll(  pi0List      );
	FreeDelAll(  ParticleTrash);
	//
	FreeAll   (  DictPList    );
	//
	if( m_findD0 || m_findD0bar || m_findDp || m_findDm || m_findDsp || m_findDsm){
		if(dtagTool) {delete dtagTool; dtagTool=NULL;}
	}
	//
	if ( m_SaveMC ) { delete m_mcTruthHelper; m_mcTruthHelper=NULL;}
}
//
void 
FSFilter::GetEcmP4(){
	m_RootID        = rscanDQ->getRootID();	
	double mpsi     = rscanDQ->getEcm();
	double me       = 0.000511;
	double costheta = cos(m_crossingAngle);
	double tantheta = tan(m_crossingAngle);
	double epsilon  = 4.0*me*me/mpsi/mpsi;
	m_cmEnergy      = mpsi/costheta*sqrt(1.0-epsilon*(1-costheta*costheta));
	p4psi = HepLorentzVector(
			mpsi*tantheta*sqrt(1.0-epsilon),
			0.0,
			0.0,
			mpsi/costheta*sqrt(1.0-epsilon*(1-costheta*costheta))
			);
}
