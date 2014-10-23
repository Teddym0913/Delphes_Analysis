//
//  Self_Analysis.h
//  
//
//  Created by Teddym on 14-03-20.
//
//  Used for simplifying the analysis of the output root files 
//  
//   Version 1.3.0  by teddym at 14-9-10
//   Adding Basic cuts in this step ( Ignore those Jets or Leptons do not satisfy the requirement )
//   Accordingly adding some member data and member function in the class Self_Events_Classify
//
//   Version 1.2.0
//   Add the Setting function instead of using Constructor!
//
//   Version 1.1.1
//   Add the label for each type of final state  14-06-16 
//
//   Version 1.1.0
//   by teddym at 14-06-10
//   Add special jets components
//
//   Version 1.0.0
//   First Version 
//-------------------------------------------------------------
//-------------------------------------------------------------

#ifndef Self_Analysis_h 
#define Self_Analysis_h
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
#include "Particles_Self.h"

using namespace std;
using namespace TMath;

class Self_Events_Classify
{
 public:
   Self_Events_Classify();// Or LHEF *event
   ~Self_Events_Classify();
   void Set_Events(Delphes* );
   int Jet_Multi;          // Number of jets not include b-jets after basic cuts
   int Bjet_Multi;         // Number of b-jets after basic cuts
   int Jet_Survive_Multi;  // Number of total jets including b-jets after basic cuts
   int Jet_tot_Multi;      // Number of All jets before basic cuts
   int Lep_Multi;
   int Elec_Multi;
   int Muon_Multi;
   int Lep_tot_Multi;
   int Elec_tot_Multi;
   int Muon_tot_Multi;   
   int CAJet_Multi;
   Float_t MET[2]; // 0: MET  1: Phi of MET 
   Particles_Jet_Self Jet_Survive_P_Self[10];  //All jets information including bjets after basic cuts
   Particles_Jet_Self Jet_P_Self[10];  // Not include bjets after basic cuts
//   Particles_Jet_Self Jet_P_Rub[10];  //  All jets that not pass the basic cuts
   Particles_Bjet_Self Bjet_P_Self[10];  // All b jets after basic cuts
   Particles_Lep_Self Lep_P_Self[10];
//   Particles_Lep_Self Lep_P_Rub[10];
   Particles_Elec_Self Elec_P_Self[10];
//   Particles_Elec_Self Elec_P_Rub[10];
   Particles_Muon_Self Muon_P_Self[10];
//   Particles_Muon_Self Muon_P_Rub[10];
//   Particles_CAJet_Self CAJet_P_Self[10];
   
 public:
   bool Basic_Cuts_Jets(Delphes*, int);
   bool Basic_Cuts_Ele(Delphes*, int);
   bool Basic_Cuts_Muon(Delphes*, int);

};




#endif
