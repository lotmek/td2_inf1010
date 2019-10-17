/*
* Titre : billetRegulier.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "billetRegulier.h"

BilletRegulier::BilletRegulier(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol) : 
	Billet(pnr, prix, od, tarif), dateVol_(dateVol)
{
}

string BilletRegulier::getDateVol() const
{
	return dateVol_;
}

void BilletRegulier::setDateVol(string dateVol)
{
	dateVol_ = dateVol;
}

// TODO
BilletRegulier* BilletRegulier::clone()
{
	return new BilletRegulier(pnr_, prix_, od_, tarif_, dateVol_);
}

// TODO
void BilletRegulier::afficher(ostream& o)
{
	Billet::afficher(o);
	o << "\t\t\t" << setw(11) << "- Vol le" << ": " << dateVol_ << endl;
}