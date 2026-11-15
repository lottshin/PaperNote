#!/usr/bin/env bash
#
# Build PaperNote (Sioyek fork) on macOS and package it as a DMG.
#
# Usage:
#   QMAKE=/opt/homebrew/opt/qt@5/bin/qmake ./scripts/build_macos_dmg.sh
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

VERSION="${VERSION:-1.0.0}"
JOBS="$(sysctl -n hw.logicalcpu)"
ARCH="$(uname -m)"

if [ -z "${QMAKE:-}" ]; then
    QMAKE="$(command -v qmake || true)"
fi
if [ -z "$QMAKE" ] || [ ! -x "$QMAKE" ]; then
    echo "error: qmake not found. Install Qt (brew install qt@5) and pass QMAKE=/path/to/qmake" >&2
    exit 1
fi

echo "==> qmake: $QMAKE"
echo "==> version: $VERSION ($ARCH)"

if [ ! -f mupdf/build/release/libmupdf.a ]; then
    echo "==> building mupdf"
    # MUPDF_MAKE_FLAGS lets a build reuse distro libraries instead of the
    # bundled submodules, e.g. USE_SYSTEM_FREETYPE=yes USE_SYSTEM_HARFBUZZ=yes ...
    # shellcheck disable=SC2086
    make -C mupdf -j"$JOBS" ${MUPDF_MAKE_FLAGS:-}
fi

echo "==> building PaperNote"
QMAKE_ARGS=("CONFIG+=non_portable")
if [ -n "${EXTRA_LIBS:-}" ]; then
    QMAKE_ARGS+=("LIBS+=$EXTRA_LIBS")
fi
"$QMAKE" "${QMAKE_ARGS[@]}" pdf_viewer_build_config.pro
make -j"$JOBS"

echo "==> assembling PaperNote.app"
rm -rf build dist
mkdir -p build dist

mv sioyek.app build/PaperNote.app

# Drop any stale runtime files sitting next to the executable; the app reads
# its configs/shaders/tutorial from Contents/Resources on macOS.
rm -rf build/PaperNote.app/Contents/MacOS/shaders
rm -f build/PaperNote.app/Contents/MacOS/*.config
rm -f build/PaperNote.app/Contents/MacOS/tutorial.pdf

# On macOS, Sioyek reads its default configs, shaders and tutorial from
# Contents/Resources (see configure_paths() in pdf_viewer/main.cpp).
RESOURCES="build/PaperNote.app/Contents/Resources"
mkdir -p "$RESOURCES"
cp -R pdf_viewer/shaders "$RESOURCES/shaders"
cp pdf_viewer/prefs.config \
   pdf_viewer/prefs_user.config \
   pdf_viewer/keys.config \
   pdf_viewer/keys_user.config \
   "$RESOURCES/"
cp tutorial.pdf "$RESOURCES/tutorial.pdf"

echo "==> bundling Qt frameworks"
"$(dirname "$QMAKE")/macdeployqt" build/PaperNote.app -always-overwrite

echo "==> ad-hoc code signing"
codesign --force --deep --sign - build/PaperNote.app

echo "==> creating DMG"
STAGE="$ROOT/build/dmg"
mkdir -p "$STAGE"
cp -R build/PaperNote.app "$STAGE/"
ln -sfn /Applications "$STAGE/Applications"

DMG="$ROOT/dist/PaperNote-${VERSION}-${ARCH}.dmg"
hdiutil create -volname "PaperNote" -srcfolder "$STAGE" -ov -format UDZO "$DMG"

echo "==> done: $DMG"
