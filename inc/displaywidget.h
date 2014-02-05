#ifndef __DISPLAY_WIDGET_H__
#define __DISPLAY_WIDGET_H__

#include <QGLWidget>

class DisplayWidget : public QGLWidget {
Q_OBJECT

public:
    DisplayWidget(QWidget * parent = 0);
    ~DisplayWidget();

public slots:
    void loadFile(QString file_name);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

    GLuint texture_id;
    QImage * image;

    QPoint start_selection;
    QPoint end_selection;
};


#endif /* __DISPLAY_WIDGET_H__ */
