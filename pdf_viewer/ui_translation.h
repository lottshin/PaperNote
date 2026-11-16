#pragma once

// Chinese (zh-CN) UI strings for the PaperNote fork.
//
// Sioyek has no translation layer of its own: menu titles and command labels are
// compiled-in English. Rather than rewriting every string in the app, this header
// provides a compact lookup used by the menu bar (the part of the UI a new user
// actually looks at) and the Chinese quick-start dialog.
//
// Unknown strings fall back to the original English text, so the app keeps
// working even if a new upstream command is added.

#include <QHash>
#include <QString>
#include <string>
#include <unordered_map>

inline QString papernote_tr_menu(const QString& english) {
    static const QHash<QString, QString> map = {
        {"File", "文件"},
        {"Window", "窗口"},
        {"View", "视图"},
        {"Navigate", "导航"},
        {"Annotations", "注释"},
        {"Highlights", "高亮"},
        {"Bookmarks", "书签"},
        {"Marks", "标记"},
        {"Portals", "门户"},
        {"Overview", "预览"},
        {"Drawings", "手绘"},
        {"Tools", "工具"},
        {"Preferences", "偏好设置"},
        {"Help", "帮助"},
        {"Scratchpad", "草稿板"},
        {"Ruler", "标尺"},
    };

    auto it = map.constFind(english);
    return it == map.constEnd() ? english : it.value();
}

inline QString papernote_tr_command(const std::string& command, const QString& fallback) {
    static const std::unordered_map<std::string, QString> map = {
        // File / 文件
        {"home", "最近打开…"},
        {"preferences_dialog", "图形化设置…"},
        {"toggle_sidebar", "显示/隐藏侧栏"},
        {"copy", "复制"},
        {"export_highlights", "导出笔记"},
        {"help", "快速上手"},
        {"edit_selected_annotation", "编辑批注…"},
        {"move_selected_bookmark", "移动书签"},
        {"open_document", "打开文档…"},
        {"open_prev_doc", "打开上一个文档"},
        {"open_document_embedded", "打开嵌入的文档…"},
        {"open_document_embedded_from_current_path", "从当前目录打开嵌入文档…"},
        {"open_last_document", "打开上次阅读的文档"},
        {"goto_tab", "切换到标签页…"},
        {"download_clipboard_url", "下载剪贴板里的链接…"},
        {"rename", "重命名文档…"},

        // Window / 窗口
        {"new_window", "新建窗口"},
        {"close_window", "关闭窗口"},
        {"goto_window", "切换到窗口…"},
        {"maximize", "最大化"},
        {"toggle_fullscreen", "全屏切换"},
        {"toggle_two_page_mode", "双页模式"},
        {"toggle_window_configuration", "切换窗口布局"},

        // View / 视图
        {"zoom_in", "放大"},
        {"zoom_out", "缩小"},
        {"fit_to_page_width", "适应页宽"},
        {"fit_to_page_width_smart", "智能适应页宽"},
        {"fit_to_page_height", "适应页高"},
        {"fit_to_page_height_smart", "智能适应页高"},
        {"toggle_dark_mode", "深色模式"},
        {"toggle_custom_color", "自定义配色"},
        {"toggle_statusbar", "显示/隐藏状态栏"},
        {"toggle_scrollbar", "显示/隐藏滚动条"},
        {"toggle_horizontal_scroll_lock", "锁定水平滚动"},
        {"toggle_presentation_mode", "演示模式"},
        {"toggle_visual_scroll", "视觉滚动"},
        {"toggle_pdf_annotations", "显示 PDF 注释"},
        {"toggleconfig_preserve_image_colors_in_dark_mode", "深色模式保留图片原色"},

        // Navigate / 导航
        {"goto_beginning", "跳到开头"},
        {"goto_end", "跳到结尾"},
        {"goto_toc", "目录…"},
        {"goto_page_with_page_number", "跳到页码…"},
        {"goto_page_with_label", "跳到标签页…"},
        {"next_page", "下一页"},
        {"previous_page", "上一页"},
        {"screen_down", "向下翻屏"},
        {"screen_up", "向上翻屏"},
        {"next_state", "前进"},
        {"prev_state", "后退"},
        {"goto_definition", "跳转到定义"},
        {"overview_definition", "预览定义"},
        {"portal_to_definition", "从定义处跳转"},
        {"goto_highlight", "跳转到高亮…"},
        {"goto_highlight_g", "全局跳转到高亮…"},
        {"goto_bookmark", "跳转到书签…"},
        {"goto_bookmark_g", "全局跳转到书签…"},
        {"goto_mark", "跳转到标记…"},
        {"set_mark", "设置标记…"},
        {"goto_portal_list", "门户列表…"},
        {"portal", "创建门户"},
        {"next_item", "下一个条目"},
        {"previous_item", "上一个条目"},
        {"move_visual_mark_up", "向上移动"},
        {"move_visual_mark_down", "向下移动"},
        {"search", "搜索…"},
        {"regex_search", "正则搜索…"},
        {"goto_tab", "切换到标签页…"},

        // Annotations / 注释
        {"add_highlight", "添加高亮"},
        {"add_highlight_with_current_type", "用当前类型高亮"},
        {"add_bookmark", "添加书签"},
        {"add_freetext_bookmark", "添加文字书签…"},
        {"add_marked_bookmark", "添加带标记的书签"},
        {"delete_highlight", "删除高亮"},
        {"delete_visible_annotation", "删除可见注释"},
        {"edit_visible_annotation", "编辑可见注释…"},
        {"add_annot_to_selected_highlight", "给高亮加批注…"},
        {"delete_portal", "删除门户"},
        {"delete_freehand_drawings", "删除手绘"},
        {"create_visible_portal", "创建可见门户"},
        {"embed_annotations", "把注释嵌入 PDF…"},
        {"import_annotations", "从文件导入注释…"},
        {"download_overview_paper", "下载预览中的论文…"},

        // Overview / 预览
        {"move_left_in_overview", "预览中左移"},
        {"move_right_in_overview", "预览中右移"},
        {"next_overview", "下一个预览"},
        {"previous_overview", "上一个预览"},
        {"zoom_in_overview", "预览放大"},
        {"zoom_out_overview", "预览缩小"},
        {"overview_next_item", "预览下一项"},
        {"overview_prev_item", "预览上一项"},
        {"close_overview", "关闭预览"},

        // Drawings / 手绘
        {"toggle_freehand_drawing_mode", "手绘模式"},
        {"set_freehand_type", "选择手绘类型…"},
        {"set_freehand_thickness", "设置手绘粗细…"},
        {"toggle_drawing_mask", "绘图遮罩"},

        // Tools / 工具
        {"command", "命令列表…"},
        {"command_palette", "命令面板…"},
        {"toggle_reading", "朗读"},
        {"setconfig_tts_rate", "设置朗读速度…"},
        {"toggle_synctex", "SyncTeX 跳转"},
        {"toggle_scratchpad_mode", "草稿板模式"},
        {"save_scratchpad", "保存草稿板…"},
        {"load_scratchpad", "加载草稿板…"},
        {"copy_screenshot_to_scratchpad", "截图到草稿板"},
        {"clear_scratchpad", "清空草稿板"},

        // Preferences / 偏好设置
        {"prefs_user", "用户偏好设置…"},
        {"keys_user", "用户键位设置…"},
        {"prefs_user_all", "全部用户偏好设置…"},
        {"keys_user_all", "全部用户键位设置…"},
        {"keys", "默认键位说明…"},
        {"prefs", "默认偏好说明…"},
    };

    auto it = map.find(command);
    return it == map.end() ? fallback : it->second;
}

