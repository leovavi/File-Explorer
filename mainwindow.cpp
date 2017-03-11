#include "mainwindow.h"
#include "ui_mainwindow.h"

extern FileSystem * fs;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    selected = NULL;
    clipboard = NULL;

    scene = new QGraphicsScene(parent);
    ui->graphicsView->setScene(scene);

    fs = new FileSystem();

    actualFolder = fs->raiz;
    ui->label->setText(actualFolder->getRuta());
    ui->cant->setText("Cantidad: " + QString::number(actualFolder->getCantidadArchivos()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pintarFiles(){
    scene->clear();

    Lista * l = fs->listarArchivos(actualFolder);

    int posX = -100;
    int posY = 0;

    for(int i = 0; i<l->tamano(); i++){
        Archivo * temp = l->obtener(i);

        bool paint = (temp == selected ? true : false);

        posY = (posX>=460 ? posY + 140 : posY);
        posX = (posX>=460 ? 30 : posX + 130);

        scene->addItem(new Files(temp, posX, posY, paint));

    }

    posY = (posY<=140 ? 380 : posY + 150);
    scene->setSceneRect(0, 0, 680, posY);
}

void MainWindow::refresh()
{
    ui->graphicsView->viewport()->update();
    pintarFiles();
    ui->label->setText(actualFolder->getRuta());
    ui->cant->setText("Cantidad: " + QString::number(actualFolder->getCantidadArchivos()));
}

void MainWindow::on_btnFolder_clicked()
{
    bool confirm = false;

    QString text = QInputDialog::getText(this, tr("Nuevo Folder"), tr("Nombre:"), QLineEdit::Normal, "", &confirm);

    if(confirm && !(text.isEmpty())){
        fs->agregarArchivo(actualFolder, text, 2);
        refresh();
    }

}

void MainWindow::on_btnArchivo_clicked()
{
    bool confirm = false;

    QString text = QInputDialog::getText(this, tr("Nuevo Archivo de Texto"), tr("Nombre:"), QLineEdit::Normal, "", &confirm);

    if(confirm && !(text.isEmpty())){
        fs->agregarArchivo(actualFolder, text, 1);
        refresh();
    }
}

void MainWindow::on_btnCopy_clicked(){
    if(selected)
        clipboard = selected;
}

void MainWindow::on_btnPaste_clicked(){
    if(clipboard){
        Folder * origen = fs->getParent(clipboard);
        fs->copiar(origen, clipboard->getNombre(), actualFolder);
        refresh();
    }else{
        QMessageBox::information(this, tr("Copiar"), tr("¡No hay archivo copiado!"));
    }
}

void MainWindow::on_btnBack_clicked(){
    QString ruta = actualFolder->getRuta();

    if(ruta != "raiz"){
        Folder * temp = fs->getParent(actualFolder);
        actualFolder = temp;
        refresh();
    }
}

void MainWindow::on_actionCrear_Nuevo_Folder_triggered(){on_btnFolder_clicked();}

void MainWindow::on_actionCrear_Nuevo_Archivo_de_Texto_triggered(){on_btnArchivo_clicked();}

void MainWindow::on_actionEliminar_Archivo_triggered(){
    if(selected != NULL){
        fs->eliminarArchivo(selected->getRuta());
        if(clipboard == selected)
            clipboard = NULL;
        selected = NULL;
        refresh();
    }
}

void MainWindow::on_actionRenombrar_Archivo_triggered(){
    if(selected != NULL){
        bool confirm = false;
        QString text = QInputDialog::getText(this, tr("Renombrar Archivo"), tr("Nuevo Nombre:"), QLineEdit::Normal,
                                             selected->getNombre(), &confirm);
        if(confirm && !(text.isEmpty())){
            selected->setNombre(text);
            selected->setRuta(actualFolder->getRuta()+"/"+selected->getNombre());
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    QPoint click = event->pos();
    click.setX(click.x()-140);
    click.setY(click.y()-98);

    QGraphicsItem * item = ui->graphicsView->itemAt(click);

    if(item){
        Files * file = (Files*)item;
        selected = file->archivo;
        refresh();
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event){
    bool confirm = false;

    QPoint click = event->pos();
    click.setX(click.x()-140);
    click.setY(click.y()-98);

    QGraphicsItem * item = ui->graphicsView->itemAt(click);

    if(item != NULL){
        Files * file = (Files*)item;

        if(file->archivo->getTipo() == "Folder"){
            actualFolder = (Folder*)file->archivo;
            selected = NULL;
            refresh();
        }else{
            ArchivoTexto * archText = (ArchivoTexto*)(file->archivo);
            Input * inp = new Input(this, archText);
            inp->exec();
            delete inp;
        }
    }
}
