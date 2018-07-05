#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <getopt.h>

//#include "Hadron.h"
#include "Tools.h"
#include "Detector.h"
#include "Physics.h"
#include "Flux.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom3.h"
#include "TGenPhaseSpace.h"

void Usage(char* argv0);
double lDparam(double xf, double pt)
{
	//from 1708.08700, 250GeV proton beam E796
	double b = 1.08;
	double n = 6.1;
	return n*(1-std::abs(xf)) - b * pt*pt;
}

int main(int argc, char** argv)
{
	const struct option longopts[] = 
	{
		{"", 	required_argument, 	0, 'b'},
		{"confidence", 	required_argument, 	0, 'C'},
		{"help", 	no_argument,	 	0, 'h'},
		{0,	0, 	0,	0},
	};

	int index; 
	int iarg = 0;
	opterr = 1;

	//std::string sProb, sTarg("H"), OutName;
	std::string OutName, DetConfig;
	std::ofstream OutFile;
	double BeamE = 800;	//DONUT
	unsigned int nMAX = 1e5;
	double NuMass = 0.0;	//neutrino mass

	while((iarg = getopt_long(argc,argv, "r:s:m:E:t:o:I:d:h", longopts, &index)) != -1)
	{
		switch(iarg)
		{
			case 'r':
				OutName.assign(optarg);
				break;
			case 'm':
				NuMass = strtod(optarg, NULL);
				break;
			case 'E':
				BeamE = strtod(optarg, NULL);
				break;
			case 'o':
				OutFile.open(optarg);
				break;
			case 'I':
				nMAX = strtol(optarg, NULL, 10);
				break;
			case 'd':
				DetConfig.assign(optarg);
				break;
			case 'h':
				Usage(argv[0]);
				return 1;
			default:
				break;
		}
	}

	std::ostream &Out = (OutFile.is_open()) ? OutFile : std::cout;

	std::string Out_ = OutName + ".root";
	std::string OutB = OutName + "Bar.root";

	TFile *FileOut_ = new TFile(Out_.c_str(), "RECREATE");
	TFile *FileOutB = new TFile(OutB.c_str(), "RECREATE");

	TH1D * hTotal_ = new TH1D("htotal1", "total",  100, 0, 20);
	TH1D * hTotalB = new TH1D("htotal2", "total",  100, 0, 20);

	//neutrino
	TH1D * hCharm = new TH1D("hcharm", "charm",  100, 0, 20);

	//antineutrino
	TH1D * hTauE  = new TH1D("htaue",  "taue",   100, 0, 20);
	TH1D * hTauM  = new TH1D("htaum",  "taum",   100, 0, 20);
	TH1D * hPion  = new TH1D("hpion",  "pion",   100, 0, 20);
	TH1D * h2Pion = new TH1D("h2pion", "2 pion", 100, 0, 20);

	//hTotal_->SetDirectory(FileOut_);
	hCharm->SetDirectory(FileOut_);

	//hTotalB->SetDirectory(FileOutB);
	hTauE->SetDirectory(FileOutB);
	hTauM->SetDirectory(FileOutB);
	hPion->SetDirectory(FileOutB);
	h2Pion->SetDirectory(FileOutB);

	//generous angular acceptance of detector
	Detector *TheBox = new Detector(DetConfig);
	double Th0 = atan2(2*TheBox->Get("Height"), TheBox->Get("Baseline"));

	TRandom3 *Gen = new TRandom3(0);

	TLorentzVector Beam(0, 0, sqrt(pow(BeamE, 2) - pow(Const::fMProton, 2)), BeamE);
	TLorentzVector Targ(0, 0, 0, Const::fMProton);
	TLorentzVector S = Beam+Targ;
	double sqrts = S.M();		//CM energy

	Neutrino *Nu_ = new Neutrino(NuMass, Neutrino::Dirac | Neutrino::Unpolarised);
	Neutrino *NuB = new Neutrino(NuMass, Neutrino::Dirac | Neutrino::Unpolarised | Neutrino::Antiparticle);
	
	//find max of Ds param
	double ptmax = sqrts;
	double maxF = lDparam(0, 0);
	double minF = lDparam(1, ptmax);

	double SF = 12.1e-3 / 331.4 * 0.077 * 0.0548 / double(nMAX);

	std::vector<Particle*> vProductDs, vProductTau;
	std::vector<Particle*>::iterator iP;

	unsigned int nIter = 0, iIter = 0;
	while (iIter < nMAX)
	{
		for (iP = vProductDs.begin(); iP != vProductDs.end(
		vProductDs.clear();k

		++nIter;
		double pt = Gen->Uniform(0, ptmax);
		double xf = Gen->Uniform(-1.0, 1.0);
		if (Gen->Uniform(0, pow(10, maxF)) < pow(10, lDparam(xf, pt)))
		{
			double px, py;
			double pz = sqrts*xf*0.5;
			Gen->Circle(px, py, pt);

			TLorentzVector Ds_vec(px, py, pz, sqrt(pt*pt + pz*pz + pow(Const::fMDs, 2)));
			Ds_vec.Boost(S.BoostVector());	//parent lab frame

			vProducts = Nu_->ProductionPS(Amplitude::_CharmT, Ds_vec);

			if(!vProducts.size())
				continue;

			if (vProducts.at(0)->Theta() < Th0)	//neutrino
				hCharm->Fill(vProducts.at(0)->Energy(), SF);

			TLorentzVector Tau_vec = vProducts.at(1)->FourVector();

			for (unsigned int i = 0; i < 4; ++i)
			{
				Amplitude::Channel Name;
				TH1D* hFill;
				double Br;
				switch (i)
				{
					case 0:
						Name = Amplitude::_TauET;
						hFill = hTauE;
						Br = SF * 0.1785;
						break;
					case 1:
						Name = Amplitude::_TauMT;
						hFill = hTauM;
						Br = SF * 0.1736;
						break;
					case 2:
						Name = Amplitude::_TauPI;
						hFill = hPion;
                                                Br = SF * 0.1082;
						break;
					case 3:
						Name = Amplitude::_Tau2PI;
						hFill = h2Pion;
                                                Br = SF * 0.2551;
						break;
					default:
						break;
				}

				vProducts.clear();
				vProducts = NuB->ProductionPS(Name, Tau_vec);

				if (vProducts.at(0)->Theta() < Th0)	//neutrino
					hFill->Fill(vProducts.at(0)->Energy(), Br);
			}

			++iIter;

			if (iIter % 100000 == 0)
			{
				FileOut_->Write();
				FileOutB->Write();
			}
		}
	}
	//		cc	pC	fDs	Br	Tot evts  
	//double SF = 12.1e-3 / 331.4 * 0.077 * 0.0548 / double(nMAX);

	//hCharm->Scale(SF);
	//hTauE->Scale(SF * 0.1785);	//tau->e (17.85 %)
	//hTauM->Scale(SF * 0.1736);	//tau->mu (17.36 %)
	//hPion->Scale(SF * 0.1082);	//tau->pi (10.82 %)
	//h2Pion->Scale(SF * 0.2551);	//tau->2pi (25.62 %)	Phase space only!!

	hTotal_->Add(hCharm);

	hTotalB->Add(hTauE);
	hTotalB->Add(hTauM);
	hTotalB->Add(hPion);
	hTotalB->Add(h2Pion);

	FileOut_->cd();
	FileOut_->Write();

	hTotal_->Write("htotal");
	//hCharm->Write();

	FileOutB->cd();
	FileOutB->Write();

	hTotalB->Write("htotal");
	//hTauE->Write();
	//hTauM->Write();
	//hPion->Write();
	//h2Pion->Write();

	std::cout << "Simulated Ds meson producing succesful neutrinos are " << (100.0 * iIter) / nIter << " % of the total" << std::endl;
	std::cout << hTotal_->GetEntries() << " neutrinos simulated, saved in ";
	std::cout << FileOut_->GetName() << std::endl;
	std::cout << hTotalB->GetEntries() << " antineutrinos simulated" << std::endl;
	std::cout << FileOutB->GetName() << std::endl;

	FileOut_->Close();
	FileOutB->Close();

	return 0;
}

void Usage(char* argv0)
{
	std::cout << "Description" << std::endl;
	std::cout << "Usage : " << std::endl;
	std::cout << argv0 << " [OPTIONS]" << std::endl;
	std::cout <<"\n  -t,  --target" << std::endl;
	std::cout << "\t\tThe element of the target (available 'H', 'C')" << std::endl;
	std::cout <<"\n  -o,  --output" << std::endl;
	std::cout << "\t\tOutput file" << std::endl;
	std::cout <<"\n  -h,  --help" << std::endl;
	std::cout << "\t\tPrint this message and exit" << std::endl;
}
