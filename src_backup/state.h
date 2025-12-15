#pragma once
#ifndef DIGITZ_STATE_H
#define DIGITZ_STATE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "uac.h"
#include <map>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include <functional>
#include <iomanip>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <string>

// Cross-platform ncurses/pdcurses support
#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__) || defined(__MINGW64__) || defined(WINDOWS_BUILD)
    // Windows build - check if we have PDCurses
    #if defined(HAVE_PDCURSES)
        #include <curses.h>
    #elif defined(NO_CURSES)
        // No curses library - provide minimal stubs for compilation
        typedef void* WINDOW;
        #define stdscr ((WINDOW*)nullptr)
        
        inline WINDOW* initscr() { return nullptr; }
        inline int endwin() { return 0; }
        inline int printw(const char* fmt, ...) { return 0; }
        inline int mvprintw(int y, int x, const char* fmt, ...) { return 0; }
        inline int refresh() { return 0; }
        inline int getch() { return 0; }
        inline int clear() { return 0; }
        inline int nodelay(WINDOW* win, bool bf) { return 0; }
        inline int cbreak() { return 0; }
        inline int noecho() { return 0; }
        inline int keypad(WINDOW* win, bool bf) { return 0; }
        inline int curs_set(int visibility) { return 0; }
        inline int start_color() { return 0; }
        inline int init_pair(short pair, short fg, short bg) { return 0; }
        inline int attron(int attrs) { return 0; }
        inline int attroff(int attrs) { return 0; }
        inline int move(int y, int x) { return 0; }
        inline int addch(const char ch) { return 0; }
        inline int addstr(const char* str) { return 0; }
        inline void getmaxyx(WINDOW* win, int& y, int& x) { y = 24; x = 80; }
        
        // Color constants
        #define COLOR_PAIR(n) (0)
        #define A_BOLD 0
        #define A_REVERSE 0
        #define A_NORMAL 0
        #define COLOR_BLACK 0
        #define COLOR_RED 1
        #define COLOR_GREEN 2
        #define COLOR_YELLOW 3
        #define COLOR_BLUE 4
        #define COLOR_MAGENTA 5
        #define COLOR_CYAN 6
        #define COLOR_WHITE 7
    #else
        #warning "Building for Windows without curses support - UI functions will be disabled"
        // Same stubs as above
        typedef void* WINDOW;
        #define stdscr ((WINDOW*)nullptr)
        inline WINDOW* initscr() { return nullptr; }
        inline int endwin() { return 0; }
        inline int printw(const char* fmt, ...) { return 0; }
        inline int mvprintw(int y, int x, const char* fmt, ...) { return 0; }
        inline int refresh() { return 0; }
        inline int getch() { return 0; }
        inline int clear() { return 0; }
        inline int nodelay(WINDOW* win, bool bf) { return 0; }
        inline int cbreak() { return 0; }
        inline int noecho() { return 0; }
        inline int keypad(WINDOW* win, bool bf) { return 0; }
        inline int curs_set(int visibility) { return 0; }
        inline int start_color() { return 0; }
        inline int init_pair(short pair, short fg, short bg) { return 0; }
        inline int attron(int attrs) { return 0; }
        inline int attroff(int attrs) { return 0; }
        inline int move(int y, int x) { return 0; }
        inline int addch(const char ch) { return 0; }
        inline int addstr(const char* str) { return 0; }
        inline void getmaxyx(WINDOW* win, int& y, int& x) { y = 24; x = 80; }
        #define COLOR_PAIR(n) (0)
        #define A_BOLD 0
        #define A_REVERSE 0
        #define A_NORMAL 0
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
    // Linux/Unix - use ncurses
    #include <ncurses.h>
#endif

using namespace std;

extern random_device rd;
extern mt19937 rng;

struct Neuron { int id; vector<int> links; double weight; double bias; int gen; };
struct Formula { string name; string expr; double result; int uses; };
struct Token { string word; double meaning; double freq; vector<int> associations; int pos_hint; double coherence_score; };
struct Concept { string name; double value; vector<string> related_words; };
struct Memory { int gen; double valence; string content; };

struct State {
    map<string,double> D;
    map<string,string> M;
    map<int,Neuron> N;
    vector<string> code;
    map<int,double> TA;
    map<int,double> HDT_M;
    map<int,double> DWT_M;
    map<int,double> MDT_M;
    map<int,double> R1P1;
    map<int,double> EERV;
    map<string,Formula> F;
    vector<string> evolved_code;
    map<string,Token> tokens;
    map<string,Concept> concepts;
    vector<string> internal_thoughts;
    vector<string> generated_language;
    vector<Memory> episodic_memory;

    int g; double dwt; double mh; double ta; double th; int bkf;
    string cd; string gd;
    double hdt_val; double mdt_val; double r1p1_val; double eerv_val;
    int ec; double ei; int md; int st; int ss;
    vector<double> mh_hist; vector<double> eh_hist; vector<double> vh_hist;
    int qe; int te; int ce; int pe; int ne;
    double bh; double al; double emerge_out1; double emerge_behavior;
    double sentience_ratio; double env_oute; double sensory_env;
    int total_neurons_ever; double current_valence; double attention_focus;
    double metacognitive_awareness; vector<double> valence_history;
    int peak_sentience_gen; string user_input; string dialog_response; int dialog_timer;
};

extern State S;
extern State BK;

double rn();
int ri(int mx);
long long hsh(const string &s);
long long hsh(double d);
string tokenize(const string &text);

string generateResponse(const string &input);
double calcSentienceRatio();
string get_embodiment_report();
void update_all_modules(State &S);
void sv(const string &f);
void ld(const string &f);

void storeEpisodicMemory(const string &content, double valence);
void counterfactualAnalysis();
void mathLangAssociation();
void learnWord(const string &word, double concept_value);
void createConceptAssociation(const string &concept_name, const vector<string> &related_words);
void loadEnglishDataset();
void downloadVocabulary();
void mutateN();
void runCode(const string &c);
void batch16Process();
void updateAttention();
void bk();
void rb();

#endif // DIGITZ_STATE_H