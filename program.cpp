#include "program.h"

Program::Program(QObject *parent) : QObject(parent)
{}

void Program::dodajWpis(){
    EdytorWpisow edytor;
    connect(&edytor,SIGNAL(dodanie(QString, QDateTime, QColor, QFont, QString)),
               this,SLOT(onDodanie(QString, QDateTime, QColor, QFont, QString)));
    edytor.show();
    edytor.exec();
    disconnect(&edytor,SIGNAL(dodanie(QString, QDateTime, QColor, QFont, QString)),
                  this,SLOT(onDodanie(QString, QDateTime, QColor, QFont, QString)));
}

void Program::onDodanie(QString tekst, QDateTime data, QColor kolor, QFont czcionka, QString obraz){
    WpisPamietnika wpis{tekst, data,kolor,czcionka,obraz};
    wpis.dodajDoListy();
    wyswietl();
}

void Program::inkrementuj(){
   WpisPamietnika::inkrementuj();
   wyswietl();
}

void Program::dekrementuj(){
   WpisPamietnika::dekrementuj();
   wyswietl();
}

void Program::wyswietl(){
    if(WpisPamietnika::getLista().size()!=0){
        WpisPamietnika akt = WpisPamietnika::getAktualnyWpis();
        emit wyswietlTekst(akt.getTekst(),akt.getData().toString("dd.MM.yyyy hh:mm"), akt.getKolor(), akt.getCzcionka(), akt.getObraz());
        emit wyswietlWczes(WpisPamietnika::skroconyWpisWczesniejszy());
        emit wyswietlPozn(WpisPamietnika::skroconyWpisPozniejszy());
    }
}

void Program::zapiszDoPliku(QString plik){
   WpisPamietnika::zapis(plik);
}

void Program::odczytajZPliku(QString plik){
    WpisPamietnika::odczyt(plik);
    wyswietl();
}

void Program::edytuj(){
    EdytorWpisow edytor;
    connect(this,SIGNAL(edytowanie(QString, QDateTime, QColor, QFont, QString)),
            &edytor,SLOT(on_Edytowanie(QString, QDateTime, QColor, QFont, QString)));
    connect(&edytor,SIGNAL(dodanie(QString, QDateTime, QColor, QFont, QString)),
               this,SLOT(onEdycja(QString, QDateTime, QColor, QFont, QString)));
    WpisPamietnika akt = WpisPamietnika::getAktualnyWpis();
    emit edytowanie(akt.getTekst(), akt.getData(), akt.getKolor(), akt.getCzcionka(), akt.getObraz());
    edytor.show();
    edytor.exec();
    disconnect(&edytor,SIGNAL(dodanie(QString, QDateTime, QColor, QFont, QString)),
                    this,SLOT(onEdycja(QString, QDateTime, QColor, QFont, QString)));
    disconnect(this,SIGNAL(edytowanie(QString, QDateTime, QColor, QFont, QString)),
              &edytor,SLOT(on_Edytowanie(QString, QDateTime, QColor, QFont, QString)));
}

void Program::onEdycja(QString tekst, QDateTime data, QColor kolor, QFont czcionka, QString obraz){
    WpisPamietnika wpis{tekst, data,kolor,czcionka,obraz};
    wpis.poEdycji();
    wyswietl();
}

bool Program::aktywujEdycja(){
    bool pustaLista = (WpisPamietnika::getLista().size()==0);
    return !pustaLista;
}

void Program::rozwinPozniejszy(){
    if(WpisPamietnika::getAktualnyIndeks()!= WpisPamietnika::getLista().size() -1 && WpisPamietnika::getLista().size() > 1){
        WpisPamietnika akt = WpisPamietnika::getLista()[WpisPamietnika::getAktualnyIndeks()+1];
       emit rozwinP(akt.getTekst(),akt.getData().toString("dd.MM.yyyy hh:mm"),akt.getKolor(),akt.getCzcionka());
    }
    else {
       wyswietl();
    }
}

void Program::rozwinWczesniejszy(){
    if(WpisPamietnika::getAktualnyIndeks() == 0){
        wyswietl();
    }
    else {
        WpisPamietnika akt = WpisPamietnika::getLista()[WpisPamietnika::getAktualnyIndeks()-1];
       emit rozwinW(akt.getTekst(),akt.getData().toString("dd.MM.yyyy hh:mm"),akt.getKolor(),akt.getCzcionka());
    }
}
