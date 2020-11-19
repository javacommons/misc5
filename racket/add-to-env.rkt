#lang racket

(require "zip-install.rkt")

(define &path (make-parameter (void)))

(command-line
   #:args (PATH)
   (&path PATH)
   (void))

(&path)

(new set-path% [:member (&path)])
(get-registry-env "USER" "PATH")
