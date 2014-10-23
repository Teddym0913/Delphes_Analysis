//-------------------------------------------------
//
//    Particles_Self.cpp
//
//    Defination of the class member function of Particles_Self
//
//    Created by Teddym at 14-5-23
//
//    Version 1.1.3  by Teddym at 14-10-06
//    Remove TLorentzVector, not useful right now
//    Version 2.0.0  by Teddym at 14-9-18
//    Using TLorentzVector to store the information of 4-Vector
//
//    Version 1.1.2
//    Add the particle type char Label[10]
//    Version 1.1.1
//    Fix the calculation of the Phi 
//    Version 1.1.0
//    Add Charge, Change the Method function accordingly  2014-6-3
//    Version 1.0.0
//    First Version
//-------------------------------------------------

#define Particles_Self_cxx
#include "Particles_Self.h"

Particles_Self::Particles_Self()
{
   for(int i=0;i<4;i++)
   {
     P[i]=0;
   }
   PT=0;
   Eta=0;
   Phi=0;
   M=0;
   Charge=0;
//   PVector.SetPtEtaPhiM(0,0,0,0);
   char temp[10]="N.A.";
   strcpy(Label,temp);
   strcpy(Label_lep,temp);

}

Particles_Self::~Particles_Self()
{

}

void Particles_Self::Setting(Float_t Pin[4], Int_t Chargein,const char *labelin)
{
  double TempM,Ptot;
  for(int i=0;i<4;i++)
  {
    P[i]=Pin[i];
  }
  Charge=Chargein;
  strcpy(Label,labelin);
  strcpy(Label_lep,"N.A.");
  PT=sqrt(P[1]*P[1]+P[2]*P[2]);
  Ptot=sqrt(PT*PT+P[3]*P[3]);
//  PVector.SetPxPyPzE(Pin[1],Pin[2],Pin[3],Pin[0]);
  if(PT != 0 )
  {
    Phi=acos(P[1]/PT);
//    if(P[2]>=0)
//    {
//      Phi = Phi;
//    }
//    else
//    {
////      Phi = 2*3.1415926-Phi;
//      Phi = -Phi;
//    }
    Phi = (P[2]>=0)?Phi:-Phi;
    Eta=log((Ptot+P[3])/(Ptot-P[3]))/2;
  }
  else
  {
    Phi = 0;
    Eta = 10;
  }
  TempM = P[0]*P[0]-Ptot*Ptot;
  if(TempM >= 0)
  {
    M = sqrt(TempM);
  }
  else
  {
    M = 0.0;
  }
  M = (TempM>=0)?sqrt(TempM):0.0;

}

void Particles_Self::Setting(Float_t Pin[4], Int_t Chargein,const char *labelin,const char *labellepin)
{
  double TempM,Ptot;
  for(int i=0;i<4;i++)
  {
    P[i]=Pin[i];
  }
  Charge=Chargein;
  strcpy(Label,labelin);
  strcpy(Label_lep,labellepin);
  PT=sqrt(P[1]*P[1]+P[2]*P[2]);
  Ptot=sqrt(PT*PT+P[3]*P[3]);
//  PVector.SetPxPyPzE(Pin[1],Pin[2],Pin[3],Pin[0]);
  if(PT != 0 )
  {
    Phi=acos(P[1]/PT);
//    if(P[2]>=0)
//    {
//      Phi = Phi;
//    }
//    else
//    {
////      Phi = 2*3.1415926-Phi;
//      Phi = -Phi;
//    }
    Phi = (P[2]>=0)?Phi:-Phi;
    Eta=log((Ptot+P[3])/(Ptot-P[3]))/2;
  }
  else
  {
    Phi = 0;
    Eta = 10;
  }
  TempM = P[0]*P[0]-Ptot*Ptot;
  if(TempM >= 0)
  {
    M = sqrt(TempM);
  }
  else
  {
    M = 0.0;
  }
  M = (TempM>=0)?sqrt(TempM):0.0;

}

void Particles_Self::Setting(Float_t PTin, Float_t Etain, Float_t Phiin, Int_t Chargein, Float_t Min,const char *labelin)
{
  PT=PTin;
  Eta=Etain;
  Phi=Phiin;
  M=Min;
  Charge=Chargein;
  strcpy(Label,labelin);
  strcpy(Label_lep,"N.A.");
  P[1]=PT*cos(Phi);
  P[2]=PT*sin(Phi);
  P[3]=PT*sinh(Eta);
  P[0]=sqrt(pow(PT*cosh(Eta),2)+M*M);
//  PVector.SetPtEtaPhiM(PTin,Etain,Phiin,Min);
  
}
void Particles_Self::Setting(Float_t PTin, Float_t Etain, Float_t Phiin, Int_t Chargein, Float_t Min,const char *labelin,const char *labellepin)
{
  PT=PTin;
  Eta=Etain;
  Phi=Phiin;
  M=Min;
  Charge=Chargein;
  strcpy(Label,labelin);
  strcpy(Label_lep,labellepin);
  P[1]=PT*cos(Phi);
  P[2]=PT*sin(Phi);
  P[3]=PT*sinh(Eta);
  P[0]=sqrt(pow(PT*cosh(Eta),2)+M*M);
//  PVector.SetPtEtaPhiM(PTin,Etain,Phiin,Min);
}


Particles_Self Particles_Self::operator + ( Particles_Self &Part2)
{
  Particles_Self Part;
  Float_t tempP[4];
  Int_t tempC;
  char templabel[10];
  strcpy(templabel,Label);
  strcat(templabel,Part2.Label);
  for(int i=0;i<4;i++)
  {
    tempP[i] = P[i]+Part2.P[i];
  }
//  tempP[0]=PVector.E()+Part2.PVector.E();
//  tempP[1]=PVector.Px()+Part2.PVector.Px();
//  tempP[2]=PVector.Py()+Part2.PVector.Py();
//  tempP[3]=PVector.Pz()+Part2.PVector.Pz();
  tempC = Charge + Part2.Charge;
  Part.Setting(tempP, tempC, templabel);
  return Part;
}
