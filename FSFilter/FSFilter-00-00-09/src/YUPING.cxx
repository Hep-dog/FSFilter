#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EventModel/EventModel.h"
#include "EventModel/Event.h"
#include "EventModel/EventHeader.h"

#include "McTruth/McParticle.h"
//#include "EventTag/IEventTagSvc.h"

#include "VertexFit/IVertexDbSvc.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/ISvcLocator.h"
#include "VertexFit/Helix.h"

#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h" 
#include "DstEvent/TofHitStatus.h" 

#include "TMath.h"
#include "TROOT.h"
#include "RooFit.h"
#include "TRandom.h"
#include "CLHEP/Random/RandGauss.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IHistogramSvc.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
using CLHEP::Hep3Vector;
using CLHEP::Hep2Vector;
using CLHEP::HepLorentzVector;

#include "CLHEP/Geometry/Point3D.h"
#ifndef ENABLE_BACKWARDS_COMPATIBILITY
typedef HepGeom::Point3D<double> HepPoint3D;
#endif
#include "FSFilter/YUPING.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/VertexFit.h"
#include "ParticleID/ParticleID.h"
#include <vector>
//const double twopi = 6.2831853;
//const double pi = 3.1415927;
const double mpi = 0.13957;
const double mk  = 0.49368;
const double mpi0 = 0.1349766;
const double xmass[5] = {0.000511, 0.105658, 0.139570,0.493677, 0.938272};
//const double velc = 29.9792458;  tof_path unit in cm.
const double velc = 299.792458;   // tof path unit in mm
typedef std::vector<int> Vint;
typedef std::vector<double> Vdouble;
typedef std::vector<HepLorentzVector> Vp4;

//declare one counter
static int counter[10]={0,0,0,0,0,0,0,0,0,0};


//*************************************************************************
// *****************************************************************
// ** A macro to create correlated Gaussian-distributed variables **
// *****************************************************************

// corset(): sets up the generation by calculating C from V.
void YUPING::corset(HepSymMatrix &V, HepMatrix &C, int n)
{
	//cout<<"v="<<V<<endl;
	//cout<<"c="<<C<<endl;
	double sum;

	// Compute square root of matrix sigma
	for (int j=0; j<n; j++) {
		sum = 0;
		for (int k=0; k<j; k++) {
			sum = sum + C[j][k]*C[j][k];

		}
		//cout<<"sum="<<sum<<endl;
		//cout<<"v("<<j<<","<<j<<")="<<V[j][j]<<endl;
		C[j][j] = sqrt(abs(V[j][j] - sum));
		//cout<<"c("<<j<<","<<j<<")="<<C[j][j]<<endl;
		// Off Diagonal terms
		for (int i=j+1; i<n; i++) {
			sum = 0;
			for (int k=0; k<j; k++) {
				sum = sum + C[i][k]*C[j][k];
			}
			C[i][j] = (V[i][j] - sum)/C[j][j];
			//cout<<"C("<<i<<","<<j<<")="<<C[i][j]<<endl;
		}
	}
}

// corgen(): generates a set of n random numbers Gaussian-distributed with covariance
// matrix V (V = C*C') and mean values zero.
void YUPING::corgen(HepMatrix &C, HepVector &x, int n)
{
	int i,j;
	int nmax = 100;

	if (n > nmax ) {
		printf("Error in corgen: array overflown");
	}

	double tmp[3];
	for(int p = 0 ; p < n; p ++){
		tmp[p] = gRandom->Gaus(0,1);
		//cout<<"tmp["<<p<<"]="<<tmp[p]<<endl;
	}
	for ( i=0; i<n; i++) {
		x[i] = 0.0;
		for (j=0; j<=i; j++) {
			x[i] = x[i]+C[i][j]*tmp[j];
		}
	}
}


