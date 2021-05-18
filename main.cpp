#include "pamietnik.h"
#include "program.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Program mainProg;
    Pamietnik p(nullptr,&mainProg);
    p.show();
    return a.exec();
}
