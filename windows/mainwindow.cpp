//
// Created by Antonie Gabriel Belu on 20.02.2025.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QHeaderView"

#include "../process/process_manager.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setFixedSize(this->size());

    proc_manager = process_manager::create();
    if (proc_manager == nullptr)
        return;

    proc_manager->fill_processes();
    const auto processes = proc_manager->get_processes();
    QList<QStandardItem*> items{};
    for (const auto &process : processes) {
        items << new QStandardItem(QString::fromStdString(process.get_name()));
        model.appendRow(items);
        items.clear();
    }

    ui->QProcList->setModel(&model);
}

MainWindow::~MainWindow() {
    delete ui;
}
