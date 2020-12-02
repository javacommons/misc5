#lang racket
; https://stackoverflow.com/questions/56386674/unique-identifier-for-racket-objects

(define ht (make-weak-hasheq))
(define next 0)

(define (get-id x)
  (define id (hash-ref ht x #f))
  (or id
      (begin0
        next
        (hash-set! ht x next)
        (set! next (+ next 1)))))

(get-id 'a)
(get-id 'b)
(get-id 'a)
(define $list (list 11 22 33))
(get-id $list)
(get-id $list)
