#include "Detector/Tracker.h"

Tracker::Tracker(std::string ConfigName) : Detector(ConfigName)
{
}

void Tracker::TrackReconstruct(Particle *&P)
{
	if (P)
	{
		if (P->Dist() == 0.0)
			TrackVertex(P);

		if (P->TrackOut() < 0)
			TrackLength(P);
		TrackSmearing(P);

		if (!IsDetectable(P))
		{
			//delete P;
			P = 0;
		}
	}
}

void Tracker::TrackVertex(Particle *&P)
{
	double X, Y;
	double Z = GenMT->Uniform(Zstart(), Zend());
	if (Z > ZstartLAr() && Z < ZendLAr())
	{
		X = GenMT->Uniform(XstartLAr(), XendLAr());
		Y = GenMT->Uniform(YstartLAr(), YendLAr());
	}
	else if (Z > ZstartFGT() && Z < ZendFGT())
	{
		X = GenMT->Uniform(XstartFGT(), XendFGT());
		Y = GenMT->Uniform(YstartFGT(), YendFGT());
	}

	P->SetPosition(X, Y, Z);
}

void Tracker::TrackSmearing(Particle *&P)
{
	double iM = P->Mass();
	double iEkin = P->EnergyKin();
	double iP = P->Momentum();
	double iTheta = P->Theta();
	double iPhi = P->Phi();
	double SigmaE, SigmaP, SigmaA; 
	double StatE, SystE;
	double Ratio;

	switch (abs(P->Pdg()))
	{
		case 11:
		case 22:
			SigmaA = Get("Angle_Gamma") / Const::fDeg;
			StatE = Get("Energ_Gamma") / sqrt(iEkin);
			SystE = Get("Ebias_Gamma");
			SigmaE = sqrt(pow(StatE, 2)+pow(SystE, 2)) * iEkin;

			P->SetEnergyKin(GenMT->Gaus(iEkin, SigmaE));
			P->SetTheta(GenMT->Gaus(iTheta, SigmaA));
			P->SetPhi(GenMT->Gaus(iPhi, SigmaA));

			break;
		case 13:
			SigmaA = Get("Angle_Muon") / Const::fDeg;
			Ratio = P->TrackIn()/P->TrackTot();

			if (Ratio > Get("Containment"))	//90% of track inside
				SigmaP = Get("Range_Muon");
				//double StatP = Get("Range_Muon") / iP;
				//SigmaP = StatP * iP;
			else
				SigmaP = Get("Exiti_Muon") * iP;
				//double StatP = Get("Exiti_Muon");
				//SigmaP = StatP * iP;

			P->SetMomentum(GenMT->Gaus(iP, SigmaP));
			P->SetTheta(GenMT->Gaus(iTheta, SigmaA));
			P->SetPhi(GenMT->Gaus(iPhi, SigmaA));

			break;
		case 211:
			SigmaA = Get("Angle_Pion") / Const::fDeg;
			Ratio = P->TrackIn()/P->TrackTot();

			if (!P->IsShower() && Ratio > Get("Containment"))	//pion track, not shower
				SigmaP = Get("Range_Pion");
				//double StatP = Get("Range_Pion") / iP;
				//SigmaP = StatP * iP;
			else
				SigmaP = Get("Exiti_Pion") * iP;
				//double StatP = Get("Exiti_Pion");
				//SigmaP = StatP * iP;

			P->SetMomentum(GenMT->Gaus(iP, SigmaP));
			P->SetTheta(GenMT->Gaus(iTheta, SigmaA));
			P->SetPhi(GenMT->Gaus(iPhi, SigmaA));

			break;
		default:
			if (P->Charge() != 0)	//other and protons?
			{
				SigmaA = Get("Angle_Hadron") / Const::fDeg;
				StatE = Get("Energ_Hadron") / sqrt(iEkin);
				SystE = Get("Ebias_Hadron");
				SigmaE = sqrt(pow(StatE, 2)+pow(SystE, 2)) * iEkin;
			
				P->SetEnergyKin(GenMT->Gaus(iEkin, SigmaE));
				P->SetTheta(GenMT->Gaus(iTheta, SigmaA));
				P->SetPhi(GenMT->Gaus(iPhi, SigmaA));
			}
			break;
	}

	P->SetTrackIn(GenMT->Gaus(P->TrackIn(), Get("Vertex")));

	if (P->TrackIn() < 0)
		P->SetTrackIn(0);

	P->SetTrackOut(GenMT->Gaus(P->TrackOut(), Get("Vertex")));

	if (P->TrackOut() < 0)
		P->SetTrackOut(0);
}

