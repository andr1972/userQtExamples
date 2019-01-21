#include "dialog.h"
#include "bexamplemodel.h"
#include <QSplitter>
#include <QPushButton>
#include <QTreeView>
#include <QHBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{            
        BExampleModel  *tempModel;
        tempModel = new BExampleModel(this);
        QTreeView *treeView = new QTreeView(this);
        treeView->setModel(tempModel);
        treeView->setMinimumSize(5,5);

        QSplitter *h1Splitter = new QSplitter(this);
        QSplitter *h2Splitter = new QSplitter(this);

        QSplitter *vSplitter = new QSplitter(this);
        vSplitter->setOrientation(Qt::Vertical);

        vSplitter->addWidget(h1Splitter);
        vSplitter->addWidget(h2Splitter);

        h1Splitter->addWidget(treeView);

        QPushButton *view = new QPushButton(this);        
        h1Splitter->addWidget(view);

        view = new QPushButton(this);
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
