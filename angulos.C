void angulos()
{
	
	TGraphErrors *gr = new TGraphErrors();
	
	//gr->SetMarkerStyle(kFullCircle);
	//gr->SetMarkerSize(1.2);
	//gr->SetMarkerColor(kRed+2);
	//gr->SetLineColor(kAzure+2);
	//gr->SetLineWidth(2);
	
	//gr->SetTitle("Distribucion Angular de Muones Cosmicos;Angulo Cenital #theta [deg];Flujo f(#theta) [s^{-1} cm^{-2} sr^{-1}]");
	
	fstream file;
	file.open("angulo.txt", ios::in);
	
	if (!file.is_open()) {
		std::cout << "Error al abrir volt.txt" << std::endl;
		return;
	}
	
	const double delta_t = 3600.0;
	const double Area = 64.0;
	const double dOmega = 0.790; //tomando en cuenta que las paletas estaban a una distancia de d aprox 18cm
	
	const double norm_factor = Area * dOmega * delta_t;
	
	while (1) {
		double theta, N;
		file >> theta >> N;
		if (file.eof()) break;
		
		//calculo de errores
		double f = N / norm_factor;
		double e_f = sqrt(N) / norm_factor;
		double e_theta = 0.5; // Error aproximado del transportador(2 grados)
		
		int n = gr->GetN();
		gr->SetPoint(n, theta, f);
		gr->SetPointError(n, e_theta, e_f);
	}
	file.close();
	
	TCanvas *c1 = new TCanvas("c1", "Distribución Angular", 800, 600);
	c1->SetGrid(); 
	
	//gr->Draw("AP");
	
	gr->SetMarkerStyle(kFullCircle);
	gr->SetMarkerSize(1.2);
	gr->SetMarkerColor(kBlack);
	gr->SetLineColor(kAzure+2);
	gr->SetLineWidth(2);
	gr->SetTitle("Distribucion Angular de Muones Cosmicos;Angulo Cenital #theta [deg];Flujo f(#theta) [s^{-1} cm^{-2} sr^{-1}]");
	
	gStyle->SetOptFit(0001);
	
	TF1 *fitCos = new TF1("fitCos", "[0] * pow(TMath::Cos(x * TMath::DegToRad()), [1])", 0, 45);
	fitCos->SetParNames("F_0", "n");
	fitCos->SetParameters(0.001, 2.16); //Semillas iniciales del artículo
	fitCos->SetLineColor(kRed+1);
	fitCos->SetLineWidth(2);
	
	gr->Fit("fitCos", "R");
	
	gr->Draw("AP");
	
	
	c1->Update();
	c1->SaveAs("distribucion_angular3.png");
	c1->SaveAs("distribucion_angular3.pdf");
}
