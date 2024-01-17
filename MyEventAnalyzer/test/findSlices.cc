{
 TFile f("results_LBRT.root");
 auto xy1=f.Get<TH2F>("x_right_near_y_right_near_band1;1");
 auto xy2=f.Get<TH2F>("x_right_near_y_right_near_band2;1");
 auto xy0=f.Get<TH2F>("x_right_near_y_right_near_band_none;1");
 auto xy=(TH2F*) xy1->Clone("x_right_near_y_right_near_all");
 xy->Add(xy2);
 xy->Add(xy0);
 auto xy1r=(TH2F*) xy1->Clone("x_right_near_y_right_near_band1_fraction");
 xy1r->Divide(xy);
 auto xy2r=(TH2F*) xy2->Clone("x_right_near_y_right_near_band2_fraction");
 xy2r->Divide(xy);
 auto xy0r=(TH2F*) xy0->Clone("x_right_near_y_right_near_band_none_fraction");
 xy0r->Divide(xy);

 auto xx1=f.Get<TH2F>("x_right_near_dx_right_band1;1");
 auto xx2=f.Get<TH2F>("x_right_near_dx_right_band2;1");
 auto xx0=f.Get<TH2F>("x_right_near_dx_right_band_none;1");

 auto xy1c=f.Get<TH2F>("x_right_near_y_right_near_band1_cut3;1");
 auto xy2c=f.Get<TH2F>("x_right_near_y_right_near_band2_cut3;1");
 auto xy0c=f.Get<TH2F>("x_right_near_y_right_near_band_none_cut3;1");
 auto xyc=(TH2F*) xy1c->Clone("x_right_near_y_right_near_all_cut3");
 xyc->Add(xy2c);
 xyc->Add(xy0c);
 auto xy1cr=(TH2F*) xy1c->Clone("x_right_near_y_right_near_band1_cut3_fraction");
 xy1cr->Divide(xyc);
 auto xy2cr=(TH2F*) xy2c->Clone("x_right_near_y_right_near_band2_cut3_fraction");
 xy2cr->Divide(xyc);
 auto xy0cr=(TH2F*) xy0c->Clone("x_right_near_y_right_near_band_none_cut3_fraction");
 xy0cr->Divide(xyc);

 auto xx1c=f.Get<TH2F>("x_right_near_dx_right_band1_cut3;1");
 auto xx2c=f.Get<TH2F>("x_right_near_dx_right_band2_cut3;1");
 auto xx0c=f.Get<TH2F>("x_right_near_dx_right_band_none_cut3;1");
 
 TCanvas MyC;
 MyC.Divide(2,2);
 MyC.cd(1);
 gPad->SetLogz();
 xy1->GetXaxis()->SetRangeUser(-15.,15.);
 xy1->GetYaxis()->SetRangeUser(5.,30.);
 xy1->Draw("colz");
 MyC.cd(2);
 gPad->SetLogz();
 xy2->GetXaxis()->SetRangeUser(-15.,15.);
 xy2->GetYaxis()->SetRangeUser(5.,30.);
 xy2->Draw("colz");
 MyC.cd(3);
 gPad->SetLogz();
 xy0->GetXaxis()->SetRangeUser(-15.,15.);
 xy0->GetYaxis()->SetRangeUser(5.,30.);
 xy0->Draw("colz");
 MyC.Print("r369585v4-LBRT-bands-x-vs-y.pdf");
 MyC.Print("r369585v4-LBRT-bands-x-vs-y.C");
 MyC.Print("r369585v4-LBRT-bands-x-vs-y.png");
 MyC.cd(1);
 xy1c->GetXaxis()->SetRangeUser(-7.,7.);
 xy1c->GetYaxis()->SetRangeUser(5.,30.);
 xy1c->Draw("colz");
 MyC.cd(2);
 xy2c->GetXaxis()->SetRangeUser(-7.,7.);
 xy2c->GetYaxis()->SetRangeUser(5.,30.);
 xy2c->Draw("colz");
 MyC.cd(3);
 xy0c->GetXaxis()->SetRangeUser(-7.,7.);
 xy0c->GetYaxis()->SetRangeUser(5.,30.);
 xy0c->Draw("colz");
 MyC.Print("r369585v4-LBRT-bands-x-vs-y-cut3.pdf");
 MyC.Print("r369585v4-LBRT-bands-x-vs-y-cut3.png");
 MyC.Print("r369585v4-LBRT-bands-x-vs-y-cut3.C");

 MyC.Clear();
 MyC.Divide(2,3);
 MyC.cd(1);
 xy1cr->GetXaxis()->SetRangeUser(-7.,7.);
 xy1cr->GetYaxis()->SetRangeUser(5.,30.);
 xy1cr->Draw("colz");
 MyC.cd(2);
 xy2cr->GetXaxis()->SetRangeUser(-7.,7.);
 xy2cr->GetYaxis()->SetRangeUser(5.,30.);
 xy2cr->Draw("colz");
 MyC.cd(3);
 xy0cr->GetXaxis()->SetRangeUser(-7.,7.);
 xy0cr->GetYaxis()->SetRangeUser(5.,30.);
 xy0cr->Draw("colz");
 MyC.cd(4);
 xy1r->GetXaxis()->SetRangeUser(-15.,15.);
 xy1r->GetYaxis()->SetRangeUser(5.,30.);
 xy1r->Draw("colz");
 MyC.cd(5);
 xy2r->GetXaxis()->SetRangeUser(-15.,15.);
 xy2r->GetYaxis()->SetRangeUser(5.,30.);
 xy2r->Draw("colz");
 MyC.cd(6);
 xy0r->GetXaxis()->SetRangeUser(-15.,15.);
 xy0r->GetYaxis()->SetRangeUser(5.,30.);
 xy0r->Draw("colz");
 MyC.Print("r369585v4-LBRT-bands-x-vs-y-band_event_fraction.pdf");
 MyC.Print("r369585v4-LBRT-bands-x-vs-y-band_event_fraction.png");
 MyC.Print("r369585v4-LBRT-bands-x-vs-y-band_event_fraction.C");

 MyC.Clear();
 MyC.Divide(2,2);
 xx1->GetYaxis()->SetRangeUser(-3.,3.);
 xx2->GetYaxis()->SetRangeUser(-3.,3.);
 xx0->GetYaxis()->SetRangeUser(-3.,3.);
 xx1c->GetYaxis()->SetRangeUser(-3.,3.);
 xx2c->GetYaxis()->SetRangeUser(-3.,3.);
 xx0c->GetYaxis()->SetRangeUser(-3.,3.);
 xx1->GetXaxis()->SetRangeUser(-13.,13.);
 xx2->GetXaxis()->SetRangeUser(-13.,13.);
 xx0->GetXaxis()->SetRangeUser(-13.,13.);
 xx1c->GetXaxis()->SetRangeUser(-13.,13.);
 xx2c->GetXaxis()->SetRangeUser(-13.,13.);
 xx0c->GetXaxis()->SetRangeUser(-13.,13.);
 xx1->GetYaxis()->SetTitle("x far minus near (mm)");
 xx2->GetYaxis()->SetTitle("x far minus near (mm)");
 xx0->GetYaxis()->SetTitle("x far minus near (mm)");
 xx1c->GetYaxis()->SetTitle("x far minus near (mm)");
 xx2c->GetYaxis()->SetTitle("x far minus near (mm)");
 xx0c->GetYaxis()->SetTitle("x far minus near (mm)");
 MyC.cd(1);
 gPad->SetLogz();
 xx1->Draw("colz");
 MyC.cd(2);
 gPad->SetLogz();
 xx2->Draw("colz");
 MyC.cd(3);
 gPad->SetLogz();
 xx0->Draw("colz");
 MyC.Print("r369585v4-LBRT-bands-x-vs-dx.pdf");
 MyC.Print("r369585v4-LBRT-bands-x-vs-dx.png");
 MyC.Print("r369585v4-LBRT-bands-x-vs-dx.C");

 MyC.cd(1);
 xx1c->Draw("colz");
 MyC.cd(2);
 xx2c->Draw("colz");
 MyC.cd(3);
 xx0c->Draw("colz");
 MyC.Print("r369585v4-LBRT-bands-x-vs-dx-cut3.pdf");
 MyC.Print("r369585v4-LBRT-bands-x-vs-dx-cut3.png");
 MyC.Print("r369585v4-LBRT-bands-x-vs-dx-cut3.C");
}
