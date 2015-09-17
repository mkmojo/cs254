;;(define total (string->number (vector-ref (current-command-line-arguments) 0)))

(define (right-braces tot cnt_string)
  (make-string (- (* tot 2) 
                  (string-length cnt_string)) 
               #\)))

(define (dfs level n str total)
  (cond
    ((= n 0) (display str) (display (right-braces total str)) (newline))
    ((= level 0) (dfs (+ level 1) (- n 1) (string-append str "(") total ))
    (else (dfs (+ level 1) (- n 1) (string-append str "(") total)
          (dfs (- level 1) n (string-append str ")") total ))))


(define (trees level n)
  (dfs level (- n 1) "(" n))

;;; Waiting for stdin
(display "How many points do you have?")
(newline)
(define n (read))
(trees 0 n)
