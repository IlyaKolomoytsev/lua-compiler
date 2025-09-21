%{
#include <iostream>
%}

%%
[0-9]+      { std::cout << "Number: " << yytext << std::endl; }
[a-zA-Z]+   { std::cout << "Word: " << yytext << std::endl; }
.           { std::cout << "Other: " << yytext << std::endl; }
%%
