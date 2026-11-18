#pragma once

// PaperNote visual theme: warm-minimal light palette and a matching dark palette.
// One stylesheet, generated from tokens, plus QPainter-drawn icons.

#include <QApplication>
#include <QColor>
#include <QGuiApplication>
#include <QIcon>
#include <QPainter>
#include <QPainterPath>
#include <QPalette>
#include <QPixmap>
#include <QString>
#include <QStyleHints>

namespace papernote {

enum class ThemeMode { System = 0, Light = 1, Dark = 2 };

inline ThemeMode& requested_mode() {
    static ThemeMode mode = ThemeMode::Light;
    return mode;
}

inline bool& dark_active() {
    static bool dark = false;
    return dark;
}

inline bool is_dark() {
    return dark_active();
}

inline QColor bg() {
    return is_dark() ? QColor(0x19, 0x19, 0x18) : QColor(0xff, 0xff, 0xff);
}
inline QColor surface() {
    return is_dark() ? QColor(0x20, 0x20, 0x20) : QColor(0xf7, 0xf6, 0xf4);
}
inline QColor surface_alt() {
    return is_dark() ? QColor(0x26, 0x26, 0x25) : QColor(0xf1, 0xef, 0xec);
}
inline QColor border() {
    return is_dark() ? QColor(0x34, 0x33, 0x2f) : QColor(0xe7, 0xe3, 0xdd);
}
inline QColor text() {
    return is_dark() ? QColor(0xec, 0xec, 0xea) : QColor(0x1f, 0x1e, 0x1c);
}
inline QColor text_muted() {
    return is_dark() ? QColor(0x9a, 0x97, 0x91) : QColor(0x6f, 0x6a, 0x64);
}
inline QColor accent() {
    return is_dark() ? QColor(0x23, 0x83, 0xe2) : QColor(0x00, 0x75, 0xde);
}
inline QColor accent_hover() {
    return is_dark() ? QColor(0x3b, 0x93, 0xe8) : QColor(0x00, 0x68, 0xc4);
}
inline QColor accent_soft() {
    return is_dark() ? QColor(0x17, 0x29, 0x3a) : QColor(0xe9, 0xf4, 0xfd);
}
inline QColor accent_text() {
    return is_dark() ? QColor(0x8f, 0xc2, 0xf0) : QColor(0x0b, 0x5f, 0xa5);
}

inline ThemeMode system_mode() {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    return QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark
        ? ThemeMode::Dark
        : ThemeMode::Light;
#else
    return ThemeMode::Light;
#endif
}

inline QString app_stylesheet() {
    QString qss = QStringLiteral(R"QSS(
QToolTip {
    background: @bg; color: @text; border: 1px solid @border;
    border-radius: 6px; padding: 5px 8px; font-size: 12px;
}
QMenu {
    background: @bg; color: @text; border: 1px solid @border;
    border-radius: 10px; padding: 6px;
}
QMenu::item { padding: 7px 28px 7px 14px; border-radius: 6px; }
QMenu::item:selected { background: @accentSoft; color: @accentText; }
QMenu::separator { height: 1px; background: @border; margin: 5px 8px; }
QMessageBox, QDialog { background: @bg; }
QMessageBox QLabel { color: @text; font-size: 13px; }
QPushButton {
    background: @bg; color: @text; border: 1px solid @border;
    border-radius: 8px; padding: 7px 16px; font-size: 13px;
}
QPushButton:hover { background: @surface; }
QPushButton:pressed { background: @surfaceAlt; }
QPushButton[primary="true"] {
    background: @accent; color: #ffffff; border: 1px solid @accent; font-weight: 600;
}
QPushButton[primary="true"]:hover { background: @accentHover; }
QPushButton[ghost="true"] {
    background: transparent; border-color: transparent; color: @muted;
}
QPushButton[ghost="true"]:hover { background: @surface; color: @text; }
QCheckBox { color: @text; font-size: 13px; spacing: 8px; }
QLineEdit {
    background: @surface; color: @text; border: 1px solid transparent;
    border-radius: 8px; padding: 5px 8px; selection-background-color: @accentSoft;
}
QLineEdit:focus { background: @bg; border-color: @accent; }
QListWidget {
    background: @bg; border: 1px solid @border; border-radius: 10px;
    color: @text; font-size: 13px;
}
QListWidget::item { padding: 9px 12px; border-bottom: 1px solid @border; }
QListWidget::item:hover { background: @surface; }
QListWidget::item:selected { background: @surface; color: @text; border-left: 3px solid @accent; }
QTabWidget::pane { border: none; background: @bg; }
QTreeWidget { background: @surface; border: none; color: @text; }
QTreeWidget::item { padding: 5px 2px; }
QTreeWidget::item:hover { background: @surfaceAlt; }
QTreeWidget::item:selected { background: @accentSoft; color: @accentText; }
QComboBox {
    background: @surface; color: @text; border: 1px solid @border;
    border-radius: 8px; padding: 5px 10px; min-width: 140px;
}
QComboBox:hover { background: @surfaceAlt; }
QComboBox QAbstractItemView {
    background: @bg; color: @text; border: 1px solid @border;
    selection-background-color: @accentSoft; selection-color: @accentText;
}
QScrollBar:vertical { background: transparent; width: 10px; margin: 2px; }
QScrollBar::handle:vertical { background: @border; border-radius: 4px; min-height: 28px; }
QScrollBar::handle:vertical:hover { background: @muted; }
QScrollBar::add-line, QScrollBar::sub-line { height: 0; width: 0; }
QScrollBar::add-page, QScrollBar::sub-page { background: transparent; }

QToolBar#papernote_toolbar {
    background: @bg; border: none; padding: 7px 10px; spacing: 2px;
}
QToolBar#papernote_toolbar QToolButton {
    color: @text; background: transparent; border: 1px solid transparent;
    border-radius: 8px; padding: 5px 9px; font-size: 12.5px;
}
QToolBar#papernote_toolbar QToolButton:hover { background: @surface; }
QToolBar#papernote_toolbar QToolButton:pressed { background: @surfaceAlt; }
QToolBar#papernote_toolbar QToolButton:disabled { color: @muted; }
QToolBar#papernote_toolbar QToolButton:checked {
    background: @accentSoft; border-color: @accent; color: @accentText;
}
QToolBar#papernote_toolbar QToolButton::menu-indicator {
    image: none; width: 0px;
}
QToolBar#papernote_toolbar::separator {
    width: 1px; background: @separator; margin: 6px 8px;
}
QToolBar#papernote_toolbar QLineEdit {
    background: @surface; color: @text; border: 1px solid transparent;
    border-radius: 8px; padding: 4px 8px; font-size: 12.5px;
}
QToolBar#papernote_toolbar QLineEdit:focus { background: @bg; border-color: @accent; }

