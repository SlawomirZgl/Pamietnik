#include "pamietnik.h"
#include "ui_pamietnik.h"
#include "ui_edytorwpisow.h"
#include <QObject>
#include <QDebug>
#include <QTimer>

Pamietnik::Pamietnik(QWidget *parent, Program *app) :
    QDialog(parent),
    ui(new Ui::Pamietnik),
    mainApp(app)
{
    app->setGUI(this);
    ui->setupUi(this);

    connect(app,SIGNAL(wyswietlTekst(QString,QString,QColor,QFont,QString)),
            this, SLOT(onWyswietlTekst(QString,QString,QColor,QFont,QString)));
    connect(app,SIGNAL(wyswietlPozn(QString)),
            this, SLOT(onWyswietlPozn(QString)));
    connect(app,SIGNAL(wyswietlWczes(QString)),
            this, SLOT(onWyswietlWczes(QString)));
    connect(app, SIGNAL(rozwinW(QString,QString,QColor,QFont)),
            this, SLOT(onRozwinW(QString,QString,QColor,QFont)));
    connect(app, SIGNAL(rozwinP(QString,QString,QColor,QFont)),
            this, SLOT(onRozwinP(QString,QString,QColor,QFont)));

    ui->textWczesniejszy->setReadOnly(true);
    ui->textAktualny->setReadOnly(true);
    ui->textPozniejszy->setReadOnly(true);
    ui->textPozniejszy->setMouseTracking(true);
    ui->textWczesniejszy->setMouseTracking(true);
    this->setMouseTracking(true);

}

Pamietnik::~Pamietnik()
{
    delete ui;
}

void Pamietnik::on_przycikDodajWpis_clicked()
{
    mainApp->dodajWpis();
    aktywujEdycje();
}

void Pamietnik::onWyswietlTekst(QString tekst,QString data,QColor kolor,QFont czcionka,QString obraz){
    ui->textAktualny->clear();
    ui->textAktualny->setFontWeight(QFont::Bold);
    ui->textAktualny->append(data);
    ui->textAktualny->setFontWeight(QFont::Normal);
    ui->textAktualny->setFontWeight(czcionka.weight());
    ui->textAktualny->setFontItalic(czcionka.italic());
    ui->textAktualny->setTextColor(kolor);
    ui->textAktualny->append(tekst);
    ui->textAktualny->setFontWeight(QFont::Normal);
    ui->textAktualny->setTextColor(QColor(0,0,0));
    ui->textAktualny->setFontItalic(false);
    QPixmap pm = obraz;
    ui->label->setPixmap(pm);
    ui->label->setScaledContents(1);
}

void Pamietnik::onWyswietlPozn(QString tekst){
    ui->textPozniejszy->setText(tekst);
}

void Pamietnik::onWyswietlWczes(QString tekst){
    ui->textWczesniejszy->setText(tekst);
}

void Pamietnik::on_przycikEdytujWpis_clicked(){
   mainApp->edytuj();
}

void Pamietnik::aktywujEdycje(){
    ui->przycikEdytujWpis->setEnabled(mainApp->aktywujEdycja());
}

void Pamietnik::on_zapis_clicked(){
    QString plik = QFileDialog::getSaveFileName(this,"Zapisz plik","","Text file (*.txt)");
    mainApp->zapiszDoPliku(plik);
}

void Pamietnik::on_wczytaj_clicked(){
     QString plik = QFileDialog::getOpenFileName(this,"Wybierz plik","","Text file (*.txt)");
     mainApp->odczytajZPliku(plik);
     aktywujEdycje();
}

void Pamietnik::on_buttonUp_clicked(){
    mainApp->dekrementuj();
}

void Pamietnik::on_buttonDown_clicked(){ 
    mainApp->inkrementuj();

}

void Pamietnik::keyPressEvent(QKeyEvent * event){
    int keyCode = event->key();
    switch (keyCode) {
    case Qt::Key_Up:
        on_buttonUp_clicked();break;
    case Qt::Key_Down:
        on_buttonDown_clicked();break;
    case Qt::Key_W:
        on_buttonUp_clicked();break;
    case Qt::Key_S:
        on_buttonDown_clicked();break;
    case Qt::Key_8:
        on_buttonUp_clicked();break;
    case Qt::Key_2:
        on_buttonDown_clicked();break;
    }
}

