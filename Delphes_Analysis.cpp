#include <iostream>
#include <fstream>
#include <string>
#include <TChain.h>
#include <TFile.h>
#include <TCanvas.h>
#include "TApplication.h"
#include "Delphes.h"
#include <TTree.h>
#include <cmath>
#include <TH1F.h>
#include <TH2F.h>
#include "Variables.h"
#include "Self_Analysis.h"
#include "Cuts.h"
#include "Cycle.h"
#include "Basic_Cuts_Out.h"
using namespace std;

void Display_Help(char* argv[]);

int main(int argc, char* argv[]){

  if( argc == 1 )
  {
    Display_Help(argv);
    return 1;
  }
  string Mode = argv[1];
  int Nmode = atoi(Mode.c_str());
  if( Nmode == 0 )
  {
    if( argc != 6 )
    {
      Display_Help(argv);
      return 1;
    }
    else
    {
      string delphespath = argv[5];
      delphespath = delphespath + "*.root";
    
      TChain *chainDelphes = new TChain("Delphes");
      chainDelphes->Add(delphespath.c_str());
      Delphes* delphesanalysis = new Delphes(chainDelphes);

      string outputname = "./Data_af_Basic/";
      outputname = outputname + argv[2] + "_out_af_Basic.root";
    
      string CS_info = argv[3];
      string kfactor_info = argv[4];
      double Tot_CS = atof(CS_info.c_str());
      double k_Factor = atof(kfactor_info.c_str());
      cout<<chainDelphes->GetEntries()<<endl;  
      int nLeft=Basic_Cuts_Out(chainDelphes,delphesanalysis,outputname,Tot_CS,k_Factor);
      cout<<"Process:  "<<argv[2]<<endl;
      cout<<"Number of Total Events:  "<<chainDelphes->GetEntries()<<endl;
      cout<<"Number of Events left:   "<<nLeft<<endl; 
    
      return 0;
    }
  }
  else if( Nmode == 1 )
  {
    if( argc != 5 )
    {
      Display_Help(argv);
      return 1;
    }
    else
    {
      string inputroot;
      inputroot = argv[3];
      TFile *f = new TFile(inputroot.c_str(),"read");
      TTree *Tbas = (TTree*)f->Get("af_Basic");
//      Int_t nTotal;
//      Double_t weight;
//      Tbas->SetBranchAddress("N_total",&nTotal);
//      Tbas->SetBranchAddress("Weight",&weight);
//      Tbas->GetEntry(0);
      string cuts[7];
      cuts[0]="MET>";
      cuts[1]="Meff>";
      cuts[2]="Mll>";
      cuts[3]="Mll<";
      cuts[4]="Mllb>";
      cuts[5]="Nj>=";
      cuts[6]="Nb>=";
    
      string outputdat;
      outputdat = argv[4];
      string Tcuts[7];
      char buffer[256];
      int flow[7];
      ofstream outfile(outputdat.c_str(),ios::out);
      double param[7];
      double param_min[7]={120,400,85,95,200,4,1};
      double param_max[7]={200,600,85,95,600,6,4};
      double step[7]={20,50,1,1,80,1,1};
      cycle(0,7,param,param_min,param_max,step,flow,cuts,Tcuts,Tbas,outfile);
      outfile.close();
      return 0;
    }
  }
  else if( Nmode == 2 )
  {
    ifstream infileBR("PlusMu_BR_Info.dat");
    ifstream infileFit("3rd-squark-CS-fit_para.dat");
    double cspara[6]={0};
    string tag;
    while(infileFit)
    {
      infileFit>>tag;
      if(tag=="##") 
      {
        infileFit.ignore(99,'\n');
      }
      else
      { 
        cspara[0]=atof(tag.c_str());
        //cout<<cspara[0]<<endl;
        for(int i=1;i<6;i++) 
        {
          infileFit>>cspara[i];
         // cout<<cspara[i]<<endl;
        }
      }
      infileFit.ignore(999,'\n');
      char first;
      infileFit.get(first);
      infileFit.putback(first);
    }
    infileFit.close();
    
    int M3ql,M1;
    double Msb,TotBR;
    double CSfinal;
    while(infileBR)
    {
      infileBR>>tag;
      if(tag=="##")
      {
        infileBR.ignore(99,'\n');
      }
      else
      {
        M3ql=atoi(tag.c_str());
        infileBR>>M1>>Msb>>TotBR;
      
        CSfinal=squarkCS_3rd(cspara,Msb)*TotBR;
      
        char buffer[200];
        sprintf(buffer,"Msb_%d.M1_%d",M3ql,M1);
      
        string delphespath = "/home/teddy/workingspace/MC-Package/MG5_aMC_v2_2_1/My_Data/PlusMu_Data/Before_Cuts/";
        delphespath = delphespath + buffer + "/*.root";
    
        TChain *chainDelphes = new TChain("Delphes");
        chainDelphes->Add(delphespath.c_str());
        Delphes* delphesanalysis = new Delphes(chainDelphes);

        string outputname = "./Data_af_Basic/Signal/";
        outputname = outputname + buffer + "_out_af_Basic.root";
    
        //string CS_info = argv[3];
        //double Tot_CS = atof(CS_info.c_str());
        cout<<chainDelphes->GetEntries()<<endl;  
        int nLeft=Basic_Cuts_Out(chainDelphes,delphesanalysis,outputname,CSfinal);
        
        delete delphesanalysis;
        delete chainDelphes;
        //delete delphesanalysis;
        TFile *f = new TFile(outputname.c_str(),"read");
        TTree *Tbas = (TTree*)f->Get("af_Basic");
//        Int_t nTotal;
//        Double_t weight;
//        Tbas->SetBranchAddress("N_total",&nTotal);
//        Tbas->SetBranchAddress("Weight",&weight);
//        Tbas->GetEntry(0);
        string cuts[5];
        cuts[0]="MET>";
        cuts[1]="Ht>";
        cuts[2]="MT>";
        cuts[3]="Nj>=";
        cuts[4]="Nb>=";
    
        string outputdat="./Data_af_Advanced/Signal/PlusMu_";
        outputdat = outputdat + buffer + "_out_af_Advanced.dat";
        string Tcuts[5];
        int flow[5];
        ofstream outfile(outputdat.c_str(),ios::out);
        double param[5];
        double param_min[5]={120,400,100,4,2};
        double param_max[5]={200,600,200,6,4};
        double step[5]={20,50,20,1,1};
        cycle(0,5,param,param_min,param_max,step,flow,cuts,Tcuts,Tbas,outfile);
        outfile.close();
        
        infileBR.ignore(999,'\n');
        char first;
        infileBR.get(first);
        infileBR.putback(first);
      }
    }
    return 0; 
  }
  else
  {
    Display_Help(argv);
    return 1;
  }
}

