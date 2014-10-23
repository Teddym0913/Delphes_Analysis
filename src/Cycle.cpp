#include "Cycle.h"

//void cycle(int n,int NCuts,int nevents,double weight,double* param,double* param_min,double* param_max,double* step,int* flow,string* cuts, string* Tcuts,TTree* Tbas, ofstream &outfile)
//{
//  char buffer[200];
//  for(param[n]=param_min[n];param[n]<=param_max[n];param[n]=param[n]+step[n])
//  {
//    sprintf(buffer,"%f",param[n]);
//    if(n==0)
//    {
//      Tcuts[n] = cuts[n] + buffer;
//    }
//    else
//    {
//      Tcuts[n] = Tcuts[n-1] + "&&" + cuts[n] + buffer;
//    }
//    flow[n]=Tbas->GetEntries(Tcuts[n].c_str());
//    if(n!=(NCuts-1))
//    {
//      cycle(n+1,NCuts,nevents,weight,param,param_min,param_max,step,flow,cuts,Tcuts,Tbas,outfile);
//    }
//    else
//    {
//      outfile<<"Origin:"<<nevents<<"    Basic:"<<Tbas->GetEntries()<<"    ";
//      double Events[10];
//      for(int i=0;i<NCuts;i++)
//      {
//        Events[i] = flow[i] * weight * 300; 
//        outfile<<cuts[i]<<param[i]<<":"<<Events[i]<<"    ";
//      }
//      outfile<<endl;
//    }
//  }

//}
