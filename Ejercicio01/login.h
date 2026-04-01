#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login() override;

private slots:
    // Esta función es la que "escucha" el clic del botón
    void on_btnIngresar_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H