#define QT_NO_DEBUG_OUTPUT

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <myglobal.h>


#include <QMainWindow>
#include <UART.h>
#include <QPainter>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QGraphicsPixmapItem>
#include "myChipMap.h"
#include "myAgent.h"
#include <QThread>
#include <map>
#include <QImage>
#include <string>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    bool eventFilter(QObject* watched, QEvent* event);
    QString qs;

  //  map<BYTE, int> data2index_map;
   // map<int, BYTE> index2data_map;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QMessageBox *msgBox;


private slots:
    void update_display();
    void errorbox(QString ErrorMessage);


signals:

    void refresh_TextUartResponse();

private:
   // QThread agent_thread;

    Ui::MainWindow *ui;
    void refresh_uart_conf(void);
    myAgent  *      cur_agent;
    QGraphicsScene* scene;
    QGraphicsView*  view;
    void refresh_result_map_paint(int);

    QImage * image_good;
    QImage * image_bad;
    QImage * image_none;
};

#endif // MAINWINDOW_H
