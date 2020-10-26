#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    Ui::Widget *ui;
    QThread* thread ;
    void updateSensors();
    void sendToArduino(char dir);
    void threadFun();
    QSerialPort arduino;

protected:

};
#endif // WIDGET_H
