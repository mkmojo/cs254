% source from this URL with simple modification:
% http://stackoverflow.com/questions/29272927/enumerating-binary-trees-in-prolog
:- [library(clpfd)].
:- write("\nPlese use trees(N-1, L). if you have N points \n").
:- write("For instance, when you have 5 points please use trees(4, L).\n\n").
 
trees(0,[]).
trees(N, [L|R]) :-
    N #> 0,
    N #= N1 + N2 + 1,
    N1 #>= 0, N2 #>= 0,
    trees(N1, L), trees(N2, R).
