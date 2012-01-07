#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Common.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addSpinBoxes(bool checked, int mCount, Range range);

private slots:
    void on_quantTriRadioButton_toggled(bool checked);

    void on_quantTraRadioButton_toggled(bool checked);

    void on_quantRelRadioButton_toggled(bool checked);

    void on_quantAbsRadioButton_toggled(bool checked);

    void on_quantifierAddPushButton_clicked();

private:
    Ui::MainWindow *ui;
    int mCount;
};

#endif // MAINWINDOW_H
