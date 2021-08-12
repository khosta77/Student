#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QListWidget"
#include "QString"
#include "QFile"
#include "studentlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

    void on_lwName_itemClicked();

    void on_btnEdit_clicked();

    void on_btnRemoveAll_clicked();

    void on_acOpen_triggered();

    void on_acSave_triggered();

    void on_asSaveHow_triggered();

private:
    bool firstClick;
    bool fileFirstClick;
    int sizeName;
    QString BackUpName;
    QString FileName;
    QFile File;
    void clear();
    void VeiwWidjetUpdate();
    bool LineEditControl();
    StudentList student;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
