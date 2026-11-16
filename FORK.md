# PaperNote — a Sioyek fork

PaperNote is a fork of [Sioyek](https://github.com/ahrm/sioyek), the PDF viewer built
for textbooks and research papers. It keeps Sioyek's keyboard-driven workflow and adds
a small feature for students: **exporting all highlights and bookmarks of a document to
a Markdown note file**, so annotations can be reused in Obsidian, Notion or any other
note system.

## What changed

| Change | Where |
| --- | --- |
| `export_highlights` command + `Ctrl+Shift+E` binding | `pdf_viewer/input.cpp`, `pdf_viewer/keys.config` |
| `MainWidget::handle_export_highlights()` — writes `<document>.notes.md` next to the PDF | `pdf_viewer/main_widget.{h,cpp}` |
| App name / bundle id / icon | `resources/Info.plist`, `resources/papernote.{icns,ico}`, `pdf_viewer_build_config.pro` |
| Window title shows the fork name | `pdf_viewer/main_widget.cpp` |
| Chinese menu bar (~80 command labels) | `pdf_viewer/ui_translation.h` |
| Chinese quick-start dialog on first launch + `F2` | `pdf_viewer/main_widget.cpp`, `pdf_viewer/input.cpp` |
| macOS DMG build script | `scripts/build_macos_dmg.sh` |
| Windows installer (Inno Setup) + CI workflow | `installer/windows/papernote.iss`, `.github/workflows/build-installers.yml` |

Everything else is upstream Sioyek, including its GPLv3 license (see `LICENSE`).

## Usage

Open a PDF, highlight some text (`h` + a letter) and/or add bookmarks, then press
`Ctrl+Shift+E`. PaperNote writes `YourDocument.notes.md` next to the PDF, grouped by
page, with the selected text, your annotation notes and bookmarks.

The command is also available from the command palette, so it can be bound to any key
or invoked with `sioyek --execute-command export_highlights`.

## Building

### macOS

```bash
brew install qt@5
git submodule update --init --recursive
QMAKE="$(brew --prefix qt@5)/bin/qmake" ./scripts/build_macos_dmg.sh
# -> dist/PaperNote-<version>-<arch>.dmg
```

### Windows

Use `build_windows.bat non_portable` with Qt 5.15/6.x + MSVC, then compile
`installer/windows/papernote.iss` with Inno Setup 6. The GitHub Actions workflow
`.github/workflows/build-installers.yml` builds the Windows installer automatically;
the macOS DMG is produced by `scripts/build_macos_dmg.sh`.

## License

GPLv3, inherited from Sioyek. The fork keeps the original copyright notices; see
`LICENSE` and the file headers.
