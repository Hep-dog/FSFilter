#include "FSFilter/RscanDQ.h"

#include <iostream>

using namespace std;

RscanDQ::RscanDQ(){

}
RscanDQ::RscanDQ(int runNo){

     init(runNo);
}

void RscanDQ::init(int runNo){

	Status(runNo);
	Ebeam (runNo);
	Ecm   (runNo);
	Number(runNo);

}
RscanDQ::~RscanDQ(){

}

double RscanDQ::Cal4260(int runNo)
{
	double ecm=(4370.93-3.75E-03*runNo)/1000.0;
	return ecm;
}
double RscanDQ::Cal4230(int runNo)
{
	double ecm=(4320.32-2.87E-03*runNo)/1000.0;
	return ecm;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void RscanDQ::Status(int runNo){

	if (runNo < 34011||runNo > 35118||runNo == 34018||runNo == 34020||runNo == 34021||runNo == 34023||runNo == 34027||runNo == 34040||runNo == 34042||runNo == 34046||runNo == 34048||runNo == 34058||runNo == 34061||runNo == 34065||runNo == 34099||runNo == 34100||runNo == 34110||runNo == 34117||runNo == 34123||runNo == 34124||runNo == 34145||runNo == 34152||runNo == 34153||runNo == 34168||runNo == 34169||runNo == 34170||runNo == 34171||runNo == 34172||runNo == 34173||runNo == 34174||runNo == 34177||runNo == 34178||runNo == 34211||runNo == 34212||runNo == 34217||runNo == 34227||runNo == 34228||runNo == 34237||runNo == 34238||runNo == 34261||runNo == 34262||runNo == 34282||runNo == 34283||runNo == 34301||runNo == 34308||runNo == 34309||runNo == 34336||runNo == 34337||runNo == 34338||runNo == 34352||runNo == 34353||runNo == 34377||runNo == 34378||runNo == 34382||runNo == 34392||runNo == 34401||runNo == 34404||runNo == 34406||runNo == 34428||runNo == 34432||runNo == 34434||runNo == 34440||runNo == 34441||runNo == 34464||runNo == 34465||runNo == 34467||runNo == 34490||runNo == 34492||runNo == 34516||runNo == 34517||runNo == 34518||runNo == 34519||runNo == 34520||runNo == 34521||runNo == 34522||runNo == 34523||runNo == 34525||runNo == 34527||runNo == 34528||runNo == 34529||runNo == 34537||runNo == 34544||runNo == 34546||runNo == 34547||runNo == 34548||runNo == 34549||runNo == 34576||runNo == 34577||runNo == 34578||runNo == 34600||runNo == 34602||runNo == 34625||runNo == 34626||runNo == 34628||runNo == 34650||runNo == 34653||runNo == 34676||runNo == 34678||runNo == 34700||runNo == 34711||runNo == 34720||runNo == 34722||runNo == 34744||runNo == 34745||runNo == 34746||runNo == 34748||runNo == 34770||runNo == 34771||runNo == 34772||runNo == 34795||runNo == 34798||runNo == 34815||runNo == 34817||runNo == 34848||runNo == 34849||runNo == 34853||runNo == 34854||runNo == 34870||runNo == 34872||runNo == 34875||runNo == 34880||runNo == 34882||runNo == 34900||runNo == 34904||runNo == 34907||runNo == 34916||runNo == 34917||runNo == 34936||runNo == 34951||runNo == 34954||runNo == 34975||runNo == 34977||runNo == 34979||runNo == 34985||runNo == 34986||runNo == 34988||runNo == 34989||runNo == 34990||runNo == 35006||runNo == 35014||runNo == 35021||runNo == 35023||runNo == 35043||runNo == 35044||runNo == 35045||runNo == 35046||runNo == 35052||runNo == 35066||runNo == 35071||runNo == 35074||runNo == 35080||runNo == 35091||runNo == 35092||runNo == 35096||runNo == 35103||runNo == 35117||runNo == 35118) m_status = 0;

	else if ( runNo == 34326||runNo == 34334||runNo == 34478||runNo == 34818||runNo == 34982||runNo == 35101) m_status = -1;

	else m_status = 1;

	// m_status (1 for good run, -1 for bad run , 0 for empty run )  

}
void RscanDQ::Ecm  (int runNo){

	double Ecm; 
	int RootID=9030443;	
	if      ( runNo >=  8093 && runNo <=  9025){
		Ecm=3.68631;
		RootID=100443;	
	}
	else if ( runNo >=  9613 && runNo <=  9779){
		Ecm=3.65000;
	}
	else if ( runNo >=  9947 && runNo <= 10878){
		Ecm=3.09692;
		RootID=443;	
	}
	else if ( runNo >= 23463 && runNo <= 23505){
		Ecm=4.01036;
		RootID=9000443;	
	}
	else if ( runNo >= 23510 && runNo <= 24141 ){
		Ecm=4.00856;
		RootID=9000443;	
	}
	else if ( runNo >= 24151 && runNo <= 24177){
		Ecm=3.68631;
		RootID=100443;	
	}
	else if ( runNo >= 27255 && runNo <= 28236){ //1B J/psi
		Ecm=3.09692;
		RootID=443;	
	}
	else if ( runNo >= 29677 && runNo <= 29820){ //4260 Lum = 523.74 pb^-1
		Ecm=Cal4260(runNo);
		RootID=9030443;	
	}
	else if ( runNo >= 29821 && runNo <= 30367){ //4260 Lum = 523.74 pb^-1
		Ecm=4.25798;
		RootID=9030443;	
	}
	else if ( runNo >= 30372 && runNo <= 30437){ //4190 Lum = 43.09 pb^-1
		Ecm=4.18857;
		RootID=9030443;	
	}
	else if ( runNo >= 30438 && runNo <= 30491){ //4230 Lum = 44.40 pb^-1
		Ecm=4.22734;
		RootID=9030443;	
	}
	else if ( runNo >= 30492 && runNo <= 30557){ //4310 Lum = 44.90 pb^-1
		Ecm=4.30786;
		RootID=9030443;	
	}
	else if ( runNo >= 30616 && runNo <= 31279){// 4360 Lum = 523 pb^-1
		Ecm   = 4.35822;
		RootID= 9040443;
	}
	else if ( runNo >= 31281 && runNo <= 31325){// 4390 Lum =  53 pb^-1
		Ecm   = 4.38736;
		RootID= 9020443;
	}
	else if ( runNo>=31327 && runNo <=31390) {//  4420 Lum = 43 pb^-1
		Ecm   = 4.41691;
		RootID= 9020443;
	}
	else if ( runNo>=31561 && runNo <=31981){//  4260 Lum = 290 pb^-1
		Ecm   = 4.25741;
		RootID= 9030443;
	}
	else if ( runNo>=31983 && runNo <=32045){//  4210 Lum = 52 pb^-1
		Ecm   = 4.20771;
		RootID= 9030443;
	}
	else if ( runNo>=32046 && runNo <=32140){//  4220 Lum = 52 pb^-1
		Ecm   = 4.21711;		 
		RootID= 9030443;
	}
	else if ( runNo>=32141 && runNo <=32226){//  4245 Lum =53 pb^-1
		Ecm   = 4.24164;
		RootID= 9030443;
	}
	else if ( runNo>=32239 && runNo <=32850){// 4230 Lum = 1011 pb^-1
		Ecm   = Cal4230(runNo);
		RootID= 9030443;
	}
	else if ( runNo>=32851 && runNo <=33484){// 4230 Lum = 1011 pb^-1
		Ecm   = 4.22552;
		RootID= 9030443;
	}
	else if ( runNo>=33490 && runNo <=33556){// 3810 Lum =  48  pb^-1
		Ecm   = 3.80769;
		RootID= 9030443;
	}
	else if ( runNo>=33571 && runNo <=33657){//  3900 Lum = 50  pb^-1
		Ecm   = 3.89627;
		RootID= 9030443;
	}
	else if ( runNo>=33659 && runNo <=33719){//  4090 Lum = 50  pb^-1
		Ecm   = 4.08545;
		RootID= 9030443;
	}
	else if ( runNo>=33725 && runNo <=33772){//  3.65GeV
		Ecm   = 3.65000;
	}
	else if ( runNo>=35227 && runNo <=36213){//  4600 Lum = ~506 pb^-1
		Ecm   = 4.59946;
	}
	else if ( runNo>=36245 && runNo <=36393){//  4470 Lum = ~100 pb^-1
		Ecm   = 4.46701;
	}
	else if ( runNo>=36398 && runNo <=36588){//  4530 Lum = ~100 pb^-1
		Ecm   = 4.52708;
	}
	else if ( runNo>=36603 && runNo <=36699){//  4575 Lum = ~42 pb^-1
		Ecm   = 4.57444;
	}
	else if ( runNo>=36773 && runNo <=37855){//  4420 Lum = ~994 pb^-1
		Ecm   = 4.41580;
	}
	else if ( runNo>=37856 && runNo <=38140){//  4420 Lum = ~994 pb^-1
		Ecm   = 4.41402;
	}
	else if ( runNo >= 34011 && runNo <=34027) {
		Ecm = 1.925*2;
	}
	else if ( runNo >= 34028 && runNo <=34036) {
		Ecm = 1.945*2;
	}
	else if ( runNo >= 34037 && runNo <=34045) {
		Ecm = 1.9475*2;
	}
	else if ( runNo >= 34046 && runNo <=34057) {
		Ecm = 1.95*2;
	}
	else if (runNo >= 34058 && runNo <=34068) {
		Ecm = 1.9525*2;
	}
	else if (runNo >= 34069 && runNo <=34076) {
		Ecm = 1.955*2;
	}
	else if (runNo >= 34077 && runNo <=34083) {
		Ecm = 1.9575*2;
	}
	else if (runNo >= 34084 && runNo <=34090) {
		Ecm = 1.96*2;
	}
	else if (runNo >= 34091 && runNo <=34096) {
		Ecm = 1.9625*2;
	}
	else if (runNo >= 34097 && runNo <=34104) {
		Ecm = 1.965*2;
	}
	else if (runNo >= 34105 && runNo <=34117) {
		Ecm = 1.9675*2;
	}
	else if (runNo >= 34118 && runNo <=34127) {
		Ecm = 1.97*2;
	}
	else if (runNo >= 34128 && runNo <=34134) {
		Ecm = 1.9725*2;
	}
	else if (runNo >= 34135 && runNo <=34141) {
		Ecm = 1.975*2;
	}
	else if (runNo >= 34142 && runNo <=34150) {
		Ecm = 1.9775*2;
	}
	else if (runNo >= 34151 && runNo <=34160) {
		Ecm = 1.98*2;
	}
	else if (runNo >= 34161 && runNo <=34167) {
		Ecm = 1.9825*2;
	}
	else if (runNo >= 34175 && runNo <=34183) {
		Ecm = 1.985*2;
	}
	else if (runNo >= 34184 && runNo <=34190) {
		Ecm = 1.9875*2;
	}
	else if (runNo >= 34191 && runNo <=34196) {
		Ecm = 1.99*2;
	}
	else if (runNo >= 34197 && runNo <=34202) {
		Ecm = 1.9925*2;
	}
	else if (runNo >= 34203 && runNo <=34210) {
		Ecm = 1.995*2;
	}
	else if (runNo >= 34211 && runNo <=34220) {
		Ecm = 1.9975*2;
	}
	else if (runNo >= 34221 && runNo <=34230) {
		Ecm = 2.00*2;
	}
	else if (runNo >= 34231 && runNo <=34239) {
		Ecm = 2.0025*2;
	}
	else if (runNo >= 34240 && runNo <=34245) {
		Ecm = 2.005*2;
	}
	else if (runNo >= 34246 && runNo <=34252) {
		Ecm = 2.006*2;
	}
	else if (runNo >= 34253 && runNo <=34257) {
		Ecm = 2.007*2;
	}
	else if (runNo >= 34258 && runNo <=34265) {
		Ecm = 2.008*2;
	}
	else if (runNo >= 34266 && runNo <=34271) {
		Ecm = 2.009*2;
	}
	else if (runNo >= 34272 && runNo <=34276) {
		Ecm = 2.010*2;
	}
	else if (runNo >= 34277 && runNo <=34281) {
		Ecm = 2.0125*2;
	}
	else if (runNo >= 34282 && runNo <=34297) {
		Ecm = 2.015*2;
	}
	else if (runNo >= 34314 && runNo <=34320) {
		Ecm = 2.0175*2;
	}
	else if (runNo >= 34321 && runNo <=34327) {
		Ecm = 2.020*2;
	}
	else if (runNo >= 34328 && runNo <=34335) {
		Ecm = 2.025*2;
	}
	else if (runNo >= 34339 && runNo <=34345) {
		Ecm = 2.0275*2;
	}
	else if (runNo >= 34346 && runNo <=34350) {
		Ecm = 2.030*2;
	}
	else if (runNo >= 34351 && runNo <=34358) {
		Ecm = 2.0325*2;
	}
	else if (runNo >= 34359 && runNo <=34367) {
		Ecm = 2.035*2;
	}
	else if (runNo >= 34368 && runNo <=34373) {
		Ecm = 2.04*2;
	}
	else if (runNo >= 34374 && runNo <=34381) {
		Ecm = 2.045*2;
	}
	else if (runNo >= 34382 && runNo <=34389) {
		Ecm = 2.050*2;
	}
	else if (runNo >= 34390 && runNo <=34396) {
		Ecm = 2.055*2;
	}
	else if (runNo >= 34397 && runNo <=34403) {
		Ecm = 2.060*2;
	}
	else if (runNo >= 34404 && runNo <=34411) {
		Ecm = 2.065*2;
	}
	else if (runNo >= 34412 && runNo <=34417) {
		Ecm = 2.070*2;
	}
	else if (runNo >= 34418 && runNo <=34427) {
		Ecm = 2.0725*2;
	}
	else if (runNo >= 34428 && runNo <=34436) {
		Ecm = 2.075*2;
	}
	else if (runNo >= 34437 && runNo <=34446) {
		Ecm = 2.080*2;
	}
	else if (runNo >= 34447 && runNo <=34460) {
		Ecm = 2.085*2;
	}
	else if (runNo >= 34478 && runNo <=34485) {
		Ecm = 2.090*2;
	}
	else if (runNo >= 34486 && runNo <=34493) {
		Ecm = 2.095*2;
	}
	else if (runNo >= 34494 && runNo <=34502) {
		Ecm = 2.0975*2;
	}
	else if (runNo >= 34503 && runNo <=34511) {
		Ecm = 2.1*2;
	}
	else if (runNo >= 34512 && runNo <=34526) {
		Ecm = 2.1015*2;
	}
	else if (runNo >= 34527 && runNo <=34540) {
		Ecm = 2.103*2;
	}
	else if (runNo >= 34541 && runNo <=34554) {
		Ecm = 2.105*2;
	}
	else if (runNo >= 34555 && runNo <=34563) {
		Ecm = 2.1075*2;
	}
	else if (runNo >= 34564 && runNo <=34573) {
		Ecm = 2.11*2;
	}
	else if (runNo >= 34574 && runNo <=34584) {
		Ecm = 2.1125*2;
	}
	else if (runNo >= 34585 && runNo <=34592) {
		Ecm = 2.115*2;
	}
	else if (runNo >= 34593 && runNo <=34602) {
		Ecm = 2.1175*2;
	}
	else if (runNo >= 34603 && runNo <=34612) {
		Ecm = 2.12*2;
	}
	else if (runNo >= 34613 && runNo <=34622) {
		Ecm = 2.1215*2;
	}
	else if (runNo >= 34623 && runNo <=34633) {
		Ecm = 2.1225*2;
	}
	else if (runNo >= 34634 && runNo <=34641) {
		Ecm = 2.124*2;
	}
	else if (runNo >= 34642 && runNo <=34651) {
		Ecm = 2.125*2;
	}
	else if (runNo >= 34652 && runNo <=34660) {
		Ecm = 2.1275*2;
	}
	else if (runNo >= 34661 && runNo <=34673) {
		Ecm = 2.13*2;
	}
	else if (runNo >= 34674 && runNo <=34684) {
		Ecm = 2.1325*2;
	}
	else if (runNo >= 34685 && runNo <=34694) {
		Ecm = 2.135*2;
	}
	else if (runNo >= 34695 && runNo <=34704) {
		Ecm = 2.1375*2;
	}
	else if (runNo >= 34705 && runNo <=34718) {
		Ecm = 2.14*2;
	}
	else if (runNo >= 34719 && runNo <=34728) {
		Ecm = 2.1425*2;
	}
	else if (runNo >= 34729 && runNo <=34739) {
		Ecm = 2.145*2;
	}
	else if (runNo >= 34740 && runNo <=34753) {
		Ecm = 2.15*2;
	}
	else if (runNo >= 34754 && runNo <=34762) {
		Ecm = 2.155*2;
	}
	else if (runNo >= 34763 && runNo <=34776) {
		Ecm = 2.16*2;
	}
	else if (runNo >= 34777 && runNo <=34784) {
		Ecm = 2.165*2;
	}
	else if (runNo >= 34785 && runNo <=34793) {
		Ecm = 2.17*2;
	}
	else if (runNo >= 34794 && runNo <=34803) {
		Ecm = 2.175*2;
	}
	else if (runNo >= 34804 && runNo <=34811) {
		Ecm = 2.18*2;
	}
	else if (runNo >= 34812 && runNo <=34824) {
		Ecm = 2.185*2;
	}
	else if (runNo >= 34825 && runNo <=34836) {
		Ecm = 2.19*2;
	}
	else if (runNo >= 34837 && runNo <=34847) {
		Ecm = 2.195*2;
	}
	else if (runNo >= 34848 && runNo <=34860) {
		Ecm = 2.1975*2;
	}
	else if (runNo >= 34861 && runNo <=34868) {
		Ecm = 2.2*2;
	}
	else if (runNo >= 34869 && runNo <=34881) {
		Ecm = 2.205*2;
	}
	else if (runNo >= 34882 && runNo <=34890) {
		Ecm = 2.21*2;
	}
	else if (runNo >= 34891 && runNo <=34899) {
		Ecm = 2.2125*2;
	}
	else if (runNo >= 34900 && runNo <=34912) {
		Ecm = 2.215*2;
	}
	else if (runNo >= 34913 && runNo <=34925) {
		Ecm = 2.22*2;
	}
	else if (runNo >= 34926 && runNo <=34935) {
		Ecm = 2.225*2;
	}
	else if (runNo >= 34936 && runNo <=34946) {
		Ecm = 2.23*2;
	}
	else if (runNo >= 34947 && runNo <=34957) {
		Ecm = 2.24*2;
	}
	else if (runNo >= 34958 && runNo <=34967) {
		Ecm = 2.25*2;
	}
	else if (runNo >= 34968 && runNo <=34981) {
		Ecm = 2.26*2;
	}
	else if (runNo >= 34982 && runNo <=35009) {
		Ecm = 2.27*2;
	}
	else if (runNo >= 35010 && runNo <=35026) {
		Ecm = 2.275*2;
	}
	else if (runNo >= 35027 && runNo <=35040) {
		Ecm = 2.28*2;
	}
	else if (runNo >= 35041 && runNo <=35059) {
		Ecm = 2.285*2;
	}
	else if (runNo >= 35060 && runNo <=35098) {
		Ecm = 2.29*2;
	}
	else if (runNo >= 35099 && runNo <=35118) {
		Ecm = 2.295*2;
	}
	else if (runNo >= 42004 && runNo <=42231) {
		Ecm = 1.065*2;
	}else{
		cout<<"Bad run number for BESIII data"<<runNo<<endl;
	}

	m_Ecm = Ecm;
	m_RootID = RootID;

}

void RscanDQ::Ebeam(int runNo){

	double Ebeam;   

	if (runNo >= 34011 && runNo <=34027) {
		Ebeam = 1.925;
	}
	if (runNo >= 34028 && runNo <=34036) {
		Ebeam = 1.945;
	}
	if (runNo >= 34037 && runNo <=34045) {
		Ebeam = 1.9475;
	}
	if (runNo >= 34046 && runNo <=34057) {
		Ebeam = 1.95;
	}
	if (runNo >= 34058 && runNo <=34068) {
		Ebeam = 1.9525;
	}
	if (runNo >= 34069 && runNo <=34076) {
		Ebeam = 1.955;
	}
	if (runNo >= 34077 && runNo <=34083) {
		Ebeam = 1.9575;
	}
	if (runNo >= 34084 && runNo <=34090) {
		Ebeam = 1.96;
	}
	if (runNo >= 34091 && runNo <=34096) {
		Ebeam = 1.9625;
	}
	if (runNo >= 34097 && runNo <=34104) {
		Ebeam = 1.965;
	}
	if (runNo >= 34105 && runNo <=34117) {
		Ebeam = 1.9675;
	}
	if (runNo >= 34118 && runNo <=34127) {
		Ebeam = 1.97;
	}
	if (runNo >= 34128 && runNo <=34134) {
		Ebeam = 1.9725;
	}
	if (runNo >= 34135 && runNo <=34141) {
		Ebeam = 1.975;
	}
	if (runNo >= 34142 && runNo <=34150) {
		Ebeam = 1.9775;
	}
	if (runNo >= 34151 && runNo <=34160) {
		Ebeam = 1.98;
	}
	if (runNo >= 34161 && runNo <=34167) {
		Ebeam = 1.9825;
	}
	if (runNo >= 34175 && runNo <=34183) {
		Ebeam = 1.985;
	}
	if (runNo >= 34184 && runNo <=34190) {
		Ebeam = 1.9875;
	}
	if (runNo >= 34191 && runNo <=34196) {
		Ebeam = 1.99;
	}
	if (runNo >= 34197 && runNo <=34202) {
		Ebeam = 1.9925;
	}
	if (runNo >= 34203 && runNo <=34210) {
		Ebeam = 1.995;
	}
	if (runNo >= 34211 && runNo <=34220) {
		Ebeam = 1.9975;
	}
	if (runNo >= 34221 && runNo <=34230) {
		Ebeam = 2.00;
	}
	if (runNo >= 34231 && runNo <=34239) {
		Ebeam = 2.0025;
	}
	if (runNo >= 34240 && runNo <=34245) {
		Ebeam = 2.005;
	}
	if (runNo >= 34246 && runNo <=34252) {
		Ebeam = 2.006;
	}
	if (runNo >= 34253 && runNo <=34257) {
		Ebeam = 2.007;
	}
	if (runNo >= 34258 && runNo <=34265) {
		Ebeam = 2.008;
	}
	if (runNo >= 34266 && runNo <=34271) {
		Ebeam = 2.009;
	}
	if (runNo >= 34272 && runNo <=34276) {
		Ebeam = 2.010;
	}
	if (runNo >= 34277 && runNo <=34281) {
		Ebeam = 2.0125;
	}
	if (runNo >= 34282 && runNo <=34297) {
		Ebeam = 2.015;
	}
	if (runNo >= 34314 && runNo <=34320) {
		Ebeam = 2.0175;
	}
	if (runNo >= 34321 && runNo <=34327) {
		Ebeam = 2.020;
	}
	if (runNo >= 34328 && runNo <=34335) {
		Ebeam = 2.025;
	}
	if (runNo >= 34339 && runNo <=34345) {
		Ebeam = 2.0275;
	}
	if (runNo >= 34346 && runNo <=34350) {
		Ebeam = 2.030;
	}
	if (runNo >= 34351 && runNo <=34358) {
		Ebeam = 2.0325;
	}
	if (runNo >= 34359 && runNo <=34367) {
		Ebeam = 2.035;
	}
	if (runNo >= 34368 && runNo <=34373) {
		Ebeam = 2.04;
	}
	if (runNo >= 34374 && runNo <=34381) {
		Ebeam = 2.045;
	}
	if (runNo >= 34382 && runNo <=34389) {
		Ebeam = 2.050;
	}
	if (runNo >= 34390 && runNo <=34396) {
		Ebeam = 2.055;
	}
	if (runNo >= 34397 && runNo <=34403) {
		Ebeam = 2.060;
	}
	if (runNo >= 34404 && runNo <=34411) {
		Ebeam = 2.065;
	}
	if (runNo >= 34412 && runNo <=34417) {
		Ebeam = 2.070;
	}
	if (runNo >= 34418 && runNo <=34427) {
		Ebeam = 2.0725;
	}
	if (runNo >= 34428 && runNo <=34436) {
		Ebeam = 2.075;
	}
	if (runNo >= 34437 && runNo <=34446) {
		Ebeam = 2.080;
	}
	if (runNo >= 34447 && runNo <=34460) {
		Ebeam = 2.085;
	}
	if (runNo >= 34478 && runNo <=34485) {
		Ebeam = 2.090;
	}
	if (runNo >= 34486 && runNo <=34493) {
		Ebeam = 2.095;
	}
	if (runNo >= 34494 && runNo <=34502) {
		Ebeam = 2.0975;
	}
	if (runNo >= 34503 && runNo <=34511) {
		Ebeam = 2.1;
	}
	if (runNo >= 34512 && runNo <=34526) {
		Ebeam = 2.1015;
	}
	if (runNo >= 34527 && runNo <=34540) {
		Ebeam = 2.103;
	}
	if (runNo >= 34541 && runNo <=34554) {
		Ebeam = 2.105;
	}
	if (runNo >= 34555 && runNo <=34563) {
		Ebeam = 2.1075;
	}
	if (runNo >= 34564 && runNo <=34573) {
		Ebeam = 2.11;
	}
	if (runNo >= 34574 && runNo <=34584) {
		Ebeam = 2.1125;
	}
	if (runNo >= 34585 && runNo <=34592) {
		Ebeam = 2.115;
	}
	if (runNo >= 34593 && runNo <=34602) {
		Ebeam = 2.1175;
	}
	if (runNo >= 34603 && runNo <=34612) {
		Ebeam = 2.12;
	}
	if (runNo >= 34613 && runNo <=34622) {
		Ebeam = 2.1215;
	}
	if (runNo >= 34623 && runNo <=34633) {
		Ebeam = 2.1225;
	}
	if (runNo >= 34634 && runNo <=34641) {
		Ebeam = 2.124;
	}
	if (runNo >= 34642 && runNo <=34651) {
		Ebeam = 2.125;
	}
	if (runNo >= 34652 && runNo <=34660) {
		Ebeam = 2.1275;
	}
	if (runNo >= 34661 && runNo <=34673) {
		Ebeam = 2.13;
	}
	if (runNo >= 34674 && runNo <=34684) {
		Ebeam = 2.1325;
	}
	if (runNo >= 34685 && runNo <=34694) {
		Ebeam = 2.135;
	}
	if (runNo >= 34695 && runNo <=34704) {
		Ebeam = 2.1375;
	}
	if (runNo >= 34705 && runNo <=34718) {
		Ebeam = 2.14;
	}
	if (runNo >= 34719 && runNo <=34728) {
		Ebeam = 2.1425;
	}
	if (runNo >= 34729 && runNo <=34739) {
		Ebeam = 2.145;
	}
	if (runNo >= 34740 && runNo <=34753) {
		Ebeam = 2.15;
	}
	if (runNo >= 34754 && runNo <=34762) {
		Ebeam = 2.155;
	}
	if (runNo >= 34763 && runNo <=34776) {
		Ebeam = 2.16;
	}
	if (runNo >= 34777 && runNo <=34784) {
		Ebeam = 2.165;
	}
	if (runNo >= 34785 && runNo <=34793) {
		Ebeam = 2.17;
	}
	if (runNo >= 34794 && runNo <=34803) {
		Ebeam = 2.175;
	}
	if (runNo >= 34804 && runNo <=34811) {
		Ebeam = 2.18;
	}
	if (runNo >= 34812 && runNo <=34824) {
		Ebeam = 2.185;
	}
	if (runNo >= 34825 && runNo <=34836) {
		Ebeam = 2.19;
	}
	if (runNo >= 34837 && runNo <=34847) {
		Ebeam = 2.195;
	}
	if (runNo >= 34848 && runNo <=34860) {
		Ebeam = 2.1975;
	}
	if (runNo >= 34861 && runNo <=34868) {
		Ebeam = 2.2;
	}
	if (runNo >= 34869 && runNo <=34881) {
		Ebeam = 2.205;
	}
	if (runNo >= 34882 && runNo <=34890) {
		Ebeam = 2.21;
	}
	if (runNo >= 34891 && runNo <=34899) {
		Ebeam = 2.2125;
	}
	if (runNo >= 34900 && runNo <=34912) {
		Ebeam = 2.215;
	}
	if (runNo >= 34913 && runNo <=34925) {
		Ebeam = 2.22;
	}
	if (runNo >= 34926 && runNo <=34935) {
		Ebeam = 2.225;
	}
	if (runNo >= 34936 && runNo <=34946) {
		Ebeam = 2.23;
	}
	if (runNo >= 34947 && runNo <=34957) {
		Ebeam = 2.24;
	}
	if (runNo >= 34958 && runNo <=34967) {
		Ebeam = 2.25;
	}
	if (runNo >= 34968 && runNo <=34981) {
		Ebeam = 2.26;
	}
	if (runNo >= 34982 && runNo <=35009) {
		Ebeam = 2.27;
	}
	if (runNo >= 35010 && runNo <=35026) {
		Ebeam = 2.275;
	}
	if (runNo >= 35027 && runNo <=35040) {
		Ebeam = 2.28;
	}
	if (runNo >= 35041 && runNo <=35059) {
		Ebeam = 2.285;
	}
	if (runNo >= 35060 && runNo <=35098) {
		Ebeam = 2.29;
	}
	if (runNo >= 35099 && runNo <=35118) {
		Ebeam = 2.295;
	}

	m_Ebeam = Ebeam;

}

void RscanDQ::Number(int runNo){

	double number;

	if (runNo >= 34011 && runNo <=34027) {
		number = 1;
	}
	if (runNo >= 34028 && runNo <=34036) {
		number = 2;
	}
	if (runNo >= 34037 && runNo <=34045) {
		number = 3;
	}
	if (runNo >= 34046 && runNo <=34057) {
		number = 4;
	}
	if (runNo >= 34058 && runNo <=34068) {
		number = 5;
	}
	if (runNo >= 34069 && runNo <=34076) {
		number = 6;
	}
	if (runNo >= 34077 && runNo <=34083) {
		number = 7;
	}
	if (runNo >= 34084 && runNo <=34090) {
		number = 8;
	}
	if (runNo >= 34091 && runNo <=34096) {
		number = 9;
	}
	if (runNo >= 34097 && runNo <=34104) {
		number = 10;
	}
	if (runNo >= 34105 && runNo <=34117) {
		number = 11;
	}
	if (runNo >= 34118 && runNo <=34127) {
		number = 12;
	}
	if (runNo >= 34128 && runNo <=34134) {
		number = 13;
	}
	if (runNo >= 34135 && runNo <=34141) {
		number = 14;
	}
	if (runNo >= 34142 && runNo <=34150) {
		number = 15;
	}
	if (runNo >= 34151 && runNo <=34160) {
		number = 16;
	}
	if (runNo >= 34161 && runNo <=34167) {
		number = 17;
	}
	if (runNo >= 34175 && runNo <=34183) {
		number = 18;
	}
	if (runNo >= 34184 && runNo <=34190) {
		number = 19;
	}
	if (runNo >= 34191 && runNo <=34196) {
		number = 20;
	}
	if (runNo >= 34197 && runNo <=34202) {
		number = 21;
	}
	if (runNo >= 34203 && runNo <=34210) {
		number = 22;
	}
	if (runNo >= 34211 && runNo <=34220) {
		number = 23;
	}
	if (runNo >= 34221 && runNo <=34230) {
		number = 24;
	}
	if (runNo >= 34231 && runNo <=34239) {
		number = 25;
	}
	if (runNo >= 34240 && runNo <=34245) {
		number = 26;
	}
	if (runNo >= 34246 && runNo <=34252) {
		number = 27;
	}
	if (runNo >= 34253 && runNo <=34257) {
		number = 28;
	}
	if (runNo >= 34258 && runNo <=34265) {
		number = 29;
	}
	if (runNo >= 34266 && runNo <=34271) {
		number = 30;
	}
	if (runNo >= 34272 && runNo <=34276) {
		number = 31;
	}
	if (runNo >= 34277 && runNo <=34281) {
		number = 32;
	}
	if (runNo >= 34282 && runNo <=34297) {
		number = 33;
	}
	if (runNo >= 34314 && runNo <=34320) {
		number = 34;
	}
	if (runNo >= 34321 && runNo <=34327) {
		number = 35;
	}
	if (runNo >= 34328 && runNo <=34335) {
		number = 36;
	}
	if (runNo >= 34339 && runNo <=34345) {
		number = 37;
	}
	if (runNo >= 34346 && runNo <=34350) {
		number = 38;
	}
	if (runNo >= 34351 && runNo <=34358) {
		number = 39;
	}
	if (runNo >= 34359 && runNo <=34367) {
		number = 40;
	}
	if (runNo >= 34368 && runNo <=34373) {
		number = 41;
	}
	if (runNo >= 34374 && runNo <=34381) {
		number = 42;
	}
	if (runNo >= 34382 && runNo <=34389) {
		number = 43;
	}
	if (runNo >= 34390 && runNo <=34396) {
		number = 44;
	}
	if (runNo >= 34397 && runNo <=34403) {
		number = 45;
	}
	if (runNo >= 34404 && runNo <=34411) {
		number = 46;
	}
	if (runNo >= 34412 && runNo <=34417) {
		number = 47;
	}
	if (runNo >= 34418 && runNo <=34427) {
		number = 48;
	}
	if (runNo >= 34428 && runNo <=34436) {
		number = 49;
	}
	if (runNo >= 34437 && runNo <=34446) {
		number = 50;
	}
	if (runNo >= 34447 && runNo <=34460) {
		number = 51;
	}
	if (runNo >= 34478 && runNo <=34485) {
		number = 52;
	}
	if (runNo >= 34486 && runNo <=34493) {
		number = 53;
	}
	if (runNo >= 34494 && runNo <=34502) {
		number = 54;
	}
	if (runNo >= 34503 && runNo <=34511) {
		number = 55;
	}
	if (runNo >= 34512 && runNo <=34526) {
		number = 56;
	}
	if (runNo >= 34527 && runNo <=34540) {
		number = 57;
	}
	if (runNo >= 34541 && runNo <=34554) {
		number = 58;
	}
	if (runNo >= 34555 && runNo <=34563) {
		number = 59;
	}
	if (runNo >= 34564 && runNo <=34573) {
		number = 60;
	}
	if (runNo >= 34574 && runNo <=34584) {
		number = 61;
	}
	if (runNo >= 34585 && runNo <=34592) {
		number = 62;
	}
	if (runNo >= 34593 && runNo <=34602) {
		number = 63;
	}
	if (runNo >= 34603 && runNo <=34612) {
		number = 64;
	}
	if (runNo >= 34613 && runNo <=34622) {
		number = 65;
	}
	if (runNo >= 34623 && runNo <=34633) {
		number = 66;
	}
	if (runNo >= 34634 && runNo <=34641) {
		number = 67;
	}
	if (runNo >= 34642 && runNo <=34651) {
		number = 68;
	}
	if (runNo >= 34652 && runNo <=34660) {
		number = 69;
	}
	if (runNo >= 34661 && runNo <=34673) {
		number = 70;
	}
	if (runNo >= 34674 && runNo <=34684) {
		number = 71;
	}
	if (runNo >= 34685 && runNo <=34694) {
		number = 72;
	}
	if (runNo >= 34695 && runNo <=34704) {
		number = 73;
	}
	if (runNo >= 34705 && runNo <=34718) {
		number = 74;
	}
	if (runNo >= 34719 && runNo <=34728) {
		number = 75;
	}
	if (runNo >= 34729 && runNo <=34739) {
		number = 76;
	}
	if (runNo >= 34740 && runNo <=34753) {
		number = 77;
	}
	if (runNo >= 34754 && runNo <=34762) {
		number = 78;
	}
	if (runNo >= 34763 && runNo <=34776) {
		number = 79;
	}
	if (runNo >= 34777 && runNo <=34784) {
		number = 80;
	}
	if (runNo >= 34785 && runNo <=34793) {
		number = 81;
	}
	if (runNo >= 34794 && runNo <=34803) {
		number = 82;
	}
	if (runNo >= 34804 && runNo <=34811) {
		number = 83;
	}
	if (runNo >= 34812 && runNo <=34824) {
		number = 84;
	}
	if (runNo >= 34825 && runNo <=34836) {
		number = 85;
	}
	if (runNo >= 34837 && runNo <=34847) {
		number = 86;
	}
	if (runNo >= 34848 && runNo <=34860) {
		number = 87;
	}
	if (runNo >= 34861 && runNo <=34868) {
		number = 88;
	}
	if (runNo >= 34869 && runNo <=34881) {
		number = 89;
	}
	if (runNo >= 34882 && runNo <=34890) {
		number = 90;
	}
	if (runNo >= 34891 && runNo <=34899) {
		number = 91;
	}
	if (runNo >= 34900 && runNo <=34912) {
		number = 92;
	}
	if (runNo >= 34913 && runNo <=34925) {
		number = 93;
	}
	if (runNo >= 34926 && runNo <=34935) {
		number = 94;
	}
	if (runNo >= 34936 && runNo <=34946) {
		number = 95;
	}
	if (runNo >= 34947 && runNo <=34957) {
		number = 96;
	}
	if (runNo >= 34958 && runNo <=34967) {
		number = 97;
	}
	if (runNo >= 34968 && runNo <=34981) {
		number = 98;
	}
	if (runNo >= 34982 && runNo <=35009) {
		number = 99;
	}
	if (runNo >= 35010 && runNo <=35026) {
		number = 100;
	}
	if (runNo >= 35027 && runNo <=35040) {
		number = 101;
	}
	if (runNo >= 35041 && runNo <=35059) {
		number = 102;
	}
	if (runNo >= 35060 && runNo <=35098) {
		number = 103;
	}
	if (runNo >= 35099 && runNo <=35118) {
		number = 104;
	}

	m_number = number;

}
