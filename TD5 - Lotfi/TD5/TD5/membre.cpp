/**********************************************************************
 * Cours : INF1010
 * Travail pratique 5
 * Nom: membres.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussi�res    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "membre.h"

 /****************************************************************************
  * Fonction:	 Membre::Membre
  * Description: Constructeur par d�faut de la classe Membre
  * Param�tres:	 aucun
  * Retour:		 aucun
  ****************************************************************************/
Membre::Membre() :
	nom_("")
{
}

/****************************************************************************
 * Fonction:	Membre::Membre
 * Description: Constructeur par param�tre de la classe Membre
 * Param�tres:	(const string&) nom
 * Retour:		aucun
 ****************************************************************************/
Membre::Membre(const string& nom) :
	nom_(nom)
{
}

/****************************************************************************
 * Fonction:	Membre::Membre
 * Description: Constructeur par copie de la classe Membre
 * Param�tres:	(Membre&) membre
 * Retour:		aucun
 ****************************************************************************/
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_)
{
	billets_.clear();
	copy(membre.getBillets().begin(), membre.getBillets().end(), back_inserter(billets_));
}

/****************************************************************************
 * Fonction:	Membre::~Membre
 * Description: Destructeur de la classe Membre, on d�salloue la m�moire r�serv�e pour les billets
 * Param�tres:	aucun
 * Retour:		aucun
 ****************************************************************************/
Membre::~Membre()
{
	for (vector<Billet*>::iterator it = billets_.begin(); it != billets_.end(); it++)
		delete *it;
}

/****************************************************************************
 * Fonction:	Membre::getNom
 * Description: Retourne le nom d'un membre
 * Param�tres:	aucun
 * Retour:		(string) nom du membre
 ****************************************************************************/
string Membre::getNom() const
{
	return nom_;
}

/****************************************************************************
 * Fonction:	Membre::getBillets
 * Description: Retourne un vecteur de billets poss�d�s par le membre
 * Param�tres:	aucun
 * Retour:		(vector<Billet*>) vecteur de billets
 ****************************************************************************/
vector<Billet*> Membre::getBillets() const
{
	return billets_;
}

/****************************************************************************
 * Fonction:	Membre::setNom
 * Description: Modifie le nom d'un membre
 * Param�tres:	(const string&) nom
 * Retour:		aucun
 ****************************************************************************/
void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

/****************************************************************************
 * Fonction:	Membre::trouverBillet
 * Description: Cherche un billet avec le pnr et retourne un it�rateur qui pointe vers ce billet
 * Param�tres:	(const string&) pnr
 * Retour:		(vector<Billet*>::iterator) it�rateur qui pointe vers le billet recherch�
 ****************************************************************************/
vector<Billet*>::iterator Membre::trouverBillet(const string& pnr)
{
	for (vector<Billet*>::iterator it = billets_.begin(); it != billets_.end(); it++) {
		if ((*it)->getPnr() == pnr) return it;
	}

	//On retourne un it�rateur nul si on ne trouve rien
	return {};
}

/****************************************************************************
 * Fonction:	Membre::utiliserBillet
 * Description: D�truit un billet utilis� ou d�cremente le nombre d'utilisations si c'est un flightpass
 * Param�tres:	(const string&) pnr
 * Retour:		aucun
 ****************************************************************************/
void Membre::utiliserBillet(const string& pnr)
{
	vector<Billet*>::iterator it = trouverBillet(pnr);

	if (auto flightPass = dynamic_cast<FlightPass*>(*it)) {
		flightPass->decrementeNbUtilisations();
		if (flightPass->getNbUtilisationsRestante() > 0) {
			return;
		}
	}

	delete *it;
	billets_.erase(it);
}

/****************************************************************************
 * Fonction:	Membre::assignerBillet
 * Description: Ajoute un billet dans le vecteur billets du membre
 * Param�tres:	(Billet*) billet
 * Retour:		aucun
 ****************************************************************************/
void Membre::ajouterBillet(Billet* billet)
{
	billet->setNomPassager(nom_);
	billets_.push_back(billet);
}

/****************************************************************************
 * Fonction:	Membre::operator==
 * Description: Surcharge l'op�rateur == pour comparer un membre (� gauche) avec un nom
 * Param�tres:	(const string&) nomMembre
 * Retour:		(bool) vrai ou faux
 ****************************************************************************/
bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}


/****************************************************************************
 * Fonction:	operator==
 * Description: Surcharge l'op�rateur == pour comparer un membre (� droite) avec un nom
 * Param�tres:	(const string&) nomMembre, (const Membre&) membre
 * Retour:		(bool) vrai ou faux
 ****************************************************************************/
bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}


/****************************************************************************
 * Fonction:	Membre::operator=
 * Description: Surcharge l'op�rateur = pour �craser les donn�es du membre et les remplacer par celles d'un autre membre
 * Param�tres:	(const Membre&) membre
 * Retour:		(Membre&) membre copi�
 ****************************************************************************/
Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;

		for (vector<Billet*>::iterator it = billets_.begin(); it != billets_.end(); it++)
			delete *it;

		billets_.clear();

		copy(membre.getBillets().begin(), membre.getBillets().end(), back_inserter(billets_));
	}

	return *this;
}


/****************************************************************************
 * Fonction:	Membre::afficher
 * Description: Affiche les informations d'un membre
 * Param�tres:	(ostream&) o
 * Retour:		aucun
 ****************************************************************************/
void Membre::afficher(ostream& o) const
{
	o << setfill(' ');
	o << "- Membre " << nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;

	copy(billets_.begin(), billets_.end(), ostream_iterator<Billet*>(cout, "\n"));
}