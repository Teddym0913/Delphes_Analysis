//------------------------------------
//
//   Cuts.c
//
//   Defination of the Class Self_Cuts
// 
//   By Teddym at 14-03-21
//
//   version 1.5.1
//   Change the content of basic cuts
//   version 1.5.0
//   Adding Basic Cuts ( Which is different from the basic cuts in Self_Events_Classify )
//   version 1.4.0
//   Evaluate the Cuts flow in every steps of cuts ( not in main())
//   version 1.3.2  14-6-16
//   Every Cut would print the cut information once 
//   version 1.3.1  14-6-14
//   Add the data nCuts store the number of Cuts you've made in the main program
//   version 1.3.0
//   Modified by Teddy on 14-04-07
//------------------------------------

#define CUTS_cxx
#include "Cuts.h"

void Self_Cuts::CountGood()
{
//  if(Cuts_result == 1)
//  {
//    Cuts_Flow[nCuts] = Cuts_Flow[nCuts] + 1;
//  }
//  else
//  {
//    Cuts_Flow[nCuts] = Cuts_Flow[nCuts];
//  }
  Cuts_Flow[nCuts]=(Cuts_result==1)?Cuts_Flow[nCuts]+1:Cuts_Flow[nCuts];
}

void Self_Cuts::Basic_Cuts(Self_Events_Classify event)
{
  nCuts = nCuts + 1;
  if(Cuts_result == 1)
  {
    double dPhi=10.0,temp=0.0,Eta=5.0;
    if(event.Jet_Survive_Multi!=0)
    {
      for(int i=0;i<event.Jet_Survive_Multi;i++)
      {
        temp = fabs(event.Jet_Survive_P_Self[i].Phi-event.MET[1]);
//        if( temp > 3.1415926)
//        {
//          temp = 2*3.1415926 - temp;
//        }
        temp = ( temp>3.1415926 )?2*3.1415926-temp:temp;
//      cout<<temp<<endl;
//        if( temp < dPhi )
//        {
//          dPhi = temp;
//        }
        dPhi=(temp<dPhi)?temp:dPhi;

      }
    } 
//    if( event.Jet_Survive_Multi >= 4 && event.Jet_Survive_P_Self[2].PT > 40 && dPhi > 0.8 )
//    {
//      Cuts_result = Cuts_result * 1;
//    }
//    else
//    {
//      Cuts_result = 0;
//    }
    Cuts_result = ( event.Jet_Survive_Multi >= 4 && event.Jet_Survive_P_Self[2].PT > 40 && dPhi > 0.8 )?Cuts_result*1:0;
  }
  if( nEventsPass == 1 )
  {
  // print once the cuts information
    cout<<"Cut_"<<nCuts<<":Basic_Cuts"<<endl;
  }
  CountGood();
}

void Self_Cuts::Total_Jets_Multi_Cuts(Self_Events_Classify event, int Tot_J_Multi)
{
  nCuts = nCuts + 1;
// Total jets multi cuts
  if(Cuts_result == 1)
  {
    if(event.Jet_Survive_Multi < Tot_J_Multi)
    {
      Cuts_result = Cuts_result * 0;
    }
  }
  if(nEventsPass == 1)
  {
    cout<<"Cut_"<<nCuts<<":#Total_jets>="<<Tot_J_Multi<<endl;
  }
  CountGood();
 
}

void Self_Cuts::Bjets_Jets_Multi_Cuts(Self_Events_Classify event, int B_Multi, int J_Multi)
{
  nCuts = nCuts + 1;
// B-Multi Cuts & Light Jets-Multi Cuts
  if(Cuts_result == 1)
  {
   if(event.Bjet_Multi>=B_Multi && event.Jet_Multi>=J_Multi)
   {
      Cuts_result = Cuts_result * 1;
   }
   else
   {
      Cuts_result = Cuts_result * 0;
   }
  }
  if(nEventsPass == 1)
  {
    cout<<"Cut_"<<nCuts<<":#Bjets>="<<B_Multi<<"#Jets>="<<J_Multi<<endl;
  }
  CountGood();
}

