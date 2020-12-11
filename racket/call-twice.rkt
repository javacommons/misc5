#lang racket

(provide callTwice)

(require ffi/unsafe
         ffi/unsafe/define)

(define-ffi-definer define-call-twice (ffi-lib "call-twice"))
(define-call-twice callTwice (_fun (_fun _int -> _int) -> _int))
(define-call-twice setFunc (_fun (_fun _int -> _int) -> _void))
(define-call-twice callTriple (_fun -> _int))

(callTwice add1)
(setFunc add1)
(callTriple)