#pragma once

// PaperNote visual theme.
//
// One place for the palette, the application-wide stylesheet and the small set
// of programmatically drawn toolbar icons. Keeping the icons vector-drawn (not
// bitmap assets) makes them crisp at any DPI and keeps the repo asset-free.

#include <QApplication>
#include <QColor>
#include <QIcon>
#include <QPainter>
#include <QPainterPath>
#include <QPalette>
#include <QPixmap>
#include <QString>

namespace papernote {

inline const QColor kBg(0x14, 0x13, 0x1a);
inline const QColor kSurface(0x1e, 0x1d, 0x26);
inline const QColor kSurfaceAlt(0x26, 0x25, 0x30);
inline const QColor kBorder(0x36, 0x34, 0x42);
inline const QColor kText(0xf0, 0xef, 0xf6);
inline const QColor kTextMuted(0xa2, 0x9f, 0xb3);
inline const QColor kAccent(0x8b, 0x6c, 0xff);
inline const QColor kAccentHover(0x9d, 0x82, 0xff);

inline QString app_stylesheet() {
    return QStringLiteral(R"QSS(
QToolTip {
    background: #2a2834; color: #ecebf4; border: 1px solid #46435a;
    border-radius: 6px; padding: 5px 8px; font-size: 12px;
}
QMenu {
    background: #201f28; color: #e9e8f1; border: 1px solid #3a3847;
    border-radius: 8px; padding: 6px;
}
QMenu::item { padding: 6px 26px 6px 14px; border-radius: 6px; }
QMenu::item:selected { background: #6d57a8; }
QMenu::separator { height: 1px; background: #34323f; margin: 5px 8px; }
QMessageBox, QDialog { background: #1c1b22; }
QMessageBox QLabel { color: #ecebf4; font-size: 13px; }
QPushButton {
    background: #2f2d39; color: #ecebf4; border: 1px solid #46435a;
    border-radius: 7px; padding: 7px 16px; font-size: 13px;
}
QPushButton:hover { background: #3b3849; }
QPushButton:pressed { background: #2a2834; }
QPushButton[primary="true"] {
    background: #8b6cff; color: #ffffff; border: 1px solid #9d82ff; font-weight: 600;
}
QPushButton[primary="true"]:hover { background: #9d82ff; }
QPushButton[ghost="true"] {
    background: transparent; border-color: transparent; color: #b7b4c7;
}
QPushButton[ghost="true"]:hover { background: #2c2a36; color: #ffffff; }
QCheckBox { color: #e9e8f1; font-size: 13px; spacing: 8px; }
QLineEdit {
    background: #17161d; color: #ecebf4; border: 1px solid #3a3847;
    border-radius: 7px; padding: 5px 8px; selection-background-color: #6d57a8;
}
QListWidget {
    background: #201f28; border: 1px solid #3a3847; border-radius: 9px;
    color: #e9e8f1; font-size: 13px;
}
QListWidget::item { padding: 9px 12px; border-bottom: 1px solid #2c2a36; }
QListWidget::item:selected { background: #55467e; }
QTabWidget::pane { border: none; background: #1a1920; }
QTreeWidget { background: #1a1920; border: none; color: #dcd9e8; }
QTreeWidget::item { padding: 5px 2px; }
QTreeWidget::item:selected { background: #3a3350; }
QScrollBar:vertical { background: transparent; width: 10px; margin: 2px; }
QScrollBar::handle:vertical { background: #3f3c4e; border-radius: 4px; min-height: 28px; }
QScrollBar::handle:vertical:hover { background: #55506a; }
QScrollBar::add-line, QScrollBar::sub-line { height: 0; width: 0; }
QScrollBar::add-page, QScrollBar::sub-page { background: transparent; }
)QSS");
}

inline void apply_app_theme(QApplication& app) {
    QPalette palette = app.palette();
    palette.setColor(QPalette::Window, kBg);
    palette.setColor(QPalette::WindowText, kText);
    palette.setColor(QPalette::Base, kSurface);
    palette.setColor(QPalette::AlternateBase, kSurfaceAlt);
    palette.setColor(QPalette::Text, kText);
    palette.setColor(QPalette::Button, kSurfaceAlt);
    palette.setColor(QPalette::ButtonText, kText);
    palette.setColor(QPalette::Highlight, kAccent);
    palette.setColor(QPalette::HighlightedText, QColor(Qt::white));
    palette.setColor(QPalette::ToolTipBase, kSurfaceAlt);
    palette.setColor(QPalette::ToolTipText, kText);
    app.setPalette(palette);

    app.setStyleSheet(app_stylesheet());
}

// Small line icons, drawn with QPainter so they stay sharp and need no assets.
inline QIcon icon(const QString& name, const QColor& color = kText, int size = 64) {
    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(color, size * 0.10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
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

    painter.end();
    return QIcon(pixmap);
}

}  // namespace papernote