void Self_Cuts::Lep_Multi_Cuts(Self_Events_Classify event, int LepMulti, int Sign, int Flavor)
{
  nCuts = nCuts + 1;
  if(Cuts_result == 1)
  {
    if(event.Lep_Multi == LepMulti)
    {
      if(LepMulti == 2)
      {
        int tempC;
        int tempF;
        tempC = event.Lep_P_Self[0].Charge * event.Lep_P_Self[1].Charge;
//        tempF = strcmp(event.Lep_P_Self[0].Label_lep,event.Lep_P_Self[1].Label_lep);
//        if( tempF == 0)
//        {
//          tempF = 1*Flavor;
//        }
//        else
//        {
//          tempF = -1*Flavor;
//        }
        tempF = (strcmp(event.Lep_P_Self[0].Label_lep,event.Lep_P_Self[1].Label_lep)==0)?1*Flavor:-1*Flavor;
//        cout<<event.Lep_P_Self[0].Label_lep<<"  "<<event.Lep_P_Self[1].Label_lep<<endl;
//        cout<<event.Lep_P_Self[0].Charge<<"  "<<event.Lep_P_Self[1].Charge<<endl;
//        cout<<tempC<<"  "<<tempF<<endl;
        if ( tempC == Sign && tempF == 1 )
        {
          Cuts_result = Cuts_result * 1;
        }
        else
        {
          if(tempC != 1 && tempC != -1)
          { cout<<tempC<<endl;}
          Cuts_result = Cuts_result * 0;
        }
      }
      else
      {
        Cuts_result = Cuts_result * 1;
      }
      
    }
    else
    {
      Cuts_result = Cuts_result * 0;
    }
  }
  if(nEventsPass == 1)
  {
    cout<<"Cut_"<<nCuts<<":#Lep=="<<LepMulti<<endl;
  }
//  cout<<"Pass:  "<<Cuts_result<<endl;
  CountGood();

}

//void Self_Cuts::CAJet_Cuts(Self_Events_Classify event, int Num, double Mass_min, double Mass_Max)
//{
//  nCuts = nCuts + 1;
//  if(Cuts_result == 1)
//  {
//    if(event.CAJet_Multi != 0)
//    {
//      int good=0;
//      for(int i=0;i<event.CAJet_Multi;i++)
//      {
//        if(event.CAJet_P_Self[i].M <= Mass_Max && event.CAJet_P_Self[i].M >= Mass_min)
//        {
//          good = good + 1;
//        }
//      }
//      if(good >= Num)
//      {
//        Cuts_result = Cuts_result * 1;
//      }
//      else
//      {
//        Cuts_result = Cuts_result * 0;
//      }
//    }
//    else
//    {
//      Cuts_result = Cuts_result * 0;
//    }
//  }
//  if(nEventsPass == 1)
//  {
//    cout<<"Cut_"<<nCuts<<":#CAjet>="<<Num<<"&&Mcajet~("<<Mass_min<<","<<Mass_Max<<")"<<endl;
//  }
//  CountGood();
//}

void Self_Cuts::Invariant_Mass_Cuts(Particles_Self P1, Particles_Self P2, double Limit_min, double Limit_max)
{
  nCuts = nCuts + 1;
  if(Cuts_result == 1)
  {
    double Mp1p2;
    Mp1p2 = Invariant_Mass_SELF(P1,P2);
    if( Mp1p2 <= Limit_max && Mp1p2 >= Limit_min)
    {
      Cuts_result = Cuts_result * 1;
    }
    else
    {
      Cuts_result = Cuts_result * 0;
    }
  }
  if(nEventsPass == 1)
  {
    cout<<"Cut_"<<nCuts<<":M_"<<P1.Label<<P2.Label<<"~("<<Limit_min<<","<<Limit_max<<")"<<endl;
  }
  CountGood();
}

void Self_Cuts::COSTHETA_Cuts(Particles_Self P1, Particles_Self P2, double Limit_min, double Limit_max)
{
  nCuts = nCuts + 1;
  if(Cuts_result == 1)
  {
    double costheta;
    costheta = COSTHETA_SELF(P1,P2);
    if( costheta >= Limit_min && costheta <= Limit_max)
    {
      Cuts_result = Cuts_result * 1;
    }
    else
    {
      Cuts_result = Cuts_result * 0;
    }
  }
  if(nEventsPass == 1)
  {
    cout<<"Cut_"<<nCuts<<":Cos_"<<P1.Label<<P2.Label<<"~("<<Limit_min<<","<<Limit_max<<")"<<endl;
  }
  CountGood();
}

