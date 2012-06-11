//------------------------------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&beatDetector, SIGNAL(beatDetected()), this, SLOT(beatDetected()));
}

//------------------------------------------------------------------------------
MainWindow::~MainWindow() {
    delete ui;
}

//------------------------------------------------------------------------------
void MainWindow::on_BeatTapButton_pressed() {
    beatDetector.tapButtonPressed();
}

//------------------------------------------------------------------------------
void MainWindow::on_useMidiBeatCheckbox_toggled(bool checked) {
    beatDetector.useMidi = checked;
}

//------------------------------------------------------------------------------
void MainWindow::on_strobeSlider_valueChanged(int value) {
    strobeAnim.setStrobeSpeed(value);
}

//------------------------------------------------------------------------------
void MainWindow::on_strobeCheckbox_toggled(bool checked) {
    if (checked)
        strobeAnim.start();
    else
        strobeAnim.quit();
}

//------------------------------------------------------------------------------
void MainWindow::beatDetected() {
    ui->beatIndicator->setStyleSheet("background-color:rgb(58, 200, 255);");
    QTimer::singleShot(100, this, SLOT(beatIndicatorTimerTimeout()));
}

//------------------------------------------------------------------------------
void MainWindow::beatIndicatorTimerTimeout() {
    ui->beatIndicator->setStyleSheet("background-color:rgb(207, 207, 207);");
}

//------------------------------------------------------------------------------
void MainWindow::on_sweepCheckbox_toggled(bool checked) {
    if (checked)
        upDownSweepAnim.start();
    else
        upDownSweepAnim.quit();
}

//------------------------------------------------------------------------------
void MainWindow::on_sweepSpeedSlider_valueChanged(int value) {
    upDownSweepAnim.sem.acquire();
    upDownSweepAnim.sweepSpeed = 1 / pow(2.0, value);
    upDownSweepAnim.sem.release();
}

//------------------------------------------------------------------------------
void MainWindow::on_snakeCheckbox_toggled(bool checked) {
    if (checked)
        beatSnakeAnim.start();
    else
        beatSnakeAnim.quit();
}

//------------------------------------------------------------------------------
void MainWindow::on_spinBox_valueChanged(int value) {
    beatSnakeAnim.setSnakeLen(value);
}

//------------------------------------------------------------------------------
void MainWindow::on_coolModeCheckbox_toggled(bool checked) {
    beatSnakeAnim.coolMode = checked;
}

//------------------------------------------------------------------------------
void MainWindow::on_precipitationCheckbox_toggled(bool checked) {
    if (checked)
        precipitationAnim.start();
    else
        precipitationAnim.quit();
}

//------------------------------------------------------------------------------
void MainWindow::on_checkBox_toggled(bool checked) {
    if (checked)
        onAnim.start();
    else
        onAnim.quit();
}

//------------------------------------------------------------------------------
void MainWindow::on_planeCheckbox_toggled(bool checked) {
    if (checked)
        planeAnim.start();
    else
        planeAnim.quit();
}

//------------------------------------------------------------------------------
