#include "controller.h"

#include <QtSerialPort/qserialport.h>
#include <QtSerialPort/qserialportinfo.h>

#include <QTimer>

#define PACKET_LENGTH 22
#define AXIS_Y_SIZE 200
#define AXIS_X_SIZE 400

int g_nIdxChart = 0;

int g_nIdxPckt = 0;
bool g_bPckt = false;
unsigned char g_bufPckt[PACKET_LENGTH];

QTimer *g_tmTimer;
int g_nIdxTimer = 0;

Controller::Controller(QObject *parent) : QObject(parent)
{

    g_bStart = false;

    qport = new QSerialPort;
    qport->setPortName("/dev/ttyUSB0");
    qport->setBaudRate(QSerialPort::Baud115200);
    qport->setDataBits(QSerialPort::Data8);
    qport->setParity(QSerialPort::NoParity);
    qport->setStopBits(QSerialPort::OneStop);
    qport->setFlowControl(QSerialPort::NoFlowControl);

    if (qport->open(QIODevice::ReadWrite))
        QObject::connect(qport, SIGNAL(readyRead()), this, SLOT(text_Reading()));

    g_tmTimer = new QTimer(this);
        connect(g_tmTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void Controller::run()
{

}

void Controller::UpdateChart(float arg0, float arg1, float arg2, float arg3)
{

    /*
    char result[7];
    char result2[7];
    char result3[7];
    char result4[7];

    int buf0,buf1,buf2,buf3;

    buf0=int(arg0);
    buf1=int(arg1);
    buf2=int(arg2);
    buf3=int(arg3);




    if(g_nIdxChart > AXIS_X_SIZE)
    {
        g_nIdxChart = 0;
        m_vx.clear();
        m_vy0.clear();
        m_vy1.clear();
        m_vy2.clear();
        m_vy3.clear();
    }

    m_vx.push_back(g_nIdxChart);
    m_vy0.push_back(buf0);
    m_vy1.push_back(buf1);
    m_vy2.push_back(buf2);
    m_vy3.push_back(buf3);


     sprintf(result,"%4.2f",arg0);
     sprintf(result2,"%4.2f",arg1);
     sprintf(result3,"%4.2f",arg2);
     sprintf(result4,"%4.2f",arg3);
     // 결과 textlabel에 값을 설정한다.

    ui->TextLabel->setText(result);
    ui->TextLabel_2->setText(result2);
    ui->TextLabel_3->setText(result3);
    ui->TextLabel_4->setText(result4);


    curve0->setRawSamples(m_vx.data(), m_vy0.data(), m_vx.count());
    curve0->setPen(* new QPen(Qt::red,2,Qt::SolidLine));
    curve0->attach(ui->qwtPlot0);
    ui->qwtPlot0->replot();
    ui->qwtPlot0->show();

    curve1->setRawSamples(m_vx.data(), m_vy1.data(), m_vx.count());
    curve1->setPen(* new QPen(Qt::green,2,Qt::SolidLine));
    curve1->attach(ui->qwtPlot1);
    ui->qwtPlot1->replot();
    ui->qwtPlot1->show();

    curve2->setRawSamples(m_vx.data(), m_vy2.data(), m_vx.count());
    curve2->setPen(* new QPen(Qt::red,2,Qt::SolidLine));
    curve2->attach(ui->qwtPlot2);
    ui->qwtPlot2->replot();
    ui->qwtPlot2->show();

    curve3->setRawSamples(m_vx.data(), m_vy3.data(), m_vx.count());
    curve3->setPen(* new QPen(Qt::blue,2,Qt::SolidLine));
    curve3->attach(ui->qwtPlot3);
    ui->qwtPlot3->replot();
    ui->qwtPlot3->show();

    g_nIdxChart++;
    */
}


void Controller::onTimeout()
{
    unsigned char tmpPckt[PACKET_LENGTH];
    int nHigh, nLow;

    nHigh = g_nIdxTimer/256;
    nLow = g_nIdxTimer%256;

    tmpPckt[0] = 0x0b;
    tmpPckt[1] = 0x10;
    tmpPckt[2] = nHigh;
    tmpPckt[3] = nLow;
    tmpPckt[4] = 0x0A;
    tmpPckt[5] = 0xF0;
    tmpPckt[6] = nHigh;
    tmpPckt[7] = nLow;
    tmpPckt[8] = 0x03;
    tmpPckt[9] = 0x20;
    tmpPckt[10] = 0x43;
    QByteArray send_Data;

//    QString str = "asdfghjhklopiuytres";
//    send_Data = str.toUtf8().left(19);

    for(int k=0; k<11; k++)
        send_Data.push_back(tmpPckt[k]);

    qport->write(send_Data.data());

    g_nIdxTimer++;
    if(g_nIdxTimer > AXIS_Y_SIZE*4)
        g_nIdxTimer = 0;
}

void Controller::text_Sending()
{

}

bool Controller::DoPacket(unsigned char buf[], float* argRet0, float* argRet1, float* argRet2, float* argRet3)
{
    int nTmp;
    char ch[4];

    *argRet0 = 0;
    *argRet1 = 0;
    *argRet2 = 0;
    *argRet3 = 0;
/*
    if(buf[0]!=0x0b)
        return false;

    if(buf[1] != 0x10)
        return false;

    if(buf[10] != 0x43)
        return false;

    nTmp = (int) ((double) (buf[2] * 255 + buf[3]) / 3.3);
    *argRet0 = nTmp;

    nTmp = (int) ((double) (buf[4] * 255 + buf[5]) / 3.3);
    *argRet1 = nTmp;

    nTmp = (int) ((double) (buf[6] * 255 + buf[7]) / 3.3);
    *argRet2 = nTmp;

    nTmp = (int) ((double) (buf[8] * 255 + buf[9]) / 3.3);
    *argRet3 = nTmp;
*/

    if(buf[0]!=0x31)
        return false;

    if(buf[1] != 0x31)
        return false;

    if(buf[2] != 0x31)
        return false;
    if(buf[3] != 0x36)
        return false;

    ch[0] = buf[5];
    ch[1] = buf[6];
    ch[2] = buf[7];
    ch[3] = buf[8];

    nTmp = atoi(ch);
    *argRet0 = (float) ((double) nTmp/3.3);

    ch[0] = buf[9];
    ch[1] = buf[10];
    ch[2] = buf[11];
    ch[3] = buf[12];

    nTmp = atoi(ch);
    *argRet1 = (float) ((double) nTmp/3.3);

    ch[0] = buf[13];
    ch[1] = buf[14];
    ch[2] = buf[15];
    ch[3] = buf[16];

    nTmp = atoi(ch);
    *argRet2 = (float) ((double) nTmp/3.3);

    ch[0] = buf[17];
    ch[1] = buf[18];
    ch[2] = buf[19];
    ch[3] = buf[20];

    nTmp = atoi(ch);
    *argRet3 = (float) ((double) nTmp/3.3);

    return true;
}
void Controller::openPort(bool bOpen)
{
    if(bOpen)
    {
        qport->setPortName("/dev/ttyUSB0");
        if(qport->open(QIODevice::ReadWrite))
            QObject::connect(qport, SIGNAL(readyRead()), this, SLOT(text_Reading()));
    }
    else
    {
        qport->close();
        QObject::disconnect(qport, SIGNAL(readyRead()), this, SLOT(text_Reading()));
    }
}

void Controller::text_Reading()
{
    bool bRet=false;
     int k = 0, nCnt = 0;
     float result0, result1, result2, result3;
     unsigned char   ch;
     unsigned char*   tmpBuf;
     int jj=0;

     QByteArray read_Data;
     read_Data = qport->readAll();

     nCnt = read_Data.count();
     tmpBuf = new unsigned char[nCnt];

     // copy data from serial to temp buf
     for(k=0; k<nCnt; k++)
     {
         tmpBuf[k] = read_Data.at(k);
     }

     for(k=0; k<nCnt; k++)
     {
         ch = tmpBuf[k];

         if(g_bPckt)
         {
             g_bufPckt[g_nIdxPckt] = ch;
             g_nIdxPckt++;

             if(g_nIdxPckt >= PACKET_LENGTH)
             {
                 bRet = DoPacket(g_bufPckt, &result0, &result1, &result2, &result3);

                 if(bRet)
                 {
                     UpdateChart(result0, result1, result2, result3);
                 }

                 memset(g_bufPckt, 0, PACKET_LENGTH);
                 g_nIdxPckt = 0;
                 g_bPckt = false;
             }
         }
         else
         {
 //            if(ch == 0x0b)  // start code for packet
             if(ch == 0x31)
             {

                 g_bufPckt[g_nIdxPckt] = ch;
                 g_nIdxPckt++;
                 g_bPckt = true;
               }
         }
     }

     delete[] tmpBuf;
 //    ui->lblReceive->setText(read_Data);
}
