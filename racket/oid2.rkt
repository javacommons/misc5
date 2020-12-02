#! racket
#lang racket
; https://stackoverflow.com/questions/56386674/unique-identifier-for-racket-objects

(define $oid-ht (make-weak-hasheq))
(define $oid-next 0)
(define $oid-semaphore (make-semaphore 1))

(define (get-oid x)
  (call-with-semaphore $oid-semaphore
   (lambda ()
     (define id (hash-ref $oid-ht x #f))
     (or id
         (begin0
           $oid-next
           (hash-set! $oid-ht x $oid-next)
           (set! $oid-next (+ $oid-next 1)))))))

(get-oid 'a)
(get-oid 'b)
(get-oid 'a)
(define $list (list 11 22 33))
(define $list2 (list 11 22 33))
(get-oid $list)
(get-oid $list2)
(get-oid $list)
