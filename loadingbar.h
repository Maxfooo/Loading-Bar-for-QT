#ifndef LOADINGBAR_H
#define LOADINGBAR_H

#include <QDebug>
#include <QLineEdit>
#include <QTimer>
#include <QFontMetrics>
#include <QLabel>
#include <vector>


// QTimer intervals (milliseconds)
constexpr int LB_TIMEOUT_SLOW      = 33;
constexpr int LB_TIMEOUT_NORMAL    = 10;
constexpr int LB_TIMEOUT_FAST      = 5;
constexpr int LB_TIMEOUT_VERY_FAST = 1;

//
constexpr int CHAR_WIDTH_FRACTION = 3;
const QChar LOADING_CHAR = '|';
const QChar LOADING_FILL = ' ';


struct LoadingBarBuffer
{
    QString buffer;
    int head;
    int tail;
    int load_width;
    LoadingBarBuffer()
    {head = 0; tail = 0; load_width = 0;}
};

class LoadingBar : public QObject
{
    Q_OBJECT
public:
    explicit LoadingBar(QLineEdit* lineEdit, QObject* parent = nullptr);
    ~LoadingBar();

    void setInterval(int speedSelect = LoadingBar::FAST);
    void setBarColor(QColor color = Qt::green);

    void clear();

    enum { SLOW, NORMAL, FAST, VERY_FAST };

signals:
    void repr(QString disp_str);

public slots:
    void start();
    void stop();
    void disp(QString str);
    void disp_stats();

private slots:
    void step();

private:
    QLineEdit* line_edit   = nullptr;
    QTimer* timer          = nullptr;
    int loading_char_width = 0;
    int char_width         = 0;
    int loading_counter    = 0;
    QPalette palette;
    struct LoadingBarBuffer lb_buffer;

    void initLineEdit();

};

#endif // LOADINGBAR_H
