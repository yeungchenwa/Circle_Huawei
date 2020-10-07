#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
#include <time.h>
#include <sstream>
#include <fstream>
typedef unsigned int uint;
using namespace std;
struct Edge
{
    uint v;
    unsigned long long w;
    Edge(uint _v = 0, unsigned long long _w = 0) : v(_v), w(_w){};
};
vector<vector<Edge>> e;
vector<vector<Edge>> re;
vector<uint> sstack;
vector<vector<uint>> cycles;
unordered_map<uint, uint> vtn;
vector<uint> vs;
vector<uint> vss;
vector<bool> vis;
vector<vector<uint>> ordered;
// vector<unordered_map<uint, vector<uint>>> p2;
vector<unordered_map<uint, vector<vector<uint>>>> p3;
vector<vector<uint>> eempty;
vector<unsigned long long> wstack;
uint cnt = 0;
uint cnt1 = 0;

void addEdge(uint u, uint v, unsigned long long w, uint i)
{
    if (i >= e.size())
    {
        e.resize(i);
        re.resize(i);
    }
    e[u].push_back(Edge(v, w));
    re[v].push_back(Edge(u, w));
    return;
}
// void construct1()
// {
//     p2.resize(e.size());
//     for (int i = 0; i < e.size(); i++)
//     {
//         vector<Edge> t1 = e[i];
//         for (int k = 0; k < t1.size(); k++)
//         {
//             vector<Edge> t2 = e[t1[k].v];
//             for (int j = 0; j < t2.size(); j++)
//             {
//                 if (t2[j].v != i)
//                 {
//                     // vector<uint> ttmp;
//                     // if(p2[t2[j].v].count(i)) 
//                     // {
//                     //     p2[t2[j].v].at(i).emplace_back(t1[k].v);
//                     // }
//                     // else
//                     // {
//                     //     ttmp.emplace_back(t1[k].v);
//                     //     p2[t2[j].v].insert(pair < uint, vector<uint>>(i, ttmp));
//                     // }
                    
                    
//                     p2[t2[j].v][i].emplace_back(t1[k].v);
//                 }
//             }
//         }
//     }
 
