#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "ui_mainwindow.h"
#include "downloader/exrdownloader.h"
#include "downloader/exrdownloadparams.h"
#include "parser/exrparser.h"
#include "parser/exrparseparam.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    QWidget *pMainWidget = new QWidget(this);
    pMainWidget->setLayout(pLayout);
    QPushButton *pButton1 = new QPushButton("download", this);
    connect(pButton1, &QPushButton::clicked, this, &MainWindow::onDownloadClicked);
    pLayout->addWidget(pButton1);

    QPushButton *pButton2 = new QPushButton("parse", this);
    connect(pButton2, &QPushButton::clicked, this, &MainWindow::onParseClicked);
    pLayout->addWidget(pButton2);

    this->setCentralWidget(pMainWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include <QDebug>
void MainWindow::onDownloadClicked()
{
    qDebug()<<"onDownloadClicked";
    std::shared_ptr<EXRDownloadParams> pParam(new EXRDownloadParams);
    pParam->m_strStartTime = "2019-01-01";
    pParam->m_strEndTime = "2019-01-11";
    pParam->m_nNationCode = 3030;
    pParam->m_nPageIndex = 75;

    std::shared_ptr<EXRDownloader> pDownloader(new EXRDownloader);
    pDownloader->doDownload(pParam);
}

#include <QFile>
void MainWindow::onParseClicked()
{
    qDebug()<<"onParseClicked";
    std::shared_ptr<EXRParseParam> pParam(new EXRParseParam);
    QFile file("./webData");
    file.open(QIODevice::ReadOnly);
    pParam->m_dataArr = file.readAll();
    file.close();
    EXRParser parser;
    parser.doParse(pParam);
}
