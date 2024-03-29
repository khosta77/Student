#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QListWidget"
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

private:
    bool firstClick;
    int sizeName;
    QString BackUpName;
    void clear();
    void VeiwWidjetUpdate();
    bool LineEditControl();
    StudentList student;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
