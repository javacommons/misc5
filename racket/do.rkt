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

(require compatibility/defmacro)


(define-macro (push %x %l)
  `(let ([%new (cons ,%x ,%l)])
     (set! ,%l %new)
     %new))
 
(define-macro (pop %l)
  `(let ([%car (car ,%l)])
     (set! ,%l (cdr ,%l))
     %car))
 
(pop $list)
$list
(push 100 $list)
$list
