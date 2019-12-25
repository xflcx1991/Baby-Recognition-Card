#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QMouseEvent>
class QMouseEvent;
//class QPainter;
QT_BEGIN_NAMESPACE namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget() override;

protected:
    //    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    virtual bool eventFilter(QObject* watched, QEvent* e) Q_DECL_OVERRIDE;
    void paintOnWidget(QWidget* w);
    //    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    Ui::Widget* ui;
    //图片列表
    QList<QString> m_imageFileNameList;
    //当前显示图片index
    int m_currentDrawImageIndx;
    // 切换图片;
    QImage m_currentImage;
    QImage m_nextImage;
    const int IMAGENUM = 15;
    const QString IMAGENAMEPATTERN = ":images/fruit_%1.jpg";
    //    QPainter *painter;
    void initImageFileNameList();
    void paintByPainter(QPainter painter);
    bool isFullScreen;

private slots:
    void switchButtonClicked(int);
};
#endif // WIDGET_H
