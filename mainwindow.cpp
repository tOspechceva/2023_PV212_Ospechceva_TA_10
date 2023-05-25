#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include <unordered_map>
#include<QMap>
#include<cmath>
#include<iostream>
class MathOperation {
public:
    enum class MathOperationTypes {
        Minus,
        Plus,
        Mul,
        Div,
        Sin,
        Cos,
        Tg,
        Ctg,
        Lg,
        Ln,
        PowNeg,
        Pow,
        Factorial,
        Root,
        Exp,
        Factr
    };

    MathOperation(){}
    explicit MathOperation(MathOperationTypes type, bool is_binary = false,
                           double (*function)(double, double) = nullptr) {
        _type = type;
        _is_binary = is_binary;
        _function = function;
    }

    [[nodiscard]] MathOperationTypes getType() const {
        return _type;
    }

    void setType(MathOperationTypes type) {
        _type = type;
    }

    [[nodiscard]] bool isBinary() const {
        return _is_binary;
    }


    double calculate(double a, double b = 0) {
        return _function(a, b);
    }

private:
    MathOperationTypes _type;
    bool _is_binary;
    double (*_function)(double, double);
};

double factorialZ(double x){
    long long x_int =x;
    long long f=1;
    for (int i=2;i<=x_int;i++) {
        f*=i;
    }

    return f;
}

double factorialR(double x){
    return pow(x / M_E, x) * sqrt(2.0 * M_PI * x) *
            (1.0 + 1.0 / (12.0 * x) + 1.0 / (288.0 * x * x));
}

double powNegative(double x){
    x=1.0/x;
    return x;
}
extern QMap<QString, MathOperation> _dictionary{
    {"×", MathOperation(MathOperation::MathOperationTypes::Mul, true,
                        [](const double a, const double b) { return a * b; })},
    {"÷", MathOperation(MathOperation::MathOperationTypes::Div, true,
                        [](const double a, const double b) { return a / b; })},
    {"+", MathOperation(MathOperation::MathOperationTypes::Plus, true,
                        [](const double a, const double b) { return a + b; })},
    {"-", MathOperation(MathOperation::MathOperationTypes::Minus, true,
                        [](const double a, const double b) { return a - b; })},
    {"sin", MathOperation(MathOperation::MathOperationTypes::Sin, false,
                          [](const double a, const double b) { return sin(a); })},
    {"cos", MathOperation(MathOperation::MathOperationTypes::Cos, false,
                          [](const double a, const double b) { return cos(a); })},
    {"tg", MathOperation(MathOperation::MathOperationTypes::Tg, false,
                         [](const double a, const double b) { return tan(a); })},
    {"ctg", MathOperation(MathOperation::MathOperationTypes::Ctg, false,
                          [](const double a, const double b) { return cos(a)/sin(a); })},
    {"ln", MathOperation(MathOperation::MathOperationTypes::Ln, false,
                         [](const double a, const double b) { return log(a); })},
    {"lg", MathOperation(MathOperation::MathOperationTypes::Lg, false,
                         [](const double a, const double b) { return log10(a); })},

    {"X^y", MathOperation(MathOperation::MathOperationTypes::Pow, true,
                          [](const double a, const double b) { return pow(a,b); })},

    {"√X", MathOperation(MathOperation::MathOperationTypes::Root, false,
                         [](const double a, const double b) { return sqrt(a); })},
    {"e", MathOperation(MathOperation::MathOperationTypes::Exp, false,
                        [](const double a, const double b) { return exp(a); })},
    {"X!", MathOperation(MathOperation::MathOperationTypes::Factr, false,
                         [](const double a, const double b) { return fabs(b-1)<0.01? factorialR(a):factorialZ(a); })},
    {"1/X", MathOperation(MathOperation::MathOperationTypes::Root, false,
                          [](const double a, const double b) { return 1.0/a; })},
};

bool error =false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_1, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_signCh, SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_procents, SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_div, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_mul, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_minas, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_pow, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_root, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_sin, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_cos, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_tg, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_ctg, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_ln, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_lg, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_negPow, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_e, SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_factr, SIGNAL(clicked()),this,SLOT(math_operations()));
}

MainWindow::~MainWindow()
{
    on_pushButton_ac_clicked();
    delete ui;
}

void accessButton(QString style, bool access, QPushButton *b){
    b->setEnabled(access);
    b->setStyleSheet(style);
}
bool is_seconOperand = false;

