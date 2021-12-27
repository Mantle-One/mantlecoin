// Copyright (c) 2018-2020 The Mantle Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MANTLE_QT_TEST_APPTESTS_H
#define MANTLE_QT_TEST_APPTESTS_H

#include <QObject>
#include <set>
#include <string>
#include <utility>

class MantleApplication;
class MantleGUI;
class RPCConsole;

class AppTests : public QObject
{
    Q_OBJECT
public:
    explicit AppTests(MantleApplication& app) : m_app(app) {}

private Q_SLOTS:
    void appTests();
    void guiTests(MantleGUI* window);
    void consoleTests(RPCConsole* console);

private:
    //! Add expected callback name to list of pending callbacks.
    void expectCallback(std::string callback) { m_callbacks.emplace(std::move(callback)); }

    //! RAII helper to remove no-longer-pending callback.
    struct HandleCallback
    {
        std::string m_callback;
        AppTests& m_app_tests;
        ~HandleCallback();
    };

    //! Mantle application.
    MantleApplication& m_app;

    //! Set of pending callback names. Used to track expected callbacks and shut
    //! down the app after the last callback has been handled and all tests have
    //! either run or thrown exceptions. This could be a simple int counter
    //! instead of a set of names, but the names might be useful for debugging.
    std::multiset<std::string> m_callbacks;
};

#endif // MANTLE_QT_TEST_APPTESTS_H
