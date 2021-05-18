#ifndef PROGRAM_H
#define PROGRAM_H
#include <QObject>
#include "edytorwpisow.h"
#include "pamietnik.h"
#include "wpispamietnika.h"

class Pamietnik;

class Program : public QObject
{
    Q_OBJECT
public:
    explicit Program(QObject *parent = nullptr);
    void setGUI(Pamietnik *ui = nullptr) {GUI = ui;}
    void dodajWpis();
    void inkrementuj();
    void dekrementuj();
    void zapiszDoPliku(QString);
    void odczytajZPliku(QString);
    void wyswietl();
    void edytuj();
    bool aktywujEdycja();
    void rozwinPozniejszy();
    void rozwinWczesniejszy();

signals:
    void wyswietlTekst(QString,QString,QColor,QFont,QString);
    void wyswietlPozn(QString);
    void wyswietlWczes(QString);
    void edytowanie(QString, QDateTime, QColor, QFont, QString);
    void rozwinP(QString,QString,QColor,QFont);
    void rozwinW(QString,QString,QColor,QFont);

private slots:
     void onDodanie(QString, QDateTime, QColor, QFont, QString);
     void onEdycja(QString, QDateTime, QColor, QFont, QString);

private:
    Pamietnik *GUI= nullptr;

};

#endif // PROGRAM_H
