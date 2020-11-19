#lang racket

(define $dummy (void))

(define $run-file (find-system-path 'run-file))
;$run-file
(define $abs-run-file (path->complete-path $run-file))
;$abs-run-file
(define $split (string-split (path->string $abs-run-file) "\\"))
;$split
(define $filename (last $split))
(define (all-but-last %lst) (reverse (cdr (reverse %lst))))
(define $root (string->path (string-join (all-but-last $split) "\\")))
;$root
(set! $dummy (putenv "HOME" (format "~a\\home\\~a" $root (getenv "USERNAME"))))
(define $path (getenv "PATH"))
(define $path-list
  (list
   (path->string (build-path $root "usr" "local" "bin"))
   (path->string (build-path $root "usr" "bin"))
   $path))
(set! $path (string-join $path-list ";"))
(set! $dummy
      (cond
        [(equal? $filename "bash32.exe")
         ;(println "<bash32>")
         (set! $path (format "~a;~a" (path->string (build-path $root "mingw32" "bin")) $path))
         (putenv "MINGW_CHOST" "i686-w64-mingw32")
         (putenv "MINGW_PACKAGE_PREFIX" "mingw-w64-i686")
         (putenv "MINGW_PREFIX" "/mingw32")
         (putenv "MSYSTEM_CARCH" "i686")
         (putenv "MSYSTEM_CHOST" "i686-w64-mingw32")
         (putenv "MSYSTEM_PREFIX" "/mingw32")
         (putenv "MSYSTEM" "MINGW32")
         ]
        [#t ;(equal? $filename "bash64.exe")
         ;(println "<bash64>")
         (set! $path (format "~a;~a" (path->string (build-path $root "mingw64" "bin")) $path))
         (putenv "MINGW_CHOST" "x86_64-w64-mingw32")
         (putenv "MINGW_PACKAGE_PREFIX" "mingw-w64-x86_64")
         (putenv "MINGW_PREFIX" "/mingw64")
         (putenv "MSYSTEM_CARCH" "x86_64")
         (putenv "MSYSTEM_CHOST" "x86_64-w64-mingw32")
         (putenv "MSYSTEM_PREFIX" "/mingw64")
         (putenv "MSYSTEM" "MINGW64")
         ]
        ))
(set! $dummy (putenv "PATH" $path))
;(println "before")
(set! $dummy (system (format "~a\\bash.exe" (build-path $root "usr" "bin"))))
;(println "after")
