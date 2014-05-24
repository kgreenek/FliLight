//------------------------------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

//------------------------------------------------------------------------------
MainWindow::MainWindow(BeatDispenser *beatDispenser,
                       AnimationController *animationController) :
    QMainWindow(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->beatDispenser = beatDispenser;
    this->animationController = animationController;

    // Detect when a beat happens so can show it with the beatIndicator.
    connect(beatDispenser, SIGNAL(beatDetected()), this, SLOT(beatDetected()));
}

//------------------------------------------------------------------------------
MainWindow::~MainWindow() {
    delete ui;
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
void MainWindow::on_BeatTapButton_pressed() {
    beatDispenser->tapButtonPressed();
}

//------------------------------------------------------------------------------
void MainWindow::on_useMidiBeatCheckbox_toggled(bool checked) {
    beatDispenser->setUseMidi(checked);
}

//------------------------------------------------------------------------------
void MainWindow::on_strobeCheckbox_toggled(bool checked) {
    animationController->setAnimationRunning(STROBE_ANIMATION, checked);
}

//------------------------------------------------------------------------------
void MainWindow::on_strobeSlider_valueChanged(int value) {
    animationController->setStrobeSpeed(value);
}

//------------------------------------------------------------------------------
void MainWindow::on_sweepCheckbox_toggled(bool checked) {
    animationController->setAnimationRunning(UP_DOWN_SWEEP_ANIMATION, checked);
}

//------------------------------------------------------------------------------
void MainWindow::on_sweepSpeedSlider_valueChanged(int value) {
    animationController->setUpDownSweepSpeed(1 / pow(2.0, value));
}

//------------------------------------------------------------------------------
void MainWindow::on_snakeCheckbox_toggled(bool checked) {
    animationController->setAnimationRunning(BEAT_SNAKE_ANIMATION, checked);
}

//------------------------------------------------------------------------------
void MainWindow::on_spinBox_valueChanged(int value) {
    animationController->setSnakeLen(value);
}

//------------------------------------------------------------------------------
void MainWindow::on_coolModeCheckbox_toggled(bool checked) {
    animationController->setSnakeCoolMode(checked);
}

//------------------------------------------------------------------------------
void MainWindow::on_precipitationCheckbox_toggled(bool checked) {
    animationController->setAnimationRunning(PRECIPITATION_ANIMATION, checked);
}

//------------------------------------------------------------------------------
void MainWindow::on_checkBox_toggled(bool checked) {
    animationController->setAnimationRunning(ON_ANIMATION, checked);
}

//------------------------------------------------------------------------------
void MainWindow::on_planeCheckbox_toggled(bool checked) {
    animationController->setAnimationRunning(PLANE_ANIMATION, checked);
}

//------------------------------------------------------------------------------
