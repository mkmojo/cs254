import sys

ans = "("

def dfs(level, total):
    global ans
    if total == 0:
        print( ans + ")"*(2*int(sys.argv[1])-len(ans)) )
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

def trees(n_nodes):
    dfs(0, n_nodes-1)

def main():
    trees(int(sys.argv[1]))

if __name__ == "__main__":
    main()
