#include "MainWindow.hpp"
#include "ui_MainWindow.h"


//Konstruktor Glavnog Prozora
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      broj_cvorova(0)

{
    ui->setupUi(this);
    scena = new QGraphicsScene(this); //scena cvorova
    TokPodataka = new Stream();       //odgovarajuci tok podataka

    //BITNO!!
    //Ova opcija se postavlja zbog izscrtavanja veza izmedju cvorova
    ui->GlavniTok->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    scena->setStickyFocus(true);
}


//Destruktor Glavnog Prozora
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_AddNodeButton_clicked()
{
    QString nazivAlgoritma;

    //dohvatanje naziva algoritma iz odabrane liste algoritama
    if(!izabranaLista.compare("Prepocesiranje")){

        auto selektovani = ui->LISTA_Preprocesiranje->selectedItems();
        QListWidgetItem* item = selektovani.first();
        nazivAlgoritma = item->text();

    }else if(!izabranaLista.compare("Klasifikacija")){

        auto selektovani = ui->LISTA_Klasifikacija->selectedItems();
        QListWidgetItem* item = selektovani.first();
        nazivAlgoritma = item->text();

    }else if(!izabranaLista.compare("Klasterovanje")){

        auto selektovani = ui->LISTA_Klasterovanje->selectedItems();
        QListWidgetItem* item = selektovani.first();
        nazivAlgoritma = item->text();

    }else if(!izabranaLista.compare("LinearnaRegresija")){

        auto selektovani = ui->LISTA_LinReg->selectedItems();
        QListWidgetItem* item = selektovani.first();
        nazivAlgoritma = item->text();

    }else if(!izabranaLista.compare("Ulaz")){

        auto selektovani = ui->LISTA_Ulaz->selectedItems();
        QListWidgetItem* item = selektovani.first();
        nazivAlgoritma = item->text();

    }else{
        return;
    }

    //generisanje jedinsvenog ID-a cvora
    auto nodeID = generisiID(nazivAlgoritma);

    //crtanje cvora na sceni
    nacrtajCvor(nodeID);

    //dodavanje cvor u tok podataka
    dodajCvorUTok(nodeID);

}

void MainWindow::nacrtajCvor(QString nodeID){

    //pravimo cvor
    auto *sn = new SceneNode(nodeID);

    //dodajemo ga na scenu
    scena->addItem(sn);

    //postavljano scenu
    ui->GlavniTok->setScene(scena);
}

void MainWindow::dodajCvorUTok(QString nodeID){

    //fja particionise ID cvora i na osnovu toga dodaje objekat odgovarajuce
    //klase u tok podataka

    if(nodeID[0] == 'U'){

        if(nodeID[2] == 'P'){            
            auto sn = new SourceNode(nodeID.toStdString());
            TokPodataka->add(sn);
        }


    }else if(nodeID[0] == 'P'){

        if(nodeID[2] == 'P'){            
            auto pn = new PartitionNode(nodeID.toStdString());
            TokPodataka->add(pn);
        }

        if(nodeID[2] == 'N'){            
            auto nn = new NormalizationNode(nodeID.toStdString());
            TokPodataka->add(nn);
        }

        if(nodeID[2] == 'S'){            
            auto sn = new StatisticsNode(nodeID.toStdString());
            TokPodataka->add(sn);
        }

        if(nodeID[2] == 'U'){            
            auto smn = new SamplingNode(nodeID.toStdString());
            TokPodataka->add(smn);
        }

        if(nodeID[2] == 'F'){
            auto fn = new FilterNode(nodeID.toStdString());
            TokPodataka->add(fn);
        }


    }else if(nodeID[0] == 'K'){

        if(nodeID[2] == 'S' && nodeID[3] == 'O'){
            auto dt = new DecisionTreeNode(nodeID.toStdString());
            dt->setTarget("Species");
            TokPodataka->add(dt);
        }

        if(nodeID[2] == 'P'){
            auto prcn = new PerceptronNode(nodeID.toStdString());
            TokPodataka->add(prcn);
        }


    }else if(nodeID[0] == 'C'){

        if(nodeID[2] == 'K' && nodeID[3] == 'S'){
            auto ks = new KMeansNode(nodeID.toStdString());
            TokPodataka->add(ks);
        }

    }else if(nodeID[0] == 'R'){

        if(nodeID[2] == 'L'){            
            auto lrn = new LinearRegressionNode(nodeID.toStdString());
            TokPodataka->add(lrn);
        }


    }else
        return;

}

