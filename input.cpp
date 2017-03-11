#include "input.h"
#include "ui_input.h"

Input::Input(QWidget *parent, ArchivoTexto * text) :QDialog(parent), ui(new Ui::Input){
    ui->setupUi(this);
    this->text = text;
    this->setWindowTitle(text->getNombre());
    ui->textEdit->setText(text->getContenido());
}

Input::~Input(){
    delete ui;
}

void Input::on_buttonBox_accepted(){
    text->setContenido(ui->textEdit->toPlainText());
}
