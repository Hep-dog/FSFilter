//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
#include "FSFilter/DTagName.h"  
//
DTagName::DTagName()
{
	Vdmode  .clear();
	NoMode  .clear();
	PName   .clear();
	MName   .clear();
	Status  .clear();
	Br      .clear();
	dBr     .clear();
	NKinDTag.clear();
	init();
}

void DTagName::init()
{
	//0
	Vdmode.push_back(kD0toKPi            ); NoMode.insert(map<int,DecayMode>::value_type(  0, kD0toKPi            ));  //
	Vdmode.push_back(kD0toKPiPi0         ); NoMode.insert(map<int,DecayMode>::value_type(  1, kD0toKPiPi0         ));  // 
	Vdmode.push_back(kD0toKPiPi0Pi0      ); NoMode.insert(map<int,DecayMode>::value_type(  2, kD0toKPiPi0Pi0      ));  // 
	Vdmode.push_back(kD0toKPiPiPi        ); NoMode.insert(map<int,DecayMode>::value_type(  3, kD0toKPiPiPi        ));  // 
	Vdmode.push_back(kD0toKPiPiPiPi0     ); NoMode.insert(map<int,DecayMode>::value_type(  4, kD0toKPiPiPiPi0     ));  // 
	Vdmode.push_back(kD0toKPiEta         ); NoMode.insert(map<int,DecayMode>::value_type(  5, kD0toKPiEta         ));  //  
	//50                                                                                                          
	Vdmode.push_back(kD0toKsKPi          ); NoMode.insert(map<int,DecayMode>::value_type(  6, kD0toKsKPi          ));  // 
	Vdmode.push_back(kD0toKsKPiPi0       ); NoMode.insert(map<int,DecayMode>::value_type(  7, kD0toKsKPiPi0       ));  //
	//100                                                                                                         
	Vdmode.push_back(kD0toKsPiPi         ); NoMode.insert(map<int,DecayMode>::value_type(  8, kD0toKsPiPi         ));  // 
	Vdmode.push_back(kD0toKsPiPiPi0      ); NoMode.insert(map<int,DecayMode>::value_type(  9, kD0toKsPiPiPi0      ));  // 
	Vdmode.push_back(kD0toKsPi0          ); NoMode.insert(map<int,DecayMode>::value_type( 10, kD0toKsPi0          ));  //   
	Vdmode.push_back(kD0toPiPiPi0        ); NoMode.insert(map<int,DecayMode>::value_type( 11, kD0toPiPiPi0        ));  // 
	Vdmode.push_back(kD0toPiPi           ); NoMode.insert(map<int,DecayMode>::value_type( 12, kD0toPiPi           ));  // 
	//105                                                                                                         
	Vdmode.push_back(kD0toKK             ); NoMode.insert(map<int,DecayMode>::value_type( 13, kD0toKK             ));  // 
	Vdmode.push_back(kD0toKKPi0          ); NoMode.insert(map<int,DecayMode>::value_type( 14, kD0toKKPi0          ));  // 
	Vdmode.push_back(kD0toPi0Pi0         ); NoMode.insert(map<int,DecayMode>::value_type( 15, kD0toPi0Pi0         ));  //   
	Vdmode.push_back(kD0toKsKs           ); NoMode.insert(map<int,DecayMode>::value_type( 16, kD0toKsKs           ));  // 
	Vdmode.push_back(kD0toKsKsPi0        ); NoMode.insert(map<int,DecayMode>::value_type( 17, kD0toKsKsPi0        ));  // 
	//110                                                                                                         
	Vdmode.push_back(kD0toKsPi0Pi0       ); NoMode.insert(map<int,DecayMode>::value_type( 18, kD0toKsPi0Pi0       ));  // 
	Vdmode.push_back(kD0toKsKK           ); NoMode.insert(map<int,DecayMode>::value_type( 19, kD0toKsKK           ));  // 
	Vdmode.push_back(kD0toKsEta          ); NoMode.insert(map<int,DecayMode>::value_type( 20, kD0toKsEta          ));  //    
	Vdmode.push_back(kD0toPi0Pi0Pi0      ); NoMode.insert(map<int,DecayMode>::value_type( 21, kD0toPi0Pi0Pi0      ));  //
	Vdmode.push_back(kD0toKsKsKs         ); NoMode.insert(map<int,DecayMode>::value_type( 22, kD0toKsKsKs         ));  //
	//115                                                                                                         
	Vdmode.push_back(kD0toPiPiPiPi       ); NoMode.insert(map<int,DecayMode>::value_type( 23, kD0toPiPiPiPi       ));  // 
	Vdmode.push_back(kD0toPiPiPi0Pi0     ); NoMode.insert(map<int,DecayMode>::value_type( 24, kD0toPiPiPi0Pi0     ));  // 
	Vdmode.push_back(kD0toKKPiPi         ); NoMode.insert(map<int,DecayMode>::value_type( 25, kD0toKKPiPi         ));  //   
	Vdmode.push_back(kD0toKKPi0Pi0       ); NoMode.insert(map<int,DecayMode>::value_type( 26, kD0toKKPi0Pi0       ));  // 
	Vdmode.push_back(kD0toKsKsPiPi       ); NoMode.insert(map<int,DecayMode>::value_type( 27, kD0toKsKsPiPi       ));  // 
	//120                                                                                                         
	Vdmode.push_back(kD0toPiPiPiPiPi0    ); NoMode.insert(map<int,DecayMode>::value_type( 28, kD0toPiPiPiPiPi0    ));  // 
	Vdmode.push_back(kD0toKsPiPiPiPi     ); NoMode.insert(map<int,DecayMode>::value_type( 29, kD0toKsPiPiPiPi     ));  // 
	Vdmode.push_back(kD0toKKPiPiPi0      ); NoMode.insert(map<int,DecayMode>::value_type( 30, kD0toKKPiPiPi0      ));  //   
	Vdmode.push_back(kD0toKsPi0Eta       ); NoMode.insert(map<int,DecayMode>::value_type( 31, kD0toKsPi0Eta       ));  //  
	Vdmode.push_back(kD0toKsEPPiPiEta    ); NoMode.insert(map<int,DecayMode>::value_type( 32, kD0toKsEPPiPiEta    ));  // 
	//125                                                                                                         
	Vdmode.push_back(kD0toKsEPRhoGam     ); NoMode.insert(map<int,DecayMode>::value_type( 33, kD0toKsEPRhoGam     ));  //    
	//200                                                                                                         
	Vdmode.push_back(kDptoKPiPi          ); NoMode.insert(map<int,DecayMode>::value_type( 34, kDptoKPiPi          ));  //   
	Vdmode.push_back(kDptoKPiPiPi0       ); NoMode.insert(map<int,DecayMode>::value_type( 35, kDptoKPiPiPi0       ));  //   
	Vdmode.push_back(kDptoKsPi           ); NoMode.insert(map<int,DecayMode>::value_type( 36, kDptoKsPi           ));  // 
	Vdmode.push_back(kDptoKsPiPi0        ); NoMode.insert(map<int,DecayMode>::value_type( 37, kDptoKsPiPi0        ));  // 
	Vdmode.push_back(kDptoKsPiPiPi       ); NoMode.insert(map<int,DecayMode>::value_type( 38, kDptoKsPiPiPi       ));  // 
	Vdmode.push_back(kDptoKKPi           ); NoMode.insert(map<int,DecayMode>::value_type( 39, kDptoKKPi           ));  // 
	Vdmode.push_back(kDptoPiPi0          ); NoMode.insert(map<int,DecayMode>::value_type( 40, kDptoPiPi0          ));  //   
	Vdmode.push_back(kDptoKPi0           ); NoMode.insert(map<int,DecayMode>::value_type( 41, kDptoKPi0           ));  // 
	Vdmode.push_back(kDptoKsK            ); NoMode.insert(map<int,DecayMode>::value_type( 42, kDptoKsK            ));  // 
	Vdmode.push_back(kDptoPiPiPi         ); NoMode.insert(map<int,DecayMode>::value_type( 43, kDptoPiPiPi         ));  // 
	Vdmode.push_back(kDptoPiPi0Pi0       ); NoMode.insert(map<int,DecayMode>::value_type( 44, kDptoPiPi0Pi0       ));  // 
	Vdmode.push_back(kDptoKsKsPi         ); NoMode.insert(map<int,DecayMode>::value_type( 45, kDptoKsKsPi         ));  //   
	Vdmode.push_back(kDptoKsKPi0         ); NoMode.insert(map<int,DecayMode>::value_type( 46, kDptoKsKPi0         ));  // 
	Vdmode.push_back(kDptoKsKsK          ); NoMode.insert(map<int,DecayMode>::value_type( 47, kDptoKsKsK          ));  // 
	Vdmode.push_back(kDptoPiPiPiPi0      ); NoMode.insert(map<int,DecayMode>::value_type( 48, kDptoPiPiPiPi0      ));  // 
	Vdmode.push_back(kDptoKsPiPi0Pi0     ); NoMode.insert(map<int,DecayMode>::value_type( 49, kDptoKsPiPi0Pi0     ));  // 
	Vdmode.push_back(kDptoKsKplusPiPi    ); NoMode.insert(map<int,DecayMode>::value_type( 50, kDptoKsKplusPiPi    ));  //   
	Vdmode.push_back(kDptoKsKminusPiPi   ); NoMode.insert(map<int,DecayMode>::value_type( 51, kDptoKsKminusPiPi   ));  // 
	Vdmode.push_back(kDptoKKPiPi0        ); NoMode.insert(map<int,DecayMode>::value_type( 52, kDptoKKPiPi0        ));  // 
	Vdmode.push_back(kDptoPiPiPiPiPi     ); NoMode.insert(map<int,DecayMode>::value_type( 53, kDptoPiPiPiPiPi     ));  // 
	Vdmode.push_back(kDptoKPiPiPiPi      ); NoMode.insert(map<int,DecayMode>::value_type( 54, kDptoKPiPiPiPi      ));  // 
	Vdmode.push_back(kDptoPiEta          ); NoMode.insert(map<int,DecayMode>::value_type( 55, kDptoPiEta          ));  //   
	Vdmode.push_back(kDptoKsPiEta        ); NoMode.insert(map<int,DecayMode>::value_type( 56, kDptoKsPiEta        ));  //   
	//                                                                                                            
	Vdmode.push_back(kDstoKsK            ); NoMode.insert(map<int,DecayMode>::value_type( 57, kDstoKsK            ));  //   
	Vdmode.push_back(kDstoKKPi           ); NoMode.insert(map<int,DecayMode>::value_type( 58, kDstoKKPi           ));  // 
	Vdmode.push_back(kDstoKsKPi0         ); NoMode.insert(map<int,DecayMode>::value_type( 59, kDstoKsKPi0         ));  // 
	Vdmode.push_back(kDstoKsKsPi         ); NoMode.insert(map<int,DecayMode>::value_type( 60, kDstoKsKsPi         ));  //   
	Vdmode.push_back(kDstoKKPiPi0        ); NoMode.insert(map<int,DecayMode>::value_type( 61, kDstoKKPiPi0        ));  // 
	Vdmode.push_back(kDstoKsKplusPiPi    ); NoMode.insert(map<int,DecayMode>::value_type( 62, kDstoKsKplusPiPi    ));  // 
	Vdmode.push_back(kDstoKsKminusPiPi   ); NoMode.insert(map<int,DecayMode>::value_type( 63, kDstoKsKminusPiPi   ));  // 
	Vdmode.push_back(kDstoKKPiPiPi       ); NoMode.insert(map<int,DecayMode>::value_type( 64, kDstoKKPiPiPi       ));  // 
	Vdmode.push_back(kDstoPiPi0          ); NoMode.insert(map<int,DecayMode>::value_type( 65, kDstoPiPi0          ));  //   
	Vdmode.push_back(kDstoPiPiPi         ); NoMode.insert(map<int,DecayMode>::value_type( 66, kDstoPiPiPi         ));  //  
	Vdmode.push_back(kDstoPiPiPiPi0      ); NoMode.insert(map<int,DecayMode>::value_type( 67, kDstoPiPiPiPi0      ));  // 
	Vdmode.push_back(kDstoPiPiPiPiPi     ); NoMode.insert(map<int,DecayMode>::value_type( 68, kDstoPiPiPiPiPi     ));  // 
	Vdmode.push_back(kDstoPiPiPiPiPiPi0  ); NoMode.insert(map<int,DecayMode>::value_type( 69, kDstoPiPiPiPiPiPi0  ));  // 
	Vdmode.push_back(kDstoPiEta          ); NoMode.insert(map<int,DecayMode>::value_type( 70, kDstoPiEta          ));  //   
	Vdmode.push_back(kDstoPiPi0Eta       ); NoMode.insert(map<int,DecayMode>::value_type( 71, kDstoPiPi0Eta       ));  // 
	Vdmode.push_back(kDstoPiPiPiEta      ); NoMode.insert(map<int,DecayMode>::value_type( 72, kDstoPiPiPiEta      ));  // 
	Vdmode.push_back(kDstoPiEPPiPiEta    ); NoMode.insert(map<int,DecayMode>::value_type( 73, kDstoPiEPPiPiEta    ));  // 
	Vdmode.push_back(kDstoPiPi0EPPiPiEta ); NoMode.insert(map<int,DecayMode>::value_type( 74, kDstoPiPi0EPPiPiEta ));  // 
	Vdmode.push_back(kDstoPiEPRhoGam     ); NoMode.insert(map<int,DecayMode>::value_type( 75, kDstoPiEPRhoGam     ));  //   
	Vdmode.push_back(kDstoPiPi0EPRhoGam  ); NoMode.insert(map<int,DecayMode>::value_type( 76, kDstoPiPi0EPRhoGam  ));  // 
	Vdmode.push_back(kDstoKsPi           ); NoMode.insert(map<int,DecayMode>::value_type( 77, kDstoKsPi           ));  // 
	Vdmode.push_back(kDstoKsPiPi0        ); NoMode.insert(map<int,DecayMode>::value_type( 78, kDstoKsPiPi0        ));  // 
	Vdmode.push_back(kDstoKPiPi          ); NoMode.insert(map<int,DecayMode>::value_type( 79, kDstoKPiPi          ));  // 
	Vdmode.push_back(kDstoKPiPiPi0       ); NoMode.insert(map<int,DecayMode>::value_type( 80, kDstoKPiPiPi0       ));  //   
	Vdmode.push_back(kDstoKKK            ); NoMode.insert(map<int,DecayMode>::value_type( 81, kDstoKKK            ));  //   
	Vdmode.push_back(kUnknown            ); NoMode.insert(map<int,DecayMode>::value_type( 82, kUnknown            ));  //   
	// start D0, Br from PDG2012
	PName.insert(map<int,char* >::value_type(kD0toKPi           ,(char*)      "D^{0}#rightarrow K^{-}#pi^{+}"                            ));
	MName.insert(map<int,char* >::value_type(kD0toKPi           ,(char*)"#bar{D}^{0}#rightarrow K^{+}#pi^{-}"                            ));
	Br   .insert(map<int,double>::value_type(kD0toKPi           ,0.0388            )); 
	dBr  .insert(map<int,double>::value_type(kD0toKPi           ,0.0005            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKPiPi0        ,(char*)      "D^{0}#rightarrow K^{-}#pi^{+}#pi^{0}"                     ));
	MName.insert(map<int,char* >::value_type(kD0toKPiPi0        ,(char*)"#bar{D}^{0}#rightarrow K^{+}#pi^{-}#pi^{0}"                     ));
	Br   .insert(map<int,double>::value_type(kD0toKPiPi0        ,0.139             )); 
	dBr  .insert(map<int,double>::value_type(kD0toKPiPi0        ,0.005             )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKPiPi0Pi0     ,(char*)      "D^{0}#rightarrow K^{-}#pi^{+}#pi^{0}#pi^{0}"              ));
	MName.insert(map<int,char* >::value_type(kD0toKPiPi0Pi0     ,(char*)"#bar{D}^{0}#rightarrow K^{+}#pi^{-}#pi^{0}#pi^{0}"              ));
	Br   .insert(map<int,double>::value_type(kD0toKPiPi0Pi0     ,0.0405            ));// isospin conservation ??? 
	dBr  .insert(map<int,double>::value_type(kD0toKPiPi0Pi0     ,0.0011            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKPiPiPi       ,(char*)      "D^{0}#rightarrow K^{-}#pi^{+}#pi^{+}#pi^{-}"              ));
	MName.insert(map<int,char* >::value_type(kD0toKPiPiPi       ,(char*)"#bar{D}^{0}#rightarrow K^{+}#pi^{-}#pi^{-}#pi^{+}"              ));
	Br   .insert(map<int,double>::value_type(kD0toKPiPiPi       ,0.0809            )); 
	dBr  .insert(map<int,double>::value_type(kD0toKPiPiPi       ,0.0021            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKPiPiPiPi0    ,(char*)      "D^{0}#rightarrow K^{-}#pi^{+}#pi^{+}#pi^{-}#pi^{0}"       ));
	MName.insert(map<int,char* >::value_type(kD0toKPiPiPiPi0    ,(char*)"#bar{D}^{0}#rightarrow K^{+}#pi^{-}#pi^{-}#pi^{+}#pi^{0}"       ));
	Br   .insert(map<int,double>::value_type(kD0toKPiPiPiPi0    ,0.042             )); 
	dBr  .insert(map<int,double>::value_type(kD0toKPiPiPiPi0    ,0.004             )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKPiEta        ,(char*)      "D^{0}#rightarrow K^{-}#pi^{+}#eta"                        ));
	MName.insert(map<int,char* >::value_type(kD0toKPiEta        ,(char*)"#bar{D}^{0}#rightarrow K^{+}#pi^{-}#eta"                        ));
	Br   .insert(map<int,double>::value_type(kD0toKPiEta        ,0.000             )); 
	dBr  .insert(map<int,double>::value_type(kD0toKPiEta        ,0.000             )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsKPi         ,(char*)      "D^{0}#rightarrow K_{S}K^{-}#pi^{+}"                       ));
	MName.insert(map<int,char* >::value_type(kD0toKsKPi         ,(char*)"#bar{D}^{0}#rightarrow K_{S}K^{+}#pi^{-}"                       ));
	Br   .insert(map<int,double>::value_type(kD0toKsKPi         ,0.0035            ));// KsK-Pi+ + KsK+Pi- ????
	dBr  .insert(map<int,double>::value_type(kD0toKsKPi         ,0.0005            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsKPiPi0      ,(char*)      "D^{0}#rightarrow K_{S}K^{-}#pi^{+}#pi^{0}"                ));
	MName.insert(map<int,char* >::value_type(kD0toKsKPiPi0      ,(char*)"#bar{D}^{0}#rightarrow K_{S}K^{+}#pi^{-}#pi^{0}"                ));
	Br   .insert(map<int,double>::value_type(kD0toKsKPiPi0      ,0.0000            ));// KsK-PiPi0 + + KsK+Pi-Pi0 ????
	dBr  .insert(map<int,double>::value_type(kD0toKsKPiPi0      ,0.0000            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsPiPi        ,(char*)      "D^{0}#rightarrow K_{S}#pi^{+}#pi^{-}"                     ));
	MName.insert(map<int,char* >::value_type(kD0toKsPiPi        ,(char*)"#bar{D}^{0}#rightarrow K_{S}#pi^{-}#pi^{+}"                     ));
	Br   .insert(map<int,double>::value_type(kD0toKsPiPi        ,0.0294            ));
	dBr  .insert(map<int,double>::value_type(kD0toKsPiPi        ,0.0016            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsPiPiPi0     ,(char*)      "D^{0}#rightarrow K_{S}#pi^{+}#pi^{-}#pi^{0}"              ));
	MName.insert(map<int,char* >::value_type(kD0toKsPiPiPi0     ,(char*)"#bar{D}^{0}#rightarrow K_{S}#pi^{-}#pi^{+}#pi^{0}"              ));
	Br   .insert(map<int,double>::value_type(kD0toKsPiPiPi0     ,0.054             ));
	dBr  .insert(map<int,double>::value_type(kD0toKsPiPiPi0     ,0.006             )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsPi0         ,(char*)      "D^{0}#rightarrow K_{S}#pi^{0}"                            ));
	MName.insert(map<int,char* >::value_type(kD0toKsPi0         ,(char*)"#bar{D}^{0}#rightarrow K_{S}#pi^{0}"                            ));
	Br   .insert(map<int,double>::value_type(kD0toKsPi0         ,0.0122            ));
	dBr  .insert(map<int,double>::value_type(kD0toKsPi0         ,0.0005            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toPiPiPi0       ,(char*)      "D^{0}#rightarrow #pi^{+}#pi^{-}#pi^{0}"                   ));
	MName.insert(map<int,char* >::value_type(kD0toPiPiPi0       ,(char*)"#bar{D}^{0}#rightarrow #pi^{-}#pi^{+}#pi^{0}"                   ));
	Br   .insert(map<int,double>::value_type(kD0toPiPiPi0       ,0.0144            ));
	dBr  .insert(map<int,double>::value_type(kD0toPiPiPi0       ,0.0006            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toPiPi          ,(char*)      "D^{0}#rightarrow #pi^{+}#pi^{-}"                          ));
	MName.insert(map<int,char* >::value_type(kD0toPiPi          ,(char*)"#bar{D}^{0}#rightarrow #pi^{-}#pi^{+}"                          ));
	Br   .insert(map<int,double>::value_type(kD0toPiPi          ,0.001397          ));
	dBr  .insert(map<int,double>::value_type(kD0toPiPi          ,0.000026          )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKK            ,(char*)      "D^{0}#rightarrow K^{-}K^{+}"                              ));
	MName.insert(map<int,char* >::value_type(kD0toKK            ,(char*)"#bar{D}^{0}#rightarrow K^{+}K^{-}"                              ));
	Br   .insert(map<int,double>::value_type(kD0toKK            ,0.00394           ));
	dBr  .insert(map<int,double>::value_type(kD0toKK            ,0.00007           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKKPi0         ,(char*)      "D^{0}#rightarrow K^{-}K^{+}#pi^{0}"                       ));
	MName.insert(map<int,char* >::value_type(kD0toKKPi0         ,(char*)"#bar{D}^{0}#rightarrow K^{+}K^{-}#pi^{0}"                       ));
	Br   .insert(map<int,double>::value_type(kD0toKKPi0         ,0.00329           ));
	dBr  .insert(map<int,double>::value_type(kD0toKKPi0         ,0.00013           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toPi0Pi0        ,(char*)      "D^{0}#rightarrow #pi^{0}#pi^{0}"                          ));
	MName.insert(map<int,char* >::value_type(kD0toPi0Pi0        ,(char*)"#bar{D}^{0}#rightarrow #pi^{0}#pi^{0}"                          ));
	Br   .insert(map<int,double>::value_type(kD0toPi0Pi0        ,0.00080           ));
	dBr  .insert(map<int,double>::value_type(kD0toPi0Pi0        ,0.00008           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsKs          ,(char*)      "D^{0}#rightarrow K_{S}K_{S}"                              ));
	MName.insert(map<int,char* >::value_type(kD0toKsKs          ,(char*)"#bar{D}^{0}#rightarrow K_{S}K_{S}"                              ));
	Br   .insert(map<int,double>::value_type(kD0toKsKs          ,0.00019           ));
	dBr  .insert(map<int,double>::value_type(kD0toKsKs          ,0.00007           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsKsPi0       ,(char*)      "D^{0}#rightarrow K_{S}K_{S}#pi^{0}"                       ));
	MName.insert(map<int,char* >::value_type(kD0toKsKsPi0       ,(char*)"#bar{D}^{0}#rightarrow K_{S}K_{S}#pi^{0}"                       ));
	Br   .insert(map<int,double>::value_type(kD0toKsKsPi0       ,0.00059           ));// upper limit
	dBr  .insert(map<int,double>::value_type(kD0toKsKsPi0       ,0.00000           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsPi0Pi0      ,(char*)      "D^{0}#rightarrow K_{S}#pi^{0}#pi^{0}"                     ));
	MName.insert(map<int,char* >::value_type(kD0toKsPi0Pi0      ,(char*)"#bar{D}^{0}#rightarrow K_{S}#pi^{0}#pi^{0}"                     ));
	Br   .insert(map<int,double>::value_type(kD0toKsPi0Pi0      ,0.0083            ));
	dBr  .insert(map<int,double>::value_type(kD0toKsPi0Pi0      ,0.0006            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsKK          ,(char*)      "D^{0}#rightarrow K_{S}K^{-}K^{+}"                         ));
	MName.insert(map<int,char* >::value_type(kD0toKsKK          ,(char*)"#bar{D}^{0}#rightarrow K_{S}K^{+}K^{-}"                         ));
	Br   .insert(map<int,double>::value_type(kD0toKsKK          ,0.00465           ));
	dBr  .insert(map<int,double>::value_type(kD0toKsKK          ,0.00030           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsEta         ,(char*)      "D^{0}#rightarrow K_{S}#eta"                               ));
	MName.insert(map<int,char* >::value_type(kD0toKsEta         ,(char*)"#bar{D}^{0}#rightarrow K_{S}#eta"                               ));
	Br   .insert(map<int,double>::value_type(kD0toKsEta         ,0.00169           ));// from eta-->pi+pi-pi0
	dBr  .insert(map<int,double>::value_type(kD0toKsEta         ,0.00006           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toPi0Pi0Pi0     ,(char*)      "D^{0}#rightarrow #pi^{0}#pi^{0}#pi^{0}"                   ));
	MName.insert(map<int,char* >::value_type(kD0toPi0Pi0Pi0     ,(char*)"#bar{D}^{0}#rightarrow #pi^{0}#pi^{0}#pi^{0}"                   ));
	Br   .insert(map<int,double>::value_type(kD0toPi0Pi0Pi0     ,0.00035           ));// upper limit
	dBr  .insert(map<int,double>::value_type(kD0toPi0Pi0Pi0     ,0.00000           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsKsKs        ,(char*)      "D^{0}#rightarrow K_{S}K_{S}K_{S}"                         ));
	MName.insert(map<int,char* >::value_type(kD0toKsKsKs        ,(char*)"#bar{D}^{0}#rightarrow K_{S}K_{S}K_{S}"                         ));
	Br   .insert(map<int,double>::value_type(kD0toKsKsKs        ,0.00095           ));
	dBr  .insert(map<int,double>::value_type(kD0toKsKsKs        ,0.00013           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toPiPiPiPi      ,(char*)      "D^{0}#rightarrow 2(#pi^{+}#pi^{-})"                       ));
	MName.insert(map<int,char* >::value_type(kD0toPiPiPiPi      ,(char*)"#bar{D}^{0}#rightarrow 2(#pi^{-}#pi^{+})"                       ));
	Br   .insert(map<int,double>::value_type(kD0toPiPiPiPi      ,0.00744           ));
	dBr  .insert(map<int,double>::value_type(kD0toPiPiPiPi      ,0.00021           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toPiPiPi0Pi0    ,(char*)      "D^{0}#rightarrow #pi^{+}#pi^{-}#pi^{0}#pi^{0}"            ));
	MName.insert(map<int,char* >::value_type(kD0toPiPiPi0Pi0    ,(char*)"#bar{D}^{0}#rightarrow #pi^{-}#pi^{+}#pi^{0}#pi^{0}"            ));
	Br   .insert(map<int,double>::value_type(kD0toPiPiPi0Pi0    ,0.0100            ));
	dBr  .insert(map<int,double>::value_type(kD0toPiPiPi0Pi0    ,0.0009            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKKPiPi        ,(char*)      "D^{0}#rightarrow K^{-}K^{+}#pi^{+}#pi^{-}"                ));
	MName.insert(map<int,char* >::value_type(kD0toKKPiPi        ,(char*)"#bar{D}^{0}#rightarrow K^{+}K^{-}#pi^{-}#pi^{+}"                ));
	Br   .insert(map<int,double>::value_type(kD0toKKPiPi        ,0.00243           ));
	dBr  .insert(map<int,double>::value_type(kD0toKKPiPi        ,0.00012           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKKPi0Pi0      ,(char*)      "D^{0}#rightarrow K^{-}K^{+}#pi^{0}#pi^{0}"                ));
	MName.insert(map<int,char* >::value_type(kD0toKKPi0Pi0      ,(char*)"#bar{D}^{0}#rightarrow K^{+}K^{-}#pi^{0}#pi^{0}"                ));
	Br   .insert(map<int,double>::value_type(kD0toKKPi0Pi0      ,0.00122           ));// Isospin conservation ???
	dBr  .insert(map<int,double>::value_type(kD0toKKPi0Pi0      ,0.00006           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsKsPiPi      ,(char*)      "D^{0}#rightarrow K_{S}K_{S}#pi^{+}#pi^{-}"                ));
	MName.insert(map<int,char* >::value_type(kD0toKsKsPiPi      ,(char*)"#bar{D}^{0}#rightarrow K_{S}K_{S}#pi^{-}#pi^{+}"                ));
	Br   .insert(map<int,double>::value_type(kD0toKsKsPiPi      ,0.00128           ));
	dBr  .insert(map<int,double>::value_type(kD0toKsKsPiPi      ,0.00024           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toPiPiPiPiPi0   ,(char*)      "D^{0}#rightarrow #pi^{+}#pi^{+}#pi^{-}#pi^{-}#pi^{0}"     ));
	MName.insert(map<int,char* >::value_type(kD0toPiPiPiPiPi0   ,(char*)"#bar{D}^{0}#rightarrow #pi^{-}#pi^{-}#pi^{+}#pi^{+}#pi^{0}"     ));
	Br   .insert(map<int,double>::value_type(kD0toPiPiPiPiPi0   ,0.0042            ));
	dBr  .insert(map<int,double>::value_type(kD0toPiPiPiPiPi0   ,0.0005            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsPiPiPiPi    ,(char*)      "D^{0}#rightarrow K_{S}#pi^{+}#pi^{+}#pi^{-}#pi^{-}"       ));
	MName.insert(map<int,char* >::value_type(kD0toKsPiPiPiPi    ,(char*)"#bar{D}^{0}#rightarrow K_{S}#pi^{-}#pi^{-}#pi^{+}#pi^{+}"       ));
	Br   .insert(map<int,double>::value_type(kD0toKsPiPiPiPi    ,0.00280           ));
	dBr  .insert(map<int,double>::value_type(kD0toKsPiPiPiPi    ,0.00030           )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKKPiPiPi0     ,(char*)      "D^{0}#rightarrow K^{-}K^{+}#pi^{+}#pi^{-}#pi^{0}"         ));
	MName.insert(map<int,char* >::value_type(kD0toKKPiPiPi0     ,(char*)"#bar{D}^{0}#rightarrow K^{+}K^{-}#pi^{-}#pi^{+}#pi^{0}"         ));
	Br   .insert(map<int,double>::value_type(kD0toKKPiPiPi0     ,0.0031            ));
	dBr  .insert(map<int,double>::value_type(kD0toKKPiPiPi0     ,0.0020            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsPi0Eta      ,(char*)      "D^{0}#rightarrow K_{S}#pi^{0}#eta"                        ));
	MName.insert(map<int,char* >::value_type(kD0toKsPi0Eta      ,(char*)"#bar{D}^{0}#rightarrow K_{S}#pi^{0}#eta"                        ));
	Br   .insert(map<int,double>::value_type(kD0toKsPi0Eta      ,0.0056            ));//0.392???
	dBr  .insert(map<int,double>::value_type(kD0toKsPi0Eta      ,0.0012            )); 
	//
	PName.insert(map<int,char* >::value_type(kD0toKsEPPiPiEta   ,(char*)      "D^{0}#rightarrow K_{S}#eta^{'}(#pi^{+}#pi^{-}#eta)"       ));
	MName.insert(map<int,char* >::value_type(kD0toKsEPPiPiEta   ,(char*)"#bar{D}^{0}#rightarrow K_{S}#eta^{'}(#pi^{-}#pi^{+}#eta)"       ));
	Br   .insert(map<int,double>::value_type(kD0toKsEPPiPiEta   ,0.00402           ));
	dBr  .insert(map<int,double>::value_type(kD0toKsEPPiPiEta   ,0.00000           ));// ????  
	//
	PName.insert(map<int,char* >::value_type(kD0toKsEPRhoGam    ,(char*)      "D^{0}#rightarrow K_{S}#eta^{'}(#gamma#rho)"               ));
	MName.insert(map<int,char* >::value_type(kD0toKsEPRhoGam    ,(char*)"#bar{D}^{0}#rightarrow K_{S}#eta^{'}(#gamma#rho)"               ));
	Br   .insert(map<int,double>::value_type(kD0toKsEPRhoGam    ,0.00272           ));
	dBr  .insert(map<int,double>::value_type(kD0toKsEPRhoGam    ,0.00000           ));// ???? 
	// start D+
	PName.insert(map<int,char* >::value_type(kDptoKPiPi         ,(char*)"D^{+}#rightarrow K^{-}#pi^{+}#pi^{+}"                           ));
	MName.insert(map<int,char* >::value_type(kDptoKPiPi         ,(char*)"D^{-}#rightarrow K^{+}#pi^{-}#pi^{-}"                           ));
	Br   .insert(map<int,double>::value_type(kDptoKPiPi         ,0.0913            ));
	dBr  .insert(map<int,double>::value_type(kDptoKPiPi         ,0.0019            ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKPiPiPi0      ,(char*)"D^{+}#rightarrow K^{-}#pi^{+}#pi^{+}#pi^{0}"                    ));
	MName.insert(map<int,char* >::value_type(kDptoKPiPiPi0      ,(char*)"D^{-}#rightarrow K^{+}#pi^{-}#pi^{-}#pi^{0}"                    ));
	Br   .insert(map<int,double>::value_type(kDptoKPiPiPi0      ,0.0599            ));
	dBr  .insert(map<int,double>::value_type(kDptoKPiPiPi0      ,0.0018            ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKsPi          ,(char*)"D^{+}#rightarrow K_{S}#pi^{+}"                                  ));
	MName.insert(map<int,char* >::value_type(kDptoKsPi          ,(char*)"D^{-}#rightarrow K_{S}#pi^{-}"                                  ));
	Br   .insert(map<int,double>::value_type(kDptoKsPi          ,0.0147            ));
	dBr  .insert(map<int,double>::value_type(kDptoKsPi          ,0.0007            ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKsPiPi0       ,(char*)"D^{+}#rightarrow K_{S}#pi^{+}#pi^{0}"                           ));
	MName.insert(map<int,char* >::value_type(kDptoKsPiPi0       ,(char*)"D^{-}#rightarrow K_{S}#pi^{-}#pi^{0}"                           ));
	Br   .insert(map<int,double>::value_type(kDptoKsPiPi0       ,0.0699            ));
	dBr  .insert(map<int,double>::value_type(kDptoKsPiPi0       ,0.0027            ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKsPiPiPi      ,(char*)"D^{+}#rightarrow K_{S}#pi^{+}#pi^{+}#pi^{-}"                    ));
	MName.insert(map<int,char* >::value_type(kDptoKsPiPiPi      ,(char*)"D^{-}#rightarrow K_{S}#pi^{-}#pi^{-}#pi^{+}"                    ));
	Br   .insert(map<int,double>::value_type(kDptoKsPiPiPi      ,0.0312            ));
	dBr  .insert(map<int,double>::value_type(kDptoKsPiPiPi      ,0.0011            ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKKPi          ,(char*)"D^{+}#rightarrow K^{-}K^{+}#pi^{+}"                             ));
	MName.insert(map<int,char* >::value_type(kDptoKKPi          ,(char*)"D^{-}#rightarrow K^{+}K^{-}#pi^{-}"                             ));
	Br   .insert(map<int,double>::value_type(kDptoKKPi          ,0.00954           ));
	dBr  .insert(map<int,double>::value_type(kDptoKKPi          ,0.00026           ));
	//
	PName.insert(map<int,char* >::value_type(kDptoPiPi0         ,(char*)"D^{+}#rightarrow #pi^{+}#pi^{0}"                                ));
	MName.insert(map<int,char* >::value_type(kDptoPiPi0         ,(char*)"D^{-}#rightarrow #pi^{-}#pi^{0}"                                ));
	Br   .insert(map<int,double>::value_type(kDptoPiPi0         ,0.00119           ));
	dBr  .insert(map<int,double>::value_type(kDptoPiPi0         ,0.00006           ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKPi0          ,(char*)"D^{+}#rightarrow K^{+}#pi^{0}"                                  ));
	MName.insert(map<int,char* >::value_type(kDptoKPi0          ,(char*)"D^{-}#rightarrow K^{-}#pi^{0}"                                  ));
	Br   .insert(map<int,double>::value_type(kDptoKPi0          ,0.000183          ));
	dBr  .insert(map<int,double>::value_type(kDptoKPi0          ,0.000026          ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKsK           ,(char*)"D^{+}#rightarrow K_{S}K^{+}"                                    ));
	MName.insert(map<int,char* >::value_type(kDptoKsK           ,(char*)"D^{-}#rightarrow K_{S}K^{-}"                                    ));
	Br   .insert(map<int,double>::value_type(kDptoKsK           ,0.00283          ));
	dBr  .insert(map<int,double>::value_type(kDptoKsK           ,0.00016          ));
	//
	PName.insert(map<int,char* >::value_type(kDptoPiPiPi        ,(char*)"D^{+}#rightarrow #pi^{+}#pi^{+}#pi^{-}"                         ));
	MName.insert(map<int,char* >::value_type(kDptoPiPiPi        ,(char*)"D^{-}#rightarrow #pi^{-}#pi^{-}#pi^{+}"                         ));
	Br   .insert(map<int,double>::value_type(kDptoPiPiPi        ,0.00318           ));
	dBr  .insert(map<int,double>::value_type(kDptoPiPiPi        ,0.00018           ));
	//
	PName.insert(map<int,char* >::value_type(kDptoPiPi0Pi0      ,(char*)"D^{+}#rightarrow #pi^{+}#pi^{0}#pi^{0}"                         ));
	MName.insert(map<int,char* >::value_type(kDptoPiPi0Pi0      ,(char*)"D^{-}#rightarrow #pi^{-}#pi^{0}#pi^{0}"                         ));
	Br   .insert(map<int,double>::value_type(kDptoPiPi0Pi0      ,0.0046            ));
	dBr  .insert(map<int,double>::value_type(kDptoPiPi0Pi0      ,0.0004            ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKsKsPi        ,(char*)"D^{+}#rightarrow K_{S}K_{S}#pi^{+}"                             ));
	MName.insert(map<int,char* >::value_type(kDptoKsKsPi        ,(char*)"D^{-}#rightarrow K_{S}K_{S}#pi^{-}"                             ));
	Br   .insert(map<int,double>::value_type(kDptoKsKsPi        ,0.00000          ));
	dBr  .insert(map<int,double>::value_type(kDptoKsKsPi        ,0.00000          ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKsKPi0        ,(char*)"D^{+}#rightarrow K_{S}K^{+}#pi^{0}"                             ));
	MName.insert(map<int,char* >::value_type(kDptoKsKPi0        ,(char*)"D^{-}#rightarrow K_{S}K^{-}#pi^{0}"                             ));
	Br   .insert(map<int,double>::value_type(kDptoKsKPi0        ,0.00000          ));
	dBr  .insert(map<int,double>::value_type(kDptoKsKPi0        ,0.00000          ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKsKsK         ,(char*)"D^{+}#rightarrow K_{S}K_{S}K^{+}"                               ));
	MName.insert(map<int,char* >::value_type(kDptoKsKsK         ,(char*)"D^{-}#rightarrow K_{S}K_{S}K^{-}"                               ));
	Br   .insert(map<int,double>::value_type(kDptoKsKsK         ,0.0045           ));
	dBr  .insert(map<int,double>::value_type(kDptoKsKsK         ,0.0020           ));
	//
	PName.insert(map<int,char* >::value_type(kDptoPiPiPiPi0     ,(char*)"D^{+}#rightarrow #pi^{+}#pi^{+}#pi^{-}#pi^{0}"                  ));
	MName.insert(map<int,char* >::value_type(kDptoPiPiPiPi0     ,(char*)"D^{-}#rightarrow #pi^{-}#pi^{-}#pi^{+}#pi^{0}"                  ));
	Br   .insert(map<int,double>::value_type(kDptoPiPiPiPi0     ,0.0113            ));
	dBr  .insert(map<int,double>::value_type(kDptoPiPiPiPi0     ,0.0008            ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKsPiPi0Pi0    ,(char*)"D^{+}#rightarrow K_{S}#pi^{+}#pi^{0}#pi^{0}"                    ));
	MName.insert(map<int,char* >::value_type(kDptoKsPiPi0Pi0    ,(char*)"D^{-}#rightarrow K_{S}#pi^{-}#pi^{0}#pi^{0}"                    ));
	Br   .insert(map<int,double>::value_type(kDptoKsPiPi0Pi0    ,0.0000            ));
	dBr  .insert(map<int,double>::value_type(kDptoKsPiPi0Pi0    ,0.0000            ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKsKplusPiPi   ,(char*)"D^{+}#rightarrow K_{S}K^{+}#pi^{+}#pi^{-}"                      ));
	MName.insert(map<int,char* >::value_type(kDptoKsKplusPiPi   ,(char*)"D^{-}#rightarrow K_{S}K^{-}#pi^{-}#pi^{+}"                      ));
	Br   .insert(map<int,double>::value_type(kDptoKsKplusPiPi   ,0.00175           ));
	dBr  .insert(map<int,double>::value_type(kDptoKsKplusPiPi   ,0.00018           ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKsKminusPiPi  ,(char*)"D^{+}#rightarrow K_{S}K^{-}#pi^{+}#pi^{+}"                      ));
	MName.insert(map<int,char* >::value_type(kDptoKsKminusPiPi  ,(char*)"D^{-}#rightarrow K_{S}K^{+}#pi^{-}#pi^{-}"                      ));
	Br   .insert(map<int,double>::value_type(kDptoKsKminusPiPi  ,0.00240           ));
	dBr  .insert(map<int,double>::value_type(kDptoKsKminusPiPi  ,0.00018           ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKKPiPi0       ,(char*)"D^{+}#rightarrow K^{-}K^{+}#pi^{+}#pi^{0}"                      ));
	MName.insert(map<int,char* >::value_type(kDptoKKPiPi0       ,(char*)"D^{-}#rightarrow K^{+}K^{-}#pi^{-}#pi^{0}"                      ));
	Br   .insert(map<int,double>::value_type(kDptoKKPiPi0       ,0.038             )); // poorly measured 0.023+0.015 ...  
	dBr  .insert(map<int,double>::value_type(kDptoKKPiPi0       ,0.015             ));
	//
	PName.insert(map<int,char* >::value_type(kDptoPiPiPiPiPi    ,(char*)"D^{+}#rightarrow #pi^{+}#pi^{+}#pi^{+}#pi^{-}#pi^{-}"           ));
	MName.insert(map<int,char* >::value_type(kDptoPiPiPiPiPi    ,(char*)"D^{-}#rightarrow #pi^{-}#pi^{-}#pi^{-}#pi^{+}#pi^{+}"           ));
	Br   .insert(map<int,double>::value_type(kDptoPiPiPiPiPi    ,0.00161           ));
	dBr  .insert(map<int,double>::value_type(kDptoPiPiPiPiPi    ,0.00016           ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKPiPiPiPi     ,(char*)"D^{+}#rightarrow K^{+}#pi^{+}#pi^{+}#pi^{-}#pi^{-}"             ));
	MName.insert(map<int,char* >::value_type(kDptoKPiPiPiPi     ,(char*)"D^{-}#rightarrow K^{-}#pi^{-}#pi^{-}#pi^{+}#pi^{+}"             ));
	Br   .insert(map<int,double>::value_type(kDptoKPiPiPiPi     ,0.0056            ));// D+-->K-pi+pi+pi+pi- in PDG2012
	dBr  .insert(map<int,double>::value_type(kDptoKPiPiPiPi     ,0.0005            ));
	//
	PName.insert(map<int,char* >::value_type(kDptoPiEta         ,(char*)"D^{+}#rightarrow #pi^{+}#eta"                                   ));
	MName.insert(map<int,char* >::value_type(kDptoPiEta         ,(char*)"D^{-}#rightarrow #pi^{-}#eta"                                   ));
	Br   .insert(map<int,double>::value_type(kDptoPiEta         ,0.00353           ));
	dBr  .insert(map<int,double>::value_type(kDptoPiEta         ,0.00021           ));
	//
	PName.insert(map<int,char* >::value_type(kDptoKsPiEta       ,(char*)"D^{+}#rightarrow K_{S}#pi^{+}#eta"                              ));
	MName.insert(map<int,char* >::value_type(kDptoKsPiEta       ,(char*)"D^{-}#rightarrow K_{S}#pi^{-}#eta"                              ));
	Br   .insert(map<int,double>::value_type(kDptoKsPiEta       ,0.00000           ));
	dBr  .insert(map<int,double>::value_type(kDptoKsPiEta       ,0.00000           ));
	// start Ds 
	PName.insert(map<int,char* >::value_type(kDstoKsK           ,(char*)"D^{+}_{s}#rightarrow K_{S}K^{+}"                                ));
	MName.insert(map<int,char* >::value_type(kDstoKsK           ,(char*)"D^{-}_{s}#rightarrow K_{S}K^{-}"                                ));
	Br   .insert(map<int,double>::value_type(kDstoKsK           ,0.0148            ));
	dBr  .insert(map<int,double>::value_type(kDstoKsK           ,0.0008            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoKKPi          ,(char*)"D^{+}_{s}#rightarrow K^{-}K^{+}#pi^{+}"                         ));
	MName.insert(map<int,char* >::value_type(kDstoKKPi          ,(char*)"D^{-}_{s}#rightarrow K^{+}K^{-}#pi^{-}"                         ));
	Br   .insert(map<int,double>::value_type(kDstoKKPi          ,0.0549            ));
	dBr  .insert(map<int,double>::value_type(kDstoKKPi          ,0.0027            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoKsKPi0        ,(char*)"D^{+}_{s}#rightarrow K_{S}K^{+}#pi^{0}"                         ));
	MName.insert(map<int,char* >::value_type(kDstoKsKPi0        ,(char*)"D^{-}_{s}#rightarrow K_{S}K^{-}#pi^{0}"                         ));
	Br   .insert(map<int,double>::value_type(kDstoKsKPi0        ,0.0000            )); //???
	dBr  .insert(map<int,double>::value_type(kDstoKsKPi0        ,0.0000            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoKsKsPi        ,(char*)"D^{+}_{s}#rightarrow K_{S}K_{S}#pi^{+}"                         ));
	MName.insert(map<int,char* >::value_type(kDstoKsKsPi        ,(char*)"D^{-}_{s}#rightarrow K_{S}K_{S}#pi^{-}"                         ));
	Br   .insert(map<int,double>::value_type(kDstoKsKsPi        ,0.0000            )); //???
	dBr  .insert(map<int,double>::value_type(kDstoKsKsPi        ,0.0000            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoKKPiPi0       ,(char*)"D^{+}_{s}#rightarrow K^{-}K^{+}#pi^{+}#pi^{0}"                  ));
	MName.insert(map<int,char* >::value_type(kDstoKKPiPi0       ,(char*)"D^{-}_{s}#rightarrow K^{+}K^{-}#pi^{-}#pi^{0}"                  ));
	Br   .insert(map<int,double>::value_type(kDstoKKPiPi0       ,0.056             ));
	dBr  .insert(map<int,double>::value_type(kDstoKKPiPi0       ,0.005             ));
	//
	PName.insert(map<int,char* >::value_type(kDstoKsKplusPiPi   ,(char*)"D^{+}_{s}#rightarrow K_{S}K^{+}#pi^{+}#pi^{-}"                  ));
	MName.insert(map<int,char* >::value_type(kDstoKsKplusPiPi   ,(char*)"D^{-}_{s}#rightarrow K_{S}K^{-}#pi^{-}#pi^{+}"                  ));
	Br   .insert(map<int,double>::value_type(kDstoKsKplusPiPi   ,0.0096            ));
	dBr  .insert(map<int,double>::value_type(kDstoKsKplusPiPi   ,0.0013            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoKsKminusPiPi  ,(char*)"D^{+}_{s}#rightarrow K_{S}K^{-}#pi^{+}#pi^{+}"                  ));
	MName.insert(map<int,char* >::value_type(kDstoKsKminusPiPi  ,(char*)"D^{-}_{s}#rightarrow K_{S}K^{+}#pi^{-}#pi^{-}"                  ));
	Br   .insert(map<int,double>::value_type(kDstoKsKminusPiPi  ,0.0164            ));
	dBr  .insert(map<int,double>::value_type(kDstoKsKminusPiPi  ,0.0012            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoKKPiPiPi      ,(char*)"D^{+}_{s}#rightarrow K^{-}K^{+}#pi^{+}#pi^{+}#pi^{-}"           ));
	MName.insert(map<int,char* >::value_type(kDstoKKPiPiPi      ,(char*)"D^{-}_{s}#rightarrow K^{+}K^{-}#pi^{-}#pi^{-}#pi^{+}"           ));
	Br   .insert(map<int,double>::value_type(kDstoKKPiPiPi      ,0.0088            ));
	dBr  .insert(map<int,double>::value_type(kDstoKKPiPiPi      ,0.0013            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoPiPi0         ,(char*)"D^{+}_{s}#rightarrow #pi^{+}#pi^{0}"                            ));
	MName.insert(map<int,char* >::value_type(kDstoPiPi0         ,(char*)"D^{-}_{s}#rightarrow #pi^{-}#pi^{0}"                            ));
	Br   .insert(map<int,double>::value_type(kDstoPiPi0         ,0.00034           ));// upper limit 
	dBr  .insert(map<int,double>::value_type(kDstoPiPi0         ,0.00000           ));
	//
	PName.insert(map<int,char* >::value_type(kDstoPiPiPi        ,(char*)"D^{+}_{s}#rightarrow #pi^{+}#pi^{+}#pi^{-}"                     ));
	MName.insert(map<int,char* >::value_type(kDstoPiPiPi        ,(char*)"D^{-}_{s}#rightarrow #pi^{-}#pi^{-}#pi^{+}"                     ));
	Br   .insert(map<int,double>::value_type(kDstoPiPiPi        ,0.0110            ));
	dBr  .insert(map<int,double>::value_type(kDstoPiPiPi        ,0.0006            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoPiPiPiPi0     ,(char*)"D^{+}_{s}#rightarrow #pi^{+}#pi^{+}#pi^{-}#pi^{0}"              ));
	MName.insert(map<int,char* >::value_type(kDstoPiPiPiPi0     ,(char*)"D^{-}_{s}#rightarrow #pi^{-}#pi^{-}#pi^{+}#pi^{0}"              ));
	Br   .insert(map<int,double>::value_type(kDstoPiPiPiPi0     ,0.0208            ));//??? 0.0183+0.0025
	dBr  .insert(map<int,double>::value_type(kDstoPiPiPiPi0     ,0.0017            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoPiPiPiPiPi    ,(char*)"D^{+}_{s}#rightarrow #pi^{+}#pi^{+}#pi^{+}#pi^{-}#pi^{-}"       ));
	MName.insert(map<int,char* >::value_type(kDstoPiPiPiPiPi    ,(char*)"D^{-}_{s}#rightarrow #pi^{-}#pi^{-}#pi^{-}#pi^{+}#pi^{+}"       ));
	Br   .insert(map<int,double>::value_type(kDstoPiPiPiPiPi    ,0.0080            ));
	dBr  .insert(map<int,double>::value_type(kDstoPiPiPiPiPi    ,0.0009            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoPiPiPiPiPiPi0 ,(char*)"D^{+}_{s}#rightarrow #pi^{+}#pi^{+}#pi^{+}#pi^{-}#pi^{-}#pi^{0}"));
	MName.insert(map<int,char* >::value_type(kDstoPiPiPiPiPiPi0 ,(char*)"D^{-}_{s}#rightarrow #pi^{-}#pi^{-}#pi^{-}#pi^{+}#pi^{+}#pi^{0}"));
	Br   .insert(map<int,double>::value_type(kDstoPiPiPiPiPiPi0 ,0.049             ));
	dBr  .insert(map<int,double>::value_type(kDstoPiPiPiPiPiPi0 ,0.032             ));
	//
	PName.insert(map<int,char* >::value_type(kDstoPiEta         ,(char*)"D^{+}_{s}#rightarrow #pi^{+}#eta"                               ));
	MName.insert(map<int,char* >::value_type(kDstoPiEta         ,(char*)"D^{-}_{s}#rightarrow #pi^{-}#eta"                               ));
	Br   .insert(map<int,double>::value_type(kDstoPiEta         ,0.0183            ));
	dBr  .insert(map<int,double>::value_type(kDstoPiEta         ,0.0015            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoPiPi0Eta      ,(char*)"D^{+}_{s}#rightarrow #pi^{+}#pi^{0}#eta"                        ));
	MName.insert(map<int,char* >::value_type(kDstoPiPi0Eta      ,(char*)"D^{-}_{s}#rightarrow #pi^{-}#pi^{0}#eta"                        ));
	Br   .insert(map<int,double>::value_type(kDstoPiPi0Eta      ,0.089             ));// 0.089 + 0.050(upper limit)
	dBr  .insert(map<int,double>::value_type(kDstoPiPi0Eta      ,0.008             ));
	//
	PName.insert(map<int,char* >::value_type(kDstoPiPiPiEta     ,(char*)"D^{+}_{s}#rightarrow #pi^{+}#pi^{+}#pi^{-}#eta"                 ));
	MName.insert(map<int,char* >::value_type(kDstoPiPiPiEta     ,(char*)"D^{-}_{s}#rightarrow #pi^{-}#pi^{-}#pi^{+}#eta"                 ));
	Br   .insert(map<int,double>::value_type(kDstoPiPiPiEta     ,0.000             ));// ??? 
	dBr  .insert(map<int,double>::value_type(kDstoPiPiPiEta     ,0.000             ));
	//
	PName.insert(map<int,char* >::value_type(kDstoPiEPPiPiEta   ,(char*)"D^{+}_{s}#rightarrow #pi^{+}#eta^{'}(#pi#pi#eta)"               ));
	MName.insert(map<int,char* >::value_type(kDstoPiEPPiPiEta   ,(char*)"D^{-}_{s}#rightarrow #pi^{-}#eta^{'}(#pi#pi#eta)"               ));
	Br   .insert(map<int,double>::value_type(kDstoPiEPPiPiEta   ,0.0164            ));   
	dBr  .insert(map<int,double>::value_type(kDstoPiEPPiPiEta   ,0.0000            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoPiPi0EPPiPiEta,(char*)"D^{+}_{s}#rightarrow #pi^{+}#pi^{0}#eta^{'}(#pi#pi#eta)"        ));
	MName.insert(map<int,char* >::value_type(kDstoPiPi0EPPiPiEta,(char*)"D^{-}_{s}#rightarrow #pi^{-}#pi^{0}#eta^{'}(#pi#pi#eta)"        ));
	Br   .insert(map<int,double>::value_type(kDstoPiPi0EPPiPiEta,0.0000            )); //???
	dBr  .insert(map<int,double>::value_type(kDstoPiPi0EPPiPiEta,0.0000            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoPiEPRhoGam    ,(char*)"D^{+}_{s}#rightarrow #pi^{+}#eta^{'}(#gamma#rho)"               ));
	MName.insert(map<int,char* >::value_type(kDstoPiEPRhoGam    ,(char*)"D^{-}_{s}#rightarrow #pi^{-}#eta^{'}(#gamma#rho)"               ));
	Br   .insert(map<int,double>::value_type(kDstoPiEPRhoGam    ,0.0111            ));
	dBr  .insert(map<int,double>::value_type(kDstoPiEPRhoGam    ,0.0000            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoPiPi0EPRhoGam ,(char*)"D^{+}_{s}#rightarrow #pi^{+}#pi^{0}#eta^{'}(#gamma#rho)"        ));
	MName.insert(map<int,char* >::value_type(kDstoPiPi0EPRhoGam ,(char*)"D^{-}_{s}#rightarrow #pi^{-}#pi^{0}#eta^{'}(#gamma#rho)"        ));
	Br   .insert(map<int,double>::value_type(kDstoPiPi0EPRhoGam ,0.0000            ));//???
	dBr  .insert(map<int,double>::value_type(kDstoPiPi0EPRhoGam ,0.0000            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoKsPi          ,(char*)"D^{+}_{s}#rightarrow K_{S}#pi^{+}"                              ));
	MName.insert(map<int,char* >::value_type(kDstoKsPi          ,(char*)"D^{-}_{s}#rightarrow K_{S}#pi^{-}"                              ));
	Br   .insert(map<int,double>::value_type(kDstoKsPi          ,0.0121            ));
	dBr  .insert(map<int,double>::value_type(kDstoKsPi          ,0.0008            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoKsPiPi0       ,(char*)"D^{+}_{s}#rightarrow K_{S}#pi^{+}#pi^{0}"                       ));
	MName.insert(map<int,char* >::value_type(kDstoKsPiPi0       ,(char*)"D^{-}_{s}#rightarrow K_{S}#pi^{-}#pi^{0}"                       ));
	Br   .insert(map<int,double>::value_type(kDstoKsPiPi0       ,0.0100/2          ));
	dBr  .insert(map<int,double>::value_type(kDstoKsPiPi0       ,0.0018/2          ));
	//
	PName.insert(map<int,char* >::value_type(kDstoKPiPi         ,(char*)"D^{+}_{s}#rightarrow K^{+}#pi^{+}#pi^{-}"                       ));
	MName.insert(map<int,char* >::value_type(kDstoKPiPi         ,(char*)"D^{-}_{s}#rightarrow K^{-}#pi^{-}#pi^{+}"                       ));
	Br   .insert(map<int,double>::value_type(kDstoKPiPi         ,0.0069            ));
	dBr  .insert(map<int,double>::value_type(kDstoKPiPi         ,0.0005            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoKPiPiPi0      ,(char*)"D^{+}_{s}#rightarrow K^{+}#pi^{+}#pi^{-}#pi^{0}"                )); 
	MName.insert(map<int,char* >::value_type(kDstoKPiPiPi0      ,(char*)"D^{-}_{s}#rightarrow K^{-}#pi^{-}#pi^{+}#pi^{0}"                )); 
	Br   .insert(map<int,double>::value_type(kDstoKPiPiPi0      ,0.0000            )); //???
	dBr  .insert(map<int,double>::value_type(kDstoKPiPiPi0      ,0.0000            ));
	//
	PName.insert(map<int,char* >::value_type(kDstoKKK           ,(char*)"D^{+}_{s}#rightarrow K^{-}K^{+}K^{+}"                           ));
	MName.insert(map<int,char* >::value_type(kDstoKKK           ,(char*)"D^{-}_{s}#rightarrow K^{+}K^{-}K^{-}"                           ));
	Br   .insert(map<int,double>::value_type(kDstoKKK           ,0.000220          ));
	dBr  .insert(map<int,double>::value_type(kDstoKKK           ,0.000023          ));
	//
	PName.insert(map<int,char* >::value_type(kUnknown           ,(char*)"Sum of All"                                                     ));
	MName.insert(map<int,char* >::value_type(kUnknown           ,(char*)"Sum of All"                                                     ));
	//
	// number of Ks, nTRKs, nShowers, starting digit , number of K+/-
	NKinDTag.insert(pair<DecayMode, int>(kD0toKPi           , 2011));   // 0
	NKinDTag.insert(pair<DecayMode, int>(kD0toKPiPi0        , 2211));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKPiPi0Pi0     , 2411));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKPiPiPi       , 4011));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKPiPiPiPi0    , 4211));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKPiEta        , 2211));   // 5
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsKPi         ,14031));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsKPiPi0      ,14231));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsPiPi        ,14000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsPiPiPi0     ,14200));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsPi0         ,12200));   // 10
	NKinDTag.insert(pair<DecayMode, int>(kD0toPiPiPi0       , 2200));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toPiPi          , 2000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKK            , 2012));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKKPi0         , 2212));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toPi0Pi0        ,  400));   // 15
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsKs          ,24000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsKsPi0       ,24200));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsPi0Pi0      ,12400));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsKK          ,14032));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsEta         ,12200));   // 20
	NKinDTag.insert(pair<DecayMode, int>(kD0toPi0Pi0Pi0     ,  600));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsKsKs        ,36000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toPiPiPiPi      , 4000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toPiPiPi0Pi0    , 2400));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKKPiPi        , 4012));   // 25
	NKinDTag.insert(pair<DecayMode, int>(kD0toKKPi0Pi0      , 2412));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsKsPiPi      ,26000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toPiPiPiPiPi0   , 4200));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsPiPiPiPi    ,16000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKKPiPiPi0     , 4212));   // 30
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsPi0Eta      ,12400));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsEPPiPiEta   ,14200));   // 
	NKinDTag.insert(pair<DecayMode, int>(kD0toKsEPRhoGam    ,14100));   // 33 
	//   
	NKinDTag.insert(pair<DecayMode, int>(kDptoKPiPi         , 3011));   // 34
	NKinDTag.insert(pair<DecayMode, int>(kDptoKPiPiPi0      , 3211));   // 35
	NKinDTag.insert(pair<DecayMode, int>(kDptoKsPi          ,13000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoKsPiPi0       ,13200));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoKsPiPiPi      ,15000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoKKPi          , 3012));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoPiPi0         , 1200));   // 40
	NKinDTag.insert(pair<DecayMode, int>(kDptoKPi0          , 1211));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoKsK           ,13031));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoPiPiPi        , 3000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoPiPi0Pi0      , 1400));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoKsKsPi        ,25000));   // 45
	NKinDTag.insert(pair<DecayMode, int>(kDptoKsKPi0        ,13231));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoKsKsK         ,25051));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoPiPiPiPi0     , 3200));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoKsPiPi0Pi0    ,13400));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoKsKplusPiPi   ,15031));   // 50
	NKinDTag.insert(pair<DecayMode, int>(kDptoKsKminusPiPi  ,15031));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoKKPiPi0       , 3212));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoPiPiPiPiPi    , 5000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoKPiPiPiPi     , 5011));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDptoPiEta         , 1200));   // 55
	NKinDTag.insert(pair<DecayMode, int>(kDptoKsPiEta       ,13200));   // 56
	//
	NKinDTag.insert(pair<DecayMode, int>(kDstoKsK           ,13031));   // 57
	NKinDTag.insert(pair<DecayMode, int>(kDstoKKPi          , 3012));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoKsKPi0        ,13231));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoKsKsPi        ,25000));   // 60
	NKinDTag.insert(pair<DecayMode, int>(kDstoKKPiPi0       , 3212));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoKsKplusPiPi   ,15031));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoKsKminusPiPi  ,15031));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoKKPiPiPi      , 5012));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoPiPi0         , 1200));   // 65
	NKinDTag.insert(pair<DecayMode, int>(kDstoPiPiPi        , 3000));   //  
	NKinDTag.insert(pair<DecayMode, int>(kDstoPiPiPiPi0     , 3200));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoPiPiPiPiPi    , 5000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoPiPiPiPiPiPi0 , 5200));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoPiEta         , 1200));   // 70
	NKinDTag.insert(pair<DecayMode, int>(kDstoPiPi0Eta      , 1400));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoPiPiPiEta     , 3200));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoPiEPPiPiEta   , 3200));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoPiPi0EPPiPiEta, 3400));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoPiEPRhoGam    , 3100));   // 75
	NKinDTag.insert(pair<DecayMode, int>(kDstoPiPi0EPRhoGam , 3300));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoKsPi          ,13000));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoKsPiPi0       ,13200));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoKPiPi         , 3011));   // 
	NKinDTag.insert(pair<DecayMode, int>(kDstoKPiPiPi0      , 3211));   // 80
	NKinDTag.insert(pair<DecayMode, int>(kDstoKKK           , 3013));   // 81
	NKinDTag.insert(pair<DecayMode, int>(kUnknown           ,    0));   // 82
	//
	for (int i=0; i< MaxMode; i++ ){
		for (int j=0; j< MaxMode; j++ ){
			StatIJ[i][j]=0;
		}
	}
	//
	for (int i=0; i< (int)Vdmode.size(); i++ ){
		Status.insert(map<int,int>::value_type( (int)Vdmode[i], 0 ));	
	}
	/*
	   for ( map<int, char* >::const_iterator iter = PName.begin();
	   iter != PName.end(); ++iter ){
	   printf(" %4d \t %s \n", (int)iter->first ,iter->second );
	   }
	   for ( map<int, char* >::const_iterator iter = MName.begin();
	   iter != MName.end(); ++iter ){
	   printf(" %4d \t %s \n", (int)iter->first ,iter->second );
	   }

	   printf("check the vector and map\n");
	   printf("number of kMode's = %2d\n",(int)Vdmode.size());
	   printf("number of +++++++ = %2d\n",(int)PName .size());
	   printf("number of ------- = %2d\n",(int)MName .size());
	   for (int i=0; i< (int)Vdmode.size(); i++ ){
	   int km   = (int)find_Mode(i);
	   map< int, char*>::iterator posP = PName.find(km); 
	   map< int, char*>::iterator posM = MName.find(km); 
	   if (posP != PName.end()) 
	   {
	   printf(" %4d %4d \t  %s \n", i, posP->first , posP->second );
	   }
	   if (posP != MName.end()) 
	   {
	   printf(" %4d %4d \t  %s \n", i, posM->first , posM->second );
	   }
	   }
	 */
}

