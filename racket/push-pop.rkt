#lang racket
(provide push pop)

(require compatibility/defmacro)

(define-macro (push %x %l)
  `(let ([%%new (cons ,%x ,%l)])
     (set! ,%l %%new)
     %%new))
 
(define-macro (pop %l)
  `(let ([%%car (car ,%l)])
     (set! ,%l (cdr ,%l))
     %%car))
