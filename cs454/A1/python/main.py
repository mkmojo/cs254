import sys

ans = "("


def trees(n_nodes):
    def dfs(level, total):
        global ans
        if total == 0:
            print( ans + ")"*(2*int(n_nodes)-len(ans)) )
            return
        if level == 0:
            ans += '('
            dfs(level+1, total-1)
            ans = ans[0:-1]
        else:
            ans += '('
            dfs(level+1, total-1)
            ans = ans[0:-1]

            ans += ')'
            dfs(level-1, total)
            ans = ans[0:-1]

    dfs(0, n_nodes-1)

def main():
    print ("How many points do you have ?")
    x = sys.stdin.readline();
    trees(int(x))

if __name__ == "__main__":
    main()