DTagName::~DTagName()
{

	FreeAll(Br      );
	FreeAll(dBr     );
	FreeAll(Vdmode  );
	FreeAll(PName   );
	FreeAll(MName   );
	FreeAll(Status  );
	FreeAll(NoMode  );
	FreeAll(NKinDTag);
}

int DTagName::GetNKinDTag   (const int decaymode)
{
	int nkindtag = 0;	
	map< DecayMode, int>::iterator pos = NKinDTag.find((DecayMode)decaymode); 
	if (pos != NKinDTag.end()) 
	{
		nkindtag=pos->second;
	}
	else
	{
		cout<<"no such a tag mode : "<<decaymode<<endl;
	}
	return nkindtag;
}

void DTagName::SetAllCharged()
{
	for (int i=0; i< (int)Vdmode.size(); i++ ){
		int nk=NKinDTag[(DecayMode)Vdmode[i]];
		nk=nk%1000;	
		nk=nk/100;
		if(nk==0)SetStatus( Vdmode[i], 1, "mode");
		else     SetStatus( Vdmode[i], 0, "mode");
	}

}
void DTagName::SetAllNeutral()
{
	for (int i=0; i< (int)Vdmode.size(); i++ ){
		int nk=NKinDTag[(DecayMode)Vdmode[i]];
		nk=nk%1000;	
		nk=nk/100;
		if(nk!=0)SetStatus( Vdmode[i], 1, "mode");
		else     SetStatus( Vdmode[i], 0, "mode");
	}

}

