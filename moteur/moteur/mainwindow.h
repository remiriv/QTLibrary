#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "persistentattribute.h"
#include "persistentmodel.h"
#include "persistentobject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU
    QString currentDB;

public:
    explicit MainWindow(QWidget *parent = 0,QString path="");
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString path;
    void createUI(const QStringList &headers);
    void createActions();
    void createMenus();
    QList<PersistentObject*> liste;
    PersistentModel* model;
    QList<PersistentObject*> deleted;
    void display();

    QMenu *fichierMenu;
    QMenu *editionMenu;
    QMenu *aideMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *addAct;
    QAction *delAct;

private slots:
    void newFile();
    void open();
    void save();
    void saveAs();
    void add();
    void del();

public slots:

signals:

};

#endif // MAINWINDOW_H
