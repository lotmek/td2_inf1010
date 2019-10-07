/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "membre.h"

//a changer
Membre::Membre() :
	nom_(""),
	typeMembre_(TypeMembre::Membre_Regulier)
{
}

//a changer
Membre::Membre(const string& nom, TypeMembre typeMembre) :
	nom_(nom),
	typeMembre_(typeMembre)
{
}

//a changer
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_),
	typeMembre_(membre.typeMembre_)
{
	for (int i = 0; i < membre.billets_.size(); ++i) {
		string dateVol = "";				// !!!!!!!!!!!!!!!!!!!!!!! C'est juste pour BIllet Regulier que dateVol change de valeur
		//BilletRegulier * billetReg = static_cast<BilletRegulier*>(membre.billets_[i]);		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//if (billets_[i]->getTypeBillet() != Billet_Base)  //Cette Ligne n'a aucun sens, c'est juste billet_Regulier qui a un dateVol.
		if (billets_[i]->getTypeBillet() == Billet_Regulier) {
			BilletRegulier * billetReg = static_cast<BilletRegulier*>(membre.billets_[i]);
			dateVol = billetReg->getDateVol();
		}
		ajouterBillet(membre.billets_[i]->getPnr(), membre.billets_[i]->getPrix(), membre.billets_[i]->getOd(), membre.billets_[i]->getTarif(), membre.billets_[i]->getTypeBillet(), dateVol);

	}
}

Membre::~Membre()
{
	for (int i = 0; i < billets_.size(); i++) {
		delete billets_[i];
	}
}

string Membre::getNom() const
{
	return nom_;
}

TypeMembre Membre::getTypeMembre() const
{
	return typeMembre_;
}

vector<Billet*> Membre::getBillets() const
{
	return billets_;
}


void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

void Membre::utiliserBillet(const string& pnr)
{
	for (int i = 0; i < billets_.size(); ++i) {
		if (billets_[i]->getPnr() == pnr) {
			if(billets_[i]->getTypeBillet() == TypeBillet::Flight_Pass){
				FlightPass* flightpass = static_cast<FlightPass*>(billets_[i]);
				flightpass->decrementeNbUtilisations();
				if (flightpass->getNbUtilisationsRestante() == 0) {
					delete billets_[i];
					billets_[i] = billets_[billets_.size()-1];
					billets_.pop_back();
				}
			}

			else {
				delete billets_[i];						//Ici on avait enlever le dernier élément, mais on chercher un billet précis!!!!!!
				billets_[i] = billets_[billets_.size() - 1];		
				billets_.pop_back();
			}
		}
		else
			cout << "Le billet n'a pas pu etre trouve dans la liste.\n";
	}
}

// a changer
void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
{
	Billet* billet = new Billet(pnr, nom_, prix, od, tarif, typeBillet);
	FlightPass* flightpass = new FlightPass(pnr, nom_, prix, od, tarif, typeBillet);
	BilletRegulier* billetReg = new BilletRegulier(pnr, nom_, prix, od, tarif, dateVol, typeBillet);
	switch (typeBillet) {
		case TypeBillet::Billet_Base : 
			billets_.push_back(billet);
			delete flightpass;
			delete billetReg;
			break;
		case TypeBillet::Billet_Regulier :
			billetReg->setDateVol(dateVol);
			billets_.push_back(billetReg);
			delete billet;
			delete flightpass;
			break;
		case TypeBillet::Flight_Pass:
			billets_.push_back(flightpass);
			delete billet;
			delete billetReg;
			break;
	}

	//inutile, cette classe ne fait pas partie du programme de fidèlité.
	//modifierPoints(calculerPoints(billet));
}



bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}

bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}

Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;
		typeMembre_ = membre.typeMembre_;


		for (int i = 0; i < billets_.size(); ++i) {
			delete billets_[i];
		}

		billets_.clear();

		for (int i = 0; i < membre.billets_.size(); i++) {
			billets_.push_back(new Billet(*membre.billets_[i]));
		}
	}

	return *this;
}

// a changer
void Membre::afficherMembre() const {
	cout << setfill(' ');
	cout << "- Membre " << nom_ << ":" << endl;
	cout << "\t- Billets :" << endl;
	for (int i = 0; i < billets_.size(); i++) {
		if (billets_[i]->getTypeBillet() == Billet_Regulier) {
			BilletRegulier * billetReg = static_cast<BilletRegulier*>(billets_[i]);
			cout << *billetReg;
		}

		else if (billets_[i]->getTypeBillet() == Flight_Pass) {
			FlightPass * fp = static_cast<FlightPass*>(billets_[i]);
			cout << *fp;
		}

		else
			cout << *billets_[i];
	}

	cout << endl;
}

ostream& operator<<(ostream& o, const Membre& membre)
{
	membre.afficherMembre();

	return o;

}
