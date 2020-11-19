#lang racket

(require ffi/unsafe
         ffi/unsafe/define)
(require msgpack)
(require net/base64)

(define-ffi-definer define-arch (ffi-lib "arch"))

(define-arch apicall (_fun _string/latin-1 _string/latin-1 -> _string/latin-1))

(define (arch-api name args)
  (printf "api-name=~s args=~s\n" name args)
  (let* ([packed-args #f] [base64-args #f] [base64-result #f] [packed-result #f] [result #f])
    (set! packed-args (pack args))
    ;(printf "(A)packed-args=~s\n" packed-args)
    (set! base64-args (base64-encode packed-args #""))
    ;(printf "(B)base64-args=~s\n" (bytes->string/latin-1 base64-args))
    (set! base64-result (apicall name (bytes->string/latin-1 base64-args)))
    ;(printf "(C)base64-result=~s\n" base64-result)
    (set! packed-result (base64-decode (string->bytes/latin-1 base64-result)))
    ;(printf "(D)packed-result=~s\n" packed-result)
    (set! result (unpack packed-result))
    ;(printf "(E)result=~s\n" result)
    result
    )
  )

(define (arch-api* name . args)
  (arch-api name args)
  )

;(provide (all-defined-out))
(provide arch-api arch-api*)
