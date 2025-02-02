#include "sizing.h"

#include <QScreen>
#include <QDebug>
#include <QGuiApplication>
#include <math.h>

Sizing::Sizing(QObject *parent) : QObject(parent)
{
    m_valid = false;
    m_mm_factor = 10;
    m_dp_factor = 1;

    m_densitie = mdpi;
    qreal refHeight =  854.; //N9
    qreal refWidth = 480.; //N9
    qreal refDpi = 251; //N9
    Q_UNUSED(refDpi);

    m_p_height = qgetenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT").toInt();
    m_p_width = qgetenv("QT_QPA_EGLFS_PHYSICAL_WIDTH").toInt();

    QScreen *screen = QGuiApplication::primaryScreen();


    m_height = qMax(screen->size().width(), screen->size().height());
    m_width = qMin(screen->size().width(), screen->size().height());

    m_dpi = screen->physicalDotsPerInch();

    m_scaleRatio = qMin(m_height/refHeight, m_width/refWidth);
    m_fontRatio = floor(m_scaleRatio*10) /10; //qMin(m_height*refDpi/(m_dpi*refHeight), m_width*refDpi/(m_dpi*refWidth))*10)/10;
    qDebug() << "Height: " << m_height << "Width: " << m_width;
    qDebug() << "Scale ratio: " << m_scaleRatio << " Font: " << m_fontRatio;

    if(m_width >= 2160){
        //>2160
        m_launcher_icon_size = 256;
    }else if (m_width >= 1080){
        //1080-2159
        m_launcher_icon_size = 128;
    }else if(m_width >= 720){
        //720-1079
        m_launcher_icon_size = 108;
    }else {
        //>720
        m_launcher_icon_size = 86;
    }

    qDebug() << "DPI is " << m_dpi;

    if(m_dpi < 140){
        m_densitie = ldpi;
    }else if(m_dpi >= 140 && m_dpi < 200){
        //~160dpi
        m_densitie = mdpi;
    }else if(m_dpi >= 200 && m_dpi < 300){
        //~240dpi
        m_densitie = hdpi;
    }else if(m_dpi >= 300 && m_dpi < 420){
        //~320dpi
        m_densitie = xhdpi;
    }else if(m_dpi >= 420 && m_dpi < 560){
        //~480dpi
        m_densitie = xxhdpi;
    }else{
        m_densitie = xxxhdpi;
    }

    if(m_p_height > 0 && m_p_width >0){
        m_valid = true;
        setMmScaleFactor();
    }else{
        if(m_p_height == 0){
            qWarning("QT_QPA_EGLFS_PHYSICAL_HEIGHT is not set!");
        }

        if(m_p_width == 0){
            qWarning("QT_QPA_EGLFS_PHYSICAL_WIDTH is not set!");
        }
        qWarning("Device mm sizing don`t work");
    }
    setDpScaleFactor();
}

void Sizing::setMmScaleFactor()
{
    if(m_p_width != 0){
        m_mm_factor = m_width/m_p_width;
    }

    qDebug() << "MM scale factor is " << m_mm_factor;
}

void Sizing::setDpScaleFactor()
{
    switch (m_densitie) {
    case ldpi:
        m_dp_factor = 0.5;
        break;
    case mdpi:
        m_dp_factor = 0.6;
        break;
    case hdpi:
        m_dp_factor = 1;
        break;
    case xhdpi:
        m_dp_factor = 1.5;
        break;
    case xxhdpi:
        m_dp_factor = 2;
        break;
    case xxxhdpi:
        m_dp_factor = 2.5;
        break;
    default:
        m_dp_factor = 1.5;
        break;
    }

    qDebug() << "DP scale factor is " << m_dp_factor;
}

float Sizing::mm(float value)
{
    return value*m_mm_factor;
}

float Sizing::dp(float value)
{
    return value*m_dp_factor;
}

float Sizing::ratio(float value)
{
    return floor(value*m_scaleRatio);
}


void Sizing::setMmScaleFactor(float value)
{
    if(value != 0)
    {
        qDebug() << "Set custom mm scale factor";

        m_p_width = value;
        setMmScaleFactor();
    }
}


void Sizing::setDpScaleFactor(float value)
{
    if(value != 0)
    {
        qDebug() << "Set custom dp scale factor";

        m_dp_factor = value;
    }
}

void Sizing::setScaleRatio(qreal scaleRatio)
{
    if(scaleRatio != 0)
        m_scaleRatio = scaleRatio;
}

void Sizing::setFontRatio(qreal fontRatio)
{
    if(fontRatio !=0 )
        m_fontRatio = fontRatio;
}
