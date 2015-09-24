open String;;

let rec dfs level total ans = match (level,total) with
     (*type error at this arm of recurssion*)
     |(_, 0) -> (print_newline (print_string (  "(" ^ ans^(String.make level ')') ^")" )) )
     |(0, _) -> ( dfs (level+1) (total-1) ( ans^"(" ) )
     | _  -> ( dfs (level+1) (total-1) ( ans^"(" );
                dfs (level-1) (total) ( ans^")" ) )
;;

let trees n_nodes = 
    dfs 0 (n_nodes-1) ""
;;

trees (int_of_string Sys.argv.(1)) 
;;
