#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>
#include <iomanip>

using namespace std;

struct sodo
{
    int *ten;
    int *moc;
    int sl;
};
struct process
{
    int id;
    int timexh;
    int timeth;
};

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}

process* input(int &n)
{
    int i,j;
    process *a,tg;
    a=new process[n];
    gotoxy(8,1);
    cout<<"Ten TT";
    gotoxy(18,1);
    cout<<"Time XH";
    gotoxy(28,1);
    cout<<"Time TH";
    for(i=0; i<n; i++)
    {
        gotoxy(10,i+2);
        cout<<"P"<<i+1;
        a[i].id=i+1;
        gotoxy(20,i+2);
        cin>>a[i].timexh;
        while(a[i].timexh<0){
            gotoxy(3,i+2);
            cout<<"Press again: P"<<i+1;
            a[i].id=i+1;
            gotoxy(25,i+2);
            cin>>a[i].timexh;
        }
        gotoxy(30,i+2);
        cin>>a[i].timeth;
        while(a[i].timeth<0){
            gotoxy(3,i+2);
            cout<<"Press again: P"<<i+1;
            a[i].id=i+1;
            gotoxy(35,i+2);
            cin>>a[i].timeth;
        }
    }
    for(i=0; i<n; i++)
        for(j=0; j<n-1; j++)
            if( a[j].timexh>a[j+1].timexh)
            {
                tg=a[j];
                a[j]=a[j+1];
                a[j+1]=tg;
            };
    return a;
}
void output(sodo &G)
{
    int i=0,j=0;
    for(i=0; i<=G.sl; i++)
    {
        cout<<G.moc[i]<<" ";
        if(i!=G.sl)
            if(G.ten[i]!=0)
            {
                cout<<"P";
                cout<<G.ten[i];
                cout<<" ";
            };
        j++;
        if(j==9)
        {
            cout<<"\n";
            j=0;
        }
    }
}
void debai(process *A,int &n)
{
    gotoxy(57,1);
    cout<<"TenTT";
    gotoxy(65,1);
    cout<<"TimeXH";
    gotoxy(73,1);
    cout<<"TimeTH";
    for(int i=0; i<n; i++)
    {
        gotoxy(57,i+2);
        cout<<"|";
        gotoxy(60,i+2);
        cout<<"P"<<A[i].id;
        gotoxy(68,i+2);
        cout<<A[i].timexh;
        gotoxy(76,i+2);
        cout<<A[i].timeth;
    }
}

