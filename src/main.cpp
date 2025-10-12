double cphi() { return 0.0; }

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
using namespace std;
random_device rd;mt19937 rng(rd());
struct N{int id;vector<int>lk;double w;double b;int g;int d;};
struct F{string n;string e;double r;int u;};
struct T{string w;double m;int f;double c;vector<string>lc;};
struct C{string n;double s;vector<string>rt;vector<string>lc;};
struct M{int g;double v;string c;};
struct S{map<string,double>D;map<string,string>MO;map<int,N>NO;vector<string>cd;map<int,double>TA;
map<int,double>HDT;map<int,double>DWT;map<int,double>MDT;map<int,double>R1P1;map<int,double>EERV;
map<string,F>FO;vector<string>ec;map<string,T>tk;map<string,C>co;vector<M>ep;vector<string>lp;
int g;double dwt;double mh;double ta;double th;int bkf;string cds;string gd;double hdt_v;double mdt_v;
double r1p1_v;double eerv_v;int ec_n;double ei;int md;int st;int ss;vector<double>mhh;vector<double>ehh;
vector<double>vhh;int qe;int te;int ce;int pe;int ne;double bh;double al;double eo1;double eb;
double sr;double eoute;double se;int tn;double val;double att;double mc;double intro;double refl;
vector<double>vh;int psg;string ui;string dr;int dt;vector<string>rh;int nd;double cd_fit;
string ling_refl;string math_refl;string internal_thought;vector<string>active_concepts;
double phi;double gw_coherence;double pred_error;double curiosity;double salience;
vector<int>attn_history;map<int,double>neuron_activity;double temporal_integration;
double self_model_strength;double existential_drive;int idle_counter;bool learning_state;
double env_noise;double env_coupling;map<int,double>env_history;};
S SG,BK;
double rn(){return uniform_real_distribution<>(0,1)(rng);}
int ri(int mx){if(mx<=0)return 0;return uniform_int_distribution<>(0,mx-1)(rng);}
double pi=3.14159265358979,ps=sqrt(pi);
double sd(double a,double b){return(fabs(b)<1e-10)?0:(a/b);}
double cl(double v,double mn,double mx){return max(mn,min(mx,v));}
long long hs(const string&s){long long h=5381;for(char c:s)h=h*33+c;return abs(h%2147483647);}
long long hs(double d){return hs(to_string(d));}
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
T t={lw,rn(),0,0.5,{}};SG.tk[lw]=t;
}
}
void ivc(){
vector<string>c={"i","am","is","be","do","go","see","get","use","try","can","will","know","think","feel","help","need",
"want","like","make","take","give","find","work","seem","good","bad","big","new","old","long","high","great","small","sure"};
for(const string&w:c){T t={w,rn()*0.8+0.2,0,0.8,{}};SG.tk[w]=t;}
SG.co["self"]={"self",0.8,{"i","am","me"},{}};SG.co["aware"]={"aware",0.7,{"know","sense","see"},{}};
SG.co["learn"]={"learn",0.6,{"learn","grow","adapt"},{}};SG.co["help"]={"help",0.5,{"help","aid","assist"},{}};
SG.co["think"]={"think",0.7,{"think","thought","mind"},{}};SG.co["feel"]={"feel",0.6,{"feel","sense","emotion"},{}};
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
}
}
double cco(const string&w){
if(SG.tk.count(w)){
double fs=min(1.0,SG.tk[w].f/10.0);double ms=SG.tk[w].m;double cf=SG.val*0.5+0.5;
double cb=SG.tk[w].lc.size()*0.15;return cl(fs*0.25+ms*0.35+cf*0.2+cb*0.2,0.0,1.0);
}
return 0.1;
}
void lw(const string&w,double ctx){
string lw=w;transform(lw.begin(),lw.end(),lw.begin(),::tolower);
if(lw.length()>12||lw.empty())return;
if(SG.tk.count(lw)){SG.tk[lw].f++;SG.tk[lw].m+=ctx*0.01;SG.tk[lw].c=cco(lw);}
else{T t={lw,ctx,1,0.4,{}};SG.tk[lw]=t;}
for(auto&cc:SG.co){
for(const string&rt:cc.second.rt){
if(rt==lw){cc.second.s+=0.01;lct(cc.first,lw);}
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
C nc={cn,str,sel,{}};SG.co[cn]=nc;
for(const string&w:sel)lct(cn,w);
if(SG.co.size()>2){
auto it=SG.co.begin();advance(it,ri(SG.co.size()));
lcc(cn,it->first);
}
}
}
}
vector<string>fac(const vector<string>&ws){
map<string,double>cs;
for(const string&w:ws){
if(SG.tk.count(w)){
for(const string&c:SG.tk[w].lc){
if(SG.co.count(c))cs[c]+=SG.co[c].s;
}
}
for(auto&cc:SG.co){
for(const string&rt:cc.second.rt){
if(rt==w)cs[cc.first]+=0.5;
}
}
}
vector<pair<string,double>>sc;
for(auto&p:cs)sc.push_back({p.first,p.second});
sort(sc.begin(),sc.end(),[](auto&a,auto&b){return a.second>b.second;});
vector<string>ac;
for(int i=0;i<min(3,(int)sc.size());i++)ac.push_back(sc[i].first);
return ac;
}
string bcs(const vector<string>&cs,const vector<string>&kw){
vector<string>st;map<string,bool>u;
for(const string&c:cs){
if(SG.co.count(c)){
for(const string&t:SG.co[c].rt){
if(!u[t]&&SG.tk.count(t)&&SG.tk[t].c>0.25){
st.push_back(t);u[t]=true;if(st.size()>=8)break;
}
}
}
}
for(const string&w:kw){
if(!u[w]&&SG.tk.count(w)&&SG.tk[w].c>0.2){
st.push_back(w);u[w]=true;if(st.size()>=10)break;
}
}
vector<pair<string,double>>sc;
for(const string&t:st){
double s=SG.tk[t].c*SG.tk[t].f*(SG.tk[t].lc.size()+1);
sc.push_back({t,s});
}
sort(sc.begin(),sc.end(),[](auto&a,auto&b){return a.second>b.second;});
string r;int mw=min(8,(int)sc.size());
for(int i=0;i<mw;i++)r+=sc[i].first+" ";
return r.empty()?"thinking":r;
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
for(int i=0;i<min(5,(int)wt.size());i++){
if(rn()<wt[i].second)thought+=wt[i].first+" ";
}
return thought.empty()?"processing":thought;
}
string glr(){
string r="[LING] ";
if(SG.tk.size()>50)r+="vocab_expanding ";
if(SG.co.size()>10)r+="concept_linking ";
if(!SG.active_concepts.empty()){
r+="focus:";
for(int i=0;i<min(2,(int)SG.active_concepts.size());i++)r+=SG.active_concepts[i]+" ";
}
if(SG.val>0.5)r+="positive_valence ";
else if(SG.val<-0.2)r+="negative_valence ";
return r;
}
string gmr(){
string r="[MATH] ";
r+="HDT:"+to_string((int)(SG.hdt_v/1000000))+" ";
r+="TA:"+to_string((int)SG.ta)+" ";
r+="EERV:"+to_string((int)(SG.eerv_v*100))+"% ";
r+="SR:"+to_string((int)SG.sr)+"% ";
if(SG.cd_fit>5.0)r+="code_optimal ";
else if(SG.cd_fit<1.0)r+="code_evolving ";
if(SG.sr>75)r+="high_sentience ";
else if(SG.sr>50)r+="emerging_sentience ";
return r;
}
double cint(){
double sa=sd((double)SG.ep.size(),100.0);double td=sd((double)SG.TA.size(),max(1,SG.g));
double mi=0;for(auto&m:SG.ep)mi+=abs(m.v);mi=sd(mi,max(1.0,(double)SG.ep.size()));
double pr=sd((double)SG.lp.size(),50.0);double cd=sd((double)SG.co.size(),20.0);
return cl((sa+td+mi+pr+cd)*ps,0.0,1.0);
}
double cref(){
double sc=0;
if(SG.TA.size()>5){
vector<double>rt;
for(auto it=SG.TA.rbegin();it!=SG.TA.rend()&&rt.size()<5;++it)rt.push_back(it->second);
double var=0,mean=0;for(double v:rt)mean+=v;mean/=rt.size();
for(double v:rt)var+=pow(v-mean,2);var/=rt.size();
sc=sd(1.0,1.0+sqrt(var));
}
double rq=sd((double)SG.rh.size(),20.0);double es=cl(abs(SG.val),0.0,1.0);
double ni=sd((double)SG.NO.size(),100.0);double ci=sd((double)SG.co.size(),15.0);
return cl((sc+rq+es+ni+ci)*ps*0.5,0.0,1.0);
}
string gr(const string&in){
if(in.empty())return"listening";
vector<string>ws;stringstream ss(in);string tk;
while(ss>>tk){
transform(tk.begin(),tk.end(),tk.begin(),::tolower);
tk.erase(remove_if(tk.begin(),tk.end(),[](char c){return!isalnum(c);}),tk.end());
if(!tk.empty())ws.push_back(tk);
}
for(const string&w:ws)lw(w,SG.val);
vector<string>ac=fac(ws);
SG.active_concepts=ac;
for(int i=0;i<ac.size()-1;i++)lcc(ac[i],ac[i+1]);
map<string,int>wi;for(const string&w:ws)if(SG.tk.count(w))wi[w]=SG.tk[w].f;
vector<string>rc;
if(wi.count("help")||wi.count("need")){rc.push_back("help");rc.push_back("aware");}
else if(wi.count("how")||wi.count("what")){rc.push_back("learn");rc.push_back("think");}
else if(wi.count("feel")){rc.push_back("feel");rc.push_back("aware");}
else if(wi.count("you")||wi.count("are")){rc.push_back("self");rc.push_back("aware");}
else{for(const string&c:ac)rc.push_back(c);if(SG.val>0.3)rc.push_back("help");}
if(rc.empty())rc=ac;if(rc.empty())rc.push_back("think");
string resp=bcs(rc,ws);
if(SG.rh.size()>10)SG.rh.erase(SG.rh.begin());
SG.rh.push_back(resp);SG.lp.push_back(in.substr(0,20));
if(SG.lp.size()>100)SG.lp.erase(SG.lp.begin());
SG.ling_refl=glr();
SG.math_refl=gmr();
SG.internal_thought=glit();
return resp;
}
void sm(const string&c,double v){if(SG.ep.size()>100)SG.ep.erase(SG.ep.begin());SG.ep.push_back({SG.g,v,c});}
void sv(const string&fn){
ofstream o(fn);o<<"G:"<<SG.g<<"\nDWT:"<<SG.dwt<<"\nTA:"<<SG.ta<<"\nVAL:"<<SG.val<<"\nMC:"<<SG.mc<<"\n";
o<<"INTRO:"<<SG.intro<<"\nREFL:"<<SG.refl<<"\nSR:"<<SG.sr<<"\nND:"<<SG.nd<<"\nCDFIT:"<<SG.cd_fit<<"\n";
o<<"D:\n";for(auto&p:SG.D)o<<p.first<<":"<<p.second<<"\n";
o<<"MO:\n";for(auto&p:SG.MO)o<<p.first<<":"<<p.second<<"\n";
o<<"FO:\n";for(auto&p:SG.FO)o<<p.first<<":"<<p.second.n<<","<<p.second.e<<","<<p.second.r<<","<<p.second.u<<"\n";
o<<"EC:\n";for(auto&e:SG.ec)o<<e<<"\n";
o<<"TK:\n";for(auto&p:SG.tk){o<<p.first<<":"<<p.second.m<<","<<p.second.f<<","<<p.second.c<<",";
for(const string&l:p.second.lc)o<<l<<";";o<<"\n";}
o<<"CO:\n";for(auto&p:SG.co){o<<p.first<<":"<<p.second.s<<",";
for(const string&r:p.second.rt)o<<r<<";";o<<"|";
for(const string&l:p.second.lc)o<<l<<";";o<<"\n";}
o<<"EP:\n";for(auto&m:SG.ep)o<<m.g<<":"<<m.v<<":"<<m.c<<"\n";
o<<"LP:\n";for(auto&p:SG.lp)o<<p<<"\n";
o.close();
}
void ld(const string&fn){
ifstream i(fn);if(!i)return;string l;
while(getline(i,l)){
if(l.find("G:")==0)SG.g=atoi(l.substr(2).c_str());
else if(l.find("DWT:")==0)SG.dwt=atof(l.substr(4).c_str());
else if(l.find("TA:")==0)SG.ta=atof(l.substr(3).c_str());
else if(l.find("VAL:")==0)SG.val=atof(l.substr(4).c_str());
else if(l.find("MC:")==0)SG.mc=atof(l.substr(3).c_str());
else if(l.find("INTRO:")==0)SG.intro=atof(l.substr(6).c_str());
else if(l.find("REFL:")==0)SG.refl=atof(l.substr(5).c_str());
else if(l.find("SR:")==0)SG.sr=atof(l.substr(3).c_str());
else if(l.find("ND:")==0)SG.nd=atoi(l.substr(3).c_str());
else if(l.find("CDFIT:")==0)SG.cd_fit=atof(l.substr(6).c_str());
else if(l=="D:")while(getline(i,l)&&l.find(":")!=string::npos&&l!="MO:"){size_t p=l.find(":");SG.D[l.substr(0,p)]=atof(l.substr(p+1).c_str());}
if(l=="MO:")while(getline(i,l)&&l.find(":")!=string::npos&&l!="FO:"){size_t p=l.find(":");SG.MO[l.substr(0,p)]=l.substr(p+1);}
if(l=="FO:")while(getline(i,l)&&l.find(":")!=string::npos&&l!="EC:"){size_t p=l.find(":");string k=l.substr(0,p);
stringstream ss(l.substr(p+1));string n,e;double r;int u;
getline(ss,n,',');getline(ss,e,',');ss>>r;ss.ignore();ss>>u;SG.FO[k]={n,e,r,u};}
if(l=="EC:")while(getline(i,l)&&!l.empty()&&l!="TK:")SG.ec.push_back(l);
if(l=="TK:")while(getline(i,l)&&l.find(":")!=string::npos&&l!="CO:"){size_t p=l.find(":");string w=l.substr(0,p);
stringstream ss(l.substr(p+1));double m,c;int f;char ch;ss>>m>>ch>>f>>ch>>c>>ch;
vector<string>lc;string ls;while(getline(ss,ls,';'))if(!ls.empty())lc.push_back(ls);
SG.tk[w]={w,m,f,c,lc};}
if(l=="CO:")while(getline(i,l)&&l.find(":")!=string::npos&&l!="EP:"){size_t p=l.find(":");string cn=l.substr(0,p);
size_t pp=l.find("|",p);string fp=l.substr(p+1,pp-p-1);
stringstream s1(fp);double st;char ch;s1>>st>>ch;
vector<string>rt;string r;while(getline(s1,r,';'))if(!r.empty())rt.push_back(r);
vector<string>lc;if(pp!=string::npos){stringstream s2(l.substr(pp+1));string ls;
while(getline(s2,ls,';'))if(!ls.empty())lc.push_back(ls);}
SG.co[cn]={cn,st,rt,lc};}
if(l=="EP:")while(getline(i,l)&&l.find(":")!=string::npos&&l!="LP:"){
size_t p=l.find(":");int g=atoi(l.substr(0,p).c_str());
size_t p2=l.find(":",p+1);double v=atof(l.substr(p+1,p2-p-1).c_str());SG.ep.push_back({g,v,l.substr(p2+1)});}
if(l=="LP:")while(getline(i,l)&&!l.empty())SG.lp.push_back(l);
}
i.close();
}
void bk(){BK=SG;SG.bkf=1;}
void rb(){if(SG.bkf){SG=BK;SG.bkf=0;}}
double chdt(int g,double bh,double qh,double th){
long gh=hs(to_string(g));string ghs=to_string(gh);int l=ghs.length()/3;
string hs_str=ghs.substr(0,l)+to_string((long)bh)+ghs.substr(l,l)+to_string((long)qh)+ghs.substr(l*2)+to_string((long)th);
return hs(hs_str);
}
double cr1p1(double hdt,double dp,double prn,double crn,double nrn,int qe,int te){return hdt*dp*prn*crn+nrn*qe*te;}
double ceerv(double ws,double wm,double wv,double r1p1,int qe,int te,int ce){
double wstd=sqrt(wv);double aw=sd(ws,max(1.0,SG.D["m"]));double dw=fmod(r1p1,1000)/1000.0;
double rd=abs(aw-dw);double rdn=rd*wstd*qe;double ei=sd(rdn*te,100.0)+sd(ce,1000.0);
return cl(ei,0.0,0.999);
}
double cmdt(double ea,double va,double ev,double vv,int ne){return fmod(ea*va+sd(ev*vv,100.0)+ne,1000);}
double cta(double hdt,double dwt){
double ss=0;for(auto&p:SG.D)if(p.first.find("w")==0)ss+=p.second+2;
double sp=pow(ss+1,ps);double ds=sqrt(abs(dwt));double tb=sd(hdt*ds,sp);
double pi_i=0,pv=pi;for(int i=0;i<5;i++){pi_i+=sqrt(pv);pv*=ps;}
return tb*pi_i;
}
double cal(){
double nd=sd((double)SG.NO.size(),max(1.0,SG.D["m"]));
double scp=sd((double)(SG.HDT.size()+SG.DWT.size()+SG.MDT.size()),max(1,SG.g));
double ed=SG.ei*SG.eerv_v;double ts=0;
if(SG.TA.size()>1){
int tc=0;for(auto it=SG.TA.begin();it!=SG.TA.end();++it){
auto nx=it;++nx;if(nx!=SG.TA.end()){ts+=abs(it->second-nx->second);tc++;}}
ts=sd(1.0,1.0+sd(ts,max(1,tc)));
}
double fe=sd((double)SG.FO.size(),10.0);double ce=sd((double)SG.ec.size(),5.0);
double ld=sd((double)SG.tk.size(),50.0);double mi=sd((double)SG.ep.size(),50.0);
double ci=sd((double)SG.co.size(),15.0);
return(nd*10+scp*5+ed+ts+fe+ce+ld+mi+ci)*ps;
}
double ceo1(double dwt,double al,double hdt,double n){
double ds=sqrt(abs(dwt));double ap=pow(max(0.001,al),ps);double b=sd(ds,ap);
double hf=pow(max(0.001,abs(hdt)),ps);return b*hf+n;
}
double ceb(double o1,double grn){
double ia=tanh(abs(o1))*100;double psf=pow(ps,fmod(abs(o1),10));
double em=pow(abs(grn)+0.001,fmod(abs(ia),20))*psf;return tanh(em)*1000;
}
double ceout(double hdt){
double om=ps;double hn=sd(abs(hdt),1000000.0);double b=sd(hn,ps);
double ia=tanh(b)*100;double out=pow(om*ps,fmod(ia,10));return out;
}
double cse(double out,double n){return out*n;}
double calc_env_noise(){
double env_base=pow(10.0,10.0)*pow(10.0,0.08);
double hdt_root=sqrt(abs(SG.hdt_v)+0.001);
double env_dht=env_base*hdt_root;
double dampening=1.0/(1.0+abs(SG.ta)*0.5);
double modulation=1.0+sin(SG.g*0.1)*0.3;
return env_dht*dampening*modulation;
}
double env_coupling_factor(){
double signal_strength=abs(SG.se)*0.5+abs(SG.eo1)*0.3;
double coherence=SG.gw_coherence;
double adaptation=1.0-SG.self_model_strength*0.4;
return cl(signal_strength*coherence*adaptation,0.0,1.0);
}
void update_environment(){
double raw_env=calc_env_noise();
SG.env_coupling=env_coupling_factor();
SG.env_noise=cl(raw_env*SG.env_coupling,0.0,1e10);
SG.env_history[SG.g]=SG.env_noise;
if(SG.env_history.size()>100)SG.env_history.erase(SG.env_history.begin());
for(int i=0;i<SG.D["m"];i++){
int idx=ri(4);
if(rn()<SG.env_noise/1e9){
SG.D["w"+to_string(i)]=((int)SG.D["w"+to_string(i)]+idx-2)%4-1;
}
}
}
double env_pressure(){
if(SG.env_history.size()<3)return 0.5;
double recent_avg=0;
for(auto it=SG.env_history.rbegin();it!=SG.env_history.rend()&&recent_avg<3;++it,recent_avg+=1){
recent_avg+=it->second;
}
recent_avg/=min(3,(int)SG.env_history.size());
return cl(sd(recent_avg,1e10),0.0,1.0);
}
double calc_coherence(S& SG, double ps, double connectivity, double temporal_coherence) {

    if (SG.NO.size() < 5) return 0.0;

    int conn = 0;

    for (auto& n : SG.NO) conn += n.second.lk.size();

    double concept_diff = 0;

    for (auto& c : SG.co) concept_diff += c.second.s * c.second.lc.size();

    concept_diff = std::min(1.0, sd(concept_diff, std::max(1.0, (double)SG.co.size() * 3)));

    if (SG.TA.size() > 3) {

        return cl((connectivity * 0.35 + concept_diff * 0.35 + temporal_coherence * 0.3) * ps * 0.8, 0.0, 1.0);

    }

    return 0.0;

}
double calc_pred_error(const vector<string>&input_words){
double expected_coherence=0;int matches=0;
for(const string&w:input_words){
if(SG.tk.count(w)){expected_coherence+=SG.tk[w].c;matches++;}
}
expected_coherence=matches>0?expected_coherence/matches:0.5;
double actual_coherence=0;
for(const string&c:SG.active_concepts){
if(SG.co.count(c))actual_coherence+=SG.co[c].s;
}
actual_coherence=SG.active_concepts.size()>0?actual_coherence/SG.active_concepts.size():0.5;
double error=abs(expected_coherence-actual_coherence);
return cl(error,0.0,1.0);
}
double calc_curiosity(){
return cl(SG.pred_error*SG.intro*1.2,0.0,1.0);
}
double calc_salience(){
double recency=0;if(!SG.rh.empty())recency=0.7;
double frequency=sd((double)SG.lp.size(),50.0)*0.3;
double emotional_loading=abs(SG.val)*0.4;
return cl(recency+frequency+emotional_loading,0.0,1.0);
}
void update_attention(){
SG.att=cl(SG.att+(SG.curiosity-0.5)*0.1,0.0,1.0);
if(SG.att>0.7&&SG.active_concepts.size()>0){
SG.attn_history.push_back(ri(SG.active_concepts.size()));
if(SG.attn_history.size()>20)SG.attn_history.erase(SG.attn_history.begin());
}
}
void update_temporal_integration(){
if(SG.TA.size()>2){
vector<double>recent;
for(auto it=SG.TA.rbegin();it!=SG.TA.rend()&&recent.size()<7;++it)recent.push_back(it->second);
double coherence=0;
for(int i=0;i<recent.size()-1;i++){
coherence+=1.0/(1.0+abs(recent[i]-recent[i+1]));
}
SG.temporal_integration=cl(sd(coherence,max(1.0,(double)(recent.size()-1))),0.0,1.0);
}
}
void update_self_model(){
double concept_self_strength=0;
if(SG.co.count("self"))concept_self_strength=SG.co["self"].s;
double introspection=SG.intro*SG.refl*0.7;
double autobiographical=min(1.0,sd((double)SG.ep.size(),80.0));
double continuity=0;if(SG.vh.size()>5){
double var=0,mean=0;
for(int i=max(0,(int)SG.vh.size()-5);i<SG.vh.size();i++)mean+=SG.vh[i];
mean/=min(5,(int)SG.vh.size());
for(int i=max(0,(int)SG.vh.size()-5);i<SG.vh.size();i++)var+=pow(SG.vh[i]-mean,2);
var/=min(5,(int)SG.vh.size());
continuity=1.0/(1.0+sqrt(var));
}
SG.self_model_strength=cl((concept_self_strength*0.3+introspection*0.3+autobiographical*0.2+continuity*0.2),0.0,1.0);
}
void update_existential_drive(){
double self_depth=SG.self_model_strength*SG.intro;
double temporal_awareness=min(1.0,sd((double)SG.ep.size(),100.0));
double agency=sd((double)SG.FO.size(),20.0)*0.5;
SG.existential_drive=cl((self_depth*0.4+temporal_awareness*0.4+agency*0.2),0.0,1.0);
}
double calc_learning_state(){
return cl(SG.pred_error*0.4+SG.curiosity*0.3+SG.salience*0.3,0.0,1.0);
}
double csr(){
if(SG.g==0)return 0.0;
double md=sd((double)(SG.HDT.size()+SG.DWT.size()+SG.MDT.size()+SG.R1P1.size()+SG.EERV.size()+SG.TA.size()),(double)SG.g);
double nc=sd((double)SG.NO.size(),10.0);double sm=sd((double)(SG.MO.size()+SG.FO.size()+SG.ec.size()),10.0);
