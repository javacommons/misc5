#lang racket

; https://gist.github.com/jessealama/e414903ea119e316a8419490a8418033
(require http) ;; not installed by default
               ;; do raco pkg install http

(define (http-request uri
                      #:redirects [redirects 10]
                      #:http-version [http-version "1.1"]
                      #:method [method "GET"]
                      #:data [data #""]
                      #:data-length [data-length #f]
                      #:heads [heads empty]
                      #:entity-reader [entity-reader read-entity/bytes])
  (if (and (bytes? data)
           (bytes=? data #"")
           (eq? data-length #f))
      (call/input-request http-version
                          method
                          uri
                          heads
                          entity-reader
                          #:redirects redirects)
      (call/output-request http-version
                           method
                           uri
                           data
                           data-length
                           heads
                           entity-reader
                           #:redirects redirects)))

(provide http-request)
