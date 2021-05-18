#ifndef PAMIETNIK_H
#define PAMIETNIK_H

#include <QDialog>
#include <QTextEdit>
#include <QString>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <fstream>
#include "program.h"

using namespace std;

class Program;

namespace Ui {
class Pamietnik;
}

class Pamietnik : public QDialog
{
    Q_OBJECT

public:
    explicit Pamietnik(QWidget *parent = nullptr, Program *app = nullptr);
    ~Pamietnik();

private slots:
    void on_przycikDodajWpis_clicked();   
    void on_buttonUp_clicked();  
    void on_buttonDown_clicked();
    void on_przycikEdytujWpis_clicked();
    void onWyswietlTekst(QString,QString,QColor,QFont,QString);
    void onWyswietlWczes(QString);
    void onWyswietlPozn(QString);
    void on_zapis_clicked();
    void on_wczytaj_clicked();
    void reactP();
    void reactW();
    void onRozwinP(QString,QString,QColor,QFont);
    void onRozwinW(QString,QString,QColor,QFont);

private:
    Ui::Pamietnik *ui = nullptr;
    Program *mainApp = nullptr;

    void keyPressEvent(QKeyEvent * event) override;
    void wheelEvent(QWheelEvent *event) override;    
    void mousePressEvent(QMouseEvent* e) override;
    void aktywujEdycje();
    void mouseMoveEvent(QMouseEvent* e) override;
};

#endif // PAMIETNIK_H
