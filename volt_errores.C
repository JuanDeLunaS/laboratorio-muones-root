void volt_errores()
{
	//gStyle->SetOptFit(1111); //Tabla de datos
	
	TGraphErrors *gr = new TGraphErrors();
	
	gr->SetMarkerStyle(kFullCircle);
	gr->SetMarkerSize(1.2);
	gr->SetMarkerColor(kRed+2);
	gr->SetLineColor(kAzure+2);
	gr->SetLineWidth(2);
	
	gr->SetTitle("Tasa de Coincidencias vs Voltaje;Voltaje [V];Rate [s^{-1}]");
	
	fstream file;
	file.open("volt.txt", ios::in);
	
	if (!file.is_open()) {
		std::cout << "Error al abrir volt.txt" << std::endl;
		return;
	}
	
	const double delta_t = 1800.0;
	
	while (1) {
		double V, N;
		file >> V >> N;
		if (file.eof()) break;
		
		//calculo de errores
		double rate = N / delta_t;
		double e_rate = sqrt(N) / delta_t;
		double eV = 0.0; // Error en voltaje
		
		int n = gr->GetN();
		gr->SetPoint(n, V, rate);
		gr->SetPointError(n, eV, e_rate);
	}
	file.close();
	
	TCanvas *c1 = new TCanvas("c1", "Curva Rate vs HV", 800, 600);
	c1->SetGrid(); 
	
	gr->Draw("AP");
	
	c1->SaveAs("tasa_vs_voltaje2.png");
	c1->SaveAs("tasa_vs_voltaje2.pdf");
	
	TF1 *fitFunc = new TF1("fitFunc", "[0]/(1.0 + exp(-(x-[1])/[2]))", 350, 950);
	fitFunc->SetParNames("N_{max}", "V_{0}", "#Delta V");
	
	fitFunc->SetParameters(80.0, 650.0, 15.0);
	fitFunc->SetLineColor(kRed+1);
	fitFunc->SetLineWidth(3);
	
	gr->Fit("fitFunc", "R");
	
	TLegend *leg = new TLegend(0.15, 0.75, 0.45, 0.88);
	leg->AddEntry(gr, "Datos experimentales (#sigma = #sqrt{N})", "pe");
	leg->AddEntry(fitFunc, "Ajuste Sigmoide (Modelo PMT)", "l");
	leg->Draw();
}
