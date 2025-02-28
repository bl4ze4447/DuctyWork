//
// Created by Antonie Gabriel Belu on 20.02.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QStandardItemModel>


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tableView->setModel(&model);
    model.setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model.setHorizontalHeaderItem(1, new QStandardItem("PID"));

    proc_manager = process_manager::create();
    proc_manager->fill_processes();
    for (const auto processes = proc_manager->get_processes(); const auto& process : processes) {
        std::cout << process.get_name() << std::endl;
        std::cout << process.get_pid() << std::endl;
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
