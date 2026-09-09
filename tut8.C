void tut8()
{
	TH1F *hist = new TH1F("hist", "Histogram", 100, 0, 10);
	
	TRandom2 *rand = new TRandom2(3);
	
	fstream file;
	file.open("data.txt", ios::out);
	
	for(int i = 0; i < 1000; i++)
	{
		double r = rand->Gaus(5,1);
		file << r << endl;
	}
	
	file.close();
	
	file.open("data.txt", ios::in);
	
	double value;
	
	while(1)
	{
		file >> value;
		hist->Fill(value);
		if(file.eof()) break;
	}
	
	file.close();
	
	hist->GetXaxis()->SetTitle("Distribution");
	hist->GetYaxis()->SetTitle("Entries");
	
	TF1 *fit = new TF1("fit", "gaus", 0,10);
	
	fit->SetParameter(0, 40);
	fit->SetParameter(1, 5);
	fit->SetParameter(2, 1);
	
	TCanvas *c1 = new TCanvas();
	hist->SetStats(0);
	hist->Draw();
	hist->Fit("fit", "R");
	
	TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
	leg->AddEntry(hist, "Measured Data", "l");
	leg->AddEntry(fit, "Fit Function", "l");
	leg->Draw();
	
	double mean = fit->GetParameter(1);
	double sigma = fit->GetParameter(2);
	
	cout << mean/sigma << endl;
}