void MainWindow::on_ConnectButton_clicked()
{

    auto selektovaniCvorovi = scena->selectedItems();

    //provera da li su selektovana tacno 2 cvora
    if(selektovaniCvorovi.size() > 2 or selektovaniCvorovi.size() < 2)
        return;


    //kastujemo u selektovane cvorove u SceneNode da bismo izvukli njihov ID
    auto tmp1 = static_cast<SceneNode*>(selektovaniCvorovi[0]);
    auto tmp2 = static_cast<SceneNode*>(selektovaniCvorovi[1]);

    SceneNode* cvor1;
    SceneNode* cvor2;

    //u zavisnosti od oznake cvora postavjaju se vrednosti promenljivih cvor1 i cvor2
    //videti klasu SceneNode za detaljnije objasnjenje oznake
    if(tmp1->GetNodeState() == SceneNode::Oznacen_1 && tmp2->GetNodeState() == SceneNode::Oznacen_2){

        cvor1 = static_cast<SceneNode*>(selektovaniCvorovi[0]);
        cvor2 = static_cast<SceneNode*>(selektovaniCvorovi[1]);

    }else if(tmp1->GetNodeState() == SceneNode::Oznacen_2 && tmp2->GetNodeState() == SceneNode::Oznacen_1){

        cvor1 = static_cast<SceneNode*>(selektovaniCvorovi[1]);
        cvor2 = static_cast<SceneNode*>(selektovaniCvorovi[0]);
    }else{
        std::cout << "Los Odabir Cvorova!" << std::endl;
        return;
    }

    //brisemo oznaku
    cvor1->ClearNodeState();
    cvor2->ClearNodeState();

    //pravimo liniju tj vezi izmedju odabranih cvorova na sceni
    auto* l = new ConnectionLine(cvor1, cvor2);
    scena->addItem(l);

    ui->GlavniTok->setScene(scena);

    //izvlacimo ID-jeve cvorova
    QString id1 = static_cast<SceneNode*>(cvor1)->getID();
    QString id2 = static_cast<SceneNode*>(cvor2)->getID();    

    auto mapaCvorova = TokPodataka->MapOfNodes();

    Node* prvi  = nullptr;
    Node* drugi = nullptr;

    //pronalazenje cvorova u toku podataka
    for(std::pair<Node*, Node*> e : mapaCvorova){

        if(!e.first->NodeName().compare(id1.toStdString()))
            prvi = e.first;

        if(!e.first->NodeName().compare(id2.toStdString()))
            drugi = e.first;
    }


    //vezivaje cvorova i unutar TokaPodataka
    TokPodataka->connect_to(prvi, drugi);

    /*
    mapaCvorova = TokPodataka->MapOfNodes();

    for(std::pair<Node*, Node*> e : mapaCvorova){

        if(e.second == nullptr)
            std::cout << e.first->NodeName() << ":" << "nullptr" << std::endl;
        else
            std::cout << e.first->NodeName() << ":" << e.second->NodeName() << std::endl;
    }
    */

}

void MainWindow::on_RunStreamButton_clicked()
{
    //dohvatanje cvora odabranog cvora sa scene
    auto odabranCvor = scena->selectedItems();
    if(odabranCvor.size() != 1)
        return;

    auto cvorSaScene = odabranCvor[0];
    QString ID = static_cast<SceneNode*>(cvorSaScene)->getID();

    //pronalazenje cvora u toku podataka
    Node* cvorIzMape = nullptr;
    auto mapaCvorova = TokPodataka->MapOfNodes();
    for(std::pair<Node*, Node*> e : mapaCvorova){

        if(!e.first->NodeName().compare(ID.toStdString()))
            cvorIzMape = e.first;
    }

    //pozivanje f-je za pokretanje toka
    TokPodataka->RunStream(cvorIzMape);
}

