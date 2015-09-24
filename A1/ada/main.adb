with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;

procedure Main is
    N_points : integer := 0;
    Count : integer := 0;
    ans : Unbounded_String := To_Unbounded_String("(");

    procedure DFS(N: Integer; L: Integer) is
        right_braces : Unbounded_String := To_Unbounded_String("");
    begin
        if N = 0 then
            Count := Count + 1;
            right_braces := (N_points * 2 - Length(ans) ) * ")";
            put(ans & right_braces);
            new_line;
            return;
        elsif L = 0 then
            ans := ans & "(";
            DFS(N-1, L+1);
            ans := Head(ans, Length(ans)-1);
        else
            ans := ans & "(";
            DFS(N-1, L+1);
            ans := Head(ans, Length(ans)-1);
            ans := ans & ")";
            DFS(N, L-1);
            ans := Head(ans, Length(ans)-1);
        end if;
    end DFS;

    procedure Trees(N: Integer) is
    begin
        DFS(N-1, 0);
    end Trees;

begin
    new_line;
    put_line("How many points do you have?");
    get(N_points);
    Trees(N_points);
    put(Count);
    new_line;
end Main;
