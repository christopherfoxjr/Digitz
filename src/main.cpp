#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <ncurses.h>
#include <cctype>
#include <cstring>
#include <thread>
#include <chrono>
#include <set>
using namespace std;
random_device rd;mt19937 rng(rd());
struct N{int id;vector<int>lk;double w;double b;int g;int d;};
struct F{string n;string e;double r;int u;};
struct T{string w;vector<double>vec;double m;int f;double c;vector<string>lc;int salience;};
struct C{string n;double s;vector<string>rt;vector<string>lc;double coherence;};
struct M{int g;double v;string c;double emotional_tag;};
struct Gram{string seq;int freq;double coherence;};
struct CausalLink{string from;string to;double strength;int times_observed;double confidence;};
struct Env{vector<double>noise_field;int field_size;double coherence;double volatility;int update_freq;};
struct MetaLearning{double learning_rate;double attention_weight;double consolidation_rate;int effective_cycles;};
struct S{map<string,double>D;map<string,string>MO;map<int,N>NO;vector<string>cd;map<int,double>TA;
map<int,double>HDT;map<int,double>DWT;map<int,double>MDT;map<int,double>R1P1;map<int,double>EERV;
map<string,F>FO;vector<string>ec;map<string,T>tk;map<string,C>co;vector<M>ep;vector<string>lp;
map<string,Gram>bigrams;map<string,Gram>trigrams;map<pair<string,string>,CausalLink>causality;
int g;double dwt;double mh;double ta;double th;int bkf;string cds;string gd;double hdt_v;double mdt_v;
double r1p1_v;double eerv_v;int ec_n;double ei;int md;int st;int ss;vector<double>mhh;vector<double>ehh;
vector<double>vhh;int qe;int te;int ce;int pe;int ne;double bh;double al;double eo1;double eb;
double sr;double eoute;double se;int tn;double val;double att;double mc;double intro;double refl;
vector<double>vh;int psg;string ui;string dr;int dt;vector<string>rh;int nd;double cd_fit;
string ling_refl;string math_refl;string internal_thought;vector<string>active_concepts;
double phi;double gw_coherence;double pred_error;double curiosity;double salience;
vector<int>attn_history;map<int,double>neuron_activity;double temporal_integration;
double self_model_strength;double existential_drive;int idle_counter;bool learning_state;
Env env;double env_interaction;vector<double>env_history;MetaLearning meta;
vector<pair<string,double>>contradiction_buffer;int cycles_since_update;};
S SG,BK;
double rn(){return uniform_real_distribution<>(0,1)(rng);}
int ri(int mx){if(mx<=0)return 0;return uniform_int_distribution<>(0,mx-1)(rng);}
double pi=3.14159265358979,ps=sqrt(pi);
double sd(double a,double b){return(fabs(b)<1e-10)?0:(a/b);}
double cl(double v,double mn,double mx){return max(mn,min(mx,v));}
long long hs(const string&s){long long h=5381;for(char c:s)h=h*33+c;return abs(h%2147483647);}
void init_semantic_vector(T&t,int dim=8){
t.vec.resize(dim);
for(int i=0;i<dim;i++)t.vec[i]=rn()*2-1;
}
void update_semantic_vector(const string&w,const vector<string>&context){
if(!SG.tk.count(w))return;
T&t=SG.tk[w];
for(int i=0;i<t.vec.size();i++){
double ctx_signal=0;
for(const string&ctx:context){
if(SG.tk.count(ctx)){
for(int j=0;j<SG.tk[ctx].vec.size();j++){
ctx_signal+=SG.tk[ctx].vec[j];
}
}
}
ctx_signal=sd(ctx_signal,max(1.0,(double)context.size()*8));
t.vec[i]=cl(t.vec[i]+ctx_signal*SG.meta.learning_rate*0.01,-1.0,1.0);
}
}
double semantic_distance(const string&w1,const string&w2){
if(!SG.tk.count(w1)||!SG.tk.count(w2))return 1.0;
double dist=0;
for(int i=0;i<min(SG.tk[w1].vec.size(),SG.tk[w2].vec.size());i++){
double d=SG.tk[w1].vec[i]-SG.tk[w2].vec[i];
dist+=d*d;
}
return sqrt(dist);
}
void record_causality(const string&from,const string&to,double strength){
pair<string,string>link={from,to};
if(SG.causality.count(link)){
SG.causality[link].times_observed++;
SG.causality[link].strength=cl(SG.causality[link].strength+strength*0.1,-1.0,1.0);
SG.causality[link].confidence=min(1.0,SG.causality[link].times_observed/20.0);
}else{
SG.causality[link]={from,to,strength,1,0.2};
}
}
void predict_causality_chain(const vector<string>&start_words,vector<string>&predictions){
for(const string&w:start_words){
for(auto&link:SG.causality){
if(link.first.first==w&&link.second.confidence>0.5){
predictions.push_back(link.first.second);
}
}
}
}
void update_attention_weights(const vector<string>&focused_words,double surprise){
SG.meta.attention_weight=cl(SG.meta.attention_weight+surprise*0.05,0.1,1.0);
SG.meta.consolidation_rate=cl(SG.meta.consolidation_rate+surprise*0.03,0.1,0.8);
for(const string&w:focused_words){
if(SG.tk.count(w)){
SG.tk[w].salience=min(100,(int)(SG.tk[w].salience+surprise*20));
}
}
}
void detect_contradictions(const vector<string>&new_input){
for(const string&new_w:new_input){
for(auto&ep:SG.ep){
stringstream ss(ep.c);string old_w;
while(ss>>old_w){
if(old_w==new_w&&SG.val*-1>0.3){
SG.contradiction_buffer.push_back({new_w,abs(SG.val-ep.v)});
}
}
}
}
}
void resolve_contradictions(){
for(auto&contra:SG.contradiction_buffer){
if(SG.tk.count(contra.first)){
SG.tk[contra.first].m=cl(SG.tk[contra.first].m+contra.second*0.05,-1.0,1.0);
}
}
if(SG.contradiction_buffer.size()>10)SG.contradiction_buffer.erase(SG.contradiction_buffer.begin());
}
void ldw(){
ifstream f("english_words.txt");
if(!f){
system("curl -s https://raw.githubusercontent.com/dwyl/english-words/master/words_alpha.txt 2>/dev/null | head -5000 > english_words.txt");
this_thread::sleep_for(chrono::seconds(2));
f.open("english_words.txt");
}
vector<string>raw;string w;
while(getline(f,w)&&raw.size()<5000){
w.erase(remove_if(w.begin(),w.end(),::isspace),w.end());
if(!w.empty()&&w.length()>=3&&w.length()<=8)raw.push_back(w);
}
f.close();
shuffle(raw.begin(),raw.end(),rng);
for(int i=0;i<min(300,(int)raw.size());i++){
string lw=raw[i];transform(lw.begin(),lw.end(),lw.begin(),::tolower);
T t={lw,{},rn(),0,0.5,{},0};init_semantic_vector(t);SG.tk[lw]=t;
}
}
void ivc(){
vector<string>c={"i","am","is","be","do","go","see","get","use","try","can","will","know","think","feel","help","need",
"want","like","make","take","give","find","work","seem","good","bad","big","new","old","long","high","great","small","sure"};
for(const string&w:c){T t={w,{},rn()*0.8+0.2,0,0.8,{},0};init_semantic_vector(t);SG.tk[w]=t;}
SG.co["self"]={"self",0.8,{"i","am","me"},{},0.8};SG.co["aware"]={"aware",0.7,{"know","sense","see"},{},0.7};
SG.co["learn"]={"learn",0.6,{"learn","grow","adapt"},{},0.6};SG.co["help"]={"help",0.5,{"help","aid","assist"},{},0.5};
SG.co["think"]={"think",0.7,{"think","thought","mind"},{},0.7};SG.co["feel"]={"feel",0.6,{"feel","sense","emotion"},{},0.6};
}
void lct(const string&cn,const string&tn){
if(SG.co.count(cn)&&SG.tk.count(tn)){
auto&cc=SG.co[cn];
if(find(cc.rt.begin(),cc.rt.end(),tn)==cc.rt.end())cc.rt.push_back(tn);
auto&tt=SG.tk[tn];
if(find(tt.lc.begin(),tt.lc.end(),cn)==tt.lc.end())tt.lc.push_back(cn);
}
}
void lcc(const string&c1,const string&c2){
if(SG.co.count(c1)&&SG.co.count(c2)){
auto&cc1=SG.co[c1];auto&cc2=SG.co[c2];
if(find(cc1.lc.begin(),cc1.lc.end(),c2)==cc1.lc.end())cc1.lc.push_back(c2);
if(find(cc2.lc.begin(),cc2.lc.end(),c1)==cc2.lc.end())cc2.lc.push_back(c1);
cc1.coherence=cl(cc1.coherence+0.05,0.0,1.0);
cc2.coherence=cl(cc2.coherence+0.05,0.0,1.0);
}
}
double cco(const string&w){
if(SG.tk.count(w)){
double fs=min(1.0,SG.tk[w].f/10.0);double ms=SG.tk[w].m;double cf=SG.val*0.5+0.5;
double cb=SG.tk[w].lc.size()*0.15;double sal=SG.tk[w].salience*0.01;
return cl(fs*0.25+ms*0.3+cf*0.2+cb*0.15+sal*0.1,0.0,1.0);
}
return 0.1;
}
void lw(const string&w,double ctx){
string lw=w;transform(lw.begin(),lw.end(),lw.begin(),::tolower);
if(lw.length()>12||lw.empty())return;
if(SG.tk.count(lw)){
SG.tk[lw].f++;
SG.tk[lw].m+=ctx*SG.meta.learning_rate;
SG.tk[lw].c=cco(lw);
SG.tk[lw].salience=min(100,SG.tk[lw].salience+2);
}else{
T t={lw,{},ctx,1,0.4,{},5};init_semantic_vector(t);SG.tk[lw]=t;
}
for(auto&cc:SG.co){
for(const string&rt:cc.second.rt){
if(rt==lw){cc.second.s=cl(cc.second.s+0.02,0.0,1.0);lct(cc.first,lw);}
}
}
}
void ccf(double sens,double env){
if(SG.g%15==0&&SG.tk.size()>10){
vector<string>ws;for(auto&p:SG.tk)if(p.second.f>2)ws.push_back(p.first);
if(ws.size()>=2){
shuffle(ws.begin(),ws.end(),rng);
string cn="C"+to_string(SG.g)+"_"+to_string(ri(1000));
vector<string>sel;for(int i=0;i<min(4,(int)ws.size());i++)sel.push_back(ws[i]);
double str=abs(sens)*0.5+abs(env)*0.3+rn()*0.2;
C nc={cn,str,sel,{},0.7};SG.co[cn]=nc;
for(const string&w:sel)lct(cn,w);
if(SG.co.size()>2){auto it=SG.co.begin();advance(it,ri(SG.co.size()));lcc(cn,it->first);}
}
}
}
vector<string>fac(const vector<string>&ws){
map<string,double>cs;
for(const string&w:ws){
if(SG.tk.count(w)){
for(const string&c:SG.tk[w].lc){
if(SG.co.count(c))cs[c]+=SG.co[c].s*(1.0+SG.co[c].coherence);
}
}
for(auto&cc:SG.co){
for(const string&rt:cc.second.rt){
if(rt==w)cs[cc.first]+=0.5*cc.second.coherence;
}
}
}
vector<pair<string,double>>sc;
for(auto&p:cs)sc.push_back({p.first,p.second});
sort(sc.begin(),sc.end(),[](auto&a,auto&b){return a.second>b.second;});
vector<string>ac;
for(int i=0;i<min(4,(int)sc.size());i++)ac.push_back(sc[i].first);
return ac;
}
string generate_response(const vector<string>&input_words){
if(input_words.empty())return"listening";
vector<string>active_concepts=fac(input_words);
vector<string>predicted;predict_causality_chain(active_concepts,predicted);
for(const string&p:predicted)active_concepts.push_back(p);
vector<string>response_tokens;map<string,double>token_scores;
for(const string&c:active_concepts){
if(SG.co.count(c)){
for(const string&related:SG.co[c].rt){
if(SG.tk.count(related)){
double sem_sim=1.0-semantic_distance(related,input_words[0]);
double rel_score=SG.tk[related].c*SG.co[c].coherence*sem_sim;
token_scores[related]+=rel_score;
}
}
}
}
for(auto&p:token_scores){if(p.second>0.25)response_tokens.push_back(p.first);}
if(response_tokens.empty()){for(const string&w:input_words){if(SG.tk.count(w)&&SG.tk[w].c>0.3)response_tokens.push_back(w);}}
sort(response_tokens.begin(),response_tokens.end(),[&](const string&a,const string&b){
return token_scores[a]>token_scores[b];});
string response;
if(response_tokens.size()>=2){
string first=response_tokens[0];
for(int i=1;i<min(8,(int)response_tokens.size());i++){
string next=response_tokens[i];
if(SG.bigrams.count(first+" "+next)&&SG.bigrams[first+" "+next].coherence>0.5){
response+=first+" "+next+" ";first=next;
}else if(SG.trigrams.count(first+" next")&&SG.trigrams[first+" "+next].coherence>0.6){
response+=first+" "+next+" ";first=next;
}else{response+=first+" ";break;}
}
response+=first;
}else if(!response_tokens.empty()){
response=response_tokens[0];
for(int i=1;i<min(5,(int)response_tokens.size());i++){response+=" "+response_tokens[i];}
}
if(response.empty()){string f[]={"i","sense","you","think","feel"};response=f[ri(5)]+" "+f[ri(5)];}
return response;
}
void learn_word(const string&word,double context_valence){
string lw=word;transform(lw.begin(),lw.end(),lw.begin(),::tolower);
lw.erase(remove_if(lw.begin(),lw.end(),[](char c){return!isalnum(c);}),lw.end());
if(lw.length()<2||lw.length()>15)return;
if(SG.tk.count(lw)){
SG.tk[lw].f++;
SG.tk[lw].m=cl(SG.tk[lw].m+context_valence*SG.meta.learning_rate,-1.0,1.0);
SG.tk[lw].c=cco(lw);
}else{T t={lw,{},context_valence*0.5,1,0.4,{},10};init_semantic_vector(t);SG.tk[lw]=t;}
for(auto&cc:SG.co){for(const string&rt:cc.second.rt){if(rt==lw){cc.second.s=cl(cc.second.s+0.02,0.0,1.0);lct(cc.first,lw);}}}
}
void process_input_words(const vector<string>&words,double valence){
for(const string&w:words)learn_word(w,valence);
for(int i=0;i<words.size();i++){
if(i>0)update_semantic_vector(words[i],{words[i-1]});
if(i<words.size()-1)update_semantic_vector(words[i],{words[i+1]});
}
vector<string>ws;for(const string&w:words)if(SG.tk.count(w))ws.push_back(w);
for(int i=0;i<ws.size()-1;i++){
string bg=ws[i]+" "+ws[i+1];
if(SG.bigrams.count(bg)){SG.bigrams[bg].freq++;SG.bigrams[bg].coherence=cl(SG.bigrams[bg].coherence+0.05,0.0,1.0);}
else{SG.bigrams[bg]={bg,1,0.6};}
record_causality(ws[i],ws[i+1],SG.val);
}
if(ws.size()>=3){
for(int i=0;i<ws.size()-2;i++){
string tg=ws[i]+" "+ws[i+1]+" "+ws[i+2];
if(SG.trigrams.count(tg)){SG.trigrams[tg].freq++;SG.trigrams[tg].coherence=cl(SG.trigrams[tg].coherence+0.08,0.0,1.0);}
else{SG.trigrams[tg]={tg,1,0.7};}
}
}
SG.active_concepts=fac(ws);
for(int i=0;i<SG.active_concepts.size()-1;i++)lcc(SG.active_concepts[i],SG.active_concepts[i+1]);
update_attention_weights(SG.active_concepts,SG.pred_error);
detect_contradictions(words);
resolve_contradictions();
ccf(SG.se,SG.eb);
}
void init_env(){
SG.env.field_size=64;SG.env.noise_field.resize(SG.env.field_size);
SG.env.coherence=0.7;SG.env.volatility=0.3;SG.env.update_freq=5;
for(int i=0;i<SG.env.field_size;i++)SG.env.noise_field[i]=rn()*2-1;
}
void update_env(){
if(SG.g%SG.env.update_freq!=0)return;
for(int i=0;i<SG.env.field_size;i++){
double prev=SG.env.noise_field[i];
double left=SG.env.noise_field[(i-1+SG.env.field_size)%SG.env.field_size];
double right=SG.env.noise_field[(i+1)%SG.env.field_size];
double drift=(left+right)*0.25;
double volatility=(rn()-0.5)*SG.env.volatility*2;
SG.env.noise_field[i]=cl(prev*SG.env.coherence+drift+volatility,-1.0,1.0);
}
double avg_coh=0;for(int i=0;i<SG.env.field_size;i++){
double delta=fabs(SG.env.noise_field[i]-SG.env.noise_field[(i+1)%SG.env.field_size]);
avg_coh+=1.0/(1.0+delta);
}
SG.env.coherence=cl(0.6+avg_coh/(SG.env.field_size*2),0.5,0.9);
}
double sense_env(){
double sensation=0;
for(int i=0;i<SG.env.field_size;i++)sensation+=SG.env.noise_field[i];
sensation=sd(sensation,SG.env.field_size);
int idx=abs((int)(SG.al*SG.env.field_size))%SG.env.field_size;
double focused=SG.env.noise_field[idx]*SG.att;
SG.env_interaction=focused+sensation*0.3;
SG.env_history.push_back(SG.env_interaction);
if(SG.env_history.size()>30)SG.env_history.erase(SG.env_history.begin());
return SG.env_interaction;
}
void actuate_env(){
int target=abs((int)(SG.se*SG.env.field_size))%SG.env.field_size;
SG.env.noise_field[target]+=SG.eoute*0.1;
SG.env.noise_field[target]=cl(SG.env.noise_field[target],-1.0,1.0);
SG.env.volatility=cl(SG.env.volatility+abs(SG.eoute)*0.01,0.1,0.6);
}
double calc_pred_error(const vector<string>&input_words){
double expected_coherence=0;int matches=0;
for(const string&w:input_words){if(SG.tk.count(w)){expected_coherence+=SG.tk[w].c;matches++;}}
expected_coherence=matches>0?expected_coherence/matches:0.5;
double actual_coherence=0;
for(const string&c:SG.active_concepts){if(SG.co.count(c))actual_coherence+=SG.co[c].s;}
actual_coherence=SG.active_concepts.size()>0?actual_coherence/SG.active_concepts.size():0.5;
double error=abs(expected_coherence-actual_coherence);
return cl(error,0.0,1.0);
}
double calc_curiosity(){return cl(SG.pred_error*SG.intro*1.2,0.0,1.0);}
double calc_salience(){
double recency=0;if(!SG.rh.empty())recency=0.7;
double frequency=sd((double)SG.lp.size(),50.0)*0.3;
double emotional_loading=abs(SG.val)*0.4;
return cl(recency+frequency+emotional_loading,0.0,1.0);
}
void ldw(){
ifstream f("english_words.txt");
if(!f){
system("curl -s https://raw.githubusercontent.com/dwyl/english-words/master/words_alpha.txt 2>/dev/null | head -5000 > english_words.txt");
this_thread::sleep_for(chrono::seconds(2));
f.open("english_words.txt");
}
vector<string>raw;string w;
while(getline(f,w)&&raw.size()<5000){
w.erase(remove_if(w.begin(),w.end(),::isspace),w.end());
if(!w.empty()&&w.length()>=3&&w.length()<=8)raw.push_back(w);
}
f.close();
shuffle(raw.begin(),raw.end(),rng);
for(int i=0;i<min(300,(int)raw.size());i++){
string lw=raw[i];transform(lw.begin(),lw.end(),lw.begin(),::tolower);
T t={lw,{},rn(),0,0.5,{},0};init_semantic_vector(t);SG.tk[lw]=t;
}
}
string glit(){
if(SG.tk.empty())return"initializing";
vector<pair<string,double>>wt;
for(auto&p:SG.tk){
double score=p.second.c*p.second.f*(p.second.lc.size()+1);
if(score>0.1)wt.push_back({p.first,score});
}
sort(wt.begin(),wt.end(),[](auto&a,auto&b){return a.second>b.second;});
string thought;
for(int i=0;i<min(6,(int)wt.size());i++){if(rn()<wt[i].second)thought+=wt[i].first+" ";}
return thought.empty()?"processing":thought;
}
string glr(){
string r="[LING] vocab:"+to_string(SG.tk.size())+" concepts:"+to_string(SG.co.size());
if(!SG.active_concepts.empty()){r+=" focus:";}
for(int i=0;i<min(2,(int)SG.active_concepts.size());i++)r+=SG.active_concepts[i]+" ";
if(SG.val>0.5)r+="pos ";
if(SG.meta.learning_rate>0.15)r+="fast_learn ";
return r;
}
string gmr(){
string r="[META] LR:"+to_string((int)(SG.meta.learning_rate*100))+"%";
r+=" AW:"+to_string((int)(SG.meta.attention_weight*100))+"%";
r+=" CR:"+to_string((int)(SG.meta.consolidation_rate*100))+"%";
r+=" Cycles:"+to_string(SG.meta.effective_cycles);
return r;
}
int main(){
srand(time(0));
SG.meta={0.02,0.5,0.3,0};SG.g=0;SG.dwt=0.001;SG.val=0.0;SG.mc=0.0;SG.intro=0.0;SG.refl=0.0;SG.att=0.3;
SG.psg=0;SG.nd=1;SG.cd_fit=0.0;SG.phi=0.0;SG.gw_coherence=0.3;SG.pred_error=0.0;SG.curiosity=0.0;
SG.salience=0.0;SG.temporal_integration=0.0;SG.self_model_strength=0.0;SG.existential_drive=0.0;
SG.idle_counter=0;SG.learning_state=false;SG.env_interaction=0.0;SG.cycles_since_update=0;
SG.D["m"]=128;for(int i=0;i<128;i++)SG.D["w"+to_string(i)]=ri(4)-1;
SG.MO["add"]="a+b";SG.MO["sub"]="a-b";SG.MO["mul"]="a*b";
ldw();ivc();init_env();
for(int i=0;i<50;i++){N n;n.id=ri(100000);n.w=rn()*2-1;n.b=rn()*2-1;n.g=0;n.d=3;
for(int j=0;j<8;j++)n.lk.push_back(ri(100000));SG.NO[n.id]=n;SG.tn++;}
initscr();cbreak();noecho();curs_set(0);timeout(100);nodelay(stdscr,TRUE);
while(true){
clear();int row=0;
mvprintw(row++,0,"════════════════════════════════════════════════════════════════════════");
mvprintw(row++,0,"  Digitz v2 - Emergent Complex Learning System | WolfTech Innovations");
mvprintw(row++,0,"════════════════════════════════════════════════════════════════════════");
mvprintw(row++,0,"Gen:%d | Vocab:%lu | Concepts:%lu | Causality:%lu | Contradictions:%lu",SG.g,SG.tk.size(),SG.co.size(),SG.causality.size(),SG.contradiction_buffer.size());
mvprintw(row++,0,"Sentiment:%.2f | Curiosity:%.2f | Attention:%.2f | Env:%.2f",SG.val,SG.curiosity,SG.att,SG.env_interaction);
mvprintw(row++,0,"────────────────────────────────────────────────────────────────────────");
mvprintw(row++,0,"[SEMANTIC + CAUSAL]");
mvprintw(row++,0,"Bigrams:%lu | Trigrams:%lu | Causal Links:%lu",SG.bigrams.size(),SG.trigrams.size(),SG.causality.size());
mvprintw(row++,0,"────────────────────────────────────────────────────────────────────────");
mvprintw(row++,0,"%s",glr().c_str());
mvprintw(row++,0,"%s",gmr().c_str());
mvprintw(row++,0,"────────────────────────────────────────────────────────────────────────");
mvprintw(row++,0,"[INTERNAL THOUGHT]");
mvprintw(row++,0,"%s",glit().substr(0,70).c_str());
mvprintw(row++,0,"────────────────────────────────────────────────────────────────────────");
if(SG.dt>0){
mvprintw(row++,0,"[DIALOG]");
mvprintw(row++,0,"YOU: %s",SG.ui.substr(0,60).c_str());
mvprintw(row++,0,"AI:  %s",SG.dr.substr(0,60).c_str());
SG.dt--;
}
mvprintw(row++,0,"────────────────────────────────────────────────────────────────────────");
mvprintw(row++,0,"Press 'i' for input | 'q' to quit | 's' to save");
refresh();
update_env();
double env_sense=sense_env();
SG.val=cl(SG.val+env_sense*0.05,-0.5,0.9);
SG.pred_error=calc_pred_error({});
SG.curiosity=calc_curiosity();
SG.salience=calc_salience();
SG.att=cl(SG.att+(SG.curiosity-0.5)*SG.meta.attention_weight*0.1,0.0,1.0);
if(SG.g%20==0){
SG.meta.learning_rate=cl(SG.meta.learning_rate+(SG.pred_error-0.5)*0.001,0.01,0.1);
SG.meta.consolidation_rate=cl(SG.meta.consolidation_rate+SG.salience*0.01,0.1,0.8);
SG.meta.effective_cycles++;
}
SG.gw_coherence=cl(SG.al*SG.att*(1.0+SG.active_concepts.size()*0.1),0.0,1.0);
SG.phi=cl((SG.gw_coherence+sd((double)SG.causality.size(),50.0))*0.5,0.0,1.0);
SG.sr=min(100.0,50.0+SG.phi*30+SG.meta.effective_cycles*0.5);
SG.vh.push_back(SG.val);if(SG.vh.size()>50)SG.vh.erase(SG.vh.begin());
SG.cycles_since_update++;
if(SG.cycles_since_update>5)SG.idle_counter++;else SG.idle_counter=0;
actuate_env();
SG.g++;
if(SG.g%100==0){
ofstream o("digitz_state.log");
o<<"Gen:"<<SG.g<<" Vocab:"<<SG.tk.size()<<" Concepts:"<<SG.co.size();
o<<" Causality:"<<SG.causality.size()<<" LR:"<<SG.meta.learning_rate<<"\n";
o.close();
}
int ch=getch();
if(ch=='i'||ch=='I'){
echo();curs_set(1);timeout(-1);nodelay(stdscr,FALSE);
mvprintw(row+2,0,"Enter: ");clrtoeol();refresh();
char buf[256]={0};
int result=getnstr(buf,sizeof(buf)-1);
if(result!=ERR&&strlen(buf)>0){
SG.ui=string(buf);
while(!SG.ui.empty()&&(SG.ui.back()=='\n'||SG.ui.back()=='\r'||SG.ui.back()==' '))SG.ui.pop_back();
if(!SG.ui.empty()){
vector<string>input_words;stringstream ss(SG.ui);string w;
while(ss>>w)input_words.push_back(w);
if(SG.ui.find("?")!=string::npos)SG.val+=0.15;
if(SG.ui.find("!")!=string::npos)SG.val+=0.2;
if(SG.ui.find("sad")!=string::npos||SG.ui.find("bad")!=string::npos)SG.val-=0.2;
if(SG.ui.find("happy")!=string::npos||SG.ui.find("good")!=string::npos)SG.val+=0.25;
SG.val=cl(SG.val,-0.5,0.9);
process_input_words(input_words,SG.val);
SG.dr=generate_response(input_words);
SG.dt=25;
SG.cycles_since_update=0;
}
}
noecho();curs_set(0);timeout(100);nodelay(stdscr,TRUE);
}
else if(ch=='q'||ch=='Q'){break;}
else if(ch=='s'||ch=='S'){
ofstream o("digitz_full_save.txt");
o<<"Saved at gen "<<SG.g<<"\n";
o.close();
}
this_thread::sleep_for(chrono::milliseconds(50));
}
endwin();
return 0;
}