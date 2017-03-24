#include "appbody.h"
#include <QPainter>

AppBody::AppBody(QWidget *parent)
    : QWidget(parent)
{

}

void AppBody::setText(const QString &text)
{
    m_bodyText = text;

    update();
}

void AppBody::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QTextOption appNameOption;
    appNameOption.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    appNameOption.setWrapMode(QTextOption::WordWrap);
    QFont appNamefont(painter.font());
    appNamefont.setPixelSize(12);

    const QFontMetrics fm(appNamefont);

    QString appBody = holdTextInRect(fm, m_bodyText, this->rect());

    painter.setFont(appNamefont);
    painter.setBrush(QBrush(Qt::transparent));
    painter.setPen(Qt::black);
    painter.drawText(this->rect(), appBody, appNameOption);

    QWidget::paintEvent(event);
}

const QString AppBody::holdTextInRect(const QFontMetrics &fm, const QString &text, const QRect &rect) const
{
    const int textFlag = Qt::AlignTop | Qt::AlignLeft | Qt::TextWordWrap;

    if (rect.contains(fm.boundingRect(rect, textFlag, text)))
        return text;

    QString str(text + "...");

    while (true)
    {
        if (str.size() < 4)
            break;

        QRect boundingRect = fm.boundingRect(rect, textFlag, str);
        if (rect.contains(boundingRect))
            break;

        str.remove(str.size() - 4, 1);
    }

    return str;
}
