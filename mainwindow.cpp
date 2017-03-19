#include "mainwindow.h"
#include "ui_mainwindow.h"

extern FileSystem * fs;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    selected = NULL;
    clipboard = NULL;
    current = 0;
    paths.push_back("raiz");

    scene = new QGraphicsScene(parent);
    ui->graphicsView->setScene(scene);

    fs = new FileSystem();

    actualFolder = fs->raiz;
    ui->label->setText(actualFolder->getRuta());
    ui->cant->setText("Cantidad: " + QString::number(actualFolder->getCantidadArchivos()));

    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("");
    ui->treeWidget->header()->setFixedHeight(0);
    treeItem = new QTreeWidgetItem(QStringList() << "raiz");
    icon = new QIcon("C:\\Users\\Leovavi\\Documents\\UNITEC\\Recursos\\File Explorer\\folder.png");
    treeItem->setIcon(0, *icon);
    treeItem->setSelected(true);
    ui->treeWidget->addTopLevelItem(treeItem);
}

MainWindow::~MainWindow(){
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

void MainWindow::deleteFromTree(){
    for(int i = 0; i<treeItem->childCount(); i++){
        QTreeWidgetItem * temp = treeItem->child(i);
        if(temp->text(0) == selected->getNombre()){
            treeItem->removeChild(temp);
            return;
        }
    }
}

void MainWindow::refreshTree(QString ruta){
//    treeItem->setSelected(false);
//    treeItem = getHijo(nombre);
//    treeItem->setSelected(true);

//    if(treeItem != ui->treeWidget->topLevelItem(0))
//        treeItem->parent()->setExpanded(true);

//    ui->treeWidget->resizeColumnToContents(0);
    QStringList lista = ruta.split('/');
    treeItem->setSelected(false);
    treeItem = ui->treeWidget->topLevelItem(0);
    for(int i = 1; i<lista.size(); i++){
        QTreeWidgetItem * temp = getHijo(lista.at(i));
        if(temp != NULL)
            treeItem = temp;
    }
    treeItem->setSelected(true);
}


QTreeWidgetItem *MainWindow::getHijo(QString nombre){
    for(int i = 0; i<treeItem->childCount(); i++){
        QTreeWidgetItem * temp = treeItem->child(i);
        if(temp->text(0) == nombre)
            return temp;
    }
    return NULL;
}

void MainWindow::addPath(){
    if(current < paths.size()-1 && paths.at(current+1) != actualFolder->getRuta()){
        for(int i = current; i<paths.size(); i++)
            paths.pop_back();
    }

    paths.push_back(actualFolder->getRuta());
    current++;
}

QString MainWindow::getPath(QTreeWidgetItem * item){
    if(item->text(0) != "raiz")
        return getPath(item->parent())+"/"+item->text(0);
    return "raiz";
}

void MainWindow::on_btnFolder_clicked(){
    bool confirm = false;

    QString text = QInputDialog::getText(this, tr("Nuevo Folder"), tr("Nombre:"), QLineEdit::Normal, "", &confirm);

    if(confirm && !(text.isEmpty())){
        selected = fs->agregarArchivo(actualFolder, text, 2);
        QTreeWidgetItem * newItem = new QTreeWidgetItem(QStringList() << selected->getNombre());
        newItem->setIcon(0, *icon);
        treeItem->addChild(newItem);
        ui->treeWidget->resizeColumnToContents(0);
        refresh();
    }

}

void MainWindow::on_btnArchivo_clicked(){
    bool confirm = false;

    QString text = QInputDialog::getText(this, tr("Nuevo Archivo de Texto"), tr("Nombre:"), QLineEdit::Normal, "", &confirm);

    if(confirm && !(text.isEmpty())){
        selected = fs->agregarArchivo(actualFolder, text, 1);
        refresh();
    }
}

void MainWindow::on_btnCopy_clicked(){
    if(selected){
        clipboard = selected;
        if(selected->getTipo() == "Folder")
            copyTreeItem = getHijo(selected->getNombre())->clone();
        else
            copyTreeItem = NULL;
    }
}

void MainWindow::on_btnPaste_clicked(){
    if(clipboard){
        Folder * origen = fs->getParent(clipboard);
        fs->copiar(origen, clipboard->getNombre(), actualFolder);
        if(copyTreeItem){
            treeItem->addChild(copyTreeItem);
        }
        refresh();
    }else{
        QMessageBox::information(this, tr("Copiar"), tr("¡No hay archivo copiado!"));
    }
}

void MainWindow::on_actionEliminar_Archivo_triggered(){
    if(selected != NULL){
        QMessageBox::StandardButton resp;
        resp = QMessageBox::question(this, tr("Eliminar Archivo"), tr("¿Desea eliminar?"),
                                     QMessageBox::Yes | QMessageBox::No);
        if(resp == QMessageBox::Yes){
            fs->eliminarArchivo(selected->getRuta());
            if(clipboard == selected)
                clipboard = NULL;
            deleteFromTree();
            selected = NULL;
            refresh();
        }
    }else
        QMessageBox::information(this, tr("Eliminar Archivo"), tr("No hay archivo seleccionado para eliminar"));
}

void MainWindow::renombrarArchivos(Folder *f){
    for(int i = 0; i<f->getCantidadArchivos(); i++){
        Archivo * temp = f->obtenerArchivo(i);
        QString ruta = f->getRuta()+"/"+temp->getNombre();
        temp->setRuta(ruta);

        if(temp->getTipo() == "Folder")
            renombrarArchivos((Folder*)temp);
    }
}

void MainWindow::on_actionRenombrar_Archivo_triggered(){
    if(selected != NULL){
        bool confirm = false;
        QString text = QInputDialog::getText(this, tr("Renombrar Archivo"), tr("Nuevo Nombre:"), QLineEdit::Normal,
                                             selected->getNombre(), &confirm);
        if(confirm && !(text.isEmpty())){
            QTreeWidgetItem * temp = getHijo(selected->getNombre());
            selected->setNombre(text);
            selected->setRuta(actualFolder->getRuta()+"/"+selected->getNombre());
            if(selected->getTipo() == "Folder"){
                renombrarArchivos((Folder*)selected);
                temp->setText(0, text);
            }
        }
    }
}

void MainWindow::on_btnBack_clicked(){
    QString ruta = actualFolder->getRuta();

    if(ruta != "raiz"){
        current--;
        actualFolder = (Folder*)(fs->cargarArchivo(paths.at(current)));
        treeItem->setSelected(false);
        treeItem = treeItem->parent();
        treeItem->setSelected(true);
        refresh();
    }
}

void MainWindow::on_btnFront_clicked(){
    if(current+1 <paths.size()){
        current++;
        actualFolder = (Folder*)(fs->cargarArchivo(paths.at(current)));
        refreshTree(actualFolder->getRuta());
        refresh();
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
    QPoint click = event->pos();
    click.setX(click.x()-140);
    click.setY(click.y()-98);

    QGraphicsItem * item = ui->graphicsView->itemAt(click);

    if(item != NULL){
        Files * file = (Files*)item;

        if(file->archivo->getTipo() == "Folder"){
            actualFolder = (Folder*)file->archivo;
            addPath();
            refreshTree(selected->getRuta());
            refresh();
            selected = NULL;
        }else{
            ArchivoTexto * archText = (ArchivoTexto*)(file->archivo);
            Input * inp = new Input(this, archText);
            inp->exec();
            delete inp;
        }
    }
}

void MainWindow::on_treeWidget_clicked(const QModelIndex &index){
    qDebug() << ui->treeWidget->currentItem()->text(0);
    if(ui->treeWidget->currentItem() != treeItem){
        treeItem = ui->treeWidget->currentItem();
        QString path = getPath(treeItem);
        actualFolder = (Folder*)(fs->cargarArchivo(path));
        if(paths.at(current) != actualFolder->getRuta()){
            addPath();
            refresh();
        }
    }
}

void MainWindow::on_actionCopiar_triggered(){on_btnCopy_clicked();}
void MainWindow::on_actionPegar_triggered(){on_btnPaste_clicked();}
void MainWindow::on_actionSalir_triggered(){MainWindow::close();}
void MainWindow::on_actionCrear_Nuevo_Folder_triggered(){on_btnFolder_clicked();}
void MainWindow::on_actionCrear_Nuevo_Archivo_de_Texto_triggered(){on_btnArchivo_clicked();}
