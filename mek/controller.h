#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>


class QSerialPort;
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

    void run();

private:
    QSerialPort *qport;
    bool g_bStart;

    void openPort(bool bOpen);
    bool DoPacket(unsigned char buf[], float* result1, float* result2, float* result3, float* result4);
    void UpdateChart(float arg0, float arg1, float arg2, float arg3);

public slots :
    void text_Sending();
    void text_Reading();
    void onTimeout();
signals:

};

#endif // CONTROLLER_H
