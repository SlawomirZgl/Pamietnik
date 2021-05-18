#include "wpispamietnika.h"

QList<WpisPamietnika> WpisPamietnika::listaWpisow;
int WpisPamietnika::aktualnyIndeks = 0;

WpisPamietnika::WpisPamietnika()
{}

WpisPamietnika::WpisPamietnika(QString s, QDateTime d, QColor k, QFont c, QString obr = "obraz_domyslny.png")
    :data(d),tekst(s), kolor(k), czcionka(c), obraz(obr)
{}

void WpisPamietnika::dodajDoListy(){
    QList<WpisPamietnika>::iterator it;
    for(it=listaWpisow.begin();it!=listaWpisow.end();it++){
        if((*it) == *this){
           listaWpisow.erase(it);
           break;
        }
    }
    listaWpisow.push_back(*this);
    std::sort(listaWpisow.begin(),listaWpisow.end());
    aktualnyIndeks = listaWpisow.indexOf(*this);
}

QString WpisPamietnika::skroconyWpisWczesniejszy(){
    if(aktualnyIndeks == 0)
        return "BRAK WCZESNIEJSZYCH WPISOW!";
    else
        return (listaWpisow[aktualnyIndeks-1].getData().toString("dd.MM.yyyy hh:mm") + "\n" +
                listaWpisow[aktualnyIndeks-1].getTekst().mid(0,5) + "...");
}
QString WpisPamietnika::skroconyWpisPozniejszy(){
    if(aktualnyIndeks == listaWpisow.size()-1)
        return "BRAK POZNIEJSZYCH WPISOW!";
    else
        return (listaWpisow[aktualnyIndeks+1].getData().toString("dd.MM.yyyy hh:mm") + "\n" +
                listaWpisow[aktualnyIndeks+1].getTekst().mid(0,5) + "...");
}

void WpisPamietnika::inkrementuj(){
    if(listaWpisow.size() == 1);
    else if(aktualnyIndeks < listaWpisow.size()-1)
        aktualnyIndeks++;
}

void WpisPamietnika::dekrementuj(){
    if(listaWpisow.size() < 2);
    else if(aktualnyIndeks != 0)
        aktualnyIndeks--;
}

void WpisPamietnika::zapis(QString plik){
    QList<WpisPamietnika>::iterator it;
    QFile f(plik);
    f.open(QIODevice::WriteOnly);
    QDataStream out(&f);
    for (it = listaWpisow.begin(); it != listaWpisow.end(); it++) {
        out<<(*it).getData();       //QDataTime
        out<<(*it).getTekst();      //QString
        out<<(*it).getKolor();      //QColor
        out<<(*it).getCzcionka();   //QFont
        out<<(*it).getObraz();      //QString
    }
    f.close();
}

void WpisPamietnika::odczyt(QString plik){
        QFile f(plik);
        f.open(QIODevice::ReadOnly);
        QDataStream in(&f);
        QDateTime data;
        QString tekst;
        QColor kolor;
        QFont czcionka;
        QString obraz;
        do{
            if(in.atEnd()) break;
            in>>data>>tekst>>kolor>>czcionka>>obraz;
            WpisPamietnika w{tekst,data,kolor,czcionka,obraz};
            w.dodajDoListy();
        } while(true);
        f.close();
}

void WpisPamietnika::poEdycji(){
    listaWpisow.removeAt(aktualnyIndeks);
    dodajDoListy();
}
