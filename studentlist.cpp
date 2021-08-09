#include "studentlist.h"
#include <QCoreApplication>
#include <QDebug>



StudentList::StudentList(){
    first = NULL;
}

void StudentList::addStudent(QString name, QString math, QString physics, QString russian){
    StudentLink* newlink = new StudentLink;
    newlink->name = name;
    newlink->math = math;
    newlink->physics = physics;
    newlink->russian = russian;
    newlink->next = first;
    first = newlink;
}

void StudentList::removeStudent(QString name){
    bool controlPrevios =false;
    StudentLink* current = first;
    StudentLink* previous = first;
    while (current) {
        if(current->name == name){
            if(current == first){
                removeLastStudent();
                break;
            }
            previous->next = current->next;
            delete current;
            break;
        }
        else{
            if(controlPrevios){
                previous = previous->next;
            }
            controlPrevios = true;
            current = current->next;
        }
    }
}

void StudentList::nameSort(){
    StudentLink* t, *m, *a, *b;
    if(first == NULL)
        return;

    for(bool go = true; go; ){
        go = false;
        a  = t = first;
        b  = first->next;

        while(b != NULL){
            if(a->name > b->name){
                if(t == a)
                    first = b;
                else
                    t->next = b;

                a->next = b->next;
                b->next = a;

                m  = a, a = b, b = m;
                go = true;
            }
            t = a;
            a = a->next;
            b = b->next;
        }
    }
}

bool StudentList::controlEmpty(){
    if(first == NULL){
        qDebug() << "ce false";
        return false;
    }
    else {
        qDebug() << "ce true";
        return true;
    }
//    return (first == NULL) ? false : true;
}

QString StudentList::getNameStudent(QString key){
    StudentLink* current = first;
    while (current){
        if(current->name == key){
            return current->name;
        }
        current = current->next;
    }
    return "404";
}

QString StudentList::getMathStudent(QString key){
    StudentLink* current = first;
    while (current){
        if(current->name == key){
            return current->math;
        }
        current = current->next;
    }
    return "404";
}

QString StudentList::getPhisicsStudent(QString key){
    StudentLink* current = first;
    while (current){
        if(current->name == key){
            return current->physics;
        }
        current = current->next;
    }
    return "404";
}

QString StudentList::getRussianStudent(QString key){
    StudentLink* current = first;
    while (current){
        if(current->name == key){
            return current->russian;
        }
        current = current->next;
    }
    return "404";
}

QString StudentList::getNameStudentForListWidjet(int i){
    StudentLink* current = first;
    for(int j = 0; j < i; j++){
        current = current->next;
    }
    return current->name;
}

void StudentList::RemoveAllStudent(){
    while (first) {
        StudentLink* newhead = first->next;
        delete first;
        first = newhead;
    }
}

StudentList::~StudentList(){
    RemoveAllStudent();
}

void StudentList::removeLastStudent(){
    StudentLink* newhead = first->next;
    delete first;
    first = newhead;
}
