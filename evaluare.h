#ifndef EVALUARE_H_INCLUDED
#define EVALUARE_H_INCLUDED
#include <bits/stdc++.h>

using namespace std;

stack<int> stiva;
char expr_post[350], exprf[350];
char var[25], fct[25], var2[25];
int nr, cnt;

int val(char s[350], unordered_map <string, int> M)
{
    int i;
    string s1 = s;
//cout<<s1;
    return M[s1];
}


int numar_cifre(int n)
{
    int m=0;
    if(n<0) n=-n;
    if (n == 0) m = 1;
    while(n)
    {
        m++;
        n/=10;
    }
    return m;
}


int ParantezareCorecta(char s[])
{
    int ok=1, j;
    stack <char> st;
    for(j=0; j<strlen(s); j++)
    {
        if(s[j]=='(') st.push(s[j]);
        else
        {
            if(s[j]==')')
            {
                if(!st.empty() && st.top()=='(')
                    st.pop();
                else ok=0;
            }
        }
    }
    if(!st.empty()) ok=0;
    return ok;
}

void ConversiePostfix(char expr_inf[350], unordered_map <string, int> M, int stare)
{
    stack<char> st;
    //cout<<"starea:"<<stare<<endl;
    //cout << expr_inf << " <-infixat\n";
    int i, k, prioritate, j, functie, n;
    char *p;

    while(!st.empty())
    st.pop();
    //cin.getline(expr_inf, 355);
    /*M["a1"]=398;
    M["m7"]=5735;
    M["g"]=93;
    M["b"]=65;
    M["g9"]=34;
    M["expr_a"]=7;*/
    k=-1;
//st.push(expr_inf[0]);
    k=-1;
//st.push(expr_inf[0]);
    functie=0;
    for(i=0; i<strlen(expr_inf); i++)
    {
        if(expr_inf[i]=='(')
            //st.push(expr_inf[i]);
        {
            st.push('(');
            if(expr_inf[i+1]=='-')
            {
                st.push('m');
                i++;
            }
        }
        else if(expr_inf[i]==')')
        {
            while(st.top()!='(')
            {
                expr_post[++k]=st.top();
                expr_post[++k]=' ';
                st.pop();
            }
            /*if(functie)
            {expr_post[++k]=')';
            expr_post[++k]=' ';
            functie--;
            }*/
            st.pop();
        }
        else if (expr_inf[i]=='+' || expr_inf[i]=='-')
        {
            while(!st.empty() &&(st.top()=='*' || st.top()=='/' || st.top()=='%' || st.top()=='^' || st.top()=='s' || st.top()=='c' || st.top()=='r' || st.top()=='a' || st.top()=='l' && st.top()=='t'|| st.top()=='^'|| st.top()=='m') && st.top()!='(')
            {
                expr_post[++k]=st.top();
                expr_post[++k]=' ';
                st.pop();
            }
            st.push(expr_inf[i]);
        }
        else if(expr_inf[i]=='*' || expr_inf[i]=='/' || expr_inf[i]=='%')
        {
            while(!st.empty() &&(st.top()=='*' || st.top()=='/' || st.top()=='%') && st.top()!='(')
            {
                expr_post[++k]=st.top();
                expr_post[++k]=' ';
                st.pop();
            }
            st.push(expr_inf[i]);
        }
        else if(expr_inf[i]=='^')
        {
            //cout<<endl<<"da"<<endl;
            while(!st.empty() &&(st.top()=='s' || st.top()=='c' || st.top()=='r' || st.top()=='a' || st.top()=='l' && st.top()=='t'|| st.top()=='^'|| st.top()=='m') && st.top()!='(')
            {
                expr_post[++k]=st.top();
                expr_post[++k]=' ';
                st.pop();
            }
            st.push(expr_inf[i]);
        }
        else
        {
            int flag=0;
            //expr_post[++k]=expr_inf[i];
//expr_post[++k]=' ';

            j=i;
            if(strchr("0123456789",expr_inf[i])==NULL) flag=1;
            while(expr_inf[j+1]!='\0' && strchr("()+-*/%^", expr_inf[j+1])==NULL)
            {
                if(strchr("0123456789",expr_inf[j+1])==NULL) flag=1;
                j++;
            }

            if(expr_inf[j+1]=='\0')
            {
                strcpy(var, expr_inf+i);
                strcat(var, " ");
            }
            else
            {
                var[0]=0;
                strncat(var, expr_inf+i, j-i+1);
                strcat(var, " ");
            }
            //cout<<var<<' '<<flag<<endl;
            if(strcmp(var, "sin ")==0 || strcmp(var, "cos ")==0 || strcmp(var, "sqrt ")==0 || strcmp(var, "abs ")==0 || strcmp(var, "log ")==0|| strcmp(var, "tan ")==0)
            {
                while(!st.empty() && (st.top()=='s' || st.top()=='c' || st.top()=='r' || st.top()=='a' || st.top()=='l' || st.top()=='t'||st.top()=='m') && st.top()!='(')
                {
                    expr_post[++k]=st.top();
                    expr_post[++k]=' ';
                    st.pop();
                }
                if(strcmp(var, "sqrt ")==0) st.push('r');
                else st.push(expr_inf[i]);
                i=j;
            }

            else
            { //cout<<var<<endl<<endl;
                if(stare==1) {
                //cout<<"yeah"<<endl;
                expr_post[++k]='1';
            expr_post[++k]=' ';
            i=j;
                            }
                else
                {if(flag)
                {
                    int n=strlen(var);
//cout<<var<<' ';
                    var[n-1]=0;
//cout<<var<<endl;
                    nr=val(var, M);
                    //cout<<"valoarea este "<<nr<<endl;
                    int aux=nr;
                    cnt=numar_cifre(nr);
                    if(nr<0)
                    {
                        nr=-nr;
                        //st.push('(');
                        st.push('m');
                        //st.push(')');
                    }
                    int m=cnt;
                    if (nr == 0)
                    {
                        expr_post[k+cnt]=char(nr%10+'0');
                        cnt--;
                        nr/=10;
                    }
                    while(nr)
                    {
                        expr_post[k+cnt]=char(nr%10+'0');
                        cnt--;
                        nr/=10;
                    }
                    k+=m;
//expr_post[++k]=char(nr+'0');
                    expr_post[++k]=' ';
                    i=j;

                }
                else
                {
                    //expr_post[++k]=' ';
                    n=strlen(var);
                    var[n-1]=0;
                    for(int l=0; l<strlen(var); l++)
                        expr_post[++k]=var[l];
                    expr_post[++k]=' ';
                    i=j;

                }
                }
            }
        }
//cout<<functie<<endl;
    }

    if(expr_post[k]=='\0') expr_post[k]=' ';
    while(!st.empty())
    {
        expr_post[++k]=st.top();
        expr_post[++k]=' ';
        st.pop();
    }

    /*while(functie)
    {
    expr_post[++k]=')';
    expr_post[++k]=' ';
    functie--;
    }*/
    expr_post[k+1]='\0';
  //cout<<"expresie_post "<<expr_post<<endl;
}


