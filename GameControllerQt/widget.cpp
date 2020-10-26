#include "widget.h"
#include "ui_widget.h"
#include "SDL_joystick.h"
#include "SDL.h"
#include "QDebug"
#include "string"
#include "QThread"
#include "QSerialPort"
#include "QTimer"




Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);



    // this thread made to capture all events from the joytick in background
    Widget::thread = QThread::create([this]{threadFun();});

    thread->start();

    arduino.setPortName("COM4");
    arduino.open(QSerialPort::WriteOnly);
    arduino.setBaudRate(QSerialPort::Baud9600);
    arduino.setDataBits(QSerialPort::Data8);
    arduino.setParity(QSerialPort::NoParity);
    arduino.setStopBits(QSerialPort::OneStop);

    // this timer made to update the values of sensors every 5 sec
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Widget::updateSensors));
    timer->start(5000);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendToArduino(char dir){
    QString x = dir+ui->horizontal->text()+ui->vertical->text();
    if(arduino.isWritable())
        arduino.write(x.toStdString().c_str());
    else qDebug() << "Error while writing to the arduino";
}


void Widget::updateSensors(){
    ui->sensorslabel->setText(arduino.readAll());
}


void Widget::threadFun()
{

    SDL_Init(SDL_INIT_JOYSTICK);
    SDL_Joystick* gGameController;
    SDL_JoystickEventState(SDL_ENABLE);
    gGameController = SDL_JoystickOpen(0);
    SDL_Event e;

    qDebug() <<"Name: " << SDL_JoystickNameForIndex(0);
    qDebug() <<"Number of Axes: " << SDL_JoystickNumAxes(gGameController);
    qDebug() <<"Number of Buttons: " << SDL_JoystickNumButtons(gGameController);
    qDebug() <<"Number of Balls: " <<  SDL_JoystickNumBalls(gGameController);

    //Event handler

    while(true)
    {
        while (SDL_PollEvent(&e)){
            if(e.type == SDL_JOYBUTTONDOWN){
                qDebug() <<  "Button pressed index : " << e.jbutton.button ;
                if(e.jbutton.button == 4){
                    sendToArduino('U');
                } else if(e.jbutton.button == 5){
                    sendToArduino('R');
                }else if(e.jbutton.button == 6){
                    sendToArduino('D');
                }else if(e.jbutton.button == 7){
                    sendToArduino('L');
                }
            }
        }
    }
}



