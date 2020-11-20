#! racket32
#lang racket
; https://docs.racket-lang.org/guide/concurrency.html
(define (make-arithmetic-thread operation)
  (thread (lambda ()
            (let loop ()
              (match (thread-receive)
                [(list oper1 oper2 result-thread)
                 (thread-send result-thread
                              (format "~a ~a ~a = ~a"
                                      oper1
                                      (object-name operation)
                                      oper2
                                      (operation oper1 oper2)))
                 (loop)])))))
 
(define addition-thread (make-arithmetic-thread +))
(define subtraction-thread (make-arithmetic-thread -))
 
(define worklist '((+ 1 1) (+ 2 2) (- 3 2) (- 4 1)))
(for ([item worklist])
  (match item
    [(list '+ o1 o2)
     (thread-send addition-thread
                  (list o1 o2 (current-thread)))]
    [(list '- o1 o2)
     (thread-send subtraction-thread
                  (list o1 o2 (current-thread)))]))
 
(for ([i (length worklist)])
  (displayln (thread-receive)))