QToolBar#papernote_tabs_bar {
    background: @bg; border: none; border-bottom: 1px solid @border;
    padding: 0px 12px 0px 12px; spacing: 0px;
}
QTabBar#papernote_doc_tabs { background: transparent; }
QTabBar#papernote_doc_tabs::tab {
    background: transparent; color: @muted; padding: 7px 14px; margin-right: 2px;
    border: none; border-bottom: 2px solid transparent; max-width: 220px;
}
QTabBar#papernote_doc_tabs::tab:selected {
    color: @text; border-bottom: 2px solid @accent;
}
QTabBar#papernote_doc_tabs::tab:hover:!selected { color: @text; }
QTabBar#papernote_doc_tabs::close-button { margin-left: 6px; }

QDockWidget#papernote_sidebar { background: @surface; border-right: 1px solid @border; }
QTabWidget#papernote_sidebar_tabs::pane { border: none; background: @surface; }
QTabWidget#papernote_sidebar_tabs QTabBar::tab {
    background: transparent; color: @muted; padding: 7px 16px;
    border-bottom: 2px solid transparent;
}
QTabWidget#papernote_sidebar_tabs QTabBar::tab:selected {
    color: @text; border-bottom: 2px solid @accent;
}
QTabWidget#papernote_sidebar_tabs QTabBar::tab:hover:!selected { color: @text; }
QListWidget#papernote_thumbnails {
    background: @surface; border: none; color: @muted; font-size: 11.5px;
}
QListWidget#papernote_thumbnails::item { padding: 5px; border-radius: 8px; }
QListWidget#papernote_thumbnails::item:hover { background: @surfaceAlt; }
QListWidget#papernote_thumbnails::item:selected { background: @accentSoft; color: @accentText; }
)QSS");

    qss.replace("@bg", bg().name());
    qss.replace("@surface", surface().name());
    qss.replace("@surfaceAlt", surface_alt().name());
    qss.replace("@border", border().name());
    qss.replace("@separator", (is_dark() ? QColor(0x3e, 0x3d, 0x38).name() : QColor(0xda, 0xd5, 0xce).name()));
    qss.replace("@text", text().name());
    qss.replace("@muted", text_muted().name());
    qss.replace("@accentSoft", accent_soft().name());
    qss.replace("@accentText", accent_text().name());
    qss.replace("@accentHover", accent_hover().name());
    qss.replace("@accent", accent().name());
    return qss;
}

