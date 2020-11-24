#lang racket
(provide push pop)

(require compatibility/defmacro)

(define-macro (push %x %l)
  `(let ([%%pair (cons ,%x ,%l)])
     (set! ,%l %%pair)
     %%pair))
 
(define-macro (pop %l)
  `(if (or (null? ,%l) (not (pair? ,%l)))
       (void)
       (let ([%%car (car ,%l)])
         (set! ,%l (cdr ,%l))
         %%car)))
