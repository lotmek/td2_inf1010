/**********************************************************************
 * Cours : INF1010
 * Travail pratique 4
 * Nom: membre.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "membre.h"

 /****************************************************************************
  * Fonction:	Membre::Membre
  * Description: Constructeur par défaut.
  * Paramètres:	aucun
  * Retour:		aucun
  ****************************************************************************/
Membre::Membre() :
	nom_("")
{
}

/****************************************************************************
 * Fonction:	Membre::Membre
 * Description: Constructeur par paramètres.
 * Paramètres:	(const string&) nom
 * Retour:		aucun
 ****************************************************************************/
Membre::Membre(const string& nom) :
	nom_(nom)
{
}

/****************************************************************************
 * Fonction:	Membre::Membre
 * Description: Constructeur par copie.
 * Paramètres:	(const Membre&) Membre
 * Retour:		aucun
 ****************************************************************************/
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_)
{
	Billet* billet = nullptr;
	for (size_t i = 0; i < membre.billets_.size(); ++i) {
		billet = membre.getBillets()[i];
		if (BilletRegulier* billetRegulier = dynamic_cast<BilletRegulier*>(billet))
			billets_.push_back(billetRegulier->clone());
		else if (FlightPass* flightPass = dynamic_cast<FlightPass*>(billet))
			billets_.push_back(flightPass->clone());
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
	for (size_t i = 0; i < billets_.size(); ++i) {
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

/**********************************************************************************************
 * Fonction:	Membre::utiliserBillet
 * Description:	Retire un billet ou décrémente son nombre d'utilisation si c'est un flightpass.
 * Paramètres:	(const string& pnr)
 * Retour:		aucun
 **********************************************************************************************/
void Membre::utiliserBillet(const string& pnr)
{
	int indexTrouve = -1;
	for (size_t i = 0; i < billets_.size(); ++i) {
		if (billets_[i]->getPnr() == pnr) {
			indexTrouve = i;
			break;
		}
	}

	if (indexTrouve == -1) {
		cout << "Le billet n'est pas trouve" << endl;
		return;
	}
	if (FlightPass* flightPass = dynamic_cast<FlightPass*>(billets_[indexTrouve])) {
		flightPass->decrementeNbUtilisations();
		if (flightPass->getNbUtilisationsRestante() > 0) {
			return;
		}
	}
		
	delete billets_[indexTrouve];
	billets_[indexTrouve] = billets_[billets_.size() - 1];
	billets_.pop_back();
}

/****************************************************************************
 * Fonction:	Membre::ajouterBillet
 * Description:	Ajoute un pointeur billet dans le vecteur.
 * Paramètres:	(Billet* billet)
 * Retour:		aucun
 ****************************************************************************/
void Membre::ajouterBillet(Billet* billet)
{
	billet->setNomPassager(nom_);
	billets_.push_back(billet);
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

		for (size_t i = 0; i < billets_.size(); ++i) {
			delete billets_[i];
		}

		billets_.clear();

		string nomTemp = nom_;										
		this->Membre::Membre(membre);
		nom_ = nomTemp;
	}

	return *this;
}


/****************************************************************************
 * Fonction:	Membre::afficher
 * Description:	Affiche les informations du membre, dont les billets dépendemment de leurs classes.
 * Paramètres:	ostream& o
 * Retour:		aucun
 ****************************************************************************/
void Membre::afficher(ostream& o) const
{
	o << setfill(' ');
	o << "- Membre " << nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;
	for (size_t i = 0; i < billets_.size(); i++) {
		
		if (BilletRegulier* billetRegulier = dynamic_cast<BilletRegulier*>(billets_[i]))
			billetRegulier->afficher(o);
		else if (FlightPass* flightPass = dynamic_cast<FlightPass*>(billets_[i]))
			flightPass->afficher(o);
		else if (Billet* billet = dynamic_cast<Billet*>(billets_[i]))
			billet->afficher(o);
	}
	o << endl;
}