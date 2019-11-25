/********************************************
* Titre: Travail pratique #6 - mainwindow.cpp
* Date: 21 novembre 2019
* Auteur: Allan BEDDOUK
*******************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ExceptionArgumentInvalide.h"


#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <algorithm>


Q_DECLARE_METATYPE(Membre*)
Q_DECLARE_METATYPE(Billet*)
Q_DECLARE_METATYPE(Coupon*)

using namespace std;

MainWindow::MainWindow(vector<Coupon*> coupons, vector<Membre*> membres, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), coupons_(coupons), membres_(membres)
{
    ui->setupUi(this);
    setup();

}


MainWindow::~MainWindow()
{
    for(auto membre : membres_)
        delete membre;

    for (auto coupon: coupons_)
         delete coupon;

    delete ui;
}

void MainWindow::setup(){
   setMenu();
   setUI();
   chargerCoupons();
   chargerBillets();
   chargerMembres();
   nettoyerVue();
}

void MainWindow::afficherMessage(QString msg) {
    // TODO
    QMessageBox* message = new QMessageBox();
    message->setText(msg);
    message->exec();
}

void MainWindow::setMenu() {
    // TODO

    // On crée un bouton 'Quitter'
    QAction* quitter = new QAction(tr("Quitter"), this);

    // On connecte le clic sur ce bouton avec l'action de clore le programme
    connect(quitter, SIGNAL(triggered()), this, SLOT(close()));

    // On crée un bouton 'Nettoyer vue'
    QAction* nettoyer = new QAction(tr("Nettoyer vue"), this);

    // On connecte le clic sur ce bouton avec l'action de clore le programme
    connect(nettoyer, SIGNAL(triggered()), this, SLOT(nettoyerVue()));


    QMenu* fichier = new QMenu("Fichier");
    fichier->addAction(quitter);
    fichier->addAction(nettoyer);
    menuBar()->addMenu(fichier);

}


void MainWindow::setUI(){
    QLocale::setDefault(QLocale::C);
    //liste des billets
    QLabel* billetsLabel = new QLabel();
    billetsLabel->setText("Billets : ");
    listeBillets_ = new QListWidget(this);
    listeBillets_->setSortingEnabled(true);
// TODO
    connect(listeBillets_, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectionnerBillet(QListWidgetItem*)));

    // Boutons radios Type de billets
    boutonsRadioTypeBillets_.push_back(new QRadioButton("Regulier", this));
    boutonsRadioTypeBillets_.push_back(new QRadioButton("Regulier Solde", this));
    boutonsRadioTypeBillets_.push_back(new QRadioButton("FlightPass", this));
    boutonsRadioTypeBillets_.push_back(new QRadioButton("FlightPass Solde", this));

    QHBoxLayout* boutonsRadioBilletsLayout = new QHBoxLayout();
    for(QRadioButton* bouton : boutonsRadioTypeBillets_)
        boutonsRadioBilletsLayout->addWidget(bouton);


    // Liste deroulante pour choisir le Membre
    choixMembreBillet_ = new QComboBox(this);
    choixMembreBillet_->addItem("Membres");
    ajouterMembresDansComboBox(choixMembreBillet_);

    //Champ pour le PNR
    editeurPNR_ = new QLineEdit();

    QHBoxLayout* pnrLayout = new QHBoxLayout();
    pnrLayout->addWidget(new QLabel("PNR : "));
    pnrLayout->addWidget(editeurPNR_);


    //Champ pour le prix
    editeurPrixBillet_ = new QLineEdit();
    editeurPrixBillet_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* prixBilletLayout = new QHBoxLayout();
    prixBilletLayout->addWidget(new QLabel("Prix : "));
    prixBilletLayout->addWidget(editeurPrixBillet_);


    //Champ pour l'Od
    editeurOD_ = new QLineEdit();

    QHBoxLayout* odBilletLayout = new QHBoxLayout();
    odBilletLayout->addWidget(new QLabel("Od : "));
    odBilletLayout->addWidget(editeurOD_);


    //Champ pour le Tarif du Billet
    choixTarifBillet_ = new QComboBox(this);
    choixTarifBillet_->addItem("Tarif Billet");
    choixTarifBillet_->addItem("Economie");
    choixTarifBillet_->addItem("Premium economie");
    choixTarifBillet_->addItem("Affaire");
    choixTarifBillet_->addItem("Premiere");

    //Champ pour la date de vol
    editeurDateVol_ = new QLineEdit();

    QHBoxLayout* dateVolLayout = new QHBoxLayout();
    dateVolLayout->addWidget(new QLabel("Date de Vol : "));
    dateVolLayout->addWidget(editeurDateVol_);


    //Champ pour le pourcentage solde du billet
    editeurPourcentageSoldeBillet_ = new QLineEdit();
    editeurPourcentageSoldeBillet_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* pourcentageSoldeBilletLayout = new QHBoxLayout();
    pourcentageSoldeBilletLayout->addWidget(new QLabel("Pourcentage Solde Billet : "));
    pourcentageSoldeBilletLayout->addWidget(editeurPourcentageSoldeBillet_);

    //Champ pour les jours restants
    editeurUtilisationsRestantesFlightPass_ = new QLineEdit();
    editeurUtilisationsRestantesFlightPass_->setValidator(new QDoubleValidator(0, 10000, 2, this));
    editeurUtilisationsRestantesFlightPass_->setDisabled(true);

    QHBoxLayout* utilisationsRestantesLayout = new QHBoxLayout();
    utilisationsRestantesLayout->addWidget(new QLabel("Utilisations Restantes : "));
    utilisationsRestantesLayout->addWidget(editeurUtilisationsRestantesFlightPass_);


    //Bouton ajouter billet
// TODO
    boutonAjouterBillet = new QPushButton(this);
    boutonAjouterBillet->setText("Ajouter Billet");
    connect(boutonAjouterBillet, SIGNAL(clicked()), this, SLOT(ajouterBillet()));

    //ligne seprant les ajouts de billets
    //et les ajouts de coupons
    QFrame* horizontaleFrameLine = new QFrame();
    horizontaleFrameLine->setFrameShape(QFrame::HLine);

    //liste des coupons
    QLabel* couponsLabel = new QLabel();
    couponsLabel->setText("Coupons : ");
    listeCoupons_ = new QListWidget(this);
    listeCoupons_->setSortingEnabled(true);
// TODO
    connect(listeCoupons_, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectionnerCoupon(QListWidgetItem*)));



    //Champ pour le code du coupon
    editeurCodeCoupon_ = new QLineEdit();

    QHBoxLayout* codeCouponLayout = new QHBoxLayout();
    codeCouponLayout->addWidget(new QLabel("Code : "));
    codeCouponLayout->addWidget(editeurCodeCoupon_);

    //Champ pour le rabais du coupon
    editeurRabaisCoupon_ = new QLineEdit();
    editeurRabaisCoupon_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* rabaisCouponLayout = new QHBoxLayout();
    rabaisCouponLayout->addWidget(new QLabel("Rabais : "));
    rabaisCouponLayout->addWidget(editeurRabaisCoupon_);

    //Champ pour le cout du coupon
    editeurCoutCoupon_ = new QLineEdit();
    editeurCoutCoupon_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* coutCouponLayout = new QHBoxLayout();
    coutCouponLayout->addWidget(new QLabel("Cout : "));
    coutCouponLayout->addWidget(editeurCoutCoupon_);


    //Bouton ajouter coupon
// TODO
    boutonAjouterCoupon = new QPushButton(this);
    boutonAjouterCoupon->setText("Ajouter Coupon");
    connect(boutonAjouterCoupon, SIGNAL(clicked()), this, SLOT(ajouterCoupon()));


    //ligne seprant les ajouts de coupons
    //et les informations des membres
    QFrame* horizontaleFrameLine2 = new QFrame();
    horizontaleFrameLine2->setFrameShape(QFrame::HLine);


    //selecteur pour les membres
    QComboBox* choixMembre = new QComboBox(this);
    choixMembre->addItem("Tout Afficher"); // Index 0
    choixMembre->addItem("Afficher Membres Reguliers"); // Index 1
    choixMembre->addItem("Afficher Membres Premium"); // Index 2
// TODO
    connect(choixMembre, SIGNAL(currentIndexChanged(int)), this, SLOT(filtrerListe(int)));

    //liste des membres
    QLabel* membresLabel = new QLabel();
    membresLabel->setText("Membres : ");
    listeMembres_ = new QListWidget(this);
    listeMembres_->setSortingEnabled(true);
// TODO
    connect(listeMembres_, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectionnerMembre(QListWidgetItem*)));


    //Champ pour les points du Membres Regulier
    editeurPoints_ = new QLineEdit();
    QDoubleValidator* validator =  new QDoubleValidator(0, 10000, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    editeurPoints_->setValidator(validator);

    QHBoxLayout* pointsMembreLayout = new QHBoxLayout();
    pointsMembreLayout->addWidget(new QLabel("Points : "));
    pointsMembreLayout->addWidget(editeurPoints_);


    //Champ pour les points cumules du Membres Regulier
    editeurPointsCumules_ = new QLineEdit();
    editeurPointsCumules_->setValidator(new QDoubleValidator(0, 10000, 2, this));
    QHBoxLayout* pointsCumMembreLayout = new QHBoxLayout();
    pointsCumMembreLayout->addWidget(new QLabel("Points Cumules : "));
    pointsCumMembreLayout->addWidget(editeurPointsCumules_);

    //Champ pour les points cumules du Membres Regulier
    editeurJoursRestants_ = new QLineEdit();
    editeurJoursRestants_->setValidator(new QDoubleValidator(0, 10000, 2, this));
    QHBoxLayout* joursRestantsLayout = new QHBoxLayout();
    joursRestantsLayout->addWidget(new QLabel("Jours Restants : "));
    joursRestantsLayout->addWidget(editeurJoursRestants_);



    //Layout de gauche
    QVBoxLayout* layoutHautGauche = new QVBoxLayout;

    layoutHautGauche->addWidget(billetsLabel);
    layoutHautGauche->addWidget(listeBillets_);

    layoutHautGauche->addWidget(couponsLabel);
    layoutHautGauche->addWidget(listeCoupons_);

    layoutHautGauche->addWidget(choixMembre);

    layoutHautGauche->addWidget(membresLabel);
    layoutHautGauche->addWidget(listeMembres_);

    //layout de droite
     QVBoxLayout* layoutHautDroite = new QVBoxLayout;
     layoutHautDroite->addWidget(choixMembreBillet_);
     layoutHautDroite->addLayout(boutonsRadioBilletsLayout);
     layoutHautDroite->addLayout(pnrLayout);
     layoutHautDroite->addLayout(prixBilletLayout);
     layoutHautDroite->addLayout(odBilletLayout);
     layoutHautDroite->addWidget(choixTarifBillet_);
     layoutHautDroite->addLayout(dateVolLayout);
     layoutHautDroite->addLayout(pourcentageSoldeBilletLayout);
     layoutHautDroite->addLayout(utilisationsRestantesLayout);
//TODO
     layoutHautDroite->addWidget(boutonAjouterBillet);

     layoutHautDroite->addWidget(horizontaleFrameLine);

     layoutHautDroite->addLayout(codeCouponLayout);
     layoutHautDroite->addLayout(rabaisCouponLayout);
     layoutHautDroite->addLayout(coutCouponLayout);
//TODO
     layoutHautDroite->addWidget(boutonAjouterCoupon);

     layoutHautDroite->addWidget(horizontaleFrameLine2);

     layoutHautDroite->addLayout(pointsMembreLayout);
     layoutHautDroite->addLayout(pointsCumMembreLayout);
     layoutHautDroite->addLayout(joursRestantsLayout);


    //ligne verticale
    QFrame* verticalFrameLine = new QFrame;
    verticalFrameLine->setFrameShape(QFrame::VLine);

    //Layout du haut
    QHBoxLayout* layoutHaut = new QHBoxLayout;
    layoutHaut->addLayout(layoutHautGauche);
    layoutHaut->addWidget(verticalFrameLine);
    layoutHaut->addLayout(layoutHautDroite);

    //Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutHaut);

    QWidget* widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);

    string title = "Bienvenue sur PolyAir !" ;
    setWindowTitle(title.c_str());
}


void MainWindow::chargerBillets(){
    listeBillets_->clear();

    for(Membre* membre: membres_){
        for(Billet* billet: membre->getBillets())
        {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(billet->getPnr()), listeBillets_);
            item->setData(Qt::UserRole, QVariant::fromValue<Billet*>(billet));
        }
    }

}

void MainWindow::chargerCoupons(){
    listeCoupons_->clear();
    for (auto coupon: coupons_){

        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(coupon->getCode()), listeCoupons_);
        item->setData(Qt::UserRole, QVariant::fromValue<Coupon*>(coupon));
    }

}

void MainWindow::chargerMembres(){
    listeMembres_->clear();
    for (auto membre: membres_){

        QListWidgetItem* item = new QListWidgetItem(
            QString::fromStdString(membre->getNom()) , listeMembres_);
        item->setData(Qt::UserRole, QVariant::fromValue<Membre*>(membre));
    }
}

void MainWindow::ajouterMembresDansComboBox(QComboBox* list){
    for(Membre* membre : membres_){
        list->addItem(QString::fromStdString(membre->getNom()));
    }
}

void MainWindow::nettoyerVue() {

    nettoyerVueBillets();
    nettoyerVueCoupons();
    nettoyerVueMembres();

    // Listes
    listeBillets_->clearSelection();
    listeCoupons_->clearSelection();
    listeMembres_->clearSelection();
    chargerBillets();
    chargerCoupons();
    chargerMembres();
}

void MainWindow::nettoyerVueBillets(){
    editeurPNR_ ->clear();
    editeurPNR_->setDisabled(false);
    editeurPrixBillet_->clear();
    editeurPrixBillet_->setDisabled(false);
    editeurOD_->clear();
    editeurOD_->setDisabled(false);
    editeurDateVol_->clear();
    editeurDateVol_ ->setDisabled(false);
    editeurPourcentageSoldeBillet_->clear();
    editeurPourcentageSoldeBillet_ ->setDisabled(false);
    editeurUtilisationsRestantesFlightPass_->clear();
    editeurPourcentageSoldeBillet_ ->setDisabled(false);

    for (auto it = boutonsRadioTypeBillets_.begin(); it != boutonsRadioTypeBillets_.end(); it++){
        (*it)->setChecked(false);
        (*it)->setDisabled(false);
        (*it)->setAutoExclusive(false);

    }

    choixMembreBillet_->setCurrentIndex(0);
    choixMembreBillet_->setDisabled(false);
    choixTarifBillet_->setDisabled(false);
    choixTarifBillet_->setCurrentIndex(0);
    boutonAjouterBillet->setDisabled(false);

}

void MainWindow::nettoyerVueCoupons(){
    editeurCodeCoupon_ ->clear();
    editeurCodeCoupon_->setDisabled(false);
    editeurRabaisCoupon_ ->clear();
    editeurRabaisCoupon_->setDisabled(false);
    editeurCoutCoupon_ ->clear();
    editeurCoutCoupon_->setDisabled(false);
    boutonAjouterCoupon->setDisabled(false);
}

void MainWindow::nettoyerVueMembres(){
    editeurPoints_->clear();
    editeurPointsCumules_->clear();
    editeurJoursRestants_->clear();
    editeurPoints_->setDisabled(false);
    editeurPointsCumules_->setDisabled(false);
    editeurJoursRestants_->setDisabled(false);

}

void MainWindow::selectionnerBillet(QListWidgetItem* item){
    // TODO
    Billet* billet = item->data(Qt::UserRole).value<Billet*>();
    editeurPNR_ ->setText(QString::fromStdString(billet->getPnr()));
    editeurPNR_->setDisabled(true);
    editeurPrixBillet_ ->setText(QString::number(billet->getPrix()));
    editeurPrixBillet_->setDisabled(true);
    editeurOD_ -> setText(QString::fromStdString(billet->getOd()));
    editeurOD_->setDisabled(true);

    //On affiche la date de vol uniquement si le billet est un billet regulier
    if(auto billetReg = dynamic_cast<BilletRegulier*>(billet))
        editeurDateVol_->setText(QString::fromStdString(billetReg->getDateVol()));
    else
        editeurDateVol_->setText(QString::fromStdString("N/a"));
    editeurDateVol_ ->setDisabled(true);

    //On affiche le pourcentage de solde uniquement si le billet est soldé
    if(auto solde = dynamic_cast<Solde*>(billet))
        editeurPourcentageSoldeBillet_->setText(QString::number(solde->getPourcentageSolde()));
    else
        editeurPourcentageSoldeBillet_->setText(QString::fromStdString("N/a"));
    editeurPourcentageSoldeBillet_ ->setDisabled(true);

    //On affiche le nombre d'utilisations restantes uniquement si le billet est un flightpass
    if(auto flightpass = dynamic_cast<FlightPass*>(billet))
        editeurUtilisationsRestantesFlightPass_->setText(QString::number(flightpass->getNbUtilisationsRestante()));
    else
        editeurUtilisationsRestantesFlightPass_->setText(QString::fromStdString("N/a"));
    editeurPourcentageSoldeBillet_ ->setDisabled(true);

    //On cherche le bon bouton radio du type de billet et on le coche
    for (auto it = boutonsRadioTypeBillets_.begin(); it != boutonsRadioTypeBillets_.end(); it++){
        (*it)->setDisabled(true);
        if (((typeid(*billet) == typeid(BilletRegulier))&& ((*it)->text().endsWith("Regulier"))) ||
            ((typeid(*billet) == typeid(BilletRegulierSolde)) && ((*it)->text().endsWith("Regulier Solde"))) ||
            ((typeid(*billet) == typeid(FlightPass)) && ((*it)->text().endsWith("FlightPass"))) ||
            ((typeid(*billet) == typeid(FlightPassSolde)) && ((*it)->text().endsWith("FlightPass Solde")))){
                (*it)->setChecked(true);
        }

    }

    //On choisit le membre qui possède le billet dans le comboBox
    for (int i = 0; i < listeMembres_-> count(); i++){
        QString nomPassager = QString::fromStdString(billet->getNomPassager());
        if(choixMembreBillet_->itemText(i).endsWith(nomPassager))
            choixMembreBillet_->setCurrentIndex(i);
        }

    choixMembreBillet_->setDisabled(true);
    choixTarifBillet_->setDisabled(true);
    choixTarifBillet_->setCurrentIndex(int(billet->getTarif())+1);
    boutonAjouterBillet->setDisabled(true);

}

void MainWindow::selectionnerCoupon(QListWidgetItem* item ){
    // TODO
    Coupon* coupon = item->data(Qt::UserRole).value<Coupon*>();
    editeurCodeCoupon_ ->setText(QString::fromStdString(coupon->getCode()));
    editeurCodeCoupon_->setDisabled(true);
    editeurRabaisCoupon_ ->setText(QString::number(coupon->getRabais()));
    editeurRabaisCoupon_->setDisabled(true);
    editeurCoutCoupon_ -> setText(QString::number(coupon->getCout()));
    editeurCoutCoupon_->setDisabled(true);
    boutonAjouterCoupon->setDisabled(true);

}
void MainWindow::selectionnerMembre(QListWidgetItem* item){
    // TODO
    Membre* membre = item->data(Qt::UserRole).value<Membre*>();
    editeurPoints_ ->setText(QString::fromStdString("N/a"));
    editeurPointsCumules_->setText(QString::fromStdString("N/a"));
    editeurJoursRestants_->setText(QString::fromStdString("N/a"));

    if (auto membrePremium = dynamic_cast<MembrePremium*>(membre)){
        editeurPointsCumules_->setText(QString::number(membrePremium->getpointsCumulee()));
        editeurJoursRestants_->setText(QString::number(membrePremium->getJourRestants()));
    }

    else if (auto membreRegulier = dynamic_cast<MembreRegulier*>(membre))
        editeurPoints_ ->setText(QString::number(membreRegulier->getPoints()));

    editeurPoints_->setDisabled(true);
    editeurPointsCumules_->setDisabled(true);
    editeurJoursRestants_->setDisabled(true);

}
void MainWindow::ajouterBillet(){
    // TODO
    Billet* nouveauBillet;
    Membre* membreSelectionne;

    // On créé le bon type d'employé selon le cas
    QRadioButton* typeBilletChoisi = nullptr;
    for (auto it = boutonsRadioTypeBillets_.begin(); it != boutonsRadioTypeBillets_.end(); it++) {
        if ((*it)->isChecked()) {
            typeBilletChoisi = *it;
            break;
        }
    }

    // On vérifie les valeurs des arguments
    try {
        string pnr = editeurPNR_->text().toStdString();
        if (pnr == "") {
            throw ExceptionArgumentInvalide("Erreur : Le PNR (Passenger Name Record) n’est pas rempli");
        }

        bool ok;
        double prix = editeurPrixBillet_->text().toDouble(&ok);
        if (!ok) {
            throw ExceptionArgumentInvalide("Erreur : Le prix du billet n'est pas valide");
        }

        string od = editeurOD_->text().toStdString();
        if (od == "") {
            throw ExceptionArgumentInvalide("Erreur : L’origine-Destination n’est pas rempli");
        }


        if (typeBilletChoisi==nullptr){
            throw ExceptionArgumentInvalide("Erreur : Le type de billet n'a pas été indiqué");
        }

        if (choixTarifBillet_->currentIndex()==0){
            throw ExceptionArgumentInvalide("Erreur : Le tarif du billet n'a pas été indiqué");
        }

        // On crée le bon type de billet selon le cas
        double pourcentageSolde = editeurPourcentageSoldeBillet_->text().toDouble(&ok);
        if (typeBilletChoisi->text().endsWith("Solde")){
            if (!ok) {
                throw ExceptionArgumentInvalide("Erreur : Le pourcentage de solde n'est pas valide");
            }
        }

        if (typeBilletChoisi->text().startsWith("Regulier")) {
            string dateVol = editeurDateVol_->text().toStdString();
            if (dateVol == "") {
                throw ExceptionArgumentInvalide("Erreur : La date de vol n'a pas été remplie");
            }

            if (typeBilletChoisi->text().endsWith("Solde")){
                nouveauBillet = new BilletRegulierSolde(pnr, prix, od, getTarifBillet(), dateVol, pourcentageSolde);
            }

            else{
                nouveauBillet = new BilletRegulier(pnr, prix, od, getTarifBillet(), dateVol);
            }
        }

        else{

            if (typeBilletChoisi->text().endsWith("Solde")){
                nouveauBillet = new FlightPassSolde(pnr, prix, od, getTarifBillet(), pourcentageSolde);
            }

            else{
                nouveauBillet = new FlightPass(pnr, prix, od, getTarifBillet());
            }
        }

        string nomMembre = choixMembreBillet_->currentText().toStdString();
        if (nomMembre == "Membres") {
            throw ExceptionArgumentInvalide("Erreur : Assigner un membre au billet");
        }

       membreSelectionne = trouverMembreParNom(nomMembre);

    } catch (ExceptionArgumentInvalide& e) {
        afficherMessage(QString::fromStdString(e.what()));
        return;
    }

    //On ajoute le nouveau billet au membre
    membreSelectionne->ajouterBillet(nouveauBillet);
    //On charge le billet pour l'ajouter à la liste et l'afficher
    chargerBillets();

    afficherMessage(QString::fromStdString("Le billet a été ajouté avec succès"));
}
void MainWindow::ajouterCoupon(){

    // TODO
    Coupon* nouveauCoupon;

    // On vérifie les valeurs des arguments
    try {
        string code = editeurCodeCoupon_->text().toStdString();
        if (code == "") {
            throw ExceptionArgumentInvalide("Erreur : Le code du coupon n’est pas rempli");
        }

        bool ok;
        double rabais = editeurRabaisCoupon_->text().toDouble(&ok);
        if (!ok)  {
            throw ExceptionArgumentInvalide("Erreur : Le rabais du coupon n'est pas valide");
        }

        if (rabais > 1.0) {
            throw ExceptionArgumentInvalide("Erreur : Le rabais du coupon est trop grand");
        }

        int cout = editeurCoutCoupon_->text().toInt(&ok);
        if ((!ok)) {
            throw ExceptionArgumentInvalide("Erreur : Le cout du coupon n'est pas valide");
        }

        nouveauCoupon = new Coupon(code,rabais,cout);

    } catch (ExceptionArgumentInvalide& e) {
        afficherMessage(QString::fromStdString(e.what()));
        return;
    }

    //On ajoute le nouveau coupon dans le vecteur coupons_
    coupons_.push_back(nouveauCoupon);
    //On charge le coupon pour l'ajouter à la liste et l'afficher
    chargerCoupons();

    afficherMessage(QString::fromStdString("Le coupon a été ajouté avec succès"));
}


void MainWindow::filtrerListe(int index){
    // TODO
    for (int i = 0; i < listeMembres_-> count(); i++){
        Membre* membre = listeMembres_->item(i)->data(Qt::UserRole).value<Membre*>();
        listeMembres_->item(i)->setHidden(false);
        if(filtrerMasque(membre,index)){
            listeMembres_->item(i)->setHidden(true);
        }
    }
}

bool MainWindow::filtrerMasque(Membre* membre, int index) {
    // TODO
    switch(index){

    //Afficher membres réguliers
    case 1:
        return (typeid(*membre) != typeid(MembreRegulier));

    //Afficher membres premiums
    case 2:
        return (typeid(*membre) != typeid(MembrePremium));
    }

    return false;
}

TarifBillet MainWindow::getTarifBillet(){
//TODO
    //Ca marche car l'ordre dans le comboBox est le même que dans la déclaration de TarifBillet
    return static_cast<TarifBillet>(choixTarifBillet_->currentIndex() - 1);
}



Membre* MainWindow::trouverMembreParNom(const string& nom){
   //TODO
    for(Membre* membre : membres_){
        if (*membre == nom)
            return membre;
    }
    return nullptr;
}
