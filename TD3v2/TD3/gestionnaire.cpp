/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: gestionnaire.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
#include "gestionnaire.h"

 /****************************************************************************
  * Fonction:	 Gestionnaire::Gestionnaire
  * Description: Constructeur par défaut.
  * Paramètres:	aucun
  * Retour:		aucun
  ****************************************************************************/
Gestionnaire::Gestionnaire()
{
}

/****************************************************************************
 * Fonction:	Gestionnaire::~Gestionnaire
 * Description: Destructeur de gestionnaire, désaloue aussi la mémoire.
 * Paramètres:	aucun
 * Retour:		aucun
 ****************************************************************************/
Gestionnaire::~Gestionnaire()
{
	for (unsigned i = 0; i < membres_.size(); i++) {
		delete membres_[i];
	}

	for (unsigned i = 0; i < coupons_.size(); i++) {
		delete coupons_[i];
	}
}

/****************************************************************************
 * Fonction:	Gestionnaire::getMembres
 * Description: Retourne le vecteur des pointeurs vers les membres.
 * Paramètres:	aucun
 * Retour:		vector<Membre*> vecteur de pointeurs membres
 ****************************************************************************/
vector<Membre*> Gestionnaire::getMembres() const
{
	return membres_;
}

/****************************************************************************
 * Fonction:	Gestionnaire::getCoupons
 * Description: Retourne le vecteur de pointeurs coupons dans le gestionnaire.
 * Paramètres:	aucun
 * Retour:		vector<Coupon*> vecteur de pointeurs coupons
 ****************************************************************************/
vector<Coupon*> Gestionnaire::getCoupons() const
{
	return coupons_;
}

/****************************************************************************
 * Fonction:	Gestionnaire::ajouterMembre
 * Description: Ajoute un membre dans le vecteur de pointeurs membres du
 *				gestionnaire. On crée des pointeurs avec des classes correspondantes au type du membre.
 * Paramètres:	const string& nomMembre, TypeMembre typeMembre
 * Retour:		aucun
 ****************************************************************************/
void Gestionnaire::ajouterMembre(const string& nomMembre, TypeMembre typeMembre)
{
	switch (typeMembre) {
	case TypeMembre::Membre_Occasionnel:
		membres_.push_back(new Membre(nomMembre, typeMembre));
		break;
	case TypeMembre::Membre_Regulier:
		membres_.push_back(new MembreRegulier(nomMembre, typeMembre));
		break;
	case TypeMembre::Membre_Premium:
		membres_.push_back(new MembrePremium(nomMembre));
		break;
	}

}

/****************************************************************************
 * Fonction:	Gestionnaire::ajouterCoupon
 * Description: Ajoute un coupon dans le vecteur de pointeurs coupons du
 *				gestionnaire. On alloue un espace mémoire pour le coupon en
 *				parametre. Ainsi, on fera une deep copy, donc de la composition.
 * Paramètres:	(const string&) code
 *				(double) rabais
 *				(int) cout
 * Retour:		aucun
 ****************************************************************************/
void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	coupons_.push_back(new Coupon(code, rabais, cout));
}

/****************************************************************************
 * Fonction:	Gestionnaire::trouverMembre
 * Description: Cherche un membre dans le vecteur de pointeurs membres du
 *				gestionnaire à l'aide du nom fourni en paramètre et de l'operateur ==
 *				que l'on a surcharge dans la classe membre.
 * Paramètres:	(const string&) nomMembre
 * Retour:		(Membre*) le pointeur membre qui a le même nom que le paramètre
 ****************************************************************************/
Membre* Gestionnaire::trouverMembre(const string& nomMembre) const
{
	for (unsigned i = 0; i < membres_.size(); i++) {
		if (*membres_[i] == nomMembre) {
			return membres_[i];
		}
	}
	cout << "Le membre " << nomMembre << " n'existe pas\n";

	return nullptr;
}

/****************************************************************************
 * Fonction:	Gestionnaire::assignerBillet
 * Description: Ajoute un billet dans le vecteur de pointeurs billets d'un membre.
 *				Permet aussi d'appliquer un coupon pour baisser le prix du billet.
 * Paramètres:	(const string&) nomMembre
 *				(const string&) pnr
 *				(double) prixBase
 *				(const string&) od
 *				(TarifBillet tarif)
 *				(const string&) dateVol
 *				(bool) utiliserCoupon)
 * Retour:		aucun
 ****************************************************************************/