// Chinese quick-start shown on first launch and from Help > 快速上手 (F1).
inline QString papernote_quickstart_html() {
    return QString(
        "<h3>PaperNote 快速上手</h3>"
        "<p>PaperNote 同时支持<b>鼠标</b>和<b>键盘</b>：顶部工具栏可以直接点，键盘快捷键更高效。"
        "下面是最常用的快捷键。</p>"
        "<table cellpadding='4'>"
        "<tr><td><b>打开文档</b></td><td><code>o</code></td>"
        "    <td><b>搜索</b></td><td><code>/</code> 或 <code>Ctrl+F</code>，<code>n</code>/<code>N</code> 跳转</td></tr>"
        "<tr><td><b>目录</b></td><td><code>t</code></td>"
        "    <td><b>翻页</b></td><td><code>空格</code>/<code>Shift+空格</code>，<code>j</code>/<code>k</code> 连续滚动</td></tr>"
        "<tr><td><b>跳页</b></td><td><code>Ctrl+PageDown</code></td>"
        "    <td><b>全屏</b></td><td><code>F11</code></td></tr>"
        "<tr><td><b>高亮</b></td><td>先选中文字，再按 <code>h</code> + 字母（a/b/c 是三种颜色）</td>"
        "    <td><b>书签</b></td><td><code>b</code></td></tr>"
        "<tr><td><b>跳到高亮</b></td><td><code>g h</code></td>"
        "    <td><b>跳到书签</b></td><td><code>g b</code></td></tr>"
        "<tr><td><b>导出笔记</b></td><td><code>Ctrl+Shift+E</code>（生成同目录 .notes.md）</td>"
        "    <td><b>命令面板</b></td><td><code>:</code>（可搜索所有命令）</td></tr>"
        "<tr><td><b>缩放</b></td><td><code>+</code>/<code>-</code>，<code>=</code> 适应页宽</td>"
        "    <td><b>本帮助</b></td><td><code>F2</code></td></tr>"
        "</table>"
        "<p>菜单栏里也有同样的功能（已汉化）。高亮和书签会自动保存，"
        "按 <code>Ctrl+Shift+E</code> 就能把它们导出成 Markdown 笔记。</p>"
        "<p style='color:#888'>PaperNote 1.0.0 · 基于开源项目 Sioyek（GPLv3）二次开发</p>"
    );
}
