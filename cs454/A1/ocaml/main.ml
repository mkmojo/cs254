open String;;

let ans = ref "(";;

let strip_last_char str = 
    if str = "" then "" else
        String.sub str 0 ((String.length str) - 1)
;;

let len x = 
    String.length x
;;

let right_braces cnt_ans n_nodes = 
    String.make (2*n_nodes - (len cnt_ans)) ')'
;;

let rec dfs level total = match (level,total) with
     | (_, 0) -> print_string ( !ans ^ (right_braces !ans (int_of_string Sys.argv.(1)) ) ^ "\n" )
     | (0, t) when t > 0 -> (ans := !ans ^ "(" ; 
                            dfs (level+1) (total-1);
                            ans := strip_last_char !ans)
     | _  -> ((ans := !ans ^ "(" ; dfs (level+1) (total-1) ; ans := strip_last_char !ans ) ; 
                ( ans := !ans ^ ")" ; dfs (level-1) (total); ans := strip_last_char !ans ))
;;

let print_tree n_nodes = 
    dfs 0 (n_nodes-1)
;;

print_tree (int_of_string Sys.argv.(1)) 
