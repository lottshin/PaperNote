#pragma once

// PaperNote visual theme — warm minimal (Notion / Craft style):
// white canvas, warm neutral greys, whisper-thin borders, one blue accent.

#include <QApplication>
#include <QColor>
#include <QIcon>
#include <QPainter>
#include <QPainterPath>
#include <QPalette>
#include <QPixmap>
#include <QString>

namespace papernote {

inline const QColor kBg(0xff, 0xff, 0xff);
inline const QColor kSurface(0xf7, 0xf6, 0xf4);
inline const QColor kSurfaceAlt(0xf1, 0xef, 0xec);
inline const QColor kBorder(0xe7, 0xe3, 0xdd);
inline const QColor kText(0x1f, 0x1e, 0x1c);
inline const QColor kTextMuted(0x6f, 0x6a, 0x64);
inline const QColor kAccent(0x00, 0x75, 0xde);
inline const QColor kAccentHover(0x00, 0x68, 0xc4);
inline const QColor kAccentSoft(0xe9, 0xf4, 0xfd);
inline const QColor kAccentText(0x0b, 0x5f, 0xa5);

inline QString app_stylesheet() {
    return QStringLiteral(R"QSS(
QToolTip {
    background: #ffffff; color: #1f1e1c; border: 1px solid #e7e3dd;
    border-radius: 6px; padding: 5px 8px; font-size: 12px;
}
QMenu {
    background: #ffffff; color: #1f1e1c; border: 1px solid #e7e3dd;
    border-radius: 10px; padding: 6px;
}
QMenu::item { padding: 7px 28px 7px 14px; border-radius: 6px; }
QMenu::item:selected { background: #e9f4fd; color: #0b5fa5; }
QMenu::separator { height: 1px; background: #eeeae4; margin: 5px 8px; }
QMessageBox, QDialog { background: #ffffff; }
QMessageBox QLabel { color: #1f1e1c; font-size: 13px; }
QPushButton {
    background: #ffffff; color: #1f1e1c; border: 1px solid #ddd8d1;
    border-radius: 8px; padding: 7px 16px; font-size: 13px;
}
QPushButton:hover { background: #f7f6f4; }
QPushButton:pressed { background: #f1efec; }
QPushButton[primary="true"] {
    background: #0075de; color: #ffffff; border: 1px solid #0075de; font-weight: 600;
}
QPushButton[primary="true"]:hover { background: #0068c4; }
QPushButton[ghost="true"] {
    background: transparent; border-color: transparent; color: #6f6a64;
}
QPushButton[ghost="true"]:hover { background: #f5f3f0; color: #1f1e1c; }
QCheckBox { color: #1f1e1c; font-size: 13px; spacing: 8px; }
QLineEdit {
    background: #f7f6f4; color: #1f1e1c; border: 1px solid transparent;
    border-radius: 8px; padding: 5px 8px; selection-background-color: #cfe8fb;
}
QLineEdit:focus { background: #ffffff; border-color: #0075de; }
QListWidget {
    background: #ffffff; border: 1px solid #e7e3dd; border-radius: 10px;
    color: #1f1e1c; font-size: 13px;
}
QListWidget::item { padding: 9px 12px; border-bottom: 1px solid #f1efec; }
QListWidget::item:hover { background: #f7f6f4; }
QListWidget::item:selected { background: #f5f3f0; color: #1f1e1c; border-left: 3px solid #0075de; }
QTabWidget::pane { border: none; background: #ffffff; }
QTreeWidget { background: #ffffff; border: none; color: #1f1e1c; }
QTreeWidget::item { padding: 5px 2px; }
QTreeWidget::item:selected { background: #e9f4fd; color: #0b5fa5; }
QScrollBar:vertical { background: transparent; width: 10px; margin: 2px; }
QScrollBar::handle:vertical { background: #dcd7d0; border-radius: 4px; min-height: 28px; }
QScrollBar::handle:vertical:hover { background: #c8c2b9; }
QScrollBar::add-line, QScrollBar::sub-line { height: 0; width: 0; }
QScrollBar::add-page, QScrollBar::sub-page { background: transparent; }
)QSS");
}

inline void apply_app_theme(QApplication& app) {
    QPalette palette = app.palette();
    palette.setColor(QPalette::Window, kBg);
    palette.setColor(QPalette::WindowText, kText);
    palette.setColor(QPalette::Base, QColor(Qt::white));
    palette.setColor(QPalette::AlternateBase, kSurface);
    palette.setColor(QPalette::Text, kText);
    palette.setColor(QPalette::Button, QColor(Qt::white));
    palette.setColor(QPalette::ButtonText, kText);
    palette.setColor(QPalette::Highlight, kAccent);
    palette.setColor(QPalette::HighlightedText, QColor(Qt::white));
    palette.setColor(QPalette::ToolTipBase, QColor(Qt::white));
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

    painter.end();
    return QIcon(pixmap);
}

}  // namespace papernote
