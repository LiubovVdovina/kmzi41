#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QtGui>
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;
ifstream input, output, key;
string inputFile, outputFile, keyFile;
QString infile, outfile, kfile;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_enCesBut_clicked()
{
    int index = 1;
    ces_crypt(index);
}

void MainWindow::on_deCesBut_clicked()
{
    int index = 2;
    ces_crypt(index);
}

void MainWindow::on_enVijBut_clicked()
{
    int index = 1;
    vij_crypt(index);
}

void MainWindow::on_deVijBut_clicked()
{
    int index = 2;
    vij_crypt(index);
}

void MainWindow::ces_crypt(int index)
{
    ifstream input(inputFile.c_str());
    ofstream output(outputFile.c_str());
    QString strKey = ui->key->text();
    bool ok;
        int key = strKey.toInt(&ok);
        if (!ok)
        {
            QMessageBox::information(this,"Error!","Incorrect key. Enter a number and try again.");
            return;
        }
    if(!input.is_open())
    {
        QMessageBox::information(this,"Error!","Can't open input file!");
        return;
    }

    char ch;
    string result = "";
    while (!input.eof())
    {
        ch = input.get();
        if (ch != EOF)
        {
            if (index == 1)
            ch = (ch + key) % 256;
            if (index == 2)
            ch = (ch - key) % 256;
            result = result + ch;
        }
    }
    output << result;
    input.close();
    output.close();
    QMessageBox::information(this,"Succes!","File is crypted!");
}

void MainWindow::vij_crypt(int index)
{
    ifstream input(inputFile.c_str());
    ofstream output(outputFile.c_str());
    ifstream key(keyFile.c_str());
    if(!input.is_open())
    {
        QMessageBox::information(this,"Error!","Can't open input file!");
        return;
    }

    if(!key.is_open())
    {
        QMessageBox::information(this,"Error!","Can't open key file!");
        return;
    }
    char ch;
    string strKey = "";
   string::iterator i = strKey.begin();
    while (!key.eof())
    {
        ch = key.get();
        if (ch != EOF)
        {
           strKey = strKey + ch;
        }
    }

    string result = "";
    i = strKey.begin();
    while (!input.eof())
    {
        ch = input.get();
        if (ch != EOF)
        {
            if (index == 1)
                ch = (ch + *i) % 256;
            if (index == 2)
                ch = (ch - *i) % 256;
            result = result + ch;
            if (i + 1 == strKey.end())
                i = strKey.begin();
            else
                i++;
         }
    }
    output << result;
    input.close();
    output.close();
    key.close();
    QMessageBox::information(this,"Succes!","File is crypted!");

}

void MainWindow::on_pushButton_clicked()
{
    infile = QFileDialog::getOpenFileName(this,tr("Открыть файл"),"/Users/","Allfiles(*)");
    inputFile = infile.toStdString();
    ui->label->setText(infile);

}

void MainWindow::on_Save_clicked()
{
    outfile = QFileDialog::getSaveFileName(this,tr("Открыть файл"),"/Users/","Allfiles(*)");
    outputFile = outfile.toStdString();
    ui->label_2->setText(outfile);
}

void MainWindow::on_pushButton_2_clicked()
{
    kfile = QFileDialog::getOpenFileName(this,tr("Открыть файл"),"/Users/","Allfiles(*)");
    keyFile = kfile.toStdString();
    ui->label_3->setText(kfile);
}
