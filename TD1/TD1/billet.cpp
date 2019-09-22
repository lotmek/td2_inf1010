
#include "billet.h"

Billet::Billet() 
{
	pnr_ = "000000000";
	nomPassager_ = "aucun nom";
	prix_ = 0.0;
	od_ = "terre - lune";
	tarif_ = TarifBillet::Economie;
	dateVol_ = "21 decembre 2012";
}

Billet::Billet(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol)
{
	pnr_ = pnr;
	nomPassager_ = nomPassager;
	prix_ = prix;
	od_ = od;
	tarif_ = tarif;
	dateVol_ = dateVol;
}

Billet::~Billet(){}

// Getters
string Billet::getPnr()
{
	return pnr_;
}

string Billet::getNomPassager()
{
	return nomPassager_;
}

double Billet::getPrix()
{
	return prix_;
}

string Billet::getOd()
{
	return od_;
}

TarifBillet Billet::getTarif()
{
	return tarif_;
}

string Billet::getDateVol()
{
	return dateVol_;
}

// Setters
void Billet::setPnr(const string& pnr)
{
	pnr_ = pnr;
}
 
void Billet::setNomPassager(const string& nomPassager)
{
	nomPassager_ = nomPassager;
}

void Billet::setPrix(double prix)
{
	prix_ = prix;
}

void Billet::setOd(const string& od)
{
	od_ = od;
}

void Billet::setTarif(TarifBillet tarif)
{
	tarif_ = tarif;
}
void Billet::setDateVol(const string& dateVol) 
{
	dateVol_ = dateVol;
}

//formatTarif
string Billet::formatTarif(TarifBillet tarif)
{
	switch (tarif) {
		case TarifBillet::Economie: return "Economie"; break;
		case TarifBillet::PremiumEconomie: return "Premium economie"; break;
		case TarifBillet::Affaire: return "Affaire"; break;
		case TarifBillet::Premiere: return "Premiere"; break;
	}
}

//Méthode d'affichage
void Billet::afficherBillet() 
{
	cout << "\t- Billet " << pnr_ << " (Classe : " << formatTarif(tarif_) << ")\n"
		<< "\t\t- Passager : " << nomPassager_ << "\n"
		<< "\t\t- Prix     : " << prix_ << "$\n"
		<< "\t\t- Trajet   : " << od_ << "\n"
		<< "\t\t- Vol le   : " << dateVol_ << "\n|"
		<< endl;
}