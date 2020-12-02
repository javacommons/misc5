#lang racket
(define a (cons 1 2))
(define b (cons 3 4))
(define e (make-ephemeron a b))
(set! a #f)
(writeln (ephemeron-value e))
(collect-garbage 'major)
(writeln (ephemeron-value e))
