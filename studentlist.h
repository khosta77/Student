#ifndef STUDENTLIST_H
#define STUDENTLIST_H
#include "QString"

struct StudentLink{
    QString name;
    QString math;
    QString physics;
    QString russian;
    StudentLink* next;
};

class StudentList{
private:
    StudentLink* first;
    void removeLastStudent();
public:
    StudentList();
    void addStudent(QString name, QString math, QString physics, QString russian);
    void removeStudent(QString name);
    void nameSort();
    bool controlEmpty();
    QString getNameStudent(QString key);
    QString getMathStudent(QString key);
    QString getPhisicsStudent(QString key);
    QString getRussianStudent(QString key);
    QString getNameStudentForListWidjet(int i);
    void RemoveAllStudent();
    ~StudentList();
};

#endif // STUDENTLIST_H
