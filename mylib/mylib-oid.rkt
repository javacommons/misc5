#lang racket
(provide to-oid from-oid oid-count)

(define $oid-ht (make-weak-hasheq))
(define $oid-reverse-ht (make-hasheq))
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
           (hash-set! $oid-reverse-ht $oid-next (make-weak-box %x))
           (set! $oid-next (+ $oid-next 1)))))))

(void (to-oid #f))

(define (from-oid %oid)
  (call-with-semaphore
   $oid-semaphore
   (lambda ()
     (define %box (hash-ref $oid-reverse-ht %oid #f))
     (and %box
          (weak-box-value %box)))))

(define (oid-count)
  (hash-count $oid-ht))
