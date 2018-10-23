#ifndef CENTERFRAME_H
#define CENTERFRAME_H
#include <QFrame>
#include <QComboBox>

class CenterFrame : public QFrame
{
public:
    CenterFrame();
    void setPenWidth(int width);
    void setPenColor(QColor color);
    void setPenStyle(int style);

    void clearPaint();
};

#endif // CENTERFRAME_H
