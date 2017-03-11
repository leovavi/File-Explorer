#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include <QString>
#include "archivotexto.h"

namespace Ui {
class Input;
}

class Input : public QDialog
{
    Q_OBJECT

public:
    explicit Input(QWidget *parent, ArchivoTexto * text);
    ~Input();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Input *ui;
    ArchivoTexto * text;
};

#endif // INPUT_H
