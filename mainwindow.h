//------------------------------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//------------------------------------------------------------------------------
#include <QMainWindow>
#include <QDebug>
#include <math.h>

#include "beatdispenser.h"
#include "animationcontroller.h"

namespace Ui {
    class MainWindow;
}

//------------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(BeatDispenser *beatDispenser = NULL,
                        AnimationController *animationController = NULL);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    BeatDispenser *beatDispenser;
    AnimationController *animationController;

private slots:
    void beatDetected();
    void beatIndicatorTimerTimeout();

    // GUI events to control animations.
    void on_BeatTapButton_pressed();
    void on_useMidiBeatCheckbox_toggled(bool checked);
    void on_strobeCheckbox_toggled(bool checked);
    void on_strobeSlider_valueChanged(int value);
    void on_sweepCheckbox_toggled(bool checked);
    void on_sweepSpeedSlider_valueChanged(int value);
    void on_snakeCheckbox_toggled(bool checked);
    void on_spinBox_valueChanged(int arg1);
    void on_coolModeCheckbox_toggled(bool checked);
    void on_precipitationCheckbox_toggled(bool checked);
    void on_checkBox_toggled(bool checked);
    void on_planeCheckbox_toggled(bool checked);
};

//------------------------------------------------------------------------------
#endif // MAINWINDOW_H

//------------------------------------------------------------------------------
