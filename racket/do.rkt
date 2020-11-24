#! racket32
#lang racket

(define $list '(11 22 33))

(do ([$l $list (cdr $l)])
    ((null? $l) (void))
  (println (car $l))
  )

(define $e (void))
(do ([$l $list (cdr $l)])
    ((null? $l) (void))
  (set! $e (car $l))
  (println $e)
  )

(require "push-pop.rkt")

(pop $list)
$list
(push 100 $list)
$list

(require dyoo-while-loop) ; raco pkg install --auto while-loop

(define $top $list)
(while (not (null? $top))
  (define $e (pop $top))
  (println $e)
 )

(for ([$e $list])
  (println $e)
 )

(set! $list '())
(println (pop $list))
(set! $list 123)
(println (pop $list))
