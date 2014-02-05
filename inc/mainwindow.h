#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QMainWindow>

class MainWindow : public QMainWindow
{
Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow() {}

protected:
    void initMenu();

protected slots:
    void openFile();

signals:
    void emitFileName(QString file_name);
};

#endif // __MAIN_WINDOW_H__