void Self_Cuts::Pt_Cuts(Particles_Self P, double Limit_min, double Limit_max)
{
  nCuts = nCuts + 1;
  if(Cuts_result == 1)
  {
    if(Limit_max == 0)
    {
       if(P.PT <= Limit_min)
       {
         Cuts_result = Cuts_result * 0; 
       }
    }
    else
    {
       if(P.PT <= Limit_min || P.PT >= Limit_max)
       {
         Cuts_result = Cuts_result * 0;
       }
    }
  }
  if(nEventsPass == 1)
  {
    cout<<"Cut_"<<nCuts<<":Pt_"<<P.Label<<"~("<<Limit_min<<","<<Limit_max<<")"<<endl;
  }
  CountGood();
}

void Self_Cuts::MET_Cuts(Self_Events_Classify event, double Limit)
{
  nCuts = nCuts + 1;
  if(Cuts_result == 1)
  {
    if(event.MET[0] <= Limit)
    {
      Cuts_result = Cuts_result * 0;
    }
  }
  if(nEventsPass == 1)
  {
  cout<<"Cut_"<<nCuts<<":MET>="<<Limit<<endl;
  }
  CountGood();
}

void Self_Cuts::Meff_Cuts(Self_Events_Classify event, double Limit)
{
  nCuts = nCuts + 1;
  if(Cuts_result == 1)
  {
    double Meff = Meff_SELF(event);
    if(Meff <= Limit)
    {
      Cuts_result = Cuts_result * 0;
    }
  }
  if(nEventsPass == 1)
  {
    cout<<"Cut_"<<nCuts<<":Meff>="<<Limit<<endl;
  }
  CountGood();
}

void Self_Cuts::HT_Cuts(Self_Events_Classify event, double Limit)
{
  nCuts = nCuts + 1;
  if(Cuts_result == 1)
  {
    double HT = HT_SELF(event);
    if(HT < Limit)
    {
      Cuts_result = Cuts_result * 0;
    }
  }
  if(nEventsPass == 1)
  {
    cout<<"Cut_"<<nCuts<<":HT>="<<Limit<<endl;
  }
  CountGood();
}

void Self_Cuts::MET_vs_HT_Cuts(Self_Events_Classify event, double Limit)
{
  nCuts = nCuts + 1;
  if(Cuts_result == 1)
  {
    double ALPHA;
    ALPHA = MET_vs_HT_SELF(event);
    if(ALPHA < Limit )
    {
      Cuts_result = Cuts_result * 0;
    }
  }
  if(nEventsPass == 1)
  {
    cout<<"Cut_"<<nCuts<<":MET/sqrt(HT)>="<<Limit<<endl;
  }
  CountGood();
}

void Self_Cuts::TRANS_MASS_Cuts(Self_Events_Classify event, double MT)
{
  nCuts = nCuts + 1;
// MET cuts  & Lep_Multi Cuts-----------------
  if(Cuts_result == 1)
  {
   if(event.Lep_Multi==1)
   {
      double TransM = TRANS_MASS(event.Lep_P_Self[0], event.MET);
      if(TransM >= MT)
      {
         Cuts_result = Cuts_result * 1;
      }
      else
      {
         Cuts_result = Cuts_result * 0;
      }
   }
   else
   {
       Cuts_result = Cuts_result * 0;
   }
  }
  if(nEventsPass == 1)
  {
    cout<<"Cut_"<<nCuts<<":MT>="<<MT<<endl;
  }
  CountGood();
}

//void Self_Cuts::Bjets_Higgs_Mass_Cuts(Self_Events_Classify event)
//{
//  nCuts = nCuts + 1;
//// Two B-jets Invariant mass would be within some range of 125GeV
//   if(Cuts_result == 1)
//   {
//        int NBpair=event.Bjet_Multi*(event.Bjet_Multi-1)/2;
//        int k=0;
//        HiggsMassClose=150.0;
//        double *InvMBB = new double[NBpair];
//        for(int i=0;i<event.Bjet_Multi-1;i++)
//        {
//           for(int j=i+1;j<event.Bjet_Multi;j++)
//           {
//             k=i+j*(j-1)/2;
//             InvMBB[k]=Invariant_Mass_SELF(event.Bjet_P_Self[i],event.Bjet_P_Self[j]);
//             if(InvMBB[k]<=150 && InvMBB[k]>=100 )
//             {
//                Cuts_result = Cuts_result * 0;
//                if( fabs(InvMBB[k]-125) < fabs(HiggsMassClose-125) )
//                { 
//                    HiggsMassClose = InvMBB[k];
//                    B_higgs[0]=i;
//                    B_higgs[1]=j;
//                }
//             }
//             else
//             {
//                 Cuts_result = Cuts_result * 1;
//             }
//           }
//         }
//        Cuts_result = (Cuts_result+1)%2;
//        delete [] InvMBB;
//    }
//}
//void Self_Cuts::TRANS_TOP_MASS_Cuts(Self_Events_Classify event)
//{
//  nCuts = nCuts + 1;
//// One b One lep & MET transverse Mass should not cut off at Mtop
//   if( Cuts_result == 1 )
//   {
//      double TranTop;
//      Particles_Self BplusL;
//      for(int i=0;i<event.Bjet_Multi;i++)
//      {
//        if(i!=B_higgs[0] && i!=B_higgs[1])
//        {           
//           BplusL = event.Bjet_P_Self[i] + event.Lep_P_Self[0];
//           TranTop = TRANS_MASS(BplusL,event.MET);
//           if(TranTop <= 200)
//           { Cuts_result = Cuts_result * 0; }
//           else
//           { Cuts_result = Cuts_result; }
//        }
//      }   
//   }

