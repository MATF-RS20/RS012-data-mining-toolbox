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


}


//Destruktor Glavnog Prozora
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_AddNodeButton_clicked()
{


    QString nazivAlgoritma;

    //dohvatanje naziva algoritma iz liste
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


    auto nodeID = generisiID(nazivAlgoritma);

    nacrtajCvor(nodeID);

    dodajCvorUTok(nodeID);

}

void MainWindow::nacrtajCvor(QString nodeID){


    SceneNode *sn = new SceneNode(nodeID);

    scena->addItem(sn);

    ui->GlavniTok->setScene(scena);
}

void MainWindow::dodajCvorUTok(QString nodeID){

    Node *noviCvor;

    if(nodeID[0] == 'U'){

        if(nodeID[2] == 'P'){
            noviCvor = new SourceNode(nodeID.toStdString());
            auto sn = static_cast<SourceNode*>(noviCvor);
            sn->setFilename("../RS012-data-mining-toolbox/iris.csv");
            sn->read();
            TokPodataka->add(sn);
        }


    }else if(nodeID[0] == 'P'){

        if(nodeID[2] == 'P'){
            noviCvor = new PartitionNode(nodeID.toStdString());
            TokPodataka->add(noviCvor);
        }

        if(nodeID[2] == 'N'){
            noviCvor = new NormalizationNode(nodeID.toStdString());
            TokPodataka->add(noviCvor);
        }

        if(nodeID[2] == 'S'){
            noviCvor = new StatisticsNode(nodeID.toStdString());
            TokPodataka->add(noviCvor);
        }

        if(nodeID[2] == 'U'){
            noviCvor = new SamplingNode(nodeID.toStdString());
            TokPodataka->add(noviCvor);
        }

        if(nodeID[2] == 'F'){
            //FilterNode
            //Nije jos implementirano
            return;
        }


    }else if(nodeID[0] == 'K'){

        if(nodeID[2] == 'D' && nodeID[3] == 'T'){
            noviCvor = new DecisionTreeNode(nodeID.toStdString());
            auto dt = static_cast<DecisionTreeNode*>(noviCvor);
            dt->setTarget("Species");
            TokPodataka->add(dt);
        }

        if(nodeID[2] == 'P'){
            noviCvor = new PerceptronNode(nodeID.toStdString());
            TokPodataka->add(noviCvor);
        }


    }else if(nodeID[0] == 'C'){

        if(nodeID[2] == 'K' && nodeID[3] == 'M'){
            //KMeans
            //nije jos implementirano
            return;
        }

    }else if(nodeID[0] == 'R'){

        if(nodeID[2] == 'L'){
            noviCvor = new LinearRegressionNode(nodeID.toStdString());
            TokPodataka->add(noviCvor);
        }


    }else
        return;

}





void MainWindow::on_ConnectButton_clicked()
{

    auto selektovaniCvorovi = scena->selectedItems();


    if(selektovaniCvorovi.size() > 2 or selektovaniCvorovi.size() < 2)
        return;


    auto cvor1 = selektovaniCvorovi[0];
    auto cvor2 = selektovaniCvorovi[1];        

    ConnectionLine* l = new ConnectionLine(cvor1, cvor2);
    scena->addItem(l);

    ui->GlavniTok->setScene(scena);


    QString id1 = static_cast<SceneNode*>(cvor1)->getID();
    QString id2 = static_cast<SceneNode*>(cvor2)->getID();

    //-------------------------

    auto mapaCvorova = TokPodataka->MapOfNodes();

    Node* prvi  = nullptr;
    Node* drugi = nullptr;

    //pronalazenje cvorova
    for(std::pair<Node*, Node*> e : mapaCvorova){

        if(!e.first->NodeName().compare(id1.toStdString()))
            prvi = e.first;

        if(!e.first->NodeName().compare(id2.toStdString()))
            drugi = e.first;
    }




    TokPodataka->connect_to(prvi, drugi);


    mapaCvorova = TokPodataka->MapOfNodes();

    for(std::pair<Node*, Node*> e : mapaCvorova){

        if(e.second == nullptr)
            std::cout << e.first->NodeName() << ":" << "nullptr" << std::endl;
        else
            std::cout << e.first->NodeName() << ":" << e.second->NodeName() << std::endl;
    }

}






QString MainWindow::generisiID(QString nazivAlgoritma)
{
    //pri generisanju jedinstvenog ID-a za cvorove brine se i o ukupnom broju cvorova
    //f-ja uvecava ukupan broj cvorova

    QString nodeName("");

    if(!nazivAlgoritma.compare("Ulazni Podaci")){

        nodeName = nodeName.append("U_");
        nodeName = nodeName.append("P_");
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));

    }else if(!nazivAlgoritma.compare("Particionisanje")){

        nodeName = nodeName.append("P_");
        nodeName = nodeName.append("P_");
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));


    }else if(!nazivAlgoritma.compare("Normalizacija")){

        nodeName = nodeName.append("P_");
        nodeName = nodeName.append("N_");
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));


    }else if(!nazivAlgoritma.compare("Uzorkovanje")){

        nodeName = nodeName.append("P_");
        nodeName = nodeName.append("U_");
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));

    }else if(!nazivAlgoritma.compare("Filter")){

        nodeName = nodeName.append("P_");
        nodeName = nodeName.append("F_");
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));


    }else if(!nazivAlgoritma.compare("Statistike")){

        nodeName = nodeName.append("P_");
        nodeName = nodeName.append("S_");
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));


    }else if(!nazivAlgoritma.compare("Stablo Odlucivanja")){

        nodeName = nodeName.append("K_");
        nodeName = nodeName.append("DT_");
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));


    }else if(!nazivAlgoritma.compare("Perceptron")){

        nodeName = nodeName.append("K_");
        nodeName = nodeName.append("P_");
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));

    }else if(!nazivAlgoritma.compare("K-Sredina")){

        nodeName = nodeName.append("C_");
        nodeName = nodeName.append("KM_");
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));

    }else if(!nazivAlgoritma.compare("DBSCAN")){

        //JOS NIJE IMPLEMENTIRANO
        return "";

    }else if(!nazivAlgoritma.compare("Prosta Linearna Regresija")){

        nodeName = nodeName.append("R_");
        nodeName = nodeName.append("L_");
        broj_cvorova++;
        nodeName = nodeName.append(QString::number(broj_cvorova));


    }else
        return "";

    std::cout << nodeName.toStdString() << std::endl;
    return nodeName;



}





void MainWindow::on_RunStreamButton_clicked()
{

    auto odabranCvor = scena->selectedItems();
    if(odabranCvor.size() != 1)
        return;

    auto cvorSaScene = odabranCvor[0];
    QString ID = static_cast<SceneNode*>(cvorSaScene)->getID();


    Node* cvorIzMape = nullptr;
    auto mapaCvorova = TokPodataka->MapOfNodes();
    for(std::pair<Node*, Node*> e : mapaCvorova){

        if(!e.first->NodeName().compare(ID.toStdString()))
            cvorIzMape = e.first;
    }

    TokPodataka->RunStream(cvorIzMape);
}

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
