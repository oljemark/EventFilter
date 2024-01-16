{
 TFile f("results_LTRB-r585-14607k-thxr1d-coarseBins.root");
 auto tx=f.Get<TH2F>("theta_x_star_left_right;1");
 TF1 ga("ga","gaus(0)+gaus(3)",-600.,600.);

 ga.SetParLimits(0,1000.,10000.);
 ga.SetParLimits(1,85.,115.);
 ga.SetParLimits(2,4.5,25.);
 ga.SetParLimits(3,1000.,1000000.);
 ga.SetParLimits(4,115.,135.);
 ga.SetParLimits(5,4.5,25.);
 TObjArray bkPk;
 gStyle->SetOptFit(1);
 tx->FitSlicesY(&ga,200,270,0,"QNR G2",&bkPk);


 TCanvas MyC;
 MyC.Divide(2,2);
 MyC.cd(1);
 tx->GetXaxis()->SetRangeUser(50.,250.);
 tx->GetYaxis()->SetRangeUser(-200.,300.);
 tx->Draw("colz");
 MyC.cd(2);
 ((TH1D*) bkPk[0])->GetXaxis()->GetTitle();
 ((TH1D*) bkPk[0])->GetYaxis()->GetTitle();
 ((TH1D*) bkPk[0])->GetYaxis()->SetTitle("Constant 1");
 ((TH1D*) bkPk[0])->GetXaxis()->SetTitle("#theta_{x,left} (#mu rad)");
 ((TH1D*) bkPk[0])->GetXaxis()->SetRangeUser(50.,250.);
 ((TH1D*) bkPk[0])->Draw();
 ((TH1D*) bkPk[1])->GetYaxis()->SetTitle("Mean 1");
 ((TH1D*) bkPk[1])->GetXaxis()->SetTitle("#theta_{x,left} (#mu rad)");
 ((TH1D*) bkPk[1])->GetXaxis()->SetRangeUser(50.,250.);
 ((TH1D*) bkPk[1])->GetYaxis()->SetRangeUser(90.,140.);
 MyC.cd(3);
 ((TH1D*) bkPk[1])->Fit("pol0","","",125.,200.);
 ((TH1D*) bkPk[2])->GetYaxis()->SetTitle("Sigma 1");
 ((TH1D*) bkPk[2])->GetXaxis()->SetTitle("#theta_{x,left} (#mu rad)");
 ((TH1D*) bkPk[2])->GetXaxis()->SetRangeUser(50.,250.);
 MyC.cd(4);
 ((TH1D*) bkPk[2])->Draw();
 MyC.Print("r369585v2-LTRB-bkgPeak1.pdf");
 MyC.Print("r369585v2-LTRB-bkgPeak1.C");
 MyC.Print("r369585v2-LTRB-bkgPeak1.png");
 MyC.Print("r369585v2-LTRB-bkgPeak1.eps");
 ((TH1D*) bkPk[3])->GetYaxis()->SetTitle("Constant 2");
 ((TH1D*) bkPk[3])->GetXaxis()->SetTitle("#theta_{x,left} (#mu rad)");
 ((TH1D*) bkPk[3])->GetXaxis()->SetRangeUser(50.,250.);
 ((TH1D*) bkPk[4])->GetYaxis()->SetTitle("Mean 2");
 ((TH1D*) bkPk[4])->GetXaxis()->SetTitle("#theta_{x,left} (#mu rad)");
 ((TH1D*) bkPk[4])->GetXaxis()->SetRangeUser(50.,250.);
 ((TH1D*) bkPk[4])->GetYaxis()->SetRangeUser(90.,140.);
 ((TH1D*) bkPk[5])->GetXaxis()->SetTitle("#theta_{x,left} (#mu rad)");
 ((TH1D*) bkPk[5])->GetYaxis()->SetTitle("Sigma 2");
 ((TH1D*) bkPk[5])->GetXaxis()->SetRangeUser(50.,250.);
 MyC.cd(2);
 ((TH1D*) bkPk[3])->Draw();
 MyC.cd(3);
 ((TH1D*) bkPk[4])->Fit("pol0","","",100.,200.);
 MyC.cd(4);
 ((TH1D*) bkPk[5])->Draw();
 MyC.Print("r369585v2-LTRB-bkgPeak2.png");
 MyC.Print("r369585v2-LTRB-bkgPeak2.pdf");
 MyC.Print("r369585v2-LTRB-bkgPeak2.eps");
 MyC.Print("r369585v2-LTRB-bkgPeak2.C");
 MyC.Clear();
 ((TH1D*) bkPk[6])->GetXaxis()->SetTitle("#theta_{x,left} (#mu rad)");
 ((TH1D*) bkPk[6])->GetYaxis()->SetTitle("Double Gaussian #chi^{2}");
 ((TH1D*) bkPk[6])->GetXaxis()->SetRangeUser(50.,250.);
 gPad->SetLogy();
 ((TH1D*) bkPk[6])->Draw();
 MyC.Print("r369585v2-LTRB-doubleFitChi2.png");
 MyC.Print("r369585v2-LTRB-doubleFitChi2.pdf");
 MyC.Print("r369585v2-LTRB-doubleFitChi2.C");
 MyC.Print("r369585v2-LTRB-doubleFitChi2.eps");
}
