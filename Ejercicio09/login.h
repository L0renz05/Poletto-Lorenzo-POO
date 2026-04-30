#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "admindb.h"

namespace Ui {
class Login; // Asegurate que en el .ui el objectName sea Login con L mayúscula
}

class Login : public QWidget {
    Q_OBJECT

public:
    explicit Login(AdminDB *db, QWidget *parent = nullptr);
    ~Login();

private slots:
    void slot_validar();

private:
    Ui::Login *ui;
    AdminDB *baseDatos;
};

#endif // LOGIN_H