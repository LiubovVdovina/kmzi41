#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_enCesBut_clicked();

    void on_enVijBut_clicked();

    void on_deCesBut_clicked();

    void on_deVijBut_clicked();

    void ces_crypt(int index);

    void vij_crypt(int index);
    void on_pushButton_clicked();

    void on_Save_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
