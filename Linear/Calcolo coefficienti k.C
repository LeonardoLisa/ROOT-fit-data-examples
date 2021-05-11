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
	c1 = new TCanvas("c1", "My ROOT Plot", 1600, 700);
	// Split window
	c1->Divide(3, 1);

	// Load data from file and add error bar
	// NOTE !!!
	// 1) File endcoding must be UTF-8
	//    https://www.freeformatter.com/convert-file-encoding.html
	//
	// 2) Data delimeter must be ' ' (space char.)
	//
	f1 = new TGraphErrors("Molla1.csv");
	f2 = new TGraphErrors("Molla2.csv");
	f3 = new TGraphErrors("Molla3.csv");

	// Set Style
	f1->SetMarkerStyle(23); // 21 for square
	f2->SetMarkerStyle(23);
	f3->SetMarkerStyle(23);
	f1->SetTitle("Spring One; delta x [m]; Force [N]");
	f2->SetTitle("Spring Two; delta x [m]; Force [N]");
	f3->SetTitle("Spring Three; delta x [m]; Force [N]");
	f1->SetLineColor(kRed+2);
	f2->SetLineColor(kBlue+2);
	f3->SetLineColor(kGreen+2);
	// f1->SetLineWidth(3);
	// f2->SetLineWidth(3);
	// f3->SetLineWidth(3);
	f1->SetMarkerSize(1.5);
	f2->SetMarkerSize(1.5);
	f3->SetMarkerSize(1.5);

	// Add point at run time
	// f->SetPoint();

	// Fit function
	g = new TF1("f", "[0]*x + [1]"); // Two unknown parameter
	g->SetParNames("k","q");

	gStyle->SetOptFit(1111);
  // p = 1 print probability
  // c = 1 print Chi-square/number of degrees of freedom
  // e = 1 print errors (if e=1, v must be 1)
  // v = 1 print name/values of parameters

	// g->SetParameters(20, -1);
	f1->Fit(g, "EM");
	f2->Fit(g, "EM");
	f3->Fit(g, "EM");
	// “E” Perform better errors estimation using the Minos technique
	// “M” Improve fit results, by using the IMPROVE algorithm of TMinuit

	c1->cd(1);
	f1->Draw("AP");
	// AP no segments
	// ALP linear segments
	// ACP curve segments

	c1->cd(2);
	f2->Draw("AP");

	c1->cd(3);
	f3->Draw("AP");
}
