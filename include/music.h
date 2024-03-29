#pragma once

#include <Windows.h>
#include <fmt/core.h>
#include <map>
#include <stdint.h>
#include <string>

struct Note {
    byte timbre;  // 音色
    byte volume;  // 音量
    byte scale;   // 音阶
    byte cmd;     // 命令
    byte channel; // 通道
    int sleep;    // 长度
};

struct Notes {
    size_t num_note;
    Note *notes;
};

class music {
  private:
    struct {
        const char *filename = nullptr;
        char *raw = nullptr;
        int offset = 0;
        int line = 0;
    } file;
    int default_segment, default_offset;
    HMIDIOUT handle;
    Note default_Note;
    bool play_note (Notes *);
    Notes *get_note();
    char getunblank();
    char getch();
    void putch();
    template <int level>
    void print_content();

  public:
    music (const char *);
    ~music();
    void print();
    void play();
    template <int level, typename T>
    void interupt (const char *file, int line, T whicherr);
};

enum { error = 0, warning = 1, info = 2 };

#define ERR(description) interupt<error> (__FILE__, __LINE__, description)
#define WAR(description) interupt<warning> (__FILE__, __LINE__, description)
#define INF(description) interupt<info> (__FILE__, __LINE__, description)

static std::map<int, std::string> level_str_map {
    {  error,   "error"},
    {warning, "warning"},
    {   info,    "info"}
};

static const char *level_color_str[] = {"\033[91m", "\033[95m", "\033[96m"};

template <int level, typename T>
void music::interupt (const char *file, int line, T whicherr) {
    fmt::print ("{}:{}: {}{}:\033[0m {}\n", file, line, level_color_str[level],
                level_str_map[level], whicherr);
    if (line)
        print_content<level>();
    if (! level)
        exit (EXIT_FAILURE);
}

template <int level>
void music::print_content() {
    char *current_pos = file.raw + file.offset - 1;
    char *begin = current_pos;
    while (*begin != '\n')
        begin--;
    begin++; // 本行第一个字符

    uint64_t linelen = 0;
    while (begin[linelen] != '\n') // 行长度
        linelen++;
    std::string out {begin, linelen}; // 输出的字符串
    int lastcomma = current_pos - begin - 1,
        nextcomma = current_pos - begin + 1; // 出错位置前后逗号

    while (out[nextcomma] != ',' && nextcomma < linelen)
        nextcomma++;
    out.insert (nextcomma + 1, "\033[0m"); // 恢复控制字符插入，包含后面的逗号
    while (out[lastcomma] != ',' && lastcomma > 0)
        lastcomma--;
    out.insert (lastcomma + 1,
                level_color_str[level]); // 彩色控制字符插入，不包含前面的逗号

    fmt::print ("{: >4} | {}\n     | {}{}^\033[0m\n", file.line, out,
                std::string (current_pos - begin, ' '), level_color_str[level]);
}