void Tracker::TrackLength(Particle *&P)	//This should not change *P
{
	double tmax, Depth;
	double iE, iM, dE;
	double dStep = 0.01, dx;
	double LengthIn = 0.0, LengthBack = 0.0, LengthOut = 0.0;
	double TotTrack = 0, Layer = 0;

	TVector3 Step(P->Direction().Unit());
	TVector3 Pos(P->Position());
	TVector3 Start(P->Position());

	switch (abs(P->Pdg()))
	{
		case 11:
			tmax = log(P->Energy()/CriticalEnergy(P)) - 1.0;
			Depth = RadiationLength(P) * GenMT->Gaus(tmax, 0.3*tmax);

			P->SetTrackIn(Depth);
			break;
		case 22:
			P->SetTrackIn(GammaDecay(P));
			break;
		case 13:
			iE = P->Energy();
			
			while (IsDetectable(P) && !IsDecayed(P, dStep))		//this should quit when particle decays too!
			{
				bool InOut;
				double dx = GenMT->Gaus(dStep, Get("Vertex"));
				double dE = dx * EnergyLoss(P, InOut);	//inside material

				if (InOut)
					LengthIn += dx;
				else
					LengthOut += dx;

				Pos += Step*dx;		//move by dx
				P->SetEnergy(P->Energy() - dE);
				P->SetPosition(Pos);
			}

			P->SetTrackIn(LengthIn);
			//P->SetTrackBack(LengthBack);
			P->SetTrackOut(LengthOut);
			P->SetEnergy(iE);		//reset to original energy
			P->SetPosition(Start);		//reset to original position
			break;
		case 211:
			iE = P->Energy();
			iM = P->Mass();
			
			while (IsDetectable(P) && !IsDecayed(P, dStep))		//this should quit when particle decays too!
			{
				double Length = GenMT->Exp(RadiationLength(P));
				double Cover = 0;

				while (IsDetectable(P) && !IsDecayed(P, dStep) && Cover < Length)	//this should quit when particle decays too!
				{
					bool InOut;
					double dx = GenMT->Gaus(dStep, Get("Vertex"));
					double dE = dx * EnergyLoss(P, InOut);	//inside material
					Cover += dx;

					if (InOut)
						LengthIn += dx;
					else
						LengthOut += dx;

					Pos += Step*dx;		//move by dx
					P->SetEnergy(P->Energy() - dE);
					P->SetPosition(Pos);
				}

				int Mult = ceil(pow(P->EnergyKin() * 1e6, 0.18) * 0.15);
				if (Mult > 1)
				{
					++Layer;
					P->SetEnergyKin(P->EnergyKin()/Mult);
				}
			}

			if (GenMT->Rndm() > 1.0/Layer)		//need something better
				P->SetShower(true);
			else P->SetShower(false);

			P->SetTrackIn(LengthIn);
			//P->SetTrackBack(LengthBack);
			P->SetTrackOut(LengthOut);
			P->SetEnergy(iE);			//reset to original energy
			P->SetPosition(Start);		//reset to original position
			break;
		default:
			break;
	}
}

double Tracker::GammaDecay(Particle *P)
{
	double Path = 9.0/7.0 * RadiationLength(P, 0);
	return GenMT->Exp(Path);
}

double Tracker::CriticalEnergy(Particle *P)
{
	Detector::Material Element;

	if (IsInsideLAr(P))
		Element = GetMaterial("TargetLAr");
	else if (IsInsideFGT(P))
		Element = GetMaterial("TargetFGT");
	else
		Element = GetMaterial("TargetOut");

	return CriticalEnergy(Element);
}

double Tracker::CriticalEnergy(Detector::Material Element)	//assuming same for positron and electron
{
	switch (Element)
	{
		case LAr:
			return 0.03284;	//GeV
		case GasAr:
			return 0.03803;	//GeV
		case Fe:
			return 0.02168;	//GeV
		case Pb:
			return 0.00743;	//GeV
		default:
			return 0;
	}
}

double Tracker::RadiationLength(Particle *P, bool Nuclear)
{
	Detector::Material Element;

	if (IsInsideLAr(P))
		Element = GetMaterial("TargetLAr"), Nuclear;
	else if (IsInsideFGT(P))
		Element = GetMaterial("TargetFGT"), Nuclear;
	else
		Element = GetMaterial("TargetOut"), Nuclear;

	return RadiationLength(Element, Nuclear);
}

double Tracker::RadiationLength(Detector::Material Element, bool Nuclear)
{
	if (!Nuclear)
		switch (Element)
		{
			case LAr:
				return 19.55/1.3945 / 100;
			case GasAr:
				return 19.55/0.1020 / 100;
			case Fe:
				return 13.84/7.874 / 100;
			case Pb:
				return 6.37 /11.34 / 100;
			default:
				return 0;
		}
	else
		switch (Element)
		{
			case LAr:
				return 119.7/1.3945 / 100;
			case GasAr:
				return 119.7/0.1020 / 100;
			case Fe:
				return 132.1/7.874 / 100;
			case Pb:
				return 199.6/11.34 / 100;
			default:
				return 0;
		}
}

