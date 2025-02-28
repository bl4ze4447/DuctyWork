//
// Created by Antonie Gabriel Belu on 20.02.2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QWidget>

#include "../process/process_manager.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QStandardItemModel model{};
    process_manager * proc_manager;
};


#endif //MAINWINDOW_H
