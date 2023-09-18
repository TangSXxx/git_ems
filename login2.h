#ifndef LOGIN2_H
#define LOGIN2_H
#include<login.h>
#include <QWidget>

namespace Ui {
class login2;
}

class login2 : public QWidget
{
    Q_OBJECT

public:
    explicit login2(QWidget *parent = nullptr);
    ~login2();

private slots:
    void on_pushButton_sure_clicked();

private:
    Ui::login2 *ui;
};

#endif // LOGIN2_H
