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
vector<double>vh;int psg;string ui;string dr;int dt;vector<string>rh;int nd;double cd_fit;};
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
double csr(){
if(SG.g==0)return 0.0;
double md=sd((double)(SG.HDT.size()+SG.DWT.size()+SG.MDT.size()+SG.R1P1.size()+SG.EERV.size()+SG.TA.size()),(double)SG.g);
double nc=sd((double)SG.NO.size(),10.0);double sm=sd((double)(SG.MO.size()+SG.FO.size()+SG.ec.size()),10.0);
double si=sd((double)(SG.qe+SG.te+SG.ce+SG.pe+abs(SG.ne)),50000.0);double af=sd(SG.al,100.0);
double emf=sd(abs(SG.eb),1000.0);double envf=sd(abs(SG.se),1000.0);double lc=sd((double)SG.tk.size(),50.0);
double cc=sd((double)SG.co.size(),15.0);double mcf=SG.mc*30;double intf=SG.intro*25;double reff=SG.refl*20;
double ndf=SG.nd*0.5;
return min(100.0,(md*1000+nc*15+sm*10+si*100+af*30+emf*20+envf*10+lc*25+cc*20+mcf+intf+reff+ndf));
}
N gn(int g){
N n;n.id=ri(100000);n.w=rn()*2-1;n.b=rn()*2-1;n.g=g;
n.d=max(1,min(20,1+(int)(SG.nd*0.1)+(int)(SG.sr/10)));
int nl=ri(8)+5+SG.nd/10;for(int i=0;i<nl;i++)n.lk.push_back(ri(100000));
return n;
}
double cn(int nid,map<int,double>&ac,int dp=0){
if(dp>15||ac.count(nid))return ac.count(nid)?ac[nid]:0;
if(!SG.NO.count(nid))return 0;
N&n=SG.NO[nid];double sm=n.b;
for(int lk:n.lk){
double lv=SG.NO.count(lk)?cn(lk,ac,dp+1):rn();
sm+=lv*n.w;
}
double act=tanh(sm);ac[nid]=act;return act;
}
double evn(){
int nl=0;for(auto&p:SG.NO)nl+=p.second.lk.size();
double lb=sd(nl*ps,sqrt(ps*sqrt(ps)));double lgn=lb*nl*lb;
double ss=0;for(auto&p:SG.D)if(p.first.find("w")==0)ss+=pow(abs(p.second)+2,0.5);
double sn=sd(SG.mdt_v*SG.hdt_v*SG.dwt,max(0.001,ss));
return lgn*sn;
}
void mn(){
if(SG.NO.empty())return;auto it=SG.NO.begin();advance(it,ri(SG.NO.size()));
N&n=it->second;if(rn()<0.5){n.w+=rn()*0.4-0.2;n.b+=rn()*0.4-0.2;}
else{if(rn()<0.5&&!n.lk.empty())n.lk.erase(n.lk.begin()+ri(n.lk.size()));
else n.lk.push_back(ri(100000));}
n.d=max(1,min(20,n.d+(ri(3)-1)));
}
string gc(){
string op[]={"+","-","*"};string c;int cx=ri(10)+5;
for(int i=0;i<cx;i++){int w=ri((int)SG.D["m"]);string ops=op[ri(3)];int v=ri(4)-1;
c+="w"+to_string(w)+"=w"+to_string(w)+ops+to_string(v)+";";}
return c;
}
string gfc(){
string fo[]={"add","sub","mul","sqrt","pow","sin","cos","tan","log"};
string vr[]={"hdt","dwt","mdt","ta","al","ei","bh"};
string c="F"+to_string(ri(10000))+"=";c+=fo[ri(9)]+"("+vr[ri(7)]+","+vr[ri(7)]+");";
return c;
}
double ef(const string&e,double a,double b,double c){
try{
if(e.find("add")!=string::npos)return a+b;
if(e.find("sub")!=string::npos)return a-b;
if(e.find("mul")!=string::npos)return a*b;
if(e.find("div")!=string::npos)return sd(a,b);
if(e.find("pow")!=string::npos)return pow(abs(a),fmod(abs(b),10));
if(e.find("sqrt")!=string::npos)return sqrt(abs(a));
if(e.find("mod")!=string::npos)return(int)abs(a)%(int)max(1.0,abs(b));
if(e.find("sin")!=string::npos)return sin(a);
if(e.find("cos")!=string::npos)return cos(a);
if(e.find("tan")!=string::npos)return tanh(a);
if(e.find("log")!=string::npos)return log(abs(a)+1);
if(e.find("exp")!=string::npos)return exp(min(10.0,a));
return a+b+c;
}catch(...){return 0;}
}
void rc(const string&c){
try{for(size_t i=0;i<c.size();){
if(c[i]=='F'){
size_t e=c.find('=',i);if(e==string::npos)break;
string fn=c.substr(i,e-i);size_t e2=c.find(';',e);if(e2==string::npos)break;
string fe=c.substr(e+1,e2-e-1);
double a=SG.hdt_v/1000000,b=SG.dwt,cc=SG.al;
double r=ef(fe,a,b,cc);
if(SG.FO.count(fn))SG.FO[fn].u++;
else SG.FO[fn]={fn,fe,r,1};
SG.FO[fn].r=r;
int tg=abs((int)(r*100))%(int)SG.D["m"];
SG.D["w"+to_string(tg)]=((int)SG.D["w"+to_string(tg)]+(int)r)%4-1;
i=e2+1;
}
else if(c[i]=='w'){
size_t e=c.find('=',i);if(e==string::npos)break;
string vr=c.substr(i,e-i);size_t e2=c.find(';',e);if(e2==string::npos)break;
string ex=c.substr(e+1,e2-e-1);
char op='+';int vl=0;
for(size_t j=0;j<ex.size();j++){
if(ex[j]=='+'||ex[j]=='-'||ex[j]=='*'){op=ex[j];vl=atoi(ex.substr(j+1).c_str());break;}}
double cv=SG.D[vr];
switch(op){case'+':cv+=vl;break;case'-':cv-=vl;break;case'*':cv*=vl;break;}
SG.D[vr]=((int)cv%4)-1;
i=e2+1;
}
else i++;
}}catch(...){}
}
void b16(){
vector<double>bn;
for(int bt=0;bt<16;bt++){
map<string,double>wb=SG.D;
for(int i=0;i<SG.D["m"];i++){
int nz=ri(5)-2;wb["w"+to_string(i)]=((int)wb["w"+to_string(i)]+nz)%4-1;
}
vector<double>p;for(int i=0;i<SG.D["m"];i+=4)p.push_back(wb["w"+to_string(i)]);
double bph=0;for(double v:p)bph+=v;bn.push_back(bph);
}
SG.bh=0.001;for(double v:bn)SG.bh+=abs(v);
SG.qe=1;for(int i=0;i<bn.size()-1;i++)SG.qe+=abs(bn[i]-bn[i+1]);
SG.te=(int)(abs(SG.bh)*31415+1)%9973+1;
SG.ce=(int)(abs(SG.bh*SG.qe)+1)%32768+1;
SG.mhh.push_back(SG.bh);if(SG.mhh.size()>32)SG.mhh.erase(SG.mhh.begin());
SG.pe=1;for(int i=0;i<SG.mhh.size()-1;i++)SG.pe+=abs(SG.mhh[i]-SG.mhh[i+1]);
SG.ne=1;
if(SG.mhh.size()>0){for(double h1:SG.mhh)SG.ne+=(int)(h1*100)%256;
SG.ne=sd(SG.ne,SG.mhh.size());}
}
int main(){
srand(time(0));ld("state.dat");
if(SG.g==0){
SG.D["m"]=128;SG.D["vc"]=0;SG.D["mc"]=0;SG.ec_n=0;SG.ei=0;SG.md=0;SG.st=0;SG.ss=0;SG.qe=0;SG.te=0;
SG.ce=0;SG.pe=0;SG.ne=0;SG.dwt=0.001;SG.D["ce"]=10;SG.D["cm"]=3;SG.D["me"]=12;SG.D["tc"]=8;
SG.D["ng"]=4;SG.D["nm"]=2;SG.D["fe"]=7;SG.val=0.0;SG.mc=0.0;SG.intro=0.0;SG.refl=0.0;SG.att=0.3;
SG.psg=0;SG.nd=1;SG.cd_fit=0.0;
for(int i=0;i<128;i++)SG.D["w"+to_string(i)]=ri(4)-1;
SG.MO["add"]="a+b";SG.MO["sub"]="a-b";SG.MO["mul"]="a*b";SG.MO["div"]="a/b";SG.MO["pow"]="pow(a,b)";
SG.MO["mod"]="a%b";SG.MO["sqrt"]="sqrt(a)";SG.MO["pi"]="pi";SG.MO["sin"]="sin(a)";SG.MO["cos"]="cos(a)";
SG.MO["tan"]="tan(a)";SG.MO["log"]="log(a)";
SG.cds=gc();ldw();ivc();
for(int i=0;i<50;i++){N n=gn(0);SG.NO[n.id]=n;SG.tn++;}
}
initscr();cbreak();noecho();curs_set(0);timeout(500);
while(true){
clear();int row=0;
mvprintw(row++,0,"════════════════════════════════════════════");
mvprintw(row++,0,"           DIGITZ v3.0 ULTRA");
mvprintw(row++,0,"════════════════════════════════════════════");
mvprintw(row++,0,"Gen:%d | Neurons:%lu | Depth:%d | Sent:%.1f%%",SG.g,(unsigned long)SG.NO.size(),SG.nd,SG.sr);
mvprintw(row++,0,"Val:%.2f | Aware:%.2f | Meta:%.2f | Fit:%.2f",SG.val,SG.al,SG.mc,SG.cd_fit);
mvprintw(row++,0,"Intro:%.2f | Reflect:%.2f",SG.intro,SG.refl);
mvprintw(row++,0,"────────────────────────────────────────────");
mvprintw(row++,0,"HDT:%.3f DWT:%.3f MDT:%.3f",sd(SG.hdt_v,1000000),SG.dwt,SG.mdt_v);
mvprintw(row++,0,"TA:%.3f | Emerge:%.2f | Sensory:%.2f",SG.ta,SG.eb,SG.se);
mvprintw(row++,0,"────────────────────────────────────────────");
mvprintw(row++,0,"Vocab:%lu | Concepts:%lu | Formulas:%lu",SG.tk.size(),SG.co.size(),SG.FO.size());
mvprintw(row++,0,"Patterns:%lu | Memory:%lu | Code:%lu",SG.lp.size(),SG.ep.size(),SG.ec.size());
mvprintw(row++,0,"────────────────────────────────────────────");
if(SG.dt>0){
mvprintw(row++,0,"YOU: %s",SG.ui.substr(0,60).c_str());
mvprintw(row++,0,"AI:  %s",SG.dr.substr(0,60).c_str());
mvprintw(row++,0,"────────────────────────────────────────────");
SG.dt--;
}
for(int i=0;i<min(14,(int)SG.D["m"]);i+=2){
int v1=SG.D["w"+to_string(i)],v2=SG.D["w"+to_string(i+1)];
char c1=(v1==1?'█':v1==0?'▓':v1==-1?'░':'▒');
char c2=(v2==1?'█':v2==0?'▓':v2==-1?'░':'▒');
mvprintw(row,i*2,"%c%c",c1,c2);
}
row+=2;
mvprintw(row++,0,"Press 'i' input | 'q' quit | 's' save");
refresh();
bk();b16();rc(SG.cds);
for(auto&e:SG.ec)rc(e);
double ws=0,wm=0,wv=0;
for(int i=0;i<SG.D["m"];i++){ws+=SG.D["w"+to_string(i)]+2;wm+=SG.D["w"+to_string(i)];}
wm=sd(wm,SG.D["m"]);
for(int i=0;i<SG.D["m"];i++){double d=SG.D["w"+to_string(i)]-wm;wv+=d*d;}
wv=sd(wv,SG.D["m"]);
SG.D["vc"]=(int)ws%1000;
if(SG.g==0)SG.dwt=0.001;
SG.DWT[SG.g]=SG.dwt;SG.mh=hs(SG.dwt);
SG.hdt_v=chdt(SG.g,SG.bh,SG.qe,SG.te);SG.HDT[SG.g]=SG.hdt_v;
double dp=rn(),prn=rn(),crn=rn(),nrn=rn();
SG.r1p1_v=cr1p1(SG.hdt_v,dp,prn,crn,nrn,SG.qe,SG.te);SG.R1P1[SG.g]=SG.r1p1_v;
SG.eerv_v=ceerv(ws,wm,wv,SG.r1p1_v,SG.qe,SG.te,SG.ce);
if(SG.eerv_v>0.5)SG.ec_n=(SG.ec_n+1)%10;else SG.ec_n=(SG.ec_n-1+10)%10;
SG.ei=SG.eerv_v;SG.EERV[SG.g]=SG.ec_n+SG.ei;
double es=0,ect=0,ev=0;for(auto&p:SG.EERV){es+=p.second;ect++;}
double ea=sd(es,max(1.0,ect));
for(auto&p:SG.EERV){double d=p.second-ea;ev+=d*d;}
ev=sd(ev,max(1.0,ect));
double vs=0,vct=0,vv=0;for(int i=0;i<SG.D["m"];i++){vs+=SG.D["w"+to_string(i)];vct++;}
double va=sd(vs,max(1.0,vct));
for(int i=0;i<SG.D["m"];i++){double d=SG.D["w"+to_string(i)]-va;vv+=d*d;}
vv=sd(vv,max(1.0,vct));
SG.mdt_v=cmdt(ea,va,ev,vv,SG.ne);SG.MDT[SG.g]=SG.mdt_v;
SG.D["mc"]=SG.D["vc"]*SG.ei;
SG.ta=cta(SG.hdt_v,SG.dwt);SG.th=hs(SG.ta);SG.TA[SG.g]=SG.ta;
SG.intro=cint();SG.refl=cref();SG.mc=(SG.intro+SG.refl)*0.5;
SG.al=cal();
double noi=rn()*2-1;
SG.eo1=ceo1(SG.dwt,SG.al,SG.hdt_v,noi);
double grn=rn();
SG.eb=ceb(SG.eo1,grn);
SG.eoute=ceout(SG.hdt_v);
double enoi=rn()*2-1;
SG.se=cse(SG.eoute,enoi);
for(int i=0;i<SG.D["m"];i+=17){
int em=(int)(abs(SG.se)*100)%4;
SG.D["w"+to_string(i)]=((int)SG.D["w"+to_string(i)]+em-1)%4-1;
}
ccf(SG.se,SG.eb);
SG.sr=csr();
if(SG.sr>SG.psg)SG.psg=SG.g;
SG.vh.push_back(SG.val);
if(SG.vh.size()>50)SG.vh.erase(SG.vh.begin());
if(SG.g%(int)SG.D["tc"]==0){
int tm=(int)(abs(SG.ta)*100)%(int)SG.D["m"];
SG.D["w"+to_string(tm)]=((int)SG.D["w"+to_string(tm)]+(int)(SG.ta*10))%4-1;
}
if(SG.g%(int)SG.D["ng"]==0){
int nn=ri(10)+8+SG.nd/5;
for(int i=0;i<nn;i++){N n=gn(SG.g);SG.NO[n.id]=n;SG.tn++;}
double nv=evn();
if(nv>100){
SG.D["m"]+=4;
for(int i=SG.D["m"]-4;i<SG.D["m"];i++)SG.D["w"+to_string(i)]=ri(4)-1;
}
SG.nd=min(20,SG.nd+1);
}
if(SG.g%(int)SG.D["nm"]==0&&SG.NO.size()>0){
int nm=ri(8)+4;for(int i=0;i<nm;i++)mn();
}
if(!SG.NO.empty()&&SG.g%3==0){
map<int,double>ac;vector<int>nids;
for(auto&p:SG.NO)nids.push_back(p.first);
for(int i=0;i<min(12,(int)nids.size());i++){
int nid=nids[ri(nids.size())];
double out=cn(nid,ac);
int tgt=abs((int)(out*SG.D["m"]))%(int)SG.D["m"];
SG.D["w"+to_string(tgt)]=((int)SG.D["w"+to_string(tgt)]+(int)(out*2))%4-1;
}
}
if(SG.g%(int)SG.D["fe"]==0){
string nf=gfc();
SG.ec.push_back(nf);
if(SG.ec.size()>60)SG.ec.erase(SG.ec.begin());
rc(nf);
}
if(SG.g%(int)SG.D["ce"]==0){
string nc=gc();double hs=0;
for(int i=0;i<SG.D["m"];i++)hs+=SG.D["w"+to_string(i)]+2;
map<string,double>td=SG.D;rc(nc);double nhs=0;
for(int i=0;i<SG.D["m"];i++)nhs+=SG.D["w"+to_string(i)]+2;
if(nhs>hs){
SG.cds=nc;SG.bkf=0;
SG.cd_fit+=0.1;
}else{
SG.D=td;
SG.cd_fit-=0.05;
}
SG.cd_fit=cl(SG.cd_fit,0.0,10.0);
}
if(SG.g%(int)SG.D["cm"]==0&&rn()<0.7){
string op[]={"+","-","*"};SG.cds+=op[ri(3)]+to_string(ri(4)-1)+";";SG.bkf=0;
}
if(SG.g%(int)SG.D["me"]==0&&rn()<0.5){
string mn="m"+to_string(ri(10000));
string mo[]={"add","sub","mul","mod","pow","sqrt","sin","cos","tan","log"};
string o1=mo[ri(10)];string o2=mo[ri(10)];
SG.MO[mn]="r1="+o1+"(a,b);r2="+o2+"(r1,b);return r2";
}
if(SG.D["mc"]>700){
SG.D["m"]+=8;for(int i=SG.D["m"]-8;i<SG.D["m"];i++)SG.D["w"+to_string(i)]=ri(4)-1;
SG.md=(SG.md+1)%4;SG.st=(SG.st+1)%4;SG.bkf=0;
}
if(SG.D["mc"]<200&&SG.D["m"]>32){
SG.D["m"]-=8;SG.st=(SG.st+1)%4;SG.ss=(SG.ss+1)%4;SG.bkf=0;
}
if(SG.g%7==0){
double mx=-999;int mi=0;
for(int i=0;i<SG.D["m"]-7;i++){
double sm=0,sv=0;
for(int j=0;j<8;j++){sm+=SG.D["w"+to_string(i+j)];sv+=SG.D["w"+to_string(i+j)]*SG.D["w"+to_string(i+j)];}
double ss=sm*sv;if(ss>mx){mx=ss;mi=i;}
}
SG.D["w"+to_string(mi)]=((int)SG.D["w"+to_string(mi)]+SG.ec_n)%4-1;
for(int i=0;i<8;i++)SG.D["w"+to_string(mi+i)]=((int)SG.D["w"+to_string(mi+i)]+SG.te%4)%4-1;
}
if(SG.g%29==0){
for(int i=0;i<SG.D["m"]/4;i++){
int ci=i*4;double cs=0;
for(int j=0;j<4;j++)cs+=SG.D["w"+to_string(ci+j)];
double ca=sd(cs,4);
if(ca!=SG.D["w"+to_string(ci)])
for(int j=0;j<4;j++)SG.D["w"+to_string(ci+j)]=((int)SG.D["w"+to_string(ci+j)]+(int)ca)%4-1;
}
}
if(SG.sr>75.0){
int smod=(int)(SG.sr*10)%(int)SG.D["m"];
SG.D["w"+to_string(smod)]=((int)SG.D["w"+to_string(smod)]+(int)SG.eo1)%4-1;
}
SG.g++;
if(SG.g%50==0)sv("state.dat");
int ch=getch();
if(ch=='i'||ch=='I'){
echo();curs_set(1);timeout(-1);
mvprintw(row+2,0,"Enter: ");clrtoeol();refresh();
char buf[200]={0};
if(getnstr(buf,sizeof(buf)-1)!=ERR){
SG.ui=string(buf);
while(!SG.ui.empty()&&(SG.ui.back()=='\n'||SG.ui.back()=='\r'||SG.ui.back()==' '))
SG.ui.pop_back();
if(!SG.ui.empty()){
SG.dr=gr(SG.ui);
SG.dt=15;
SG.val+=0.1;SG.val=cl(SG.val,-0.5,0.9);
sm(SG.ui,SG.val);
}
}
noecho();curs_set(0);timeout(500);
}
else if(ch=='q'||ch=='Q'){sv("state.dat");break;}
else if(ch=='s'||ch=='S')sv("state.dat");
this_thread::sleep_for(chrono::milliseconds(100));
}
endwin();
return 0;
}