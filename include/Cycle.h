#ifndef __Cycle_h__
#define __Cycle_h__

#include <iostream>
#include <fstream>
#include "TTree.h"
#include <string>

using namespace std;

inline void cycle(int, int, double*, double*, double*, double*, int*, string*, string*, TTree*, ofstream &);


inline void cycle(int n,int NCuts,double* param,double* param_min,double* param_max,double* step,int* flow,string* cuts, string* Tcuts,TTree* Tbas, ofstream &outfile)
{
  char buffer[200];
  for(param[n]=param_min[n];param[n]<=param_max[n];param[n]=param[n]+step[n])
  {
    sprintf(buffer,"%f",param[n]);
    if(n==0)
    {
      Tcuts[n] = cuts[n] + buffer;
    }
    else
    {
      Tcuts[n] = Tcuts[n-1] + "&&" + cuts[n] + buffer;
    }
    flow[n]=Tbas->GetEntries(Tcuts[n].c_str());
    if(n!=(NCuts-1))
    {
      cycle(n+1,NCuts,param,param_min,param_max,step,flow,cuts,Tcuts,Tbas,outfile);
    }
    else
    {
      Double_t kfactor;
      Int_t nTotal;
      Double_t weight;
      Tbas->SetBranchAddress("N_total",&nTotal);
      Tbas->SetBranchAddress("Weight",&weight);
      Tbas->SetBranchAddress("K_Factor",&kfactor);
      Tbas->GetEntry(0);
      outfile<<"Origin:"<<nTotal*weight*300*kfactor<<"    Basic:"<<Tbas->GetEntries()*weight*300*kfactor<<"    ";
      double Events[10];
      for(int i=0;i<NCuts;i++)
      {
        Events[i] = flow[i] * weight * 300 * kfactor; 
        outfile<<cuts[i]<<param[i]<<":"<<Events[i]<<"    ";
      }
      outfile<<endl;
    }
  }

}
#endif

