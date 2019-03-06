#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileSystemModel>

class Dialog : public QDialog
{
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
};

#endif // DIALOG_H
