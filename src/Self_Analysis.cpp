//------------------------------------
//
//   Self_Analysis.c
//
//   Defination of the Class Self_Events_Classify
//
//   
//   Version 1.3.1  by teddym at 14-10-06
//   A little change in the code try to improve the time-consuming
//
//   Version 1.3.0  by teddym at 14-9-10
//   Adding Basic cuts in this step ( Ignore those Jets or Leptons do not satisfy the requirement )
//   Accordingly adding some member data and member function in the class Self_Events_Classify
//
//   version 1.2.0
//   Add the Setting function instead of using Constructor!
//
//   version 1.1.1
//   Add the label for each type of final state  14-06-16 
//
//   version 1.1.0
//   by teddym at 14-06-10
//   Add special jets components
//
//   By Teddym at 14-03-20
//   version 1.0.0
//------------------------------------

#define Self_Analysis_cxx
#include "Self_Analysis.h"

Self_Events_Classify::Self_Events_Classify()
{

}

bool Self_Events_Classify::Basic_Cuts_Jets(Delphes* event, int Jet_Index)
{
  double dPhi_jMet;
  dPhi_jMet = fabs(event->Jet_Phi[Jet_Index]-event->MissingET_Phi[0]);
//  if( dPhi_jMet > 3.1415926 )
//  {
//    dPhi_jMet = 2*3.1415926 - dPhi_jMet;
//  }
  dPhi_jMet = (dPhi_jMet > 3.1415926) ? 2*3.1415926-dPhi_jMet : dPhi_jMet; 
//  if(fabs(event->Jet_Eta[Jet_Index])>=2.5 || event->Jet_PT[Jet_Index] <= 25 || dPhi_jMet < 0.6 )
//  {
//    return false;
//  }
//  else
//  {
//    return true;
//  }
  return (fabs(event->Jet_Eta[Jet_Index])>=2.5 || event->Jet_PT[Jet_Index] <= 25 || dPhi_jMet < 0.6 ) ? false : true;
}

bool Self_Events_Classify::Basic_Cuts_Ele(Delphes* event, int Ele_Index)
{
  double dRmin=7.0,temp,dphi,deta;
  for(int i=0;i<Jet_Survive_Multi;i++)
  {
    dphi = fabs(Jet_Survive_P_Self[i].Phi-event->Electron_Phi[Ele_Index]);
//    if(dphi > 3.1415926)
//    {
//      dphi = 2*3.1415926 - dphi;
//    }
    dphi = (dphi>3.1415926)?2*3.1415926-dphi:dphi;
    deta = fabs(Jet_Survive_P_Self[i].Eta-event->Electron_Eta[Ele_Index]);
    temp = sqrt(pow(dphi,2)+pow(deta,2));
//    if(temp < dRmin)
//    {
//      dRmin = temp;
//    }
    dRmin = (temp < dRmin)?temp:dRmin;
  }
//  if(fabs(event->Electron_Eta[Ele_Index])>=2.5 || event->Electron_PT[Ele_Index] <= 20 || dRmin < 0.4)
//  {
//    return false;
//  }
//  else
//  {
//    return true;
//  }
  return (fabs(event->Electron_Eta[Ele_Index])>=2.5 || event->Electron_PT[Ele_Index] <= 20 || dRmin < 0.4)?false:true;
}

bool Self_Events_Classify::Basic_Cuts_Muon(Delphes* event, int Muon_Index)
{
  double dRmin=7.0,temp,dphi,deta;
  for(int i=0;i<Jet_Survive_Multi;i++)
  {
    dphi = fabs(Jet_Survive_P_Self[i].Phi-event->Muon_Phi[Muon_Index]);
//    if(dphi > 3.1415926)
//    {
//      dphi = 2*3.1415926 - dphi;
//    }
    dphi=(dphi>3.1415926)?2*3.1415926-dphi:dphi;
    deta = fabs(Jet_Survive_P_Self[i].Eta-event->Muon_Eta[Muon_Index]);
    temp = sqrt(pow(dphi,2)+pow(deta,2));
//    if(temp < dRmin)
//    {
//      dRmin = temp;
//    }
    dRmin=(temp<dRmin)?temp:dRmin;
  }
//  if(fabs(event->Muon_Eta[Muon_Index])>=2.5 || event->Muon_PT[Muon_Index] <= 20 || dRmin < 0.4)
//  {
//    return false;
//  }
//  else
//  {
//    return true;
//  }
  return (fabs(event->Muon_Eta[Muon_Index])>=2.5 || event->Muon_PT[Muon_Index] <= 20 || dRmin < 0.4)?false:true;
}

