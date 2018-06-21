/*
 * Decay rate simplifier for a three body decay of muon and kaon(0)
 * Author: Tommaso Boschi
 */

#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>

#include "Physics/Amplitude.h"
#include "cuba.h"

class Production : public Amplitude
{
	public:
		Production();

		Amplitude::Channel FindChannel(std::string Name);
		std::vector<std::string> ListChannel();

		bool IsAllowed(Channel Name);
		double Gamma(Channel Name);
		double Scale(Channel Name);

		double Total();
		double MuonE();
                double MuonM();
                double TauEE();
                double TauET();
                double TauMM();
                double TauMT();
		double TauPion();
                double PionE();
                double PionM();
                double KaonE();
                double KaonM();
                double CharmE();
                double CharmM();
                double CharmT();
                double Kaon0E();
                double Kaon0M();
		double KaonCE();
                double KaonCM();

		double AntiLeptonNeutrinoDecay(double M_LeptonA, double M_LeptonB, double M_Neut);
		double I_AntiLeptonNeutrino(double x, double y, double z);
		double I_AntiLeptonNeutrino_s(const double s);

		double LeptonNeutrinoDecay(double M_LeptonA, double M_LeptonB, double M_Neutrino);
		double I_LeptonNeutrino(double x, double y, double z);
		double I_LeptonNeutrino_u(const double u);

		double LeptonMesonDecay(double M_Lepton, double M_Meson);
		double I_LeptonMeson(double x, double y);

		double MesonTwoDecay(double M_Meson, double M_Lepton);
		double I_MesonTwo(double x, double y);

		double MesonThreeDecay(double M_Meson0, double M_Meson1, double M_Lepton, double L_, double L0);
		double I_MesonThree(double x, double y, double z, double L_, double L0);
		double I_MesonThree_s(const double s);
		double I_MesonThree_t(const double t);
		double I_MesonThree_D(const double *x);

		void Reset();
		void SetFunction(double (Production::*FF)(const double));
		void SetFunction_D(double (Production::*FF)(const double*));

	private:

		double fMuonE,
                       fMuonM,
                       fTauEE,
                       fTauET,
                       fTauMM,
                       fTauMT,
		       fTauPion,
                       fPionE,
                       fPionM,
                       fKaonE,
                       fKaonM,
                       fCharmE,
                       fCharmM,
                       fCharmT,
                       fKaon0E,
                       fKaon0M,
                       fKaonCE,
                       fKaonCM;
};

#endif