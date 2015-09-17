% source from this URL with simple modification:
% http://stackoverflow.com/questions/29272927/enumerating-binary-trees-in-prolog
:- [library(clpfd)].
trees(0,[]).
trees(N, [L|R]) :-
    N #> 0,
    N #= N1 + N2 + 1,
    N1 #>= 0, N2 #>= 0,
    trees(N1, L), trees(N2, R).