///-----------------------------------------------------------------------------------


///((345>1)&&(213 > 345))
void ConversiePostfixBool(char s[])
{
    stack<char> st;
    //cout<<"heeeere"<<s<<endl;
    int len = 0;
    strcpy(expr_post, "");
     while(!st.empty())
    st.pop();
    for (int i = 0; s[i] != 0; )
    {
        if ('0' <= s[i] && s[i] <= '9')
        {
            while('0' <= s[i] && s[i] <= '9')
            {
                expr_post[len++] = s[i++];
            }
            expr_post[len] = ' ';
            len++;
        }

        else if (s[i] == '(')
        {
            st.push(s[i]);
            i++;
        }
        else if (s[i] == ')')
        {
            while (st.top() != '(')
            {
                expr_post[len++] = st.top();
                expr_post[len++] = ' ';
                st.pop();
            }
            st.pop();
            i++;
        }
        else if (s[i] == '>')
        {
            if (s[i + 1] == '=')
            {
                st.push('#');
                i += 2;
            }
            else
            {
                st.push('>');
                i++;
            }
        }
        else if (s[i] == '<')
        {
            if (s[i + 1] == '=')
            {
                st.push('$');
                i += 2;
            }
            else
            {
                st.push('<');
                i++;
            }
        }
        else if (s[i] == '!')
        {
            st.push('!');
            i += 2;
        }
        else if (s[i] == '=')
        {
            st.push('=');
            i += 2;
        }
        else if (s[i] == '&')
        {
            while (st.top() != '&' && st.top() != '(' && st.top() != '|' && !st.empty())
            {
                expr_post[len++] = st.top();
                expr_post[len++] = ' ';
                st.pop();
            }
            st.push('&');
            i += 2;
        }
        else if (s[i] == '|')
        {
            while ((st.top() != '&') && (st.top() != '(') && (st.top() != '|') && !st.empty())
            {
                expr_post[len++] = st.top();
                expr_post[len++] = ' ';
                st.pop();
            }
            st.push('|');
            i += 2;
        }
    }
    while (!st.empty())
    {
        expr_post[len++] = st.top();
        expr_post[len++] = ' ';
        st.pop();
    }
    strcpy(s, expr_post);
    cout<<s<<endl;
}

