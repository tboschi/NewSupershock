/* 
 * unpolarised amplitudes for processes involving N
 * also other util procedures for derived classes
 * and definition of decay width from unpolarised amplitude
 */

#include "Amplitude.h"

Amplitude::Amplitude()	: //Decay rates calculator
	M_Neutrino(0.0),
	M_Photon(0.0),
	M_Electron(Const::fMElectron),
	M_Muon(Const::fMMuon),
	M_Pion(Const::fMPion),
	M_Pion0(Const::fMPion0),
	M_Kaon(Const::fMKaon),
	M_Kaon0(Const::fMKaon0),
	M_Eta(Const::fMEta),
        M_Rho(Const::fMRho),
        M_Rho0(Const::fMRho0),
        M_Omega(Const::fMOmega),
        M_Kaonx(Const::fMKaonx),
        M_Etai(Const::fMEtai),
        M_Phi(Const::fMPhi),
        M_Tau(Const::fMTau),
        M_Charm(Const::fMCharm),
        M_CharmS(Const::fMDs)
{
	M_Sterile_prev = -1.0;
	Channel_prev = _undefined;
}

void Amplitude::LoadMap()
{
	chMap[_undefined] = "undefined";	//0
	chMap[_ALL]    = "ALL";			//1

	//decay channels
	chMap[_nnn]    = "nnn";			//2
	chMap[_nGAMMA] = "nGAMMA";
	chMap[_nEE]    = "nEE";
	chMap[_nEM]    = "nEM";
	chMap[_nME]    = "nME";
	chMap[_nMM]    = "nMM";
	chMap[_nET]    = "nET";
	chMap[_nTE]    = "nTE";
	chMap[_nMT]    = "nMT";
	chMap[_nTM]    = "nTM";
	chMap[_nPI0]   = "nPI0";
	chMap[_EPI]    = "EPI";
	chMap[_MPI]    = "MPI";
	chMap[_TPI]    = "TPI";
	chMap[_EKA]    = "EKA";
	chMap[_MKA]    = "MKA";
	chMap[_nRHO0]  = "nRHO0";
	chMap[_ERHO]   = "ERHO";
	chMap[_MRHO]   = "MRHO";
	chMap[_EKAx]   = "EKAx";
	chMap[_MKAx]   = "MKAx";
	chMap[_nOMEGA] = "nOMEGA";
	chMap[_nETA]   = "nETA";
	chMap[_nETAi]  = "nETAi";
	chMap[_nPHI]   = "nPHI";
	chMap[_ECHARM] = "ECHARM";
	chMap[_ExpALL] = "ExpALL";

	//production channels
	chMap[_MuonE]   = "MuonE";		//29
	chMap[_MuonM]   = "MuonM";
	chMap[_TauEE]   = "TauEE";
	chMap[_TauET]   = "TauET";
	chMap[_TauMM]   = "TauMM";
	chMap[_TauMT]   = "TauMT";
	chMap[_TauPion] = "TauPion";
	chMap[_PionE]   = "PionE";
	chMap[_PionM]   = "PionM";
	chMap[_KaonE]   = "KaonE";
	chMap[_KaonM]   = "KaonM";
	chMap[_CharmE]  = "CharmE";
	chMap[_CharmM]  = "CharmM";
	chMap[_CharmT]  = "CharmT";
	chMap[_Kaon0E]  = "Kaon0E";
	chMap[_Kaon0M]  = "Kaon0M";
	chMap[_KaonCE]  = "KaonCE";
	chMap[_KaonCM]  = "KaonCM";
}

std::string Amplitude::ShowChannel(Channel Name)
{
	if (chMap.size() == 0)
		LoadMap();

	return chMap[Name];
}

