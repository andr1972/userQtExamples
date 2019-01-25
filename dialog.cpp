#include "dialog.h"
#include "bexamplemodel.h"
#include "blazycachedmodel.h"
#include <QSplitter>
#include <QPushButton>
#include <QTreeView>
#include <QHBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{            
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

        QSplitter *h1Splitter = new QSplitter(this);
        QSplitter *h2Splitter = new QSplitter(this);

        QSplitter *vSplitter = new QSplitter(this);
        vSplitter->setOrientation(Qt::Vertical);

        vSplitter->addWidget(h1Splitter);
        vSplitter->addWidget(h2Splitter);

        h1Splitter->addWidget(treeView1);
        h1Splitter->addWidget(treeView2);

        QPushButton *view = new QPushButton(this);
        h2Splitter->addWidget(view);

        view  = new QPushButton(this);
        h2Splitter->addWidget(view);

        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addWidget(vSplitter);
        setLayout(layout);
        setMinimumSize(100,100);
}

Dialog::~Dialog()
{

}
