using System;

public class PrintTree
{
    public void dfs(int level, int total)
    {
        if(total == 0){
            string right = new String(')', 2*n_nodes - ans.Length);
            Console.WriteLine(ans+right);
            return;
        }

        if(level == 0){
            ans+="(";
            dfs(level+1, total-1);
            ans = ans.Remove(ans.Length-1);
        } else{
            ans+="(";
            dfs(level+1, total-1);
            ans = ans.Remove(ans.Length-1);
            ans+=")";
            dfs(level-1, total);
            ans = ans.Remove(ans.Length-1);
        }
    }

    private string ans="(";
    private int n_nodes;
    //constructor
    public PrintTree(int x)
    {
        this.n_nodes = x;
    }

    public void print_tree()
    {
        dfs(0, n_nodes-1);
    }

    public static void Main(string[] args)
    {
        string line;
        Console.WriteLine("\nHow many points do you have?");
        line = Console.ReadLine();
        PrintTree p = new PrintTree(Int32.Parse(line));
        p.print_tree();
    }

}
