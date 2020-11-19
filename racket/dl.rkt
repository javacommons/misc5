#lang racket

(require "http-request.rkt")

(http-request "https://www.google.com/")

(print 'before)
(define archive (http-request "https://repo.msys2.org/distrib/x86_64/msys2-base-x86_64-20200903.tar.xz"))
(print 'after)
