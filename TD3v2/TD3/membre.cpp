/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: membre.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
#include "membre.h"

//a changer

 /****************************************************************************
  * Fonction:	Membre::Membre
  * Description: Constructeur par défaut.
  * Paramètres:	aucun
  * Retour:		aucun
  ****************************************************************************/
Membre::Membre() :
	nom_(""),
	typeMembre_(TypeMembre::Membre_Regulier)
{
}

//a changer

/****************************************************************************
 * Fonction:	Membre::Membre
 * Description: Constructeur par paramètres.
 * Paramètres:	(const string&) nom, (TypeMembre) typeMembre
 * Retour:		aucun
 ****************************************************************************/
Membre::Membre(const string& nom, TypeMembre typeMembre) :
	nom_(nom),
	typeMembre_(typeMembre)
{
}

//a changer

/****************************************************************************
 * Fonction:	Membre::Membre(
 * Description: Constructeur par copie.
 * Paramètres:	(const Membre&) copieMembre
 * Retour:		aucun
 ****************************************************************************/
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_),
	typeMembre_(membre.typeMembre_)
{
	for (unsigned i = 0; i < membre.billets_.size(); ++i) {
		string dateVol = "";			
		if (billets_[i]->getTypeBillet() == Billet_Regulier) {
			BilletRegulier * billetReg = static_cast<BilletRegulier*>(membre.billets_[i]);
			dateVol = billetReg->getDateVol();
		}
		ajouterBillet(membre.billets_[i]->getPnr(), membre.billets_[i]->getPrix(), membre.billets_[i]->getOd(), membre.billets_[i]->getTarif(), membre.billets_[i]->getTypeBillet(), dateVol);

	}
}


/****************************************************************************
 * Fonction:	Membre::~Membre
 * Description: Destructeur, détruit le membre du système.
 * Paramètres:	aucun
 * Retour:		aucun
 ****************************************************************************/
Membre::~Membre()
{
	for (unsigned i = 0; i < billets_.size(); i++) {
		delete billets_[i];
	}
}


/****************************************************************************
 * Fonction:	Membre::getNom
 * Description: Fournit le nom.
 * Paramètres:	aucun
 * Retour:		(string) Nom du membre
 ****************************************************************************/
string Membre::getNom() const
{
	return nom_;
}

/****************************************************************************
 * Fonction:	Membre::getTypeMembre
 * Description: Fournit le type de membre.
 * Paramètres:	aucun
 * Retour:		(TypeMembre) le type de membre
 ****************************************************************************/
TypeMembre Membre::getTypeMembre() const
{
	return typeMembre_;
}

/****************************************************************************
 * Fonction:	Membre::getBillets
 * Description: Fournit les billets.
 * Paramètres:	aucun
 * Retour:		vector<Billet*> vecteur de billets
 ****************************************************************************/
vector<Billet*> Membre::getBillets() const
{
	return billets_;
}

/****************************************************************************
 * Fonction:	Membre::setNom
 * Description: Modificateur de nom.
 * Paramètres:	(const string& nom)
 * Retour:		aucun
 ****************************************************************************/
void Membre::setNom(const string& nom)
{
	nom_ = nom;
}


/****************************************************************************
 * Fonction:	Membre::utiliserBillet
 * Description:	Retire un billet ou décrémente son nombre d'utilisation si c'est un flightpass.
 * Paramètres:	(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
 * Retour:		aucun
 ****************************************************************************/
void Membre::utiliserBillet(const string& pnr)
{
	for (unsigned i = 0; i < billets_.size(); ++i) {
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
				delete billets_[i];
				billets_[i] = billets_[billets_.size() - 1];		
				billets_.pop_back();
			}
		}
		else
			cout << "Le billet n'a pas pu etre trouve dans la liste.\n";
	}
}

// a changer

/****************************************************************************
 * Fonction:	Membre::ajouterBillet
 * Description:	Ajoute un pointeur billet dans le vecteur.
 * Paramètres:	(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
 * Retour:		aucun
 ****************************************************************************/
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


/****************************************************************************
 * Fonction:	Membre::operator==
 * Description:	Surcharge l'operateur == (operande de gauche est un membre et droite est un string)
 *				Compare les noms.
 * Paramètres:	const string& nomMembre
 * Retour:		bool vrai ou faux
 ****************************************************************************/
bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}

/****************************************************************************
 * Fonction:	friend operator==
 * Description:	Surcharge l'operateur == (operande de gauche est un string et droite est un membre)
 *				Compare les noms.
 * Paramètres:	(const string& nomMembre, const Membre& membre)
 * Retour:		bool vrai ou faux
 ****************************************************************************/
bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}

/****************************************************************************
 * Fonction:	Membre::operator=
 * Description:	Surcharge l'operateur =
 *				Ecrase les attributs d'un membre et les remplace par ceux de l'autre
 * Paramètres:	(const Membre& membre)
 * Retour:		Membre& membre final avec les attributs du membre passé en paramètre
 ****************************************************************************/
Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;
		typeMembre_ = membre.typeMembre_;


		for (unsigned i = 0; i < billets_.size(); ++i) {
			delete billets_[i];
		}

		billets_.clear();

		for (unsigned i = 0; i < membre.billets_.size(); i++) {
			billets_.push_back(new Billet(*membre.billets_[i]));
		}
	}

	return *this;
}

// a changer

/****************************************************************************
 * Fonction:	Membre::afficherMembre
 * Description:	Affiche les informations du membre, dont les billets dépendemment de leurs classes.
 * Paramètres:	aucun
 * Retour:		aucun
 ****************************************************************************/
void Membre::afficherMembre(ostream& o) const {
	o << setfill(' ');
	o << "- Membre " << nom_ << ":" << endl;
	o << "\t- Billets :" << endl;
	for (unsigned i = 0; i < billets_.size(); i++) {
		if (billets_[i]->getTypeBillet() == Billet_Regulier) {
			BilletRegulier * billetReg = static_cast<BilletRegulier*>(billets_[i]);
			o << *billetReg;
		}

		else if (billets_[i]->getTypeBillet() == Flight_Pass) {
			FlightPass * fp = static_cast<FlightPass*>(billets_[i]);
			o << *fp;
		}

		else
			o << *billets_[i];
	}

	o << endl;
}

/****************************************************************************
 * Fonction:	friend operator<<
 * Description:	Surcharge l'operateur <<
 * Paramètres:	(ostream& o, const Membre& membre)
 * Retour:		ostream& affichage
 ****************************************************************************/
ostream& operator<<(ostream& o, const Membre& membre)
{
	membre.afficherMembre(o);

	return o;

}