void Amplitude::LoadMass(Channel Name)
{
	vMass.clear();
	switch(Name)
	{
		//masses in ascending order
		case _ALL:
		case _nnn:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Neutrino);
			vPdg.push_back(12);
			vPdg.push_back(12);
			vPdg.push_back(12);
			break;
		case _nGAMMA:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Photon);
			vPdg.push_back(12);
			vPdg.push_back(22);
			break;
		case _nEE:
		case _ExpALL:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Electron);
			vMass.push_back(M_Electron);
			vPdg.push_back(12);
			vPdg.push_back(11);
			vPdg.push_back(11);
			break;
		case _nEM:
		case _nME:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Electron);
			vMass.push_back(M_Muon);
			vPdg.push_back(12);
			vPdg.push_back(11);
			vPdg.push_back(13);
			break;
		case _nMM:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Muon);
			vMass.push_back(M_Muon);
			vPdg.push_back(12);
			vPdg.push_back(13);
			vPdg.push_back(13);
			break;
		case _nET:
		case _nTE:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Electron);
			vMass.push_back(M_Tau);
			vPdg.push_back(12);
			vPdg.push_back(11);
			vPdg.push_back(15);
			break;
		case _nMT:
		case _nTM:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Muon);
			vMass.push_back(M_Tau);
			vPdg.push_back(12);
			vPdg.push_back(13);
			vPdg.push_back(15);
			break;
		case _nPI0:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Pion0);
			vPdg.push_back(12);
			vPdg.push_back(111);
			break;
		case _EPI:
			vMass.push_back(M_Electron);
			vMass.push_back(M_Pion);
			vPdg.push_back(11);
			vPdg.push_back(211);
			break;
		case _MPI:
			vMass.push_back(M_Muon);
			vMass.push_back(M_Pion);
			vPdg.push_back(13);
			vPdg.push_back(211);
			break;
		case _TPI:
			vMass.push_back(M_Pion);
			vMass.push_back(M_Tau);
			vPdg.push_back(211);
			vPdg.push_back(15);
			break;
		case _EKA:
			vMass.push_back(M_Electron);
			vMass.push_back(M_Kaon);
			vPdg.push_back(11);
			vPdg.push_back(321);
			break;
		case _MKA:
			vMass.push_back(M_Muon);
			vMass.push_back(M_Kaon);
			vPdg.push_back(13);
			vPdg.push_back(321);
			break;
		case _EKAx:
			vMass.push_back(M_Electron);
			vMass.push_back(M_Kaonx);
			vPdg.push_back(11);
			vPdg.push_back(9000321);
			break;
		case _MKAx:
			vMass.push_back(M_Muon);
			vMass.push_back(M_Kaonx);
			vPdg.push_back(13);
			vPdg.push_back(9000321);
			break;
		case _nRHO0:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Rho0);
			vPdg.push_back(12);
			vPdg.push_back(113);
			break;
		case _ERHO:
			vMass.push_back(M_Electron);
			vMass.push_back(M_Rho);
			vPdg.push_back(11);
			vPdg.push_back(213);
			break;
		case _MRHO:
			vMass.push_back(M_Muon);
			vMass.push_back(M_Rho0);
			vPdg.push_back(13);
			vPdg.push_back(213);
			break;
			break;
		case _nETA:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Eta);
			vPdg.push_back(12);
			vPdg.push_back(221);
			break;
		case _nETAi:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Etai);
			vPdg.push_back(12);
			vPdg.push_back(331);
			break;
		case _nOMEGA:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Omega);
			vPdg.push_back(12);
			vPdg.push_back(223);
			break;
		case _nPHI:
			vMass.push_back(M_Neutrino);
			vMass.push_back(M_Phi);
			vPdg.push_back(12);
			vPdg.push_back(333);
			break;
		case _ECHARM:
			vMass.push_back(M_Electron);
			vMass.push_back(M_Charm);
			vPdg.push_back(12);
			vPdg.push_back(411);
			break;

		//Parent first, then in ascending order
		case _MuonE:
		case _MuonM:
			vMass.push_back(M_Muon);
			vMass.push_back(M_Electron);
			vMass.push_back(M_Neutrino);
			vPdg.push_back(13);
			vPdg.push_back(11);
			vPdg.push_back(12);
			break;
		case _TauEE:
		case _TauET:
			vMass.push_back(M_Tau);
			vMass.push_back(M_Electron);
			vMass.push_back(M_Neutrino);
			vPdg.push_back(15);
			vPdg.push_back(11);
			vPdg.push_back(12);
			break;
		case _TauMM:
		case _TauMT:
			vMass.push_back(M_Tau);
			vMass.push_back(M_Muon);
			vMass.push_back(M_Neutrino);
			vPdg.push_back(15);
			vPdg.push_back(13);
			vPdg.push_back(12);
			break;
		case _TauPion:
			vMass.push_back(M_Tau);
			vMass.push_back(M_Pion);
			vPdg.push_back(15);
			vPdg.push_back(211);
			break;
		case _PionE:
			vMass.push_back(M_Pion);
			vMass.push_back(M_Electron);
			vPdg.push_back(211);
			vPdg.push_back(11);
			break;
		case _PionM:
			vMass.push_back(M_Pion);
			vMass.push_back(M_Muon);
			vPdg.push_back(211);
			vPdg.push_back(13);
			break;
		case _KaonE:
			vMass.push_back(M_Kaon);
			vMass.push_back(M_Electron);
			vPdg.push_back(321);
			vPdg.push_back(11);
			break;
		case _KaonM:
			vMass.push_back(M_Kaon);
			vMass.push_back(M_Muon);
			vPdg.push_back(321);
			vPdg.push_back(13);
			break;
		case _CharmE:
			vMass.push_back(M_CharmS);
			vMass.push_back(M_Electron);
			vPdg.push_back(431);
			vPdg.push_back(11);
			break;
		case _CharmM:
			vMass.push_back(M_CharmS);
			vMass.push_back(M_Muon);
			vPdg.push_back(431);
			vPdg.push_back(13);
			break;
		case _CharmT:
			vMass.push_back(M_CharmS);
			vMass.push_back(M_Tau);
			vPdg.push_back(431);
			vPdg.push_back(15);
			break;
		case _Kaon0E:
			vMass.push_back(M_Kaon0);
			vMass.push_back(M_Pion);
			vMass.push_back(M_Electron);
			vPdg.push_back(130);
			vPdg.push_back(211);
			vPdg.push_back(11);
			break;
		case _Kaon0M:
			vMass.push_back(M_Kaon0);
			vMass.push_back(M_Pion);
			vMass.push_back(M_Muon);
			vPdg.push_back(130);
			vPdg.push_back(211);
			vPdg.push_back(13);
			break;
		case _KaonCE:
			vMass.push_back(M_Kaon);
			vMass.push_back(M_Pion0);
			vMass.push_back(M_Electron);
			vPdg.push_back(321);
			vPdg.push_back(111);
			vPdg.push_back(11);
			break;
		case _KaonCM:
			vMass.push_back(M_Kaon);
			vMass.push_back(M_Pion0);
			vMass.push_back(M_Muon);
			vPdg.push_back(321);
			vPdg.push_back(111);
			vPdg.push_back(13);
			break;
		default:
			std::cerr << ShowChannel(Name) << " : Channel not recognised" << std::endl;
			break;
	}
}