void MainWindow::on_DisconnectButton_clicked()
{

    //analogno fji za povezivanje cvorova

    auto selektovaniCvorovi = scena->selectedItems();

    //osiguravamo se da su odabrana dva cvora
    if(selektovaniCvorovi.size() > 2 or selektovaniCvorovi.size() < 2)
        return;

    auto tmp1 = static_cast<SceneNode*>(selektovaniCvorovi[0]);
    auto tmp2 = static_cast<SceneNode*>(selektovaniCvorovi[1]);

    SceneNode* cvor1;
    SceneNode* cvor2;

    //proveravamo oznake
    if(tmp1->GetNodeState() == SceneNode::Oznacen_1 && tmp2->GetNodeState() == SceneNode::Oznacen_2){

        cvor1 = static_cast<SceneNode*>(selektovaniCvorovi[0]);
        cvor2 = static_cast<SceneNode*>(selektovaniCvorovi[1]);

    }else if(tmp1->GetNodeState() == SceneNode::Oznacen_2 && tmp2->GetNodeState() == SceneNode::Oznacen_1){

        cvor1 = static_cast<SceneNode*>(selektovaniCvorovi[1]);
        cvor2 = static_cast<SceneNode*>(selektovaniCvorovi[0]);
    }else{
        std::cout << "Los Odabir Cvorova!" << std::endl;
        return;
    }

    cvor1->ClearNodeState();
    cvor2->ClearNodeState();


    //dohvatamo odgovarajucu liniju koja povezuje ta dva cvora i brisemo je
    auto sviElementi = scena->items();

    ConnectionLine* nekaLinija;
    ConnectionLine* linijaZaBrisanje = nullptr;

    for(auto i : sviElementi){
        if((nekaLinija = dynamic_cast<ConnectionLine*>(i))){

            if(nekaLinija->getPocetniCvor() == cvor1 && nekaLinija->getKrajnjiCvor() == cvor2){
                linijaZaBrisanje = nekaLinija;
                break;
            }
        }
    }

    //brisanje linije
    scena->removeItem(linijaZaBrisanje);

    //dohvatamo id drugog cvora
    QString id2 = static_cast<SceneNode*>(cvor2)->getID();

    auto mapaCvorova = TokPodataka->MapOfNodes();

    Node* drugi = nullptr;

    //pronalazenje drugog cvorova u toku podataka
    for(std::pair<Node*, Node*> e : mapaCvorova){

        if(!e.first->NodeName().compare(id2.toStdString()))
            drugi = e.first;
    }

    //brisanje veze i iz toka podataka
    TokPodataka->disconnect(drugi);


    //ispis mape radi provere
    /*
    mapaCvorova = TokPodataka->MapOfNodes();

    for(std::pair<Node*, Node*> e : mapaCvorova){

        if(e.second == nullptr)
            std::cout << e.first->NodeName() << ":" << "nullptr" << std::endl;
        else
            std::cout << e.first->NodeName() << ":" << e.second->NodeName() << std::endl;
    }
    */
}

void MainWindow::on_ClearScene_clicked()
{
    //uklanjamo sve cvorove sa scene, kao i iz toka podataka
    scena->clear();
    TokPodataka = new Stream();
}