//     for (int i = 0; i < p2.size(); i++)
//     {
//         for (auto j : p2[i])
//         {
//             if (j.second.size() > 1)
//             {
//                 sort(j.second.begin(), j.second.end());
//             }
//         }
//     }
// }
void construct2()
{
    p3.resize(e.size());
    for (int i = 0; i < e.size(); i++)
    {
        vector<Edge> t1 = e[i];
        for (int k = 0; k < t1.size(); k++)
        {
            vector<Edge> t2 = e[t1[k].v];
            for (int j = 0; j < t2.size(); j++)
            {
                if (t2[j].v != i)
                {
                    int n = p3[t2[j].v][i].size();
                    p3[t2[j].v][i].resize(n+1);
                    p3[t2[j].v][i][n].emplace_back(t1[k].v);
                }
                vector<Edge> t3=e[t2[j].v];
                for(int q=0;q<t3.size();q++)
                {
                    if(t3[q].v!=i&&t1[k].v!=t2[j].v)
                    {
                        int n = p3[t3[q].v][i].size();
                        p3[t3[q].v][i].resize(n+1);
                        p3[t3[q].v][i][n].emplace_back(t1[k].v);
                        p3[t3[q].v][i][n].emplace_back(t2[j].v);
                    }
                    vector<Edge> t4=e[t3[q].v];
                    
                    for(int w=0;w<t4.size();w++)
                    {
                        
                        if(t4[w].v!=i&&t1[k].v!=t2[j].v&&t2[j].v!=t3[q].v&&t3[q].v!=t1[k].v)
                        {
                            int n = p3[t4[w].v][i].size();
                           
                            p3[t4[w].v][i].resize(n+1);
                            p3[t4[w].v][i][n].emplace_back(t1[k].v);
                            p3[t4[w].v][i][n].emplace_back(t2[j].v);
                            p3[t4[w].v][i][n].emplace_back(t3[q].v);
                            
                        }
                    }
                }
            }
        }
    }
}
void construct3()
{
    p3.resize(e.size());
    for (int i = 0; i < e.size(); i++)
    {
        vector<Edge> t1 = e[i];
        for (int k = 0; k < t1.size(); k++)
        {
            vector<Edge> t2 = e[t1[k].v];
            for (int j = 0; j < t2.size(); j++)
            {
                vector<Edge> t3=e[t2[j].v];
                if(t2[j].w==0||t1[k].w==0) continue;
                if((float)t2[j].w/t1[k].w<0.2||(float)t2[j].w/t1[k].w>3) continue;
                for(int q=0;q<t3.size();q++)
                {
                    if(t2[j].w==0||t3[q].w==0) continue;
                    if((float)t3[q].w/t2[j].w<0.2||(float)t3[q].w/t2[j].w>3) continue;
                    vector<Edge> t4=e[t3[q].v];
                    for(int w=0;w<t4.size();w++)
                    {
                        if(t4[w].w==0||t3[q].w==0) continue;
                        if((float)t4[w].w/t3[q].w<0.2||(float)t4[w].w/t3[q].w>3) continue;
                        if(t4[w].v!=i&&t1[k].v!=t2[j].v&&t2[j].v!=t3[q].v&&t3[q].v!=t1[k].v&&t1[k].v>t4[w].v&&t2[j].v>t4[w].v&&t3[q].v>t4[w].v)
                        {
                            if (!p3[t4[w].v].count(i))
                            {
                                p3[t4[w].v].insert(pair<uint, vector<vector<uint>>>(i, eempty));
                            }
                            int n = p3[t4[w].v][i].size();
                                p3[t4[w].v][i].resize(n+1);
                                p3[t4[w].v][i][n].emplace_back(t1[k].v);
                                p3[t4[w].v][i][n].emplace_back(t2[j].v);
                                p3[t4[w].v][i][n].emplace_back(t3[q].v);
                                p3[t4[w].v][i][n].emplace_back(e[i][k].w);
                                p3[t4[w].v][i][n].emplace_back(t4[w].w);
                        }
                    }
                }
            }
        }
    }
}
void construct4(uint a,uint b)
{
    
        vector<Edge> t1 = e[b];
        for (int k = 0; k < t1.size(); k++)
        {
            vector<Edge> t2 = e[t1[k].v];
            for (int j = 0; j < t2.size(); j++)
            {
                vector<Edge> t3=e[t2[j].v];
                if(t2[j].w==0||t1[k].w==0) continue;
                if((float)t2[j].w/t1[k].w<0.2||(float)t2[j].w/t1[k].w>3) continue;
                for(int q=0;q<t3.size();q++)
                {
                    if(t2[j].w==0||t3[q].w==0) continue;
                    if((float)t3[q].w/t2[j].w<0.2||(float)t3[q].w/t2[j].w>3) continue;
                    vector<Edge> t4=e[t3[q].v];
                    for(int w=0;w<t4.size();w++)
                    {
                        if(t4[w].w==0||t3[q].w==0) continue;
                        if((float)t4[w].w/t3[q].w<0.2||(float)t4[w].w/t3[q].w>3) continue;
                        if(t4[w].v!=b&&t4[w].v==a&&t1[k].v!=t2[j].v&&t2[j].v!=t3[q].v&&t3[q].v!=t1[k].v&&t1[k].v>t4[w].v&&t2[j].v>t4[w].v&&t3[q].v>t4[w].v)
                        {
                            if (!p3[t4[w].v].count(b))
                            {
                                p3[t4[w].v].insert(pair<uint, vector<vector<uint>>>(b, eempty));
                            }
                            int n = p3[t4[w].v][b].size();
                                p3[t4[w].v][b].resize(n+1);
                                p3[t4[w].v][b][n].emplace_back(t1[k].v);
                                p3[t4[w].v][b][n].emplace_back(t2[j].v);
                                p3[t4[w].v][b][n].emplace_back(t3[q].v);
                                p3[t4[w].v][b][n].emplace_back(e[b][k].w);
                                p3[t4[w].v][b][n].emplace_back(t4[w].w);
                        }
                    }
                }
            }
        }
    
}
void construct5(uint v,unordered_map<uint,vector<uint>> &layer2,unordered_set<uint> &layer3)
{
    uint t1,t2;
    for(int i=0;i<re[v].size();i++)
    {
        if(re[v][i].v>v)
        {
            t1=re[v][i].v;
            for(int j=0;j<re[t1].size();j++)
            {
                if(re[t1][j].v>v)
                {
                    t2=re[t1][j].v;
                    if(layer2.count(t2))
                    {
                        layer2[t2].push_back(t1);
                    }
                    else 
                    {
                        layer2[t2]=vector<uint>{t1};
                    }
                    for(int k=0;k<re[t2].size();k++)
                    {
                        if(re[t2][k].v>v)
                        {
                            layer3.insert(re[t2][k].v);
                        }
                    }
                }

            }
        }
    }
}

