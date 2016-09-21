#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooGaussModel.h"
#include "RooAddModel.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooPolynomial.h"
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooProdPdf.h"
#include "TCanvas.h"
#include "TLorentzVector.h"
#include "TAxis.h"
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"
#include "TLegend.h"
#include "RooPlot.h"

using namespace RooFit ;
//root -b -q fake_ratio.C\(20,30\)
void fake_ratio(float lowpt,float highpt){
 

////////////////////////////
//updated with AN2016-051-v8 ZGamma
///////////////////////////


    // Signal sample
//    TFile* f1 = TFile::Open("../../WA_ploting/PKUTree/outtree/outsignal_160503.root");
    // Data sample
//    TFile* f2 = TFile::Open("../../WA_ploting/PKUTree/outtree/outSMU.root");
	TFile* f2 = TFile::Open("/Users/junho/Desktop/WA2jet_code/WA+Jets/WA_ploting/PKUTree/outtree/outSingleMuon_preICHEP.root");

//    TTree* t1 = (TTree*) f1->Get("demo");
    TTree* t2 = (TTree*) f2->Get("demo");
/*
    t1->SetBranchStatus("photon_pev",1);
    t1->SetBranchStatus("photon_hoe",1);
    t1->SetBranchStatus("photon_chiso",1);
    t1->SetBranchStatus("photon_nhiso",1);
    t1->SetBranchStatus("photon_phoiso",1);
    t1->SetBranchStatus("photon_sieie",1);
    t1->SetBranchStatus("photon_pt",1);
    t1->SetBranchStatus("photon_eta",1);
    t1->SetBranchStatus("photon_phi",1);
    t1->SetBranchStatus("photon_isprompt",1);
    t1->SetBranchStatus("photon_drla",1);
    t1->SetBranchStatus("lumiWeight",1);
    t1->SetBranchStatus("pileupWeight",1);
    t1->SetBranchStatus("scalef",1);
*/
     t2->SetBranchStatus("photon_pev",1);
     t2->SetBranchStatus("photon_hoe",1);
     t2->SetBranchStatus("photon_chiso",1);
     t2->SetBranchStatus("photon_nhiso",1);
     t2->SetBranchStatus("photon_phoiso",1);
     t2->SetBranchStatus("photon_sieie",1);
     t2->SetBranchStatus("photon_pt",1);
     t2->SetBranchStatus("photon_eta",1);
     t2->SetBranchStatus("photon_phi",1);
     t2->SetBranchStatus("photon_e",1);
     t2->SetBranchStatus("photon_drla",1);
     t2->SetBranchStatus("lep",1);
     t2->SetBranchStatus("HLT_Mu1",1);
     t2->SetBranchStatus("ptlep1",1);
     t2->SetBranchStatus("etalep1",1);
     t2->SetBranchStatus("nlooseeles",1);
     t2->SetBranchStatus("nloosemus",1);
     t2->SetBranchStatus("MET_et",1);
     t2->SetBranchStatus("mtVlepJECnew",1);
t2->SetBranchStatus("Mjj",1);


     Double_t photon_eta[50],photon_pt[50],photon_phi[50],photon_e[50];
     Char_t   photon_pev[50];
     Double_t photon_hoe[50],photon_chiso[50],photon_nhiso[50],photon_phoiso[50],photon_sieie[50],photon_drla[50],massVlep;
     Int_t    photon_isprompt[50];
     Double_t photon_drla[50],massVlep,yVlep,phiVlep,ptVlep,mlla;
     Int_t    lep,HLT_Mu1,nlooseeles,nloosemus;
     Double_t ptlep,etalep,MET_et;
     Double_t Mva;
     Double_t mtVlepJECnew;
Double_t Mjj;


     t2->SetBranchAddress("photon_eta",photon_eta);
     t2->SetBranchAddress("photon_pt",photon_pt);
     t2->SetBranchAddress("photon_e",photon_e);
     t2->SetBranchAddress("photon_phi",photon_phi);
     t2->SetBranchAddress("photon_pev",photon_pev);
     t2->SetBranchAddress("photon_hoe",photon_hoe);
     t2->SetBranchAddress("photon_chiso",photon_chiso);
     t2->SetBranchAddress("photon_nhiso",photon_nhiso);
     t2->SetBranchAddress("photon_phoiso",photon_phoiso);
     t2->SetBranchAddress("photon_sieie",photon_sieie);
     t2->SetBranchAddress("photon_isprompt",photon_isprompt);
     t2->SetBranchAddress("photon_drla",photon_drla);
     t2->SetBranchAddress("lep",&lep);
     t2->SetBranchAddress("HLT_Mu1",&HLT_Mu1);
     t2->SetBranchAddress("nloosemus",&nloosemus);
     t2->SetBranchAddress("nlooseeles",&nlooseeles);
     t2->SetBranchAddress("ptlep1",&ptlep);
     t2->SetBranchAddress("etalep1",&etalep);
     t2->SetBranchAddress("MET_et",&MET_et);
     t2->SetBranchAddress("Mva",&Mva);
     t2->SetBranchAddress("mtVlepJECnew",&mtVlepJECnew);
t2->SetBranchAddress("Mjj",&Mjj);

     Int_t nBins = 7;
     Double_t bins[8] = {0.0,0.006,0.008,0.009,0.0102,0.0125,0.015,0.02};


		//>>>>>>>>>>>>>>>>>>>>>fake photon template>>>>>>>>>>>>>>>>>>>>

	 Float_t Sieie_fkp; // pointer to the leading photon
     Long64_t nentries_fkp = t2->GetEntries();
     TFile* newfile2 = new TFile(Form("newtree2_%0.f_%0.f.root",lowpt,highpt),"recreate");
     TTree* temp_fkp = new TTree("temp_fkp","temp_fkp");
     temp_fkp->Branch("sieie",&Sieie_fkp);
     TH1F* hfkp = new TH1F("hfkp","hfkp",nBins,bins);
     TH1F* hfkp_sieie_sb = new TH1F("hfkp_sieie_sb","hfkp_sieie_sb",nBins,bins);
	 Int_t numevents_fkp = 0;
 

    for(int i=0;i<nentries_fkp;i++)
    //          for(int i=0;i<10;i++)
     {								
         t2->GetEntry(i);
         Int_t iPhoton12_fp = 0;
         Int_t disc2 = 0;
         Int_t pass2 = 0;
         Double_t photonet_fp = -100;
         if(i%1000000==0) std::cout << "Entry num " << i << std::endl;

//if(Mjj<400) continue;

         for (Int_t iPhoton=0;iPhoton<6;iPhoton++){
             if(photon_pev[iPhoton]==1 &&
                photon_hoe[iPhoton]<0.05 &&
//                (photon_chiso[iPhoton] < 1.37) && // (photon_chiso[iPhoton] < 0.2*photon_pt[iPhoton]) &&
//				((photon_chiso[iPhoton] < 13.0) && (photon_chiso[iPhoton] > 4.0)  )
			(photon_chiso[iPhoton] < TMath::Min(0.2*photon_pt[iPhoton],5*3.32)) &&
//				(photon_nhiso[iPhoton]< (1.06 + 0.014*photon_pt[iPhoton] + 0.000019*photon_pt[iPhoton]*photon_pt[iPhoton])) &&// (photon_nhiso[iPhoton] <  2.57 + exp(100*0.044*photon_pt[iPhoton]+0.5809 )) &&

			(photon_nhiso[iPhoton] < TMath::Min(0.2*photon_pt[iPhoton], 5*(1.92+0.014*photon_pt[iPhoton]+0.000019*photon_pt[iPhoton]*photon_pt[iPhoton])  ))  &&

//(photon_phoiso[iPhoton] < (0.28 + 0.0053*photon_pt[iPhoton])) &&// 5*(15.0 + 0.0043*photon_pt[iPhoton])) && (photon_phoiso[iPhoton] < 0.2*photon_pt[iPhoton]) &&
			(photon_phoiso[iPhoton] < TMath::Min(0.2*photon_pt[iPhoton], 5*(0.81+0.0053*photon_pt[iPhoton] ) ) ) &&

 			TMath::Abs(photon_eta[iPhoton])<1.4442 &&
			
			(photon_chiso[iPhoton] > 3.32 || photon_phoiso[iPhoton] > 0.81+0.0053*photon_pt[iPhoton] || photon_nhiso[iPhoton] > 1.92 + 0.014*photon_pt[iPhoton] + 0.000019*photon_pt[iPhoton]*photon_pt[iPhoton]  ) &&

			(photon_sieie[iPhoton] > 0.001 ) &&
//				(photon_chiso[iPhoton] > 7.0  ||  photon_nhiso[iPhoton] > 5*(1.06 + 0.014*photon_pt[iPhoton] + 0.000019*photon_pt[iPhoton]*photon_pt[iPhoton])  ||   photon_phoiso[iPhoton] > 5* (0.28 + 0.0053*photon_pt[iPhoton]) &&//(15.0 + 0.0043*photon_pt[iPhoton]))	&&

                photon_pt[iPhoton]>lowpt && photon_pt[iPhoton]<highpt)
			 {
                 disc2=1;
                 pass2++;
             }
             if (disc2>0 && photon_pt[iPhoton]>photonet_fp) {
                 iPhoton12_fp= iPhoton;
                 photonet_fp = photon_pt[iPhoton12_fp];
             }
         }
 
         if(pass2>0 && photon_drla[iPhoton12_fp]>0.7){
             Sieie_fkp = photon_sieie[iPhoton12_fp];
             temp_fkp->Fill();
             hfkp->Fill(Sieie_fkp);
			
			 if(Sieie_fkp > 0.0100) hfkp_sieie_sb->Fill(Sieie_fkp);
 
         }
     }
     newfile2->cd();
     hfkp->Write();
	 hfkp_sieie_sb->Write();
     temp_fkp->Write();
     std::cout<<"numevents_fkp = "<<hfkp->Integral()<<std::endl;
	 std::cout<<"numevents_fkp_sideband = "<<hfkp_sieie_sb->Integral()<<std::endl;
     std::cout<<"temp_fkp OK"<<std::endl;
 

 
     //>>>>>>>>>>>>>>>>>>>>>true photon>>>>>>>>>>>>>>>>>>>>
 
     Float_t Sieie_num; // pointer to the leading photon
     Long64_t nentries_num = t2->GetEntries();
     TFile* newfile3 = new TFile(Form("newtree3_%0.f_%0.f.root",lowpt,highpt),"recreate");
     TTree* temp_num = new TTree("temp_num","temp_num");
     temp_num->Branch("sieie",&Sieie_num);
//     TH1F* hnum = new TH1F("hnum","hnum",nBins,bins);
	 TH1F* hnum = new TH1F("hnum","hnum",100,0,0.04);
	 TH1F* hnum_sieie_sb = new TH1F("hnum_sieie_sb","hnum_sieie_sb",nBins,bins);
	 TH1F* hnum_sieie_signal = new TH1F("hnum_sieie_signal","hnum_sieie_signal",nBins,bins);	 
 
     for(int i=0;i<nentries_num;i++)
    //        for(int i=0;i<10;i++)
     {
         t2->GetEntry(i);
         Int_t iPhoton12 = 0;
         Int_t pass3 = 0;
         Int_t disc3 = 0;
         Sieie_num = -1;
         Double_t photonet_data = -100;
 
         if(i%1000000==0) std::cout << "Entry num " << i << std::endl;

//if(Mjj<400) continue;

         for(Int_t iPhoton=0;iPhoton<6;iPhoton++){
             if(photon_pev[iPhoton]==1 &&
                photon_hoe[iPhoton]<0.05 &&
                photon_chiso[iPhoton]<1.37 &&
                photon_nhiso[iPhoton]<(1.06 + 0.014*photon_pt[iPhoton] + 0.000019*photon_pt[iPhoton]*photon_pt[iPhoton]) &&
                photon_phoiso[iPhoton]<(0.28 + 0.0053*photon_pt[iPhoton]) && photon_sieie[iPhoton] > 0.001 &&
                TMath::Abs(photon_eta[iPhoton])<1.4442 && photon_pt[iPhoton]>lowpt && photon_pt[iPhoton]<highpt)    
			 {
                 disc3=1;
                 pass3++;
             }
             if (disc3>0 && photon_pt[iPhoton]>photonet_data) {
                 iPhoton12= iPhoton;
                 photonet_data = photon_pt[iPhoton12];
             }
         }
 
 
         if(pass3>0 && photon_drla[iPhoton12]>0.7)
/*			 && lep==13  &&
             HLT_Mu1>0 &&
          //  ptlep>30. &&
            ptlep>35. &&
             fabs(etalep)<2.1 &&
             nlooseeles==0 &&
             nloosemus<2 &&
          //  MET_et>40)
             mtVlepJECnew>70)
*/	
		 {
             Sieie_num = photon_sieie[iPhoton12];
             temp_num->Fill();
             hnum->Fill(Sieie_num);
			 if(Sieie_num>0.0100)	hnum_sieie_sb->Fill(Sieie_num);
			 else hnum_sieie_signal->Fill(Sieie_num);
         }
     }
         newfile3->cd();
         hnum->Write();
		 hnum_sieie_sb->Write();
		 hnum_sieie_signal->Write();
     temp_num->Write();
     std::cout<<"numevents_num = "<<hnum->GetSumOfWeights()<<std::endl;		std::cout<<"numevents_num = "<<hnum->Integral()<<std::endl;
	 std::cout<<"numevents_num_sideband = "<<hnum_sieie_sb->GetSumOfWeights()<<std::endl; std::cout<<"numevents_num_sideband = "<<hnum_sieie_sb->Integral()<<std::endl;
     std::cout<<"temp_num OK"<<std::endl;







    //>>>>>>>>>>>>>>>>>> obtain fake photon fraction>>>>>>>>>>

	Double_t scale_sb;
	scale_sb = hnum_sieie_sb->Integral()/hfkp_sieie_sb->Integral();

cout<<endl<<endl<<"scale of sideband = "<<scale_sb<<endl<<endl;
      TFile* newfile4 = new TFile(Form("newtree4_%0.f_%0.f.root",lowpt,highpt),"recreate");
//      TH1F* hfkp_scale = new TH1F("hfkp_scale","hfkp_scale",nBins,bins);
	  TH1F* hfkp_scale = new TH1F("hfkp_scale","hfkp_scale",100,0,0.04);
      TH1F* hfkp_scale_signal = new TH1F("hfkp_scale_signal","hfkp_scale_signal",nBins,bins);
	  numevents_fkp = 0;

     for(int i=0;i<nentries_fkp;i++)
     //          for(int i=0;i<10;i++)
      {
          t2->GetEntry(i);
           iPhoton12_fp = 0;
           disc2 = 0;
           pass2 = 0;
        photonet_fp = -100;
          if(i%1000000==0) std::cout << "Entry num " << i << std::endl;

//if(Mjj<400) continue;

          for (Int_t iPhoton=0;iPhoton<6;iPhoton++){
              if(  photon_pev[iPhoton]==1 &&
 				   photon_hoe[iPhoton]<0.05 &&
				   (photon_chiso[iPhoton] < TMath::Min(0.2*photon_pt[iPhoton],5*3.32)) &&
				   (photon_nhiso[iPhoton] < TMath::Min(0.2*photon_pt[iPhoton], 5*(1.92+0.014*photon_pt[iPhoton]+0.000019*photon_pt[iPhoton]*photon_pt[iPhoton])  ))  &&
				   (photon_phoiso[iPhoton] < TMath::Min(0.2*photon_pt[iPhoton], 5*(0.81+0.0053*photon_pt[iPhoton] ) ) ) &&
				   TMath::Abs(photon_eta[iPhoton])<1.4442 &&
				   (photon_chiso[iPhoton] > 3.32 || photon_phoiso[iPhoton] > 0.81+0.0053*photon_pt[iPhoton] || photon_nhiso[iPhoton] > 1.92 + 0.014*photon_pt[iPhoton] + 0.000019*photon_pt[iPhoton]*photon_pt[iPhoton]  ) &&
				   (photon_sieie[iPhoton] > 0.001 ) &&
                   photon_pt[iPhoton]>lowpt && photon_pt[iPhoton]<highpt
				)
              {
                  disc2=1;
                  pass2++;
              }
              if (disc2>0 && photon_pt[iPhoton]>photonet_fp) {
                  iPhoton12_fp= iPhoton;
                  photonet_fp = photon_pt[iPhoton12_fp];
              }
          }
 
          if(pass2>0 && photon_drla[iPhoton12_fp]>0.7){
              Sieie_fkp = photon_sieie[iPhoton12_fp];
              hfkp_scale->Fill(Sieie_fkp,scale_sb);
 			  
			  if(Sieie_fkp<=0.0100) hfkp_scale_signal->Fill(Sieie_fkp,scale_sb);
 
          }
      }
      newfile4->cd();
      hfkp_scale->Write();
	  hfkp_scale_signal->Write();
	  std::cout<<"numevents_num_total = "<<hfkp_scale->Integral() <<std::endl;
	  std::cout<<"numevents_num_signal = "<<hfkp_scale_signal->Integral() <<std::endl;

	
	Double_t fake_photon_ratio = (hfkp_scale_signal->Integral()) / (hnum_sieie_signal->Integral());
	cout<<"fake photon ratio : "<<fake_photon_ratio<<endl;

//	Float_t Sieie_combine;	
//	TFile *ff = new TFile(Form("together_%0.f_%0.f.root",lowpt,highpt),"recreate");
//	TH1F *hh = new TH1F("hh","hh",nBins,bins);
	TCanvas *c01 = new TCanvas("c01","",700,500);

	hnum->SetTitle("ratio method measurement of jet fake rate");
	hnum->GetXaxis()->SetTitle("Sieie");
	hnum->GetXaxis()->CenterTitle();
	hnum->GetYaxis()->SetTitle("event num");
	hnum->GetYaxis()->CenterTitle();	

	hnum->SetStats(0);
	hnum->SetLineColor(kBlue);
  	hnum->Draw();
	hfkp_scale->SetLineColor(kRed);
	hfkp_scale->Draw("same");	


    TLegend *l1 = new TLegend(0.54, 0.7, 0.88, 0.88);
	l1->SetMargin(0.4);
    l1->SetBorderSize(1);
    l1->SetFillColor(0);
    l1->AddEntry(hnum,"true photon","f");
    l1->AddEntry(hfkp_scale,"fake photon","f");
    l1->Draw();
	
//	c01->SaveAs("ratio_%0.f_%0.f.eps",lowpt,highpt);
//	c01->SaveAs("ratio_%0.f_%0.f.png",lowpt,highpt);
	c01->SaveAs("ratio_50_400_Mjj_signal.png");

	hnum->Write();	

	//>>>>>>>>>>>>>>>>>>>> output txt file>>>>>>>>>>>>>>>>>
	
	ofstream myfile(TString("rate_")+Form("Mjj_signal_photon_pt%0.f_%0.f.txt",lowpt,highpt),ios::out);
	myfile <<"Fake Rate : "<<fake_photon_ratio<<endl;
	



}
