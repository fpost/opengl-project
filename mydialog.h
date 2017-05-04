#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>

class MyDialog : public QDialog
{
private:
    QVBoxLayout* layout;
    QDialogButtonBox* buttonBox;
    void setUpWindow();

public:
    MyDialog();
};

#endif // MYDIALOG_H
