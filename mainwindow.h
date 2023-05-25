#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digit_numbers();
    void on_pushButton_coma_clicked();
    void operations();
    void math_operations();
    void on_pushButton_equality_clicked();
    void on_pushButton_ac_clicked();
    void error_input_block();
    void error_input_unblock();
    void on_pushButton_del_clicked();
    void on_pushButton_pi_clicked();
    void on_pushButton_0_clicked();

};

#endif // MAINWINDOW_H
