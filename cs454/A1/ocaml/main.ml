open String;;

let ans = ref "(";;

(*  Remove last char of a string.  *)
let strip_last_char str = 
    if str = "" then "" else
        String.sub str 0 ((String.length str) - 1) ;;

(*  Shorthand for getting length of a string.  *)
let len x = 
    String.length x ;;

(*  Construct a string with all ')' base on given lengths *)
let right_braces cnt_ans n_nodes = 
    String.make (2*n_nodes - (len cnt_ans)) ')'
;;

let rec dfs level total = match (level,total) with
     (* used all points, found one answer *)
     | (_, 0) -> print_string ( !ans ^ (right_braces !ans (int_of_string Sys.argv.(1)) ) ^ "\n" )
     (* can only move down the tree *)
     | (0, t) when t > 0 -> (ans := !ans ^ "(" ; 
                            dfs (level+1) (total-1);
                            ans := strip_last_char !ans)
     (* have a real choice, deal with one at a time *)
     | _  -> ((ans := !ans ^ "(" ; dfs (level+1) (total-1) ; ans := strip_last_char !ans ) ; 
                ( ans := !ans ^ ")" ; dfs (level-1) (total); ans := strip_last_char !ans ))
;;

let trees n_nodes = 
    dfs 0 (n_nodes-1)
;;

trees (int_of_string Sys.argv.(1)) 
