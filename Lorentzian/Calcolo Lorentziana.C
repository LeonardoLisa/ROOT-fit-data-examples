// Calcolo Lorentziana
/*
  *
  * Leonardo Lisa
  * 01/05/2021
  * leonardo.lisa@studenti.unimi.it
  *
  */

{
	// Formatting plot
	c1 = new TCanvas("c1", "My ROOT Plot", 1800, 800);
	// Split window
	c1->Divide(2, 1);

	// Load data from file and add error bar
	// NOTE !!!
	// 1) File endcoding must be UTF-8
	//    https://www.freeformatter.com/convert-file-encoding.html
	//
	// 2) Data delimeter must be ' ' (space char.)
	//
  f1 = new TGraphErrors("Lorentziana in controfase.csv");
  f2 = new TGraphErrors("Lorentziana in Fase.csv");

	// Set Style
	f1->SetMarkerStyle(23); // 21 for square
	f2->SetMarkerStyle(23);
	f1->SetTitle("Lorentzian in Counter-Phase; Frequency [Hz]; Amplitude [m]");
	f2->SetTitle("Lorentzian in Phase; Frequency [Hz]; Amplitude [m]");
	// f1->SetLineColor(kRed+2);
	// f2->SetLineColor(kBlue+2);
	// f1->SetLineWidth(3);
	// f2->SetLineWidth(3);
	f1->SetMarkerSize(1.5);
	f2->SetMarkerSize(1.5);

	// Add point at run time
	// f->SetPoint();

	// Fit function
	g = new TF1("f", "[2]/(sqrt(([1]^2 - x^2)^2 + ([0]^2)*(x^2)))"); // Two unknown parameter
	g->SetParameter(0, 0.02);
  g->SetParLimits(0, 0.01, 0.05);
  g->SetParameter(1, 2);
  g->SetParLimits(1, 0.5, 4);
  g->SetParameter(2, 0.004);
  g->SetParLimits(2, 0.001, 0.01);
  g->SetParNames("Gamma","Resonance_f", "F/M");

	gStyle->SetOptFit(1111);
  // p = 1 print probability
  // c = 1 print Chi-square/number of degrees of freedom
  // e = 1 print errors (if e=1, v must be 1)
  // v = 1 print name/values of parameters

	f1->Fit(g, "EM");
	f2->Fit(g, "EM");
	// “E” Perform better errors estimation using the Minos technique
	// “M” Improve fit results, by using the IMPROVE algorithm of TMinuit

	c1->cd(1);
	f1->SetMaximum(0.12);
	f1->SetMinimum(0);
	f1->Draw("AP");
	// AP no segments
	// ALP linear segments
	// ACP curve segments

	c1->cd(2);
	f2->SetMaximum(0.12);
	f2->SetMinimum(0);
	f2->Draw("AP");
	//f2->GetYaxis()->SetRange(0, 0.12);
}
