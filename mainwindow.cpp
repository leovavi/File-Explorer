#include "mainwindow.h"
#include "ui_mainwindow.h"

extern FileSystem * fs;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(parent);
    ui->graphicsView->setScene(scene);

    extern FileSystem * fs;
    selected = fs->raiz;

    ui->label->setText(selected->getRuta());
    ui->cant->setText("Cantidad: " + QString::number(fs->selected->getCantidadArchivos()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSelected(Folder * f){
    selected = f;
}

void MainWindow::pintarFiles(){
    extern FileSystem * fs;
    scene->clear();

    Lista * l = fs->listarArchivos(selected);

    int posX = -100;
    int posY = 0;

    for(int i = 0; i<l->tamano(); i++){
        Archivo * temp = l->obtener(i);

        posY = (posX>=460 ? posY + 140 : posY);
        posX = (posX>=460 ? 30 : posX + 130);

        scene->addItem(new Files(temp, posX, posY));

    }

    posY = (posY<=140 ? 380 : posY + 150);
    scene->setSceneRect(0, 0, 680, posY);
}

void MainWindow::refresh()
{
    extern FileSystem * fs;
    setSelected(fs->selected);
    ui->graphicsView->viewport()->update();
    pintarFiles();
    ui->label->setText(selected->getRuta());
    ui->cant->setText("Cantidad: " + QString::number(fs->selected->getCantidadArchivos()));
}

void MainWindow::on_btnFolder_clicked()
{
    extern FileSystem * fs;
    bool confirm = false;

    QString text = QInputDialog::getText(this, tr("Nuevo Folder"), tr("Nombre:"), QLineEdit::Normal, "", &confirm);

    if(confirm && !(text.isEmpty())){
        fs->agregarArchivo(selected, text, 2);
        refresh();
    }

}

void MainWindow::on_btnArchivo_clicked()
{
    bool confirm = false;

    QString text = QInputDialog::getText(this, tr("Nuevo Archivo de Texto"), tr("Nombre:"), QLineEdit::Normal, "", &confirm);

    if(confirm && !(text.isEmpty())){
        fs->agregarArchivo(selected, text, 1);
        refresh();
    }
}
