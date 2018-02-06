#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"
#include <QtGui>

#include "livre.h"

MainWindow::MainWindow(QWidget *parent,QString path) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->createUI(QStringList() << trUtf8("Auteurs")
                   << trUtf8("Titre")
                   << trUtf8("ISBN")
                   << trUtf8("Année")
                   );
    this->createActions();
    this->createMenus();
    this->model = new PersistentModel();
    this->liste = this->model->load("moteur", QString("livre"),path);
    this->currentDB=QString("moteur");
    this->display();
    this->path=path;
}

void MainWindow::display(){
    ui->tableWidget->setRowCount(this->liste.length());
    for(int i=0; i<this->liste.length(); i++) {
            QTableWidgetItem *auteurs = new QTableWidgetItem(((Livre*)this->liste.at(i))->auteurs.join("/"));
            ui->tableWidget->setItem(i, 0, auteurs);
            QTableWidgetItem *titre = new QTableWidgetItem(((Livre*)this->liste.at(i))->titre);
            ui->tableWidget->setItem(i, 1, titre);
            QTableWidgetItem *ISBN = new QTableWidgetItem(((Livre*)this->liste.at(i))->ISBN);
            ui->tableWidget->setItem(i, 2, ISBN);
            QTableWidgetItem *annee = new QTableWidgetItem(QString::number(((Livre*)this->liste.at(i))->annee));
            ui->tableWidget->setItem(i, 3, annee);
    }
    ui->retranslateUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createUI(const QStringList &headers)
{
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->resizeColumnsToContents();
}


void MainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setText(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open"), this);
    openAct->setText(tr("Open file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setText(tr("Save file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    saveAsAct = new QAction(tr("&Save as ..."), this);
    saveAsAct->setText(tr("Save a file as..."));
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveAs);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setStatusTip(tr("Exit the application"));
    QObject::connect(exitAct, &QAction::triggered, this, &QWidget::close);

    addAct = new QAction(tr("&Add book"), this);
    addAct->setText(tr("Add a book"));
    connect(addAct, &QAction::triggered, this, &MainWindow::add);

    delAct = new QAction(tr("&Delete book"), this);
    delAct->setText(tr("Delete a book"));
    connect(delAct, &QAction::triggered, this, &MainWindow::del);

}

void MainWindow::createMenus()
{
    fichierMenu = menuBar()->addMenu(tr("&Fichier"));
    fichierMenu->addAction(newAct);
    fichierMenu->addAction(openAct);
    fichierMenu->addAction(saveAct);
    fichierMenu->addAction(saveAsAct);
    fichierMenu->addSeparator();
    fichierMenu->addAction(exitAct);

    editionMenu = menuBar()->addMenu(tr("&Edition"));
    editionMenu->addAction(addAct);
    editionMenu->addAction(delAct);

    aideMenu = menuBar()->addMenu(tr("&Aide"));
}


#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::newFile()
{
//    QSqlQuery::finish();
    this->model->db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::database(this->currentDB).connectionName());
    QString result = QInputDialog::getText(0, "Text input", "Value:");
    this->currentDB=result;
    this->model->createDatabase(result,this->path);
    this->liste=this->model->load(result, QString("livre"),this->path);
    this->display();
}

void MainWindow::open()
{
//    QSqlQuery::finish();
    this->model->db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::database(this->currentDB).connectionName());
    QString result = QInputDialog::getText(0, "Text input", "Value:");
    this->currentDB=result;
    this->model->createDatabase(result,this->path);
    this->liste=this->model->load(result, QString("livre"),this->path);
    this->display();
}

void MainWindow::save()
{
    for(PersistentObject *p:this->liste){
        p->save();
    }
    for(PersistentObject* p:this->deleted){
        p->delet();
    }
    this->display();
}

void MainWindow::saveAs()
{
}

void MainWindow::add()
{
    QStringList auteurs = QStringList(QInputDialog::getText(0, "Text input", "Auteurs:"));
    QString titre = QInputDialog::getText(0, "Text input", "Titre:");
    QString ISBN = QInputDialog::getText(0, "Text input", "ISBN:");
    int annee = QInputDialog::getText(0, "Text input", "Annee:").toInt();

    Livre* livre = new Livre(auteurs, titre, ISBN, annee);
    livre->setDBName(this->currentDB);
    this->liste.append(livre);
    int index=this->liste.size()-1;
    ui->tableWidget->setRowCount(this->liste.length());

    QTableWidgetItem *auteursW = new QTableWidgetItem(livre->auteurs.join("/"));
    ui->tableWidget->setItem(index, 0, auteursW);

    QTableWidgetItem *titreW = new QTableWidgetItem(livre->titre);
    ui->tableWidget->setItem(index, 1, titreW);

    QTableWidgetItem *ISBNW = new QTableWidgetItem(livre->ISBN);
    ui->tableWidget->setItem(index, 2, ISBNW);

    QTableWidgetItem *anneeW = new QTableWidgetItem(QString::number(livre->annee));
    ui->tableWidget->setItem(index, 3, anneeW);
    ui->retranslateUi(this);

}

void MainWindow::del()
{
    QString result = QInputDialog::getText(0, "Text input", "Value:");
    PersistentObject* p;
    for(int i=0;i<this->liste.length();i++){
        p=this->liste.at(i);
        if((((Livre*)p)->ISBN)==result){
            this->deleted.append(this->liste.takeAt(i));
            i--;
        }
    }
    this->display();
}
