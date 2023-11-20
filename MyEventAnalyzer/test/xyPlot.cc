{
	TFile d1("results_LBRT.root");
	TFile d2("results_LTRB.root");
	TCanvas MyC;
	gPad->SetLogz();
	auto* xyl1=d1.Get<TH2F>("x_left_near_y_left_near;1");
	auto* xyl2=d2.Get<TH2F>("x_left_near_y_left_near;1");
	xyl1->SetTitle("X vs Y, left near (diagonal LBRT);X_{L,nr} (mm);Y_{L,nr}");
	xyl2->SetTitle("X vs Y, left near (diagonal LTRB);X_{L,nr} (mm);Y_{L,nr}");
	xyl1->GetXaxis()->SetRangeUser(-30.,30.);
	xyl2->GetXaxis()->SetRangeUser(-30.,30.);
	xyl1->GetYaxis()->SetRangeUser(-35.,-5.);
	xyl2->GetYaxis()->SetRangeUser(5.,35.);
	auto* xyl1b=d1.Get<TH2F>("x_left_near_y_left_near_cut3;1");
	auto* xyl2b=d2.Get<TH2F>("x_left_near_y_left_near_cut3;1");
	xyl1b->SetTitle("X vs Y, left near (diagonal LBRT+cuts 1-2-3);X_{L,nr} (mm);Y_{L,nr}");
	xyl2b->SetTitle("X vs Y, left near (diagonal LTRB+cuts 1-2-3);X_{L,nr} (mm);Y_{L,nr}");
	xyl1b->GetXaxis()->SetRangeUser(-30.,30.);
	xyl2b->GetXaxis()->SetRangeUser(-30.,30.);
	xyl1b->GetYaxis()->SetRangeUser(-35.,-5.);
	xyl2b->GetYaxis()->SetRangeUser(5.,35.);
	xyl1->Draw("colz");
	MyC.Print("xNear-yNear-diag1-r596-17p22millionEvt.pdf");
	MyC.Print("xNear-yNear-diag1-r596-17p22millionEvt.png");
	xyl2->Draw("colz");
	MyC.Print("xNear-yNear-diag2-r596-17p22millionEvt.pdf");
	MyC.Print("xNear-yNear-diag2-r596-17p22millionEvt.png");
	xyl1b->Draw("colz");
	MyC.Print("xNear-yNear-diag1-cut3-r596-17p22millionEvt.pdf");
	MyC.Print("xNear-yNear-diag1-cut3-r596-17p22millionEvt.png");
	xyl2b->Draw("colz");
	MyC.Print("xNear-yNear-diag2-cut3-r596-17p22millionEvt.pdf");
	MyC.Print("xNear-yNear-diag2-cut3-r596-17p22millionEvt.png");
}
