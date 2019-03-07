#include "dialog.h"
#include "../blazycachedmodel.h"
#include "../btablemodel.h"
#include <QPushButton>
#include <QTableView>
#include <QHBoxLayout>
#include <QDebug>


struct MyData : public IVariantable
{
    QString name;
    int age;
    QVariant getData(int col);
};

QVariant MyData::getData(int col)
{
    switch(col)
    {
        case 0: return name;
        case 1: return age;
    default: return QVariant();
    }
}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
        QStringList headers = {"Name","Age"};
        QList<IVariantable*> list;
        MyData *rec;
        rec = new MyData;
        rec->name = "Adam";
        rec->age = 23;
        list.append(rec);
        rec = new MyData;
        rec->name = "John";
        rec->age = 35;
        list.append(rec);
        QFileInfo fi("dialog.cpp");
        qDebug() << fi.absolutePath() << fi.absoluteFilePath();
        BTableModel  *simpleModel;
        simpleModel = new BTableModel(this);
        simpleModel->setList(list, headers);
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
