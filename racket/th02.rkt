#! racket32
#lang racket
; https://docs.racket-lang.org/guide/concurrency.html
(define worker (thread
                 (lambda ()
                   (for ([i 100])
                     (printf "Working hard... ~a~n" i)))))
(thread-wait worker)
(displayln "Worker finished")