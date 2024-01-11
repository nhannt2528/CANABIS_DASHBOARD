#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);
    ~Home();

private slots:

    void on_onButton_clicked();


    void on_autoButton_clicked();

    void on_offButton_clicked();

    void on_homeButton_clicked();

    void on_settingButton_clicked();

private:
    Ui::Home *ui;
};
#endif // HOME_H