inline void apply(QApplication& app, ThemeMode mode) {
    requested_mode() = mode;
    dark_active() = (mode == ThemeMode::Dark) || (mode == ThemeMode::System && system_mode() == ThemeMode::Dark);

    QPalette palette = app.palette();
    palette.setColor(QPalette::Window, bg());
    palette.setColor(QPalette::WindowText, text());
    palette.setColor(QPalette::Base, is_dark() ? surface() : QColor(Qt::white));
    palette.setColor(QPalette::AlternateBase, surface_alt());
    palette.setColor(QPalette::Text, text());
    palette.setColor(QPalette::Button, is_dark() ? surface_alt() : QColor(Qt::white));
    palette.setColor(QPalette::ButtonText, text());
    palette.setColor(QPalette::Highlight, accent());
    palette.setColor(QPalette::HighlightedText, QColor(Qt::white));
    palette.setColor(QPalette::ToolTipBase, bg());
    palette.setColor(QPalette::ToolTipText, text());
    app.setPalette(palette);
    app.setStyleSheet(app_stylesheet());
}

// Small line icons, drawn with QPainter so they stay sharp and need no assets.
inline QIcon icon(const QString& name, const QColor& color, int size = 64) {
    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(color, size * 0.09, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    const qreal s = size;
    const qreal u = s / 32.0;  // design on a 32x32 grid

    auto line = [&](qreal x1, qreal y1, qreal x2, qreal y2) {
        painter.drawLine(QPointF(x1 * u, y1 * u), QPointF(x2 * u, y2 * u));
    };

    if (name == "open") {
        QPainterPath path;
        path.moveTo(5 * u, 25 * u);
        path.lineTo(5 * u, 9 * u);
        path.lineTo(12 * u, 9 * u);
        path.lineTo(14.5 * u, 12 * u);
        path.lineTo(25 * u, 12 * u);
        path.lineTo(25 * u, 25 * u);
        path.closeSubpath();
        painter.drawPath(path);
        line(5, 16, 25, 16);
    }
    else if (name == "recent") {
        painter.drawEllipse(QPointF(16 * u, 16 * u), 10 * u, 10 * u);
        line(16, 9, 16, 16);
        line(16, 16, 21, 19);
    }
    else if (name == "prev") {
        line(19, 9, 12, 16);
        line(12, 16, 19, 23);
    }
    else if (name == "next") {
        line(13, 9, 20, 16);
        line(20, 16, 13, 23);
    }
    else if (name == "zoom_in") {
        painter.drawEllipse(QPointF(14 * u, 14 * u), 7 * u, 7 * u);
        line(19.5, 19.5, 25, 25);
        line(11, 14, 17, 14);
        line(14, 11, 14, 17);
    }
    else if (name == "zoom_out") {
        painter.drawEllipse(QPointF(14 * u, 14 * u), 7 * u, 7 * u);
        line(19.5, 19.5, 25, 25);
        line(11, 14, 17, 14);
    }
    else if (name == "fit") {
        line(6, 16, 12, 16);
        line(20, 16, 26, 16);
        line(9, 13, 6, 16);
        line(6, 16, 9, 19);
        line(23, 13, 26, 16);
        line(26, 16, 23, 19);
        line(4, 10, 4, 22);
        line(28, 10, 28, 22);
    }
    else if (name == "highlight") {
        QPainterPath path;
        path.moveTo(9 * u, 22 * u);
        path.lineTo(11 * u, 13 * u);
        path.lineTo(20 * u, 6 * u);
        path.lineTo(26 * u, 12 * u);
        path.lineTo(17 * u, 19 * u);
        path.closeSubpath();
        painter.drawPath(path);
        line(7, 25, 25, 25);
    }
    else if (name == "bookmark") {
        QPainterPath path;
        path.moveTo(9 * u, 6 * u);
        path.lineTo(23 * u, 6 * u);
        path.lineTo(23 * u, 26 * u);
        path.lineTo(16 * u, 21 * u);
        path.lineTo(9 * u, 26 * u);
        path.closeSubpath();
        painter.drawPath(path);
    }
    else if (name == "export") {
        line(16, 6, 16, 19);
        line(11, 14, 16, 19);
        line(21, 14, 16, 19);
        QPainterPath path;
        path.moveTo(7 * u, 20 * u);
        path.lineTo(7 * u, 26 * u);
        path.lineTo(25 * u, 26 * u);
        path.lineTo(25 * u, 20 * u);
        painter.drawPath(path);
    }
    else if (name == "search") {
        painter.drawEllipse(QPointF(14 * u, 14 * u), 7 * u, 7 * u);
        line(19.5, 19.5, 25, 25);
    }
    else if (name == "help") {
        painter.drawEllipse(QPointF(16 * u, 16 * u), 10 * u, 10 * u);
        line(13, 12.5, 16, 10.5);
        line(16, 10.5, 19, 12.5);
        line(19, 12.5, 19, 15);
        line(19, 15, 16, 17);
        line(16, 17, 16, 18.5);
        painter.setBrush(color);
        painter.drawEllipse(QPointF(16 * u, 22 * u), 1.2 * u, 1.2 * u);
        painter.setBrush(Qt::NoBrush);
    }
    else if (name == "sidebar") {
        painter.drawRect(QRectF(5 * u, 8 * u, 22 * u, 17 * u));
        line(12, 8, 12, 25);
        line(15, 13, 24, 13);
        line(15, 17, 24, 17);
        line(15, 21, 24, 21);
    }
    else if (name == "page") {
        QPainterPath path;
        path.moveTo(9 * u, 6 * u);
        path.lineTo(20 * u, 6 * u);
        path.lineTo(25 * u, 11 * u);
        path.lineTo(25 * u, 26 * u);
        path.lineTo(9 * u, 26 * u);
        path.closeSubpath();
        painter.drawPath(path);
        line(20, 6, 20, 11);
        line(20, 11, 25, 11);
        line(12, 16, 22, 16);
        line(12, 20, 22, 20);
    }
    else if (name == "settings") {
        line(7, 11, 25, 11);
        line(7, 21, 25, 21);
        painter.setBrush(color);
        painter.drawEllipse(QPointF(13 * u, 11 * u), 2.2 * u, 2.2 * u);
        painter.drawEllipse(QPointF(20 * u, 21 * u), 2.2 * u, 2.2 * u);
        painter.setBrush(Qt::NoBrush);
    }
    else if (name == "moon") {
        QPainterPath path;
        path.addEllipse(QPointF(17 * u, 16 * u), 9 * u, 9 * u);
        QPainterPath cut;
        cut.addEllipse(QPointF(22 * u, 12 * u), 8 * u, 8 * u);
        painter.drawPath(path.subtracted(cut));
    }
    else if (name == "sun") {
        painter.drawEllipse(QPointF(16 * u, 16 * u), 6 * u, 6 * u);
        for (int i = 0; i < 8; i++) {
            qreal angle = i * M_PI / 4.0;
            line(16 + 9 * cos(angle), 16 + 9 * sin(angle),
                 16 + 12 * cos(angle), 16 + 12 * sin(angle));
        }
    }

    painter.end();
    return QIcon(pixmap);
}

}  // namespace papernote
