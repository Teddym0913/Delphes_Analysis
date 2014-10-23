//
//
//     Basic_Cuts_Out.h
//     by Teddym 14-9-18
//
//     Version 1.0.0
//     First Version
//
//

#ifndef _Basic_Cuts_Out_h
#define _Basic_Cuts_Out_h

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "Self_Analysis.h"
#include "Delphes.h"
#include "Variables.h"
#include "Cuts.h"
#include <string>

using namespace std;

inline int Basic_Cuts_Out(TChain* TC, Delphes* Del, string OutFileName, double Tot_CS, double k_Factor=1);

inline int Basic_Cuts_Out(TChain* TC, Delphes* Del, string OutFileName, double Tot_CS, double k_Factor)
{
  TFile *FOut = new TFile(OutFileName.c_str(),"recreate");
  TTree *TOut = new TTree("af_Basic","Results after Basic Cuts");
  
  Int_t b_Ntot;
  Double_t b_Weight;
  Double_t b_KFactor;
  Double_t b_Meff;
  Double_t b_Ht;
  Double_t b_MET;
  Double_t b_Mll;
  Double_t b_Mllb;
//  Double_t b_MT;
  Int_t b_Nj;
  Int_t b_Nb;
  Int_t b_BasicCuts;
  TOut->Branch("N_total",&b_Ntot,"N_total/I");
  TOut->Branch("Weight",&b_Weight,"Weight/D");
  TOut->Branch("K_Factor",&b_KFactor,"K_Factor/D");
  TOut->Branch("Meff",&b_Meff,"Meff/D");
  TOut->Branch("Ht",&b_Ht,"Ht/D");
  TOut->Branch("MET",&b_MET,"MET/D");
  TOut->Branch("Mll",&b_Mll,"Mll/D");
  TOut->Branch("Mllb",&b_Mllb,"Mllb/D");
//  TOut->Branch("MT",&b_MT,"MT/D");
  TOut->Branch("Nj",&b_Nj,"Nj/I");
  TOut->Branch("Nb",&b_Nb,"Nb/I");
  TOut->Branch("BasicCuts",&b_BasicCuts,"BasicCuts/I");
  
  int nevents = TC->GetEntries();
  int nCuts=0;
  Self_Cuts Cuts1;
  Self_Events_Classify Ana_Event;
//  time_t start=time(NULL);
  for(int i=0;i<nevents;i++)
  {
    Del->GetEntry(i);
    Ana_Event.Set_Events(Del);
    
    Cuts1.Reset_Cuts();
    Cuts1.Lep_Multi_Cuts(Ana_Event,2,-1,1);
    Cuts1.Basic_Cuts(Ana_Event);
    nCuts=Cuts1.nCuts;
    
    if(Cuts1.Cuts_result==1)
    {
      b_Ntot = nevents;
      b_Weight = Tot_CS/nevents;
      b_KFactor = k_Factor;
      b_Meff = Meff_SELF(Ana_Event);
      b_Ht = HT_SELF(Ana_Event);
      b_MET = Ana_Event.MET[0];
      b_Mll = Invariant_Mass_SELF(Ana_Event.Lep_P_Self[0],Ana_Event.Lep_P_Self[1]);
      b_Mllb = Invariant_Mass_SELF(Ana_Event.Lep_P_Self[0],Ana_Event.Lep_P_Self[1],Ana_Event.Bjet_P_Self[0]);
//      b_MT = TRANS_MASS(Ana_Event.Lep_P_Self[0],Ana_Event.MET);
      b_Nj = Ana_Event.Jet_Survive_Multi;
      b_Nb = Ana_Event.Bjet_Multi;
      b_BasicCuts = Cuts1.Cuts_result;
      TOut->Fill();
    }
    
//    DISPLAY_SELF(i,nevents,start);
  }
  FOut->Write();

//  FOut->Close();
  
  return Cuts1.Cuts_Flow[nCuts];

}

#endif