bool check(int mode,int a=0,int b=0)
{
    wstack.clear();
    if(mode==0)
    {
        for(int i=0;i<sstack.size();i++)
        {
            for(int j=0;j<e[sstack[i]].size();j++)
            {
                if(e[sstack[i]][j].v==sstack[(i+1)%sstack.size()])
                {    
                    if(e[sstack[i]][j].w==0) return false;
                    wstack.emplace_back(e[sstack[i]][j].w); 
                    break; 
                }
            }
        }
        for(int i=0;i<wstack.size();i++)
        {
            if((float)wstack[(i+1)%wstack.size()]/wstack[i]>=0.2&&(float)wstack[(i+1)%wstack.size()]/wstack[i]<=3) continue;
            else return false;
        }
    }
    else if(mode==1)
    {
        for(int i=0;i<sstack.size()-1;i++)
        {
            for(int j=0;j<e[sstack[i]].size();j++)
            {
                if(e[sstack[i]][j].v==sstack[i+1])
                {    
                    if(e[sstack[i]][j].w==0) return false;
                    wstack.emplace_back(e[sstack[i]][j].w); 
                    break; 
                }
            }
        }
        wstack.emplace_back(a);
        int u=wstack.size();
        wstack.emplace_back(b);
        int q=wstack.size();
        for(int i=0;i<u-1;i++)
        {
            if((float)wstack[i+1]/wstack[i]>=0.2&&(float)wstack[i+1]/wstack[i]<=3) continue;
            else return false;
        }
        if((float)wstack[0]/wstack[q-1]<0.2||(float)wstack[0]/wstack[q-1]>3) return false;
    }
    return true;
}
void dfs3(uint v,uint s)
{
    vis[v] = 1;
    sstack.emplace_back(v);
    
    for (int i = 0; i < e[v].size(); i++)
    {
        if(sstack.size()==3||sstack.size()==4)
        {
            if (e[v][i].v == s&&check(0))
            {
                cycles.resize(cycles.size() + 1);
                for (int j = 0; j < sstack.size(); j++)
                {
                    cycles[cnt].emplace_back(sstack[j]);
                }
                cnt++;
            }
        }
        
        if(sstack.size()<4&&e[v][i].v>s&&vis[e[v][i].v]==0)  dfs3(e[v][i].v, s); 
        
    }
    if(sstack.size()>=2)
    {
        vector<vector<uint>> kk;
        bool flag=0;
        int ww=0;
        // if(sstack.size()==2) ww=first_w;
        // else 
        // {
        //     int n=sstack.size();
        //     for(int p=0;p<e[sstack[n-2]].size();p++)
        //     {
        //         if(e[sstack[n - 2]][p].v==sstack[n-1]) {ww=e[sstack[n - 2]][p].w; break; }
        //     }
        // }
        if(p3[s].count(v))  kk = p3[s][v];
        else kk.resize(0);
        
        for(int j=0;j<kk.size();j++)
        {
            if(sstack.size()<=4&&vis[kk[j][1]]==0&&vis[kk[j][0]]==0&&vis[kk[j][2]]==0&&check(1,kk[j][3],kk[j][4]))//&&(float)kk[j][3]/ww>=0.2&&(float)kk[j][3]/ww<=3&&(float)first_w/kk[j][4]>=0.2&&(float)first_w/kk[j][4]<=3)
            {
                cycles.resize(cycles.size() + 1);
                for (int k = 0; k < sstack.size(); k++)
                {
                    cycles[cnt].emplace_back(sstack[k]);
                }
                cycles[cnt].emplace_back(kk[j][0]);
                cycles[cnt].emplace_back(kk[j][1]);
                cycles[cnt].emplace_back(kk[j][2]);
                // cout<<cycles[cnt].size()<<endl;
                cnt++;
                cnt1++;
                flag=1;
            }
        }
    }
    // cout<<"herhe"<<endl;
    vis[v] = 0;
    sstack.pop_back();
    
    return;
}
void dfs4(uint v,uint s)
{
    vis[v] = 1;
    sstack.emplace_back(v);
    
    for (int i = 0; i < e[v].size(); i++)
    {
        if(sstack.size()==3||sstack.size()==4)
        {
            if (e[v][i].v == s&&check(0))
            {
                cycles.resize(cycles.size() + 1);
                for (int j = 0; j < sstack.size(); j++)
                {
                    cycles[cnt].emplace_back(sstack[j]);
                }
                cnt++;
            }
        }
        
        if(sstack.size()<4&&e[v][i].v>s&&vis[e[v][i].v]==0)  dfs4(e[v][i].v, s); 
        
    }
    if(sstack.size()>=2)
    {
        vector<vector<uint>> kk;
        bool flag=0;
        if(!p3[s].count(v))
        construct4(s,v);
        if(p3[s].count(v))  kk = p3[s][v];
        else kk.resize(0);
        
        for(int j=0;j<kk.size();j++)
        {
            if(sstack.size()<=4&&vis[kk[j][1]]==0&&vis[kk[j][0]]==0&&vis[kk[j][2]]==0&&check(1,kk[j][3],kk[j][4]))//&&(float)kk[j][3]/ww>=0.2&&(float)kk[j][3]/ww<=3&&(float)first_w/kk[j][4]>=0.2&&(float)first_w/kk[j][4]<=3)
            {
                cycles.resize(cycles.size() + 1);
                for (int k = 0; k < sstack.size(); k++)
                {
                    cycles[cnt].emplace_back(sstack[k]);
                }
                cycles[cnt].emplace_back(kk[j][0]);
                cycles[cnt].emplace_back(kk[j][1]);
                cycles[cnt].emplace_back(kk[j][2]);
                // cout<<cycles[cnt].size()<<endl;
                cnt++;
                cnt1++;
                flag=1;
            }
        }
    }
    // cout<<"herhe"<<endl;
    vis[v] = 0;
    sstack.pop_back();
    
    return;

}
void dfs5(uint v,uint s,unordered_map<uint,vector<uint>> &layer2,unordered_set<uint> &layer3)
{
    vis[v] = 1;
    sstack.emplace_back(v);
    int vv;
    vector<uint> kk;
    for(int i=0;i<e[v].size();i++)
    {
        if(e[v][i].v>s)
        {
            vv=e[v][i].v;
            if(vis[vv]) continue;
            if(layer2.count(vv))
            {
                sstack.emplace_back(vv);
                kk=layer2[vv];
                for(int j=0;j<kk.size();j++)
                {
                    vv=kk[j];
                    if(vis[vv]) continue;
                    sstack.emplace_back(vv);
                    if(check(0))
                    {
                        cycles.resize(cycles.size() + 1);
                        cycles[cnt] = sstack;
                        cnt++;
                    }
                    sstack.pop_back();
                }
                sstack.pop_back();
            }
            vv=e[v][i].v;
            if(sstack.size()<5||(sstack.size()==5&&layer3.find(vv)!=layer3.end()))
            {
                dfs5(vv,s,layer2,layer3);
            }
        }
    }
    vis[v] = 0;
    sstack.pop_back();
    return;
}
void findc(int start,int end)
{
    unordered_map<uint,vector<uint>> layer2;
    unordered_set<uint> layer3;
    for(int i=start;i<end;i++)
    {
        layer2.clear();
        layer3.clear();
        construct5(i,layer2,layer3);
        dfs5(i,i,layer2,layer3);
    }
    
}
int main()
{ 
    FILE *fp1=fopen("test_data.txt","r");
    FILE *fp2=fopen("result.txt","wb");
    char douhao=',';
    char huanhang='\n';
    int id;
    char buf[1024];
    string str1;
    //freopen("test_data.txt", "r", stdin);
    //freopen("result11.txt", "w", stdout);
    uint u, v; 
    double w;
    unsigned long long www;
    clock_t t = clock();
    uint num = 0;
    vector<unsigned long long> ws;
    while (fscanf(fp1,"%d,%d,%lf", &u, &v, &w) != EOF)
    {
        vs.emplace_back(u);
        vs.emplace_back(v);
        // ws.emplace_back((unsigned long long)w*100);
        www=w;
        w-=www;
        www=www*100+100*w;
        ws.emplace_back(www);
        // cout<<www<<endl;
    }
    vss = vs;
    sort(vs.begin(), vs.end());
    set<uint> se(vs.begin(), vs.end());
    vs.assign(se.begin(), se.end());
    set<uint>().swap(se);
    for (int i = 0; i < vs.size(); i++)
    {
        vtn.insert(pair<uint, uint>(vs[i], i));
    }
    int k=0;
    for (int i = 0; i < vss.size(); i = i + 2)
    {
        
        addEdge(vtn.at(vss[i]), vtn.at(vss[i + 1]), ws[k], max(vtn.at(vss[i]), vtn.at(vss[i + 1])) + 2);
        k++;
    }
    // cout<<k<<","<<ws.size()<<endl;
    vector<uint>().swap(vss);
     num = e.size() + 2;
    vis.resize(num);
    // vector<uint> tmpp;
    // int sub_num = submap.size();
    // int cc = 0;
    // clock_t t2 = clock();
    
    // construct3();
    // //  cout<<vtn.at(427)<< " " <<vtn.at(441)<<endl;
    // while (cc < sub_num)
    // {

    //     int C = 0;
    //     while (C < submap[cc].size())
    //     {
    //         vector<uint>().swap(sstack);
    //         dfs3(submap[cc][C], submap[cc][C]);
    //         C++;
    //         // cout << cnt << "," << cnt1 << "," << cnt2 << "," << (clock() - t2) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
    //     }
    //     cc++;
    // }
    // p3.resize(e.size());
    // cout<<vtn.at(6053);
    findc(0,e.size()-1);
    // id=sprintf(buf,"%d",cnt);
    // fwrite(buf,id,sizeof(char),fp2);
    // fwrite(&huanhang,sizeof(huanhang),1,fp2);
    fprintf(fp2,"%d\n",cnt);
    int ans = 0;
    int limites[] = {3, 4, 5, 6, 7,8};

    
    ordered.resize(cycles.size());

    for (int i = 0; i < cycles.size(); i++)
    {
        for (int j = 0; j < cycles[i].size(); j++)
        {
            ordered[i].push_back(vs[cycles[i][j]]);
        }
    }
    
    sort(ordered.begin(), ordered.end());
    for (int k = 0; k < 6; k++)
    {
        for (int i = 0; i < ordered.size(); i++)
        {
            if (ordered[i].size() == limites[k])
            {
                for (int j = 0; j < ordered[i].size(); j++)
                {
                    if (j == ordered[i].size() - 1)
                    {
                        //fwrite(&ordered[i][j],sizeof(ordered[i][j]),1,fp2);
                       // printf("%d,", ordered[i][j]);
                       id=sprintf(buf,"%d",ordered[i][j]);
                       fwrite(buf,id,sizeof(char),fp2);
                    //    fprintf(fp2,"%u",ordered[i][j]);
                    }
                    else
                    {
                        //fwrite(&ordered[i][j],sizeof(ordered[i][j]),1,fp2);
                        //printf("%d", ordered[i][j]);
                        id=sprintf(buf,"%d",ordered[i][j]);
                        fwrite(buf,id,sizeof(char),fp2);
                        fwrite(&douhao,sizeof(douhao),1,fp2);
                        // fprintf(fp2,"%u,",ordered[i][j]);
                    }
                }
                // fprintf(fp2,"\n");
                //printf("\n");
               fwrite(&huanhang,sizeof(huanhang),1,fp2);
            }
        }
    }
    
    clock_t t1 = clock();
    int secondd= (t1 - t) * 1000 / CLOCKS_PER_SEC ;
    //id=sprintf(buf,"%d",secondd);
    // fwrite(buf,id,sizeof(char),fp2);
    // fprintf(fp2,"%dms",secondd);
    fclose(fp2);
    return 0;
}