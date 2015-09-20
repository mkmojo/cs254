import sys

def dfs(level, total, ans):
    if total == 0:
        print( "(" +  ans + (")"*level) + ")" )
    elif level == 0:
        dfs(level+1, total-1, ans + "(")
    else:
        dfs(level+1, total-1, ans + "(")
        dfs(level-1, total, ans + ")")

def trees(n):
    dfs(0, n-1, "")

def main():
    print ("How many points do you have ?")
    x = int(sys.stdin.readline());
    trees(x)

if __name__ == "__main__":
    main()
