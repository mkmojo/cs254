(define (dfs level n str)
  (cond
    ((= n 0) (display (apply string-append (list "(" str (make-string level #\)) ")" ))) (newline))
    ((= level 0) (dfs (+ level 1) (- n 1) (string-append str "(") ))
    (else (dfs (+ level 1) (- n 1) (string-append str "("))
          (dfs (- level 1) n (string-append str ")") ))))

(define (trees n)
  (dfs 0 (- n 1) ""))

;;; Waite for stdin
(display "How many points do you have?")
(newline)
(define n (read))
(trees n)