//Kinematic function
double Amplitude::Kallen(double X, double Y, double Z)
{
	return X*X + Y*Y + Z*Z - 2*(X*Y + X*Z + Y*Z);
}

double Amplitude::SqrtKallen(double X, double Y, double Z)
{
	double Kal = Kallen(X, Y, Z);
	if (Kal < 0)
		return sqrt(-Kal);
	else
		return sqrt(Kal);
}

/////////////////////
//Diff decay widths//
////////////////////

//	to be integrated over ds/m0², dt/m0², da, dcosb, dc
//	ds = -2M dE
double Amplitude::dGammad5_3B(double M2)
{
	//return M2 / (512 * Const::fPi3 * Const::fPi2 * GetMass());
	return M2 * Mass() / (512 * Const::fPi3 * Const::fPi2);	//integration over dsigma dtau
}

//	after integrating angular depend., to be integrated over ds, dt
double Amplitude::dGammad2_3B(double M2)
{
	return 8 * Const::fPi2 * dGammad5_3B(M2);
}

//	to be integrated over da, dcosb		(m1/m0)²  (m2/m0)²
double Amplitude::dGammad2_2B(double M2, double x, double y)
{
	return M2 * SqrtKallen(1, x, y) / (64 * Const::fPi2 * Mass());
}

//	constant, after integrating angular depend.
double Amplitude::dGammad0_2B(double M2, double x, double y)
{
	return 4 * Const::fPi * dGammad2_2B(M2, x, y);
}

//integration limits for three body when is constant wrt to t
double Amplitude::Limit(double &s, double x, double y, double z)
{
	double t = 0;
	return Limit(s, t, x, y, z);
}

//integration limits for three body, where z refers to s, y referst to t, and x refers to u
double Amplitude::Limit(double &s, double &t, double x, double y, double z)
{
	double s0 = s;
	double sInf = x + y + 2*sqrt(x*y);
	double sSup = 1 + z - 2*sqrt(z);
	s = sInf + (sSup - sInf) * s;	//this is s

	double Kal = SqrtKallen(s, y, x) * SqrtKallen(1, s, z);
	double tInf = z + x + ((1 - s - z) * (s - y + x) - Kal) / (2 * s);
	double tSup = z + x + ((1 - s - z) * (s - y + x) + Kal) / (2 * s);
	t = tInf + (tSup - tInf) * t;	//this is t

	return (sSup - sInf) * (tSup - tInf);
}

//////////////////////
//Generic amplitudes//	//check prefactors!
//////////////////////

