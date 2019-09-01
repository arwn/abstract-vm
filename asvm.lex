%{
  #include <iostream>
  #include "operand.hpp"
%}
%option noyywrap
%option c++


string  \"[^\n"]+\"

alpha   [A-Za-z]
dig     [0-9]
name    ({alpha}|{dig}|\$)({alpha}|{dig}|[_.\-/$])*
num     [-+]?{dig}+
num1    [-+]?{dig}+\.?([eE][-+]?{dig}+)?
num2    [-+]?{dig}*\.{dig}+([eE][-+]?{dig}+)?
number  {num1}|{num2}
comment ;.+
int8    int8\({num}\)
int16   int16\({num}\)
int32   int32\({num}\)
float   float\({number}\)
double  double\({number}\)

%%
;;				  {return (int)commandtype::EndStream;}
{comment}   {return (int)septype::Comment;}
exit			  {return (int)commandtype::Exit;}
push			  {return (int)commandtype::Push;}
pop				  {return (int)commandtype::Pop;}
dump			  {return (int)commandtype::Dump;}
assert		  {return (int)commandtype::Assert;}
add				  {return (int)commandtype::Add;}
sub				  {return (int)commandtype::Sub;}
mul				  {return (int)commandtype::Mul;}
div				  {return (int)commandtype::Div;}
mod				  {return (int)commandtype::Mod;}
print			  {return (int)commandtype::Print;}
emit        {return (int)commandtype::Emit;}
{int8}		  {return (int)optype::Int8;}
{int16}     {return (int)optype::Int16;}
{int32}     {return (int)optype::Int32;}
{float}     {return (int)optype::Float;}
{double}    {return (int)optype::Double;}
[ \t]			  {return (int)septype::Space;}
[\n]			  {return (int)septype::Newline;}
{name}      {return -1;}
{number}    {return -1;}
.           {return -1;}
%%
