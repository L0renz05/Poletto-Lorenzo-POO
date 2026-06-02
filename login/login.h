#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class Login : public QWidget {
    Q_OBJECT
public:
    Login(QWidget *parent = nullptr);
private slots:
    void slot_validar();
private:
    QLineEdit *txtUser;
    QLineEdit *txtPass;
    QPushButton *btnEntrar;
};

#endif // LOGIN_H
