#lang racket

(require file/resource)

(write-resource
 "HKEY_CURRENT_USER"
 "javacommons\\htmlfile\\shell\\open\\command4"
 "javacommons value"
 #:type 'string
 #:create-key? #t)

(get-resource
 "HKEY_CURRENT_USER"
 "javacommons\\htmlfile\\shell\\open\\command4")