void Pamietnik::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().y() < 0){
        on_buttonDown_clicked();
    }
    else{
        on_buttonUp_clicked();
    }
}

void Pamietnik::mousePressEvent(QMouseEvent * e){
    int xP = ui->textPozniejszy->geometry().x();
    int yP = ui->textPozniejszy->geometry().y();
    int xW = ui->textWczesniejszy->geometry().x();
    int yW = ui->textWczesniejszy->geometry().y();

    if(xP < e->localPos().x() && e->localPos().x() < xP + ui->textPozniejszy->width()
            && yP < e->localPos().y() && e->localPos().y() < yP + ui->textPozniejszy->height()){
            on_buttonDown_clicked();
    }
    else if(xW < e->localPos().x() && e->localPos().x() < xW + ui->textWczesniejszy->width()
            && yW < e->localPos().y() && e->localPos().y() < yW + ui->textWczesniejszy->height()){
            on_buttonUp_clicked();
    }
}




//ROZWIJANIE PRZY NAJECHANIU KURSOREM

void Pamietnik::mouseMoveEvent(QMouseEvent * e){
    int xP = ui->textPozniejszy->geometry().x();
    int yP = ui->textPozniejszy->geometry().y();
    int xW = ui->textWczesniejszy->geometry().x();
    int yW = ui->textWczesniejszy->geometry().y();

    if((xP < e->localPos().x() && e->localPos().x() < (xP + ui->textPozniejszy->width()))
            && (yP < e->localPos().y() && e->localPos().y() < (yP + ui->textPozniejszy->height()))){
            QTimer::singleShot(3000,this,SLOT(reactP()));
    }
    else{
        mainApp->wyswietl();
    }
    if((xW < e->localPos().x() && e->localPos().x() < (xW + ui->textWczesniejszy->width()))
            && (yW < e->localPos().y() && e->localPos().y() < (yW + ui->textWczesniejszy->height()))){
            QTimer::singleShot(3000,this,SLOT(reactW()));
    }
    else{
        mainApp->wyswietl();
    }
}

void Pamietnik::reactP(){
    mainApp->rozwinPozniejszy();
}

void Pamietnik::onRozwinP(QString tekst,QString data,QColor kolor,QFont czcionka){
    ui->textPozniejszy->clear();
    ui->textPozniejszy->setFontWeight(QFont::Bold);
    ui->textPozniejszy->append(data);
    ui->textPozniejszy->setFontWeight(QFont::Normal);
    ui->textPozniejszy->setFontWeight(czcionka.weight());
    ui->textPozniejszy->setFontItalic(czcionka.italic());
    ui->textPozniejszy->setTextColor(kolor);
    ui->textPozniejszy->append(tekst);
    ui->textPozniejszy->setFontWeight(QFont::Normal);
    ui->textPozniejszy->setTextColor(QColor(0,0,0));
    ui->textPozniejszy->setFontItalic(false);
}

void Pamietnik::reactW(){
     mainApp->rozwinWczesniejszy();
}

void Pamietnik::onRozwinW(QString tekst,QString data="",QColor kolor=QColor(0,0,0),QFont czcionka=QFont()){
    ui->textWczesniejszy->clear();
    ui->textWczesniejszy->setFontWeight(QFont::Bold);
    ui->textWczesniejszy->append(data);
    ui->textWczesniejszy->setFontWeight(QFont::Normal);
    ui->textWczesniejszy->setFontWeight(czcionka.weight());
    ui->textWczesniejszy->setFontItalic(czcionka.italic());
    ui->textWczesniejszy->setTextColor(kolor);
    ui->textWczesniejszy->append(tekst);
    ui->textWczesniejszy->setFontWeight(QFont::Normal);
    ui->textWczesniejszy->setTextColor(QColor(0,0,0));
    ui->textWczesniejszy->setFontItalic(false);
}
