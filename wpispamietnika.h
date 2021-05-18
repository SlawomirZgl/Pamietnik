#ifndef WPISPAMIETNIKA_H
#define WPISPAMIETNIKA_H
#include <QString>
#include <QDate>
#include <QColor>
#include <QFont>
#include <QList>
#include <QFile>
#include <QDataStream>
#include <QDebug>

class WpisPamietnika
{
private:
    QDateTime data;
    QString tekst;
    QColor kolor;
    QFont czcionka;
    QString obraz;
    static QList<WpisPamietnika> listaWpisow;
    static int aktualnyIndeks;

public:
    WpisPamietnika();
    WpisPamietnika(QString, QDateTime, QColor, QFont, QString);
    void setData(QDateTime dt){data = dt;}
    void setTekst(QString s){tekst = s;}    
    void dodajDoListy();
    void poEdycji();
    QDateTime getData(){return data;}
    QString getTekst(){return tekst;}
    QColor getKolor(){return kolor;}
    QFont getCzcionka(){return czcionka;}
    QString getObraz(){return obraz;}
    static WpisPamietnika getAktualnyWpis(){return listaWpisow[aktualnyIndeks];}
    static QString skroconyWpisWczesniejszy();
    static QString skroconyWpisPozniejszy();
    static QList<WpisPamietnika> getLista(){return listaWpisow;};
    static int getAktualnyIndeks(){ return aktualnyIndeks;};
    static void inkrementuj();
    static void dekrementuj();
    static void zapis(QString);
    static void odczyt(QString);

    bool operator<(const WpisPamietnika com){
        return (this->data < com.data);
    }
    bool operator>(const WpisPamietnika com){
        return (this->data > com.data);
    }
    bool operator==(const WpisPamietnika com){
        return(this->data.toString("dd.MM.yyyy hh:mm") == com.data.toString("dd.MM.yyyy hh:mm"));
    }
};

#endif // WPISPAMIETNIKA_H
