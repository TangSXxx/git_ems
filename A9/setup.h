#ifndef SETUP_H
#define SETUP_H

#include <QWidget>

namespace Ui {
class setup;
}

class setup : public QWidget
{
    Q_OBJECT

public:
    explicit setup(QWidget *parent = nullptr);
    ~setup();

private:
    Ui::setup *ui;
};

#endif // SETUP_H
