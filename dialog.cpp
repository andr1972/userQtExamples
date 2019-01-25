#include "dialog.h"
#include "bexamplemodel.h"
#include "blazycachedmodel.h"
#include "bdirmodel.h"
#include <QSplitter>
#include <QPushButton>
#include <QTreeView>
#include <QHBoxLayout>
#include <QDebug>
#include <QFileInfo>
#include <QFileSystemModel>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{            
        QFileInfo fi("dialog.cpp");
        qDebug() << fi.absolutePath() << fi.absoluteFilePath();
        BExampleModel  *simpleModel;
        simpleModel = new BExampleModel(this);
        QTreeView *treeView1 = new QTreeView(this);
        treeView1->setModel(simpleModel);
        treeView1->setMinimumSize(5,5);

        BLazyCachedModel  *lazyModel;
        lazyModel = new BLazyCachedModel(this,3,3);
        QTreeView *treeView2 = new QTreeView(this);
        treeView2->setModel(lazyModel);
        treeView2->setMinimumSize(5,5);

        BDirModel  *dirModel;
        dirModel = new BDirModel(this,3,3);
        QTreeView *treeView3 = new QTreeView(this);
        treeView3->setModel(dirModel);
        treeView3->setMinimumSize(5,5);

        QFileSystemModel *qtModel;
        qtModel = new QFileSystemModel(this);
        qtModel->setFilter(QDir::Dirs | QDir::Drives | QDir::NoDotAndDotDot |QDir::Files);
        qtModel->setRootPath("");
        QTreeView *treeView4 = new QTreeView(this);
        treeView4->setModel(qtModel);
        treeView4->setMinimumSize(5,5);

        QSplitter *h1Splitter = new QSplitter(this);
        QSplitter *h2Splitter = new QSplitter(this);

        QSplitter *vSplitter = new QSplitter(this);
        vSplitter->setOrientation(Qt::Vertical);

        vSplitter->addWidget(h1Splitter);
        vSplitter->addWidget(h2Splitter);

        h1Splitter->addWidget(treeView1);
        h1Splitter->addWidget(treeView2);
        h2Splitter->addWidget(treeView3);
        h2Splitter->addWidget(treeView4);

        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addWidget(vSplitter);
        setLayout(layout);
        setMinimumSize(100,100);
}

Dialog::~Dialog()
{

}
