#ifndef JOG_H
#define JOG_H

#include <QWidget>

namespace Ui {
class Jog;
}

class Jog : public QWidget
{
    Q_OBJECT

public:
    explicit Jog(QWidget *parent = nullptr);
    ~Jog();

private:
    Ui::Jog *ui;
};

#endif // JOG_H
