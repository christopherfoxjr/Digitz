#pragma once
#ifndef DIGITZ_STATE_H
#define DIGITZ_STATE_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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