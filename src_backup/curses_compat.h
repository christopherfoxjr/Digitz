// curses_compat.h - Cross-platform ncurses/pdcurses compatibility
#ifndef CURSES_COMPAT_H
#define CURSES_COMPAT_H

// Detect platform and include appropriate curses library
#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__) || defined(__MINGW64__) || defined(WINDOWS_BUILD)
    // Windows: use PDCurses
    #ifdef HAVE_PDCURSES
        #include <curses.h>  // PDCurses typically installs as curses.h
    #else
        // Define minimal stubs if PDCurses is not available
        #warning "PDCurses not found - using stub implementations"
        
        // Minimal curses stubs for compilation
        typedef struct _win_st WINDOW;
        
        #define WINDOW void
        #define stdscr ((WINDOW*)0)
        
        inline WINDOW* initscr() { return nullptr; }
        inline int endwin() { return 0; }
        inline int printw(const char*, ...) { return 0; }
        inline int mvprintw(int, int, const char*, ...) { return 0; }
        inline int refresh() { return 0; }
        inline int getch() { return 0; }
        inline int clear() { return 0; }
        inline int nodelay(WINDOW*, bool) { return 0; }
        inline int cbreak() { return 0; }
        inline int noecho() { return 0; }
        inline int keypad(WINDOW*, bool) { return 0; }
        inline int curs_set(int) { return 0; }
        inline int start_color() { return 0; }
        inline int init_pair(short, short, short) { return 0; }
        inline int attron(int) { return 0; }
        inline int attroff(int) { return 0; }
        inline int move(int, int) { return 0; }
        inline int addch(const char) { return 0; }
        inline int addstr(const char*) { return 0; }
        inline void getmaxyx(WINDOW*, int&, int&) { }
        
        #define COLOR_PAIR(n) (0)
        #define A_BOLD 0
        #define A_REVERSE 0
        #define COLOR_BLACK 0
        #define COLOR_RED 1
        #define COLOR_GREEN 2
        #define COLOR_YELLOW 3
        #define COLOR_BLUE 4
        #define COLOR_MAGENTA 5
        #define COLOR_CYAN 6
        #define COLOR_WHITE 7
    #endif
#else
    // Linux/Unix: use ncurses
    #include <ncurses.h>
#endif

#endif // CURSES_COMPAT_H