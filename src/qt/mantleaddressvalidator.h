// Copyright (c) 2011-2014 The Mantle Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MANTLE_QT_MANTLEADDRESSVALIDATOR_H
#define MANTLE_QT_MANTLEADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class MantleAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MantleAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Mantle address widget validator, checks for a valid mantle address.
 */
class MantleAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MantleAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // MANTLE_QT_MANTLEADDRESSVALIDATOR_H
