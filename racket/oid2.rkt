#! racket
#lang racket
; https://stackoverflow.com/questions/56386674/unique-identifier-for-racket-objects

(define $oid-ht (make-weak-hasheq))
(define $oid-next 0)
(define $oid-semaphore (make-semaphore 1))

(define (to-oid %x)
  (call-with-semaphore
   $oid-semaphore
   (lambda ()
     (define %oid (hash-ref $oid-ht %x #f))
     (or %oid
         (begin0
           $oid-next
           (hash-set! $oid-ht %x $oid-next)
           (set! $oid-next (+ $oid-next 1)))))))

(define (from-oid %oid)
  (define $result (void))
  (hash-for-each
   $oid-ht
   (lambda (%key %value)
     (when (= %value %oid)
       (set! $result %key))))
  $result)

(to-oid 'a)
(to-oid 'b)
(to-oid 'a)
(define $list (list 11 22 33))
(define $list2 (list 11 22 33))
(to-oid $list)
(to-oid $list2)
(to-oid $list)

(from-oid 2)

(to-oid (void))

(hash-count $oid-ht)
(set! $list (void))
(set! $list2 (void))
(collect-garbage)
(hash-count $oid-ht)
(eq? $list $list2)

(define $th (current-thread))
(to-oid $th)