void Display_Help(char *argv[])
{
  {
    cout<<"===================================================================="<<endl;
    cout<<"        Please Enter Related Information of your Process:"<<endl;
    cout<<"        "<<argv[0]<<" Mode_Number [options]"<<endl;
    cout<<"        Mode Number: 0 for Basic cuts;"<<endl;
    cout<<"                     1 for Advanced cuts;"<<endl;
    cout<<"                     2 for Looping all Signals or Backgrounds Processes"<<endl;
    cout<<"        If Mode Number == 0:  "<<endl;
    cout<<"            "<<argv[0]<<" 0 PRO_NAME PRO_CS K_Factor PATH_TO_ROOT_FILES"<<endl;
    cout<<"            Note: if K_Factor == 1 then assume that CS is NLO value"<<endl;
    cout<<"                  else CS is the LO value given by MG5"<<endl;
//    cout<<"            or"<<endl;
//    cout<<"            "<<argv[0]<<" 0 PROC_INFO_DATA_FILE"<<endl;
    cout<<"        If Mode Number == 1:  "<<endl;
    cout<<"            "<<argv[0]<<" 1 PRO_NAME BASIC_CUTS_ROOT_FILES ADVANCED_CUTS_DAT_FILES"<<endl;
    cout<<"        If Mode Number == 2:  "<<endl;
    cout<<"            You may need to check in the main function."<<endl;
    cout<<"            No More Options"<<endl;
    cout<<"===================================================================="<<endl;
  }
}
