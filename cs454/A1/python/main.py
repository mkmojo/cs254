import sys

ans = "("

def trees(n_nodes):
    #define function inside function
    def dfs(level, total):
        global ans
        if total == 0:
            #found one answer
            #print( ans + ")"*(2*int(n_nodes)-len(ans)) )
            print (ans + ")" * (level+1))
            return
        if level == 0:
            #at root, have to move deeper
            ans += '('
            dfs(level+1, total-1)
            ans = ans[0:-1]
        else:
            #have real choice, do one at a time
            ans += '('
            dfs(level+1, total-1)
            ans = ans[0:-1]

            ans += ')'
            dfs(level-1, total)
            ans = ans[0:-1]

    #start recursion from root
    dfs(0, n_nodes-1)

def main():
    print ("How many points do you have ?")
    x = sys.stdin.readline();
    trees(int(x))

if __name__ == "__main__":
    main()
