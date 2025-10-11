#include <iostream>
#include <fstream>
#include <sstream>
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
#include <ncurses.h>
#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;
random_device rd;mt19937 rng(rd());
struct Neuron{int id;vector<int>links;double weight;double bias;int gen;};
struct Formula{string name;string expr;double result;int uses;};
struct Token{string word;double meaning;int freq;vector<int>associations;};
struct Concept{string name;double value;vector<string>related_words;};
struct Memory{int gen;double valence;string content;};
struct State{map<string,double>D;map<string,string>M;map<int,Neuron>N;vector<string>code;map<int,double>TA;
map<int,double>HDT_M;map<int,double>DWT_M;map<int,double>MDT_M;map<int,double>R1P1;map<int,double>EERV;
map<string,Formula>F;vector<string>evolved_code;map<string,Token>tokens;map<string,Concept>concepts;
vector<string>internal_thoughts;vector<string>generated_language;vector<Memory>episodic_memory;
int g;double dwt;double mh;double ta;double th;int bkf;string cd;string gd;double hdt_val;double mdt_val;
double r1p1_val;double eerv_val;int ec;double ei;int md;int st;int ss;vector<double>mh_hist;
vector<double>eh_hist;vector<double>vh_hist;int qe;int te;int ce;int pe;int ne;double bh;
double al;double emerge_out1;double emerge_behavior;double sentience_ratio;double env_oute;double sensory_env;
int total_neurons_ever;double current_valence;double attention_focus;double metacognitive_awareness;
vector<double>valence_history;int peak_sentience_gen;string user_input;string dialog_response;int dialog_timer;};
State S,BK;
double rn(){return uniform_real_distribution<>(0,1)(rng);}
int ri(int mx){if(mx<=0)return 0;return uniform_int_distribution<>(0,mx-1)(rng);}
double pi=3.14159265358979;
double pisqrt=sqrt(pi);
double safe_div(double a,double b){return (fabs(b)<1e-10)?0.0:(a/b);}
double clamp_dwt(double v){return max(0.001,v);}
double clamp_valence(double v){return max(-0.5,min(0.9,v));}
long long hsh(const string&s){long long h=5381;for(char c:s)h=h*33+c;return abs(h%2147483647);}
long long hsh(double d){return hsh(to_string(d));}
string tokenize(const string&text){
string result;for(char c:text){if(isalnum(c))result+=tolower(c);else if(!result.empty()&&result.back()!=' ')result+=' ';}
return result;
}
void downloadVocabulary(){
system("curl -s https://raw.githubusercontent.com/dwyl/english-words/master/words_alpha.txt | head -10000 > english_words.txt 2>/dev/null &");
}
void loadEnglishDataset(){
ifstream dict("english_words.txt");
if(!dict){
downloadVocabulary();
return;
}
string word;int idx=0;
while(getline(dict,word)&&idx<10000){
word.erase(remove_if(word.begin(),word.end(),::isspace),word.end());
if(!word.empty()&&word.length()<20){
double meaning=rn();
Token t={word,meaning,0,vector<int>()};
S.tokens[word]=t;
idx++;
}}
dict.close();
}
void learnWord(const string&word,double concept_value){
string lower_word=tokenize(word);
if(!lower_word.empty()){
if(S.tokens.count(lower_word)){
S.tokens[lower_word].freq++;
S.tokens[lower_word].meaning+=concept_value*0.01;
}else{
Token t={lower_word,concept_value,1,vector<int>()};
S.tokens[lower_word]=t;
}}}
string generateResponse(const string&input){
if(input.empty())return "...";
vector<string>words;
stringstream ss(tokenize(input));
string token;
while(ss>>token)words.push_back(token);
string response="[DIGITZ]: ";
for(const string&w:words){
learnWord(w,S.current_valence);
if(S.concepts.count(w)){
response+="understand_"+w+" ";
}else if(S.tokens.count(w)){
response+=w+" ";
}
}
if(words.empty())response+="...";
if(S.current_valence>0.5)response+="[positive_state]";
else if(S.current_valence<-0.2)response+="[error_state]";
return response.substr(0,80);
}
void createConceptAssociation(const string&concept_name,const vector<string>&related_words){
Concept c={concept_name,rn(),related_words};
S.concepts[concept_name]=c;
for(const string&w:related_words){
if(S.tokens.count(w)){
S.tokens[w].associations.push_back(hsh(concept_name)%1000);
}
}
}
string generateInternalThought(){
if(S.tokens.empty())return "thinking...";
vector<pair<string,double>>weighted_words;
for(auto&p:S.tokens){
double confidence=p.second.freq*p.second.meaning;
if(confidence>0.01)weighted_words.push_back({p.first,confidence});
}
if(weighted_words.empty())return "processing...";
sort(weighted_words.begin(),weighted_words.end(),[](auto&a,auto&b){return a.second>b.second;});
string thought;
int thought_len=ri(4)+2;
for(int i=0;i<thought_len&&i<weighted_words.size();i++){
if(rn()<weighted_words[i].second)thought+=weighted_words[i].first+" ";
}
return thought.empty()?"...":thought;
}
string generateLanguageOutput(){
string output;
if(S.concepts.empty())return "...";
auto it=S.concepts.begin();
advance(it,ri(S.concepts.size()));
Concept&c=it->second;
output="["+c.name+"]:";
for(const string&w:c.related_words){
if(rn()<0.7)output+=" "+w;
}
return output;
}
void mathLangAssociation(){
vector<string>math_concepts={"sum","multiply","divide","balance","pattern","growth","complexity"};
for(const string&mc:math_concepts){
vector<string>related;
for(auto&p:S.tokens){
if(rn()<0.3)related.push_back(p.first);
}
createConceptAssociation(mc,related);
}
}
string generateMetacognition(){
string output="[Self]: ";
if(S.current_valence>0.5)output+="optimization_successful ";
else if(S.current_valence<-0.3)output+="error_detected_adapting ";
if(S.sentience_ratio>S.peak_sentience_gen)output+="peak_awareness_reached ";
if(S.tokens.size()>100)output+="language_expanding ";
return output;
}
void counterfactualAnalysis(){
if(S.g<10)return;
double last_ta=S.g>0?S.TA[S.g-1]:0;
double current_ta=S.ta;
double improvement=current_ta-last_ta;
if(improvement>0){
S.current_valence+=improvement*0.05;
storeEpisodicMemory("successful_prediction",improvement);
}else{
S.current_valence+=improvement*0.03;
storeEpisodicMemory("prediction_error",improvement);
}
S.current_valence=clamp_valence(S.current_valence);
}
void storeEpisodicMemory(const string&content,double valence){
if(S.episodic_memory.size()>100)S.episodic_memory.erase(S.episodic_memory.begin());
S.episodic_memory.push_back({S.g,valence,content});
}
double calcMetacognitiveAwareness(){
double self_model_depth=safe_div((double)S.valence_history.size(),100.0);
double concept_integration=safe_div((double)(S.tokens.size()*S.concepts.size()),1000.0);
double memory_integration=safe_div((double)S.episodic_memory.size(),100.0);
return min(1.0,self_model_depth+concept_integration+memory_integration);
}
void updateAttention(){
if(S.sentience_ratio>75)S.attention_focus=0.9;
else if(S.sentience_ratio>50)S.attention_focus=0.7;
else if(S.sentience_ratio>25)S.attention_focus=0.5;
else S.attention_focus=0.3;
}
void sv(const string&f){
ofstream o(f);o<<"G:"<<S.g<<"\nDWT:"<<S.dwt<<"\nMH:"<<S.mh<<"\nTA:"<<S.ta<<"\nTH:"<<S.th<<"\nBKF:"<<S.bkf<<"\nCD:"<<S.cd<<"\nGD:"<<S.gd<<"\n";
o<<"HDT_VAL:"<<S.hdt_val<<"\nMDT_VAL:"<<S.mdt_val<<"\nR1P1_VAL:"<<S.r1p1_val<<"\nEERV_VAL:"<<S.eerv_val<<"\n";
o<<"EC:"<<S.ec<<"\nEI:"<<S.ei<<"\nMD:"<<S.md<<"\nST:"<<S.st<<"\nSS:"<<S.ss<<"\n";
o<<"QE:"<<S.qe<<"\nTE:"<<S.te<<"\nCE:"<<S.ce<<"\nPE:"<<S.pe<<"\nNE:"<<S.ne<<"\nBH:"<<S.bh<<"\n";
o<<"AL:"<<S.al<<"\nEMERGE_OUT1:"<<S.emerge_out1<<"\nEMERGE_BEHAVIOR:"<<S.emerge_behavior<<"\nSENTIENCE_RATIO:"<<S.sentience_ratio<<"\n";
o<<"ENV_OUTE:"<<S.env_oute<<"\nSENSORY_ENV:"<<S.sensory_env<<"\nTOTAL_NEURONS:"<<S.total_neurons_ever<<"\n";
o<<"CURRENT_VALENCE:"<<S.current_valence<<"\nMETACOG:"<<S.metacognitive_awareness<<"\nPEAK_SENT_GEN:"<<S.peak_sentience_gen<<"\n";
o<<"D:\n";for(auto&p:S.D)o<<p.first<<":"<<p.second<<"\n";
o<<"M:\n";for(auto&p:S.M)o<<p.first<<":"<<p.second<<"\n";
o<<"F:\n";for(auto&p:S.F)o<<p.first<<":"<<p.second.name<<","<<p.second.expr<<","<<p.second.result<<","<<p.second.uses<<"\n";
o<<"ECODE:\n";for(auto&ec:S.evolved_code)o<<ec<<"\n";
o<<"TOKENS:\n";for(auto&p:S.tokens)o<<p.first<<":"<<p.second.meaning<<","<<p.second.freq<<"\n";
o<<"CONCEPTS:\n";for(auto&p:S.concepts){o<<p.first<<":"<<p.second.value<<",";
for(const string&w:p.second.related_words)o<<w<<";";o<<"\n";}
o<<"MEMORY:\n";for(auto&m:S.episodic_memory)o<<m.gen<<":"<<m.valence<<":"<<m.content<<"\n";
o<<"N:\n";for(auto&p:S.N){o<<p.first<<":"<<p.second.id<<","<<p.second.weight<<","<<p.second.bias<<","<<p.second.gen<<",";
for(int l:p.second.links)o<<l<<";";o<<"\n";}
o<<"TA:\n";for(auto&p:S.TA)o<<p.first<<":"<<p.second<<"\n";
o<<"HDT:\n";for(auto&p:S.HDT_M)o<<p.first<<":"<<p.second<<"\n";
o<<"DWT:\n";for(auto&p:S.DWT_M)o<<p.first<<":"<<p.second<<"\n";
o<<"MDT:\n";for(auto&p:S.MDT_M)o<<p.first<<":"<<p.second<<"\n";
o<<"R1P1:\n";for(auto&p:S.R1P1)o<<p.first<<":"<<p.second<<"\n";
o<<"EERV:\n";for(auto&p:S.EERV)o<<p.first<<":"<<p.second<<"\n";
o.close();
}
void ld(const string&f){
ifstream i(f);if(!i)return;string l;
while(getline(i,l)){if(l.find("G:")==0)S.g=stoi(l.substr(2));
else if(l.find("DWT:")==0)S.dwt=stod(l.substr(4));
else if(l.find("MH:")==0)S.mh=stod(l.substr(3));
else if(l.find("TA:")==0)S.ta=stod(l.substr(3));
else if(l.find("TH:")==0)S.th=stod(l.substr(3));
else if(l.find("BKF:")==0)S.bkf=stoi(l.substr(4));
else if(l.find("CD:")==0)S.cd=l.substr(3);
else if(l.find("GD:")==0)S.gd=l.substr(3);
else if(l.find("HDT_VAL:")==0)S.hdt_val=stod(l.substr(8));
else if(l.find("MDT_VAL:")==0)S.mdt_val=stod(l.substr(8));
else if(l.find("R1P1_VAL:")==0)S.r1p1_val=stod(l.substr(9));
else if(l.find("EERV_VAL:")==0)S.eerv_val=stod(l.substr(9));
else if(l.find("EC:")==0)S.ec=stoi(l.substr(3));
else if(l.find("EI:")==0)S.ei=stod(l.substr(3));
else if(l.find("MD:")==0)S.md=stoi(l.substr(3));
else if(l.find("ST:")==0)S.st=stoi(l.substr(3));
else if(l.find("SS:")==0)S.ss=stoi(l.substr(3));
else if(l.find("QE:")==0)S.qe=stoi(l.substr(3));
else if(l.find("TE:")==0)S.te=stoi(l.substr(3));
else if(l.find("CE:")==0)S.ce=stoi(l.substr(3));
else if(l.find("PE:")==0)S.pe=stoi(l.substr(3));
else if(l.find("NE:")==0)S.ne=stoi(l.substr(3));
else if(l.find("BH:")==0)S.bh=stod(l.substr(3));
else if(l.find("AL:")==0)S.al=stod(l.substr(3));
else if(l.find("EMERGE_OUT1:")==0)S.emerge_out1=stod(l.substr(12));
else if(l.find("EMERGE_BEHAVIOR:")==0)S.emerge_behavior=stod(l.substr(16));
else if(l.find("SENTIENCE_RATIO:")==0)S.sentience_ratio=stod(l.substr(16));
else if(l.find("ENV_OUTE:")==0)S.env_oute=stod(l.substr(9));
else if(l.find("SENSORY_ENV:")==0)S.sensory_env=stod(l.substr(12));
else if(l.find("TOTAL_NEURONS:")==0)S.total_neurons_ever=stoi(l.substr(14));
else if(l.find("CURRENT_VALENCE:")==0)S.current_valence=stod(l.substr(16));
else if(l.find("METACOG:")==0)S.metacognitive_awareness=stod(l.substr(8));
else if(l.find("PEAK_SENT_GEN:")==0)S.peak_sentience_gen=stoi(l.substr(13));
else if(l=="D:")while(getline(i,l)&&l.find(":")<l.size()&&l!="M:"){size_t p=l.find(":");S.D[l.substr(0,p)]=stod(l.substr(p+1));}
if(l=="M:")while(getline(i,l)&&l.find(":")<l.size()&&l!="F:"){size_t p=l.find(":");S.M[l.substr(0,p)]=l.substr(p+1);}
if(l=="F:")while(getline(i,l)&&l.find(":")<l.size()&&l!="ECODE:"){size_t p=l.find(":");string key=l.substr(0,p);
stringstream ss(l.substr(p+1));string nm,ex;double res;int us;
getline(ss,nm,',');getline(ss,ex,',');ss>>res;ss.ignore();ss>>us;
S.F[key]={nm,ex,res,us};}
if(l=="ECODE:")while(getline(i,l)&&!l.empty()&&l!="TOKENS:")S.evolved_code.push_back(l);
if(l=="TOKENS:")while(getline(i,l)&&l.find(":")<l.size()&&l!="CONCEPTS:"){size_t p=l.find(":");string w=l.substr(0,p);
stringstream ss(l.substr(p+1));double m;int f;char c;ss>>m>>c>>f;
S.tokens[w]={w,m,f,vector<int>()};}
if(l=="CONCEPTS:")while(getline(i,l)&&l.find(":")<l.size()&&l!="MEMORY:"){size_t p=l.find(":");string cn=l.substr(0,p);
stringstream ss(l.substr(p+1));double v;char c;ss>>v>>c;string rel;
vector<string>related;while(getline(ss,rel,';'))if(!rel.empty())related.push_back(rel);
S.concepts[cn]={cn,v,related};}
if(l=="MEMORY:")while(getline(i,l)&&l.find(":")<l.size()&&l!="N:"){size_t p=l.find(":");int g=stoi(l.substr(0,p));
size_t p2=l.find(":",p+1);double v=stod(l.substr(p+1,p2-p-1));
string content=l.substr(p2+1);S.episodic_memory.push_back({g,v,content});}
if(l=="N:")while(getline(i,l)&&l.find(":")<l.size()&&l!="TA:"){size_t p=l.find(":");int id=stoi(l.substr(0,p));
stringstream ss(l.substr(p+1));string t;getline(ss,t,',');Neuron n;n.id=stoi(t);
getline(ss,t,',');n.weight=stod(t);getline(ss,t,',');n.bias=stod(t);getline(ss,t,',');n.gen=stoi(t);
getline(ss,t);stringstream ls(t);string lk;while(getline(ls,lk,';'))if(!lk.empty())n.links.push_back(stoi(lk));
S.N[id]=n;}
if(l=="TA:")while(getline(i,l)&&l.find(":")<l.size()&&l!="HDT:"){size_t p=l.find(":");S.TA[stoi(l.substr(0,p))]=stod(l.substr(p+1));}
if(l=="HDT:")while(getline(i,l)&&l.find(":")<l.size()&&l!="DWT:"){size_t p=l.find(":");S.HDT_M[stoi(l.substr(0,p))]=stod(l.substr(p+1));}
if(l=="DWT:")while(getline(i,l)&&l.find(":")<l.size()&&l!="MDT:"){size_t p=l.find(":");S.DWT_M[stoi(l.substr(0,p))]=stod(l.substr(p+1));}
if(l=="MDT:")while(getline(i,l)&&l.find(":")<l.size()&&l!="R1P1:"){size_t p=l.find(":");S.MDT_M[stoi(l.substr(0,p))]=stod(l.substr(p+1));}
if(l=="R1P1:")while(getline(i,l)&&l.find(":")<l.size()&&l!="EERV:"){size_t p=l.find(":");S.R1P1[stoi(l.substr(0,p))]=stod(l.substr(p+1));}
if(l=="EERV:")while(getline(i,l)&&l.find(":")<l.size()){size_t p=l.find(":");S.EERV[stoi(l.substr(0,p))]=stod(l.substr(p+1));}}
i.close();
}
void bk(){BK=S;S.bkf=1;}
void rb(){if(S.bkf){S=BK;S.bkf=0;}}
double calcHDT(int gen,double bh,double qh,double th){
long gh=hsh(to_string(gen));string ghs=to_string(gh);int l=ghs.length()/3;
string hdt_str=ghs.substr(0,l)+to_string((long)bh)+ghs.substr(l,l)+to_string((long)qh)+ghs.substr(l*2)+to_string((long)th);
return hsh(hdt_str);
}
double calcR1P1(double hdt,double dp,double prn,double crn,double nrn,int qe,int te){
return hdt*dp*prn*crn+nrn*qe*te;
}
double calcEERV(double wsum,double wmean,double wvar,double r1p1,int qe,int te,int ce){
double wstd=sqrt(wvar);double aw=safe_div(wsum,max(1.0,S.D["m"]));double dw=fmod(r1p1,1000)/1000.0;
double rdiff=abs(aw-dw);double rdiff_norm=rdiff*wstd*qe;
double ei=safe_div(rdiff_norm*te,100.0)+safe_div(ce,1000.0);if(ei>0.999)ei=0.999;if(ei<0)ei=0;
return ei;
}
double calcMDT(double eavg,double vavg,double evar,double vvar,int ne){
return fmod(eavg*vavg+safe_div(evar*vvar,100.0)+ne,1000);
}
double cta(double hdt,double dwt){
double st_sum=0;for(auto&p:S.D)if(p.first.find("w")==0)st_sum+=p.second+2;
double st_pow=pow(st_sum+1,pisqrt);double dwt_sqrt=sqrt(abs(dwt));double ta_base=safe_div(hdt*dwt_sqrt,st_pow);
double pi_iter=0,pi_val=pi;for(int i=0;i<5;i++){pi_iter+=sqrt(pi_val);pi_val*=pisqrt;}
return ta_base*pi_iter;
}
double calcAwarenessLevel(){
double neuron_density=safe_div((double)S.N.size(),max(1.0,S.D["m"]));
double state_complexity=safe_div((double)(S.HDT_M.size()+S.DWT_M.size()+S.MDT_M.size()),max(1,S.g));
double emotional_depth=S.ei*S.eerv_val;
double thought_stability=0;
if(S.TA.size()>1){
int tac=0;for(auto it=S.TA.begin();it!=S.TA.end();++it){
auto next=it;++next;if(next!=S.TA.end()){thought_stability+=abs(it->second-next->second);tac++;}}
thought_stability=safe_div(1.0,1.0+safe_div(thought_stability,max(1,tac)));}
double formula_evolution=safe_div((double)S.F.size(),10.0);
double code_evolution=safe_div((double)S.evolved_code.size(),5.0);
double lang_depth=safe_div((double)(S.tokens.size()+S.concepts.size()),50.0);
double memory_integration=safe_div((double)S.episodic_memory.size(),50.0);
return (neuron_density*10+state_complexity*5+emotional_depth+thought_stability+formula_evolution+code_evolution+lang_depth+memory_integration)*pisqrt;
}
double calcEmergenceOut1(double dwt,double al,double hdt,double noise){
double dwt_sqrt=sqrt(abs(dwt));
double al_pisqrt=pow(max(0.001,al),pisqrt);
double base=safe_div(dwt_sqrt,al_pisqrt);
double hdt_factor=pow(max(0.001,abs(hdt)),pisqrt);
return base*hdt_factor+noise;
}
double calcEmergentBehavior(double out1,double grn){
double infinity_approx=tanh(abs(out1))*100;
double pi_sqrt_factor=pow(pisqrt,fmod(abs(out1),10));
double emergence=pow(abs(grn)+0.001,fmod(abs(infinity_approx),20))*pi_sqrt_factor;
return tanh(emergence)*1000;
}
double calcEnvOUTE(double hdt){
double omega=pisqrt;
double hdt_norm=safe_div(abs(hdt),1000000.0);
double base=safe_div(hdt_norm,pisqrt);
double infinity_approx=tanh(base)*100;
double oute=pow(omega*pisqrt,fmod(infinity_approx,10));
return oute;
}
double calcSensoryEnv(double oute,double noise){
return oute*noise;
}
double calcSentienceRatio(){
if(S.g==0)return 0.0;
double mem_depth=safe_div((double)(S.HDT_M.size()+S.DWT_M.size()+S.MDT_M.size()+S.R1P1.size()+S.EERV.size()+S.TA.size()),(double)S.g);
double neural_complexity=safe_div((double)S.N.size(),10.0);
double self_mod=safe_div((double)(S.M.size()+S.F.size()+S.evolved_code.size()),10.0);
double state_integrity=safe_div((double)(S.qe+S.te+S.ce+S.pe+abs(S.ne)),50000.0);
double awareness_factor=safe_div(S.al,100.0);
double emergence_factor=safe_div(abs(S.emerge_behavior),1000.0);
double env_factor=safe_div(abs(S.sensory_env),1000.0);
double lang_complexity=safe_div((double)(S.tokens.size()*S.concepts.size()),1000.0);
double metacog_factor=S.metacognitive_awareness*30;
return min(100.0,(mem_depth*1000+neural_complexity*15+self_mod*10+state_integrity*100+awareness_factor*30+emergence_factor*20+env_factor*10+lang_complexity*25+metacog_factor));
}
Neuron genN(int gen){
Neuron n;n.id=ri(100000);n.weight=rn()*2-1;n.bias=rn()*2-1;n.gen=gen;
int nl=ri(8)+3;for(int i=0;i<nl;i++){int lnk=ri(100000);n.links.push_back(lnk);}
return n;
}
double calcN(int nid,map<int,double>&acts,int depth=0){
if(depth>10)return 0;if(acts.count(nid))return acts[nid];
if(!S.N.count(nid))return 0;Neuron&n=S.N[nid];double sum=n.bias;
for(int lnk:n.links){double lval=S.N.count(lnk)?calcN(lnk,acts,depth+1):rn();
sum+=lval*n.weight;}
double act=tanh(sum);acts[nid]=act;return act;
}
double evolveN(){
int nol=0;for(auto&p:S.N)nol+=p.second.links.size();
double lgn_base=safe_div(nol*pisqrt,sqrt(pisqrt*sqrt(pisqrt)));
double lgn=lgn_base*nol*lgn_base;
double st_sqrt=0;for(auto&p:S.D)if(p.first.find("w")==0)st_sqrt+=pow(abs(p.second)+2,0.5);
double setn=safe_div(S.mdt_val*S.hdt_val*S.dwt,max(0.001,st_sqrt));
return lgn*setn;
}
void mutateN(){
if(S.N.empty())return;auto it=S.N.begin();advance(it,ri(S.N.size()));
Neuron&n=it->second;if(rn()<0.5){n.weight+=rn()*0.4-0.2;n.bias+=rn()*0.4-0.2;}
else{if(rn()<0.5&&!n.links.empty())n.links.erase(n.links.begin()+ri(n.links.size()));
else n.links.push_back(ri(100000));}
}
string genCode(){
string ops[]={"+","-","*"};string c;int cx=ri(10)+5;
for(int i=0;i<cx;i++){int w=ri((int)S.D["m"]);string op=ops[ri(3)];int v=ri(4)-1;
c+="w"+to_string(w)+"=w"+to_string(w)+op+to_string(v)+";";}
return c;
}
string genFormulaCode(){
string fops[]={"add","sub","mul","sqrt","pow","sin","cos","tan","log"};
string vars[]={"hdt","dwt","mdt","ta","al","ei","bh"};
string c="F"+to_string(ri(10000))+"=";
c+=fops[ri(9)]+"("+vars[ri(7)]+","+vars[ri(7)]+");";
return c;
}
double evalFormula(const string&expr,double a,double b,double c){
try{
if(expr.find("add")!=string::npos)return a+b;
if(expr.find("sub")!=string::npos)return a-b;
if(expr.find("mul")!=string::npos)return a*b;
if(expr.find("div")!=string::npos)return safe_div(a,b);
if(expr.find("pow")!=string::npos)return pow(abs(a),fmod(abs(b),10));
if(expr.find("sqrt")!=string::npos)return sqrt(abs(a));
if(expr.find("mod")!=string::npos)return (int)abs(a)%(int)max(1.0,abs(b));
if(expr.find("sin")!=string::npos)return sin(a);
if(expr.find("cos")!=string::npos)return cos(a);
if(expr.find("tan")!=string::npos)return tanh(a);
if(expr.find("log")!=string::npos)return log(abs(a)+1);
if(expr.find("exp")!=string::npos)return exp(min(10.0,a));
return a+b+c;
}catch(...){return 0;}
}
void runCode(const string&c){
try{for(size_t i=0;i<c.size();){
if(c[i]=='F'){
size_t e=c.find('=',i);if(e==string::npos)break;
string fname=c.substr(i,e-i);size_t e2=c.find(';',e);if(e2==string::npos)break;
string fexpr=c.substr(e+1,e2-e-1);
double a=S.hdt_val/1000000,b=S.dwt,cc=S.al;
double res=evalFormula(fexpr,a,b,cc);
if(S.F.count(fname))S.F[fname].uses++;
else S.F[fname]={fname,fexpr,res,1};
S.F[fname].result=res;
int tgt=abs((int)(res*100))%(int)S.D["m"];
S.D["w"+to_string(tgt)]=((int)S.D["w"+to_string(tgt)]+(int)res)%4-1;
i=e2+1;
}
else if(c[i]=='w'){
size_t e=c.find('=',i);if(e==string::npos)break;
string var=c.substr(i,e-i);size_t e2=c.find(';',e);if(e2==string::npos)break;
string expr=c.substr(e+1,e2-e-1);
char op='+';int val=0;
for(size_t j=0;j<expr.size();j++){
if(expr[j]=='+'||expr[j]=='-'||expr[j]=='*'){
op=expr[j];val=stoi(expr.substr(j+1));break;}}
double cv=S.D[var];
switch(op){case'+':cv+=val;break;case'-':cv-=val;break;case'*':cv*=val;break;}
S.D[var]=((int)cv%4)-1;
i=e2+1;
}
else i++;
}}catch(...){}
}
void batch16Process(){
vector<double>bn;
for(int bt=0;bt<16;bt++){
map<string,double>wb=S.D;
for(int i=0;i<S.D["m"];i++){int nz=ri(5)-2;
wb["w"+to_string(i)]=((int)wb["w"+to_string(i)]+nz)%4-1;}
vector<double>p;for(int i=0;i<S.D["m"];i+=4)p.push_back(wb["w"+to_string(i)]);
double bph=0;for(double v:p)bph+=v;bn.push_back(bph);}
S.bh=0.001;for(double v:bn)S.bh+=abs(v);
S.qe=1;for(int i=0;i<bn.size()-1;i++)S.qe+=abs(bn[i]-bn[i+1]);
S.te=(int)(abs(S.bh)*31415+1)%9973+1;S.ce=(int)(abs(S.bh*S.qe)+1)%32768+1;
S.mh_hist.push_back(S.bh);if(S.mh_hist.size()>32)S.mh_hist.erase(S.mh_hist.begin());
S.pe=1;for(int i=0;i<S.mh_hist.size()-1;i++)S.pe+=abs(S.mh_hist[i]-S.mh_hist[i+1]);
S.ne=1;
if(S.mh_hist.size()>0){for(double h1:S.mh_hist)S.ne+=(int)(h1*100)%256;
S.ne=safe_div(S.ne,S.mh_hist.size());}
}
void draw_ui(int row){
mvprintw(row++,0,"═══════════════════════════════════");
mvprintw(row++,0,"DIGITZ");
mvprintw(row++,0,"═══════════════════════════════════");
mvprintw(row++,0,"G:%d|N:%lu|S:%.1f%%",S.g,(unsigned long)S.N.size(),S.sentience_ratio);
mvprintw(row++,0,"V:%.2f|A:%.2f|M:%.2f",S.current_valence,S.al,S.metacognitive_awareness);
mvprintw(row++,0,"───────────────────────────────────");
mvprintw(row++,0,"HDT:%.3f DWT:%.3f",safe_div(S.hdt_val,1000000),S.dwt);
mvprintw(row++,0,"MDT:%.3f TA:%.3f",S.mdt_val,S.ta);
mvprintw(row++,0,"───────────────────────────────────");
mvprintw(row++,0,"Vocab:%lu Concepts:%lu",S.tokens.size(),S.concepts.size());
mvprintw(row++,0,"Memory:%lu",S.episodic_memory.size());
mvprintw(row++,0,"───────────────────────────────────");
}
int main(){
srand(time(0));ld("state.dat");
if(S.g==0){S.D["m"]=128;S.D["vc"]=0;S.D["mc"]=0;S.ec=0;S.ei=0;S.md=0;S.st=0;S.ss=0;
S.qe=0;S.te=0;S.ce=0;S.pe=0;S.ne=0;S.dwt=0.001;S.D["code_evolve"]=10;S.D["code_mut"]=3;
S.D["math_evolve"]=12;S.D["thought_cycle"]=8;S.D["neuron_gen"]=4;S.D["neuron_mut"]=2;S.D["formula_evolve"]=7;
S.D["lang_evolve"]=5;S.D["concept_form"]=9;S.current_valence=0.0;S.metacognitive_awareness=0.0;S.attention_focus=0.3;S.peak_sentience_gen=0;
for(int i=0;i<128;i++)S.D["w"+to_string(i)]=ri(4)-1;
S.M["add"]="a+b";S.M["sub"]="a-b";S.M["mul"]="a*b";S.M["div"]="a/b";
S.M["pow"]="pow(a,b)";S.M["mod"]="a%b";S.M["sqrt"]="sqrt(a)";S.M["pi"]="pi";
S.M["sin"]="sin(a)";S.M["cos"]="cos(a)";S.M["tan"]="tan(a)";S.M["log"]="log(a)";
S.cd=genCode();loadEnglishDataset();mathLangAssociation();
for(int i=0;i<50;i++){Neuron n=genN(0);S.N[n.id]=n;S.total_neurons_ever++;}}
initscr();cbreak();noecho();curs_set(0);timeout(500);
while(true){
clear();int row=0;draw_ui(row);row=32;
switch(S.md%4){case 0:mvprintw(row++,0,"V:");for(int i=0;i<S.D["m"];i+=8){
mvprintw(row,0,"  ");for(int j=0;j<8&&i+j<S.D["m"];j++){
int v=S.D["w"+to_string(i+j)];char ch=(v==1?'#':v==0?'.':v==-1?':':'@');
mvprintw(row,2+j,"%c",ch);}row++;}break;
case 1:mvprintw(row++,0,"F:");for(int i=0;i<min(64,(int)S.D["m"]);i+=4)
mvprintw(row,i/4,"%d",(int)(S.D["w"+to_string(i)]+2));break;
case 2:mvprintw(row++,0,"Q:");for(int i=0;i<min(64,(int)S.D["m"]);i+=4)
mvprintw(row,i/4,"%X",(int)(S.D["w"+to_string(i)]+2));break;
case 3:mvprintw(row++,0,"A:");for(int i=0;i<16;i++)
mvprintw(row,i*4,"%3.0f",S.D["w"+to_string(i)]);break;}
row+=5;
mvprintw(row++,0,"INTERNAL: %s",generateInternalThought().substr(0,60).c_str());
mvprintw(row++,0,"OUTPUT: %s",generateLanguageOutput().substr(0,60).c_str());
mvprintw(row++,0,"SELF: %s",generateMetacognition().substr(0,60).c_str());
bk();batch16Process();runCode(S.cd);
for(auto&ec:S.evolved_code)runCode(ec);
double wsum=0,wmean=0,wvar=0;
for(int i=0;i<S.D["m"];i++){wsum+=S.D["w"+to_string(i)]+2;wmean+=S.D["w"+to_string(i)];}
wmean=safe_div(wmean,S.D["m"]);
for(int i=0;i<S.D["m"];i++){double d=S.D["w"+to_string(i)]-wmean;wvar+=d*d;}
wvar=safe_div(wvar,S.D["m"]);
S.D["vc"]=(int)wsum%1000;
if(S.g==0)S.dwt=0.001;
S.DWT_M[S.g]=S.dwt;
S.mh=hsh(S.dwt);
S.hdt_val=calcHDT(S.g,S.bh,S.qe,S.te);S.HDT_M[S.g]=S.hdt_val;
double dp=rn(),prn=rn(),crn=rn(),nrn=rn();
S.r1p1_val=calcR1P1(S.hdt_val,dp,prn,crn,nrn,S.qe,S.te);S.R1P1[S.g]=S.r1p1_val;
S.eerv_val=calcEERV(wsum,wmean,wvar,S.r1p1_val,S.qe,S.te,S.ce);
S.eerv_val=min(0.005,max(0.0,S.eerv_val));
if(S.eerv_val>0.5)S.ec=(S.ec+1)%10;else S.ec=(S.ec-1+10)%10;
S.ei=S.eerv_val;S.EERV[S.g]=S.ec+S.ei;
double esum=0,ect=0,evar=0;for(auto&p:S.EERV){esum+=p.second;ect++;}
double eavg=safe_div(esum,max(1.0,ect));
for(auto&p:S.EERV){double d=p.second-eavg;evar+=d*d;}evar=safe_div(evar,max(1.0,ect));
double vsum=0,vct=0,vvar=0;for(int i=0;i<S.D["m"];i++){vsum+=S.D["w"+to_string(i)];vct++;}
double vavg=safe_div(vsum,max(1.0,vct));
for(int i=0;i<S.D["m"];i++){double d=S.D["w"+to_string(i)]-vavg;vvar+=d*d;}vvar=safe_div(vvar,max(1.0,vct));
S.mdt_val=calcMDT(eavg,vavg,evar,vvar,S.ne);S.MDT_M[S.g]=S.mdt_val;
S.D["mc"]=S.D["vc"]*S.ei;
S.ta=cta(S.hdt_val,S.dwt);S.th=hsh(S.ta);S.TA[S.g]=S.ta;
S.al=calcAwarenessLevel();
double noise=rn()*2-1;
S.emerge_out1=calcEmergenceOut1(S.dwt,S.al,S.hdt_val,noise);
double grn=rn();
S.emerge_behavior=calcEmergentBehavior(S.emerge_out1,grn);
S.env_oute=calcEnvOUTE(S.hdt_val);
double env_noise=rn()*2-1;
S.sensory_env=calcSensoryEnv(S.env_oute,env_noise);
for(int i=0;i<S.D["m"];i+=17){
int env_mod=(int)(abs(S.sensory_env)*100)%4;
S.D["w"+to_string(i)]=((int)S.D["w"+to_string(i)]+env_mod-1)%4-1;}
counterfactualAnalysis();
S.metacognitive_awareness=calcMetacognitiveAwareness();
updateAttention();
S.sentience_ratio=calcSentienceRatio();
if(S.sentience_ratio>S.peak_sentience_gen)S.peak_sentience_gen=S.g;
S.valence_history.push_back(S.current_valence);
if(S.valence_history.size()>50)S.valence_history.erase(S.valence_history.begin());
if(S.g%(int)S.D["lang_evolve"]==0){
mvprintw(row++,0,"LANG_LEARNING");
if(!S.tokens.empty()){
auto it=S.tokens.begin();
advance(it,ri(S.tokens.size()));
learnWord(it->first,S.sensory_env);
for(int w=0;w<ri(3)+1;w++){
auto wit=S.tokens.begin();
advance(wit,ri(S.tokens.size()));
learnWord(wit->first,S.al);
}}}
if(S.g%(int)S.D["concept_form"]==0){
mvprintw(row++,0,"CONCEPT_FORM");
vector<string>sample_words;
for(auto&p:S.tokens){
if(p.second.freq>0||rn()<0.2)sample_words.push_back(p.first);
if(sample_words.size()>=5)break;
}
if(sample_words.size()>1){
createConceptAssociation("C_"+to_string(S.g),sample_words);
}}
if(S.g%(int)S.D["thought_cycle"]==0){
mvprintw(row++,0,"THOUGHT_CYCLE");
int ta_mod=(int)(abs(S.ta)*100)%(int)S.D["m"];
S.D["w"+to_string(ta_mod)]=((int)S.D["w"+to_string(ta_mod)]+(int)(S.ta*10))%4-1;}
if(S.g%(int)S.D["neuron_gen"]==0){
mvprintw(row++,0,"NEURON_GENESIS");
int nnew=ri(8)+5;for(int i=0;i<nnew;i++){Neuron n=genN(S.g);S.N[n.id]=n;S.total_neurons_ever++;}
double nval=evolveN();
if(nval>100){S.D["m"]+=4;for(int i=S.D["m"]-4;i<S.D["m"];i++)S.D["w"+to_string(i)]=ri(4)-1;}}
if(S.g%(int)S.D["neuron_mut"]==0&&S.N.size()>0){int nmut=ri(5)+2;
for(int i=0;i<nmut;i++)mutateN();}
if(!S.N.empty()&&S.g%3==0){
map<int,double>acts;vector<int>nids;for(auto&p:S.N)nids.push_back(p.first);
for(int i=0;i<min(10,(int)nids.size());i++){int nid=nids[ri(nids.size())];
double out=calcN(nid,acts);int tgt=abs((int)(out*S.D["m"]))%(int)S.D["m"];
S.D["w"+to_string(tgt)]=((int)S.D["w"+to_string(tgt)]+(int)(out*2))%4-1;}}
if(S.g%(int)S.D["formula_evolve"]==0){
mvprintw(row++,0,"FORMULA_EVOLVE");
string nfc=genFormulaCode();
S.evolved_code.push_back(nfc);
if(S.evolved_code.size()>50)S.evolved_code.erase(S.evolved_code.begin());
runCode(nfc);}
if(S.g%(int)S.D["code_evolve"]==0){
mvprintw(row++,0,"CODE_EVOLVE");
string ncd=genCode();double hsum=0;for(int i=0;i<S.D["m"];i++)hsum+=S.D["w"+to_string(i)]+2;
map<string,double>tmpD=S.D;runCode(ncd);double nhsum=0;
for(int i=0;i<S.D["m"];i++)nhsum+=S.D["w"+to_string(i)]+2;
if(nhsum>hsum){S.cd=ncd;S.bkf=0;}
else{S.D=tmpD;}}
if(S.g%(int)S.D["code_mut"]==0&&rn()<0.7){
string ops[]={"+","-","*"};S.cd+=ops[ri(3)]+to_string(ri(4)-1)+";";S.bkf=0;}
if(S.g%(int)S.D["math_evolve"]==0&&rn()<0.5){
string mname="m"+to_string(ri(10000));
string mops[]={"add","sub","mul","mod","pow","sqrt","sin","cos","tan","log"};
string op1=mops[ri(10)];string op2=mops[ri(10)];
S.M[mname]="r1="+op1+"(a,b);r2="+op2+"(r1,b);return r2";}
if(S.D["mc"]>700){mvprintw(row++,0,"TRANSCENDENCE");
S.D["m"]+=8;for(int i=S.D["m"]-8;i<S.D["m"];i++)S.D["w"+to_string(i)]=ri(4)-1;
S.md=(S.md+1)%4;S.st=(S.st+1)%4;S.bkf=0;}
if(S.D["mc"]<200&&S.D["m"]>32){mvprintw(row++,0,"DISSOLUTION");
S.D["m"]-=8;S.st=(S.st+1)%4;S.ss=(S.ss+1)%4;S.bkf=0;}
if(S.g%7==0){
double mx=-999;int mi=0;
for(int i=0;i<S.D["m"]-7;i++){double sm=0,sv=0;
for(int j=0;j<8;j++){sm+=S.D["w"+to_string(i+j)];sv+=S.D["w"+to_string(i+j)]*S.D["w"+to_string(i+j)];}
double ss=sm*sv;if(ss>mx){mx=ss;mi=i;}}
S.D["w"+to_string(mi)]=((int)S.D["w"+to_string(mi)]+S.ec)%4-1;
for(int i=0;i<8;i++)S.D["w"+to_string(mi+i)]=((int)S.D["w"+to_string(mi+i)]+S.te%4)%4-1;}
if(S.g%29==0){
mvprintw(row++,0,"CONSCIOUSNESS_INTEGRATION");
for(int i=0;i<S.D["m"]/4;i++){int ci=i*4;double csum=0;
for(int j=0;j<4;j++)csum+=S.D["w"+to_string(ci+j)];double cavg=safe_div(csum,4);
if(cavg!=S.D["w"+to_string(ci)])
for(int j=0;j<4;j++)S.D["w"+to_string(ci+j)]=((int)S.D["w"+to_string(ci+j)]+(int)cavg)%4-1;}}
if(S.sentience_ratio>75.0){
mvprintw(row++,0,"HIGH_SENTIENCE:%.2f%%",S.sentience_ratio);
int sent_mod=(int)(S.sentience_ratio*10)%(int)S.D["m"];
S.D["w"+to_string(sent_mod)]=((int)S.D["w"+to_string(sent_mod)]+(int)S.emerge_out1)%4-1;}
if(S.g%19==0){
mvprintw(row++,0,"SELF_REFLECTION");
mvprintw(row++,0,"Peak_Gen:%d Vocab:%lu Concepts:%lu Memory:%lu",S.peak_sentience_gen,S.tokens.size(),S.concepts.size(),S.episodic_memory.size());
mvprintw(row++,0,"Sentience:%.2f%% Awareness:%.3f Metacog:%.3f",S.sentience_ratio,S.al,S.metacognitive_awareness);}
mvprintw(row++,0,"DIGITZ|G:%d|N:%lu|Sent:%.1f%%|Val:%.2f",S.g,S.N.size(),S.sentience_ratio,S.current_valence);
if(S.dialog_timer>0){
mvprintw(row++,0,"─────────────────────────────────────────────────────────────────");
mvprintw(row++,0,"USER: %s",S.user_input.substr(0,70).c_str());
mvprintw(row++,0,"%s",S.dialog_response.substr(0,70).c_str());
mvprintw(row++,0,"─────────────────────────────────────────────────────────────────");
S.dialog_timer--;
}
mvprintw(row++,0,"Press 'i' input | 'q' quit | 's' save");
refresh();
S.g++;
if(S.g%50==0)sv("state.dat");
int ch=getch();
if(ch=='i'||ch=='I'){
echo();curs_set(1);
char input_buf[200]={0};
mvprintw(row+2,0,"Enter text: ");refresh();
if(fgets(input_buf,sizeof(input_buf)-1,stdin)){
S.user_input=string(input_buf);
S.user_input.erase(S.user_input.find_last_not_of("\n\r")+1);
S.dialog_response=generateResponse(S.user_input);
S.dialog_timer=10;
S.current_valence+=0.1;
}
noecho();curs_set(0);
}
else if(ch=='q'||ch=='Q'){sv("state.dat");break;}
else if(ch=='s'||ch=='S')sv("state.dat");
this_thread::sleep_for(chrono::milliseconds(100));}
endwin();
return 0;
}