#include "edytorwpisow.h"
#include "ui_edytorwpisow.h"
#include <QDateTime>
#include <QDebug>
#include <QPixmap>

EdytorWpisow::EdytorWpisow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdytorWpisow)
{
    ui->setupUi(this);

    podgladObrazu();

    ui->dataGodzina->setDateTime(QDateTime::currentDateTime());
    ui->mieszalnik->setText("");
    mieszanieKolorow();

    ui->spinBoxR->setMaximum(255);
    ui->spinBoxG->setMaximum(255);
    ui->spinBoxB->setMaximum(255);

    ui->sliderR->setMaximum(255);
    ui->sliderG->setMaximum(255);
    ui->sliderB->setMaximum(255);

    ui->czcionka->addItem("Normalny");
    ui->czcionka->addItem("Kursywa");
    ui->czcionka->addItem("Pogrubiony");  
}

EdytorWpisow::~EdytorWpisow(){
    delete ui;
}

QFont EdytorWpisow::czcionka(){
    QFont font;
    if(ui->czcionka->currentText() == "Kursywa"){
      font.setItalic(true);
    }
    else if (ui->czcionka->currentText() == "Pogrubiony"){
        font.setBold(true);
    }
    return font;
}

void EdytorWpisow::on_Edytowanie(QString tekst, QDateTime data, QColor kolor, QFont czcionka, QString obraz){
    ui->wpis->setFontWeight(czcionka.weight());
    ui->wpis->setFontItalic(czcionka.italic());
    ui->wpis->setTextColor(kolor);
    ui->wpis->append(tekst);
    ui->wpis->setTextColor(QColor(0,0,0));
    ui->wpis->setFontItalic(false);
    filePath = obraz;
    QPixmap pm = obraz;
    ui->wczytanyobraz->setPixmap(pm);
    ui->wczytanyobraz->setScaledContents(1);
    ui->sliderR->setValue(kolor.red());
    ui->sliderG->setValue(kolor.green());
    ui->sliderB->setValue(kolor.blue());
    ui->dataGodzina->setDateTime(data);
}

void EdytorWpisow::on_przyciskDodaj_clicked(){
    emit dodanie((ui->wpis->toPlainText()),(ui->dataGodzina->dateTime()),mieszanieKolorow(),czcionka(), filePath);
    this->close();
}

void EdytorWpisow::on_pushButton_clicked(){
    this->close();
}

//MIESZALNIK KOLOROW
QColor EdytorWpisow::mieszanieKolorow(){
   QPixmap p(100,100);
   QColor kolor(ui->spinBoxR->value(),ui->spinBoxG->value(),ui->spinBoxB->value());
   p.fill(kolor);
   ui->mieszalnik->setPixmap(p);
   return kolor;
}


void EdytorWpisow::on_buttonZdjecie_clicked(){
    filePath = QFileDialog::getOpenFileName(this,"Wybierz zdjecie","C:/users/desktop","Graphics file (*.gif *.jpg *.jpeg *.png)");
    podgladObrazu();
}

void EdytorWpisow::podgladObrazu(){
    QPixmap pm(filePath);
    ui->wczytanyobraz->setPixmap(pm);
    ui->wczytanyobraz->setScaledContents(1);
}

void EdytorWpisow::on_sliderR_valueChanged(int value){
    ui->spinBoxR->setValue(value);
        mieszanieKolorow();
}

void EdytorWpisow::on_sliderG_valueChanged(int value){
    ui->spinBoxG->setValue(value);
       mieszanieKolorow();
}

void EdytorWpisow::on_sliderB_valueChanged(int value){
    ui->spinBoxB->setValue(value);
       mieszanieKolorow();
}

void EdytorWpisow::on_spinBoxR_valueChanged(int value){
    ui->sliderR->setValue(value);
       mieszanieKolorow();
}

void EdytorWpisow::on_spinBoxG_valueChanged(int value){
    ui->sliderG->setValue(value);
    mieszanieKolorow();
}

void EdytorWpisow::on_spinBoxB_valueChanged(int value){
    ui->sliderB->setValue(value);
       mieszanieKolorow();
}