void DTagName::SetOnlyOnePi0()
{
	for (int i=0; i< (int)Vdmode.size(); i++ ){
		int nk=NKinDTag[(DecayMode)Vdmode[i]];
		nk=nk%1000;	
		nk=nk/100;
		if(nk<=2)SetStatus( Vdmode[i], 1, "mode");
		else     SetStatus( Vdmode[i], 0, "mode");
	}

}

void DTagName::SetGoldenIJ()
{
	for (int i=0; i< MaxMode; i++ ){
		for (int j=0; j< MaxMode; j++ ){
			StatIJ[i][j]=0;
		}
	}
	StatIJ[ 0][ 0]=1;StatIJ[ 0][ 0]=1; 
	StatIJ[ 0][ 1]=1;StatIJ[ 1][ 0]=1; 
	StatIJ[ 0][ 2]=1;StatIJ[ 2][ 0]=1; 
	StatIJ[ 0][ 3]=1;StatIJ[ 3][ 0]=1; 
	StatIJ[ 0][ 4]=1;StatIJ[ 4][ 0]=1; 
	StatIJ[ 0][ 8]=1;StatIJ[ 8][ 0]=1; 
	StatIJ[ 0][ 9]=1;StatIJ[ 9][ 0]=1; 
	StatIJ[ 0][23]=1;StatIJ[23][ 0]=1; 
	StatIJ[ 1][ 1]=1;StatIJ[ 1][ 1]=1; 
	StatIJ[ 1][ 2]=1;StatIJ[ 2][ 1]=1; 
	StatIJ[ 1][ 3]=1;StatIJ[ 3][ 1]=1; 
	StatIJ[ 1][ 4]=1;StatIJ[ 4][ 1]=1; 
	StatIJ[ 1][ 8]=1;StatIJ[ 8][ 1]=1; 
	StatIJ[ 1][ 9]=1;StatIJ[ 9][ 1]=1; 
	StatIJ[ 1][10]=1;StatIJ[10][ 1]=1; 
	StatIJ[ 1][11]=1;StatIJ[11][ 1]=1; 
	StatIJ[ 1][13]=1;StatIJ[13][ 1]=1; 
	StatIJ[ 1][23]=1;StatIJ[23][ 1]=1; 
	StatIJ[ 2][ 3]=1;StatIJ[ 3][ 2]=1; 
	StatIJ[ 3][ 3]=1;StatIJ[ 3][ 3]=1; 
	StatIJ[ 3][ 8]=1;StatIJ[ 8][ 3]=1; 
	StatIJ[ 3][ 9]=1;StatIJ[ 9][ 3]=1;
	StatIJ[ 3][10]=1;StatIJ[10][ 3]=1;
	StatIJ[ 3][11]=1;StatIJ[11][ 3]=1;
	StatIJ[ 3][19]=1;StatIJ[19][ 3]=1;
	StatIJ[ 8][ 9]=1;StatIJ[ 9][ 8]=1;
	//
	StatIJ[34][34]=1;StatIJ[34][34]=1;
	StatIJ[34][35]=1;StatIJ[35][34]=1;
	StatIJ[34][36]=1;StatIJ[36][34]=1;
	StatIJ[34][37]=1;StatIJ[37][34]=1;
	StatIJ[34][38]=1;StatIJ[38][34]=1;
	StatIJ[34][39]=1;StatIJ[39][34]=1;
	StatIJ[34][42]=1;StatIJ[42][34]=1;
	StatIJ[34][43]=1;StatIJ[43][34]=1;
	StatIJ[34][48]=1;StatIJ[48][34]=1;
	StatIJ[34][52]=1;StatIJ[52][34]=1;
	StatIJ[35][37]=1;StatIJ[37][35]=1;
	StatIJ[35][38]=1;StatIJ[38][35]=1;
	StatIJ[35][39]=1;StatIJ[39][35]=1;
	StatIJ[36][37]=1;StatIJ[37][36]=1;
	StatIJ[37][37]=1;StatIJ[37][37]=1;
	StatIJ[37][38]=1;StatIJ[38][37]=1;
	StatIJ[37][39]=1;StatIJ[39][37]=1;
	//
	StatIJ[57][58]=1;StatIJ[58][57]=1;
	StatIJ[57][70]=1;StatIJ[70][57]=1;
	StatIJ[57][71]=1;StatIJ[71][57]=1;
	StatIJ[58][58]=1;StatIJ[58][58]=1;
	StatIJ[58][61]=1;StatIJ[61][58]=1;
	StatIJ[58][62]=1;StatIJ[62][58]=1;
	StatIJ[58][63]=1;StatIJ[63][58]=1;
	StatIJ[58][66]=1;StatIJ[66][58]=1;
	StatIJ[58][67]=1;StatIJ[67][58]=1;
	StatIJ[58][68]=1;StatIJ[68][58]=1;
	StatIJ[58][69]=1;StatIJ[69][58]=1;
	StatIJ[58][70]=1;StatIJ[70][58]=1;
	StatIJ[58][71]=1;StatIJ[71][58]=1;
	StatIJ[58][75]=1;StatIJ[75][58]=1;
	StatIJ[58][77]=1;StatIJ[77][58]=1;
	StatIJ[58][79]=1;StatIJ[79][58]=1;
	StatIJ[61][71]=1;StatIJ[71][61]=1;
	StatIJ[63][71]=1;StatIJ[71][63]=1;
	StatIJ[66][71]=1;StatIJ[71][66]=1;
	StatIJ[67][71]=1;StatIJ[71][67]=1;
	StatIJ[69][71]=1;StatIJ[71][69]=1;
	StatIJ[69][77]=1;StatIJ[77][69]=1;
	StatIJ[70][71]=1;StatIJ[71][70]=1;
	StatIJ[71][71]=1;StatIJ[71][71]=1;
	StatIJ[71][77]=1;StatIJ[77][71]=1;
	//
	for (int i=0; i< MaxMode; i++ ){
		for (int j=0; j< MaxMode; j++ ){
			if(StatIJ[i][j]!=0){
				//SetStatus(i,1);SetStatus(j,1); //????
			}
		}
	}
}
void DTagName::SetOnlyGolden()
{
	for (int i=0; i< (int)Vdmode.size(); i++ ){
		SetStatus( Vdmode[i], 0, "mode");
	}
	//
	SetStatus(   0, 1, "mode");
	//SetStatus(   1, 1, "mode");
	//SetStatus(   2, 1, "mode");
	SetStatus(   3, 1, "mode");
	//SetStatus(   4, 1, "mode");
	//SetStatus(   5, 1, "mode");
	//SetStatus( 100, 1, "mode");
	//SetStatus( 101, 1, "mode");
	//SetStatus( 102, 1, "mode");
	//SetStatus( 103, 1, "mode");
	//SetStatus( 116, 1, "mode");
	//
	SetStatus( 200, 1, "mode");
	SetStatus( 201, 1, "mode");
	//SetStatus( 202, 1, "mode");
	//SetStatus( 203, 1, "mode");
	//SetStatus( 204, 1, "mode");
	//SetStatus( 205, 1, "mode");
	//SetStatus( 214, 1, "mode");
	//
	SetStatus( 400, 1, "mode");
	SetStatus( 401, 1, "mode");
	//SetStatus( 402, 1, "mode");
	//SetStatus( 403, 1, "mode");
	//SetStatus( 404, 1, "mode");
	//SetStatus( 405, 1, "mode");
	//SetStatus( 406, 1, "mode");
	//SetStatus( 420, 1, "mode");
	//SetStatus( 421, 1, "mode");
	//SetStatus( 422, 1, "mode");
	//SetStatus( 424, 1, "mode");
	//SetStatus( 440, 1, "mode");
	//SetStatus( 441, 1, "mode");
	//SetStatus( 442, 1, "mode");
	//SetStatus( 460, 1, "mode");
	//SetStatus( 480, 1, "mode");
	//SetStatus( 501, 1, "mode");
	//SetStatus( 502, 1, "mode");
	//SetStatus( 503, 1, "mode");
}