void Self_Events_Classify::Set_Events(Delphes* event)
{
//---------------------
//  Find MET 
//---------------------
    
    MET[0]=event->MissingET_MET[0];
    MET[1]=event->MissingET_Phi[0];
//    cout<<MET[0]<<"; "<<MET[1]<<endl;
    
//-----------
// Find Normal Jets, B-jets
//-----------
//   cout<<"Hello"<<endl;
   Bool_t BtagOK, JetOK;
   Jet_Multi=0;
   Bjet_Multi=0;
   Jet_tot_Multi=0;
   char charJet[10]="j";
   char charBjet[10]="b";
//   cout<<Jet_tot_Multi<<endl;
   Jet_tot_Multi = event->Jet_size;
//   cout<<Jet_tot_Multi<<endl;
//   for(int i=0;i<Jet_tot_Multi;i++)
//   {
//      BtagOK = ( event->Jet_BTag[i] & ( 1<<0 ) );
//      if(BtagOK)
//      {
//        Bjet_Multi=Bjet_Multi+1;
//      }
//   }      
//   Jet_Multi=Jet_tot_Multi-Bjet_Multi;
//   Jet_P_Self = new Particles_Self[Jet_Multi];
//   Bjet_P_Self = new Particles_Self[Bjet_Multi];
//   Jet_P_Self = new Float_t* [Jet_Multi];     //  0   1   2   3   4   5   6   7
//   for(int j=0;j<Jet_Multi;j++) { Jet_P_Self[j] = new Float_t[8];}
//   (*Bjet_P_Self)[8] = new Float_t[Bjet_Multi][8];   //  E   Px  Py  Pz  M   PT  ETA phi 
   int nj=0;
   int nb=0;
   int nsurJ=0;
   int nRubJ=0;
   for(int i=0;i<Jet_tot_Multi;i++)
   { 
//     cout<<i<<endl;
     JetOK = Basic_Cuts_Jets(event,i);
     BtagOK = ( event->Jet_BTag[i] & ( 1<<0 ) );
     if(!BtagOK && JetOK)
     {
       Jet_P_Self[nj].Setting(event->Jet_PT[i],event->Jet_Eta[i],event->Jet_Phi[i],event->Jet_Charge[i],event->Jet_Mass[i],charJet);
       Jet_Survive_P_Self[nsurJ].Setting(event->Jet_PT[i],event->Jet_Eta[i],event->Jet_Phi[i],event->Jet_Charge[i],event->Jet_Mass[i],charJet);

       nj=nj+1;
       nsurJ=nsurJ+1;
//       cout<<nj<<endl;
     }
     else if(BtagOK && JetOK)
     {
       Bjet_P_Self[nb].Setting(event->Jet_PT[i],event->Jet_Eta[i],event->Jet_Phi[i],event->Jet_Charge[i],event->Jet_Mass[i],charBjet);
       Jet_Survive_P_Self[nsurJ].Setting(event->Jet_PT[i],event->Jet_Eta[i],event->Jet_Phi[i],event->Jet_Charge[i],event->Jet_Mass[i],charJet);

       nb=nb+1;
       nsurJ=nsurJ+1;
//       cout<<nb<<endl;
     }
     else if( !JetOK )
     {
//       Jet_P_Rub[nRubJ].Setting(event->Jet_PT[i],event->Jet_Eta[i],event->Jet_Phi[i],event->Jet_Charge[i],event->Jet_Mass[i],charJet);
       nRubJ=nRubJ+1;
     }
     else
     {
       cout<<"Find Other B-tag message: "<<event->Jet_BTag[i]<<endl;
       cout<<"You should recheck this info and rewrite the program about B-tag"<<endl;
     }
   }
   Jet_Multi=nj;
   Bjet_Multi=nb;
   Jet_Survive_Multi=nj+nb;
   if((nb+nj+nRubJ) != Jet_tot_Multi || Jet_Survive_Multi != nsurJ)
   {
     cout<<"Counting Error: "<<"Jet Multiplicity Error!"<<endl;
   }

//------------------------------------
//   Find Special Jets ( CA Algorithm )
//------------------------------------   
//   CAJet_Multi=event->CAJet_size;
//   int ncajet=0;
//   char charCAJet[10]="Jca";
//   if(CAJet_Multi>0)
//   {
//     for(int i=0;i<CAJet_Multi;i++)
//     {
//       CAJet_P_Self[ncajet].Setting(event->CAJet_PT[i],event->CAJet_Eta[i],event->CAJet_Phi[i],event->CAJet_Charge[i],event->CAJet_Mass[i],charCAJet);
//       ncajet=ncajet+1;
//     }
//   }
//   if( ncajet != CAJet_Multi )
//   {
//     cout<<"Counting Error: "<<"ncajet= "<<ncajet<<" != "<<"CAJet_Multi= "<<CAJet_Multi<<endl;
//     cout<<"Please Check the Program File Self_Analysis.cpp or your ROOT Files"<<endl;
//     cout<<"Initialization of Self_Events_Classify Failed!"<<endl;
//   }
   
   
   
//----------------------
//  Find Light Lepton e mu 
//----------------------  
   Elec_tot_Multi=event->Electron_size;
   Muon_tot_Multi=event->Muon_size;
   Lep_tot_Multi=Elec_tot_Multi+Muon_tot_Multi;
   char charlep[10]="l";
//   cout<<Elec_Multi<<" "<<Muon_Multi<<" "<<Lep_Multi<<endl;
   int ne=0;
   int nmu=0;
   int nl=0;
   int nRubL=0;
   int nRubE=0;
   int nRubM=0;
   Bool_t EleOK,MuonOK;
   if(Elec_tot_Multi>0)
   {
     for(int i=0;i<Elec_tot_Multi;i++)
     {
       EleOK = Basic_Cuts_Ele(event,i);
       if( EleOK )
       {
         Lep_P_Self[nl].Setting(event->Electron_PT[i],event->Electron_Eta[i],event->Electron_Phi[i],event->Electron_Charge[i],0.0,charlep,"e");
         Elec_P_Self[ne].Setting(event->Electron_PT[i],event->Electron_Eta[i],event->Electron_Phi[i],event->Electron_Charge[i],0.0,"e","e");    

         ne=ne+1;
         nl=nl+1;
       }
       else
       {
//         Lep_P_Rub[nRubL].Setting(event->Electron_PT[i],event->Electron_Eta[i],event->Electron_Phi[i],event->Electron_Charge[i],0.0,charlep,"e");
//         Elec_P_Rub[nRubE].Setting(event->Electron_PT[i],event->Electron_Eta[i],event->Electron_Phi[i],event->Electron_Charge[i],0.0,"e","e");
         nRubL=nRubL+1;
         nRubE=nRubE+1;
       }
     }
     if(Muon_tot_Multi>0)
     {

       for(int i=0;i<Muon_tot_Multi;i++)
       {
         MuonOK=Basic_Cuts_Muon(event,i);
         if(MuonOK)
         {
           Lep_P_Self[nl].Setting(event->Muon_PT[i],event->Muon_Eta[i],event->Muon_Phi[i],event->Muon_Charge[i],0.0,charlep,"mu");
           Muon_P_Self[nmu].Setting(event->Muon_PT[i],event->Muon_Eta[i],event->Muon_Phi[i],event->Muon_Charge[i],0.0,"mu","mu");

           nmu=nmu+1;
           nl=nl+1;
         }
         else
         {
//           Lep_P_Rub[nRubL].Setting(event->Muon_PT[i],event->Muon_Eta[i],event->Muon_Phi[i],event->Muon_Charge[i],0.0,charlep,"mu");
//           Muon_P_Rub[nRubM].Setting(event->Muon_PT[i],event->Muon_Eta[i],event->Muon_Phi[i],event->Muon_Charge[i],0.0,"mu","mu");
           nRubL=nRubL+1;
           nRubM=nRubM+1;
         }
       }
     }
     else
     {
       nmu=0;
     }
   }
   else
   {
      ne=0;
      if(Muon_tot_Multi>0)
      {
        for(int i=0;i<Muon_tot_Multi;i++)
        {
          MuonOK=Basic_Cuts_Muon(event,i);
          if(MuonOK)
          {
            Lep_P_Self[nl].Setting(event->Muon_PT[i],event->Muon_Eta[i],event->Muon_Phi[i],event->Muon_Charge[i],0.0,charlep,"mu");
            Muon_P_Self[nmu].Setting(event->Muon_PT[i],event->Muon_Eta[i],event->Muon_Phi[i],event->Muon_Charge[i],0.0,"mu","mu");

            nmu=nmu+1;
            nl=nl+1;
          }
          else
          {
//            Lep_P_Rub[nRubL].Setting(event->Muon_PT[i],event->Muon_Eta[i],event->Muon_Phi[i],event->Muon_Charge[i],0.0,charlep,"mu");
//            Muon_P_Rub[nRubM].Setting(event->Muon_PT[i],event->Muon_Eta[i],event->Muon_Phi[i],event->Muon_Charge[i],0.0,"mu","mu");
            nRubL=nRubL+1;
            nRubM=nRubM+1;
          }
        }
      }
      else
      {
        nmu=0;
        nl=0;
      }
   }
   if((ne+nRubE) != Elec_tot_Multi )
   {
     cout<<"Counting Error: ne ="<<ne<<" != "<<"Elec_Multi ="<<Elec_Multi<<endl;
   }
   if((nmu+nRubM) != Muon_tot_Multi )
   {
     cout<<"Counting Error: nmu ="<<nmu<<" != "<<"Muon_Multi ="<<Muon_Multi<<endl;
   }
   if((nl+nRubL) != Lep_tot_Multi )
   {
     cout<<"Counting Error: nl ="<<nl<<" != "<<"Lep_Multi ="<<Lep_Multi<<endl;
   }
   Lep_Multi=nl;
   Elec_Multi=ne;
   Muon_Multi=nmu;  

}

Self_Events_Classify::~Self_Events_Classify()
{
   //cout<<"Finished"<<endl;
}

