QString MainWindow::generisiID(QString nazivAlgoritma)
{
    //generisanje jedinstvenog ID-a za svaki cvor
    //na osnovu njega se pravi veza izmedju cvorova na sceni i cvorova u glavnom toku podataka
    //jer je taj ID jedinstven i za cvorove u glavnom toku a isti kao ID njihovOG odogovarajucEG cvora na sceni

    //pri generisanju jedinstvenog ID-a za cvorove brine se i o ukupnom broju cvorova
    //f-ja uvecava ukupan broj cvorova

    QString nodeName("");

    if(!nazivAlgoritma.compare("Ulazni Podaci")){

        nodeName = nodeName.append("U_"); //ulaz
        nodeName = nodeName.append("P_"); //podaci
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));

    }else if(!nazivAlgoritma.compare("Particionisanje")){

        nodeName = nodeName.append("P_"); //perprocesiranje
        nodeName = nodeName.append("P_"); //particionisanje
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));


    }else if(!nazivAlgoritma.compare("Normalizacija")){

        nodeName = nodeName.append("P_"); //preprocesiranje
        nodeName = nodeName.append("N_"); //normalizacija
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));


    }else if(!nazivAlgoritma.compare("Uzorkovanje")){

        nodeName = nodeName.append("P_"); //preprocesiranje
        nodeName = nodeName.append("U_"); //uzorkovanje
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));

    }else if(!nazivAlgoritma.compare("Filter")){

        nodeName = nodeName.append("P_"); //preprocesiranje
        nodeName = nodeName.append("F_"); //filter
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));


    }else if(!nazivAlgoritma.compare("Statistike")){

        nodeName = nodeName.append("P_"); //preprocesiranje
        nodeName = nodeName.append("S_"); //statistike
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));


    }else if(!nazivAlgoritma.compare("Stablo Odlucivanja")){

        nodeName = nodeName.append("K_");  //klasifikacija
        nodeName = nodeName.append("SO_"); //stablo odlucivanja
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));


    }else if(!nazivAlgoritma.compare("Perceptron")){

        nodeName = nodeName.append("K_"); //klasifikacija
        nodeName = nodeName.append("P_"); //perceptron
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));

    }else if(!nazivAlgoritma.compare("K-Sredina")){

        nodeName = nodeName.append("C_");  //klasterovanje
        nodeName = nodeName.append("KS_"); //K-Sredina
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));

    }else if(!nazivAlgoritma.compare("Prosta Linearna Regresija")){

        nodeName = nodeName.append("R_"); //regresija
        nodeName = nodeName.append("L_"); //prosta lin. regresija
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));


    }else
        return "";

    //std::cout << nodeName.toStdString() << std::endl;

    return nodeName;
}

void MainWindow::on_DataViewButton_clicked()
{

    //za odabrani cvor fja ispisuje rezultate u prozor TableDialog

    auto selektovaniCvorovi = scena->selectedItems();


    if(selektovaniCvorovi.size() > 1 or selektovaniCvorovi.size() < 1)
        return;

    //kast iz QGraphicsItem u SceneNode
    auto cvor_S = static_cast<SceneNode*>(selektovaniCvorovi[0]);

    QString id = static_cast<SceneNode*>(cvor_S)->getID();

    Node* Cvor = pronadjiCvor(id);

    //pravljenje prozora i ispis rezultata cvora
    TableDialog td;
    td.setModal(true);
    td.view(Cvor);
    td.exec();
}

Node *MainWindow::pronadjiCvor(QString id)
{
    auto mapaCvorova = TokPodataka->MapOfNodes();
    Node* Cvor = nullptr;
    for(std::pair<Node*, Node*> e : mapaCvorova){

        if(!e.first->NodeName().compare(id.toStdString()))
            Cvor = e.first;
    }

    return Cvor;
}

//slede f-je za detektovanje odabrane liste algoritama
void MainWindow::on_LISTA_Preprocesiranje_clicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    izabranaLista = "Prepocesiranje";

}
void MainWindow::on_LISTA_Klasifikacija_clicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    izabranaLista = "Klasifikacija";
}
void MainWindow::on_LISTA_Klasterovanje_clicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    izabranaLista = "Klasterovanje";
}
void MainWindow::on_LISTA_LinReg_clicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    izabranaLista = "LinearnaRegresija";
}
void MainWindow::on_LISTA_Ulaz_clicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    izabranaLista = "Ulaz";
}


