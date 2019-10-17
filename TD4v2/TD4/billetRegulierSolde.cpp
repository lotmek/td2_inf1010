/*
* Titre : billetRegulierSolde.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "billetRegulierSolde.h"

// TODO
BilletRegulierSolde::BilletRegulierSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol, double pourcentageSolde)
	:BilletRegulier(pnr, prix, od, tarif, dateVol),
	Solde(pourcentageSolde)
{
}

// TODO
double BilletRegulierSolde::getPrix() const
{
	return (1-pourcentageSolde_) * prix_;
}

// TODO
double BilletRegulierSolde::getPrixBase() const
{
	return prix_;
}

// TODO
BilletRegulierSolde* BilletRegulierSolde::clone()
{
	return new BilletRegulierSolde(pnr_, prix_, od_, tarif_, dateVol_, pourcentageSolde_);
}

// TODO
void BilletRegulierSolde::afficher(ostream& o)
{
	BilletRegulier::afficher(o);
	o << "\t\t\t" << setw(11) << "- Pourcentage solde" << ": " << pourcentageSolde_ <<"%" << endl;
}