#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "studentlist.h"
#include "QDebug"
#include "QDebugStateSaver"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow){
    firstClick = true;
    sizeName = 0;
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_btnAdd_clicked(){

    if(LineEditControl()){
        student.addStudent(ui->leName->text(), ui->leMath->text(), ui->lePhysics->text(), ui->leRussian->text());
        clear();
        ui->lwScore->clear();
        sizeName++;
        VeiwWidjetUpdate();
    }
}

void MainWindow::on_btnRemove_clicked(){
    if(student.controlEmpty()){
        student.removeStudent(ui->lwName->currentItem()->text());
        sizeName--;
        ui->lwScore->clear();
        VeiwWidjetUpdate();
    }
}

void MainWindow::clear(){
    ui->leName->clear();
    ui->leMath->clear();
    ui->lePhysics->clear();
    ui->leRussian->clear();
}

void MainWindow::VeiwWidjetUpdate(){
    ui->lwName->clear();
    student.nameSort();
    for (int i = 0; i < sizeName; i++) {
        ui->lwName->addItem(student.getNameStudentForListWidjet(i));
    }
}

bool MainWindow::LineEditControl(){
    return (ui->leName->text() == "") ? false : true;
}


void MainWindow::on_lwName_itemClicked(){
    if(student.controlEmpty()){
        ui->lwScore->clear();
        ui->lwScore->addItem("Матиматика:   " + student.getMathStudent(ui->lwName->currentItem()->text()));
        ui->lwScore->addItem("Физика:             " + student.getPhisicsStudent(ui->lwName->currentItem()->text()));
        ui->lwScore->addItem("Русский язык: " + student.getRussianStudent(ui->lwName->currentItem()->text()));
    }
}


void MainWindow::on_btnEdit_clicked(){
    if(student.controlEmpty()){
        if(firstClick){
            qDebug() << "e1";
            ui->lwScore->clear();
            ui->leName->setText(student.getNameStudent(ui->lwName->currentItem()->text()));
            ui->leMath->setText(student.getMathStudent(ui->lwName->currentItem()->text()));
            ui->lePhysics->setText(student.getPhisicsStudent(ui->lwName->currentItem()->text()));
            ui->leRussian->setText(student.getRussianStudent(ui->lwName->currentItem()->text()));
            ui->btnAdd->setDisabled(true);
            ui->btnRemove->setDisabled(true);
            ui->btnRemoveAll->setDisabled(true);
            ui->btnEdit->setText("Сохранить изменения");
            firstClick = false;
            BackUpName = student.getNameStudent(ui->lwName->currentItem()->text());
        }
        else{
            qDebug() << "e2";
            ui->lwScore->clear();
            student.removeStudent(BackUpName);
            student.addStudent(ui->leName->text(), ui->leMath->text(), ui->lePhysics->text(), ui->leRussian->text());
            clear();
            VeiwWidjetUpdate();
            ui->btnAdd->setDisabled(false);
            ui->btnRemove->setDisabled(false);
            ui->btnRemoveAll->setDisabled(false);
            ui->btnEdit->setText("Изменить данные");
            firstClick = true;
            BackUpName = 0;
        }
    }
}

void MainWindow::on_btnRemoveAll_clicked(){
    if(student.controlEmpty()){
        ui->lwScore->clear();
        clear();
        student.RemoveAllStudent();
        sizeName = 0;
        VeiwWidjetUpdate();
    }
}

void MainWindow::on_acOpen_triggered(){
    FileName = QFileDialog::getOpenFileName( 0, "Выбор файла");
    File.setFileName(FileName);
    if (File.open(QIODevice::ReadOnly | QIODevice::Text)){
        on_btnRemoveAll_clicked();
        int const BUFFERSIZE = 5;
        QString bufferStudent[BUFFERSIZE];
        while (!File.atEnd()) {
            bufferStudent[0] = File.readLine();
            for(int i = 0, j = 1; i < bufferStudent[0].size() - 2; i++){
                    if(bufferStudent[0].at(i) != QChar('?')){
                        bufferStudent[j] += bufferStudent[0].at(i);
                    }
                    else {
                        j++;
                    }
            }
            if(!bufferStudent[1].isEmpty()){
                student.addStudent(bufferStudent[1], bufferStudent[2], bufferStudent[3], bufferStudent[4]);
                for (int i = 0; i < BUFFERSIZE; i++) {
                    bufferStudent[i] = 0;
                }
                sizeName++;
            }
        }
        VeiwWidjetUpdate();
        File.close();
    }
}


void MainWindow::on_acSave_triggered(){
    if(FileName.isEmpty()){
        FileName = QFileDialog::getSaveFileName( 0, "Выбор файла");
    }
    File.setFileName(FileName);
    if(File.open(QIODevice::Append | QIODevice::Truncate)){
        QTextStream out(&File);
        for(int i = 0; i < sizeName; i++){
            out
               << student.getNameStudent(student.getNameStudentForListWidjet(i)).toLocal8Bit()
               << "?"
               << student.getMathStudent(student.getNameStudentForListWidjet(i)).toLocal8Bit()
               << "?"
               << student.getPhisicsStudent(student.getNameStudentForListWidjet(i)).toLocal8Bit()
               << "?"
               << student.getRussianStudent(student.getNameStudentForListWidjet(i)).toLocal8Bit()
               << " \n";
        }
        File.close();
    }
}


void MainWindow::on_asSaveHow_triggered(){
    FileName = QFileDialog::getSaveFileName( 0, "Выбор файла");
    if(!FileName.isEmpty()){
        on_acSave_triggered();
    }
}