void MainWindow::on_SetParameters_clicked()
{
    //fja se poziva na pritisak dugmeta za postavljanje parametara cvora


    //dohvatanje odabranog cvora na sceni
    auto selektovaniCvorovi = scena->selectedItems();

    if(selektovaniCvorovi.size() > 1 or selektovaniCvorovi.size() < 1)
        return;

    auto cvor_S = static_cast<SceneNode*>(selektovaniCvorovi[0]);

    QString nodeID = static_cast<SceneNode*>(cvor_S)->getID();

    //pronalazenje odgovarajuceg cvora u glanom toku podataka
    Node* Cvor = pronadjiCvor(nodeID);


    //pozivanje odgovarajuce fje za postavljanje parametara u zavisnosti od tipa odabranog cvora
    //svaka fja otvara poseban prozor za unos podataka

    if(nodeID[0] == 'U'){

        if(nodeID[2] == 'P'){
            podesiParametre_Ulazni(Cvor);
        }


    }else if(nodeID[0] == 'P'){

        if(nodeID[2] == 'U'){
           podesiParametre_Uzorkovanje(Cvor);
        }

        if(nodeID[2] == 'P'){
            podesiParametre_Particionisanje(Cvor);
        }

        if(nodeID[2] == 'F'){
            podesiParametre_Filter(Cvor);
        }


    }else if(nodeID[0] == 'C'){

        if(nodeID[2] == 'K' && nodeID[3] == 'S'){
            podesiParametre_KSredina(Cvor);
        }

    }else if(nodeID[0] == 'K'){

        if(nodeID[2] == 'S' && nodeID[3] == 'O'){
            podesiParametre_StabloOdlucivanja(Cvor);
        }

        if(nodeID[2] == 'P'){
            podesiParametre_Perceptron(Cvor);
        }


    }else if(nodeID[0] == 'R'){

        if(nodeID[2] == 'L'){
            podesiParametre_LinearnaRegresija(Cvor);
        }


    }else
        return;

}

//u nastavku slede fje za otvaranje prozora u kojima korisnik moze postaviti parametre za odabrane cvorova

void MainWindow::podesiParametre_Ulazni(Node *cvor)
{
    auto* Src = dynamic_cast<SourceNode*>(cvor);
    SourceParametersDialog spD(Src);
    spD.setModal(true);
    spD.exec();
}

void MainWindow::podesiParametre_Uzorkovanje(Node *cvor)
{
    auto* sm = dynamic_cast<SamplingNode*>(cvor);
    SamplingParametersDialog smD(sm);
    smD.setModal(true);
    smD.exec();
}

void MainWindow::podesiParametre_Particionisanje(Node *cvor)
{
    auto* Prt = dynamic_cast<PartitionNode*>(cvor);
    PartitionParametersDialog prtD(Prt);
    prtD.setModal(true);
    prtD.exec();
}

void MainWindow::podesiParametre_Filter(Node *cvor)
{
    auto* fil = dynamic_cast<FilterNode*>(cvor);
    FilterParametersDialog filD(fil);
    filD.setModal(true);
    filD.exec();
}

void MainWindow::podesiParametre_KSredina(Node *cvor)
{
    auto* km = dynamic_cast<KMeansNode*>(cvor);
    KMeansParametersDialog kmD(km);
    kmD.setModal(true);
    kmD.exec();
}

void MainWindow::podesiParametre_StabloOdlucivanja(Node *cvor)
{
    auto* dt = dynamic_cast<DecisionTreeNode*>(cvor);
    DecisionTreeParametersDialog dtD(dt);
    dtD.setModal(true);
    dtD.exec();
}

void MainWindow::podesiParametre_Perceptron(Node *cvor)
{
    auto* pr = dynamic_cast<PerceptronNode*>(cvor);
    PerceptronParametersDialog prD(pr);
    prD.setModal(true);
    prD.exec();
}

void MainWindow::podesiParametre_LinearnaRegresija(Node *cvor)
{
    auto* ln = dynamic_cast<LinearRegressionNode*>(cvor);
    LinearRegressionParametersDialog linD(ln);
    linD.setModal(true);
    linD.exec();

}
