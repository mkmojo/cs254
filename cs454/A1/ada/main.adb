with Ada.Text_IO; 
use Ada.Text_IO;
with Ada.Integer_Text_IO;
use Ada.Integer_Text_IO;


procedure Main is
    N : integer := 0;
    type Ans is array(Integer range <>) of Character;

    procedure DFS(N: Integer; L: Integer) is
    begin
        if N = 0 then
            return;
        elsif L = 0 then
            DFS(N-1, L+1);
        else
            DFS(N-1, L+1);
            DFS(N, L-1);
        end if;
    end DFS;

    procedure Trees(N: Integer) is
    begin
        DFS(N-1, 0);
    end Trees;



begin
    get(N);
    Trees(18);
    put(N);
end Main;
