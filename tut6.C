void tut6()
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
	
	TCanvas *c1 = new TCanvas();
	hist->Draw();
}
