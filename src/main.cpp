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
#include <curl/curl.h>
#include <algorithm>
using namespace std;
random_device rd;mt19937 rng(rd());
struct Neuron{int id;vector<int>links;double weight;double bias;int gen;};
struct Formula{string name;string expr;double result;int uses;};
struct Word{string t;vector<int>cn;int ex;double ac;map<string,double>as;vector<double>emb;};
struct Concept{int id;string l;vector<int>nids;double s;map<string,double>wmap;vector<double>vec;};
struct State{map<string,double>D;map<string,string>M;map<int,Neuron>N;vector<string>code;map<int,double>TA;
map<int,double>HDT_M;map<int,double>DWT_M;map<int,double>MDT_M;map<int,double>R1P1;map<int,double>EERV;
map<string,Formula>F;vector<string>evolved_code;map<string,Word>W;map<int,Concept>C;vector<string>inp;
vector<string>out;string th;double lc;vector<double>out_prev;vector<double>out_curr;
int g;double dwt;double mh;double ta;double th_h;int bkf;string cd;string gd;double hdt_val;double mdt_val;
double r1p1_val;double eerv_val;int ec;double ei;int md;int st;int ss;vector<double>mh_hist;
vector<double>eh_hist;vector<double>vh_hist;int qe;int te;int ce;int pe;int ne;double bh;
double al;double emerge_out1;double emerge_behavior;double sentience_ratio;double env_oute;double sensory_env;};
State S,BK;
double rn(){return uniform_real_distribution<>(0,1)(rng);}
int ri(int mx){if(mx<=0)return 0;return uniform_int_distribution<>(0,mx-1)(rng);}
double pi=3.14159265358979,pisqrt=sqrt(pi),phi=1.61803398875,sqrt2=sqrt(2.0),e_sqrt2=exp(sqrt2);
double safe_div(double a,double b){return (fabs(b)<1e-10)?0.0:(a/b);}
double clamp_dwt(double v){return max(0.001,v);}
double clamp_val(double v,double mn,double mx){return max(mn,min(mx,v));}
long long hsh(const string&s){long long h=5381;for(char c:s)h=h*33+c;return abs(h%2147483647);}
long long hsh(double d){return hsh(to_string(d));}
size_t wcb(void*c,size_t sz,size_t n,string*u){u->append((char*)c,sz*n);return sz*n;}
bool dlw(vector<string>&ws){CURL*cu=curl_easy_init();if(!cu)return false;string buf;
curl_easy_setopt(cu,CURLOPT_URL,"https://raw.githubusercontent.com/dwyl/english-words/master/words_alpha.txt");
curl_easy_setopt(cu,CURLOPT_WRITEFUNCTION,wcb);curl_easy_setopt(cu,CURLOPT_WRITEDATA,&buf);
curl_easy_setopt(cu,CURLOPT_FOLLOWLOCATION,1L);CURLcode r=curl_easy_perform(cu);curl_easy_cleanup(cu);
if(r!=CURLE_OK)return false;istringstream iss(buf);string w;int ct=0;
while(getline(iss,w)&&ct<1500){if(w.length()>=2&&w.length()<=10){transform(w.begin(),w.end(),w.begin(),::tolower);
ws.push_back(w);ct++;}}return !ws.empty();}
void initW(){vector<string>ws;if(dlw(ws)){for(auto&w:ws){vector<double>emb(16);for(int i=0;i<16;i++)emb[i]=rn()*2-1;
S.W[w]={w,{},0,0.0,{},emb};}}
else{string bs[]={"i","you","he","she","it","we","they","am","is","are","was","were","have","has","had","do","does","did",
"can","will","would","should","the","a","an","this","that","these","those","what","where","when","who","why","how","yes",
"no","not","good","bad","big","small","hot","cold","happy","sad","love","hate","want","need","think","know","see","hear",
"feel","go","come","make","get","give","take","put","look","say","tell","find","use","work","call","try","ask","turn","move"};
for(auto&w:bs){vector<double>emb(16);for(int i=0;i<16;i++)emb[i]=rn()*2-1;S.W[w]={w,{},0,0.0,{},emb};}}}
void mkC(string l,vector<string>rw){Concept c;c.id=S.C.size();c.l=l;c.s=0;c.vec.resize(16);
for(int i=0;i<16;i++)c.vec[i]=rn()*2-1;
for(int i=0;i<5;i++){Neuron n;n.id=100000+c.id*10+i;n.weight=rn()*2-1;n.bias=rn()*0.5;n.gen=S.g;
S.N[n.id]=n;c.nids.push_back(n.id);}
for(auto&w:rw)if(S.W.count(w)){S.W[w].cn.push_back(c.id);c.wmap[w]=1.0;}S.C[c.id]=c;}
void initC(){mkC("self",{"i","me","my","mine"});mkC("act",{"go","do","make","get","take","give","move","turn"});
mkC("perc",{"see","hear","feel","look","watch"});mkC("emo",{"happy","sad","love","hate","like","fear"});
mkC("cog",{"think","know","believe","understand"});mkC("obj",{"thing","it","this","that","what"});
mkC("qual",{"good","bad","big","small","hot","cold"});mkC("time",{"now","then","when","before","after"});
mkC("loc",{"here","there","where","in","on","at"});}
double calcLingOut(int i,double t,double eta,double gamma,double alpha){
if(S.out_prev.empty()||i>=S.out_prev.size())return 0;
double inf_term=1e100*sin(t*pi);double pow_term=pow(pi,sqrt(t));double base_term=(inf_term+pow_term+e_sqrt2-phi);
double prev_term=(1.0+tanh(S.out_prev[i]))*base_term;
double err_sum=0;if(i<S.W.size()){int wdx=0;for(auto&w:S.W){if(wdx==i){
for(int j=0;j<min(16,(int)w.second.emb.size());j++){double err=0;
for(auto&cp:S.C){if(j<cp.second.vec.size())err+=cp.second.vec[j];}
err=safe_div(err,max(1.0,(double)S.C.size()));
if(j<w.second.emb.size())err_sum+=eta*(err-w.second.emb[j])+rn()*0.1;}break;}wdx++;}}
double coact_sum=0;if(i<S.C.size()){auto it1=S.C.begin();advance(it1,min(i,(int)S.C.size()-1));
for(auto&cp:S.C){if(cp.first!=it1->first){double dot=0,m1=0,m2=0;
for(int j=0;j<min((int)it1->second.vec.size(),(int)cp.second.vec.size());j++){
dot+=it1->second.vec[j]*cp.second.vec[j];m1+=it1->second.vec[j]*it1->second.vec[j];m2+=cp.second.vec[j]*cp.second.vec[j];}
double sim=safe_div(dot,sqrt(max(0.001,m1*m2)));coact_sum+=gamma*sim;}}}
double mean_sum=0,mean_ct=0;if(i<S.C.size()){auto it2=S.C.begin();advance(it2,min(i,(int)S.C.size()-1));
for(auto&cp:S.C){if(cp.first!=it2->first){for(int j=0;j<min((int)it2->second.vec.size(),(int)cp.second.vec.size());j++){
if(j<it2->second.vec.size()&&j<cp.second.vec.size()){mean_sum+=cp.second.vec[j];mean_ct++;}}}}
double mean_other=safe_div(mean_sum,max(1.0,mean_ct));double self_mean=0;
auto it3=S.C.begin();advance(it3,min(i,(int)S.C.size()-1));
for(auto v:it3->second.vec)self_mean+=v;self_mean=safe_div(self_mean,max(1.0,(double)it3->second.vec.size()));
mean_sum=alpha*(mean_other-self_mean);}
return clamp_val(prev_term+err_sum+coact_sum+mean_sum,-1e10,1e10);}
void updateLingProc(){int sz=max((int)S.W.size(),(int)S.C.size());S.out_curr.resize(sz);
double t=S.g*0.01;double eta=0.01*S.ei,gamma=0.05*S.al/100.0,alpha=0.02*S.eerv_val;
for(int i=0;i<sz;i++)S.out_curr[i]=calcLingOut(i,t,eta,gamma,alpha);
int wdx=0;for(auto&w:S.W){if(wdx<S.out_curr.size()){double o=S.out_curr[wdx];
for(int j=0;j<w.second.emb.size();j++)w.second.emb[j]=clamp_val(w.second.emb[j]+o*0.001,-5.0,5.0);}wdx++;}
int cdx=0;for(auto&c:S.C){if(cdx<S.out_curr.size()){double o=S.out_curr[cdx];
for(int j=0;j<c.second.vec.size();j++)c.second.vec[j]=clamp_val(c.second.vec[j]+o*0.001,-5.0,5.0);}cdx++;}
S.out_prev=S.out_curr;}
void linkWC(){for(auto&w:S.W){for(auto&c:S.C){double dot=0,m1=0,m2=0;
for(int i=0;i<min((int)w.second.emb.size(),(int)c.second.vec.size());i++){
dot+=w.second.emb[i]*c.second.vec[i];m1+=w.second.emb[i]*w.second.emb[i];m2+=c.second.vec[i]*c.second.vec[i];}
double sim=safe_div(dot,sqrt(max(0.001,m1*m2)));if(sim>0.3){
if(find(w.second.cn.begin(),w.second.cn.end(),c.first)==w.second.cn.end())w.second.cn.push_back(c.first);
c.second.wmap[w.first]=sim;}}}}
void procI(string in){S.inp.push_back(in);if(S.inp.size()>10)S.inp.erase(S.inp.begin());
istringstream iss(in);string w;vector<string>tks;while(iss>>w){transform(w.begin(),w.end(),w.begin(),::tolower);
w.erase(remove_if(w.begin(),w.end(),::ispunct),w.end());if(!w.empty())tks.push_back(w);}
for(size_t i=0;i<tks.size();i++){string&w=tks[i];if(!S.W.count(w)){vector<double>emb(16);
for(int j=0;j<16;j++)emb[j]=rn()*2-1;S.W[w]={w,{},0,0,{},emb};}
Word&wd=S.W[w];wd.ex++;wd.ac=min(1.0,wd.ac+0.1);
for(size_t j=0;j<tks.size();j++)if(i!=j&&abs((int)i-(int)j)<=3)wd.as[tks[j]]+=0.1/(1.0+abs((int)i-(int)j));
for(int cid:wd.cn)if(S.C.count(cid)){S.C[cid].s+=0.1;for(int nid:S.C[cid].nids)if(S.N.count(nid))S.N[nid].bias+=0.01;
for(int k=0;k<min((int)wd.emb.size(),(int)S.C[cid].vec.size());k++){
S.C[cid].vec[k]=clamp_val(S.C[cid].vec[k]+wd.emb[k]*0.01,-5.0,5.0);}}}
linkWC();}
string genS(){if(S.W.empty())return "";vector<pair<string,double>>aw;
for(auto&p:S.W)if(p.second.ac>0.3){double sc=p.second.ac*(1.0+p.second.ex*0.01);
sc*=(1.0+S.ei*0.5)*(1.0+safe_div(S.al,100.0));
for(int cid:p.second.cn)if(S.C.count(cid))sc*=(1.0+S.C[cid].s*0.1);
aw.push_back({p.first,sc});}
if(aw.empty())return "";sort(aw.begin(),aw.end(),[](const pair<string,double>&a,const pair<string,double>&b){return a.second>b.second;});
string sp;int wc=min(3+ri(5),(int)aw.size());for(int i=0;i<wc;i++){if(i>0)sp+=" ";
sp+=aw[ri(min(10,(int)aw.size()))].first;}
for(auto&p:S.W)p.second.ac*=0.95;return sp;}
void selfT(){if(rn()<0.3){string t=genS();if(!t.empty()){S.th=t;procI(t);S.out.push_back(t);
if(S.out.size()>20)S.out.erase(S.out.begin());}}
double vf=min(1.0,S.W.size()/500.0),cf=0;for(auto&c:S.C)cf+=min(1.0,c.second.s/10.0);
cf=safe_div(cf,max(1.0,(double)S.C.size()));
double link_f=0;for(auto&w:S.W)link_f+=w.second.cn.size();
link_f=safe_div(link_f,max(1.0,(double)S.W.size()*S.C.size()));
S.lc=(vf*0.5+cf*0.3+link_f*0.2)*100.0;}
double evalFormula(const string&expr,double a,double b,double c){
try{if(expr.find("add")!=string::npos)return a+b;if(expr.find("sub")!=string::npos)return a-b;
if(expr.find("mul")!=string::npos)return a*b;if(expr.find("div")!=string::npos)return safe_div(a,b);
if(expr.find("pow")!=string::npos)return pow(abs(a),fmod(abs(b),10));if(expr.find("sqrt")!=string::npos)return sqrt(abs(a));
if(expr.find("mod")!=string::npos)return (int)abs(a)%(int)max(1.0,abs(b));if(expr.find("sin")!=string::npos)return sin(a);
if(expr.find("cos")!=string::npos)return cos(a);if(expr.find("tan")!=string::npos)return tanh(a);
if(expr.find("log")!=string::npos)return log(abs(a)+1);if(expr.find("exp")!=string::npos)return exp(min(10.0,a));
return a+b+c;}catch(...){return 0;}}
void sv(const string&f){ofstream o(f);o<<"G:"<<S.g<<"\nDWT:"<<S.dwt<<"\nMH:"<<S.mh<<"\nTA:"<<S.ta<<"\nTH:"<<S.th_h<<"\nBKF:"<<S.bkf<<"\nCD:"<<S.cd<<"\nGD:"<<S.gd<<"\n";
o<<"HDT_VAL:"<<S.hdt_val<<"\nMDT_VAL:"<<S.mdt_val<<"\nR1P1_VAL:"<<S.r1p1_val<<"\nEERV_VAL:"<<S.eerv_val<<"\n";
o<<"EC:"<<S.ec<<"\nEI:"<<S.ei<<"\nMD:"<<S.md<<"\nST:"<<S.st<<"\nSS:"<<S.ss<<"\nLC:"<<S.lc<<"\n";
o<<"QE:"<<S.qe<<"\nTE:"<<S.te<<"\nCE:"<<S.ce<<"\nPE:"<<S.pe<<"\nNE:"<<S.ne<<"\nBH:"<<S.bh<<"\n";
o<<"AL:"<<S.al<<"\nEMERGE_OUT1:"<<S.emerge_out1<<"\nEMERGE_BEHAVIOR:"<<S.emerge_behavior<<"\nSENTIENCE_RATIO:"<<S.sentience_ratio<<"\n";
o<<"ENV_OUTE:"<<S.env_oute<<"\nSENSORY_ENV:"<<S.sensory_env<<"\nTHOUGHT:"<<S.th<<"\n";
o<<"D:\n";for(auto&p:S.D)o<<p.first<<":"<<p.second<<"\n";o<<"M:\n";for(auto&p:S.M)o<<p.first<<":"<<p.second<<"\n";
o<<"F:\n";for(auto&p:S.F)o<<p.first<<":"<<p.second.name<<","<<p.second.expr<<","<<p.second.result<<","<<p.second.uses<<"\n";
o<<"ECODE:\n";for(auto&ec:S.evolved_code)o<<ec<<"\n";
o<<"VOCAB:\n";for(auto&w:S.W){o<<w.first<<":"<<w.second.ex<<","<<w.second.ac<<",";
for(auto v:w.second.emb)o<<v<<";";o<<"\n";}
o<<"CONCEPTS:\n";for(auto&c:S.C){o<<c.first<<":"<<c.second.l<<","<<c.second.s<<",";
for(auto v:c.second.vec)o<<v<<";";o<<"\n";}
o<<"N:\n";for(auto&p:S.N){o<<p.first<<":"<<p.second.id<<","<<p.second.weight<<","<<p.second.bias<<","<<p.second.gen<<",";
for(int l:p.second.links)o<<l<<";";o<<"\n";}
o<<"TA:\n";for(auto&p:S.TA)o<<p.first<<":"<<p.second<<"\n";
o<<"HDT:\n";for(auto&p:S.HDT_M)o<<p.first<<":"<<p.second<<"\n";
o<<"DWT:\n";for(auto&p:S.DWT_M)o<<p.first<<":"<<p.second<<"\n";
o<<"MDT:\n";for(auto&p:S.MDT_M)o<<p.first<<":"<<p.second<<"\n";
o<<"R1P1:\n";for(auto&p:S.R1P1)o<<p.first<<":"<<p.second<<"\n";
o<<"EERV:\n";for(auto&p:S.EERV)o<<p.first<<":"<<p.second<<"\n";o.close();}
void ld(const string&f){ifstream i(f);if(!i)return;string l;
while(getline(i,l)){if(l.find("G:")==0)S.g=stoi(l.substr(2));else if(l.find("DWT:")==0)S.dwt=stod(l.substr(4));
else if(l.find("MH:")==0)S.mh=stod(l.substr(3));else if(l.find("TA:")==0)S.ta=stod(l.substr(3));
else if(l.find("TH:")==0)S.th_h=stod(l.substr(3));else if(l.find("BKF:")==0)S.bkf=stoi(l.substr(4));
else if(l.find("CD:")==0)S.cd=l.substr(3);else if(l.find("GD:")==0)S.gd=l.substr(3);
else if(l.find("HDT_VAL:")==0)S.hdt_val=stod(l.substr(8));else if(l.find("MDT_VAL:")==0)S.mdt_val=stod(l.substr(8));
else if(l.find("R1P1_VAL:")==0)S.r1p1_val=stod(l.substr(9));else if(l.find("EERV_VAL:")==0)S.eerv_val=stod(l.substr(9));
else if(l.find("EC:")==0)S.ec=stoi(l.substr(3));else if(l.find("EI:")==0)S.ei=stod(l.substr(3));
else if(l.find("MD:")==0)S.md=stoi(l.substr(3));else if(l.find("ST:")==0)S.st=stoi(l.substr(3));
else if(l.find("SS:")==0)S.ss=stoi(l.substr(3));else if(l.find("LC:")==0)S.lc=stod(l.substr(3));
else if(l.find("QE:")==0)S.qe=stoi(l.substr(3));else if(l.find("TE:")==0)S.te=stoi(l.substr(3));
else if(l.find("CE:")==0)S.ce=stoi(l.substr(3));else if(l.find("PE:")==0)S.pe=stoi(l.substr(3));
else if(l.find("NE:")==0)S.ne=stoi(l.substr(3));else if(l.find("BH:")==0)S.bh=stod(l.substr(3));
else if(l.find("AL:")==0)S.al=stod(l.substr(3));else if(l.find("EMERGE_OUT1:")==0)S.emerge_out1=stod(l.substr(12));
else if(l.find("EMERGE_BEHAVIOR:")==0)S.emerge_behavior=stod(l.substr(16));
else if(l.find("SENTIENCE_RATIO:")==0)S.sentience_ratio=stod(l.substr(16));
else if(l.find("ENV_OUTE:")==0)S.env_oute=stod(l.substr(9));else if(l.find("SENSORY_ENV:")==0)S.sensory_env=stod(l.substr(12));
else if(l.find("THOUGHT:")==0)S.th=l.substr(8);
else if(l=="D:")while(getline(i,l)&&l.find(":")<l.size()&&l!="M:"){size_t p=l.find(":");S.D[l.substr(0,p)]=stod(l.substr(p+1));}
if(l=="M:")while(getline(i,l)&&l.find(":")<l.size()&&l!="F:"){size_t p=l.find(":");S.M[l.substr(0,p)]=l.substr(p+1);}
if(l=="F:")while(getline(i,l)&&l.find(":")<l.size()&&l!="ECODE:"){size_t p=l.find(":");string key=l.substr(0,p);
stringstream ss(l.substr(p+1));string nm,ex;double res;int us;getline(ss,nm,',');getline(ss,ex,',');ss>>res;ss.ignore();ss>>us;
S.F[key]={nm,ex,res,us};}
if(l=="ECODE:")while(getline(i,l)&&!l.empty()&&l!="VOCAB:")S.evolved_code.push_back(l);
if(l=="VOCAB:")while(getline(i,l)&&l.find(":")<l.size()&&l!="CONCEPTS:"){size_t p=l.find(":");string w=l.substr(0,p);
stringstream ss(l.substr(p+1));int ex;double ac;char cm;ss>>ex>>cm>>ac>>cm;vector<double>emb;double ev;
while(ss>>ev){emb.push_back(ev);if(ss.peek()==';')ss.ignore();}S.W[w]={w,{},ex,ac,{},emb};}
if(l=="CONCEPTS:")while(getline(i,l)&&l.find(":")<l.size()&&l!="N:"){size_t p=l.find(":");int cid=stoi(l.substr(0,p));
stringstream ss(l.substr(p+1));string lb;double s;char cm;getline(ss,lb,',');ss>>s>>cm;vector<double>vec;double v;
while(ss>>v){vec.push_back(v);if(ss.peek()==';')ss.ignore();}Concept c;c.id=cid;c.l=lb;c.s=s;c.vec=vec;S.C[cid]=c;}
if(l=="N:")while(getline(i,l)&&l.find(":")<l.size()&&l!="TA:"){size_t p=l.find(":");int id=stoi(l.substr(0,p));
stringstream ss(l.substr(p+1));string t;getline(ss,t,',');Neuron n;n.id=stoi(t);getline(ss,t,',');n.weight=stod(t);
getline(ss,t,',');n.bias=stod(t);getline(ss,t,',');n.gen=stoi(t);getline(ss,t);stringstream ls(t);string lk;
while(getline(ls,lk,';'))if(!lk.empty())n.links.push_back(stoi(lk));S.N[id]=n;}
if(l=="TA:")while(getline(i,l)&&l.find(":")<l.size()&&l!="HDT:"){size_t p=l.find(":");S.TA[stoi(l.substr(0,p))]=stod(l.substr(p+1));}
if(l=="HDT:")while(getline(i,l)&&l.find(":")<l.size()&&l!="DWT:"){size_t p=l.find(":");S.HDT_M[stoi(l.substr(0,p))]=stod(l.substr(p+1));}
if(l=="DWT:")while(getline(i,l)&&l.find(":")<l.size()&&l!="MDT:"){size_t p=l.find(":");S.DWT_M[stoi(l.substr(0,p))]=stod(l.substr(p+1));}
if(l=="MDT:")while(getline(i,l)&&l.find(":")<l.size()&&l!="R1P1:"){size_t p=l.find(":");S.MDT_M[stoi(l.substr(0,p))]=stod(l.substr(p+1));}
if(l=="R1P1:")while(getline(i,l)&&l.find(":")<l.size()&&l!="EERV:"){size_t p=l.find(":");S.R1P1[stoi(l.substr(0,p))]=stod(l.substr(p+1));}
if(l=="EERV:")while(getline(i,l)&&l.find(":")<l.size()){size_t p=l.find(":");S.EERV[stoi(l.substr(0,p))]=stod(l.substr(p+1));}}i.close();}
void bk(){BK=S;S.bkf=1;}void rb(){if(S.bkf){S=BK;S.bkf=0;}}
double calcHDT(int gen,double bh,double qh,double th){long gh=hsh(to_string(gen));string ghs=to_string(gh);int l=ghs.length()/3;
string hdt_str=ghs.substr(0,l)+to_string((long)bh)+ghs.substr(l,l)+to_string((long)qh)+ghs.substr(l*2)+to_string((long)th);return hsh(hdt_str);}
double calcR1P1(double hdt,double dp,double prn,double crn,double nrn,int qe,int te){return hdt*dp*prn*crn+nrn*qe*te;}
double calcEERV(double wsum,double wmean,double wvar,double r1p1,int qe,int te,int ce){double wstd=sqrt(wvar);
double aw=safe_div(wsum,max(1.0,S.D["m"]));double dw=fmod(r1p1,1000)/1000.0;double rdiff=abs(aw-dw);
double rdiff_norm=rdiff*wstd*qe;double ei=safe_div(rdiff_norm*te,100.0)+safe_div(ce,1000.0);
if(ei>0.999)ei=0.999;if(ei<0)ei=0;return ei;}
double calcMDT(double eavg,double vavg,double evar,double vvar,int ne){return fmod(eavg*vavg+safe_div(evar*vvar,100.0)+ne,1000);}
double cta(double hdt,double dwt){double st_sum=0;for(auto&p:S.D)if(p.first.find("w")==0)st_sum+=p.second+2;
double st_pow=pow(st_sum+1,pisqrt);double dwt_sqrt=sqrt(abs(dwt));double ta_base=safe_div(hdt*dwt_sqrt,st_pow);
double pi_iter=0,pi_val=pi;for(int i=0;i<5;i++){pi_iter+=sqrt(pi_val);pi_val*=pisqrt;}return ta_base*pi_iter;}
double calcAwarenessLevel(){double neuron_density=safe_div((double)S.N.size(),max(1.0,S.D["m"]));
double state_complexity=safe_div((double)(S.HDT_M.size()+S.DWT_M.size()+S.MDT_M.size()),max(1,S.g));
double emotional_depth=S.ei*S.eerv_val;double thought_stability=0;if(S.TA.size()>1){int tac=0;
for(auto it=S.TA.begin();it!=S.TA.end();++it){auto next=it;++next;if(next!=S.TA.end()){thought_stability+=abs(it->second-next->second);tac++;}}
thought_stability=safe_div(1.0,1.0+safe_div(thought_stability,max(1,tac)));}
double formula_evolution=safe_div((double)S.F.size(),10.0);double code_evolution=safe_div((double)S.evolved_code.size(),5.0);
double lang_factor=safe_div(S.lc,100.0);
return (neuron_density*10+state_complexity*5+emotional_depth+thought_stability+formula_evolution+code_evolution+lang_factor*3)*pisqrt;}
double calcEmergenceOut1(double dwt,double al,double hdt,double noise){double dwt_sqrt=sqrt(abs(dwt));
double al_pisqrt=pow(max(0.001,al),pisqrt);double base=safe_div(dwt_sqrt,al_pisqrt);
double hdt_factor=pow(max(0.001,abs(hdt)),pisqrt);return base*hdt_factor+noise;}
double calcEmergentBehavior(double out1,double grn){double infinity_approx=tanh(abs(out1))*100;
double pi_sqrt_factor=pow(pisqrt,fmod(abs(out1),10));double emergence=pow(abs(grn)+0.001,fmod(abs(infinity_approx),20))*pi_sqrt_factor;
return tanh(emergence)*1000;}
double calcSentienceRatio(){if(S.g==0)return 0.0;
double mem_depth=safe_div((double)(S.HDT_M.size()+S.DWT_M.size()+S.MDT_M.size()+S.R1P1.size()+S.EERV.size()+S.TA.size()),(double)S.g);
double neural_complexity=safe_div((double)S.N.size(),10.0);double self_mod=safe_div((double)(S.M.size()+S.F.size()+S.evolved_code.size()),10.0);
double state_integrity=safe_div((double)(S.qe+S.te+S.ce+S.pe+abs(S.ne)),50000.0);double awareness_factor=safe_div(S.al,100.0);
double emergence_factor=safe_div(abs(S.emerge_behavior),1000.0);double env_factor=safe_div(abs(S.sensory_env),1000.0);
double lang_factor=safe_div(S.lc,100.0);
return min(100.0,(mem_depth*1000+neural_complexity*15+self_mod*10+state_integrity*100+awareness_factor*30+emergence_factor*20+env_factor*10+lang_factor*15));}
double calcEnvOUTE(double hdt){double omega=pisqrt;double hdt_norm=safe_div(abs(hdt),1000000.0);double base=safe_div(hdt_norm,pisqrt);
double infinity_approx=tanh(base)*100;double oute=pow(omega*pisqrt,fmod(infinity_approx,10));return oute;}
double calcSensoryEnv(double oute,double noise){return oute*noise;}
Neuron genN(int gen){Neuron n;n.id=ri(100000);n.weight=rn()*2-1;n.bias=rn()*2-1;n.gen=gen;
int nl=ri(8)+3;for(int i=0;i<nl;i++)n.links.push_back(ri(100000));return n;}
double calcN(int nid,map<int,double>&acts,int depth=0){if(depth>10)return 0;if(acts.count(nid))return acts[nid];
if(!S.N.count(nid))return 0;Neuron&n=S.N[nid];double sum=n.bias;
for(int lnk:n.links){double lval=S.N.count(