//}

//void Self_Cuts::Jets_W_Mass_Cuts(Self_Events_Classify event)
//{
//  nCuts = nCuts + 1;
//// Two Jets should come from One W-boson
//  if ( Cuts_result == 1 )
//  {
////      double M_jj[6];
////      M_jj[0]=Invariant_Mass_SELF(event.Jet_P_Self[0],event.Jet_P_Self[1]);
////      M_jj[1]=Invariant_Mass_SELF(event.Jet_P_Self[0],event.Jet_P_Self[2]);
////      M_jj[2]=Invariant_Mass_SELF(event.Jet_P_Self[0],event.Jet_P_Self[3]);
////      M_jj[3]=Invariant_Mass_SELF(event.Jet_P_Self[1],event.Jet_P_Self[2]);
////      M_jj[4]=Invariant_Mass_SELF(event.Jet_P_Self[1],event.Jet_P_Self[3]);
////      M_jj[5]=Invariant_Mass_SELF(event.Jet_P_Self[2],event.Jet_P_Self[3]);
////      if((M_jj[0]<110 && M_jj[0] > 50 && M_jj[5]<110 && M_jj[5]>50) || (M_jj[1]<110 && M_jj[1] > 50 && M_jj[4]<110 && M_jj[4]>50) || (M_jj[2]<110 && M_jj[2] > 50 && M_jj[3]<110 && M_jj[3]>50))
////      {
////         Cuts_result = Cuts_result * 1;
////      }
////      else
////      {
////         Cuts_result = Cuts_result * 0;
////      }
//      int NJpair=event.Jet_Multi*(event.Jet_Multi-1)/2;
//      int k=0;
//      double InvMjj[20][20];
//      int Good1[30];
//      int Good2[30];
//      int temp=1; 
//      for(int i=0;i<event.Jet_Multi-1;i++)
//      {
//        for(int j=i+1;j<event.Jet_Multi;j++)
//        {
//          InvMjj[i][j]=Invariant_Mass_SELF(event.Jet_P_Self[i],event.Jet_P_Self[j]);
//          if(InvMjj[i][j]>55 && InvMjj[i][i]<105)
//          {
//            Good1[k]=i;
//            Good2[k]=j;
//            k=k+1;
//          }
//        }
//      }
//      for(int l=0;l<k-1;l++)
//      {
//        for(int m=l+1;m<k;m++)
//        {
//          if((Good1[l] != Good1[m]) && (Good2[l] != Good2[m]))
//          {
//            temp = temp * 0;
//          }
//          else
//          {
//            temp = temp * 1;
//          }
//        }
//      }
//      Cuts_result = (temp+1)%2;