void ConversiePostfixBoolTestare(char expr_inf[])
{
     stack<char> st;
    //cout<<"starea:"<<stare<<endl;
    //cout << expr_inf << " <-infixat\n";
    int i, k, prioritate, j, functie, n;
    char *p;

    while(!st.empty())
    st.pop();
    //cin.getline(expr_inf, 355);
    /*M["a1"]=398;
    M["m7"]=5735;
    M["g"]=93;
    M["b"]=65;
    M["g9"]=34;
    M["expr_a"]=7;*/
    k=-1;
//st.push(expr_inf[0]);
    k=-1;
//st.push(expr_inf[0]);
    functie=0;
    for(i=0; i<strlen(expr_inf); i++)
    {
        if(expr_inf[i]=='(')
            //st.push(expr_inf[i]);
        {
            st.push('(');
            if(expr_inf[i+1]=='-')
            {
                st.push('m');
                i++;
            }
        }
        else if(expr_inf[i]==')')
        {
            while(st.top()!='(')
            {
                expr_post[++k]=st.top();
                expr_post[++k]=' ';
                st.pop();
            }
            /*if(functie)
            {expr_post[++k]=')';
            expr_post[++k]=' ';
            functie--;
            }*/
            st.pop();
        }
         else if (expr_inf[i] == '>')
        {
            if (expr_inf[i + 1] == '=')
            {
                st.push('#');
                i ++;
            }
            else
            {
                st.push('>');

            }
        }
        else if (expr_inf[i] == '<')
        {
            if (expr_inf[i + 1] == '=')
            {
                st.push('$');
                i ++;
            }
            else
            {
                st.push('<');

            }
        }
        else if (expr_inf[i] == '!')
        {
            st.push('!');
            i ++;
        }
        else if (expr_inf[i] == '=')
        {
            st.push('=');
            i ++;
        }
        else if (expr_inf[i] == '&')
        {
            while (st.top() != '&' && st.top() != '(' && st.top() != '|' && !st.empty())
            {
                expr_post[++k] = st.top();
                expr_post[++k] = ' ';
                st.pop();
            }
            st.push('&');
            i ++;
        }
        else if (expr_inf[i] == '|')
        {
            while ((st.top() != '&') && (st.top() != '(') && (st.top() != '|') && !st.empty())
            {
                expr_post[++k] = st.top();
                expr_post[++k] = ' ';
                st.pop();
            }
            st.push('|');
            i ++;
        }

        else
        {
            int flag=0;
            //expr_post[++k]=expr_inf[i];
//expr_post[++k]=' ';

            j=i;
            if(strchr("0123456789",expr_inf[i])==NULL) flag=1;
            while(expr_inf[j+1]!='\0' && strchr("()+-*/%^", expr_inf[j+1])==NULL)
            {
                if(strchr("0123456789",expr_inf[j+1])==NULL) flag=1;
                j++;
            }

            if(expr_inf[j+1]=='\0')
            {
                strcpy(var, expr_inf+i);
                strcat(var, " ");
            }
            else
            {
                var[0]=0;
                strncat(var, expr_inf+i, j-i+1);
                strcat(var, " ");
            }
            //cout<<var<<' '<<flag<<endl;
            if(strcmp(var, "sin ")==0 || strcmp(var, "cos ")==0 || strcmp(var, "sqrt ")==0 || strcmp(var, "abs ")==0 || strcmp(var, "log ")==0|| strcmp(var, "tan ")==0)
            {
                while(!st.empty() && (st.top()=='s' || st.top()=='c' || st.top()=='r' || st.top()=='a' || st.top()=='l' || st.top()=='t'||st.top()=='m') && st.top()!='(')
                {
                    expr_post[++k]=st.top();
                    expr_post[++k]=' ';
                    st.pop();
                }
                if(strcmp(var, "sqrt ")==0) st.push('r');
                else st.push(expr_inf[i]);
                i=j;
            }

            else
            { //cout<<var<<endl<<endl;
                //cout<<"yeah"<<endl;
                expr_post[++k]='1';
            expr_post[++k]=' ';
            i=j;


            }
        }
strcpy(expr_inf, expr_post);
    }

    if(expr_post[k]=='\0') expr_post[k]=' ';
    while(!st.empty())
    {
        expr_post[++k]=st.top();
        expr_post[++k]=' ';
        st.pop();
    }

    /*while(functie)
    {
    expr_post[++k]=')';
    expr_post[++k]=' ';
    functie--;
    }*/
    expr_post[k+1]='\0';
  //cout<<"expresie_post "<<expr_post<<endl;
}





