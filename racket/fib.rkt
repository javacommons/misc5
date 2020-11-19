#lang racket

; Source: https://satosystems.hatenablog.com/entry/20121228/1356655565

(define (fib n)
  (if (< n 2)
    n
    (+ (fib (- n 2)) (fib (- n 1)))))

;(write (fib 38))
(write (fib 45))
(newline)