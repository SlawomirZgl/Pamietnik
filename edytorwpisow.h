#ifndef EDYTORWPISOW_H
#define EDYTORWPISOW_H

#include <QDialog>
#include <QDateTime>
#include <QColor>
#include <QFileDialog>
#include "program.h"

class Program;

namespace Ui {
class EdytorWpisow;
}

class EdytorWpisow : public QDialog
{
    Q_OBJECT

public:
    explicit EdytorWpisow(QWidget *parent = nullptr);
    ~EdytorWpisow();


signals:
    void dodanie(QString, QDateTime, QColor, QFont, QString);

private slots:
    void on_przyciskDodaj_clicked();

    void on_pushButton_clicked();

    void on_sliderR_valueChanged(int value);

    void on_sliderG_valueChanged(int value);

    void on_sliderB_valueChanged(int value);

    void on_spinBoxR_valueChanged(int arg1);

    void on_spinBoxG_valueChanged(int arg1);

    void on_spinBoxB_valueChanged(int arg1);

    void on_buttonZdjecie_clicked();

    void on_Edytowanie(QString, QDateTime, QColor, QFont, QString);

private:
    Ui::EdytorWpisow *ui;
    QString filePath = "obraz_domyslny.png";
    QColor mieszanieKolorow();
    QFont czcionka();
    void podgladObrazu();
};

#endif // EDYTORWPISOW_H
