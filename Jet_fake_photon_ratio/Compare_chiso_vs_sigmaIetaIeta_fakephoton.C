#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>


void Compare_chiso_vs_sigmaIetaIeta_fakephoton()
{
	TFile* f2 = TFile::Open("/Users/junho/Desktop/WA2jet_code/WA+Jets/WA_ploting/PKUTree/outtree/outSingleMuon_preICHEP.root");
	TTree* t2 = (TTree*) f2->Get("demo");

 
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


	Long64_t nentries = t2->GetEntries();
	Double_t ini_bin_x, fin_bin_x, ini_bin_y, fin_bin_y;
	Int_t bin_x, bin_y;
   	ini_bin_x=0.;
    fin_bin_x=0.02;
    bin_x=100;
	ini_bin_y=0.;
	fin_bin_y=20.;
	bin_y=100;

	Double_t photonMax_pt1, photonMax_pt2 ,photonMax_pt3, photonMax_pt4;
	Int_t iPhoton_Max1, iPhoton_Max2, iPhoton_Max3;
/*
	TH2F *histo1= new TH2F("histo1","photon_pt > 20, no photon ID requirement",bin_x,ini_bin_x,fin_bin_x,bin_y,ini_bin_y,fin_bin_y);
	histo1->GetXaxis()->SetTitle("Sigma_IetaIeta");
	histo1->GetYaxis()->SetTitle("Charged isolation [GeV]");
	histo1->SetStats(kFALSE);
	histo1->SetMaximum(25000);

    TH2F *histo2= new TH2F("histo2","80X medium photon ID cut",bin_x,ini_bin_x,fin_bin_x,bin_y,ini_bin_y,fin_bin_y);
    histo2->GetXaxis()->SetTitle("Sigma_IetaIeta");
    histo2->GetYaxis()->SetTitle("Charged isolation [GeV]");
	histo2->SetStats(kFALSE);
	histo2->SetMaximum(30000);

    TH2F *histo3= new TH2F("histo3","80X medium photon ID & photon_pt > 20",bin_x,ini_bin_x,fin_bin_x,bin_y,ini_bin_y,fin_bin_y);
    histo3->GetXaxis()->SetTitle("Sigma_IetaIeta");
    histo3->GetYaxis()->SetTitle("Charged isolation [GeV]");
	histo3->SetStats(kFALSE);
	histo3->SetMaximum(10000);

    TH2F *histo4= new TH2F("histo4","80X medium photon ID & photon_pt > 20 & mjj > 120",bin_x,ini_bin_x,fin_bin_x,bin_y,ini_bin_y,fin_bin_y);
    histo4->GetXaxis()->SetTitle("Sigma_IetaIeta");
    histo4->GetYaxis()->SetTitle("Charged isolation [GeV]");
	histo4->SetStats(kFALSE);
	histo4->SetMaximum(1500);
*/
//    TH2F *histo_fake = new TH2F("histo_fake","fake photon template with loose photon",bin_x,ini_bin_x,fin_bin_x,bin_y,ini_bin_y,fin_bin_y);
//    histo_fake->GetXaxis()->SetTitle("Sigma_IetaIeta");
//    histo_fake->GetYaxis()->SetTitle("Charged isolation [GeV]");
//    histo_fake->SetStats(kFALSE);
//    histo_fake->SetMaximum(7000);

/*

	for(Long64_t i=0; i<nentries; i++)
	{   
		photonMax_pt1=-10, photonMax_pt2=-10, photonMax_pt3=-10;
		iPhoton_Max1=0; iPhoton_Max2=-1, iPhoton_Max3=-1;
		t2->GetEntry(i);
		if(i%1000000==0) std::cout << "Entry num " << i << std::endl;
//		if(i>1000000) break;
	
		Int_t disc=0;
		Int_t pass=0;
	//	photonMax_pt3=-100;
		

		for (Int_t iPhoton=0;iPhoton<6;iPhoton++)
		{
//			if(photon_sieie[iPhoton] > 20 || photon_chiso[iPhoton] > 0.02 )  continue;
			if(photon_pt[iPhoton] > photonMax_pt1) 
				{
					photonMax_pt1=photon_pt[iPhoton];  iPhoton_Max1 = iPhoton;	    // c1 plot
				}
			
			if(photon_pev[iPhoton]==1 && photon_hoe[iPhoton]<0.05 && photon_chiso[iPhoton]<1.37 && photon_nhiso[iPhoton]<(1.06 + 0.014*photon_pt[iPhoton] + 0.000019*photon_pt[iPhoton]*photon_pt[iPhoton]) && photon_phoiso[iPhoton]<(0.28 + 0.0053*photon_pt[iPhoton]) && photon_sieie[iPhoton] > 0.001 && TMath::Abs(photon_eta[iPhoton])<1.4442)  //c2 plot
				{	
					iPhoton_Max2 = iPhoton;
					histo2->Fill(photon_sieie[iPhoton_Max2],photon_chiso[iPhoton_Max2],1); //without selecting highest pt photon 80X medium ID photon 
					disc=1;
					pass++;

					if(disc>0 && photon_pt[iPhoton]>photonMax_pt3) 
						{
							iPhoton_Max3 = iPhoton;
							photonMax_pt3 = photon_pt[iPhoton_Max3];
						}
				
				}
		}

		if(photonMax_pt1 > 20 && iPhoton_Max1 > -1 )  
		histo1->Fill(photon_sieie[iPhoton_Max1],photon_chiso[iPhoton_Max1],1);  //only with hight pt photon
		
//		if(iPhoton_Max2 > 0 ) 
//		histo2->Fill(photon_sieie[iPhoton_Max2],photon_chiso[iPhoton_Max2],1); // without pt photon 80X medium ID photon 

		if(photonMax_pt3 > 20 && iPhoton_Max3 > -1 )
		histo3->Fill(photon_sieie[iPhoton_Max3],photon_chiso[iPhoton_Max3],1); // with highest photon and 80X medium ID photon

		if(Mjj>120 && photonMax_pt3 > 20 && iPhoton_Max3 > -1 )
		histo4->Fill(photon_sieie[iPhoton_Max3],photon_chiso[iPhoton_Max3],1); // with highest photon and 80X medium ID photon with Mjj cut



	}
	can->cd(1); gPad->SetLogy();
	histo1->Draw("COLZ");	
	can->cd(2); gPad->SetLogy();
	histo2->Draw("COLZ");
	can->cd(3); gPad->SetLogy();
	histo3->Draw("COLZ");
	can->cd(4); gPad->SetLogy();
	histo4->Draw("COLZ");
	can->SaveAs("chiso_vs_sigmaIEtaIEta.png");
*/

   
	///////////////////////////////// fake photon template  ////////////////
	
	
	TCanvas *can2 = new TCanvas("can","canvas",1600,1600);

    TH2F *histo_fake = new TH2F("histo_fake","fake photon template with loose photon",bin_x,ini_bin_x,fin_bin_x,bin_y,ini_bin_y,fin_bin_y);
    histo_fake->GetXaxis()->SetTitle("Sigma_IetaIeta");
    histo_fake->GetYaxis()->SetTitle("Charged isolation [GeV]");
    histo_fake->SetStats(kFALSE);
    histo_fake->SetMaximum(9000);


	cout<<endl<<endl<<"next loop for fake photon template"<<endl<<endl;
	Int_t disc2, pass2;
	Int_t iPhoton12_fp;
	Double_t photonet_fp;

    for(int i=0;i<nentries;i++)
	{
		t2->GetEntry(i);
        iPhoton12_fp = 0;
        disc2 = 0;
        pass2 = 0;
		photonet_fp = -100;

		if(i%1000000==0) std::cout << "Entry num " << i << std::endl;
		for (Int_t iPhoton=0;iPhoton<6;iPhoton++)
		{
			if( photon_pev[iPhoton]==1 &&
		        photon_hoe[iPhoton]<0.05 &&
				(photon_chiso[iPhoton] < TMath::Min(0.2*photon_pt[iPhoton],5*3.32)) &&
				(photon_nhiso[iPhoton] < TMath::Min(0.2*photon_pt[iPhoton], 5*(1.92+0.014*photon_pt[iPhoton]+0.000019*photon_pt[iPhoton]*photon_pt[iPhoton])  ))  &&
				(photon_phoiso[iPhoton] < TMath::Min(0.2*photon_pt[iPhoton], 5*(0.81+0.0053*photon_pt[iPhoton] ) ) ) &&
				TMath::Abs(photon_eta[iPhoton])<1.4442 &&			
				(photon_chiso[iPhoton] > 3.32 || photon_phoiso[iPhoton] > 0.81+0.0053*photon_pt[iPhoton] || photon_nhiso[iPhoton] > 1.92 + 0.014*photon_pt[iPhoton] + 0.000019*photon_pt[iPhoton]*photon_pt[iPhoton]  ) &&
				(photon_sieie[iPhoton] > 0.001 ) 
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
		histo_fake->Fill(photon_sieie[iPhoton12_fp],photon_chiso[iPhoton12_fp],1);
	}

//	can2->cd(1);
   	gPad->SetLogy();
	histo_fake->Draw("COLZ");
	can2->->SaveAs("chiso_vs_sigmaIEtaIEta-fake_photon_template.png");

}