sodo RR(process *x,int &n)
{
    sodo G;
    process *a;
    int i,j,q;
    a=new process[n];
    for(i=0; i<n; i++)
        a[i]=x[i];
    int *xh,sopt=0,slxh=0,*vt,*cl;
    xh=new int[n];
    vt=new int;
    cl=new int;
    G.ten=new int;
    G.moc=new int;
    G.sl=0;
    G.moc[0]=0;
    for(i=0; i<n; i++)
        xh[i]=0;
    cout<<"\tLuong tu thoi gian: q = ";   cin>>q;
    while(q<0){
        cout << endl << setw(34) << "Yeu cau q>0. Moi nhap lai: q = ";  cin >> q;
    }
    cout << endl << "\tKet qua theo thuat toan RR:\n\n";
    for(i=0; i<n; i++)
        if(a[i].timexh==G.moc[0] && xh[i]==0)
        {
            vt=(int*)realloc(vt,(sopt+1)*sizeof(int));
            cl=(int*)realloc(cl,(sopt+1)*sizeof(int));
            vt[sopt]=a[i].id;
            cl[sopt]=a[i].timeth;
            xh[i]=1;
            sopt++;
            slxh++;
        }
    while(sopt>0 || slxh<n )
    {
        G.ten=(int*)realloc(G.ten,(G.sl+1)*sizeof(int));
        G.moc=(int*)realloc(G.moc,(G.sl+2)*sizeof(int));

        if(sopt>0)
        {
            if(cl[sopt-1]<=q)
            {
                G.moc[G.sl+1]=G.moc[G.sl]+cl[sopt-1];
                G.ten[G.sl]=vt[sopt-1];
                sopt--;
                for(i=0; i<n; i++)
                    if(a[i].id==G.ten[G.sl])
                    {
                        j=i;
                        break;
                    }
                xh[j]=1;
            }
            else
            {
                G.moc[G.sl+1]=G.moc[G.sl]+q;
                G.ten[G.sl]=vt[sopt-1];
                for(i=sopt-1; i>0; i--)
                {
                    vt[i]=vt[i-1];
                    cl[i]=cl[i-1];
                    xh[i]=xh[i-1];
                }
                vt[0]=G.ten[G.sl];
                for(i=0; i<n; i++)
                    if(a[i].id==G.ten[G.sl])
                    {
                        j=i;
                        break;
                    }
                a[j].timeth-=q;
                cl[0]=a[j].timeth;
                xh[j]=1;
            }
            G.sl++;
        }
        else
        {
            for(i=0; i<n; i++)
                if(xh[i]==0)
                {
                    j=i;
                    break;
                }
            vt=(int*)realloc(vt,(sopt+1)*sizeof(int));
            cl=(int*)realloc(cl,(sopt+1)*sizeof(int));
            vt[sopt]=a[j].id;
            cl[sopt]=a[j].timeth;
            G.moc[G.sl+1]=a[j].timexh;
            G.ten[G.sl]=0;
            slxh++;
            sopt++;
            G.sl++;
            continue;
        }
        for(i=0; i<n; i++)
            if(a[i].timexh<=G.moc[G.sl] && xh[i]==0)
            {
                vt=(int*)realloc(vt,(sopt+1)*sizeof(int));
                cl=(int*)realloc(cl,(sopt+1)*sizeof(int));
                vt[sopt]=a[i].id;
                cl[sopt]=a[i].timeth;
                sopt++;
                slxh++;
                xh[i]=1;
            }
    }
    return G;
}
float waittimeavg(sodo &g,process *x,int &n)
{
    int *list,*waittime,*timefinish;
    float waittimeavg;
    int i=g.sl-1,j=0,kt,tg;
    int totalwaittime=0;
    list=new int[n+1];
    waittime=new int[n];
    timefinish=new int[n];
    while(j<=g.sl+1 && i>=0)
    {
        int k=0;
        while(k<=j && g.ten[i]!=list[k])
            k++;
        if(k<=j)
            kt=1;
        else
            kt=0;
        if(kt==0)
        {
            timefinish[j]=g.moc[i+1];
            j++;
            list[j]=g.ten[i];
        }
        i--;
    }
    for(i=0; i<n; i++)
        for(j=1; j<=n; j++)
            if(list[j]==x[i].id)
            {
                tg=timefinish[i];
                timefinish[i]=timefinish[j-1];
                timefinish[j-1]=tg;
                tg=list[i+1];
                list[i+1]=list[j];
                list[j]=tg;
            }
    for(i=0; i<n; i++)
    {
        waittime[i]=timefinish[i]-(x[i].timexh+x[i].timeth);
        totalwaittime+=waittime[i];
    }
    waittimeavg=(float)totalwaittime/n;
    return waittimeavg;
}
int main()
{
    char k;
    int n;
    process *X;
    sodo G;
    system("cls");
    do
    {
        cout<<"So luong tien trinh: ";
        cin>>n;
        if(n < 2)   cout<<"So tien trinh phai lon hon 1.";
        cout<<endl;
    }
    while(n < 2);

    X=new process[n];
    system("cls");
    X=input(n);   // Tien hanh nhap du lieu cho mang tien trinh
label:
    system("cls");
    debai(X,n);
    gotoxy(1,1);
    cout<<"\n4: Thuat toan RR\n";
    float timeavg;
    G=RR(X,n);
    output(G);
    timeavg=waittimeavg(G,X,n); //Tinh thoi gian cho doi trung binh cua thuat toan
    cout<<"\n\nThoi gian cho doi trung binh = "<<timeavg;
    getch();
    goto label;
    return 0;
}
