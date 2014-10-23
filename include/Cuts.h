//------------------------------------------------------------
//------------------------------------------------------------
//
//  Cuts.h
//  
//
//  Created by Teddym on 14-03-21.
//
//  Used for setting cuts to the events 
//
//  Version 1.3.0 
//  Modified by Teddy On 14-04-07
//-------------------------------------------------------------
//-------------------------------------------------------------

#ifndef CUTS_H
#define CUTS_H
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
#include "Self_Analysis.h"
#include "Variables.h"


class Self_Cuts
{
  public :
    int Cuts_result;
//    int B_higgs[2];
//    int J_W[2];
    int nCuts;
    int nEventsPass;
    int Cuts_Flow[20];
//    double HiggsMassClose;
//    double WMassClose;
    void CountGood();
    void Basic_Cuts(Self_Events_Classify);    // Basic Cuts, Such the minimum Pt for Jets/lepton, the dR Cuts, Basic Eta Cuts etc. 
    void Total_Jets_Multi_Cuts(Self_Events_Classify,int);
    void Bjets_Jets_Multi_Cuts(Self_Events_Classify, int, int);  // First int is the min # of B-jets the second is the min # of normal jets
    void Lep_Multi_Cuts(Self_Events_Classify, int, int,int);           // first int # of lepton  second int for two or more lepton with same- sign or oppsite sign, third int for the same flavor or not in 2-lep case
//    void CAJet_Cuts(Self_Events_Classify,int,double,double);             // CA algorithm Jets  first int for the minimum number of such kind of Jets, the second and third double for the mass cuts 
    void MET_vs_HT_Cuts(Self_Events_Classify, double);          // min value of MET/sqrt(HT)
    void Pt_Cuts(Particles_Self, double, double);                 //  First for min  second for max( if 0 no cuts on max)
    void HT_Cuts(Self_Events_Classify, double);
    void Meff_Cuts(Self_Events_Classify,double);               // double for the min value of Meff 
    void Invariant_Mass_Cuts(Particles_Self,Particles_Self,double,double);
    void COSTHETA_Cuts(Particles_Self,Particles_Self,double,double); //First double  for minimum second for maximum ( one of these set to be 0 means no minimum or maximum )
    void TRANS_MASS_Cuts(Self_Events_Classify, double);  
    void MET_Cuts(Self_Events_Classify, double);    
    void Bjets_Higgs_Mass_Cuts(Self_Events_Classify);
    void TRANS_TOP_MASS_Cuts(Self_Events_Classify);
    void Jets_W_Mass_Cuts(Self_Events_Classify);
    void Top_Veto(Self_Events_Classify);
    void Top_Veto_2(Self_Events_Classify);

  public :
    Self_Cuts()
    {
       Cuts_result = 1;  // initiate the cuts result to TRUE(1)
       nCuts = 0;
       nEventsPass = 0;
       for(int k=0;k<20;k++){ Cuts_Flow[k]=0; }
//       cout<<"Please enter the parameters that should be passed into your own cuts"<<endl:
//       cout<<"Number of B-jets: ";
//       cin>>nbjets;
//       cout<<endl<<"Number of Normal-jets: ";
//       cin>>njets;
//       cout<<endl<<" ";
    }
    void Reset_Cuts()
    {
       Cuts_result = 1; // Reset the cuts result to TRUE(1);
       nCuts = 0;  // Reset the # of Cut.
       nEventsPass = nEventsPass + 1;  // Count the events have passed through all cuts.
       Cuts_Flow[nCuts] = Cuts_Flow[nCuts] + 1;
    }

};




#endif
