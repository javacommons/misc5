#! racket32
#lang racket

(require ffi/com)

(string->clsid "{17eb186b-4677-4d9c-b179-9b3715e5d1e6}")
(clsid->progid (string->clsid "{17eb186b-4677-4d9c-b179-9b3715e5d1e6}"))

(define $obj1 (com-create-instance "javacommons.Object1" 'local))
;(define $obj1 (com-create-instance "17eb186b-4677-4d9c-b179-9b3715e5d1e6" 'local))
(com-invoke $obj1 "Add2" 11 22)
(com-invoke $obj1 "Add2" 11 (/ 1 3))