//					lepton		meson	angle
double Amplitude::M2_LeptonPseudoMeson(double x, double y, double cos0)
{
	return Const::fGF2 * Mass(4) * 
		(pow(1 - x, 2) - y * (1 + x) - (1 - x) * Helicity() * SqrtKallen(1, x, y) * cos0);
}

//					neutrino	meson	angle
double Amplitude::M2_NeutrinoPseudoMeson(double x, double y, double cos0)
{
	return M2_LeptonPseudoMeson(x, y, cos0) / 2.0;
}

//					lepton		meson	angle
double Amplitude::M2_LeptonVectorMeson(double x, double y, double cos0)	//must be divided by vector meson mass
{
	return Const::fGF2 * Mass(4) * 
		(pow(1 - x, 2) + y * (1 + x) - 2*y - (1 - x - 2*y) *  Helicity() * SqrtKallen(1, x, y) * cos0);
}

//					lepton		meson	angle
double Amplitude::M2_NeutrinoVectorMeson(double x, double y, double cos0)
{
	return M2_LeptonVectorMeson(x, y, cos0) / 2.0;
}

//			lepton energy is s = (p0-p2)² and cos0s the angle wrt z-axis
//			       neutrino, letpon,   lepton
double Amplitude::M2_WW(double x, double y, double z, double s, double cos0)	//gL^2 + gR^2
{
	return 16 * Const::fGF2 * Mass(4) *
	       (s - x - y) * (1 + z - s - Helicity() * SqrtKallen(1, z, s) * cos0);
}

//			lepton energies are s = (p0-p2)², t = (p0-p3)² and cos0s,t the angles wrt z-axis
//			       neutrino, letpon,   lepton
double Amplitude::M2_WZ(double x, double y, double z, double s, double t, double cos0s, double cos0t)	//2gL*gR
{
	double u = 1 + x + y + z - s - t;
	double cos0u = (SqrtKallen(1, y, s) * cos0s + SqrtKallen(1, z, t) * cos0t) / 
			SqrtKallen(1, x, u) ;

	return M2_WZ(x, y, z, u, cos0u);
}

//			lepton energiy is u = (p0-p1)² and cos0u the angle wrt z-axis
//			       neutrino, letpon,   lepton
double Amplitude::M2_WZ(double x, double y, double z, double u, double cos0u)	//2gL*gR
{
	return 16 * Const::fGF2 * Mass(4) *
		sqrt(y * z) * (1 + x - u - Helicity() * SqrtKallen(1, x, u) * cos0u);
}

//
//////////////
//production//
//////////////
//
//		This amplitude is to be used if the mixing comes from the decaying flavour
//		   production is from lepton, described in Jackson Frame!
//				           neutrino  lepton    neutrino
double Amplitude::M2_LeptonNeutrino(double x, double y, double z, double u)
{
	return 16 * Const::fGF2 * Mass(4) *
		(1 + x - u) * (u - y - z - Helicity() * SqrtKallen(u, y, z));
}

//	This amplitude is to be used if the mixing comes from the flavour in final state
//				     neutrino  lepton    neutrino  neutrino  angle betw. lepton and neutr
//	production is from antilepeton
double Amplitude::M2_AntiLeptonNeutrino(double x, double y, double z, double s)
{
	return 16 * Const::fGF2 * Mass(4) * 
		(s - x - y) * (1 + z - s - Helicity() * SqrtKallen(1, s, z));
}

//					      neutrino	meson
double Amplitude::M2_LeptonMeson(double x, double y)	//y is the meson
{
	return Const::fGF2 * Mass(4) * 
		(pow(1 - x, 2) - y * (1 + x) - (1 - x) * Helicity() * SqrtKallen(1, x, y));
}

//					   neutrino  lepton
double Amplitude::M2_MesonTwo(double x, double y)
{
	return Const::fGF2 * Mass(4) * 
		(x + y - pow(x - y, 2) - Helicity() * (y - x) * SqrtKallen(1, x, y));
}

//Jackson frame??
double Amplitude::M2_MesonThree(double s, double t, double x, double y, double z, double L_, double L0)
{
	double u = 1 + x + y + z - s - t;

	double F = 2 * (1 + L_ * u / x);
	double G = (1 + L_ * u / x) - (L_ - L0) * (1 + 1 / x);

	double A = (1 + y - t)*(1 + z - s - Helicity() * SqrtKallen(1, z, s)) -
	           (u - y - z - Helicity() * SqrtKallen(u, y, z));
	double B = (y + z) * (u - y - z) + 4 * y * z -
	           (y - z) * Helicity() * SqrtKallen(u, y, z);
	double C = (1 + y - t) * 2*z + (1 + z - s) * (2*y + Helicity() * SqrtKallen(u, y, z)) -
		   Helicity() * (u - z + y) * SqrtKallen(1, z, s);

	return Const::fGF2 * ( (F*F) * A + (G*G) * B - (F*G) * C ) / 2.0;
}

