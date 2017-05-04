#include "mydialog.h"

MyDialog::MyDialog()
{
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout = new QVBoxLayout;
    setUpWindow();
}

void MyDialog::setUpWindow()
{
    layout->addWidget(buttonBox);
    setLayout(layout);
}
