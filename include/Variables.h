//
//  Variables.h
//  
//
//  Created by Teddym on 13-12-10.
//
//  version v1.3.0
//  version v1.2.0

#ifndef _Variables_h
#define _Variables_h
#include <cmath>
#include <string.h>
#include <time.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TRef.h>
#include <TRefArray.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>
#include "Self_Analysis.h"


inline void DISPLAY_SELF(int i, int n, time_t start);

inline void DISPLAY_CUTS_RESULT(int Cuts_Flow[6], int nevents, int Ncuts);


//template< typename HISTO >
inline void DRAW_HISTO_SELF(TH1F *H1, char Name[50], double Scale_factor);

inline double MET_vs_HT_SELF(Self_Events_Classify event);

inline double Meff_SELF(Self_Events_Classify event);

inline double HT_SELF(Self_Events_Classify event);

inline double DELTA_R_SELF(Particles_Self P1, Particles_Self P2);

inline double COSTHETA_SELF(Particles_Self P1, Particles_Self P2);

inline double Invariant_Mass_SELF(Particles_Self P1, Particles_Self P2);

inline double Invariant_Mass_SELF(Particles_Self P1, Particles_Self P2, Particles_Self P3);

inline double TRANS_MASS(Particles_Self PL, Float_t PMET[2]);


inline double squarkCS_3rd(double *para,double M)
{
  return (exp(para[0]+para[1]*M+para[2]*M*M+para[3]*M*M*M+para[4]*M*M*M*M+para[5]/M)*1000); //in fb
}

inline void DISPLAY_SELF(int i, int n, time_t start)
{
   double PER;
   long duration;
   int min,sec,hour;
   time_t Now;
   int nn = n/20;
   int a = (i+1)%nn;
   if( i == 0 || a == 0 || i == n-1 )
   {
     PER=i/((double)n-1);
     a = (int)(PER*20+0.5);
     string b(a,'#');
     string c(20-a,'-');
     Now = time(NULL);
     duration = Now-start;
     min=((int)(duration/60))%60;
     sec=(duration)%60;
     hour=(int)(duration/3600);
     cout<<"\r"<<"["<<b<<c<<"]"<<setprecision(2)<<setiosflags(ios::fixed)<<PER*100<<"%  ["<<setw(2)<<hour<<"h"<<setw(3)<<min<<"min"<<setw(3)<<sec<<"sec"<<" ]"<<flush;
     cout.unsetf(ios::fixed);
     cout<<setprecision(5);
   }
   if(i==n-1)
   {
     cout<<endl;
   }
}

inline void DISPLAY_CUTS_RESULT(int Cuts_Flow[10], int nevents, int Ncuts)
{
   cout<<"The Events left after each Cuts are:"<<endl;
   cout<<setw(11)<<"#Cuts"<<setw(9)<<"No Cuts";
   for(int i=1;i<=Ncuts;i++)
   {
       cout<<setw(8)<<"Cut-"<<i;
   }
   cout<<endl;
   cout<<setw(11)<<"Events_Flow";//<<setw(9)<<nevents;
   for(int i=0;i<=Ncuts;i++)
   {
        cout<<setw(9)<<Cuts_Flow[i];
   }
   cout<<endl;
}

//template< typename HISTO >
inline void DRAW_HISTO_SELF(TH1F *H1, char Name[200], double Scale_Factor)
{
  H1->Scale(Scale_Factor);
  H1->Draw();
  strcat(Name,".root");
  H1->SaveAs(Name);
}

inline double Meff_SELF(Self_Events_Classify event)
{
   double Meff=0;
   for(int i=0;i<event.Bjet_Multi;i++)
   {
     Meff = Meff + event.Bjet_P_Self[i].PT;
   }
   for(int i=0;i<event.Jet_Multi;i++)
   {
     Meff = Meff + event.Jet_P_Self[i].PT;
   }
   for(int i=0;i<event.Lep_Multi;i++)
   {
     Meff = Meff + event.Lep_P_Self[i].PT;
   }
   Meff = Meff + event.MET[0];
   return Meff;
}

inline double HT_SELF(Self_Events_Classify event)
{
    Float_t HT=0.0;

    for(int i=0;i<event.Bjet_Multi;i++)
    {
      HT = HT + event.Bjet_P_Self[i].PT;
    }
    for(int j=0;j<event.Jet_Multi;j++)
    {
      HT = HT + event.Jet_P_Self[j].PT;
    }
    return HT;
}

inline double MET_vs_HT_SELF(Self_Events_Classify event)
{
    Float_t HT=0.0;
    double ALPHA;
    for(int i=0;i<event.Bjet_Multi;i++)
    {
      HT = HT + event.Bjet_P_Self[i].PT;
    }
    for(int j=0;j<event.Jet_Multi;j++)
    {
      HT = HT + event.Jet_P_Self[j].PT;
    }
    ALPHA = event.MET[0]/sqrt(HT);
    return ALPHA;
}


inline double DELTA_R_SELF(Particles_Self P1, Particles_Self P2)
{
    double dR,DeltaPhi;
    DeltaPhi=P1.Phi-P2.Phi;
    if( fabs(DeltaPhi) > 3.1415926 )
    {
      DeltaPhi = 2*3.1415926 - fabs(DeltaPhi);
    }
    dR=sqrt(pow(DeltaPhi,2)+pow(P1.Eta-P2.Eta,2));
    return dR;
}

inline double COSTHETA_SELF(Particles_Self P1, Particles_Self P2)
{
  double costheta,pp1,pp2;
  pp1=sqrt(pow(P1.P[1],2)+pow(P1.P[2],2)+pow(P1.P[2],2)); 
  pp2=sqrt(pow(P2.P[1],2)+pow(P2.P[2],2)+pow(P2.P[2],2)); 
  costheta =(P1.P[1]*P2.P[1]+P1.P[2]*P2.P[2]+P1.P[3]*P2.P[3])/(pp1*pp2);
  return costheta;
}
inline double Invariant_Mass_SELF(Particles_Self P1, Particles_Self P2)
{
    Particles_Self P3;
    P3 = P1 + P2;
    return P3.M;
}

inline double Invariant_Mass_SELF(Particles_Self P1, Particles_Self P2, Particles_Self P3)
{
    Particles_Self P4;
    P4 = P1 + P2 + P3;
    return P4.M;
}

inline double TRANS_MASS(Particles_Self PL, Float_t PMET[2])
{
    double MT;
    MT=sqrt(2*PL.PT*PMET[0]*(1-cos(PL.Phi-PMET[1])));
    return MT;
}

//abcd

#endif
