void volt1()
{
	
	TGraph *gr = new TGraph();
	
	gr->SetMarkerStyle(kFullCircle);
	gr->SetLineWidth(2);
	gr->SetLineColor(kRed);
	
	gr->SetTitle("Graph");
	gr->GetXaxis()->SetTitle("Voltaje");
	gr->GetYaxis()->SetTitle("Detecciones");
	
	fstream file;
	file.open("volt.txt", ios::in);
	
	while(1)
	{
		double x, y;
		file >> x >> y;
		gr->SetPoint(gr->GetN(), x, y);
		if(file.eof()) break;
	}
	
	file.close();
	
	TCanvas *c1 = new TCanvas();
	gr->Draw("ALP");
}
