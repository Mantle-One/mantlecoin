#!/usr/bin/env bash
# Copyright (c) 2016-2019 The Mantle Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

MANTLED=${MANTLED:-$BINDIR/mantled}
MANTLECLI=${MANTLECLI:-$BINDIR/mantle-cli}
MANTLETX=${MANTLETX:-$BINDIR/mantle-tx}
WALLET_TOOL=${WALLET_TOOL:-$BINDIR/mantle-wallet}
MANTLEQT=${MANTLEQT:-$BINDIR/qt/mantle-qt}

[ ! -x $MANTLED ] && echo "$MANTLED not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
read -r -a MACVER <<< "$($MANTLECLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }')"

# Create a footer file with copyright content.
# This gets autodetected fine for mantled if --version-string is not set,
# but has different outcomes for mantle-qt and mantle-cli.
echo "[COPYRIGHT]" > footer.h2m
$MANTLED --version | sed -n '1!p' >> footer.h2m

for cmd in $MANTLED $MANTLECLI $MANTLETX $WALLET_TOOL $MANTLEQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${MACVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${MACVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