//Generic function set up for template analysis
//
void Amplitude::SetFunction(double (Amplitude::*FF)(const double))
{
	fFunction = FF;
}

void Amplitude::SetFunction_D(double (Amplitude::*FF)(const double*))
{
	fFunction_D = FF;
}

double Amplitude::Function(const double x)
{
	return (this->*fFunction)(x);
}

double Amplitude::Function_D(const double *x)
{
	return (this->*fFunction_D)(x);
}

bool Amplitude::IsChanged()
{
	bool Ret = (fabs(MassN() - M_Sterile_prev) > 1e-9) ||
		   (Helicity() != iHel_prev);

	M_Sterile_prev = MassN();
	iHel_prev = Helicity();

	//Reset decay widths if changed
	if (Ret)
		Reset();

	return Ret;
}

//Get functions
double Amplitude::Mass(int E)		//decaying particle mass
{
	return pow(M_Parent, E);
}

double Amplitude::MassN(int E)		//neutrino mass
{
	return pow(M_Sterile, E);
}

double Amplitude::Ue(int E)
{
	return pow(fUe, E);
}

double Amplitude::Um(int E)
{
	return pow(fUm, E);
}

double Amplitude::Ut(int E)
{
	return pow(fUt, E);
}

int Amplitude::Helicity()
{
	return iHel;
}

bool Amplitude::GetFermion()
{
	return bFermion;
}

bool Amplitude::GetParticle()
{
	return bParticle;
}

//Set functions
void Amplitude::SetMass(double Mass)		//mass of decaying particle
{
	M_Parent = Mass;
}

void Amplitude::SetMassN(double Mass)		//mass of neutrino
{
	M_Sterile = Mass;
}

void Amplitude::SetUe(double Ue)
{
	fUe = Ue;
}

void Amplitude::SetUm(double Um)
{
	fUm = Um;
}

void Amplitude::SetUt(double Ut)
{
	fUt = Ut;
}

void Amplitude::SetFermion(bool Fermion)
{
	bFermion = Fermion;	//true for Dirac, false for Majorana
}

void Amplitude::SetParticle(bool Particle)
{
	bParticle = Particle;	//true for Dirac, false for Majorana
}

void Amplitude::SetHelicity(int Helicity)
{
	iHel = Helicity;	//-1 for Left, +1 for Right, 0 for unpolarised
}

void Amplitude::SetNeutrino(double Mass, double* Mixings, bool Fermion, bool Particle, int Helix)
{
	SetMassN(Mass);
	SetUe(Mixings[0]);
	SetUm(Mixings[1]);
	SetUt(Mixings[2]);
	SetFermion(Fermion);
	SetParticle(Particle);
	SetHelicity(Helix);
}


/*
double Amplitude::Gauss_V()
{
	CC = 0;
	int Trial, Fail;
	double Error, Chi2Prob;
	SetFunction_D(&Amplitude::Gauss_D);
	double Ret =  Inte::VegasIntegration(this, 2, Trial, Fail, Error, Chi2Prob);
	return Ret;
}

double Amplitude::Gauss_D(const double *p)
{
	const double x = p[0]; 
	const double y = p[0]; 
	return Gauss_xy(x, y);
}

double Amplitude::Gauss_B()
{
	CC = 0;
	SetFunction(&Amplitude::Gauss_x);
	double Ret = Inte::BooleIntegration(this);

	return Ret;
}

double Amplitude::Gauss_x(const double x)
{
	F_var.push_back(x);
	SetFunction(&Amplitude::Gauss_y);

	double Ret = Inte::BooleIntegration(this);
	SetFunction(&Amplitude::Gauss_x);
	F_var.pop_back();

	return Ret;
}

double Amplitude::Gauss_y(const double y)
{
	double x_ = F_var.at(0);
	double y_ = y;
	return Gauss_xy(x_, y_);
}

double Amplitude::Gauss_xy(const double x, const double y)
{
	++CC;
	double x_ = -1 + 2*(fabs(x-1e-9)); 
	double y_ = -sqrt(1-x_*x_) + 2*sqrt(1-x_*x_)*y; 
	//double y_ = -1 + 2*y;

	return 2 * 2*sqrt(1-x_*x_) * 1;
	//return 4 * exp(-x_*x_ - y_*y_);
}
*/