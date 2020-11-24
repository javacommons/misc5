#! racket32
#lang racket

(for ([i '(1 2 3)]
        [j "abc"]
        #:when (odd? i)
        [k #(#t #f)])
    (display (list i j k)))

(println "<newline>")

(for ([i '(1 2 3)]
        [j "abc"]
        [k #(#t #f)])
    (display (list i j k)))

(println "<newline>")

(for ([i '(1 2 3)]
        #:when #t
        [j "abc"]
        #:when #t
        [k #(#t #f)])
    (display (list i j k)))

(println "<newline>")

(for ([i '(1 2 3)] #:break (>= i 2))
    (display (list i)))

(println "<newline>")

(for ([i '(1 2 3)] #:final (>= i 2))
    (display (list i)))

(println "<newline>")

(for ([i 5])
    (display (list i)))