void YUPING::calibration(RecMdcKalTrack *trk , HepVector &wtrk_zHel, int n )
{

	HepVector pip_calerr_d2(5,0);
	HepVector pim_calerr_d2(5,0);
	HepVector kp_calerr_d2(5,0);
	HepVector km_calerr_d2(5,0);

	// BOSS 6.5.1p02

	/*
	   pip_calerr_d2[0] = 1.0;
	   pip_calerr_d2[1] = 1.189*1.050;
	   pip_calerr_d2[2] = 1.235*1.060;
	   pip_calerr_d2[3] = 1.0;
	   pip_calerr_d2[4] = 1.189*1.048;

	   pim_calerr_d2[0] = 1.0;
	   pim_calerr_d2[1] = 1.187*1.040;
	   pim_calerr_d2[2] = 1.194*1.061;
	   pim_calerr_d2[3] = 1.0;
	   pim_calerr_d2[4] = 1.168*1.036;

	   kp_calerr_d2[0] = 1.0;
	   kp_calerr_d2[1] = 1.164*1.019;
	   kp_calerr_d2[2] = 1.216*1.056;
	   kp_calerr_d2[3] = 1.0;
	   kp_calerr_d2[4] = 1.188*1.053;

	   km_calerr_d2[0] = 1.0;
	   km_calerr_d2[1] = 1.177*1.024;
	   km_calerr_d2[2] = 1.191*1.050;
	   km_calerr_d2[3] = 1.0;
	   km_calerr_d2[4] = 1.172*1.032;
	 */


	// BOSS 6.5.5

	pip_calerr_d2[0] = 1.0;
	pip_calerr_d2[1] = 1.05*1.188;
	pip_calerr_d2[2] = 1.042*1.195;
	pip_calerr_d2[3] = 1.0;
	pip_calerr_d2[4] = 1.0128*1.134;

	pim_calerr_d2[0] = 1.0;
	pim_calerr_d2[1] = 1.038*1.173;
	pim_calerr_d2[2] = 1.0364*1.182;
	pim_calerr_d2[3] = 1.0;
	pim_calerr_d2[4] = 1.004*1.129;

	kp_calerr_d2[0] = 1.0;
	kp_calerr_d2[1] = 1.0094*1.165;
	kp_calerr_d2[2] = 1.055*1.205;
	kp_calerr_d2[3] = 1.0;
	kp_calerr_d2[4] = 1.008*1.132;

	km_calerr_d2[0] = 1.0;
	km_calerr_d2[1] = 1.02*1.167;
	km_calerr_d2[2] = 1.044*1.188;
	km_calerr_d2[3] = 1.0;
	km_calerr_d2[4] = 0.9969*1.115;


	HepVector pip_calmean_d2(5,0);
	HepVector pim_calmean_d2(5,0);
	HepVector kp_calmean_d2(5,0);
	HepVector km_calmean_d2(5,0);

	pip_calmean_d2[0] = 0;
	pip_calmean_d2[1] = 0;
	pip_calmean_d2[2] = 0;
	pip_calmean_d2[3] = 0;
	pip_calmean_d2[4] = 0;
	pim_calmean_d2[0] = 0;
	pim_calmean_d2[1] = 0;
	pim_calmean_d2[2] = 0;
	pim_calmean_d2[3] = 0;
	pim_calmean_d2[4] = 0;
	kp_calmean_d2[0] = 0;
	kp_calmean_d2[1] = 0;
	kp_calmean_d2[2] = 0;
	kp_calmean_d2[3] = 0;
	kp_calmean_d2[4] = 0;
	km_calmean_d2[0] = 0;
	km_calmean_d2[1] = 0;
	km_calmean_d2[2] = 0;
	km_calmean_d2[3] = 0;
	km_calmean_d2[4] = 0;

	if(trk->charge()>0 && n==0){
		//pip
		HepSymMatrix wpip_zerr(5,0);
		wpip_zerr = trk->getZError();
		HepSymMatrix wpip_zcal(3,0);

		wpip_zcal[0][0] = (pip_calerr_d2[1]*pip_calerr_d2[1]-1)*wpip_zerr[1][1];
		wpip_zcal[1][1] = (pip_calerr_d2[2]*pip_calerr_d2[2]-1)*wpip_zerr[2][2];
		wpip_zcal[2][2] = (pip_calerr_d2[4]*pip_calerr_d2[4]-1)*wpip_zerr[4][4];

		HepMatrix wpip_zerrc(3,3,0);
		YUPING::corset(wpip_zcal,wpip_zerrc,3);
		HepVector wpip_zgen(3,0);
		YUPING::corgen(wpip_zerrc,wpip_zgen,3);

		wtrk_zHel[0] = trk->getZHelix()[0];
		wtrk_zHel[1] = trk->getZHelix()[1]+pip_calmean_d2[1]*sqrt(wpip_zerr[1][1])+wpip_zgen[0];
		wtrk_zHel[2] = trk->getZHelix()[2]+pip_calmean_d2[2]*sqrt(wpip_zerr[2][2])+wpip_zgen[1];
		wtrk_zHel[3] = trk->getZHelix()[3];
		wtrk_zHel[4] = trk->getZHelix()[4]+pip_calmean_d2[4]*sqrt(wpip_zerr[4][4])+wpip_zgen[2];

	}
	if(trk->charge()<0 && n==0)
	{
		//pim
		HepSymMatrix wpim_zerr(5,0);
		wpim_zerr = trk->getZError();

		HepSymMatrix wpim_zcal(3,0);

		wpim_zcal[0][0] = (pim_calerr_d2[1]*pim_calerr_d2[1]-1)*wpim_zerr[1][1];
		wpim_zcal[1][1] = (pim_calerr_d2[2]*pim_calerr_d2[2]-1)*wpim_zerr[2][2];
		wpim_zcal[2][2] = (pim_calerr_d2[4]*pim_calerr_d2[4]-1)*wpim_zerr[4][4];

		HepMatrix wpim_zerrc(3,3,0);
		YUPING::corset(wpim_zcal,wpim_zerrc,3);
		HepVector wpim_zgen(3,0);
		YUPING::corgen(wpim_zerrc,wpim_zgen,3);


		wtrk_zHel[0] = trk->getZHelix()[0];
		wtrk_zHel[1] = trk->getZHelix()[1]+pim_calmean_d2[1]*sqrt(wpim_zerr[1][1])+wpim_zgen[0];
		wtrk_zHel[2] = trk->getZHelix()[2]+pim_calmean_d2[2]*sqrt(wpim_zerr[2][2])+wpim_zgen[1];
		wtrk_zHel[3] = trk->getZHelix()[3];
		wtrk_zHel[4] = trk->getZHelix()[4]+pim_calmean_d2[4]*sqrt(wpim_zerr[4][4])+wpim_zgen[2];

	}
	if(trk->charge()>0 && n==1)
	{
		//kp
		HepSymMatrix wkp_zerr(5,0);
		wkp_zerr = trk->getZErrorK();

		HepSymMatrix wkp_zcal(3,0);

		wkp_zcal[0][0] = (kp_calerr_d2[1]*kp_calerr_d2[1]-1)*wkp_zerr[1][1];
		wkp_zcal[1][1] = (kp_calerr_d2[2]*kp_calerr_d2[2]-1)*wkp_zerr[2][2];
		wkp_zcal[2][2] = (kp_calerr_d2[4]*kp_calerr_d2[4]-1)*wkp_zerr[4][4];

		HepMatrix wkp_zerrc(3,3,0);
		YUPING::corset(wkp_zcal,wkp_zerrc,3);
		HepVector wkp_zgen(3,0);
		YUPING::corgen(wkp_zerrc,wkp_zgen,3);

		wtrk_zHel[0] = trk->getZHelixK()[0];
		wtrk_zHel[1] = trk->getZHelixK()[1]+kp_calmean_d2[1]*sqrt(wkp_zerr[1][1])+wkp_zgen[0];
		wtrk_zHel[2] = trk->getZHelixK()[2]+kp_calmean_d2[2]*sqrt(wkp_zerr[2][2])+wkp_zgen[1];
		wtrk_zHel[3] = trk->getZHelixK()[3];
		wtrk_zHel[4] = trk->getZHelixK()[4]+kp_calmean_d2[4]*sqrt(wkp_zerr[4][4])+wkp_zgen[2];

	}

	if(trk->charge()<0 && n==1)
	{
		//km
		HepSymMatrix wkm_zerr(5,0);
		wkm_zerr = trk->getZErrorK();

		HepSymMatrix wkm_zcal(3,0);

		wkm_zcal[0][0] = (km_calerr_d2[1]*km_calerr_d2[1]-1)*wkm_zerr[1][1];
		wkm_zcal[1][1] = (km_calerr_d2[2]*km_calerr_d2[2]-1)*wkm_zerr[2][2];
		wkm_zcal[2][2] = (km_calerr_d2[4]*km_calerr_d2[4]-1)*wkm_zerr[4][4];

		HepMatrix wkm_zerrc(3,3,0);
		YUPING::corset(wkm_zcal,wkm_zerrc,3);
		HepVector wkm_zgen(3,0);
		YUPING::corgen(wkm_zerrc,wkm_zgen,3);

		wtrk_zHel[0] = trk->getZHelixK()[0];
		wtrk_zHel[1] = trk->getZHelixK()[1]+km_calmean_d2[1]*sqrt(wkm_zerr[1][1])+wkm_zgen[0];
		wtrk_zHel[2] = trk->getZHelixK()[2]+km_calmean_d2[2]*sqrt(wkm_zerr[2][2])+wkm_zgen[1];
		wtrk_zHel[3] = trk->getZHelixK()[3];
		wtrk_zHel[4] = trk->getZHelixK()[4]+km_calmean_d2[4]*sqrt(wkm_zerr[4][4])+wkm_zgen[2];

	}         


}