void MainWindow::error_input_unblock(){
    QString operationStyle="QPushButton{background-color: rgb(255, 151, 57);color: white; border: 1px solid gray;} QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FF7832, stop: 1 #FF9739);}";

    accessButton(operationStyle,true,ui->pushButton_del);
    accessButton(operationStyle,true,ui->pushButton_procents);
    accessButton(operationStyle,true,ui->pushButton_signCh);
    accessButton(operationStyle,true,ui->pushButton_coma);

    QString mathOperationStyle="QPushButton {background-color: rgb(215, 215, 215);border: 1px solid gray;color:black;}QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #BEBEBE, stop: 1 #D7D7D7);}";

    accessButton(mathOperationStyle,true,ui->pushButton_sin);
    accessButton(mathOperationStyle,true,ui->pushButton_cos);
    accessButton(mathOperationStyle,true,ui->pushButton_tg);
    accessButton(mathOperationStyle,true,ui->pushButton_ctg);
    accessButton(mathOperationStyle,true,ui->pushButton_pow);
    accessButton(mathOperationStyle,true,ui->pushButton_lg);
    accessButton(mathOperationStyle,true,ui->pushButton_ln);
    accessButton(mathOperationStyle,true,ui->pushButton_div);
    accessButton(mathOperationStyle,true,ui->pushButton_mul);
    accessButton(mathOperationStyle,true,ui->pushButton_minas);
    accessButton(mathOperationStyle,true,ui->pushButton_plus);
    accessButton(mathOperationStyle,true,ui->pushButton_equality);
    accessButton(mathOperationStyle,true,ui->pushButton_e);
    accessButton(mathOperationStyle,true,ui->pushButton_root);
    accessButton(mathOperationStyle,true,ui->pushButton_negPow);

    error=false;
}
void MainWindow::digit_numbers(){
    QPushButton *button = static_cast<QPushButton*>(sender());
    double all_numbers;
    if(error){
        on_pushButton_ac_clicked();
        all_numbers = (button->text()).toDouble();
        error_input_unblock();
    }
    if(!is_seconOperand)
        all_numbers = (ui->result_show->text()+button->text()).toDouble();
    else {
        all_numbers = (button->text()).toDouble();
        is_seconOperand=false;
    }
    QString new_label=QString::number(all_numbers,'g',10);
    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_coma_clicked()
{
    if(!ui->result_show->text().contains('.')){
        ui->result_show->setText(ui->result_show->text()+'.');
    }
}

void MainWindow::operations(){
    QPushButton *button = static_cast<QPushButton*>(sender());
    double all_numbers;
    QString new_label;

    if(button->text()=="+/-"){
        all_numbers = (ui->result_show->text().toDouble());
        all_numbers*=-1;
        new_label=QString::number(all_numbers,'g',10);

        ui->result_show->setText(new_label);
    }else if (button->text()=="%") {
        all_numbers = (ui->result_show->text().toDouble());
        all_numbers*=0.01;
        new_label=QString::number(all_numbers,'g',10);

        ui->result_show->setText(new_label);
    }
}

double num_first = 0;
MathOperation math_operation;
bool isBinOpLastClick = false;
void MainWindow::math_operations(){
    QPushButton *button = static_cast<QPushButton*>(sender());
    on_pushButton_equality_clicked();
    math_operation =_dictionary.value(button->text());
    if(math_operation.isBinary()){
        isBinOpLastClick = true;
        is_seconOperand=true;
        num_first = (ui->result_show->text().toDouble());
        // ui->result_show->setText("0");
    }else{
        isBinOpLastClick =false;
        double all_numbers=(ui->result_show->text()).toDouble();
        all_numbers = math_operation.calculate(all_numbers,ui->result_show->text().contains('.'));
        if(!_isnan(all_numbers)){
            QString new_label = QString::number(all_numbers,'g',10);
            ui->result_show->setText(new_label);
        }else {
            error_input_block();
            ui->result_show->setText("Неверный ввод");
        }

    }
}

void MainWindow::error_input_block(){
    QString blockStyle="border-color:gray;";
    accessButton(blockStyle,false,ui->pushButton_del);
    accessButton(blockStyle,false,ui->pushButton_procents);
    accessButton(blockStyle,false,ui->pushButton_signCh);
    accessButton(blockStyle,false,ui->pushButton_coma);
    accessButton(blockStyle,false,ui->pushButton_sin);
    accessButton(blockStyle,false,ui->pushButton_cos);
    accessButton(blockStyle,false,ui->pushButton_tg);
    accessButton(blockStyle,false,ui->pushButton_ctg);
    accessButton(blockStyle,false,ui->pushButton_pow);
    accessButton(blockStyle,false,ui->pushButton_lg);
    accessButton(blockStyle,false,ui->pushButton_ln);
    accessButton(blockStyle,false,ui->pushButton_div);
    accessButton(blockStyle,false,ui->pushButton_mul);
    accessButton(blockStyle,false,ui->pushButton_minas);
    accessButton(blockStyle,false,ui->pushButton_plus);
    accessButton(blockStyle,false,ui->pushButton_equality);
    accessButton(blockStyle,false,ui->pushButton_e);
    accessButton(blockStyle,false,ui->pushButton_root);
    accessButton(blockStyle,false,ui->pushButton_negPow);
    error = true;
}

void MainWindow::on_pushButton_equality_clicked()
{
    double all_numbers=(ui->result_show->text()).toDouble();
    if(isBinOpLastClick==true){
        all_numbers = math_operation.calculate(num_first,all_numbers);
        isBinOpLastClick =false;
        is_seconOperand=false;
    }
    QString new_label = QString::number(all_numbers,'g',10);
    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_ac_clicked()
{
    num_first = 0;
    isBinOpLastClick = false;
    is_seconOperand = false;
    if(error)
        error_input_unblock();
    ui->result_show->setText("0");

}

void MainWindow::on_pushButton_del_clicked()
{
    auto text_res = ui->result_show->text();
    text_res.chop(1);
    if(text_res.length()==0){
        ui->result_show->setText("0");
    }else
        ui->result_show->setText(text_res);
}

void MainWindow::on_pushButton_pi_clicked()
{
    if(error){
        on_pushButton_ac_clicked();
        error_input_unblock();
    }

    if(is_seconOperand)
    {
        is_seconOperand=false;
    }

    QString pi = QString::number(M_PI,'g',10);
    ui->result_show->setText(pi);
}

void MainWindow::on_pushButton_0_clicked()
{
    double all_numbers;
    if(error){
        on_pushButton_ac_clicked();
        all_numbers = 0;
        error_input_unblock();
    }
    if(!is_seconOperand)
        all_numbers = (ui->result_show->text()+"0").toDouble();
    else {
        all_numbers = 0;
        is_seconOperand=false;
    }
    QString new_label=QString::number(all_numbers,'g',10);
    if(ui->result_show->text().contains('.')){
        new_label=ui->result_show->text()+"0";
    }
    ui->result_show->setText(new_label);
}