void DTagName::SetAll       ()
{
	for (int i=0; i< (int)Vdmode.size(); i++ ){
		SetStatus( Vdmode[i], 1, "mode");
	}
	//
	for (int i=0; i< MaxMode; i++ ){
		for (int j=0; j< MaxMode; j++ ){
			StatIJ[i][j]=1;
		}
	}
}


double DTagName::GetSumOfBr(string name)
{
	int i_dep=0, i_fin=34;
	if(name=="D+" || name == "D-" ){
		i_dep=34; i_fin=57;
	}
	if(name=="Ds+"|| name =="Ds-" ){
		i_dep=57; i_fin=82;
	}
	double Br=0;
	for (int i=i_dep; i< i_fin; i++ ){
		if(GetStatus(i)==0) continue;
		Br+=GetBr(i);	
	}
	return Br; 
}

DecayMode DTagName::find_Mode(const int i)
{
	DecayMode mode = kUnknown;
	map< int, DecayMode>::iterator pos = NoMode.find(i);
	if (pos != NoMode.end()) 
	{
		mode=pos->second;
	}
	return mode;
}

int DTagName::find_Numb(const int j)
{
	int numb = -1 ;
	for ( map< int, DecayMode>::const_iterator iter = NoMode.begin(); iter != NoMode.end(); ++iter ){
		if((int)iter->second == j )
		{
			numb = iter->first; 
			return numb;	
		}
	}
	return numb;
}


