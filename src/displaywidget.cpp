#include <QMouseEvent>
#include <QImage>

#include "displaywidget.h"

DisplayWidget::DisplayWidget(QWidget * parent) : QGLWidget(parent)
{
    texture_id = 0;
    image = 0;
}

DisplayWidget::~DisplayWidget()
{
    deleteTexture(texture_id);
    if (image) delete image;
}

void DisplayWidget::loadFile(QString file_name)
{
    QImage * test_image = new QImage(file_name);

    if (test_image->isNull()) {
        delete test_image;
        return;
    }

    if (image) {
        deleteTexture(texture_id);
        delete image;
    }

    image = test_image;
    texture_id = bindTexture(*image, GL_TEXTURE_2D, GL_RGBA,
                             QGLContext::LinearFilteringBindOption);

    setMinimumSize(image->size());
    updateGL();
}

void DisplayWidget::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width(), height(), 0, 0, 1);
    glViewport(0, 0, width(), height());

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    QColor color = palette().color(QPalette::Window);
    glClearColor(color.redF(), color.greenF(), color.blueF(), 1.0f);
}

void DisplayWidget::resizeGL(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_MODELVIEW);
}

void DisplayWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (!image) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2i(0, 0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2i(image->width(), 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2i(image->width(), image->height());
    glTexCoord2f(0.0f, 1.0f);
    glVertex2i(0, image->height());
    glEnd();
    glDisable(GL_TEXTURE_2D);

    if (start_selection == end_selection) return;

    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);
    glColor4f(0.2f, 0.2f, 0.2f, 0.2f);

    glBegin(GL_QUADS);
    glVertex2i(start_selection.x(), start_selection.y());
    glVertex2i(start_selection.x(), end_selection.y());
    glVertex2i(end_selection.x(), end_selection.y());
    glVertex2i(end_selection.x(), start_selection.y());
    glEnd();
    glPopAttrib();
    glPopMatrix();
}

void DisplayWidget::mousePressEvent(QMouseEvent * event)
{
    start_selection = end_selection = event->pos();
    updateGL();
}

void DisplayWidget::mouseMoveEvent(QMouseEvent * event)
{
    end_selection = event->pos();
    updateGL();
}
