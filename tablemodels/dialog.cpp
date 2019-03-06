#include "dialog.h"
#include "../blazycachedmodel.h"
#include "../btablemodel.h"
#include <QPushButton>
#include <QTableView>
#include <QHBoxLayout>
#include <QDebug>



Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{            
        QFileInfo fi("dialog.cpp");
        qDebug() << fi.absolutePath() << fi.absoluteFilePath();
        BTableModel  *simpleModel;
        simpleModel = new BTableModel(this);
        QTableView *tableView = new QTableView(this);
        tableView->setModel(simpleModel);
        tableView->setMinimumSize(5,5);
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addWidget(tableView);
        setLayout(layout);
        setMinimumSize(100,100);
}

Dialog::~Dialog()
{

}