////      WMassClose=105;
////      double *InvMJJ = new double[NJpair];
////      for(int i=0;i<event.Jet_Multi-1;i++)
////      {
////         for(int j=i+1;j<event.Jet_Multi;j++)
////         {
////           k=i+j*(j-1)/2;
////           InvMJJ[k]=Invariant_Mass_SELF(event.Jet_P_Self[i],event.Jet_P_Self[j]);
////           if( InvMJJ[k] <= 105 && InvMJJ[k] >= 55 )
////           {
////              Cuts_result = Cuts_result * 0;
////              if( fabs(InvMJJ[k]-80) < fabs(WMassClose-80) )
////              {
////                  WMassClose = InvMJJ[k];
////                  J_W[0]=i;
////                  J_W[1]=j;
////               }
////           }
////           else
////           {
////                Cuts_result = Cuts_result * 1;
////           }
////        }
////      }
////      Cuts_result = (Cuts_result+1)%2;
////      delete [] InvMJJ;
//   }
//}
//void Self_Cuts::Top_Veto(Self_Events_Classify event)
//{
//  nCuts = nCuts + 1;
//// Top-quark Veto
//  if(Cuts_result == 1)
//  {
//     double InvTop;
//     for(int i=0;i<event.Bjet_Multi;i++)
//     {
//        if( i!= B_higgs[0] && i!= B_higgs[1] )
//        {
//          InvTop = Invariant_Mass_SELF(event.Jet_P_Self[J_W[0]],event.Jet_P_Self[J_W[1]],event.Bjet_P_Self[i]);
//          if(InvTop <= 200 && InvTop >= 150)
//          {
//             Cuts_result = Cuts_result * 0;
//          }
//          else
//          {
//             Cuts_result = Cuts_result * 1;
//          }
//        }
//      }
//   }
//}
//void Self_Cuts::Top_Veto_2(Self_Events_Classify event)
//{
//  nCuts = nCuts + 1;
//// Another Top Veto Algorithm
//  if(Cuts_result == 1)
//  {
//      int NJpair=event.Jet_Multi*(event.Jet_Multi-1)/2;
//      int k=0;
//      WMassClose=105;
//      double *InvMJJ = new double[NJpair];
//      for(int i=0;i<event.Jet_Multi-1;i++)
//      {
//         for(int j=i+1;j<event.Jet_Multi;j++)
//         {
//           k=i+j*(j-1)/2;
//           InvMJJ[k]=Invariant_Mass_SELF(event.Jet_P_Self[i],event.Jet_P_Self[j]);
//           if( InvMJJ[k] <= 105 && InvMJJ[k] >= 55 )
//           {
//              Cuts_result = Cuts_result * 0;
//              if( fabs(InvMJJ[k]-80) < fabs(WMassClose-80) )
//              {
//                  WMassClose = InvMJJ[k];
//                  J_W[0]=i;
//                  J_W[1]=j;
//               }
//           }
//           else
//           {
//                Cuts_result = Cuts_result * 1;
//           }
//        }
//      }
//      Cuts_result = (Cuts_result+1)%2;
//      if(Cuts_result == 1)
//      {
//        int NBpair=event.Bjet_Multi*(event.Bjet_Multi-1)/2;
//        int k=0;
//        HiggsMassClose=150.0;
//        double *InvMBB = new double[NBpair];
//        for(int i=0;i<event.Bjet_Multi-1;i++)
//        {
//           for(int j=i+1;j<event.Bjet_Multi;j++)
//           {
//             k=i+j*(j-1)/2;
//             InvMBB[k]=Invariant_Mass_SELF(event.Bjet_P_Self[i],event.Bjet_P_Self[j]);
//             if(InvMBB[k]<=150 && InvMBB[k]>=100 )
//             {
//                Cuts_result = Cuts_result * 0;
//                if( fabs(InvMBB[k]-125) < fabs(HiggsMassClose-125) )
//                { 
//                    HiggsMassClose = InvMBB[k];
//                    B_higgs[0]=i;
//                    B_higgs[1]=j;
//                }
//             }
//             else
//             {
//                 B_higgs[0]=100;
//                 B_higgs[1]=200;
//                 Cuts_result = Cuts_result * 1;
//             }
//           }
//         }
//        Cuts_result = (Cuts_result+1)%2;
//        delete [] InvMBB;
//        if(Cuts_result == 1)
//        {
//        double InvTop;
//        for(int i=0;i<event.Bjet_Multi;i++)
//        {
//          if( i!= B_higgs[0] && i!= B_higgs[1] )
//          {
//            InvTop = Invariant_Mass_SELF(event.Jet_P_Self[J_W[0]],event.Jet_P_Self[J_W[1]],event.Bjet_P_Self[i]);
//            if(InvTop <= 200 && InvTop >= 150)
//            {
//               Cuts_result = Cuts_result * 0;
//            }
//            else
//            {
//               Cuts_result = Cuts_result * 1;
//            }
//          }
//      
//        }
//        }
//      delete [] InvMJJ;
//      }
//      else
//      {
//        Cuts_result = 1;
//      }    
//  }
//  else
//  {
//    Cuts_result = 0;
//  } 
//}





















