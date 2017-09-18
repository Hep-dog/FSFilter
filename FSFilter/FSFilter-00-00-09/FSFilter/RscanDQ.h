#ifndef Physics_Analysis_RscanDQ_H
#define Physics_Analysis_RscanDQ_H

class RscanDQ
{

public:

  RscanDQ();
  RscanDQ(int runNo);
  ~RscanDQ();

public:

  int    getStatus() {return m_status;}
  double getEbeam () {return m_Ebeam ;}
  double getEcm   () {return m_Ecm   ;}
  int    getRootID() {return m_RootID;}
  int    getNumber() {return m_number;}
  void   init  (int); 
private:

  void Ecm   (int runNo);
  void Status(int runNo);
  void Ebeam (int runNo);
  void Number(int runNo);
  double Cal4230(int runNo);
  double Cal4260(int runNo);

private:

  double m_Ecm   ;
  double m_Lumi  ;
  double m_Ebeam ;
  int    m_status;
  int    m_number;
  int    m_RootID;
};

#endif