double Tracker::EnergyLoss(Particle *P, bool &Contained)
{
	if (IsInsideLAr(P))
	{
		Contained = true;
		return BetheLoss(P, GetMaterial("TargetLAr"));
	}
	else if (IsInsideFGT(P))
	{
		Contained = true;
		return BetheLoss(P, GetMaterial("TargetFGT"));
	}
	else
	{
		Contained = false;
		return BetheLoss(P, GetMaterial("TargetOut"));
	}
}

double Tracker::BetheLoss(Particle *P, Material Target)
{
	switch (Target)
	{
		case LAr:
			return Bethe(P, 1.3945, 188.0, 18, 40);
		case GasAr:
			return Bethe(P, 0.1020, 188.0, 18, 40);
		case Fe:
			return Bethe(P, 7.874, 286.0, 26, 56);
		case Pb:
			return Bethe(P, 11.34, 823.0, 82, 207);
		default:
			0;
	}
}
							//I is in eV
double Tracker::Bethe(Particle *P, double Density, double I, int Z, int A)	//GeV/m
{
	double K = 0.307075;		//From PDG MeV mol-1 cm2
	double e2M = Const::fMElectron / P->Mass();
	double Beta2 = pow(P->Beta(), 2);
	double Gamma2 = pow(P->Gamma(), 2);
			//electron mass in MeV -> *1000
	double Wmax = (2000 * Const::fMElectron * Beta2 * Gamma2) / 
		(1 + 2 * P->Gamma() * e2M + e2M * e2M);

	double LogArg = 2000 * Const::fMElectron * Beta2 * Gamma2 * Wmax /
		(1e-12 * I * I); 	//Everything in MeV

	return 0.1 * Density * K * Z / (A * Beta2) * (0.5 * log (LogArg) - Beta2);	//stopping power in GeV/m (0.1*)
}

bool Tracker::IsDecayed(Particle *P, double dx)	//Threshold check
{
	return GenMT->Rndm() > exp(-dx/(Const::fC * P->LabSpace()));	//this should quit when particle decays too!
}

bool Tracker::IsDetectable(Particle *P)	//Threshold check
{
	double Threshold = 0.0;

	switch (abs(P->Pdg()))
	{
		case 11:
		case 22:
			Threshold = Get("Thres_Gamma");
			break;
		case 13:
			Threshold = Get("Thres_Muon");
			break;
		case 211:
			Threshold = Get("Thres_Pion");
			break;
		default:
			if (P->Charge() != 0)
				Threshold = Get("Thres_Hadron");
			else
				Threshold = 2 * P->EnergyKin();		//not detectable
			break;
	}

	return (P->EnergyKin() > Threshold);
}

void Tracker::Pi0Decay(Particle *Pi0, Particle *&PA, Particle *&PB)
{
	//in rest frame
	double M_Pion0 = Const::fMPion0;

	delete PA, PB;
	PA = 0, PB = 0;

	TrackVertex(Pi0);
	TVector3 vBoost(Pi0->FourVector().BoostVector());
	TVector3 Start(Pi0->Position());		//starting point is vertex

	TLorentzVector GammaA(0, 0,  M_Pion0/2.0, M_Pion0/2.0); 
	TLorentzVector GammaB(0, 0, -M_Pion0/2.0, M_Pion0/2.0); 
	double Theta = GenMT->Uniform(-Const::fPi, Const::fPi);
	double Phi   = GenMT->Uniform(-Const::fPi, Const::fPi);
	GammaA.SetTheta(Theta);
	GammaB.SetTheta(Theta + Const::fPi);
	GammaA.SetPhi(Phi);
	GammaB.SetPhi(Phi + Const::fPi);
	GammaA.Boost(vBoost);
	GammaB.Boost(vBoost);

	PA = new Particle(22, GammaA, Start);	//here are the photons
	PB = new Particle(22, GammaB, Start);	//position should be different

	TVector3 MoveA(GammaA.Vect().Unit());
	TVector3 MoveB(GammaB.Vect().Unit());
	MoveA *= GammaDecay(PA);
	MoveB *= GammaDecay(PB);
	MoveA += Start;
	MoveB += Start;

	PA->SetPosition(MoveA);
	PB->SetPosition(MoveB);
}

void Tracker::Focus(Particle *P)
{
	double Radius = sqrt(pow(Xsize(), 2) + pow(Ysize(), 2));
	double SigmaT = atan2(Radius, Get("Baseline"));	//3sigma will be inside the detector (better distribution needed)

	P->SetTheta( abs(GenMT->Gaus(0, SigmaT)) );	
	P->SetPhi( GenMT->Uniform(-Const::fPi, Const::fPi) );
}
