#include "loadingbar.h"

LoadingBar::LoadingBar(QLineEdit *lineEdit, QObject *parent) : QObject(parent)
{
    line_edit = lineEdit;

    palette.setColor(QPalette::Text,Qt::green);
    line_edit->setPalette(palette);

    initLineEdit();

    timer = new QTimer(this);
    timer->setInterval(LB_TIMEOUT_FAST);
    connect(timer, SIGNAL(timeout()), this, SLOT(step()));
}

LoadingBar::~LoadingBar()
{
    if (timer->isActive()) { timer->stop(); }
}

void LoadingBar::initLineEdit()
{
    loading_char_width = 3; // QFontMetrics(QLabel(LOADING_CHAR).font()).width(LOADING_CHAR) - 1;
    loading_char_width = loading_char_width < 1 ? 1 : loading_char_width;
    char_width = line_edit->width() / loading_char_width;
    lb_buffer.load_width = char_width / CHAR_WIDTH_FRACTION;
    clear();
}

void LoadingBar::start()
{
    initLineEdit();
    disp(QString("Starting\n"));
    timer->start();
}

void LoadingBar::stop()
{
    disp(QString("Stopping\n"));
    timer->stop();
    initLineEdit();
}

void LoadingBar::step()
{
    if (loading_counter >= (char_width + lb_buffer.load_width))
    {
        loading_counter = 0;
        lb_buffer.head  = 0;
        lb_buffer.tail  = 0;
    }
    else
    {
        loading_counter++;

        if (loading_counter > lb_buffer.load_width)
        {
            if (lb_buffer.head >= char_width)
            {
                lb_buffer.buffer.replace(lb_buffer.tail, 1, LOADING_FILL);
                lb_buffer.tail = lb_buffer.tail < lb_buffer.head ? lb_buffer.tail+1 : lb_buffer.tail;
            }
            else
            {
                lb_buffer.buffer.replace(lb_buffer.tail++, 1, LOADING_FILL);
                lb_buffer.buffer.replace(lb_buffer.head++, 1, LOADING_CHAR);
            }
        }
        else
        {
            lb_buffer.buffer.replace(lb_buffer.head++, 1, LOADING_CHAR);
        }
    }

    line_edit->setText(lb_buffer.buffer);
}

void LoadingBar::clear()
{
    loading_counter = 0;
    lb_buffer.buffer.clear();
    lb_buffer.buffer.fill(LOADING_FILL, char_width);
    lb_buffer.head  = 0;
    lb_buffer.tail  = 0;
    line_edit->setText(lb_buffer.buffer);
}

void LoadingBar::setInterval(int speedSelect)
{
    int interval = LB_TIMEOUT_FAST;

    switch (speedSelect)
    {
        case LoadingBar::SLOW:      interval = LB_TIMEOUT_SLOW;      break;
        case LoadingBar::NORMAL:    interval = LB_TIMEOUT_NORMAL;    break;
        case LoadingBar::FAST:      interval = LB_TIMEOUT_FAST;      break;
        case LoadingBar::VERY_FAST: interval = LB_TIMEOUT_VERY_FAST; break;
        default:                    interval = LB_TIMEOUT_FAST;
    }

    if (timer->isActive())
    {
        timer->stop();
        timer->setInterval(interval);
        timer->start();
    }
    else { timer->setInterval(interval); }
}

void LoadingBar::setBarColor(QColor color)
{
    palette.setColor(QPalette::Text, color);
    line_edit->setPalette(palette);
}

void LoadingBar::disp(QString str)
{
    QString disp_str = QString("\n- Loading Bar Display -\n") + str;

    emit repr(disp_str);
}

void LoadingBar::disp_stats()
{
    QString disp_str = QString("Char Width......... %1\n") + \
                       QString("Loading Bar Width.. %2\n") + \
                       QString("Line Edit Width.... %3\n") + \
                       QString("'|' Width.......... %4\n");

    disp_str = disp_str.arg(char_width).arg(lb_buffer.load_width).arg(line_edit->width()).arg(loading_char_width);

    disp(disp_str);
}