void Gestionnaire::assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon, TypeBillet typeBillet)
{
	double prixReel;
	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		return;
	}
	if (typeBillet == Flight_Pass)
		prixBase *= 10;

	if (utiliserCoupon) {
		prixReel = prixBase - appliquerCoupon(membre, prixBase);
	}
	else {
		prixReel = prixBase;
	}

	if (membre->getTypeMembre() == Membre_Premium) {
		MembrePremium * membrePrem = static_cast<MembrePremium*>(membre);
		double rabais = membrePrem->getpointsCumulee() * 5 / 1000 / 100.0 >= 0.1 ? 0.1 : membrePrem->getpointsCumulee() / 1000 / 100.0;
		prixReel -= prixReel * rabais;
	}
		
	membre->ajouterBillet(pnr, prixReel, od, tarif, typeBillet, dateVol);
}

/****************************************************************************
 * Fonction:	Gestionnaire::appliquerCoupon
 * Description: Calcule le meilleur coupon que possède le membre et retourne
 *				la différence à appliquer. On utilise l'operateur > de la
 *				classe coupon ainsi que l'operateur -= que nous avons surchargé dans
 *				la classe Membre
 * Paramètres:	(Membre*) membre
 *				(double) prix
 * Retour:		(double) la différence à appliquer sur le prix
 ****************************************************************************/
double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	if (membre->getTypeMembre() != Membre_Occasionnel) {
		MembreRegulier* membre0 = static_cast<MembreRegulier*>(membre);
		if (membre0->getCoupons().size() == 0) {
			cout << "Le membre n'a pas de coupon utilisable\n";
			return 0;
		}

		else {
			Coupon* meilleurCoupon = membre0->getCoupons()[0];
			vector<Coupon*> coupons = membre0->getCoupons();
			for (unsigned i = 1; i < coupons.size(); ++i) {
				if (coupons[i]->getCout() >= meilleurCoupon->getCout()) {
					meilleurCoupon = coupons[i];
				}
			}

			*membre0 -= meilleurCoupon;
			return prix * meilleurCoupon->getRabais();
		
		}
	}

	else {
		cout << "Le membre ne peut pas avoir de coupon\n";
		return 0;
	}

}

/****************************************************************************
 * Fonction:	Gestionnaire::acheterCoupon
 * Description: Achète un coupon pour un client (s'il a assez de points).
 * Paramètres:	(const string&) nomMembre
 * Retour:		aucun
 ****************************************************************************/
void Gestionnaire::acheterCoupon(const string& nomMembre)
{
	if (coupons_.size() == 0) {
		cout << "Le gestionnaire n'a pas de coupon!" << endl;
		return;
	}

	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		return;
	}

	Coupon* meilleurCoupon = nullptr;
	if (membre->getTypeMembre() != Membre_Occasionnel) {

		MembreRegulier* membre0 = static_cast<MembreRegulier*>(membre);
		for (unsigned int i = 0; i < coupons_.size(); i++) {
			if (membre0->getPoints() >= coupons_[i]->getCout()) {
				// Si on avait pas encore trouve de meilleur coupon, on fait la premiere assignation
				if (meilleurCoupon == nullptr) {
					meilleurCoupon = coupons_[i];
				}
				// Sinon on compare si le coupon courant a un rabais superieur au meilleur coupon
				else if (coupons_[i]->getRabais() > meilleurCoupon->getRabais()) {
					meilleurCoupon = coupons_[i];
				}
			}
		}

		if (membre->getTypeMembre() == Membre_Premium && meilleurCoupon != nullptr) {
			MembrePremium* membre1 = static_cast<MembrePremium*>(membre0);
			membre1->acheterCoupon(meilleurCoupon);
		}

		else if (meilleurCoupon != nullptr)
			membre0->acheterCoupon(meilleurCoupon);
	}

	else {
		cout << "Le membre ne peut acheter de coupon\n";
	}
}

/****************************************************************************
 * Fonction:	Gestionnaire::operator<<
 * Description: Affiche les informations de tous les membres dans le vecteur de
 *				membres, dépendamment de leurs classes.
 * Paramètres:	aucun
 * Retour:		(ostream&) o
 ****************************************************************************/
ostream& operator<<(ostream& o, const Gestionnaire& gestionnaire)
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	MembreRegulier* membreReg = nullptr;// = static_cast<MembreRegulier*>(gestionnaire.membres_[i]);
	MembrePremium* membrePrem = nullptr;// = static_cast<MembrePremium*>(gestionnaire.membres_[i]);
	for (unsigned i = 0; i < gestionnaire.membres_.size(); i++) {
		//if (gestionnaire.membres_[i]->getTypeMembre()==Membre_Premium)
		switch (gestionnaire.membres_[i]->getTypeMembre()) {
			case Membre_Occasionnel:
				o << *gestionnaire.membres_[i];
			break;

			case Membre_Regulier:
				membreReg = static_cast<MembreRegulier*>(gestionnaire.membres_[i]);
				o << *membreReg;
			break;

			case Membre_Premium:
				membrePrem = static_cast<MembrePremium*>(gestionnaire.membres_[i]);
				o << *membrePrem;
				break;
		}

	}

	return o;
}
