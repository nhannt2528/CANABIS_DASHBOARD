#include "home.h"
#include "./ui_home.h"

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
}

Home::~Home()
{
    delete ui;
}
void Home::on_onButton_clicked()
{
    ui->onButton->setStyleSheet("background-color: rgba(104, 11, 11, 177);");
    ui->autoButton->setStyleSheet("background-color: #1E1E1E;");
    ui->offButton->setStyleSheet("background-color: #1E1E1E;");

}
void Home::on_autoButton_clicked()
{
    ui->autoButton->setStyleSheet("background-color: rgba(104, 11, 11, 177);");
    ui->onButton->setStyleSheet("background-color: #1E1E1E;");
    ui->offButton->setStyleSheet("background-color: #1E1E1E;");
}
void Home::on_offButton_clicked()
{
    ui->offButton->setStyleSheet("background-color: rgba(104, 11, 11, 177);");
    ui->onButton->setStyleSheet("background-color: #1E1E1E;");
    ui->autoButton->setStyleSheet("background-color: #1E1E1E;");
}


void Home::on_homeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Home::on_settingButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);

}

