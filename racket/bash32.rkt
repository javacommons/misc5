#lang racket

(define $path (find-system-path 'run-file))
$path
(define $path-text (path->string $path))
$path-text
(regexp-match? (regexp "[.]rkt$") $path-text)
(regexp-match? (regexp "[.]rkt$") $path)
(printf "$path is ~s\n" $path)
(printf "$path is ~a\n" $path)
(define $abs-path (path->complete-path $path))
$abs-path
(string-split (path->string $abs-path) "\\")