double DTagName::GetBr( const int i, string mode)
{
	double br = 0;	
	int km    = 0;
	if(mode==(char*)"number") km = find_Mode(i);
	else                      km = i; 
	map< int, double>::iterator pos = Br.find(km); 
	if (pos != Br.end()) 
	{
		br=pos->second;
	}
	else
	{
		cout<<"no such a tag mode of Br : "<<km<<endl;
	}
	return br;
}

double DTagName::GetdBr( const int i, string mode)
{
	double dbr = 0;	
	int km     = 0;
	if(mode==(char*)"number") km = find_Mode(i);
	else                      km =i; 
	map< int, double>::iterator pos = dBr.find(km); 
	if (pos != dBr.end()) 
	{
		dbr=pos->second;
	}
	else
	{
		cout<<"no such a tag mode of dBr : "<<km<<endl;
	}
	return dbr;
}

char* DTagName::GetPName( const int i, string mode)
{
	char*   name =   (char*)"Unknown";
	int km   = 0;
	if(mode==(char*)"number") km = find_Mode(i);
	else                        km = i; 
	map< int, char*>::iterator pos = PName.find(km); 
	if (pos != PName.end()) 
	{
		name=pos->second;
	}
	else
	{
		cout<<"no such a tag mode of PName: "<<km<<endl;
	}
	return name;
}

