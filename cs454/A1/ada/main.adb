with Ada.Text_IO; 
use Ada.Text_IO;
with Ada.Integer_Text_IO;
use Ada.Integer_Text_IO;


procedure Main is
    N : integer := 0;
    type Ans is array(Integer range <>) of Character;

    procedure DFS(N: Integer; L: Integer) is
    begin
        return;
    end DFS;

    procedure Trees(N: Integer) is
    begin
        DFS(N-1, 0);
    end Trees;



begin
    get(N);
    put(N);
    put(ans);
end Main;
