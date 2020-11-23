#! racket32
#lang racket

(require net/http-easy) ; raco pkg install --auto http-easy
(require dyoo-while-loop) ; raco pkg install --auto while-loop
(require http)

(define (listen-for-progress in)
  (sync (port-progress-evt in))
  (unless (port-closed? in)
    (define-values [line col pos] (port-next-location in))
    (printf "\rbytes read: ~a" pos)
    (listen-for-progress in)))

(define (read-with-progress)
  ;(define res (get "https://www.google.com/" #:stream? #t))
  (define res (get "https://repo.msys2.org/distrib/x86_64/msys2-base-x86_64-20200903.tar.xz" #:stream? #t))
  (define in (response-output res))
  ;(thread (λ () (listen-for-progress in)))
  #| do something with in |#
  (define %bytes (port->bytes in))
  (printf "\n")
  %bytes
  )

;(define $bytes (read-with-progress))
;(bytes-length $bytes)

(define (::reader %in %response-headers)
  (thread (λ () (listen-for-progress %in)))
  (define %bytes (read-entity/bytes %in %response-headers))
  (sleep 0.1)
  (printf "\rbytes read: ~a\n" (bytes-length %bytes))
  %bytes)

(define $bytes
(call/input-request "1.1"
                    "GET"
                    "https://repo.msys2.org/distrib/x86_64/msys2-base-x86_64-20200903.tar.xz" ; "https://www.google.com/"
                    empty
                    ::reader
                    #:redirects 10)
)
(bytes-length $bytes)