char* DTagName::GetMName( const int i, string mode)
{
	char*   name =    (char*)"Unknown";
	int km   = 0;
	if(mode==(char*)"number") km = find_Mode(i);
	else                      km =i; 
	map< int, char*>::iterator pos = MName.find(km); 
	if (pos != MName.end()) 
	{
		name=pos->second;
	}
	else
	{
		cout<<"no such a tag mode of MName: "<<km<<endl;
	}
	return name;
}

void  DTagName::SetStatus( const int i, const int flag, string mode)
{
	int km   = 0;
	if(mode=="number") km = find_Mode(i);
	else               km = i; 
	map< int, int>::iterator pos = Status.find(km); 
	if (pos != Status.end()) 
	{
		pos->second=flag;
	}
	else
	{
		cout<<"no such a tag mode: "<<km<<endl;
	}
}


int  DTagName::GetStatus( const int i, string mode )
{
	int flag = 0;
	int km   = 0;
	if(mode=="number") km = find_Mode(i);
	else               km = i; 
	map< int, int>::iterator pos = Status.find(km); 
	if (pos != Status.end()) 
	{
		flag = pos->second;
	}
	else
	{
		cout<<"no such a tag mode of status: "<<km<<endl;
	}
	return flag;
}

int  DTagName::GetStatus( const int i, const int j, string mode )
{
	int km   = -1, kn = -1;
	if(mode=="mode") {
		km = find_Numb(i);
		kn = find_Numb(j);
	}else{
		km = i; 
		kn = j; 
	}
	if( km<0 || kn<0 || km>=MaxMode || kn>=MaxMode){
		cout<<"no such a tag mode of status: "<<km<<" "<<kn<<endl;
		return 0;
	}
	return StatIJ[km][kn];
}
