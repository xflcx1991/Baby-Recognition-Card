#include "widget.h"
#include "ui_widget.h"
#include <QBitmap>
#include <QBrush>
#include <QDebug>
#include <QImage>
#include <QMouseEvent>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QRect>
#include <QSignalMapper>
Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_currentDrawImageIndx(0)
    , isFullScreen(false)
{
    ui->setupUi(this);
    //    this->setPalette(QPalette(Qt::transparent));
    //    this->setAutoFillBackground(true);

    //设置左右按钮
    QPixmap pixmapLeft(":/images/left");
    ui->btnLeft->setMask(QBitmap(pixmapLeft.mask()));
    ui->btnLeft->resize(pixmapLeft.size());

    QPixmap pixmapRight(":/images/right");
    ui->btnRight->setMask(QBitmap(pixmapRight.mask()));
    ui->btnRight->resize(pixmapRight.size());

    ui->frame->installEventFilter(this);

    //    painter = nullptr;

    //初始化图片名字列表
    initImageFileNameList();
    //初始化信号槽
    //    connect(ui->btnLeft, &QPushButton::clicked, this,
    //    &Widget::switchButtonClicked);
    //    connect(ui->btnRight, &QPushButton::clicked, this,
    //    &Widget::switchButtonClicked);
    connect(ui->btnLeft, &QPushButton::clicked,
        [=]() { switchButtonClicked(-1); });
    connect(ui->btnRight, &QPushButton::clicked,
        [=]() { switchButtonClicked(1); });
    qDebug() << "fsdfdsfdsf";
}

Widget::~Widget()
{
    delete ui;
}

/**
 * @brief 初始化图片名字列表
 */
void Widget::initImageFileNameList()
{
    //有15张图片
    for (int i = 0; i < IMAGENUM; ++i) {
        QString imageName = IMAGENAMEPATTERN.arg(i);

        m_imageFileNameList.append(imageName);
    }
}

void Widget::switchButtonClicked(int i)
{
    m_currentDrawImageIndx += i;
    if (m_currentDrawImageIndx < 0) {
        m_currentDrawImageIndx = IMAGENUM - 1;
    }
    if (m_currentDrawImageIndx >= IMAGENUM) {
        m_currentDrawImageIndx = 0;
    }
    //    paintOnWidget(ui->frame);
    ui->frame->update();
}
/*
void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    //创建QPainter对象
    QPainter painter(ui->frame);
    //    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    //    int W = this->width();
    //    int H = this->height();
    int W = ui->frame->width();
    int H = ui->frame->height();
    const int width = 1500;
    const int height = 1200;
    int availableW = 0;
    int availabelH = 0;
    int side = qMin(W, H);
    if (W > H) {
        double xi = static_cast<double>(side) / static_cast<double>(height);
        availabelH = side;
        availableW = static_cast<int>(width * xi);
    } else {
        double xi = static_cast<double>(side) / static_cast<double>(width);
        availabelH = static_cast<int>(height * xi);
        availableW = side;
    }
    qDebug() << W << H;
    qDebug() << availableW << availabelH;
    qDebug() << "*********************************";
    painter.setViewport((W - availableW) / 2, (H - availabelH) / 2, availableW,
availabelH);
    painter.setWindow(-(width / 2), -(height) / 2, width, height);
    //    painter.setWindow(0, 0, width, height);

    QRect rect(-(width / 2), -(height) / 2, width, height);
    //    QRect rect(0, 0, width, height);

    //设置画笔
    //    QPen pen;
    //    pen.setWidth(1);
    //    pen.setColor(Qt::red);
    //    pen.setStyle(Qt::SolidLine);
    //    pen.setCapStyle(Qt::FlatCap);
    //    pen.setJoinStyle(Qt::BevelJoin);
    //    painter.setPen(pen);
    //设置画刷
    //    QPixmap texturePixmap(":images/screen");
    //    QBrush brush;
    //    brush.setColor(Qt::yellow);
    //    brush.setStyle(Qt::TexturePattern);
    //    brush.setTexture(texturePixmap);
    //    painter.setBrush(brush);
    //绘图
    //    painter.drawRect(rect);
    //    painter.drawRect(rect);
    painter.drawImage(rect, QImage(":images/fruit_12.jpg"));
}
*/
bool Widget::eventFilter(QObject* watched, QEvent* e)
{
    if (watched == ui->frame) {
        if (e->type() == QEvent::Paint) {
            paintOnWidget(ui->frame);

            return true;
        }
    }

    return QWidget::eventFilter(watched, e);
}

void Widget::paintOnWidget(QWidget* w)
{
    qDebug() << "paintOnWidget";
    //创建QPainter对象
    QPainter painter(w);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    /*
  if (painter == nullptr) {
      painter = new QPainter(w);
      painter->setRenderHint(QPainter::Antialiasing);
      painter->setRenderHint(QPainter::TextAntialiasing);
  }
*/
    qDebug() << w->metaObject()->className();
    qDebug() << w->styleSheet();
    qDebug() << "================";
    int W = w->width();
    int H = w->height();
    const int width = 1500;
    const int height = 1200;
    int availableW = 0;
    int availabelH = 0;
    int side = qMin(W, H);
    if (W > H) {
        double xi = static_cast<double>(side) / static_cast<double>(height);
        availabelH = side;
        availableW = static_cast<int>(width * xi);
    } else {
        double xi = static_cast<double>(side) / static_cast<double>(width);
        availabelH = static_cast<int>(height * xi);
        availableW = side;
    }
    qDebug() << W << H;
    qDebug() << availableW << availabelH;
    qDebug() << "*********************************";
    painter.setViewport((W - availableW) / 2, (H - availabelH) / 2, availableW,
        availabelH);
    painter.setWindow(-(width / 2), -(height) / 2, width, height);
    //    painter.setWindow(0, 0, width, height);

    QRect rect(-(width / 2), -(height) / 2, width, height);

    painter.drawImage(rect,
        QImage(m_imageFileNameList.at(m_currentDrawImageIndx)));
    painter.end();
    //要或不要都能运行，内存占用增长也均一样，都保持在同一个数值后不变了
    //    delete painter;
    //    painter = nullptr;
}
// void Widget::mousePressEvent(QMouseEvent *event)
//{
//    qDebug() << "mousePressEvent";
//}

void Widget::mouseDoubleClickEvent(QMouseEvent* event)
{
    isFullScreen = !isFullScreen;
    if (isFullScreen) {
        this->showFullScreen();
    } else {
        this->showNormal();
    }

    QWidget::mouseDoubleClickEvent(event);
}
