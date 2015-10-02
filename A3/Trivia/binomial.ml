let rec fac = function 
| 0 -> 1
| n -> n * (fac (n - 1))
;;

let bc n k =
    (fac n) / ((fac k) * (fac (n - k)))
;;

