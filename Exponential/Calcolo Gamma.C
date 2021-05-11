// Calcolo coeficienti angolari k
/*
  *
  * Leonardo Lisa
  * 01/05/2021
  * leonardo.lisa@studenti.unimi.it
  *
  */

{
	// Formatting plot
	c1 = new TCanvas("c1", "My ROOT Plot", 1800, 700);
	// Split window
	c1->Divide(2, 1);

	// Load data from file and add error bar
	// NOTE !!!
	// 1) File endcoding must be UTF-8
	//    https://www.freeformatter.com/convert-file-encoding.html
	//
	// 2) Data delimeter must be ' ' (space char.)
	//
	f1 = new TGraphErrors("Peak positive DOCP.csv");
	f2 = new TGraphErrors("Peak negative DOCP.csv");

	// Set Style
	f1->SetMarkerStyle(23); // 21 for square
	f2->SetMarkerStyle(22);
	f1->SetTitle("Driven oscillator in counter phase positive peaks; Time [s]; Amplitude [m]");
	f2->SetTitle("Driven oscillator in counter phase negative peaks; Time [s]; Amplitude [m]");
	f1->SetLineColor(kRed+2);
	f2->SetLineColor(kBlue+2);
	// f1->SetLineWidth(3);
	// f2->SetLineWidth(3);
	f1->SetMarkerSize(1.5);
	f2->SetMarkerSize(1.5);

	// Add point at run time
	// f->SetPoint();

	// Fit function
	g = new TF1("g", "[1]*e^(-([0]*x)/2) + [2]"); // Two unknown parameter
	g->SetParameter(0, 0.01);
    g->SetParameter(1, 0.01);
	g->SetParameter(2, 0.2688);
	g->SetParLimits(2, 0.265, 0.270);
	g->SetParNames("Gamma","A0", "q");

	gStyle->SetOptFit(1111);
	// p = 1 print probability
	// c = 1 print Chi-square/number of degrees of freedom
	// e = 1 print errors (if e=1, v must be 1)
	// v = 1 print name/values of parameters

	// g->SetParameters(20, -1);
	f1->Fit(g, "EM");
	g->SetParameter(0, 0.01);
	g->SetParameter(1, -0.01);
	g->SetParameter(2, 0.2688);
	g->SetParLimits(2, 0.265, 0.270);
	f2->Fit(g, "EM");
	// “E” Perform better errors estimation using the Minos technique
	// “M” Improve fit results, by using the IMPROVE algorithm of TMinuit

	c1->cd(1);
	f1->Draw("AP");
	// AP no segments
	// ALP linear segments
	// ACP curve segments

	c1->cd(2);
	f2->Draw("AP");
}