int Valoare_Adevar_Expresie(char s[])
{
    for (int i = 0; s[i] != 0; )
    {
        if ('0' <= s[i] && s[i] <= '9')
        {
            int x = 0;
            while ('0' <= s[i] && s[i] <= '9' && s[i] != 0)
            {
                x = x * 10 + (s[i] - '0');
                i++;
            }
            stiva.push(x);
        }
        else if (s[i] != ' ')
        {
            int val2 = stiva.top();
            stiva.pop();
            int val1 = stiva.top();
            stiva.pop();
            if (s[i] == '<')
            {
                if (val1 < val2) stiva.push(1);
                else stiva.push(0);
            }
            else if (s[i] == '>')
            {
                if (val1 > val2) stiva.push(1);
                else stiva.push(0);
            }
            else if (s[i] == '!')
            {
                if (val1 != val2) stiva.push(1);
                else stiva.push(0);
            }
            else if (s[i] == '=')
            {
                if (val1 == val2) stiva.push(1);
                else stiva.push(0);
            }
            else if (s[i] == '#')
            {
                if (val1 >= val2) stiva.push(1);
                else stiva.push(0);
            }
            else if (s[i] == '#')
            {
                if (val1 <= val2) stiva.push(1);
                else stiva.push(0);
            }
            else if (s[i] == '&') stiva.push(val1 & val2);
            else if (s[i] == '|') stiva.push(val1 | val2);
            i++;
        }
        else i++;
    }
    if (stiva.top() == 0) return 0;
    return 1;
}

int Eval_Expr(char s[], unordered_map<string, int> M, int stare, int &eroare)
{
    ConversiePostfix(s, M, stare);
    strcpy(s, expr_post);
    while(!stiva.empty())
    stiva.pop();
    //cout << s << " <- postfixata\n";
    //cout<<s<<endl;
    eroare=0;
    int n;
    n = strlen(s);
    int val1, val2, varf_stiva=0;
    for (int i = 0; s[i] != 0 && eroare==0; )
    {//cout<<s[i]<<' '<<eroare<<endl;
        if ('0' <= s[i] && s[i] <= '9')
        {
            int x = 0;
            while ('0' <= s[i] && s[i] <= '9')
            {
                x = x * 10 + (s[i] - '0');
                i++;
            }
            stiva.push(x);
        }
        else if (s[i] != ' ')
        {
            if(strchr("scrlatm", s[i])==NULL)
            {
                 if(!stiva.empty())
                {val1 = stiva.top();
                stiva.pop();
                if(!stiva.empty())
                 {val2 = stiva.top();
                stiva.pop();}
                else eroare=1;
                }
                else eroare=1;
                // cout << val1 << " " << val2 << "\n";
                if(eroare==0)
                {if (s[i] == '+')stiva.push(val1 + val2);
                else if (s[i] == '-') stiva.push(val2 - val1);
                else if (s[i] == '*') stiva.push(val1 * val2);
                else if (s[i] == '/')
                {if(val1!=0)
                stiva.push(val2 / val1);
                else eroare=1;
                }
                else if (s[i] == '%')
                {if(val1!=0)
                stiva.push(val2 % val1);
                else eroare=1;
                }
                else if(s[i]=='^') stiva.push(pow(val2, val1));
                else eroare=0;}
                i++;
            }
            else
            {
                 if(!stiva.empty())
                 {val1 = stiva.top();
                stiva.pop();}
                else eroare=1;
                if(eroare==0)
                {if(s[i]=='s')
                    stiva.push(int(sin(val1)));
                else if(s[i]=='c')
                    stiva.push(int(cos(val1)));
                else if(s[i]=='r')
                    stiva.push(int(sqrt(val1)));
                else if(s[i]=='a')
                    stiva.push(abs(val1));
                else if(s[i]=='t')
                    stiva.push(int(tan(val1)));
                else if(s[i]=='l')
                    stiva.push(int(log(val1)));
                else if(s[i]=='m')
                    stiva.push(-(val1));
                }
                i++;
            }

        }
        else i++;
    }


    if(!stiva.empty())
    {varf_stiva=stiva.top();
    stiva.pop();
    }
    else eroare=1;
    if(!stiva.empty())
        eroare=1;

    return varf_stiva;

    //cout << "The Top: " << the_top << "\n";
}

#endif // EVALUARE_H_INCLUDED
