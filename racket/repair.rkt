#lang racket

(require "zip-install.rkt")

(get-registry-env "USER" "xyz")

(define $path (get-registry-env "USER" "PATH"))
$path

(define $path-list (string-split $path ";"))
$path-list

(define (is-msys64 %x)
  (regexp-match? (regexp "\\\\msys64\\\\") %x))

(is-msys64 "C:\\Users\\user\\.software\\msys64\\mingw64\\bin")

(delete-registry-env! "USER" "HOME")
(delete-registry-env! "USER" "MSYSTEM")
(delete-registry-env! "USER" "MSYSTEM_CARCH")
(delete-registry-env! "USER" "MSYSTEM_CHOST")

(filter is-msys64 $path-list)
;(filter not-msys64 $path-list)
(define $list1 (filter (lambda (%x) (not (is-msys64 %x))) $path-list))
$list1
(define $list2 (map (lambda (%x) (string-replace %x "\\\\" "\\")) $list1))
$list2
(string-join $list2 ";")
(set-registry-env! "USER" "PATH" (string-join $list2 ";"))
