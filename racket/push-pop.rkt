#lang racket
(provide push pop)

(require compatibility/defmacro)

(define-macro (push %x %l)
  (define %%pair (gensym "%%pair-"))
  `(let ([,%%pair (cons ,%x ,%l)])
     (set! ,%l ,%%pair)
     ,%%pair))

(define-macro (pop %l)
  (define %%car (gensym "%%car-"))
  `(if (or (null? ,%l) (not (pair? ,%l)))
       (void)
       (let ([,%%car (car ,%l)])
         (set! ,%l (cdr ,%l))
         ,%%car)))

;(pretty-print (push 'X 'L))
;(pretty-print (pop 'L))
