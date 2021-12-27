// Copyright (c) 2011-2019 The Mantle Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MANTLE_QT_OPENURIDIALOG_H
#define MANTLE_QT_OPENURIDIALOG_H

#include <QDialog>

namespace Ui {
    class OpenURIDialog;
}

class OpenURIDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenURIDialog(QWidget *parent);
    ~OpenURIDialog();

    QString getURI();

protected Q_SLOTS:
    void accept() override;

private:
    Ui::OpenURIDialog *ui;
};

#endif // MANTLE_QT_OPENURIDIALOG_H
