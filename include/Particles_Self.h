//
//   Particles_Self.h
//
//
//   Created by Teddym on 14-5-22
//
//   Used for storing information for every detected particle
//
//   Version 1.1.3  2014-10-06
//   Remove the TLorentzVector. Not useful right now
//   Version 2.0.0
//   Using TLorentzVector to store the information of 4-vector
//
//   Version 1.1.0
//   Add Charge    2014-6-3
//   Version 1.0.0
//   First Version
//--------------------------------------------------------------
//--------------------------------------------------------------

#ifndef Particles_Self_h
#define Particles_Self_h
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Delphes.h" //Or LHEF.h according to your situations
#include <cmath>
#include "TObject.h"
#include "TFile.h"
#include "TMath.h"
#include "TROOT.h"
#include "TClonesArray.h"
#include "TChain.h"
#include "TLorentzVector.h"

using namespace std;
using namespace TMath;

class Particles_Self
{
  public:
    Particles_Self();
    ~Particles_Self();
//    TLorentzVector PVector;
    Float_t P[4];
    Float_t M;
    Float_t PT;
    Float_t Eta;
    Float_t Phi;
    Int_t Charge; 
    char Label[10];
    char Label_lep[10];
    Particles_Self operator + ( Particles_Self &Part2);
    
  public:
    void Setting(Float_t[4], Int_t ,const char* );
    void Setting(Float_t[4], Int_t, const char*, const char*);
    void Setting(Float_t, Float_t, Float_t, Int_t, Float_t, const char*); // Pt; Eta; Phi; Charge; M; Label;
    void Setting(Float_t, Float_t, Float_t, Int_t, Float_t, const char*, const char*); //Pt; Eta; Phi; Charge; M; Label;
//    Float_t PT();
//    Float_t Eta();
//    Float_t Phi();
//    Float_t M();
//    Float_t *P();
    
    

};

class Particles_Jet_Self: public Particles_Self
{
  public:
    Particles_Jet_Self(){ strcpy(Label,"j"); }
    ~Particles_Jet_Self(){};
};

class Particles_Bjet_Self: public Particles_Self
{
  public:
    Particles_Bjet_Self(){ strcpy(Label,"b"); }
    ~Particles_Bjet_Self(){};
};

class Particles_Lep_Self: public Particles_Self
{
  public:
    Particles_Lep_Self(){ strcpy(Label,"l"); }
    ~Particles_Lep_Self(){};
};

class Particles_Elec_Self: public Particles_Self
{
  public:
    Particles_Elec_Self(){ strcpy(Label,"l"); strcpy(Label_lep,"e"); }
    ~Particles_Elec_Self(){};
};

class Particles_Muon_Self: public Particles_Self
{
  public:
    Particles_Muon_Self(){ strcpy(Label,"l"); strcpy(Label_lep,"mu"); }
    ~Particles_Muon_Self(){};
};

//class Particles_CAJet_Self: public Particles_Self
//{
//  public:
//    Particles_CAJet_Self(){ strcpy(Label,"Jca"); }
//    ~Particles_CAJet_Self(){};
//};




#endif
