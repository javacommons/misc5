#lang racket
(provide to-oid from-oid oid-count)

(define $oid-ht-1 (make-weak-hasheq))
(define $oid-ht-2 (make-hasheq))
(define $oid-next 0)
(define $oid-semaphore (make-semaphore 1))

(define (to-oid %v)
  (call-with-semaphore
   $oid-semaphore
   (lambda ()
     (define %oid (hash-ref $oid-ht-1 %v #f))
     (or %oid
         (begin0
           $oid-next
           (hash-set! $oid-ht-1 %v $oid-next)
           (hash-set! $oid-ht-2 $oid-next (make-weak-box %v))
           (set! $oid-next (+ $oid-next 1)))))))

(void (to-oid #f))

(define (from-oid %oid)
  (call-with-semaphore
   $oid-semaphore
   (lambda ()
     (define %box (hash-ref $oid-ht-2 %oid #f))
     (and %box
          (weak-box-value %box)))))

(define (oid-count)
  (hash-count $oid-ht-1))
